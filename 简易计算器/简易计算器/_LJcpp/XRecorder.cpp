#include "stdafx.h"
#ifdef XRECORDER_
namespace LJ
{
	namespace Sound
	{
		//Recorder��

		VRecorder::VRecorder()
			:hz(SoundEnvironment::DefaultHz),ch(SoundEnvironment::DefaultChannels),bits(SoundEnvironment::DefaultBits),isFloat(false),//����Ĭ�ϸ�ʽ
			isRecording(false),started(false),isSelecting(false),isClosing(false),UsingDefaultDevice(true),
			DeviceID(XString::Empty),DeviceName(XString::Empty),
			pDevice(NULL),pAudioClient(NULL),pCaptureClient(NULL),
			CurrentFormat(),
			hnsRequestedDuration(SoundEnvironment::DefaultRecorderRequestedDuration),
			converter()
		{
			buffer.SetMinimumSizeBefore(0);
			SelectDeviceById(XString::Empty);
			//��environment��ע��
			SoundEnvironment::AddRecorder(this);
		}
		VRecorder::~VRecorder()
		{
			SoundEnvironment::RemoveRecorder(this);//��environment���Ƴ�
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
			if(hms<SoundEnvironment::MinimumRecorderRequestedDuration)//����
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
			//��ȡĬ���豸
			Close();//�رգ����½����Ự
			if(pDevice = id.IsNullOrEmpty()?SoundEnvironment::GetDefaultRecordingDevice():SoundEnvironment::GetDevice(id))//��ȡ�豸�ɹ�
			{
				const_cast<XString&>(DeviceID) = id;
				const_cast<XString&>(DeviceName) = SoundEnvironment::GetDeviceName(DeviceID);//�豸����
				if(SUCCEEDED(hr=pDevice->Activate(IID_IAudioClient, CLSCTX_ALL, NULL, (void**)&pAudioClient)))//����Ự
				{
					//��ȡ������ʽ
					WAVEFORMATEX* pwfx;
					if(FAILED(hr=pAudioClient->GetMixFormat(&pwfx)))goto End;
					CurrentFormat = *pwfx;
					//������Դ��ʽ
					converter.SetFormat(CurrentFormat);//�����ʺ͸���ת��
					//ʹ�ù���ģʽ����hnsRequestedDuration��ʱ�������г�ʼ��,Initialize���������ޣ�ֻʶ��CoTaskMemalloc������ڴ�
					if(FAILED(hr=pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED,0,hnsRequestedDuration,0,pwfx,NULL)))
					{
						CoTaskMemFree(pwfx);
						goto End;
					}
					CoTaskMemFree(pwfx);
					//��ȡ��֡��
					if(FAILED(hr=pAudioClient->GetBufferSize(&bufferFrameCount)))goto End;
					//��ȡ���ŷ���
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
			if((int)buffer.Length<(len*2))//���������С
			{
				buffer.Resize(len*2);
			}
			if(!started)Start();//�Զ���ʼ
			while(started && pCaptureClient)
			{
				if((int)buffer.GetReadable()<len)//���������ݹ���
				{
					if(isClosing || isSelecting)
					{
						tc.ThreadDone();
						return XArray<unsigned char>(0);
					}
					if(isRecording)
					{
						if(FAILED(hr=pCaptureClient->GetNextPacketSize(&numFramesAvailable))){goto End;}//��ȡ�ɶ�����
					}
					else numFramesAvailable = 0;
					if(!numFramesAvailable)
					{
						Sleep(10);
						continue;
					}

					if(SUCCEEDED(hr=pCaptureClient->GetBuffer(&pData,&numFramesAvailable,&flags, NULL, NULL)) && !(flags & AUDCLNT_BUFFERFLAGS_SILENT))////��ȡ�ɶ�����;�Ǿ���
					{
						if(numFramesAvailable && pData)
						{
							XArray<unsigned char> tmp1 = converter.Convert(XArray<unsigned char>(numFramesAvailable*CurrentFormat.nBlockAlign,pData,Reference),hz,bits,ch,isFloat);//���ת��������ڴ��д��֡����
							buffer.PutAfter(tmp1);//д�����ݵ�����������Ҫ�󻺳������㹻�Ŀռ�
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
			XArray<unsigned char> result = (int)buffer.GetReadable()>=len?buffer.GetAfter(len):XArray<unsigned char>(0);//��ȡ����
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
			if(!started)Start();//�Զ���ʼ
			while(started && pCaptureClient)
			{
					if(isClosing || isSelecting)
					{
						tc.ThreadDone();
						return XWaveData();
					}
					if(isRecording)
					{
						if(FAILED(hr=pCaptureClient->GetNextPacketSize(&numFramesAvailable))){goto End;}//��ȡ�ɶ�����
					}
					else numFramesAvailable = 0;
					if(!numFramesAvailable)
					{
						Sleep(10);
						continue;
					}

					if(SUCCEEDED(hr=pCaptureClient->GetBuffer(&pData,&numFramesAvailable,&flags, NULL, NULL)) && !(flags & AUDCLNT_BUFFERFLAGS_SILENT))////��ȡ�ɶ�����;�Ǿ���
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
		//�豸����¼�
		void VRecorder::OnDeviceAdded()
		{
			try{
					if(SoundEnvironment::OnAddedDeviceId==DeviceID)Restart();
			}
			catch(...)
			{
				Sleep(500);
				try{//�ٴγ���
					SelectDeviceById(SoundEnvironment::OnAddedDeviceId);
				}
				catch(...){}
			}
		}
		//�豸״̬�ı��¼�
		void VRecorder::OnDeviceStateChanged()
		{}
		//�豸�Ƴ��¼�
		void VRecorder::OnDeviceRemoved()
		{
			try{
			if(SoundEnvironment::OnRemovedDeviceId==DeviceID)Close();
			}catch(...)
			{}
		}
		//Ĭ���豸�ı��¼�
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
		//�豸���Ըı��¼�
		void VRecorder::OnDevicePropertyValueChanged()
		{}
		//XRecorder��
		const XTypes& XRecorder::CurrentType=CREATECLASSTYPE(LJ::Sound::XRecorder,LJ::XBase);
	}
}
#endif