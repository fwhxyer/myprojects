#pragma once
#define SOUNDENVIRONMENT_
#include "XSpeaker.h"
#include "XRecorder.h"
namespace LJ
{
	namespace Sound
	{
		//各种GUID和静态常量
		const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
		const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
		const IID IID_IAudioClient = __uuidof(IAudioClient);
		const IID IID_IAudioCaptureClient = __uuidof(IAudioCaptureClient);
		const IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);

		//考虑线程安全
		class SoundEnvironment
		{
			friend VSpeaker;
			friend VRecorder;
			friend DeviceChangeCallback;
			//线程同步控制
			static ThreadControl soundtc;
			//录音设备集合
			static IMMDeviceCollection* pRecordingDevices;
			//播放设备集合
			static IMMDeviceCollection* pSpeakingDevices;
			//设备枚举器
			static IMMDeviceEnumerator *pEnumerator;
			//产生异步的设备更改过程
			static DeviceChangeCallback* pNotify;
			//记录已有的扬声器，以便环境变化时发出通知
			static VArray<VSpeaker*> speakerList;
			//记录已有的录音机，以便环境变化时发出通知
			static VArray<VRecorder*> recorderList;
			//添加扬声器指针，方便有事件发生时进行通知
			static void AddSpeaker(VSpeaker* speaker);
			//添加录音机指针，方便有事件发生时进行通知
			static void AddRecorder(VRecorder* recorder);
			//移除扬声器指针
			static void RemoveSpeaker(VSpeaker* speaker);
			//移除录音机指针
			static void RemoveRecorder(VRecorder* recorder);
			//获取默认录音设备,使用完毕需要调用其成员函数Release()
			static IMMDevice* GetDefaultRecordingDevice();
			//获取默认播放设备,使用完毕需要调用其成员函数Release()
			static IMMDevice* GetDefaultSpeakingDevice();
			//获取按设备Id指定的设备,使用完毕需要调用其成员函数Release()
			static IMMDevice* GetDevice(const XString& Id);
			//获取设备ID
			static XString GetDeviceID(IMMDevice* pDevice);
			//根据设备名
			static XString GetDeviceName(IMMDevice* pDevice);

			//设备变更次数
			static volatile long changedCount;
		public:
			//发生各项事件时执行的委托（事件）
			static XDelegate<void,XString> OnDeviceAdded;
			static XDelegate<void,XString,DWORD> OnDeviceStateChanged;
			static XDelegate<void,XString> OnDeviceRemoved;
			static XDelegate<void,EDataFlow,ERole,XString> OnDefaultDeviceChanged;
			static XDelegate<void,XString,const PROPERTYKEY> OnPropertyValueChanged;
			//录音设备名称列表
			static const VArray<XString> RecordingDevicesList;
			//录音设备ID列表
			static const VArray<XString> RecordingDevicesIDList;
			//播放设备名称列表
			static const VArray< XString> SpeakingDevicesList;
			//播放设备ID列表
			static const VArray<XString> SpeakingDevicesIDList;
			//默认声道数
			static short DefaultChannels;
			//默认位数
			static short DefaultBits;
			//默认样本率
			static int DefaultHz;

			//默认XSpeaker缓冲时间
			static XTime DefaultSpeakerRequestedDuration;
			//最小XSpeaker缓冲时间
			static XTime MinimumSpeakerRequestedDuration;
			//默认XRecorder缓冲时间
			static XTime DefaultRecorderRequestedDuration;
			//最小XRecorder缓冲时间
			static XTime MinimumRecorderRequestedDuration;
			//最后一次更改时已添加的设备ID
			static XString OnAddedDeviceId;
			//最后一次状态更改的设备ID
			static XString OnStateChangedDeviceId;
			//最后一次状态更改到的新状态
			static DWORD OnStateChangedNewState;
			//最后一次移除的设备ID
			static XString OnRemovedDeviceId;
			//最后一次默认设备更改的设备ID
			static XString OnDefaultChangedDeviceId;
			//最后一次默认设备更改的设备流向
			static EDataFlow OnDefaultChangedFlow;
			//最后一次默认设备更改的设备角色
			static ERole OnDefaultChangedRole;
			//最后一次设备属性更改的设备ID
			static XString OnPropertyValueChangedDeviceId;
			//最后一次设备属性更改的设备属性 
			static PROPERTYKEY OnPropertyValueChangedKey;
			SoundEnvironment();
			~SoundEnvironment();
			//获取已有的扬声器列表
			static XArray<XSpeaker> GetSpeakersList();
			//获取已有的录音机列表
			static XArray<XRecorder> GetRecordersList();
			//获取更改次数
			static int GetChangedCount();
			//删除原有信息
			static void Clear();
			//刷新设备信息
			static void Refresh();
			static HRESULT SetState(HRESULT hr);
			//获取默认录音设备Id
			static XString GetDefaultRecordingDeviceId();
			//获取默认播放设备Id
			static XString GetDefaultSpeakingDeviceId();
			//获取设备数量
			static int GetDevicesCount();
			//根据设备名称获取id，请慎用此功能，因为可能存在相同名称的设备
			static XString GetDeviceID(const XString& name);
			//根据设备ID获取名称，该ID既可以是录音设备也可以是播放设备的
			static XString GetDeviceName(const XString& id);

			static SoundEnvironment Default;
		};

	}
}