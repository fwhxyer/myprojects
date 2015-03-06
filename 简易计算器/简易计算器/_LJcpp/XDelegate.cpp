#include "stdafx.h"
#ifdef XDELEGATE_
namespace LJ
{
	const XTypes& IDelegate::CurrentType = CREATECLASSTYPE(LJ::IDelegate,LJ::XBase);
	const XTypes& XActions::CurrentType = CREATECLASSTYPE(LJ::XActions,LJ::XBase);
	const XTypes& XDelegates::CurrentType = CREATECLASSTYPE(LJ::XDelegates,LJ::XBase);

	//ͨ���������������XActions����
	IDelegate* IDelegate::NewAction(void*,void*,void*,void*,void*,void*,void*,void*){return NULL;}
	IDelegate* IDelegate::NewAction(void*,void*,void*,void*,void*,void*,void*){return NULL;}
	IDelegate* IDelegate::NewAction(void*,void*,void*,void*,void*,void*){return NULL;}
	IDelegate* IDelegate::NewAction(void*,void*,void*,void*,void*){return NULL;}
	IDelegate* IDelegate::NewAction(void*,void*,void*,void*){return NULL;}
	IDelegate* IDelegate::NewAction(void*,void*,void*){return NULL;}
	IDelegate* IDelegate::NewAction(void*,void*){return NULL;}
	IDelegate* IDelegate::NewAction(void*){return NULL;}
	IDelegate* IDelegate::NewAction(){return NULL;}
	//ͬ�����ã�����з���ֵ�����ѡ��Ľ��ܷ���ֵ
	void* IDelegate::Invoke(void*,void*,void*,void*,void*,void*,void*,void*,void*const&){return NULL;}
	void* IDelegate::Invoke(void*,void*,void*,void*,void*,void*,void*,void*const&){return NULL;}
	void* IDelegate::Invoke(void*,void*,void*,void*,void*,void*,void*const&){return NULL;}
	void* IDelegate::Invoke(void*,void*,void*,void*,void*,void*const&){return NULL;}
	void* IDelegate::Invoke(void*,void*,void*,void*,void*const&){return NULL;}
	void* IDelegate::Invoke(void*,void*,void*,void*const&){return NULL;}
	void* IDelegate::Invoke(void*,void*,void*const&){return NULL;}
	void* IDelegate::Invoke(void*,void*const&){return NULL;}
	void* IDelegate::Invoke(void*const&){return NULL;}
	void* IDelegate::Invoke(){return NULL;}
	//�첽���ã���ѡ����ܷ���ֵ���������ֵΪ���ã���д��һ��ָ��
	DWORD IDelegate::BeginInvoke(void* x1,void* x2,void* x3,void* x4,void* x5,void* x6,void* x7,void* x8,void*const&x9){return NULL;}
	DWORD IDelegate::BeginInvoke(void* x1,void* x2,void* x3,void* x4,void* x5,void* x6,void* x7,void*const&x8){return NULL;}
	DWORD IDelegate::BeginInvoke(void* x1,void* x2,void* x3,void* x4,void* x5,void* x6,void*const&x7){return NULL;}
	DWORD IDelegate::BeginInvoke(void* x1,void* x2,void* x3,void* x4,void* x5,void*const&x6){return NULL;}
	DWORD IDelegate::BeginInvoke(void* x1,void* x2,void* x3,void* x4,void*const&x5){return NULL;}
	DWORD IDelegate::BeginInvoke(void* x1,void* x2,void* x3,void*const&x4){return NULL;}
	DWORD IDelegate::BeginInvoke(void* x1,void* x2,void*const&x3){return NULL;}
	DWORD IDelegate::BeginInvoke(void* x1,void*const&x2){return NULL;}
	DWORD IDelegate::BeginInvoke(void*const&x1){return NULL;}
	DWORD IDelegate::BeginInvoke(){return NULL;}


	bool IDelegate::IsAction()const{return false;}
	void IDelegate::Do(){}
	DWORD IDelegate::DoSync()
	{
		return ThreadControl::StartThread(this,&IDelegate::Do);
	}
	IDelegate* IDelegate::NewDelegate()const{return NULL;}
	void* IDelegate::GetReturnValuePointer(){return GetParameterPointer(0);}
	XTypes IDelegate::GetParameterType(int)const{return XTypes(Types<void>());}
	void* IDelegate::GetParameterPointer(int)const{return NULL;}




	XDelegates XActions::MakeDelegate()const
	{
		return Pointer()->NewDelegate();
	}
	//ͬ��ִ�ж���
	void XActions::Do()
	{
		Pointer()->Do();
	}
	//�첽ִ�ж���
	DWORD XActions::DoSync()
	{
		return Pointer()->DoSync();
	}

}
#endif