#pragma once
#define XRECORDER_
#include "XWave.h"
namespace LJ
{
	namespace Sound
	{
		//¼������
		class VRecorder:public XBase
		{
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
			IAudioCaptureClient *pCaptureClient;
			//��ʱ��������Ƶ���С��10000000��֮1��Ϊ��λ
			XTime hnsRequestedDuration;
			//�豸����֡��
			UINT32 bufferFrameCount;
			//���������ʣ���������8000��16000��22500��44100��48000��96000��
			double hz;
			//��������һ��Ϊ2
			short ch;
			//��������һ��Ϊ16��32
			short bits;
			//�Ƿ�Ϊ����
			bool isFloat;
			//�Ƿ�����¼��
			bool isRecording;
			//�Ƿ�����ѡ���豸
			bool isSelecting;
			//�Ƿ���Start
			bool started;
			//�Ƿ����ڹر�
			bool isClosing;

			//��������
			VRecorder(const VRecorder&){}
			//������ʹ�ø�ֵ���
			void operator=(const VRecorder){}

			PROPERTY_OFFSET(VRecorder,Volume);
		public:
			//�Ƿ�ʼ��ʹ��Ĭ���豸��Ĭ���豸�䶯ʱ�Զ�����Ĭ���豸��
			bool UsingDefaultDevice;
			//������ʽ�������ۣ�
			WAVEFORMATEX CurrentFormat;
			//��ʼ��
			VRecorder();
			//����
			~VRecorder();
			//ȡ��ַ
			VRecorder* operator&(){return reinterpret_cast<VRecorder*>(XBase:: operator&());}
			//ȡ��ַ
			const VRecorder* operator&()const{return reinterpret_cast<const VRecorder*>(XBase:: operator&());}
			//����������С��volΪ�Ŵ�����һ��ȡ0~1������1���ܻᱬ�ƣ�
			void SetVol(double vol);
			//��ȡ��ǰ������С��һ��Ϊ0~1��
			double GetVol()const;
			//��ȡ��ǰ������
			double GetHz()const;
			//��ȡ��ǰ������
			short GetChannels()const;
			//��ȡ��ǰλ��
			short GetBits()const;
			//��ȡ�Ƿ�Ϊ����
			bool GetIsFloat()const;
			//ʹ�õ��豸ID
			const XString DeviceID;
			//ʹ�õ��豸����
			const XString DeviceName;
			union
			{
				//��д���ԣ�������С
				PROPERTY_GETSET(double,VRecorder,GetVol,SetVol,Volume);
				//ֻ�����ԣ�������
				PROPERTY_GET(double,VRecorder,GetHz,Hz);
				//ֻ�����ԣ���Ƶλ��
				PROPERTY_GET(short,VRecorder,GetBits,Bits);
				//ֻ�����ԣ���Ƶ������
				PROPERTY_GET(short,VRecorder,GetChannels,Channels);
				//ֻ�����ԣ���Ƶ�Ƿ�Ϊ����
				PROPERTY_GET(bool,VRecorder,GetIsFloat,IsFloat);
			};

			//����¼��
			void Start();
			//ֹͣ¼��
			void Stop();
			//��ͣ¼��(��ֹͣ¼������������ReaData��������������)
			void Pause();
			//�رջỰ
			void Close();
			//�����������
			void Clear();
			//���������PCM��Ƶ��ʽ
			void SetOutFormat(double hz,short bits,short ch,bool isfloat = false);
			//���������PCM��Ƶ��ʽ��ʹ��ϵͳ��PCM��ʽ��
			void SetOutFormat(const WAVEFORMATEX& fwx);
			//��ȡ��ǰ�����PCM��Ƶ��ʽ�����ֻ���ȡһ�����ԣ������������Դ���NULL
			void GetOutFormat(int* phz,short* pbits,short* pch,bool* pisfloat=NULL);
			//��ȡ��ǰ�����PCM��Ƶ��ʽ�����ֻ���ȡһ�����ԣ������������Դ���NULL
			void GetOutFormat(double* phz,short* pbits,short* pch,bool* pisfloat=NULL);
			//��ȡ������Ƶ��ʽ
			WAVEFORMATEX GetOutFormat();
			//��ȡԴ����ʽ
			WAVEFORMATEX& GetSourceFormat();
			//��ȡԴ����ʽ
			void GetSourceFormat(int* phz,short* pbits,short* pch,bool* pisfloat = NULL);
			//���û���ʱ�䳤��
			void SetBufferTime(const XTime& hms);
			//ѡ���豸
			bool SelectDeviceById(const XString Id);
			//ѡ���豸
			bool SelectDeviceByName(const XString& Name);
			//��ȡlen�������ݣ�������������(�˺����Զ�����¼��)
			XArray<unsigned char> Read(int len);
			//��ȡһ��ʹ��Դ����ʽ����Ƶ���ݰ�
			XWaveData Read();
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

		class XRecorder:public XBase
		{
			PROPERTY_OFFSET(XRecorder,Volume);
		public:
			XBaseRTypeMethods_H(XRecorder,VRecorder);
			//ʹ����������Ŵ���������һ���µ�¼��������
			XRecorder(double vol):XBase(new VRecorder()){SetVol(vol);}
			//ʹ����������Ŵ�������������ʡ��������λ����������������Ƿ񸡵㴴���µ�¼��������
			XRecorder(double vol,double hz,short bits,short channels,bool isFloat=false):XBase(new VRecorder())
			{SetVol(vol);SetOutFormat(hz,bits,channels,isFloat);}
			//����������С��volΪ�Ŵ�����һ��ȡ0~1������1���ܻᱬ�ƣ�
			void SetVol(double vol){Pointer()->SetVol(vol);}
			//��ȡ��ǰ������С��һ��Ϊ0~1��
			double GetVol()const{return Pointer()->GetVol();}
			//��ȡ��ǰ������
			double GetHz()const{return Pointer()->GetHz();}
			//��ȡ��ǰ������
			short GetChannels()const{return Pointer()->GetChannels();}
			//��ȡ��ǰλ��
			short GetBits()const{return Pointer()->GetBits();}
			//��ȡ�Ƿ�Ϊ����
			bool GetIsFloat()const{return Pointer()->GetIsFloat();}
			//��ȡһ��boolֵ��ָʾ�Ƿ���Ĭ���豸����ʱ�Զ��л����µ�Ĭ���豸
			bool GetUsingDefaultDevice()const{return Pointer()->UsingDefaultDevice;}
			//����һ��boolֵ��ָʾ�Ƿ���Ĭ���豸����ʱ�Զ��л����µ�Ĭ���豸
			void SetUsingDefaultDevice(bool b){Pointer()->UsingDefaultDevice = b;}
			//��ȡ��ǰʹ�õ���Ƶ��ʽ
			WAVEFORMATEX GetCurrentFormat()const{return Pointer()->CurrentFormat;}
			//ʹ�õ��豸ID
			XString GetDeviceID()const{return Pointer()->DeviceID;}
			//ʹ�õ��豸����
			XString GetDeviceName()const{return Pointer()->DeviceName;}
			union
			{
				//��д���ԣ�������С
				PROPERTY_GETSET(double,XRecorder,GetVol,SetVol,Volume);
				//ֻ�����ԣ�������
				PROPERTY_GET(double,XRecorder,GetHz,Hz);
				//ֻ�����ԣ���Ƶλ��
				PROPERTY_GET(short,XRecorder,GetBits,Bits);
				//ֻ�����ԣ���Ƶ������
				PROPERTY_GET(short,XRecorder,GetChannels,Channels);
				//ֻ�����ԣ���Ƶ�Ƿ�Ϊ����
				PROPERTY_GET(bool,XRecorder,GetIsFloat,IsFloat);
				//��д���ԣ�һ��boolֵָʾ�Ƿ���Ĭ���豸����ʱ�Զ��л����µ�Ĭ���豸
				PROPERTY_GETSET(bool,XRecorder,GetUsingDefaultDevice,SetUsingDefaultDevice,UsingDefaultDevice);
				//ֻ�����ԣ�������ʽ
				PROPERTY_GET(WAVEFORMATEX,XRecorder,GetCurrentFormat,CurrentFormat);
				//ֻ�����ԣ�ʹ�õ��豸ID
				PROPERTY_GET(XString,XRecorder,GetDeviceID,DeviceID);
				//ֻ�����ԣ�ʹ�õ��豸����
				PROPERTY_GET(XString,XRecorder,GetDeviceName,DeviceName);
			};

			//����¼��
			void Start(){return Pointer()->Start();}
			//ֹͣ¼��
			void Stop(){return Pointer()->Stop();}
			//��ͣ¼��(��ֹͣ¼������������ReaData��������������)
			void Pause(){return Pointer()->Pause();}
			//�رջỰ
			void Close(){return Pointer()->Close();}
			//�����������
			void Clear(){return Pointer()->Clear();}
			//���������PCM��Ƶ��ʽ
			void SetOutFormat(double hz,short bits,short ch,bool isfloat = false){return Pointer()->SetOutFormat(hz,bits,ch,isfloat);}
			//���������PCM��Ƶ��ʽ��ʹ��ϵͳ��PCM��ʽ��
			void SetOutFormat(const WAVEFORMATEX& fwx){return Pointer()->SetOutFormat(fwx);}
			//��ȡ��ǰ�����PCM��Ƶ��ʽ�����ֻ���ȡһ�����ԣ������������Դ���NULL
			void GetOutFormat(int* phz,short* pbits,short* pch,bool* pisfloat=NULL){return Pointer()->GetOutFormat(phz,pbits,pch,pisfloat);}
			//��ȡ��ǰ�����PCM��Ƶ��ʽ�����ֻ���ȡһ�����ԣ������������Դ���NULL
			void GetOutFormat(double* phz,short* pbits,short* pch,bool* pisfloat=NULL){return Pointer()->GetOutFormat(phz, pbits, pch, pisfloat);}
			//��ȡ������Ƶ��ʽ
			WAVEFORMATEX GetOutFormat(){return Pointer()->GetOutFormat();}
			//��ȡԴ����ʽ
			WAVEFORMATEX& GetSourceFormat(){return Pointer()->GetSourceFormat();}
			//��ȡԴ����ʽ
			void GetSourceFormat(int* phz,short* pbits,short* pch,bool* pisfloat = NULL){return Pointer()->GetSourceFormat(phz, pbits, pch, pisfloat);}
			//���û���ʱ�䳤��
			void SetBufferTime(const XTime& hms){return Pointer()->SetBufferTime(hms);}
			//ѡ���豸
			bool SelectDeviceById(const XString id){return Pointer()->SelectDeviceById(id);}
			//ѡ���豸
			bool SelectDeviceByName(const XString& name){return Pointer()->SelectDeviceByName(name);}
			//��ȡlen�������ݣ�������������(�˺����Զ�����¼��)
			XArray<unsigned char> Read(int len){return Pointer()->Read(len);}
			//��ȡһ��ʹ��Դ����ʽ����Ƶ���ݰ�
			XWaveData Read(){return Pointer()->Read();}
			//�豸����ʱ����
			void Restart(){return Pointer()->Restart();}
		};
	}
}