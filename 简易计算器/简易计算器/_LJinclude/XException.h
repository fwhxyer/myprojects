#pragma once
#define XEXCEPTION_

//下标越界错误
#ifndef COR_E_INDEXOUTOFRANGE
#define COR_E_INDEXOUTOFRANGE 0x80131508
#endif

namespace LJ
{
	//异常类型，在检测到错误时抛出
	class XException:public XBase
	{
	protected:
		//错误描述
		XString description;
		//错误类名
		XString errorClassName;
		//内部错误
		XException* pInner;
	public:
		PROPERTY_OFFSET(XException,ErrorClassName);
		//通用基类方法
		XBaseVTypeMethods_H(XException);
		//默认构造函数
		XException()throw();
		//复制构造函数
		XException(const XException& e)throw();
		//使用一个字符串来初始化
		XException(const XString& description)throw();
		//使用一个字符串、错误码、类名来初始化
		XException(const XString& description, HRESULT hr,const XString& className=XString::Empty )throw();
		//使用一个字符串、错误码、类名、内部错误来初始化
		XException(const XString& description, HRESULT hr,const XString& className,const XException& innerException )throw();
		//使用一个错误码来初始化
		XException(HRESULT hr)throw();
		virtual ~XException();
		virtual XString ToString()const;
		virtual XString GetErrorClassName() const;
		virtual XString GetDescription() const;
		virtual XException GetInnerException() const;
		static const char* GetDescription(HRESULT);
		virtual bool Equals(const XException&)const;
		union
		{
			//错误码
			const HRESULT HResult;
			//只读属性：错误类名
			PROPERTY_GET(XString,XException,GetErrorClassName,ErrorClassName);
			//只读属性：错误描述
			PROPERTY_GET(XString,XException,GetDescription,Description);
			//只读属性：内部错误
			PROPERTY_GET(XException,XException,GetInnerException,InnerException);
		};
		//无错误
		const static XException None;
#ifdef _CLR //托管支持
		//从托管异常初始化
		XException(System::Exception^ e);
		//到托管异常的转换
		operator System::Exception^()const;
		//使用托管的方法
		System::Exception^ operator->()const;
#endif
	};
}