#pragma once
#define DEVICECHANGECALLBACK_
namespace LJ
{
	namespace Sound
	{
		//设备变化回调类
		class DeviceChangeCallback :public  IMMNotificationClient
		{
			//引用计数
			LONG _cRef;
			//回调同时操作数（多线程）
			volatile long count;
		public:
			DeviceChangeCallback():_cRef(1),count(0){}
			~DeviceChangeCallback(){}
			//继承自IUnknow
			ULONG STDMETHODCALLTYPE AddRef();
			//继承自IUnknow
			ULONG STDMETHODCALLTYPE Release();
			//继承自IUnknow
			HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, VOID **ppvInterface);
			//设备状态改变
			HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState);
			//设备添加
			HRESULT STDMETHODCALLTYPE OnDeviceAdded( LPCWSTR pwstrDeviceId);
			//设备被移除
			HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR pwstrDeviceId);
			//默认设备改变
			HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow flow,ERole role,LPCWSTR pwstrDefaultDeviceId);
			//属性值改变
			HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR pwstrDeviceId,const PROPERTYKEY key);
		};
	}
}