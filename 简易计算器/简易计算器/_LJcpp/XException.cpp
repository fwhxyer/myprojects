#include "stdafx.h"
#ifdef XEXCEPTION_
#include "WinError.h"
namespace LJ
{
	//当前的类型
	//获取对象类型信息
	const XTypes& XException::CurrentType = CREATECLASSTYPE(LJ::XException,LJ::XBase);
	XException::XException()throw()
		:HResult(0),errorClassName(XString::Empty),description(XString::Empty),pInner(nullptr)
	{	}

	XException::XException(const XString& description)throw()
		:HResult(0),errorClassName(XString::Empty),description(description),pInner(nullptr)
	{	}
	XException::XException(const XException& e)throw()
		:HResult(e.HResult),description(e.description),errorClassName(e.errorClassName),pInner(e.pInner?new XException(*e.pInner):nullptr)
	{	}
	XException::XException(const XString& description, HRESULT HResult,const XString& className)throw()
		:HResult(HResult),errorClassName(className),description(description),pInner(nullptr)
	{	}
	XException::XException(const XString& description, HRESULT HResult,const XString& className,const XException& innerException )throw()
		:HResult(HResult),errorClassName(className),description(description),pInner(new XException(innerException))
	{	}

	XException::XException(HRESULT HResult)throw()
		:HResult(HResult),description(GetDescription(HResult)),pInner(nullptr)
	{	}
	XException::~XException()
	{
		delete pInner;
	}
	XString XException::GetErrorClassName() const
	{
		return errorClassName;
	}
	XString XException::GetDescription() const
	{
		return description;
	}
	XException XException::GetInnerException() const
	{
		if(pInner)
		{
			return *pInner;
		}
		return None;
	}
	XString XException::ToString()const
	{
		return description;
	}
#ifdef _CLR //托管支持
	XException::XException(System::Exception^ e)//从托管异常初始化
		:HResult(Marshal::GetHRForException(e)),errorClassName(e->Source),description(e->Message)
	{	}
	XException::operator System::Exception^()const//到托管异常的转换
	{
		if(pInner)return gcnew System::Exception(String::Format( "(HRESULT:0x{1:X8}) {0}",description.ToGcString(), HResult),*pInner);
		return gcnew System::Exception(String::Format( "(HRESULT:0x{1:X8}) {0}",description.ToGcString(), HResult),nullptr);
	}
	System::Exception^ XException::operator->()const
	{
		return (System::Exception^)*this;
	}
#endif
	const char* XException::GetDescription(HRESULT HResult)
	{
		switch(HResult)
		{
		case S_OK:return "操作成功";
		case E_UNEXPECTED:return "意外的失败";
		case E_NOTIMPL:return "未实现";
		case E_OUTOFMEMORY:return "未能分配所需的内存";
		case E_INVALIDARG:return "一个或多个参数无效";
		case E_NOINTERFACE:return "不支持此接口";
		case E_POINTER:return "无效指针";
		case E_HANDLE:return "无效句柄";
		case E_ABORT:return "操作已中止";
		case E_FAIL:return "未指定的失败";
		case E_ACCESSDENIED:return "访问被拒绝";
		case COR_E_INDEXOUTOFRANGE:return "数组下标越界";
		default:HLOCAL LocalAddress=NULL;  //从系统的描述映射中查找（英文描述）
FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_SYSTEM,  
     NULL,HResult,0,(PTSTR)&LocalAddress,0,NULL);  
		return LocalAddress?(LPCSTR)LocalAddress:"未知错误";
		}
	}
	bool XException::Equals(const XException&e)const{return e.HResult==HResult;}
}
#endif