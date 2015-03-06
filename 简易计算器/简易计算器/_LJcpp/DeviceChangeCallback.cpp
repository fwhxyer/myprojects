#include "stdafx.h"
#ifdef DEVICECHANGECALLBACK_
namespace LJ
{
	namespace Sound
	{
		//DeviceChangeCallback类
		ULONG STDMETHODCALLTYPE DeviceChangeCallback::AddRef()
		{
			return InterlockedIncrement(&_cRef);//引用计数增加
		}
		ULONG STDMETHODCALLTYPE DeviceChangeCallback::Release()
		{
			ULONG ulRef = InterlockedDecrement(&_cRef);
			if (0 == ulRef)
			{//不执行删除
			}
			return ulRef;
		}
		HRESULT STDMETHODCALLTYPE DeviceChangeCallback::QueryInterface(REFIID riid, VOID **ppvInterface)
		{
			if (IID_IUnknown == riid)
			{
				AddRef();
				*ppvInterface = (IUnknown*)this;
			}
			else if (__uuidof(IMMNotificationClient) == riid)
			{
				AddRef();
				*ppvInterface = (IMMNotificationClient*)this;
			}
			else
			{
				*ppvInterface = NULL;
				return E_NOINTERFACE;
			}
			return S_OK;
		}
		HRESULT STDMETHODCALLTYPE DeviceChangeCallback::OnDeviceAdded( LPCWSTR pwstrDeviceId)
		{
			InterlockedIncrement(&SoundEnvironment::changedCount);
			if(!SoundEnvironment::soundtc.ThreadTry())
			{
				if(InterlockedIncrement(&count)>1){InterlockedDecrement(&count);return 0;}
				SoundEnvironment::soundtc.ThreadWait();
			}
			SoundEnvironment::OnAddedDeviceId = pwstrDeviceId;
			for(int i =0;i<SoundEnvironment::speakerList.Length;++i)ThreadControl::StartThread(SoundEnvironment::speakerList[i],&VSpeaker::OnDeviceAdded);
			for(int i =0;i<SoundEnvironment::recorderList.Length;++i)ThreadControl::StartThread(SoundEnvironment::recorderList[i],&VRecorder::OnDeviceAdded);
			InterlockedDecrement(&count);
			SoundEnvironment::soundtc.ThreadDone();
			if(!SoundEnvironment::OnDeviceAdded.IsNull())SoundEnvironment::OnDeviceAdded.BeginInvoke(pwstrDeviceId);
			return 0;
		}
		HRESULT STDMETHODCALLTYPE DeviceChangeCallback::OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState)
		{
			InterlockedIncrement(&SoundEnvironment::changedCount);
			if(!SoundEnvironment::soundtc.ThreadTry())
			{
				if(InterlockedIncrement(&count)>1){InterlockedDecrement(&count);return 0;}
				SoundEnvironment::soundtc.ThreadWait();
			}
			SoundEnvironment::OnStateChangedDeviceId = pwstrDeviceId;
			SoundEnvironment::OnStateChangedNewState = dwNewState;
			for(int i =0;i<SoundEnvironment::speakerList.Length;++i)ThreadControl::StartThread(SoundEnvironment::speakerList[i],&VSpeaker::OnDeviceStateChanged);
			for(int i =0;i<SoundEnvironment::recorderList.Length;++i)ThreadControl::StartThread(SoundEnvironment::recorderList[i],&VRecorder::OnDeviceStateChanged);
			InterlockedDecrement(&count);
			SoundEnvironment::soundtc.ThreadDone();
			if(!SoundEnvironment::OnDeviceStateChanged.IsNull())SoundEnvironment::OnDeviceStateChanged.BeginInvoke(pwstrDeviceId,dwNewState);
			return 0;
		}
		HRESULT STDMETHODCALLTYPE DeviceChangeCallback::OnDeviceRemoved(LPCWSTR pwstrDeviceId)
		{
			InterlockedIncrement(&SoundEnvironment::changedCount);
			if(!SoundEnvironment::soundtc.ThreadTry())
			{
				if(InterlockedIncrement(&count)>1){InterlockedDecrement(&count);return 0;}
				SoundEnvironment::soundtc.ThreadWait();
			}
			SoundEnvironment::OnRemovedDeviceId = pwstrDeviceId;
			for(int i =0;i<SoundEnvironment::speakerList.Length;++i)ThreadControl::StartThread(SoundEnvironment::speakerList[i],&VSpeaker::OnDeviceRemoved);
			for(int i =0;i<SoundEnvironment::recorderList.Length;++i)ThreadControl::StartThread(SoundEnvironment::recorderList[i],&VRecorder::OnDeviceRemoved);
			InterlockedDecrement(&count);
			SoundEnvironment::soundtc.ThreadDone();
			if(!SoundEnvironment::OnDeviceRemoved.IsNull())SoundEnvironment::OnDeviceRemoved.BeginInvoke(pwstrDeviceId);
			return 0;
		} 
		HRESULT STDMETHODCALLTYPE DeviceChangeCallback::OnDefaultDeviceChanged(EDataFlow flow,ERole role,LPCWSTR pwstrDefaultDeviceId)
		{
			InterlockedIncrement(&SoundEnvironment::changedCount);
			if(!SoundEnvironment::soundtc.ThreadTry())
			{
				if(InterlockedIncrement(&count)>1){InterlockedDecrement(&count);return 0;}
				SoundEnvironment::soundtc.ThreadWait();
			}
			SoundEnvironment::OnDefaultChangedFlow = flow;
			SoundEnvironment::OnDefaultChangedRole = role;
			SoundEnvironment::OnDefaultChangedDeviceId = pwstrDefaultDeviceId;
			if(flow==eRender)for(int i =0;i<SoundEnvironment::speakerList.Length;++i)ThreadControl::StartThread(SoundEnvironment::speakerList[i],&VSpeaker::OnDefaultDeviceChanged);
			if(flow==eCapture)for(int i =0;i<SoundEnvironment::recorderList.Length;++i)ThreadControl::StartThread(SoundEnvironment::recorderList[i],&VRecorder::OnDefaultDeviceChanged);
			InterlockedDecrement(&count);
			SoundEnvironment::soundtc.ThreadDone();
			if(!SoundEnvironment::OnDefaultDeviceChanged.IsNull())SoundEnvironment::OnDefaultDeviceChanged.BeginInvoke(flow,role,pwstrDefaultDeviceId);
			return 0;
		}
		HRESULT STDMETHODCALLTYPE DeviceChangeCallback::OnPropertyValueChanged(LPCWSTR pwstrDeviceId,const PROPERTYKEY key)
		{
			InterlockedIncrement(&SoundEnvironment::changedCount);
			if(!SoundEnvironment::soundtc.ThreadTry())
			{
				if(InterlockedIncrement(&count)>1){InterlockedDecrement(&count);return 0;}
				SoundEnvironment::soundtc.ThreadWait();
			}
			SoundEnvironment::OnPropertyValueChangedDeviceId=pwstrDeviceId;
			SoundEnvironment::OnPropertyValueChangedKey = key;
			for(int i =0;i<SoundEnvironment::speakerList.Length;++i)ThreadControl::StartThread(SoundEnvironment::speakerList[i],&VSpeaker::OnDevicePropertyValueChanged);
			for(int i =0;i<SoundEnvironment::recorderList.Length;++i)ThreadControl::StartThread(SoundEnvironment::recorderList[i],&VRecorder::OnDevicePropertyValueChanged);
			InterlockedDecrement(&count);
			SoundEnvironment::soundtc.ThreadDone();
			if(!SoundEnvironment::OnPropertyValueChanged.IsNull())SoundEnvironment::OnPropertyValueChanged.BeginInvoke(pwstrDeviceId,key);
			return 0;
		}
	}
}
#endif