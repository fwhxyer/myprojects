#include "stdafx.h"
#ifdef SOUNDENVIRONMENT_
namespace LJ
{
	namespace Sound
	{

		//SoundEnvironment类
		ThreadControl SoundEnvironment::soundtc;
		//录音设备集合
		IMMDeviceCollection* SoundEnvironment::pRecordingDevices;
		//播放设备集合
		IMMDeviceCollection* SoundEnvironment::pSpeakingDevices;
		//设备枚举器
		IMMDeviceEnumerator* SoundEnvironment::pEnumerator=nullptr;
		//产生异步的设备更改过程
		DeviceChangeCallback* SoundEnvironment::pNotify=nullptr;

		//记录已有的扬声器，以便环境变化时发出通知
		VArray<VSpeaker*> SoundEnvironment::speakerList;
		//记录已有的录音机，以便环境变化时发出通知
		VArray<VRecorder*> SoundEnvironment::recorderList;

		//发生各项事件时执行的委托（事件）
		XDelegate<void,XString> SoundEnvironment::OnDeviceAdded;
		XDelegate<void,XString,DWORD> SoundEnvironment::OnDeviceStateChanged;
		XDelegate<void,XString> SoundEnvironment::OnDeviceRemoved;
		XDelegate<void,EDataFlow,ERole,XString> SoundEnvironment::OnDefaultDeviceChanged;
		XDelegate<void,XString,const PROPERTYKEY> SoundEnvironment::OnPropertyValueChanged;

		//录音设备名称列表
		const VArray<XString> SoundEnvironment::RecordingDevicesList;
		//录音设备ID列表
		const VArray<XString> SoundEnvironment::RecordingDevicesIDList;
		//播放设备名称列表
		const VArray< XString> SoundEnvironment::SpeakingDevicesList;
		//播放设备ID列表
		const VArray<XString> SoundEnvironment::SpeakingDevicesIDList;

		//默认声道数
		short SoundEnvironment::DefaultChannels = 2;
		//默认位数
		short SoundEnvironment::DefaultBits = 16;
		//默认样本率
		int SoundEnvironment::DefaultHz = 44100;

		//默认XSpeaker缓冲时间(100ms)
		XTime SoundEnvironment::DefaultSpeakerRequestedDuration=1000000;
		//最小XSpeaker缓冲时间(50ms)
		XTime SoundEnvironment::MinimumSpeakerRequestedDuration=500000;
		//默认XRecorder缓冲时间(100ms)
		XTime SoundEnvironment::DefaultRecorderRequestedDuration=1000000;
		//最小XRecorder缓冲时间(50ms)
		XTime SoundEnvironment::MinimumRecorderRequestedDuration=500000;
		//最后一次更改时已添加的设备ID
		XString SoundEnvironment::OnAddedDeviceId;
		//最后一次状态更改的设备ID
		XString SoundEnvironment::OnStateChangedDeviceId;
		//最后一次状态更改到的新状态
		DWORD SoundEnvironment::OnStateChangedNewState;
		//最后一次移除的设备ID
		XString SoundEnvironment::OnRemovedDeviceId;
		//最后一次默认设备更改的设备ID
		XString SoundEnvironment::OnDefaultChangedDeviceId;
		//最后一次默认设备更改的设备流向
		EDataFlow SoundEnvironment::OnDefaultChangedFlow;
		//最后一次默认设备更改的设备角色
		ERole SoundEnvironment::OnDefaultChangedRole;
		//最后一次设备属性更改的设备ID
		XString SoundEnvironment::OnPropertyValueChangedDeviceId;
		//最后一次设备属性更改的设备属性 
		PROPERTYKEY SoundEnvironment::OnPropertyValueChangedKey;
		//设备更改次数
		volatile long SoundEnvironment::changedCount=0;
		SoundEnvironment::SoundEnvironment()
		{
			if(this!=&Default)throw XSoundException(L"请使用默认音频环境：SoundEnvironment::Default.",E_ILLEGAL_METHOD_CALL,L"SoundEnvironment");
			//初始化
			HRESULT hr=CoInitializeEx(NULL,COINIT_MULTITHREADED);
			if(hr==RPC_E_CHANGED_MODE)
			{//COM库已经被初始化且传入参数设置的并发模式和本次不同。
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
			SetState(pDevice->GetId(&tmp));//获取id
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
			SetState(pDevice->OpenPropertyStore(STGM_READ,&p));//获取信息
			PROPVARIANT inf;
			if(FAILED(hr=p->GetValue(PKEY_Device_FriendlyName,&inf)))//获取名称信息
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
			//此处需要使用重载的&运算符
			for(int i=0;i<speakerList.Length;++i)tmp[i] = speakerList[i]?&(*speakerList[i]):NULL;
			soundtc.ThreadDone();
			return tmp;
		}
		XArray<XRecorder> SoundEnvironment::GetRecordersList()
		{
			soundtc.ThreadWait();
			XArray<XRecorder>tmp(recorderList.Length);
			//此处需要使用重载的&运算符
			for(int i=0;i<recorderList.Length;++i)tmp[i] = recorderList[i]?&(*recorderList[i]):NULL;
			soundtc.ThreadDone();
			return tmp;
		}
		int SoundEnvironment::GetChangedCount(){return changedCount;}//获取更改次数
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
				//创建设备枚举器
				if(SUCCEEDED(SetState(CoCreateInstance(CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, IID_IMMDeviceEnumerator,(void**)&pEnumerator))))
				{
					if(pNotify)pEnumerator->UnregisterEndpointNotificationCallback(pNotify);
					pNotify = new DeviceChangeCallback;
					SetState(pEnumerator->RegisterEndpointNotificationCallback(pNotify));//注册回调类
					SetState(pEnumerator->EnumAudioEndpoints(eCapture,DEVICE_STATEMASK_ALL,&pRecordingDevices));//录音设备
					SetState(pEnumerator->EnumAudioEndpoints(eRender,DEVICE_STATEMASK_ALL,&pSpeakingDevices));//播放设备
				}
			}
			if(pEnumerator)
			{
				LPWSTR pwszID = NULL;//临时字符串
				IMMDevice  *device = NULL;//具体设备
				IPropertyStore *pProps = NULL;
				PROPVARIANT varName;//共用变量转换
				UINT cRD,cSD;//设备数量
				//成功获取设备信息，先删除录音设备描述列表：
				pRecordingDevices->GetCount(&cRD);
				pSpeakingDevices->GetCount(&cSD);
				const_cast<VArray<XString>&>(RecordingDevicesList).ResizeAndDestroy(cRD);
				const_cast<VArray<XString>&>(SpeakingDevicesList).ResizeAndDestroy(cSD);
				const_cast<VArray<XString>&>(RecordingDevicesIDList).ResizeAndDestroy(cRD);
				const_cast<VArray<XString>&>(SpeakingDevicesIDList).ResizeAndDestroy(cSD);
				
				if(cRD)
				{
					UINT count(cRD);
					while(count)//获取设备ID列表和名称列表
					{
						count --;
						pRecordingDevices->Item(count,&device);//取设备到device
						device->GetId(&pwszID);//取设备id
						const_cast<VArray<XString>&>(RecordingDevicesIDList)[count] = pwszID;//记录id
						CoTaskMemFree(pwszID);
						device->OpenPropertyStore(STGM_READ, &pProps);//取设备描述
						pProps->GetValue(PKEY_Device_FriendlyName, &varName);//取设备名
						const_cast<VArray<XString>&>(RecordingDevicesList)[count] = varName.pwszVal;//写入
						pProps->Release();//释放
						device->Release();//释放
					}
				}
				if(cSD)
				{
					UINT count(cSD);
					while(count)//获取设备ID列表和名称列表
					{
						count --;
						pSpeakingDevices->Item(count,&device);//取设备到device
						device->GetId(&pwszID);//取设备id
						const_cast<VArray<XString>&>(SpeakingDevicesIDList)[count] = pwszID;//记录id
						CoTaskMemFree(pwszID);
						device->OpenPropertyStore(STGM_READ, &pProps);//取设备描述
						pProps->GetValue(PKEY_Device_FriendlyName, &varName);//取设备名
						const_cast<VArray<XString>&>(SpeakingDevicesList)[count] = varName.pwszVal;//写入
						pProps->Release();//释放
						device->Release();//释放
					}
				}
			}
			soundtc.ThreadDone();
		}
		HRESULT SoundEnvironment::SetState(HRESULT hr)//出错设置
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