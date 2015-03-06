#include "stdafx.h"
#ifdef XEXCEPTION_
#include "WinError.h"
namespace LJ
{
	//��ǰ������
	//��ȡ����������Ϣ
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
#ifdef _CLR //�й�֧��
	XException::XException(System::Exception^ e)//���й��쳣��ʼ��
		:HResult(Marshal::GetHRForException(e)),errorClassName(e->Source),description(e->Message)
	{	}
	XException::operator System::Exception^()const//���й��쳣��ת��
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
		case S_OK:return "�����ɹ�";
		case E_UNEXPECTED:return "�����ʧ��";
		case E_NOTIMPL:return "δʵ��";
		case E_OUTOFMEMORY:return "δ�ܷ���������ڴ�";
		case E_INVALIDARG:return "һ������������Ч";
		case E_NOINTERFACE:return "��֧�ִ˽ӿ�";
		case E_POINTER:return "��Чָ��";
		case E_HANDLE:return "��Ч���";
		case E_ABORT:return "��������ֹ";
		case E_FAIL:return "δָ����ʧ��";
		case E_ACCESSDENIED:return "���ʱ��ܾ�";
		case COR_E_INDEXOUTOFRANGE:return "�����±�Խ��";
		default:HLOCAL LocalAddress=NULL;  //��ϵͳ������ӳ���в��ң�Ӣ��������
FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_SYSTEM,  
     NULL,HResult,0,(PTSTR)&LocalAddress,0,NULL);  
		return LocalAddress?(LPCSTR)LocalAddress:"δ֪����";
		}
	}
	bool XException::Equals(const XException&e)const{return e.HResult==HResult;}
}
#endif