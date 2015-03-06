#pragma once
#define DEVICECHANGECALLBACK_
namespace LJ
{
	namespace Sound
	{
		//�豸�仯�ص���
		class DeviceChangeCallback :public  IMMNotificationClient
		{
			//���ü���
			LONG _cRef;
			//�ص�ͬʱ�����������̣߳�
			volatile long count;
		public:
			DeviceChangeCallback():_cRef(1),count(0){}
			~DeviceChangeCallback(){}
			//�̳���IUnknow
			ULONG STDMETHODCALLTYPE AddRef();
			//�̳���IUnknow
			ULONG STDMETHODCALLTYPE Release();
			//�̳���IUnknow
			HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, VOID **ppvInterface);
			//�豸״̬�ı�
			HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState);
			//�豸���
			HRESULT STDMETHODCALLTYPE OnDeviceAdded( LPCWSTR pwstrDeviceId);
			//�豸���Ƴ�
			HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR pwstrDeviceId);
			//Ĭ���豸�ı�
			HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow flow,ERole role,LPCWSTR pwstrDefaultDeviceId);
			//����ֵ�ı�
			HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR pwstrDeviceId,const PROPERTYKEY key);
		};
	}
}