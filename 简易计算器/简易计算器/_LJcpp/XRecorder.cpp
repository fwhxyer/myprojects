#include "stdafx.h"
#ifdef XRECORDER_
namespace LJ
{
	namespace Sound
	{
		//Recorder类

		VRecorder::VRecorder()
			:hz(SoundEnvironment::DefaultHz),ch(SoundEnvironment::DefaultChannels),bits(SoundEnvironment::DefaultBits),isFloat(false),//设置默认格式
			isRecording(false),started(false),isSelecting(false),isClosing(false),UsingDefaultDevice(true),
			DeviceID(XString::Empty),DeviceName(XString::Empty),
			pDevice(NULL),pAudioClient(NULL),pCaptureClient(NULL),
			CurrentFormat(),
			hnsRequestedDuration(SoundEnvironment::DefaultRecorderRequestedDuration),
			converter()
		{
			buffer.SetMinimumSizeBefore(0);
			SelectDeviceById(XString::Empty);
			//在environment中注册
			SoundEnvironment::AddRecorder(this);
		}
		VRecorder::~VRecorder()
		{
			SoundEnvironment::RemoveRecorder(this);//在environment中移除
			tc.ThreadWait();
			Close();
			int i=0;
			while(tc.GetThreadDeep()>=0 && i++<500){isClosing = 1;Sleep(10);}
		}
		void VRecorder::Start()
		{
			while(!tc.ThreadTry()){if(isClosing || isSelecting)return;Sleep(1);}
			if(pAudioClient)
			{
				pAudioClient->Start();
				started = true;
				isRecording = true;
			}
			tc.ThreadDone();
		}
		void VRecorder::Stop()
		{
			while(!tc.ThreadTry()){if(isClosing || isSelecting)return;Sleep(1);}
			if(isRecording && pAudioClient)
			{
				isRecording = false;
				started = false;
				pAudioClient->Stop();
			}
			tc.ThreadDone();
		}
		void VRecorder::Pause()
		{
			while(!tc.ThreadTry()){if(isClosing || isSelecting)return;Sleep(1);}
			if(isRecording && pAudioClient)
			{
				isRecording = false;
				pAudioClient->Stop();
			}
			tc.ThreadDone();
		}
		void VRecorder::Close()
		{
			tc.ThreadWait();
			isClosing = true;
			Stop();
			const_cast<XString&>(DeviceName) = XString::Empty;
			const_cast<XString&>(DeviceID) = XString::Empty;
			if(pCaptureClient)pCaptureClient->Release();
			pCaptureClient = NULL;
			if(pAudioClient)pAudioClient->Release();
			pAudioClient = NULL;
			if(pDevice)pDevice->Release();
			pDevice = NULL;
			isClosing = false;
			tc.ThreadDone();
		}
		void VRecorder::Clear()
		{
			while(!tc.ThreadTry()){if(isClosing)return;Sleep(1);}
			buffer.Reset();
			tc.ThreadDone();
		}
		double VRecorder::GetHz()const
		{return hz;}
		short VRecorder::GetChannels()const
		{return ch;}
		short VRecorder::GetBits()const
		{
			return bits;
		}
		bool VRecorder::GetIsFloat()const
		{
			return isFloat;
		}
		void VRecorder::SetOutFormat(double hz,short bits,short ch,bool isfloat)
		{
			if(hz<=0 || this->hz==hz && this->ch==ch && this->bits==bits && this->isFloat==isfloat)return;
			while(!tc.ThreadTry()){if(isClosing || isSelecting)return;Sleep(1);}
			buffer.Reset();
			this->hz = hz;
			this->ch = ch;
			this->bits = bits;
			this->isFloat = isfloat;
			tc.ThreadDone();
			return;
		}
		void VRecorder::SetOutFormat(const WAVEFORMATEX&pwfx)
		{
			SetOutFormat(pwfx.nSamplesPerSec,pwfx.wBitsPerSample,pwfx.nChannels,pwfx.wFormatTag == 0xfffe);
		}
		void VRecorder::GetOutFormat(int* phz,short* pbits,short* pch,bool* pisfloat)
		{
			if(phz)*phz = (int)hz;
			if(pch)*pch = ch;
			if(pbits)*pbits = bits;
			if(pisfloat)*pisfloat = isFloat;
		}
		void VRecorder::GetOutFormat(double* phz,short* pbits,short* pch,bool* pisfloat)
		{
			if(phz)*phz = hz;
			if(pch)*pch = ch;
			if(pbits)*pbits = bits;
			if(pisfloat)*pisfloat = isFloat;
		}
		WAVEFORMATEX VRecorder::GetOutFormat()
		{
			int hz;short bits,ch;bool isfloat;
			GetOutFormat(&hz,&bits,&ch,&isfloat);
			return VWave::MakeFormat(hz,bits,ch,isfloat);
		}
		WAVEFORMATEX& VRecorder::GetSourceFormat()
		{
			return CurrentFormat;
		}
		void VRecorder::GetSourceFormat(int* phz,short* pbits,short* pch,bool* pisfloat)
		{
			if(phz)*phz = CurrentFormat.nSamplesPerSec;
			if(pch)*pch = CurrentFormat.nChannels;
			if(pbits)*pbits = CurrentFormat.wBitsPerSample;
			if(pisfloat)*pisfloat = CurrentFormat.wFormatTag == 0xfffe;
		}
		void VRecorder::SetVol(double vol)
		{
			converter.Volume = vol;
		}
		double VRecorder::GetVol()const
		{
			return converter.Volume;
		}
		void VRecorder::SetBufferTime(const XTime& hus)
		{
			XTime hms(hus);
			if(hms<SoundEnvironment::MinimumRecorderRequestedDuration)//限制
				hms = SoundEnvironment::MinimumRecorderRequestedDuration;
			if(hms == hnsRequestedDuration)return;
			hnsRequestedDuration = hms;
			bool pa = started && !isRecording;
			SelectDeviceById(DeviceID);
			if(pa)Pause();
		}
		bool VRecorder::SelectDeviceById(const XString id)
		{
			while(!tc.ThreadTry()){if(isClosing)return false;Sleep(1);}
			isSelecting = true;
			HRESULT hr=0;
			//获取默认设备
			Close();//关闭，重新建立会话
			if(pDevice = id.IsNullOrEmpty()?SoundEnvironment::GetDefaultRecordingDevice():SoundEnvironment::GetDevice(id))//获取设备成功
			{
				const_cast<XString&>(DeviceID) = id;
				const_cast<XString&>(DeviceName) = SoundEnvironment::GetDeviceName(DeviceID);//设备名称
				if(SUCCEEDED(hr=pDevice->Activate(IID_IAudioClient, CLSCTX_ALL, NULL, (void**)&pAudioClient)))//激活会话
				{
					//获取混音格式
					WAVEFORMATEX* pwfx;
					if(FAILED(hr=pAudioClient->GetMixFormat(&pwfx)))goto End;
					CurrentFormat = *pwfx;
					//设置音源格式
					converter.SetFormat(CurrentFormat);//采样率和浮点转换
					//使用共享模式，按hnsRequestedDuration的时间间隔进行初始化,Initialize函数很挑剔，只识别CoTaskMemalloc分配的内存
					if(FAILED(hr=pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED,0,hnsRequestedDuration,0,pwfx,NULL)))
					{
						CoTaskMemFree(pwfx);
						goto End;
					}
					CoTaskMemFree(pwfx);
					//获取块帧数
					if(FAILED(hr=pAudioClient->GetBufferSize(&bufferFrameCount)))goto End;
					//获取播放服务
					if(FAILED(hr=pAudioClient->GetService(IID_IAudioCaptureClient,(void**)&pCaptureClient)))goto End;
					isSelecting = false;
					tc.ThreadDone();
					return true;
				}
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
		XArray<unsigned char> VRecorder::Read(int len)
		{
			if(!pCaptureClient)return XArray<unsigned char>(0);
			while(!tc.ThreadTry()){if(isClosing)return XArray<unsigned char>(0);Sleep(1);}
			if(!pCaptureClient)
			{
				tc.ThreadDone();
				return XArray<unsigned char>(0);
			}
			HRESULT hr=0;
			BYTE *pData;
			UINT32 numFramesAvailable;
			DWORD flags;
			if((int)buffer.Length<(len*2))//缓冲区域过小
			{
				buffer.Resize(len*2);
			}
			if(!started)Start();//自动开始
			while(started && pCaptureClient)
			{
				if((int)buffer.GetReadable()<len)//缓冲区内容过少
				{
					if(isClosing || isSelecting)
					{
						tc.ThreadDone();
						return XArray<unsigned char>(0);
					}
					if(isRecording)
					{
						if(FAILED(hr=pCaptureClient->GetNextPacketSize(&numFramesAvailable))){goto End;}//获取可读数据
					}
					else numFramesAvailable = 0;
					if(!numFramesAvailable)
					{
						Sleep(10);
						continue;
					}

					if(SUCCEEDED(hr=pCaptureClient->GetBuffer(&pData,&numFramesAvailable,&flags, NULL, NULL)) && !(flags & AUDCLNT_BUFFERFLAGS_SILENT))////获取可读数据;非静音
					{
						if(numFramesAvailable && pData)
						{
							XArray<unsigned char> tmp1 = converter.Convert(XArray<unsigned char>(numFramesAvailable*CurrentFormat.nBlockAlign,pData,Reference),hz,bits,ch,isFloat);//获得转换后的新内存和写入帧数量
							buffer.PutAfter(tmp1);//写入数据到缓冲区，这要求缓冲区有足够的空间
						}
					}
					else
					{
						Sleep(10);
						break;
					}
					if(FAILED(hr=pCaptureClient->ReleaseBuffer(numFramesAvailable))){goto End;}
					continue;
				}
				break;
			}
End:;
			if(FAILED(hr))
			{
				tc.ThreadDone();
				throw XSoundException(hr);
			}
			XArray<unsigned char> result = (int)buffer.GetReadable()>=len?buffer.GetAfter(len):XArray<unsigned char>(0);//读取数据
			tc.ThreadDone();
			return result;
		}
		XWaveData VRecorder::Read()
		{
			if(!pCaptureClient)return XWaveData();
			while(!tc.ThreadTry()){if(isClosing)return XWaveData();Sleep(1);}
			if(!pCaptureClient)
			{
				tc.ThreadDone();
				return XWaveData();
			}
			HRESULT hr=0;
			BYTE *pData;
			UINT32 numFramesAvailable;
			DWORD flags;
			XWaveData tdata(new VWaveData());
			if(!started)Start();//自动开始
			while(started && pCaptureClient)
			{
					if(isClosing || isSelecting)
					{
						tc.ThreadDone();
						return XWaveData();
					}
					if(isRecording)
					{
						if(FAILED(hr=pCaptureClient->GetNextPacketSize(&numFramesAvailable))){goto End;}//获取可读数据
					}
					else numFramesAvailable = 0;
					if(!numFramesAvailable)
					{
						Sleep(10);
						continue;
					}

					if(SUCCEEDED(hr=pCaptureClient->GetBuffer(&pData,&numFramesAvailable,&flags, NULL, NULL)) && !(flags & AUDCLNT_BUFFERFLAGS_SILENT))////获取可读数据;非静音
					{
						if(numFramesAvailable && pData)
						{
							tdata.Format = CurrentFormat;
							tdata.GetData() = XArray<unsigned char>(numFramesAvailable*CurrentFormat.nBlockAlign,pData,Reference);
						}
					}
					else
					{
						Sleep(10);
						break;
					}
					hr=pCaptureClient->ReleaseBuffer(numFramesAvailable);
					break;
			}
End:;
			if(FAILED(hr))
			{
				tc.ThreadDone();
				throw XSoundException(hr);
			}
			tc.ThreadDone();
			return tdata;
		}
		void VRecorder::Restart()
		{
			bool pa = started && !isRecording;
			SelectDeviceById(DeviceID);
			if(pa)Pause();
			else Start();
		}
		//设备添加事件
		void VRecorder::OnDeviceAdded()
		{
			try{
					if(SoundEnvironment::OnAddedDeviceId==DeviceID)Restart();
			}
			catch(...)
			{
				Sleep(500);
				try{//再次尝试
					SelectDeviceById(SoundEnvironment::OnAddedDeviceId);
				}
				catch(...){}
			}
		}
		//设备状态改变事件
		void VRecorder::OnDeviceStateChanged()
		{}
		//设备移除事件
		void VRecorder::OnDeviceRemoved()
		{
			try{
			if(SoundEnvironment::OnRemovedDeviceId==DeviceID)Close();
			}catch(...)
			{}
		}
		//默认设备改变事件
		void VRecorder::OnDefaultDeviceChanged()
		{
			try{
			if(UsingDefaultDevice && SoundEnvironment::OnDefaultChangedFlow==eCapture)SelectDeviceById(SoundEnvironment::OnDefaultChangedDeviceId);
			}catch(...)
			{
				Sleep(500);
			try{
			if(UsingDefaultDevice && SoundEnvironment::OnDefaultChangedFlow==eCapture)SelectDeviceById(SoundEnvironment::OnDefaultChangedDeviceId);
			}catch(...)
			{
			}
			}
		}
		//设备属性改变事件
		void VRecorder::OnDevicePropertyValueChanged()
		{}
		//XRecorder类
		const XTypes& XRecorder::CurrentType=CREATECLASSTYPE(LJ::Sound::XRecorder,LJ::XBase);
	}
}
#endif