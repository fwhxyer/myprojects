#pragma once
#define XSPEAKER_
#include "XWave.h"
namespace LJ
{
	namespace Sound
	{
		//�������࣬ÿ�������һ����Ƶ�Ự
		class VSpeaker:public XBase
		{
			PROPERTY_OFFSET(VSpeaker,Volume);
			//�߳�ͬ������
			ThreadControl tc;
			//��Ƶ��ʽת��
			VWave converter;
			//���ݻ�����
			VBuffer buffer;

			//����ָ�����豸
			IMMDevice *pDevice;
			//��Ƶ�Ự
			IAudioClient *pAudioClient;
			//��Ƶ���ſͻ���
			IAudioRenderClient *pRenderClient;
			//��ʱ��������Ƶ���С��10000000��֮1��Ϊ��λ
			XTime hnsRequestedDuration;
			//�豸����֡��
			UINT32 bufferFrameCount;
			//����Ƶ�ʣ���������8000��16000��22500��44100��48000��96000��
			double hz;
			//���õ��߳���
			int threadCount;
			//��������һ��Ϊ2
			short ch;
			//��������һ��Ϊ16��32
			short bits;
			//�Ƿ�����д��
			bool isWriting;
			//�Ƿ�Ϊ����
			bool isFloat;
			//�Ƿ����ڲ���
			bool isPlaying;
			//�Ƿ���Start
			bool started;
			//�Ƿ�����ѡ���豸
			bool isSelecting;
			//�Ƿ����ڹر�
			bool isClosing;

			//������ʹ�ø�ֵ���
			void operator=(const VSpeaker&){}
			//��ֹ���ƹ���
			VSpeaker(const VSpeaker&){}
		public:
			//�Ƿ�ʹ��Ĭ������
			bool UsingDefaultDevice;
			//��ǰ�������
			static const XTypes& CurrentType;
			//��ȡ����������Ϣ
			virtual const XTypes& GetClassType()const{return CurrentType;}
			//ȡ��ַ
			VSpeaker* operator&(){return static_cast<VSpeaker*>(XBase::operator&());}
			const VSpeaker* operator&()const{return static_cast<const VSpeaker*>(XBase::operator&());}
			//������ʽ�������ۣ�
			WAVEFORMATEX SpeakingFormat;
			//���캯��
			VSpeaker();
			//��������
			virtual ~VSpeaker();
			//����������С��volΪ�Ŵ�����һ��ȡ0~1������1���ܻᱬ�ƣ�
			void SetVol(double vol);
			//��ȡ��ǰ������С��һ��Ϊ0~1��
			double GetVol()const;
			//��д���ԣ������Ŵ���
			PROPERTY_GETSET(double,VSpeaker,GetVol,SetVol,Volume);
			//ʹ�õ��豸ID
			XString DeviceID;
			//ʹ�õ��豸����
			XString DeviceName;
			//��ʼ��������Ż�������ݣ��÷���Ӧ�����첽����
			void Start();
			//ֹͣ����,��ջ������ݣ��÷���Ӧ�����첽����
			void Stop();
			//��ͣ���ţ���������棬�÷���Ӧ�����첽����
			void Pause();
			//�رջỰ
			void Close();
			//��ջ�������
			void Clear();
			//д��PCM��Ƶ����,����ɲ����ء��ò���������ͬ������
			template<typename T>void Write(const XArray<T>&xArray,int startIndex,int length);
			//д��PCM��Ƶ����,����ɲ����ء��ò���������ͬ������
			template<typename T>void Write(const XArray<T>&xArray,int startIndex=0){return Write(xArray,startIndex,xArray.Length-startIndex);}
			//д��PCM��Ƶ����,����ɲ����ء��ò���������ͬ������
			template<typename T>void Write(const VArray<T>&xArray,int startIndex,int length){return Write(XArray<T>(xArray.Length,xArray,Reference),startIndex,length);}
			//д��PCM��Ƶ����,����ɲ����ء��ò���������ͬ������
			template<typename T>void Write(const VArray<T>&xArray,int startIndex=0){return Write(XArray<T>(xArray.Length,xArray,Reference),startIndex);}
			//д��һ���������ݣ�����ɲ�����,ע��ò������ı�������Ƶ��ʽ����
			void Write(const VWaveData& data){SetFormat(data.Hz,data.Bits,data.Channels,data.IsFloat);Write(XArray<unsigned char>(data.Data.Length,data.Data,Reference));}
			//д��һ���������ݣ�����ɲ�����,ע��ò������ı�������Ƶ��ʽ����
			void Write(const XWaveData& data){if(data.IsNull())return;SetFormat(data.Hz,data.Bits,data.Channels,data.IsFloat);Write(XArray<unsigned char>(data.GetData().Length,data.GetData(),Reference));}
			//���û���ʱ�䳤�ȣ���100nsΪ��λ
			void SetBufferTime(const XTime& hms);
			//���ò��ŵ�PCM��Ƶ��ʽ��isfloatָʾ�Ƿ�Ϊ����
			void SetFormat(double hz,short bits,short ch,bool isFloat = false);
			//���ò��ŵ�PCM��Ƶ��ʽ��ʹ��ϵͳ��PCM��ʽ��
			void SetFormat(const WAVEFORMATEX& fwx);
			//����Ĭ�ϵ�PCM��Ƶ��ʽ
			void SetToDefaultFormat();
			//��ȡ��ǰ��PCM��Ƶ��ʽ�����ֻ���ȡһ�����ԣ������������Դ���NULL
			void GetFormat(int* phz,short* pbits,short* pch,bool *isFloat=NULL);
			//��ȡ��ǰ��PCM��Ƶ��ʽ
			WAVEFORMATEX GetFormat();
			//��ȡ�����豸��Id�б�
			static XArray<XString> GetIdList();
			//��ȡ�����豸�������б�
			static XArray<XString> GetNameList();
			//���豸Id����ѡ���豸���ɹ�����true
			bool SelectDeviceById(const XString& Id);
			//���豸������ѡ���豸���ɹ�����true
			bool SelectDeviceByName(const XString& name);
			//�豸����ʱ����
			void Restart();
			//�豸����¼�
			void OnDeviceAdded();
			//�豸״̬�ı��¼�
			void OnDeviceStateChanged();
			//�豸�Ƴ��¼�
			void OnDeviceRemoved();
			//Ĭ���豸�ı��¼�
			void OnDefaultDeviceChanged();
			//�豸���Ըı��¼�
			void OnDevicePropertyValueChanged();
		};
		class XSpeaker:public XBase
		{
			PROPERTY_OFFSET(XSpeaker,Volume);
		public:
			XBaseRTypeMethods_H(XSpeaker,VSpeaker);
			//ʹ��������С������һ����������
			XSpeaker(double vol):XBase(new VSpeaker()){SetVol(vol);}
			//ʹ������ֵ�������ʡ�������������λ���������µ�������
			XSpeaker(double vol,double hz,short bits,short ch,bool isFloat=false):XBase(new VSpeaker())
			{SetVol(vol);SetFormat(hz,bits,ch,isFloat);}
			//����������С��volΪ�Ŵ�����һ��ȡ0~1������1���ܻᱬ�ƣ�
			void SetVol(double vol){return Pointer()->SetVol(vol);}
			//��ȡ��ǰ������С��һ��Ϊ0~1��
			double GetVol()const{return Pointer()->GetVol();}
			//��ȡһ��boolֵ��ָʾ�Ƿ�ʹ��Ĭ���豸
			bool GetUsingDefaultDevice()const{return Pointer()->UsingDefaultDevice;}
			//����һ��boolֵ��ָʾ�Ƿ�ʹ��Ĭ���豸
			void SetUsingDefaultDevice(bool b){Pointer()->UsingDefaultDevice = b;}
			//��ȡ��ǰ��ʽ
			WAVEFORMATEX GetSpeakingFormat()const{return Pointer()->SpeakingFormat;}
			//���õ�ǰ��ʽ
			void SetSpeakingFormat(WAVEFORMATEX x){Pointer()->SpeakingFormat = x;}
			//��ȡ��ǰ�豸ID
			XString GetCurrentDeviceID()const{return Pointer()->DeviceID;}
			//��ȡ��ǰ�豸��
			XString GetCurrentDeviceName()const{return Pointer()->DeviceName;}
			union
			{
				//��д���ԣ��Ƿ�ʹ��Ĭ���豸
				PROPERTY_GETSET(bool,XSpeaker,GetUsingDefaultDevice,SetUsingDefaultDevice,UsingDefaultDevice);
				//��д���ԣ������Ŵ���
				PROPERTY_GETSET(double,XSpeaker,GetVol,SetVol,Volume);
				//��д���ԣ���ǰ��ʽ
				PROPERTY_GETSET(WAVEFORMATEX,XSpeaker,GetSpeakingFormat,SetSpeakingFormat,SpeakingFormat);
				//ֻ�����ԣ���ǰ�豸ID
				PROPERTY_GET(XString,XSpeaker,GetCurrentDeviceID,DeviceID);
				//ֻ�����ԣ���ǰ�豸��
				PROPERTY_GET(XString,XSpeaker,GetCurrentDeviceName,DeviceName);
			};
			//��ʼ��������Ż�������ݣ��÷���Ӧ�����첽����
			void Start(){return Pointer()->Start();}
			//ֹͣ����,��ջ������ݣ��÷���Ӧ�����첽����
			void Stop(){return Pointer()->Stop();}
			//��ͣ���ţ���������棬�÷���Ӧ�����첽����
			void Pause(){return Pointer()->Pause();}
			//�رջỰ
			void Close(){return Pointer()->Close();}
			//��ջ�������
			void Clear(){return Pointer()->Clear();}
			//д��PCM��Ƶ����,����ɲ����ء��ò���������ͬ������
			template<typename T>void Write(const XArray<T>&xArray,int startIndex=0){return Pointer()->Write(xArray,startIndex,xArray.Length-startIndex);}
			//д��PCM��Ƶ����,����ɲ����ء��ò���������ͬ������
			template<typename T>void Write(const XArray<T>&xArray,int startIndex,int length){return Pointer()->Write(xArray,startIndex,length);}
			//д��һ���������ݣ�����ɲ�����,ע��ò������ı�������Ƶ��ʽ����
			void Write(const VWaveData& data){return Pointer()->Write(data);}
			//д��һ���������ݣ�����ɲ�����,ע��ò������ı�������Ƶ��ʽ����
			void Write(const XWaveData& data){return Pointer()->Write(data);}
			//���û���ʱ�䳤�ȣ���100nsΪ��λ
			void SetBufferTime(const XTime& hms){return Pointer()->SetBufferTime(hms);}
			//�������ݵ�PCM��Ƶ��ʽ��isfloatָʾ�Ƿ�Ϊ����
			void SetFormat(double hz,short bits,short ch,bool isFloat = false){return Pointer()->SetFormat(hz, bits, ch, isFloat);}
			//�������ݵ�PCM��Ƶ��ʽ
			void SetFormat(const WAVEFORMATEX& pwfx){return Pointer()->SetFormat(pwfx);}
			//����Ĭ�ϵ�PCM��Ƶ��ʽ
			void SetToDefaultFormat(){return Pointer()->SetToDefaultFormat();}
			//��ȡ��ǰ���õ�����PCM��Ƶ��ʽ�����ֻ���ȡһ�����ԣ������������Դ���NULL
			void GetFormat(int* phz,short* pbits,short* pch,bool *isFloat=NULL){return Pointer()->GetFormat(phz, pbits, pch,isFloat);}
			//��ȡ��ǰ��PCM��Ƶ��ʽ
			WAVEFORMATEX GetFormat(){return Pointer()->GetFormat();}
			//��ȡ�����豸��Id�б�
			static XArray<XString> GetIdList(){return VSpeaker::GetIdList();}
			//��ȡ�����豸�������б�
			static XArray<XString> GetNameList(){return VSpeaker::GetNameList();}
			//���豸Id����ѡ���豸���ɹ�����true
			bool SelectDeviceById(const XString& Id){return Pointer()->SelectDeviceById(Id);}
			//���豸������ѡ���豸���ɹ�����true
			bool SelectDeviceByName(const XString& name){return Pointer()->SelectDeviceByName(name);}
			//�豸����ʱ����
			void Restart(){return Pointer()->Restart();}
		};

		template<typename T>void VSpeaker::Write(const XArray<T>&xArray,int startIndex,int length)
        {
			HRESULT hr=0;
            if(!pRenderClient)return;
			while(!tc.ThreadTry()){if(isClosing)return;Sleep(1);}
			isWriting = true;
			XArray<T> pdata;
            if(!pRenderClient)goto End;
            UINT32 frames;
            unsigned char *pdes;
			//ת�����ݸ�ʽ
			pdata = converter.Convert(xArray.SubArray(startIndex,length,Reference),SpeakingFormat);//���ת��������ڴ�͵�����֡����
			if(buffer.Length<pdata.GetLengthOfBytes()+(int)buffer.GetReadable())buffer.Resize(pdata.GetLengthOfBytes()+buffer.GetReadable());//������С
			if((unsigned int)buffer.Length<bufferFrameCount*SpeakingFormat.nBlockAlign)buffer.Resize(bufferFrameCount*SpeakingFormat.nBlockAlign);
            //����������Ⱦۼ���buffer��
			buffer.PutAfter(pdata);

			//buffer�п�������������ܿ����ռ��һ��ʱ��ֱ�ӷ���
            if(buffer.GetReadable()<bufferFrameCount*(SpeakingFormat.nBlockAlign/2))
				goto End;

            while(pAudioClient)
            {
                //��ȡ�����֡��
				if(FAILED(hr=pAudioClient->GetCurrentPadding(&frames)))goto End;
                frames = bufferFrameCount-frames;//��ȡ��д��ռ�
                if(frames<(bufferFrameCount/2))//�����ռ���٣�����Ҫ���������Ŀռ�������
                {
					tc.ThreadDone();
					Sleep(5);
                    if(!started)//�Զ���ʼ����
                        Start();
					while(!tc.ThreadTry()){if(isClosing)return;}
                    continue;
                }
                frames = bufferFrameCount/2;
                if(buffer.GetReadable()>=frames*SpeakingFormat.nBlockAlign && SUCCEEDED(hr=pRenderClient->GetBuffer(frames,&pdes)))//��ȡ�ڴ������
                {	
                    XArray<unsigned char>tmp = buffer.GetAfter(frames*SpeakingFormat.nBlockAlign);//�ӻ����ȡ���ݵ�ָ������
					Memory::Copy(pdes,tmp,frames*SpeakingFormat.nBlockAlign);
                    if(FAILED(hr=pRenderClient->ReleaseBuffer(frames,NULL)))goto End;
                }
                else
                {
                    goto End;
                }
                if(buffer.GetReadable()<frames*SpeakingFormat.nBlockAlign)break;
            }
End:;
			isWriting = false;
            tc.ThreadDone();
			if(FAILED(hr))throw XSoundException(hr);
        }
	}
}