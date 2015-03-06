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
			case	AUDCLNT_E_NOT_INITIALIZED:return "��Ƶ��δ���ɹ���ʼ��";
			case	AUDCLNT_E_ALREADY_INITIALIZED:return "��Ƶ���Ѿ���ʼ����";
			case	AUDCLNT_E_WRONG_ENDPOINT_TYPE:return "�ڲ����豸��ʹ�ñ�ǣ�AUDCLNT_STREAMFLAGS_LOOPBACK";
			case	AUDCLNT_E_DEVICE_INVALIDATED:return "��Ƶ�豸���γ���������֮������Ӳ���Ѹı�";
			case	AUDCLNT_E_NOT_STOPPED:return "��Ƶ����δֹͣ";
			//case AUDCLNT_E_BUFFER_SIZE_NOT_ALIGNED:return "���Сδ����";
			case	AUDCLNT_E_BUFFER_TOO_LARGE:return "����Ŀ��С����";
			case	AUDCLNT_E_OUT_OF_ORDER:return "IAudioCaptureClient::GetBuffer��IAudioCaptureClient::Releaseδ�ܶ�Ӧ";
			case	AUDCLNT_E_UNSUPPORTED_FORMAT:return "��֧�ֵĸ�ʽ";
			case	AUDCLNT_E_INVALID_SIZE:return "д��֡����������ֵ";
			case	AUDCLNT_E_DEVICE_IN_USE:return "��Ƶ�豸��ռ��";
			case	AUDCLNT_E_BUFFER_OPERATION_PENDING:return "���ڽ������������õ��»�����޷�����";
			case	AUDCLNT_E_THREAD_NOT_REGISTERED:return "�߳�δע��";
			case	0x8889000d://AUDCLNT_E_NO_SINGLE_PROCESS
				return "�ǵ�һ�߳�";
			case	AUDCLNT_E_EXCLUSIVE_MODE_NOT_ALLOWED:return "�豸������ʹ��exclusive-mode";
			//case AUDCLNT_E_INVALID_DEVICE_PERIOD:return "exclusive-mode �ͻ������ʱ�ڴ���500����";
			case	AUDCLNT_E_ENDPOINT_CREATE_FAILED:return "������Ƶ�ն�ʧ�ܣ������豸�Ƿ��Ѳ�ò�����";
			case	AUDCLNT_E_SERVICE_NOT_RUNNING:return "Windows��Ƶ����δ����";
			case	AUDCLNT_E_EVENTHANDLE_NOT_EXPECTED:return "��Ƶ��δΪ�¼�������ʼ��";
			case	AUDCLNT_E_EXCLUSIVE_MODE_ONLY:return "������exclusive-mode";
			case	AUDCLNT_E_BUFDURATION_PERIOD_NOT_EQUAL:return "ʹ�ñ�ǣ�AUDCLNT_STREAMFLAGS_EVENTCALLBACK�������� hnsBufferDuration ��hnsPeriodicity�����";
			case	AUDCLNT_E_EVENTHANDLE_NOT_SET:return "�¼����δ����";
			case	AUDCLNT_E_INCORRECT_BUFFER_SIZE:return "����ȷ�Ŀ��С";
			case	AUDCLNT_E_BUFFER_SIZE_ERROR:return "exclusive-mode�ͻ�����Ŀ鳤�ȳ�����Χ";
			case	AUDCLNT_E_CPUUSAGE_EXCEEDED :return "���ڸ�CPUʹ����";
			default:return XException::GetDescription(hr);
			}
		}
	}
}
#endif