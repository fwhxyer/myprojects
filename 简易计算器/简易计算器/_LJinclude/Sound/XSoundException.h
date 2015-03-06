#pragma once
#define XSOUNDEXCEPTION_
#include "..\\XException.h"
namespace LJ
{
	namespace Sound
	{
		//音频异常类
		class XSoundException:public LJ::XException
		{
		public:
			//使用字符串初始化
			XSoundException(const XString& description)throw();
			//使用字符串、错误码、类名初始化
			XSoundException(const XString& description, HRESULT hr,const XString&className)throw();
			//使用错误码初始化
			XSoundException(HRESULT hr)throw();
			//获取对应错误码的描述
			static const char* GetDescription(HRESULT hr);
		};
	}
}