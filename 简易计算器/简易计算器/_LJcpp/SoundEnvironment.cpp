#include "stdafx.h"
#ifdef SOUNDENVIRONMENT_
namespace LJ
{
	namespace Sound
	{

		//SoundEnvironment��
		ThreadControl SoundEnvironment::soundtc;
		//¼���豸����
		IMMDeviceCollection* SoundEnvironment::pRecordingDevices;
		//�����豸����
		IMMDeviceCollection* SoundEnvironment::pSpeakingDevices;
		//�豸ö����
		IMMDeviceEnumerator* SoundEnvironment::pEnumerator=nullptr;
		//�����첽���豸���Ĺ���
		DeviceChangeCallback* SoundEnvironment::pNotify=nullptr;

		//��¼���е����������Ա㻷���仯ʱ����֪ͨ
		VArray<VSpeaker*> SoundEnvironment::speakerList;
		//��¼���е�¼�������Ա㻷���仯ʱ����֪ͨ
		VArray<VRecorder*> SoundEnvironment::recorderList;

		//���������¼�ʱִ�е�ί�У��¼���
		XDelegate<void,XString> SoundEnvironment::OnDeviceAdded;
		XDelegate<void,XString,DWORD> SoundEnvironment::OnDeviceStateChanged;
		XDelegate<void,XString> SoundEnvironment::OnDeviceRemoved;
		XDelegate<void,EDataFlow,ERole,XString> SoundEnvironment::OnDefaultDeviceChanged;
		XDelegate<void,XString,const PROPERTYKEY> SoundEnvironment::OnPropertyValueChanged;

		//¼���豸�����б�
		const VArray<XString> SoundEnvironment::RecordingDevicesList;
		//¼���豸ID�б�
		const VArray<XString> SoundEnvironment::RecordingDevicesIDList;
		//�����豸�����б�
		const VArray< XString> SoundEnvironment::SpeakingDevicesList;
		//�����豸ID�б�
		const VArray<XString> SoundEnvironment::SpeakingDevicesIDList;

		//Ĭ��������
		short SoundEnvironment::DefaultChannels = 2;
		//Ĭ��λ��
		short SoundEnvironment::DefaultBits = 16;
		//Ĭ��������
		int SoundEnvironment::DefaultHz = 44100;

		//Ĭ��XSpeaker����ʱ��(100ms)
		XTime SoundEnvironment::DefaultSpeakerRequestedDuration=1000000;
		//��СXSpeaker����ʱ��(50ms)
		XTime SoundEnvironment::MinimumSpeakerRequestedDuration=500000;
		//Ĭ��XRecorder����ʱ��(100ms)
		XTime SoundEnvironment::DefaultRecorderRequestedDuration=1000000;
		//��СXRecorder����ʱ��(50ms)
		XTime SoundEnvironment::MinimumRecorderRequestedDuration=500000;
		//���һ�θ���ʱ����ӵ��豸ID
		XString SoundEnvironment::OnAddedDeviceId;
		//���һ��״̬���ĵ��豸ID
		XString SoundEnvironment::OnStateChangedDeviceId;
		//���һ��״̬���ĵ�����״̬
		DWORD SoundEnvironment::OnStateChangedNewState;
		//���һ���Ƴ����豸ID
		XString SoundEnvironment::OnRemovedDeviceId;
		//���һ��Ĭ���豸���ĵ��豸ID
		XString SoundEnvironment::OnDefaultChangedDeviceId;
		//���һ��Ĭ���豸���ĵ��豸����
		EDataFlow SoundEnvironment::OnDefaultChangedFlow;
		//���һ��Ĭ���豸���ĵ��豸��ɫ
		ERole SoundEnvironment::OnDefaultChangedRole;
		//���һ���豸���Ը��ĵ��豸ID
		XString SoundEnvironment::OnPropertyValueChangedDeviceId;
		//���һ���豸���Ը��ĵ��豸���� 
		PROPERTYKEY SoundEnvironment::OnPropertyValueChangedKey;
		//�豸���Ĵ���
		volatile long SoundEnvironment::changedCount=0;
		SoundEnvironment::SoundEnvironment()
		{
			if(this!=&Default)throw XSoundException(L"��ʹ��Ĭ����Ƶ������SoundEnvironment::Default.",E_ILLEGAL_METHOD_CALL,L"SoundEnvironment");
			//��ʼ��
			HRESULT hr=CoInitializeEx(NULL,COINIT_MULTITHREADED);
			if(hr==RPC_E_CHANGED_MODE)
			{//COM���Ѿ�����ʼ���Ҵ���������õĲ���ģʽ�ͱ��β�ͬ��
			}
		}
		SoundEnvironment::~SoundEnvironment()
		{
			Clear();
			if(pSpeakingDevices)pSpeakingDevices->Release();
			if(pRecordingDevices)pRecordingDevices->Release();
			if(pEnumerator)
			{
				if(pNotify)pEnumerator->UnregisterEndpointNotificationCallback(pNotify);
				delete pNotify;
				pNotify = NULL;
				pEnumerator->Release();
				pEnumerator = NULL;
			}
			CoUninitialize();
		}
		void SoundEnvironment::AddSpeaker(VSpeaker* ps)
		{
			soundtc.ThreadWait();
			speakerList.Append(ps);
			soundtc.ThreadDone();
		}
		void SoundEnvironment::AddRecorder(VRecorder* pr)
		{
			soundtc.ThreadWait();
			recorderList.Append(pr);
			soundtc.ThreadDone();
		}
		void SoundEnvironment::RemoveSpeaker(VSpeaker* ps)
		{
			soundtc.ThreadWait();
			int k=speakerList.IndexOf(ps);
			if(k>=0)
			{
				speakerList[k] = speakerList[speakerList.Length-1];
				speakerList.Resize(speakerList.Length-1);
			}
			soundtc.ThreadDone();
		}
		void SoundEnvironment::RemoveRecorder(VRecorder* pr)
		{
			soundtc.ThreadWait();
			int k=recorderList.IndexOf(pr);
			if(k>=0)
			{
				recorderList[k] = recorderList[recorderList.Length-1];
				recorderList.Resize(recorderList.Length-1);
			}
			soundtc.ThreadDone();
		}
		IMMDevice *SoundEnvironment::GetDefaultRecordingDevice()
		{
			IMMDevice *pdev = NULL;
			soundtc.ThreadWait();
			if(!pEnumerator)Refresh();
			if(pEnumerator)pEnumerator->GetDefaultAudioEndpoint(eCapture,eConsole,&pdev);
			soundtc.ThreadDone();
			return pdev;
		}
		IMMDevice *SoundEnvironment::GetDefaultSpeakingDevice()
		{
			IMMDevice *pdev = NULL;
			soundtc.ThreadWait();
			if(!pEnumerator)Refresh();
			if(pEnumerator)pEnumerator->GetDefaultAudioEndpoint(eRender,eConsole,&pdev);
			soundtc.ThreadDone();
			return pdev;
		}
		XString SoundEnvironment::GetDefaultRecordingDeviceId()
		{
			IMMDevice *pdev = NULL;
			soundtc.ThreadWait();
			if(!pEnumerator)Refresh();
			if(pEnumerator)pEnumerator->GetDefaultAudioEndpoint(eCapture,eConsole,&pdev);
			LPWSTR pwstr;
			pdev->GetId(&pwstr);
			XString s = RecordingDevicesIDList[RecordingDevicesIDList.IndexOf(pwstr)];
			CoTaskMemFree(pwstr);
			pdev->Release();
			soundtc.ThreadDone();
			return s;
		}
		XString SoundEnvironment::GetDefaultSpeakingDeviceId()
		{
			IMMDevice *pdev = NULL;
			soundtc.ThreadWait();
			if(!pEnumerator)Refresh();
			if(pEnumerator)pEnumerator->GetDefaultAudioEndpoint(eRender,eConsole,&pdev);
			LPWSTR pwstr;
			pdev->GetId(&pwstr);
			XString s = SpeakingDevicesIDList[SpeakingDevicesIDList.IndexOf(pwstr)];
			CoTaskMemFree(pwstr);
			pdev->Release();
			soundtc.ThreadDone();
			return s;
		}
		IMMDevice *SoundEnvironment::GetDevice(const XString&id)
		{
			IMMDevice *pdev(NULL);
			soundtc.ThreadWait();
			if(pEnumerator)pEnumerator->GetDevice(id,&pdev);
			soundtc.ThreadDone();
			return pdev;
		}
		XString SoundEnvironment::GetDeviceID(IMMDevice* pDevice)
		{
			if(!pDevice)return XString::Empty;
			soundtc.ThreadWait();
			if(!pEnumerator)Refresh();
			LPWSTR tmp;
			SetState(pDevice->GetId(&tmp));//��ȡid
			XString s;
			int i = SpeakingDevicesIDList.IndexOf(tmp);
			if(i<0)
			{
				i=RecordingDevicesIDList.IndexOf(tmp);
				if(i<0)s = tmp;
				else s = RecordingDevicesIDList[i];
			}
			else s = SpeakingDevicesIDList[i];
			CoTaskMemFree(tmp);
			soundtc.ThreadDone();
			return s;
		}
		XString SoundEnvironment::GetDeviceName(IMMDevice* pDevice)
		{
			if(!pDevice)return XString::Empty;
			soundtc.ThreadWait();
			if(!pEnumerator)Refresh();
			HRESULT hr;
			IPropertyStore * p;
			SetState(pDevice->OpenPropertyStore(STGM_READ,&p));//��ȡ��Ϣ
			PROPVARIANT inf;
			if(FAILED(hr=p->GetValue(PKEY_Device_FriendlyName,&inf)))//��ȡ������Ϣ
			{
				p->Release();
				SetState(hr);
			}
			XString s;
			int i = SpeakingDevicesList.IndexOf(inf.pwszVal);
			if(i<0)
			{
				i=RecordingDevicesList.IndexOf(inf.pwszVal);
				if(i<0)s = inf.pwszVal;
				else s = RecordingDevicesList[i];
			}
			else s = SpeakingDevicesList[i];
			p->Release();
			soundtc.ThreadDone();
			return s;
		}

		XArray<XSpeaker> SoundEnvironment::GetSpeakersList()
		{
			soundtc.ThreadWait();
			XArray<XSpeaker>tmp(speakerList.Length);
			//�˴���Ҫʹ�����ص�&�����
			for(int i=0;i<speakerList.Length;++i)tmp[i] = speakerList[i]?&(*speakerList[i]):NULL;
			soundtc.ThreadDone();
			return tmp;
		}
		XArray<XRecorder> SoundEnvironment::GetRecordersList()
		{
			soundtc.ThreadWait();
			XArray<XRecorder>tmp(recorderList.Length);
			//�˴���Ҫʹ�����ص�&�����
			for(int i=0;i<recorderList.Length;++i)tmp[i] = recorderList[i]?&(*recorderList[i]):NULL;
			soundtc.ThreadDone();
			return tmp;
		}
		int SoundEnvironment::GetChangedCount(){return changedCount;}//��ȡ���Ĵ���
		void SoundEnvironment::Clear()
		{
			soundtc.ThreadWait();
			const_cast<VArray<XString>&>(RecordingDevicesList).Resize(0);
			const_cast<VArray<XString>&>(SpeakingDevicesList).Resize(0);
			const_cast<VArray<XString>&>(RecordingDevicesIDList).Resize(0);
			const_cast<VArray<XString>&>(SpeakingDevicesIDList).Resize(0);
			soundtc.ThreadDone();
		}
		void SoundEnvironment::Refresh()
		{
			soundtc.ThreadWait();
			if(!pEnumerator)
			{
				//�����豸ö����
				if(SUCCEEDED(SetState(CoCreateInstance(CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, IID_IMMDeviceEnumerator,(void**)&pEnumerator))))
				{
					if(pNotify)pEnumerator->UnregisterEndpointNotificationCallback(pNotify);
					pNotify = new DeviceChangeCallback;
					SetState(pEnumerator->RegisterEndpointNotificationCallback(pNotify));//ע��ص���
					SetState(pEnumerator->EnumAudioEndpoints(eCapture,DEVICE_STATEMASK_ALL,&pRecordingDevices));//¼���豸
					SetState(pEnumerator->EnumAudioEndpoints(eRender,DEVICE_STATEMASK_ALL,&pSpeakingDevices));//�����豸
				}
			}
			if(pEnumerator)
			{
				LPWSTR pwszID = NULL;//��ʱ�ַ���
				IMMDevice  *device = NULL;//�����豸
				IPropertyStore *pProps = NULL;
				PROPVARIANT varName;//���ñ���ת��
				UINT cRD,cSD;//�豸����
				//�ɹ���ȡ�豸��Ϣ����ɾ��¼���豸�����б�
				pRecordingDevices->GetCount(&cRD);
				pSpeakingDevices->GetCount(&cSD);
				const_cast<VArray<XString>&>(RecordingDevicesList).ResizeAndDestroy(cRD);
				const_cast<VArray<XString>&>(SpeakingDevicesList).ResizeAndDestroy(cSD);
				const_cast<VArray<XString>&>(RecordingDevicesIDList).ResizeAndDestroy(cRD);
				const_cast<VArray<XString>&>(SpeakingDevicesIDList).ResizeAndDestroy(cSD);
				
				if(cRD)
				{
					UINT count(cRD);
					while(count)//��ȡ�豸ID�б�������б�
					{
						count --;
						pRecordingDevices->Item(count,&device);//ȡ�豸��device
						device->GetId(&pwszID);//ȡ�豸id
						const_cast<VArray<XString>&>(RecordingDevicesIDList)[count] = pwszID;//��¼id
						CoTaskMemFree(pwszID);
						device->OpenPropertyStore(STGM_READ, &pProps);//ȡ�豸����
						pProps->GetValue(PKEY_Device_FriendlyName, &varName);//ȡ�豸��
						const_cast<VArray<XString>&>(RecordingDevicesList)[count] = varName.pwszVal;//д��
						pProps->Release();//�ͷ�
						device->Release();//�ͷ�
					}
				}
				if(cSD)
				{
					UINT count(cSD);
					while(count)//��ȡ�豸ID�б�������б�
					{
						count --;
						pSpeakingDevices->Item(count,&device);//ȡ�豸��device
						device->GetId(&pwszID);//ȡ�豸id
						const_cast<VArray<XString>&>(SpeakingDevicesIDList)[count] = pwszID;//��¼id
						CoTaskMemFree(pwszID);
						device->OpenPropertyStore(STGM_READ, &pProps);//ȡ�豸����
						pProps->GetValue(PKEY_Device_FriendlyName, &varName);//ȡ�豸��
						const_cast<VArray<XString>&>(SpeakingDevicesList)[count] = varName.pwszVal;//д��
						pProps->Release();//�ͷ�
						device->Release();//�ͷ�
					}
				}
			}
			soundtc.ThreadDone();
		}
		HRESULT SoundEnvironment::SetState(HRESULT hr)//��������
		{
			if(FAILED(hr))throw XSoundException(hr);
			return hr;
		}
		int SoundEnvironment::GetDevicesCount()
		{
			if(!pEnumerator)Refresh();
			return SpeakingDevicesList.Length+RecordingDevicesList.Length;
		}
		XString SoundEnvironment::GetDeviceID(const XString& name)
		{
			soundtc.ThreadWait();
			if(!pEnumerator)Refresh();
			XString s=XString::Empty;
			int i = SpeakingDevicesList.IndexOf(name);
			if(i>=0)
			{
				if(i<SpeakingDevicesIDList.Length)s=SpeakingDevicesIDList[i];
			}
			else
			{
				i = RecordingDevicesList.IndexOf(name);
				if(i>=0&&i<RecordingDevicesIDList.Length)s=RecordingDevicesIDList[i];
			}
			soundtc.ThreadDone();
			return s;
		}
		XString SoundEnvironment::GetDeviceName(const XString& id)
		{
			soundtc.ThreadWait();
			if(!pEnumerator)Refresh();
			XString s=XString::Empty;
			int i = SpeakingDevicesIDList.IndexOf(id);
			if(i>=0)
			{
				if(i<SpeakingDevicesList.Length)s=SpeakingDevicesList[i];
			}
			else
			{
				i = RecordingDevicesIDList.IndexOf(id);
				if(i>=0&&i<RecordingDevicesList.Length)s=RecordingDevicesList[i];
			}
			soundtc.ThreadDone();
			return s;
		}

		SoundEnvironment SoundEnvironment::Default;
	}
}
#endif