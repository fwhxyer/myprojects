#pragma once
#define XSOUNDEXCEPTION_
#include "..\\XException.h"
namespace LJ
{
	namespace Sound
	{
		//��Ƶ�쳣��
		class XSoundException:public LJ::XException
		{
		public:
			//ʹ���ַ�����ʼ��
			XSoundException(const XString& description)throw();
			//ʹ���ַ����������롢������ʼ��
			XSoundException(const XString& description, HRESULT hr,const XString&className)throw();
			//ʹ�ô������ʼ��
			XSoundException(HRESULT hr)throw();
			//��ȡ��Ӧ�����������
			static const char* GetDescription(HRESULT hr);
		};
	}
}