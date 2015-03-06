#include "stdafx.h"
#ifdef XSOUNDEXCEPTION_
namespace LJ
{
	namespace Sound
	{
		XSoundException::XSoundException(const XString& description)throw()
			:XException(description)
		{}
		XSoundException::XSoundException(const XString& description, HRESULT hr,const XString&className)throw()
			:XException(description,hr,className)
		{			}
		XSoundException::XSoundException(HRESULT hr)throw()
			:XException(GetDescription(hr),hr,XString::Empty)
		{			}
		const char* XSoundException::GetDescription(HRESULT hr)
		{
			switch(hr)
			{
			case	AUDCLNT_E_NOT_INITIALIZED:return "音频流未被成功初始化";
			case	AUDCLNT_E_ALREADY_INITIALIZED:return "音频流已经初始化过";
			case	AUDCLNT_E_WRONG_ENDPOINT_TYPE:return "在捕获设备上使用标记：AUDCLNT_STREAMFLAGS_LOOPBACK";
			case	AUDCLNT_E_DEVICE_INVALIDATED:return "音频设备被拔出，或者与之关联的硬件已改变";
			case	AUDCLNT_E_NOT_STOPPED:return "音频流尚未停止";
			//case AUDCLNT_E_BUFFER_SIZE_NOT_ALIGNED:return "块大小未对齐";
			case	AUDCLNT_E_BUFFER_TOO_LARGE:return "请求的块大小过大";
			case	AUDCLNT_E_OUT_OF_ORDER:return "IAudioCaptureClient::GetBuffer与IAudioCaptureClient::Release未能对应";
			case	AUDCLNT_E_UNSUPPORTED_FORMAT:return "不支持的格式";
			case	AUDCLNT_E_INVALID_SIZE:return "写入帧数超出请求值";
			case	AUDCLNT_E_DEVICE_IN_USE:return "音频设备被占用";
			case	AUDCLNT_E_BUFFER_OPERATION_PENDING:return "正在进行数据流重置导致缓冲块无法访问";
			case	AUDCLNT_E_THREAD_NOT_REGISTERED:return "线程未注册";
			case	0x8889000d://AUDCLNT_E_NO_SINGLE_PROCESS
				return "非单一线程";
			case	AUDCLNT_E_EXCLUSIVE_MODE_NOT_ALLOWED:return "设备不允许使用exclusive-mode";
			//case AUDCLNT_E_INVALID_DEVICE_PERIOD:return "exclusive-mode 客户请求的时期大于500毫秒";
			case	AUDCLNT_E_ENDPOINT_CREATE_FAILED:return "创建音频终端失败，请检查设备是否已插好并启用";
			case	AUDCLNT_E_SERVICE_NOT_RUNNING:return "Windows音频服务未启动";
			case	AUDCLNT_E_EVENTHANDLE_NOT_EXPECTED:return "音频流未为事件驱动初始化";
			case	AUDCLNT_E_EXCLUSIVE_MODE_ONLY:return "仅能用exclusive-mode";
			case	AUDCLNT_E_BUFDURATION_PERIOD_NOT_EQUAL:return "使用标记：AUDCLNT_STREAMFLAGS_EVENTCALLBACK，但参数 hnsBufferDuration 和hnsPeriodicity不相等";
			case	AUDCLNT_E_EVENTHANDLE_NOT_SET:return "事件句柄未设置";
			case	AUDCLNT_E_INCORRECT_BUFFER_SIZE:return "不正确的块大小";
			case	AUDCLNT_E_BUFFER_SIZE_ERROR:return "exclusive-mode客户请求的块长度超出范围";
			case	AUDCLNT_E_CPUUSAGE_EXCEEDED :return "长期高CPU使用率";
			default:return XException::GetDescription(hr);
			}
		}
	}
}
#endif