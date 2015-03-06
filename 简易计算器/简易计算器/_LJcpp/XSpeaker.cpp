#include "stdafx.h"
#ifdef XSPEAKER_
namespace LJ
{
	namespace Sound
	{
		//VSpeaker类
		const XTypes& VSpeaker::CurrentType = CREATECLASSTYPE(LJ::Sound::VSpeaker,LJ::XBase);
		const XTypes& XSpeaker::CurrentType = CREATECLASSTYPE(LJ::Sound::XSpeaker,LJ::XBase);
		VSpeaker::VSpeaker()
			:hz(SoundEnvironment::DefaultHz),ch(SoundEnvironment::DefaultChannels),bits(SoundEnvironment::DefaultBits),isFloat(false),//设置默认格式
			isPlaying(false),started(false),isSelecting(false),isWriting(false),
			pDevice(NULL),
			DeviceID(XString::Empty),DeviceName(XString::Empty),
			pAudioClient(NULL),pRenderClient(NULL),
			SpeakingFormat(),
			hnsRequestedDuration(SoundEnvironment::DefaultSpeakerRequestedDuration),
			converter(),
			isClosing(false),
			UsingDefaultDevice(true)
		{
			buffer.SetMinimumSizeBefore(0);
			SelectDeviceById(XString::Empty);
			SoundEnvironment::AddSpeaker(this);
		}
		VSpeaker::~VSpeaker()
		{
			SoundEnvironment::RemoveSpeaker(this);
			isClosing = true;
			tc.ThreadWait();
			Stop();
			DeviceName = XString::Empty;
			if(pRenderClient)pRenderClient->Release();
			pRenderClient = NULL;
			if(pAudioClient)pAudioClient->Release();
			pAudioClient = NULL;
			if(pDevice)pDevice->Release();
			pDevice = NULL;
			tc.ThreadDone();
			int i=0;
			while((isWriting || isSelecting )&& i++<50){isClosing = true;Sleep(10);}
		}
		void VSpeaker::Close()
		{
			tc.ThreadWait();
			isClosing = true;
			Stop();
			DeviceName = XString::Empty;
			DeviceID =XString::Empty;
			if(pRenderClient)pRenderClient->Release();
			pRenderClient = NULL;
			if(pAudioClient)pAudioClient->Release();
			pAudioClient = NULL;
			if(pDevice)pDevice->Release();
			pDevice = NULL;
			isClosing = false;
			tc.ThreadDone();
		}
		void VSpeaker::Start()
		{
			while(!tc.ThreadTry())
			{
				if(isClosing)return;
				Sleep(1);
			}
			if(pAudioClient)
			{
				pAudioClient->Start();
				isPlaying = true;
				started = true;
			}
			tc.ThreadDone();
		}
		void VSpeaker::Stop()
		{
			while(!tc.ThreadTry())
			{
				if(isClosing)return;
				Sleep(1);
			}
			if(isPlaying && pAudioClient)
			{
				isPlaying = false;
				started = false;
				pAudioClient->Stop();
				buffer.Reset();
			}
			tc.ThreadDone();
		}
		//清空缓存内容
		void VSpeaker::Clear()
		{
			while(!tc.ThreadTry()){if(isClosing)return;}
			buffer.Reset();
			tc.ThreadDone();
		}
		void VSpeaker::Pause()
		{
			while(!tc.ThreadTry())
			{
				if(isClosing)return;
				Sleep(1);
			}
			if(pAudioClient)
			{
				isPlaying = false;
				pAudioClient->Stop();
			}
			tc.ThreadDone();
		}
		void VSpeaker::SetFormat(double hz,short bits,short ch,bool isfloat)
		{
			if(hz<=0 || this->hz==hz && this->ch==ch && this->bits==bits && this->isFloat==isfloat)return;
			tc.ThreadWait();
			buffer.Reset();
			this->hz = hz;
			this->ch = ch;
			this->bits = bits;
			this->isFloat = isfloat;
			converter.SetFormat(hz,bits,ch,isfloat);
			tc.ThreadDone();
			return;
		}
		void VSpeaker::SetFormat(const WAVEFORMATEX& pwfx)
		{
			SetFormat(pwfx.nSamplesPerSec,pwfx.wBitsPerSample,pwfx.nChannels,pwfx.wFormatTag == 0xfffe);
		}
		void VSpeaker::SetToDefaultFormat()
		{
			SetFormat(SoundEnvironment::DefaultHz,SoundEnvironment::DefaultBits,SoundEnvironment::DefaultChannels);
		}
		void VSpeaker::GetFormat(int* phz,short* pbits,short* pch,bool* pIsfloat)
		{
			if(phz)*phz = (int)hz;
			if(pch)*pch = ch;
			if(pbits)*pbits = bits;
			if(pIsfloat)*pIsfloat = isFloat;
		}
		WAVEFORMATEX VSpeaker::GetFormat()
		{
			int hz;short bits;short ch;bool isfloat;
			GetFormat(&hz,&bits,&ch,&isfloat);
			return VWave::MakeFormat(hz,bits,ch,isfloat);
		}
		void VSpeaker::SetVol(double vol)
		{
			converter.Volume = vol;
		}
		double VSpeaker::GetVol()const
		{
			return converter.Volume;
		}
		void VSpeaker::SetBufferTime(const XTime& hus)
		{
			XTime hms(hus);
			if(hms<SoundEnvironment::MinimumSpeakerRequestedDuration)//限制
				hms = SoundEnvironment::MinimumSpeakerRequestedDuration;
			if(hms == hnsRequestedDuration)return;
			hnsRequestedDuration = hms;
			bool pa = started && !isPlaying;
			SelectDeviceById(DeviceID);
			if(pa)Pause();
		}
		bool VSpeaker::SelectDeviceById(const XString& id)
		{
			HRESULT hr=0;
			isSelecting = true;
			while(!tc.ThreadTry())
			{
				if(isClosing)
				{
					isSelecting = false;
					return false;
				}
				Sleep(1);
			}
			Close();//关闭，重新建立会话
			if(pDevice = id.IsNullOrEmpty()?SoundEnvironment::GetDefaultSpeakingDevice():SoundEnvironment::GetDevice(id))//获取设备成功
			{
				DeviceID = id;
				DeviceName = SoundEnvironment::GetDeviceName(id);//设备名称
				if(SUCCEEDED(pDevice->Activate(IID_IAudioClient, CLSCTX_ALL, NULL, (void**)&pAudioClient)))//激活会话
				{
					//获取混音格式
					WAVEFORMATEX* pwfx;
					if(FAILED(hr=pAudioClient->GetMixFormat(&pwfx)))goto End;
					SpeakingFormat = *pwfx;
					//使用共享模式，按hnsRequestedDuration的时间间隔进行初始化
					if(FAILED(hr=pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED,0,hnsRequestedDuration,0,pwfx,NULL)))goto End;
					CoTaskMemFree(pwfx);
					//获取块帧数
					if(FAILED(hr=pAudioClient->GetBufferSize(&bufferFrameCount)))goto End;
					//获取播放服务
					if(FAILED(hr=pAudioClient->GetService(IID_IAudioRenderClient,(void**)&pRenderClient)))goto End;
				}
				isSelecting = false;
				tc.ThreadDone();
				return true;
			}
End:;
			isSelecting = false;
			if(FAILED(hr))
			{
				Close();
				tc.ThreadDone();
				throw XSoundException(hr);
			}
			tc.ThreadDone();
			return false;
		}
		bool VSpeaker::SelectDeviceByName(const XString& name)
		{
			return SelectDeviceById(SoundEnvironment::GetDeviceID(name));
		}
		void VSpeaker::Restart()
		{
			bool pa = started && !isPlaying;
			SelectDeviceById(DeviceID);
			if(pa)Pause();
			else Start();
		}
		//设备添加事件
		void VSpeaker::OnDeviceAdded()
		{
			try{
			if(SoundEnvironment::OnAddedDeviceId==this->DeviceID)Restart();
			}catch(...)
			{
				Sleep(500);
			try{
				SelectDeviceById(SoundEnvironment::OnAddedDeviceId);
			}catch(...)
			{
			}
			}
		}
		//设备状态改变事件
		void VSpeaker::OnDeviceStateChanged()
		{
			
		}
		//设备移除事件
		void VSpeaker::OnDeviceRemoved()
		{
			try{
			if(SoundEnvironment::OnRemovedDeviceId==this->DeviceID)Close();
			}catch(...){}
		}
		//默认设备改变事件
		void VSpeaker::OnDefaultDeviceChanged()
		{
			try{
			if(UsingDefaultDevice && SoundEnvironment::OnDefaultChangedFlow==eRender)SelectDeviceById(SoundEnvironment::OnDefaultChangedDeviceId);
			}catch(...)
			{
				Sleep(500);
			try{
			if(UsingDefaultDevice && SoundEnvironment::OnDefaultChangedFlow==eRender)SelectDeviceById(SoundEnvironment::OnDefaultChangedDeviceId);
			}catch(...){}
			}
		}
		//设备属性改变事件
		void VSpeaker::OnDevicePropertyValueChanged()
		{
		}
	}
}
#endif