#pragma once
#define SOUNDENVIRONMENT_
#include "XSpeaker.h"
#include "XRecorder.h"
namespace LJ
{
	namespace Sound
	{
		//����GUID�;�̬����
		const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
		const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
		const IID IID_IAudioClient = __uuidof(IAudioClient);
		const IID IID_IAudioCaptureClient = __uuidof(IAudioCaptureClient);
		const IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);

		//�����̰߳�ȫ
		class SoundEnvironment
		{
			friend VSpeaker;
			friend VRecorder;
			friend DeviceChangeCallback;
			//�߳�ͬ������
			static ThreadControl soundtc;
			//¼���豸����
			static IMMDeviceCollection* pRecordingDevices;
			//�����豸����
			static IMMDeviceCollection* pSpeakingDevices;
			//�豸ö����
			static IMMDeviceEnumerator *pEnumerator;
			//�����첽���豸���Ĺ���
			static DeviceChangeCallback* pNotify;
			//��¼���е����������Ա㻷���仯ʱ����֪ͨ
			static VArray<VSpeaker*> speakerList;
			//��¼���е�¼�������Ա㻷���仯ʱ����֪ͨ
			static VArray<VRecorder*> recorderList;
			//���������ָ�룬�������¼�����ʱ����֪ͨ
			static void AddSpeaker(VSpeaker* speaker);
			//���¼����ָ�룬�������¼�����ʱ����֪ͨ
			static void AddRecorder(VRecorder* recorder);
			//�Ƴ�������ָ��
			static void RemoveSpeaker(VSpeaker* speaker);
			//�Ƴ�¼����ָ��
			static void RemoveRecorder(VRecorder* recorder);
			//��ȡĬ��¼���豸,ʹ�������Ҫ�������Ա����Release()
			static IMMDevice* GetDefaultRecordingDevice();
			//��ȡĬ�ϲ����豸,ʹ�������Ҫ�������Ա����Release()
			static IMMDevice* GetDefaultSpeakingDevice();
			//��ȡ���豸Idָ�����豸,ʹ�������Ҫ�������Ա����Release()
			static IMMDevice* GetDevice(const XString& Id);
			//��ȡ�豸ID
			static XString GetDeviceID(IMMDevice* pDevice);
			//�����豸��
			static XString GetDeviceName(IMMDevice* pDevice);

			//�豸�������
			static volatile long changedCount;
		public:
			//���������¼�ʱִ�е�ί�У��¼���
			static XDelegate<void,XString> OnDeviceAdded;
			static XDelegate<void,XString,DWORD> OnDeviceStateChanged;
			static XDelegate<void,XString> OnDeviceRemoved;
			static XDelegate<void,EDataFlow,ERole,XString> OnDefaultDeviceChanged;
			static XDelegate<void,XString,const PROPERTYKEY> OnPropertyValueChanged;
			//¼���豸�����б�
			static const VArray<XString> RecordingDevicesList;
			//¼���豸ID�б�
			static const VArray<XString> RecordingDevicesIDList;
			//�����豸�����б�
			static const VArray< XString> SpeakingDevicesList;
			//�����豸ID�б�
			static const VArray<XString> SpeakingDevicesIDList;
			//Ĭ��������
			static short DefaultChannels;
			//Ĭ��λ��
			static short DefaultBits;
			//Ĭ��������
			static int DefaultHz;

			//Ĭ��XSpeaker����ʱ��
			static XTime DefaultSpeakerRequestedDuration;
			//��СXSpeaker����ʱ��
			static XTime MinimumSpeakerRequestedDuration;
			//Ĭ��XRecorder����ʱ��
			static XTime DefaultRecorderRequestedDuration;
			//��СXRecorder����ʱ��
			static XTime MinimumRecorderRequestedDuration;
			//���һ�θ���ʱ����ӵ��豸ID
			static XString OnAddedDeviceId;
			//���һ��״̬���ĵ��豸ID
			static XString OnStateChangedDeviceId;
			//���һ��״̬���ĵ�����״̬
			static DWORD OnStateChangedNewState;
			//���һ���Ƴ����豸ID
			static XString OnRemovedDeviceId;
			//���һ��Ĭ���豸���ĵ��豸ID
			static XString OnDefaultChangedDeviceId;
			//���һ��Ĭ���豸���ĵ��豸����
			static EDataFlow OnDefaultChangedFlow;
			//���һ��Ĭ���豸���ĵ��豸��ɫ
			static ERole OnDefaultChangedRole;
			//���һ���豸���Ը��ĵ��豸ID
			static XString OnPropertyValueChangedDeviceId;
			//���һ���豸���Ը��ĵ��豸���� 
			static PROPERTYKEY OnPropertyValueChangedKey;
			SoundEnvironment();
			~SoundEnvironment();
			//��ȡ���е��������б�
			static XArray<XSpeaker> GetSpeakersList();
			//��ȡ���е�¼�����б�
			static XArray<XRecorder> GetRecordersList();
			//��ȡ���Ĵ���
			static int GetChangedCount();
			//ɾ��ԭ����Ϣ
			static void Clear();
			//ˢ���豸��Ϣ
			static void Refresh();
			static HRESULT SetState(HRESULT hr);
			//��ȡĬ��¼���豸Id
			static XString GetDefaultRecordingDeviceId();
			//��ȡĬ�ϲ����豸Id
			static XString GetDefaultSpeakingDeviceId();
			//��ȡ�豸����
			static int GetDevicesCount();
			//�����豸���ƻ�ȡid�������ô˹��ܣ���Ϊ���ܴ�����ͬ���Ƶ��豸
			static XString GetDeviceID(const XString& name);
			//�����豸ID��ȡ���ƣ���ID�ȿ�����¼���豸Ҳ�����ǲ����豸��
			static XString GetDeviceName(const XString& id);

			static SoundEnvironment Default;
		};

	}
}