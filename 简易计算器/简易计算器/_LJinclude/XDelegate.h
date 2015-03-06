#pragma once
#include "IDelegate.h"
#ifndef E_ILLEGAL_METHOD_CALL
#define E_ILLEGAL_METHOD_CALL 0x8000000EL
#endif
namespace LJ
{
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>class XDelegate;
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>class XAction;


	//��ʾһ��ί�е����ã���װ��ִ�ж����ָ�루��Գ�Ա����������ĳ���ض��ķ�����ָ��
	class XDelegates:public XBase
	{
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>friend class XDelegate;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegates,IDelegate);
		//��ʵ������ָ�빹��
		XDelegates(IDelegate*p):XBase(p){		}
		//XDelegateͨ�÷���
		/*��ȡ����������id*/
		XTypes GetParameterType(int index)const{return Pointer()->GetParameterType(index);}
		/*��ȡί�в�������*/
		int GetParametersCount()const{return Pointer()->GetParametersCount();}
		/*���ز������ͼ�����*/
		TypesCheckingObject GetTypesChecking()const{return Pointer()->GetTypesChecking();}
		/*�з���ֵ*/
		bool CanReturnValue()const{return Pointer()->CanReturnValue();}
		//��ת
		void Reverse(){return Pointer()->Reverse();}

		//��XDelegate����
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>XDelegates(const XDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>&);
		//��VDelegate���죺
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>XDelegates(const VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>& d):XBase(d.NewCopy()){}
		//�ɺ���ֱ�ӹ���

		//__cdecl
#ifdef CANUSECDECL
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>XDelegates(R (__cdecl*fun)(T1,T2,T3,T4,T5,T6,T7,T8))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun)){}
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>XDelegates(R (__cdecl*fun)(T1,T2,T3,T4,T5,T6,T7))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7>(fun)){}
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6>XDelegates(R (__cdecl*fun)(T1,T2,T3,T4,T5,T6))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6>(fun)){}
		template<class R,class T1,class T2,class T3,class T4,class T5>XDelegates(R (__cdecl*fun)(T1,T2,T3,T4,T5))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5>(fun)){}
		template<class R,class T1,class T2,class T3,class T4>XDelegates(R (__cdecl*fun)(T1,T2,T3,T4))
			:XBase(new VDelegate<R,T1,T2,T3,T4>(fun)){}
		template<class R,class T1,class T2,class T3>XDelegates(R (__cdecl*fun)(T1,T2,T3))
			:XBase(new VDelegate<R,T1,T2,T3>(fun)){}
		template<class R,class T1,class T2>XDelegates(R (__cdecl*fun)(T1,T2))
			:XBase(new VDelegate<R,T1,T2>(fun)){}
		template<class R,class T1>XDelegates(R (__cdecl*fun)(T1))
			:XBase(new VDelegate<R,T1>(fun)){}
		template<class R>XDelegates(R (__cdecl*fun)())
			:XBase(new VDelegate<R>(fun)){}
#endif
		//__stdcall
#ifdef CANUSESTDCALL
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>XDelegates(R (__stdcall*fun)(T1,T2,T3,T4,T5,T6,T7,T8))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun)){}
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>XDelegates(R (__stdcall*fun)(T1,T2,T3,T4,T5,T6,T7))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7>(fun)){}
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6>XDelegates(R (__stdcall*fun)(T1,T2,T3,T4,T5,T6))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6>(fun)){}
		template<class R,class T1,class T2,class T3,class T4,class T5>XDelegates(R (__stdcall*fun)(T1,T2,T3,T4,T5))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5>(fun)){}
		template<class R,class T1,class T2,class T3,class T4>XDelegates(R (__stdcall*fun)(T1,T2,T3,T4))
			:XBase(new VDelegate<R,T1,T2,T3,T4>(fun)){}
		template<class R,class T1,class T2,class T3>XDelegates(R (__stdcall*fun)(T1,T2,T3))
			:XBase(new VDelegate<R,T1,T2,T3>(fun)){}
		template<class R,class T1,class T2>XDelegates(R (__stdcall*fun)(T1,T2))
			:XBase(new VDelegate<R,T1,T2>(fun)){}
		template<class R,class T1>XDelegates(R (__stdcall*fun)(T1))
			:XBase(new VDelegate<R,T1>(fun)){}
		template<class R>XDelegates(R (__stdcall*fun)())
			:XBase(new VDelegate<R>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>XDelegates(R (__fastcall*fun)(T1,T2,T3,T4,T5,T6,T7,T8))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun)){}
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>XDelegates(R (__fastcall*fun)(T1,T2,T3,T4,T5,T6,T7))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7>(fun)){}
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6>XDelegates(R (__fastcall*fun)(T1,T2,T3,T4,T5,T6))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6>(fun)){}
		template<class R,class T1,class T2,class T3,class T4,class T5>XDelegates(R (__fastcall*fun)(T1,T2,T3,T4,T5))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5>(fun)){}
		template<class R,class T1,class T2,class T3,class T4>XDelegates(R (__fastcall*fun)(T1,T2,T3,T4))
			:XBase(new VDelegate<R,T1,T2,T3,T4>(fun)){}
		template<class R,class T1,class T2,class T3>XDelegates(R (__fastcall*fun)(T1,T2,T3))
			:XBase(new VDelegate<R,T1,T2,T3>(fun)){}
		template<class R,class T1,class T2>XDelegates(R (__fastcall*fun)(T1,T2))
			:XBase(new VDelegate<R,T1,T2>(fun)){}
		template<class R,class T1>XDelegates(R (__fastcall*fun)(T1))
			:XBase(new VDelegate<R,T1>(fun)){}
		template<class R>XDelegates(R (__fastcall*fun)())
			:XBase(new VDelegate<R>(fun)){}
#endif
		//__thiscall
		template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>XDelegates(T*t,R (T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>(t,fun))
		{		}
		template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7>XDelegates(T*t,R (T::*fun)(T1,T2,T3,T4,T5,T6,T7))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7>(t,fun))
		{		}
		template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6>XDelegates(T*t,R (T::*fun)(T1,T2,T3,T4,T5,T6))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6>(t,fun))
		{		}
		template<class R,class T,class T1,class T2,class T3,class T4,class T5>XDelegates(T*t,R (T::*fun)(T1,T2,T3,T4,T5))
			:XBase(new VDelegate<R,T1,T2,T3,T4,T5>(t,fun))
		{		}
		template<class R,class T,class T1,class T2,class T3,class T4>XDelegates(T*t,R (T::*fun)(T1,T2,T3,T4))
			:XBase(new VDelegate<R,T1,T2,T3,T4>(t,fun))
		{		}
		template<class R,class T,class T1,class T2,class T3>XDelegates(T*t,R (T::*fun)(T1,T2,T3))
			:XBase(new VDelegate<R,T1,T2,T3>(t,fun))
		{		}
		template<class R,class T,class T1,class T2>XDelegates(T*t,R (T::*fun)(T1,T2))
			:XBase(new VDelegate<R,T1,T2>(t,fun))
		{		}
		template<class R,class T,class T1>XDelegates(T*t,R (T::*fun)(T1))
			:XBase(new VDelegate<R,T1>(t,fun))
		{		}
		template<class R,class T>XDelegates(T*t,R (T::*fun)())
			:XBase(new VDelegate<R>(t,fun))
		{		}

		//�Ƚ�
		friend bool operator==(const XDelegates&x1,const XDelegates&x2)
		{
			if(x1.Equals(x2))return true;
			return false;
		}

		//ί��ͬ�����á�
		//��������з���ֵ�������һ����������������շ���ֵ������ָ�룻�ر���������ֵΪ�������ͣ������һ������Ӧ�����������գ�ָ�򷵻����õ�ָ�룩��ָ��
		//�������nullptr���򲻽��ܷ���ֵ
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8,class X9>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6,X7 const& x7,X8 const& x8,X9* const& pResult)
		{
			//���ھŸ������ĵ��ñ����з���ֵ���Һ�����������Ϊ8
#ifdef _DEBUG
			if(!CanReturnValue() || GetParametersCount()!=8)IDelegate::ShowParamertersCountError(GetParametersCount());
			int i= GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7,X8>(9),1);
			if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X9>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}
#endif
			return Pointer()->Invoke(&x1,&x2,&x3,&x4,&x5,&x6,&x7,&x8,*(void**)&pResult);
		}
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6,X7 const& x7,X8 const& x8)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 8:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7,X8>(9),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 7:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7>(8),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X8>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==8)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,(void*)&x8,NULL);
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,*(void**)&x8);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,(void*)&x8);
		}
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6,X7 const& x7)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 7:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7>(8),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 6:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6>(7),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X7>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==7)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,NULL);
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,*(void**)&x7);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7);
		}
		template<class X1,class X2,class X3,class X4,class X5,class X6>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 6:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6>(7),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 5:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5>(6),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X6>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==6)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,NULL);
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,*(void**)&x6);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6);
		}
		template<class X1,class X2,class X3,class X4,class X5>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 5:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5>(6),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 4:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4>(5),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X5>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==5)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,NULL);
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,*(void**)&x5);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5);
		}
		template<class X1,class X2,class X3,class X4>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 4:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4>(5),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 3:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3>(4),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X4>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==4)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,NULL);
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,*(void**)&x4);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4);
		}
		template<class X1,class X2,class X3>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 3:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3>(4),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 2:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2>(3),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X3>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==3)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,NULL);
				return Pointer()->Invoke((void*)&x1,(void*)&x2,*(void**)&x3);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3);
		}
		template<class X1,class X2>void* Invoke(X1 const& x1,X2 const& x2)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 2:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2>(3),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 1:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1>(2),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X2>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==2)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,NULL);
				return Pointer()->Invoke((void*)&x1,*(void**)&x2);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2);
		}
		template<class X1>void* Invoke(X1 const& x1)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 1:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1>(2),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 0:{if(Pointer()->GetParameterType(0)!=XTypes(new Types<X1>()).GetPointedType()){IDelegate::ShowParamertersTypeError(0);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==1)
					return Pointer()->Invoke((void*)&x1,NULL);
				return Pointer()->Invoke(*(void**)&x1);
			}
			else
				return Pointer()->Invoke((void*)&x1);
		}
		void* Invoke()
		{
			if(GetParametersCount()!=0){IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;}
			if(CanReturnValue())
				return Pointer()->Invoke(NULL);
			else
				return Pointer()->Invoke();
		}

		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8,class X9>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6,X7 const& x7,X8 const& x8,X9* const& pResult)
		{
			//���ھŸ������ĵ��ñ����з���ֵ���Һ�����������Ϊ8
#ifdef _DEBUG
			if(!CanReturnValue() || GetParametersCount()!=8)IDelegate::ShowParamertersCountError(GetParametersCount());
			int i= GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7,X8>(9),1);
			if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X9>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}
#endif
			return Pointer()->BeginInvoke(&x1,&x2,&x3,&x4,&x5,&x6,&x7,&x8,*(void**)&pResult);
		}
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6,X7 const& x7,X8 const& x8)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 8:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7,X8>(9),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 7:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7>(8),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X8>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==8)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,(void*)&x8,NULL);
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,*(void**)&x8);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,(void*)&x8);
		}
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6,X7 const& x7)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 7:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7>(8),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 6:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6>(7),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X7>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==7)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,NULL);
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,*(void**)&x7);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7);
		}
		template<class X1,class X2,class X3,class X4,class X5,class X6>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 6:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6>(7),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 5:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5>(6),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X6>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==6)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,NULL);
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,*(void**)&x6);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6);
		}
		template<class X1,class X2,class X3,class X4,class X5>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 5:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5>(6),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 4:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4>(5),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X5>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==5)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,NULL);
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,*(void**)&x5);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5);
		}
		template<class X1,class X2,class X3,class X4>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 4:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4>(5),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 3:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3>(4),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X4>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==4)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,NULL);
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,*(void**)&x4);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4);
		}
		template<class X1,class X2,class X3>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 3:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3>(4),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 2:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2>(3),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X3>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==3)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,NULL);
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,*(void**)&x3);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3);
		}
		template<class X1,class X2>DWORD BeginInvoke(X1 const& x1,X2 const& x2)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 2:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2>(3),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 1:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1>(2),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X2>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==2)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,NULL);
				return Pointer()->BeginInvoke((void*)&x1,*(void**)&x2);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2);
		}
		template<class X1>DWORD BeginInvoke(X1 const& x1)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 1:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1>(2),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 0:{if(Pointer()->GetParameterType(0)!=XTypes(new Types<X1>()).GetPointedType()){IDelegate::ShowParamertersTypeError(0);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==1)
					return Pointer()->BeginInvoke((void*)&x1,NULL);
				return Pointer()->BeginInvoke(*(void**)&x1);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1);
		}
		DWORD BeginInvoke()
		{
			if(GetParametersCount()!=0){IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;}
			if(CanReturnValue())
				return Pointer()->BeginInvoke(NULL);
			else
				return Pointer()->BeginInvoke();
		}

		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8,class X9>void* operator()(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& x6,const X7& x7,const X8& x8,X9* pResult){return Invoke(x1,x2,x3,x4,x5,x6,x7,x8,pResult);}
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8>void* operator()(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& x6,const X7& x7,const X8& pResult){return Invoke(x1,x2,x3,x4,x5,x6,x7,pResult);}
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7>void* operator()(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& x6,const X7& pResult){return Invoke(x1,x2,x3,x4,x5,x6,pResult);}
		template<class X1,class X2,class X3,class X4,class X5,class X6>void* operator()(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& pResult){return Invoke(x1,x2,x3,x4,x5,pResult);}
		template<class X1,class X2,class X3,class X4,class X5>void* operator()(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& pResult){return Invoke(x1,x2,x3,x4,pResult);}
		template<class X1,class X2,class X3,class X4>void* operator()(const X1& x1,const X2& x2,const X3& x3,const X4& pResult){return Invoke(x1,x2,x3,pResult);}
		template<class X1,class X2,class X3>void* operator()(const X1& x1,const X2& x2,const X3& pResult){return Invoke(x1,x2,pResult);}
		template<class X1,class X2>void* operator()(const X1& x1,const X2& pResult){return Invoke(x1,pResult);}
		template<class X1>void* operator()(const X1& pResult){return Invoke(pResult);}
		void* operator()(){return Invoke();}

		XDelegates& operator+=(const XDelegates&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegates*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void>*)Pointer())+=*((VDelegate<void>*)x.Pointer());
			return *this;
		}
		XDelegates& operator-=(const XDelegates&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegates*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void>*)Pointer())-=*((VDelegate<void>*)x.Pointer());
			return *this;
		}

		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8>XActions MakeAction(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& x6,const X7& x7,const X8& x8)const;
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7>XActions MakeAction(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& x6,const X7& x7)const;
		template<class X1,class X2,class X3,class X4,class X5,class X6>XActions MakeAction(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& x6)const;
		template<class X1,class X2,class X3,class X4,class X5>XActions MakeAction(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5)const;
		template<class X1,class X2,class X3,class X4>XActions MakeAction(const X1& x1,const X2& x2,const X3& x3,const X4& x4)const;
		template<class X1,class X2,class X3>XActions MakeAction(const X1& x1,const X2& x2,const X3& x3)const;
		template<class X1,class X2>XActions MakeAction(const X1& x1,const X2& x2)const;
		template<class X1>XActions MakeAction(const X1& x1)const;
		XActions MakeAction()const;
	};
	//��ʾһ������������
	class XActions:public XBase
	{
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>friend class XAction;
	public:
		//����ͨ�÷���
		XBaseIRTypeMethods_H(XActions,IDelegate);
		//��ʵ������ָ�빹��
		XActions(IDelegate*p):XBase(p){		}
		//�Ƚϣ�����Equals()
		bool operator==(const XActions& x)const{return Equals(x);}
		//ͬ��ִ�ж���
		void Do();
		//�첽ִ�ж���,����ִ�е��߳�ID
		DWORD DoSync();
		//��ȡ����ֵָ��
		template<class T>T GetReturnValue()const{return *(ParameterStore<T>*)Pointer()->GetReturnValuePointer();}
		//��ȡ����������id
		XTypes GetParameterType(int index)const{return Pointer()->GetParameterType(index);}
		//��ȡί�в�������
		int GetParametersCount()const{return Pointer()->GetParametersCount();}
		//���ز������ͼ�����
		TypesCheckingObject GetTypesChecking()const{return Pointer()->GetTypesChecking();}
		//��ת
		void Reverse(){return Pointer()->Reverse();}
		//�з���ֵ
		bool CanReturnValue()const{return Pointer()->CanReturnValue();}
		//��ĳ����������Ϊĳ��ֵ
		template<class T>void SetParameter(int index,T& t)
		{
			if(Pointer()->GetParameterType()!=XTypes(new Types<T>))throw XException(E_INVALIDARG);
			ParameterStore<T>::PointerToReference(Pointer()->GetParameterPointer(index))=t;
		}
		//��ȡĳ��������ֵ
		template<class T>T GetParameter(int index)
		{
			if(Pointer()->GetParameterType()!=XTypes(new Types<T>))throw XException(E_INVALIDARG);
			return ParameterStore<T>::PointerToReference(Pointer()->GetParameterPointer(index));
		}
		//��ȡί��
		XDelegates GetDelegate()const{return Pointer();}
		//��ȡί�и���
		XDelegates MakeDelegate()const;
		//���������
		XActions MakeCopy()const{return (IDelegate*)Pointer()->NewCopy();}

		//��XAction���ù���
		template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>XActions(const XAction<T1,T2,T3,T4,T5,T6,T7,T8,T9>&t):XBase(t){}
		//��VAction���ù���
		template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>XActions(const VAction<T1,T2,T3,T4,T5,T6,T7,T8,T9>&t):XBase(t.NewCopy()){}
		//�ɺ���ֱ�ӹ���

		//__cdecl
#ifdef CANUSECDECL
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>XActions(R (__cdecl*fun)(T1,T2,T3,T4,T5,T6,T7,T8),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>XActions(R (__cdecl*fun)(T1,T2,T3,T4,T5,T6,T7),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7>(fun,t1,t2,t3,t4,t5,t6,t7)){}
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6>XActions(R (__cdecl*fun)(T1,T2,T3,T4,T5,T6),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6>(fun,t1,t2,t3,t4,t5,t6)){}
		template<class R,class T1,class T2,class T3,class T4,class T5>XActions(R (__cdecl*fun)(T1,T2,T3,T4,T5),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<R,T1,T2,T3,T4,T5>(fun,t1,t2,t3,t4,t5)){}
		template<class R,class T1,class T2,class T3,class T4>XActions(R (__cdecl*fun)(T1,T2,T3,T4),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<R,T1,T2,T3,T4>(fun,t1,t2,t3,t4)){}
		template<class R,class T1,class T2,class T3>XActions(R (__cdecl*fun)(T1,T2,T3),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<R,T1,T2,T3>(fun,t1,t2,t3)){}
		template<class R,class T1,class T2>XActions(R (__cdecl*fun)(T1,T2),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<R,T1,T2>(fun,t1,t2)){}
		template<class R,class T1>XActions(R (__cdecl*fun)(T1),typename ParameterStore<T1>::RC t1)
			:XBase(new VAction<R,T1>(fun,t1)){}
		template<class R>XActions(R (__cdecl*fun)())
			:XBase(new VAction<R>(fun)){}
#endif
		//__stdcall
#ifdef CANUSESTDCALL
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>XActions(R (__stdcall*fun)(T1,T2,T3,T4,T5,T6,T7,T8),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>XActions(R (__stdcall*fun)(T1,T2,T3,T4,T5,T6,T7),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7>(fun,t1,t2,t3,t4,t5,t6,t7)){}
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6>XActions(R (__stdcall*fun)(T1,T2,T3,T4,T5,T6),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6>(fun,t1,t2,t3,t4,t5,t6)){}
		template<class R,class T1,class T2,class T3,class T4,class T5>XActions(R (__stdcall*fun)(T1,T2,T3,T4,T5),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<R,T1,T2,T3,T4,T5>(fun,t1,t2,t3,t4,t5)){}
		template<class R,class T1,class T2,class T3,class T4>XActions(R (__stdcall*fun)(T1,T2,T3,T4),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<R,T1,T2,T3,T4>(fun,t1,t2,t3,t4)){}
		template<class R,class T1,class T2,class T3>XActions(R (__stdcall*fun)(T1,T2,T3),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<R,T1,T2,T3>(fun,t1,t2,t3)){}
		template<class R,class T1,class T2>XActions(R (__stdcall*fun)(T1,T2),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<R,T1,T2>(fun,t1,t2)){}
		template<class R,class T1>XActions(R (__stdcall*fun)(T1),typename ParameterStore<T1>::RC t1)
			:XBase(new VAction<R,T1>(fun,t1)){}
		template<class R>XActions(R (__stdcall*fun)())
			:XBase(new VAction<R>(fun)){}
#endif
		//fastcall
#ifdef CANUSEFASTCALL
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>XActions(R (__fastcall*fun)(T1,T2,T3,T4,T5,T6,T7,T8),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>XActions(R (__fastcall*fun)(T1,T2,T3,T4,T5,T6,T7),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7>(fun,t1,t2,t3,t4,t5,t6,t7)){}
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6>XActions(R (__fastcall*fun)(T1,T2,T3,T4,T5,T6),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6>(fun,t1,t2,t3,t4,t5,t6)){}
		template<class R,class T1,class T2,class T3,class T4,class T5>XActions(R (__fastcall*fun)(T1,T2,T3,T4,T5),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<R,T1,T2,T3,T4,T5>(fun,t1,t2,t3,t4,t5)){}
		template<class R,class T1,class T2,class T3,class T4>XActions(R (__fastcall*fun)(T1,T2,T3,T4),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<R,T1,T2,T3,T4>(fun,t1,t2,t3,t4)){}
		template<class R,class T1,class T2,class T3>XActions(R (__fastcall*fun)(T1,T2,T3),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<R,T1,T2,T3>(fun,t1,t2,t3)){}
		template<class R,class T1,class T2>XActions(R (__fastcall*fun)(T1,T2),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<R,T1,T2>(fun,t1,t2)){}
		template<class R,class T1>XActions(R (__fastcall*fun)(T1),typename ParameterStore<T1>::RC t1)
			:XBase(new VAction<R,T1>(fun,t1)){}
		template<class R>XActions(R (__fastcall*fun)())
			:XBase(new VAction<R>(fun)){}
#endif
		//__thiscall
		template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>XActions(T* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>(p,fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
		template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7>XActions(T* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7>(p,fun,t1,t2,t3,t4,t5,t6,t7)){}
		template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6>XActions(T* p,R(T::*fun)(T1,T2,T3,T4,T5,T6),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6>(p,fun,t1,t2,t3,t4,t5,t6)){}
		template<class R,class T,class T1,class T2,class T3,class T4,class T5>XActions(T* p,R(T::*fun)(T1,T2,T3,T4,T5),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<R,T1,T2,T3,T4,T5>(p,fun,t1,t2,t3,t4,t5)){}
		template<class R,class T,class T1,class T2,class T3,class T4>XActions(T* p,R(T::*fun)(T1,T2,T3,T4),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<R,T1,T2,T3,T4>(p,fun,t1,t2,t3,t4)){}
		template<class R,class T,class T1,class T2,class T3>XActions(T* p,R(T::*fun)(T1,T2,T3),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<R,T1,T2,T3>(p,fun,t1,t2,t3)){}
		template<class R,class T,class T1,class T2>XActions(T* p,R(T::*fun)(T1,T2),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<R,T1,T2>(p,fun,t1,t2)){}
		template<class R,class T,class T1>XActions(T* p,R(T::*fun)(T1),typename ParameterStore<T1>::RC t1)
			:XBase(new VAction<R,T1>(p,fun,t1)){}
		template<class R,class T>XActions(T* p,R(T::*fun)())
			:XBase(new VAction<R>(p,fun)){}


		//ί��ͬ�����á�
		//��������з���ֵ�������һ����������������շ���ֵ������ָ�룻�ر���������ֵΪ�������ͣ������һ������Ӧ�����������գ�ָ�򷵻����õ�ָ�룩��ָ��
		//�������nullptr���򲻽��ܷ���ֵ
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8,class X9>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6,X7 const& x7,X8 const& x8,X9* const& pResult)
		{
			//���ھŸ������ĵ��ñ����з���ֵ���Һ�����������Ϊ8
#ifdef _DEBUG
			if(!CanReturnValue() || GetParametersCount()!=8)IDelegate::ShowParamertersCountError(GetParametersCount());
			int i= GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7,X8>(9),1);
			if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X9>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}
#endif
			return Pointer()->Invoke(&x1,&x2,&x3,&x4,&x5,&x6,&x7,&x8,*(void**)&pResult);
		}
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6,X7 const& x7,X8 const& x8)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 8:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7,X8>(9),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 7:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7>(8),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X8>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==8)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,(void*)&x8,NULL);
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,*(void**)&x8);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,(void*)&x8);
		}
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6,X7 const& x7)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 7:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7>(8),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 6:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6>(7),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X7>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==7)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,NULL);
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,*(void**)&x7);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7);
		}
		template<class X1,class X2,class X3,class X4,class X5,class X6>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 6:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6>(7),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 5:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5>(6),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X6>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==6)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,NULL);
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,*(void**)&x6);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6);
		}
		template<class X1,class X2,class X3,class X4,class X5>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 5:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5>(6),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 4:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4>(5),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X5>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==5)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,NULL);
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,*(void**)&x5);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5);
		}
		template<class X1,class X2,class X3,class X4>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 4:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4>(5),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 3:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3>(4),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X4>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==4)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,NULL);
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,*(void**)&x4);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4);
		}
		template<class X1,class X2,class X3>void* Invoke(X1 const& x1,X2 const& x2,X3 const& x3)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 3:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3>(4),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 2:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2>(3),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X3>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==3)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3,NULL);
				return Pointer()->Invoke((void*)&x1,(void*)&x2,*(void**)&x3);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2,(void*)&x3);
		}
		template<class X1,class X2>void* Invoke(X1 const& x1,X2 const& x2)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 2:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2>(3),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 1:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1>(2),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X2>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==2)
					return Pointer()->Invoke((void*)&x1,(void*)&x2,NULL);
				return Pointer()->Invoke((void*)&x1,*(void**)&x2);
			}
			else
				return Pointer()->Invoke((void*)&x1,(void*)&x2);
		}
		template<class X1>void* Invoke(X1 const& x1)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 1:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1>(2),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 0:{if(Pointer()->GetParameterType(0)!=XTypes(new Types<X1>()).GetPointedType()){IDelegate::ShowParamertersTypeError(0);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==1)
					return Pointer()->Invoke((void*)&x1,NULL);
				return Pointer()->Invoke(*(void**)&x1);
			}
			else
				return Pointer()->Invoke((void*)&x1);
		}
		void* Invoke()
		{
			if(GetParametersCount()!=0){IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;}
			if(CanReturnValue())
				return Pointer()->Invoke(NULL);
			else
				return Pointer()->Invoke();
		}

		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8,class X9>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6,X7 const& x7,X8 const& x8,X9* const& pResult)
		{
			//���ھŸ������ĵ��ñ����з���ֵ���Һ�����������Ϊ8
#ifdef _DEBUG
			if(!CanReturnValue() || GetParametersCount()!=8)IDelegate::ShowParamertersCountError(GetParametersCount());
			int i= GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7,X8>(9),1);
			if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X9>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}
#endif
			return Pointer()->BeginInvoke(&x1,&x2,&x3,&x4,&x5,&x6,&x7,&x8,*(void**)&pResult);
		}
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6,X7 const& x7,X8 const& x8)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 8:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7,X8>(9),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 7:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7>(8),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X8>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==8)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,(void*)&x8,NULL);
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,*(void**)&x8);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,(void*)&x8);
		}
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6,X7 const& x7)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 7:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7>(8),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 6:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6>(7),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X7>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==7)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7,NULL);
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,*(void**)&x7);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,(void*)&x7);
		}
		template<class X1,class X2,class X3,class X4,class X5,class X6>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5,X6 const& x6)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 6:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6>(7),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 5:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5>(6),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X6>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==6)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6,NULL);
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,*(void**)&x6);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,(void*)&x6);
		}
		template<class X1,class X2,class X3,class X4,class X5>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4,X5 const& x5)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 5:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5>(6),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 4:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4>(5),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X5>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==5)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5,NULL);
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,*(void**)&x5);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,(void*)&x5);
		}
		template<class X1,class X2,class X3,class X4>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3,X4 const& x4)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 4:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4>(5),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 3:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3>(4),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X4>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==4)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4,NULL);
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,*(void**)&x4);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,(void*)&x4);
		}
		template<class X1,class X2,class X3>DWORD BeginInvoke(X1 const& x1,X2 const& x2,X3 const& x3)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 3:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3>(4),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 2:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2>(3),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X3>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==3)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3,NULL);
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,*(void**)&x3);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,(void*)&x3);
		}
		template<class X1,class X2>DWORD BeginInvoke(X1 const& x1,X2 const& x2)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 2:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2>(3),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 1:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1>(2),1);if(i>=0 || Pointer()->GetParameterType(0)!=XTypes(new Types<X2>()).GetPointedType()){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==2)
					return Pointer()->BeginInvoke((void*)&x1,(void*)&x2,NULL);
				return Pointer()->BeginInvoke((void*)&x1,*(void**)&x2);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1,(void*)&x2);
		}
		template<class X1>DWORD BeginInvoke(X1 const& x1)
		{
#ifdef _DEBUG
			switch(GetParametersCount())
			{
			case 1:{int i=GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1>(2),1);if(i>=0){IDelegate::ShowParamertersTypeError(i);return NULL;}}
				break;
			case 0:{if(Pointer()->GetParameterType(0)!=XTypes(new Types<X1>()).GetPointedType()){IDelegate::ShowParamertersTypeError(0);return NULL;}}
				break;
			default:IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;
			}
#endif
			if(CanReturnValue())
			{
				if(GetParametersCount()==1)
					return Pointer()->BeginInvoke((void*)&x1,NULL);
				return Pointer()->BeginInvoke(*(void**)&x1);
			}
			else
				return Pointer()->BeginInvoke((void*)&x1);
		}
		DWORD BeginInvoke()
		{
			if(GetParametersCount()!=0){IDelegate::ShowParamertersCountError(GetParametersCount());return NULL;}
			if(CanReturnValue())
				return Pointer()->BeginInvoke(NULL);
			else
				return Pointer()->BeginInvoke();
		}

		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8,class X9>void* operator()(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& x6,const X7& x7,const X8& x8,X9* pResult){return Invoke(x1,x2,x3,x4,x5,x6,x7,x8,pResult);}
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8>void* operator()(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& x6,const X7& x7,const X8& pResult){return Invoke(x1,x2,x3,x4,x5,x6,x7,pResult);}
		template<class X1,class X2,class X3,class X4,class X5,class X6,class X7>void* operator()(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& x6,const X7& pResult){return Invoke(x1,x2,x3,x4,x5,x6,pResult);}
		template<class X1,class X2,class X3,class X4,class X5,class X6>void* operator()(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& pResult){return Invoke(x1,x2,x3,x4,x5,pResult);}
		template<class X1,class X2,class X3,class X4,class X5>void* operator()(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& pResult){return Invoke(x1,x2,x3,x4,pResult);}
		template<class X1,class X2,class X3,class X4>void* operator()(const X1& x1,const X2& x2,const X3& x3,const X4& pResult){return Invoke(x1,x2,x3,pResult);}
		template<class X1,class X2,class X3>void* operator()(const X1& x1,const X2& x2,const X3& pResult){return Invoke(x1,x2,pResult);}
		template<class X1,class X2>void* operator()(const X1& x1,const X2& pResult){return Invoke(x1,pResult);}
		template<class X1>void* operator()(const X1& pResult){return Invoke(pResult);}
		void* operator()(){return Invoke();}

		XActions& operator+=(const XDelegates&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XActions*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void>*)Pointer())+=*((VDelegate<void>*)x.Pointer());
			return *this;
		}
		XActions& operator-=(const XDelegates&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XActions*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void>*)Pointer())-=*((VDelegate<void>*)x.Pointer());
			return *this;
		}

	};



#define XDelegateIRMethods()\
	/*��ȡ����������id*/\
	XTypes GetParameterType(int index)const{return Pointer()->GetParameterType(index);}\
	/*��ȡί�в�������*/\
	int GetParametersCount()const{return Pointer()->GetParametersCount();}\
	/*���ز������ͼ�����*/\
	TypesCheckingObject GetTypesChecking()const{return Pointer()->GetTypesChecking();}\
	/*�з���ֵ*/\
	bool CanReturnValue()const{return Pointer()->CanReturnValue();}\
	/*��Delegates��ʼ��*/\
	XDelegate(const XDelegates& d){*this=(IDelegate*)d.pObject;	}\
	/*��ת*/\
	void Reverse(){return Pointer()->Reverse();}

	//��ʾһ������ί�е�����
	template<class R,class T1=void,class T2=void,class T3=void,class T4=void,class T5=void,class T6=void,class T7=void,class T8=void>class XDelegate:public XBase
	{
		friend XAction<R,T1,T2,T3,T4,T5,T6,T7,T8>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2,T3,T4,T5,T6,T7,T8)const):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>(t,fun)){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2,T3,T4,T5,T6,T7,T8)):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>(t,fun)){}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>::PCdeclFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>::PStdCallFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>::PFastCallFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun)){}
#endif
		//��ί�е��Զ�ת��
		operator VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,T8>(9)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer();
		}

		XAction<R,T1,T2,T3,T4,T5,T6,T7,T8> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2,ParameterStore<T3>t3,ParameterStore<T4>t4,ParameterStore<T5>t5,ParameterStore<T6>t6,ParameterStore<T7>t7,ParameterStore<T8>t8);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,T8>(9)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��8���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,T8>(9);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return;}
#endif
			Pointer()->Invoke((void*)&t1,(void*)&t2,(void*)&t3,(void*)&t4,(void*)&t5,(void*)&t6,(void*)&t7,(void*)&t8,*(void**)&pr);
			return;
		}
		//ͬ�����ã�ί��8���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2	,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,T8>(9);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,(typename ParameterPass<T6>::R)t6,(typename ParameterPass<T7>::R)t7,(typename ParameterPass<T8>::R)t8);
		}

		//�첽���ã�ί��1���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,T8>(9);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;}
#endif
			return Pointer()->BeginInvoke((void*)&t1,(void*)&t2,(void*)&t3,(void*)&t4,(void*)&t5,(void*)&t6,(void*)&t7,(void*)&t8,*(void**)&pr);
		}
		//�첽���ã�ί��1���������з���ֵ��������ֱֵ�ӷ��أ�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2	,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,T8>(9);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,(typename ParameterPass<T6>::R)t6,(typename ParameterPass<T7>::R)t7,(typename ParameterPass<T8>::R)t8,NULL);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer())+=*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer())-=*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��8���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8,typename ParameterPass<typename Types<R>::Normal*>::RC pr){return Invoke(t1,t2,t3,t4,t5,t6,t7,t8,pr);}
		//ͬ�����ã�ί��8���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8){return Invoke(t1,t2,t3,t4,t5,t6,t7,t8);}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>class XDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>:public XBase
	{
		friend XAction<R,T1,T2,T3,T4,T5,T6,T7,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2,T3,T4,T5,T6,T7)const):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>(t,fun)){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2,T3,T4,T5,T6,T7)):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7>(8)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>::PCdeclFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>::PStdCallFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>::PFastCallFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>(fun)){}
#endif

		XAction<R,T1,T2,T3,T4,T5,T6,T7,void> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2,ParameterStore<T3>t3,ParameterStore<T4>t4,ParameterStore<T5>t5,ParameterStore<T6>t6,ParameterStore<T7>t7);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7>(8)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��7���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7>(8);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return;}
#endif
			Pointer()->Invoke((void*)&t1,(void*)&t2,(void*)&t3,(void*)&t4,(void*)&t5,(void*)&t6,(void*)&t7,*(void**)&pr);
			return;
		}
		//ͬ�����ã�ί��7���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7>(8);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<R,T1,T2,T3,T4,T5,T6,T7>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,(typename ParameterPass<T6>::R)t6,(typename ParameterPass<T7>::R)t7);
		}

		//�첽���ã�ί��7���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7>(8);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;}
#endif
			return Pointer()->BeginInvoke((void*)&t1,(void*)&t2,(void*)&t3,(void*)&t4,(void*)&t5,(void*)&t6,(void*)&t7,*(void**)&pr);
		}
		//�첽���ã�ί��7���������з���ֵ��������ֱֵ�ӷ��أ�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7>(8);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<R,T1,T2,T3,T4,T5,T6,T7>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,(typename ParameterPass<T6>::R)t6,(typename ParameterPass<T7>::R)t7,NULL);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7>*)Pointer())+=*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7>*)Pointer())-=*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��7���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return Invoke(t1,t2,t3,t4,t5,t6,t7,pr);}
		//ͬ�����ã�ί��7���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7)
		{return Invoke(t1,t2,t3,t4,t5,t6,t7);}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6>class XDelegate<R,T1,T2,T3,T4,T5,T6,void,void>:public XBase
	{
		friend XAction<R,T1,T2,T3,T4,T5,T6,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2,T3,T4,T5,T6)const):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2,T3,T4,T5,T6)):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6>(7)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>::PCdeclFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>::PStdCallFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>::PFastCallFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>(fun)){}
#endif

		XAction<R,T1,T2,T3,T4,T5,T6,void,void> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2,ParameterStore<T3>t3,ParameterStore<T4>t4,ParameterStore<T5>t5,ParameterStore<T6>t6);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6>(7)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��6���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6>(7);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return;}
#endif
			Pointer()->Invoke((void*)&t1,(void*)&t2,(void*)&t3,(void*)&t4,(void*)&t5,(void*)&t6,*(void**)&pr);
			return;
		}
		//ͬ�����ã�ί��6���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6>(7);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<R,T1,T2,T3,T4,T5,T6>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,(typename ParameterPass<T6>::R)t6);
		}

		//�첽���ã�ί��6���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6>(7);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;}
#endif
			return Pointer()->BeginInvoke((void*)&t1,(void*)&t2,(void*)&t3,(void*)&t4,(void*)&t5,(void*)&t6,*(void**)&pr);
		}
		//�첽���ã�ί��6���������з���ֵ��������ֱֵ�ӷ��أ�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6>(7);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<R,T1,T2,T3,T4,T5,T6>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,(typename ParameterPass<T6>::R)t6,NULL);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5,T6>*)Pointer())+=*((VDelegate<R,T1,T2,T3,T4,T5,T6>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5,T6>*)Pointer())-=*((VDelegate<R,T1,T2,T3,T4,T5,T6>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��6���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return Invoke(t1,t2,t3,t4,t5,t6,pr);}
		//ͬ�����ã�ί��6���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6)
		{return Invoke(t1,t2,t3,t4,t5,t6);}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5>class XDelegate<R,T1,T2,T3,T4,T5,void,void,void>:public XBase
	{
		friend XAction<R,T1,T2,T3,T4,T5,void,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<R,T1,T2,T3,T4,T5,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2,T3,T4,T5)const):XBase(new VDelegate<R,T1,T2,T3,T4,T5,void,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2,T3,T4,T5)):XBase(new VDelegate<R,T1,T2,T3,T4,T5,void,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<R,T1,T2,T3,T4,T5,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5>(6)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<R,T1,T2,T3,T4,T5,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,T5,void,void,void>::PCdeclFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,T5,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,T5,void,void,void>::PStdCallFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,T5,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,T5,void,void,void>::PFastCallFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,T5,void,void,void>(fun)){}
#endif

		XAction<R,T1,T2,T3,T4,T5,void,void,void> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2,ParameterStore<T3>t3,ParameterStore<T4>t4,ParameterStore<T5>t5);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5>(6)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��5���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5>(6);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return;}
#endif
			Pointer()->Invoke((void*)&t1,(void*)&t2,(void*)&t3,(void*)&t4,(void*)&t5,*(void**)&pr);
			return;
		}
		//ͬ�����ã�ί��5���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5>(6);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<R,T1,T2,T3,T4,T5>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5);
		}

		//�첽���ã�ί��5���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5>(6);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;}
#endif
			return Pointer()->BeginInvoke((void*)&t1,(void*)&t2,(void*)&t3,(void*)&t4,(void*)&t5,*(void**)&pr);
		}
		//�첽���ã�ί��5���������з���ֵ��������ֱֵ�ӷ��أ�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5>(6);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<R,T1,T2,T3,T4,T5>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,NULL);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			*((VDelegate<R,T1,T2,T3,T4,T5>*)Pointer())+=*((VDelegate<R,T1,T2,T3,T4,T5>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5>*)Pointer())-=*((VDelegate<R,T1,T2,T3,T4,T5>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��5���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return Invoke(t1,t2,t3,t4,t5,pr);}
		//ͬ�����ã�ί��5���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5)
		{return Invoke(t1,t2,t3,t4,t5);}
	};
	template<class R,class T1,class T2,class T3,class T4>class XDelegate<R,T1,T2,T3,T4,void,void,void,void>:public XBase
	{
		friend XAction<R,T1,T2,T3,T4,void,void,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<R,T1,T2,T3,T4,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2,T3,T4)const):XBase(new VDelegate<R,T1,T2,T3,T4,void,void,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2,T3,T4)):XBase(new VDelegate<R,T1,T2,T3,T4,void,void,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<R,T1,T2,T3,T4,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4>(5)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<R,T1,T2,T3,T4,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,void,void,void,void>::PCdeclFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,void,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,void,void,void,void>::PStdCallFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,void,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<R,T1,T2,T3,T4,void,void,void,void>::PFastCallFun fun):XBase(new VDelegate<R,T1,T2,T3,T4,void,void,void,void>(fun)){}
#endif

		XAction<R,T1,T2,T3,T4,void,void,void,void> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2,ParameterStore<T3>t3,ParameterStore<T4>t4);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4>(5)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��4���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4>(5);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return;}
#endif
			Pointer()->Invoke((void*)&t1,(void*)&t2,(void*)&t3,(void*)&t4,*(void**)&pr);
			return;
		}
		//ͬ�����ã�ί��4���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4>(5);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<R,T1,T2,T3,T4>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4);
		}

		//�첽���ã�ί��4���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4>(5);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;}
#endif
			return Pointer()->BeginInvoke((void*)&t1,(void*)&t2,(void*)&t3,(void*)&t4,*(void**)&pr);
		}
		//�첽���ã�ί��4���������з���ֵ��������ֱֵ�ӷ��أ�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3,T4>(5);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<R,T1,T2,T3,T4>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,NULL);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4>*)Pointer())+=*((VDelegate<R,T1,T2,T3,T4>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			*((VDelegate<R,T1,T2,T3,T4>*)Pointer())-=*((VDelegate<R,T1,T2,T3,T4>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��4���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return Invoke(t1,t2,t3,t4,pr);}
		//ͬ�����ã�ί��4���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4)
		{return Invoke(t1,t2,t3,t4);}
	};
	template<class R,class T1,class T2,class T3>class XDelegate<R,T1,T2,T3,void,void,void,void,void>:public XBase
	{
		friend XAction<R,T1,T2,T3,void,void,void,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<R,T1,T2,T3,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2,T3)const):XBase(new VDelegate<R,T1,T2,T3,void,void,void,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2,T3)):XBase(new VDelegate<R,T1,T2,T3,void,void,void,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<R,T1,T2,T3,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2,T3>(4)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<R,T1,T2,T3,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<R,T1,T2,T3,void,void,void,void,void>::PCdeclFun fun):XBase(new VDelegate<R,T1,T2,T3,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<R,T1,T2,T3,void,void,void,void,void>::PStdCallFun fun):XBase(new VDelegate<R,T1,T2,T3,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<R,T1,T2,T3,void,void,void,void,void>::PFastCallFun fun):XBase(new VDelegate<R,T1,T2,T3,void,void,void,void,void>(fun)){}
#endif

		XAction<R,T1,T2,T3,void,void,void,void,void> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2,ParameterStore<T3>t3);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2,T3>(4)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��3���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3>(4);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return;}
#endif
			Pointer()->Invoke((void*)&t1,(void*)&t2,(void*)&t3,*(void**)&pr);
			return;
		}
		//ͬ�����ã�ί��3���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3>(4);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<R,T1,T2,T3>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3);
		}

		//�첽���ã�ί��3���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3>(4);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;}
#endif
			return Pointer()->BeginInvoke((void*)&t1,(void*)&t2,(void*)&t3,*(void**)&pr);
		}
		//�첽���ã�ί��3���������з���ֵ��������ֱֵ�ӷ��أ�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2,T3>(4);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<R,T1,T2,T3>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,NULL);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3>*)Pointer())+=*((VDelegate<R,T1,T2,T3>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3>*)Pointer())-=*((VDelegate<R,T1,T2,T3>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��3���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return Invoke(t1,t2,t3,pr);}
		//ͬ�����ã�ί��3���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3)
		{return Invoke(t1,t2,t3);}
	};
	template<class R,class T1,class T2>class XDelegate<R,T1,T2,void,void,void,void,void,void>:public XBase
	{
		friend XAction<R,T1,T2,void,void,void,void,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<R,T1,T2,void,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2)const):XBase(new VDelegate<R,T1,T2,void,void,void,void,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1,T2)):XBase(new VDelegate<R,T1,T2,void,void,void,void,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<R,T1,T2,void,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2>(3)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<R,T1,T2,void,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<R,T1,T2,void,void,void,void,void,void>::PCdeclFun fun):XBase(new VDelegate<R,T1,T2,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<R,T1,T2,void,void,void,void,void,void>::PStdCallFun fun):XBase(new VDelegate<R,T1,T2,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<R,T1,T2,void,void,void,void,void,void>::PFastCallFun fun):XBase(new VDelegate<R,T1,T2,void,void,void,void,void,void>(fun)){}
#endif

		XAction<R,T1,T2,void,void,void,void,void,void> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2>(3)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��2���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2>(3);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return;}
#endif
			Pointer()->Invoke((void*)&t1,(void*)&t2,*(void**)&pr);
			return;
		}
		//ͬ�����ã�ί��2���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2>(3);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<R,T1,T2>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2);
		}

		//�첽���ã�ί��2���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2>(3);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;}
#endif
			return Pointer()->BeginInvoke((void*)&t1,(void*)&t2,*(void**)&pr);
		}
		//�첽���ã�ί��2���������з���ֵ��������ֱֵ�ӷ��أ�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1,T2>(3);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<R,T1,T2>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,NULL);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2>*)Pointer())+=*((VDelegate<R,T1,T2>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2>*)Pointer())-=*((VDelegate<R,T1,T2>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��2���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return Invoke(t1,t2,pr);}
		//ͬ�����ã�ί��2���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2)
		{return Invoke(t1,t2);}
	};
	template<class R,class T1>class XDelegate<R,T1,void,void,void,void,void,void,void>:public XBase
	{
		friend XAction<R,T1,void,void,void,void,void,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<R,T1,void,void,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1)const):XBase(new VDelegate<R,T1,void,void,void,void,void,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,R(T::* fun)(T1)):XBase(new VDelegate<R,T1,void,void,void,void,void,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<R,T1,void,void,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1>(2)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<R,T1,void,void,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<R,T1,void,void,void,void,void,void,void>::PCdeclFun fun):XBase(new VDelegate<R,T1,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<R,T1,void,void,void,void,void,void,void>::PStdCallFun fun):XBase(new VDelegate<R,T1,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<R,T1,void,void,void,void,void,void,void>::PFastCallFun fun):XBase(new VDelegate<R,T1,void,void,void,void,void,void,void>(fun)){}
#endif

		XAction<R,T1,void,void,void,void,void,void,void> MakeAction(ParameterStore<T1>t1);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1>(2)!=t)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��1���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1>(2);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return;}
#endif
			Pointer()->Invoke((void*)&t1,*(void**)&pr);
			return;
		}
		//ͬ�����ã�ί��1���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1>(2);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<R,T1>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1);
		}

		//�첽���ã�ί��1���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1>(2);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;}
#endif
			return Pointer()->BeginInvoke((void*)&t1,*(void**)&pr);
		}
		//�첽���ã�ί��1���������з���ֵ��������ֱֵ�ӷ��أ�
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R,T1>(2);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<R,T1>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,NULL);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1>*)Pointer())+=*((VDelegate<R,T1>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1>*)Pointer())-=*((VDelegate<R,T1>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��1���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<typename Types<R>::Normal*>::RC pr){return Invoke(t1,pr);}
		//ͬ�����ã�ί��1���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1){return Invoke(t1);}
	};
	template<class R>class XDelegate<R,void,void,void,void,void,void,void,void>:public XBase
	{
		friend XAction<R,void,void,void,void,void,void,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<R,void,void,void,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,R(T::* fun)()const):XBase(new VDelegate<R,void,void,void,void,void,void,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,R(T::* fun)()):XBase(new VDelegate<R,void,void,void,void,void,void,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<R,void,void,void,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R>(1)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<R,void,void,void,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<R,void,void,void,void,void,void,void,void>::PCdeclFun fun):XBase(new VDelegate<R,void,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<R,void,void,void,void,void,void,void,void>::PStdCallFun fun):XBase(new VDelegate<R,void,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<R,void,void,void,void,void,void,void,void>::PFastCallFun fun):XBase(new VDelegate<R,void,void,void,void,void,void,void,void>(fun)){}
#endif

		XAction<R,void,void,void,void,void,void,void,void> MakeAction();
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R>(1)!=t)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��0���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void Invoke(typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R>(1);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return;}
#endif
			Pointer()->Invoke(*(void**)&pr);
			return;
		}
		//ͬ�����ã�ί��0���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke()
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R>(1);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<R>*)Pointer())->VInvoke();
		}

		//�첽���ã�ί��0���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		DWORD BeginInvoke(typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R>(1);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;}
#endif
			return Pointer()->BeginInvoke(*(void**)&pr);
		}
		//�첽���ã�ί��0���������з���ֵ��������ֱֵ�ӷ��أ�
		DWORD BeginInvoke()
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<R>(1);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<R>*)Pointer())->VBeginInvoke(NULL);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R>*)Pointer())+=*((VDelegate<R>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R>*)Pointer())-=*((VDelegate<R>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��0���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<typename Types<R>::Normal*>::RC pr){return Invoke(pr);}
		//ͬ�����ã�ί��0���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(){return Invoke();}
	};

	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>class XDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>:public XBase
	{
		friend XAction<void,T1,T2,T3,T4,T5,T6,T7,T8>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2,T3,T4,T5,T6,T7,T8)const):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>(t,fun)){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2,T3,T4,T5,T6,T7,T8)):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>(t,fun)){}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>::PCdeclFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>::PStdCallFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>::PFastCallFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>(fun)){}
#endif
		//��ί�е��Զ�ת��
		operator VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7,T8>(9)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer();
		}

		XAction<void,T1,T2,T3,T4,T5,T6,T7,T8> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2,ParameterStore<T3>t3,ParameterStore<T4>t4,ParameterStore<T5>t5,ParameterStore<T6>t6,ParameterStore<T7>t7,ParameterStore<T8>t8);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7,T8>(9)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��8���������޷���ֵ
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2	,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7,T8>(9);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,(typename ParameterPass<T6>::R)t6,(typename ParameterPass<T7>::R)t7,(typename ParameterPass<T8>::R)t8);
		}

		//�첽���ã�ί��1���������޷���ֵ
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2	,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7,T8>(9);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,(typename ParameterPass<T6>::R)t6,(typename ParameterPass<T7>::R)t7,(typename ParameterPass<T8>::R)t8);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer())+=*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer())-=*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��8���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8){return Invoke(t1,t2,t3,t4,t5,t6,t7,t8);}
	};
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7>class XDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>:public XBase
	{
		friend XAction<void,T1,T2,T3,T4,T5,T6,T7,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2,T3,T4,T5,T6,T7)const):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>(t,fun)){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2,T3,T4,T5,T6,T7)):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7>(8)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>::PCdeclFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>::PStdCallFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>::PFastCallFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>(fun)){}
#endif

		XAction<void,T1,T2,T3,T4,T5,T6,T7,void> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2,ParameterStore<T3>t3,ParameterStore<T4>t4,ParameterStore<T5>t5,ParameterStore<T6>t6,ParameterStore<T7>t7);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7>(8)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��7���������޷���ֵ
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7>(8);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<void,T1,T2,T3,T4,T5,T6,T7>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,(typename ParameterPass<T6>::R)t6,(typename ParameterPass<T7>::R)t7);
		}

		//�첽���ã�ί��7���������޷���ֵ
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7>(8);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<void,T1,T2,T3,T4,T5,T6,T7>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,(typename ParameterPass<T6>::R)t6,(typename ParameterPass<T7>::R)t7);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7>*)Pointer())+=*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7>*)Pointer())-=*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��7���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7)
		{return Invoke(t1,t2,t3,t4,t5,t6,t7);}
	};
	template<class T1,class T2,class T3,class T4,class T5,class T6>class XDelegate<void,T1,T2,T3,T4,T5,T6,void,void>:public XBase
	{
		friend XAction<void,T1,T2,T3,T4,T5,T6,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2,T3,T4,T5,T6)const):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2,T3,T4,T5,T6)):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6>(7)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>::PCdeclFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>::PStdCallFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>::PFastCallFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>(fun)){}
#endif

		XAction<void,T1,T2,T3,T4,T5,T6,void,void> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2,ParameterStore<T3>t3,ParameterStore<T4>t4,ParameterStore<T5>t5,ParameterStore<T6>t6);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6>(7)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��6���������޷���ֵ
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6>(7);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<void,T1,T2,T3,T4,T5,T6>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,(typename ParameterPass<T6>::R)t6);
		}

		//�첽���ã�ί��6���������޷���ֵ
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6>(7);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<void,T1,T2,T3,T4,T5,T6>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5,(typename ParameterPass<T6>::R)t6);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5,T6>*)Pointer())+=*((VDelegate<void,T1,T2,T3,T4,T5,T6>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5,T6>*)Pointer())-=*((VDelegate<void,T1,T2,T3,T4,T5,T6>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��6���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6)
		{return Invoke(t1,t2,t3,t4,t5,t6);}
	};
	template<class T1,class T2,class T3,class T4,class T5>class XDelegate<void,T1,T2,T3,T4,T5,void,void,void>:public XBase
	{
		friend XAction<void,T1,T2,T3,T4,T5,void,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<void,T1,T2,T3,T4,T5,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2,T3,T4,T5)const):XBase(new VDelegate<void,T1,T2,T3,T4,T5,void,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2,T3,T4,T5)):XBase(new VDelegate<void,T1,T2,T3,T4,T5,void,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<void,T1,T2,T3,T4,T5,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5>(6)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<void,T1,T2,T3,T4,T5,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,T5,void,void,void>::PCdeclFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,T5,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,T5,void,void,void>::PStdCallFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,T5,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,T5,void,void,void>::PFastCallFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,T5,void,void,void>(fun)){}
#endif

		XAction<void,T1,T2,T3,T4,T5,void,void,void> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2,ParameterStore<T3>t3,ParameterStore<T4>t4,ParameterStore<T5>t5);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5>(6)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��5���������޷���ֵ
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5>(6);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<void,T1,T2,T3,T4,T5>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5);
		}

		//�첽���ã�ί��5���������޷���ֵ
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5>(6);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<void,T1,T2,T3,T4,T5>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4,(typename ParameterPass<T5>::R)t5);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			*((VDelegate<void,T1,T2,T3,T4,T5>*)Pointer())+=*((VDelegate<void,T1,T2,T3,T4,T5>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5>*)Pointer())-=*((VDelegate<void,T1,T2,T3,T4,T5>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��5���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5)
		{return Invoke(t1,t2,t3,t4,t5);}
	};
	template<class T1,class T2,class T3,class T4>class XDelegate<void,T1,T2,T3,T4,void,void,void,void>:public XBase
	{
		friend XAction<void,T1,T2,T3,T4,void,void,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<void,T1,T2,T3,T4,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2,T3,T4)const):XBase(new VDelegate<void,T1,T2,T3,T4,void,void,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2,T3,T4)):XBase(new VDelegate<void,T1,T2,T3,T4,void,void,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<void,T1,T2,T3,T4,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4>(5)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<void,T1,T2,T3,T4,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,void,void,void,void>::PCdeclFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,void,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,void,void,void,void>::PStdCallFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,void,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<void,T1,T2,T3,T4,void,void,void,void>::PFastCallFun fun):XBase(new VDelegate<void,T1,T2,T3,T4,void,void,void,void>(fun)){}
#endif

		XAction<void,T1,T2,T3,T4,void,void,void,void> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2,ParameterStore<T3>t3,ParameterStore<T4>t4);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4>(5)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��4���������޷���ֵ
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2,T3,T4>(5);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<void,T1,T2,T3,T4>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4);
		}

		//�첽���ã�ί��4���������޷���ֵ
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2,T3,T4>(5);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<void,T1,T2,T3,T4>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3,(typename ParameterPass<T4>::R)t4);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4>*)Pointer())+=*((VDelegate<void,T1,T2,T3,T4>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			*((VDelegate<void,T1,T2,T3,T4>*)Pointer())-=*((VDelegate<void,T1,T2,T3,T4>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��4���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4)
		{return Invoke(t1,t2,t3,t4);}
	};
	template<class T1,class T2,class T3>class XDelegate<void,T1,T2,T3,void,void,void,void,void>:public XBase
	{
		friend XAction<void,T1,T2,T3,void,void,void,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<void,T1,T2,T3,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2,T3)const):XBase(new VDelegate<void,T1,T2,T3,void,void,void,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2,T3)):XBase(new VDelegate<void,T1,T2,T3,void,void,void,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<void,T1,T2,T3,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2,T3>(4)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<void,T1,T2,T3,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<void,T1,T2,T3,void,void,void,void,void>::PCdeclFun fun):XBase(new VDelegate<void,T1,T2,T3,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<void,T1,T2,T3,void,void,void,void,void>::PStdCallFun fun):XBase(new VDelegate<void,T1,T2,T3,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<void,T1,T2,T3,void,void,void,void,void>::PFastCallFun fun):XBase(new VDelegate<void,T1,T2,T3,void,void,void,void,void>(fun)){}
#endif

		XAction<void,T1,T2,T3,void,void,void,void,void> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2,ParameterStore<T3>t3);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2,T3>(4)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��3���������޷���ֵ
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2,T3>(4);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<void,T1,T2,T3>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3);
		}

		//�첽���ã�ί��3���������޷���ֵ
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2,T3>(4);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<void,T1,T2,T3>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2,(typename ParameterPass<T3>::R)t3);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3>*)Pointer())+=*((VDelegate<void,T1,T2,T3>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3>*)Pointer())-=*((VDelegate<void,T1,T2,T3>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��3���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3)
		{return Invoke(t1,t2,t3);}
	};
	template<class T1,class T2>class XDelegate<void,T1,T2,void,void,void,void,void,void>:public XBase
	{
		friend XAction<void,T1,T2,void,void,void,void,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<void,T1,T2,void,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2)const):XBase(new VDelegate<void,T1,T2,void,void,void,void,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1,T2)):XBase(new VDelegate<void,T1,T2,void,void,void,void,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<void,T1,T2,void,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2>(3)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<void,T1,T2,void,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<void,T1,T2,void,void,void,void,void,void>::PCdeclFun fun):XBase(new VDelegate<void,T1,T2,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<void,T1,T2,void,void,void,void,void,void>::PStdCallFun fun):XBase(new VDelegate<void,T1,T2,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<void,T1,T2,void,void,void,void,void,void>::PFastCallFun fun):XBase(new VDelegate<void,T1,T2,void,void,void,void,void,void>(fun)){}
#endif

		XAction<void,T1,T2,void,void,void,void,void,void> MakeAction(ParameterStore<T1>t1,ParameterStore<T2>t2);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2>(3)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��2���������޷���ֵ
		void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2>(3);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<void,T1,T2>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2);
		}

		//�첽���ã�ί��2���������޷���ֵ
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1,T2>(3);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<void,T1,T2>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1,(typename ParameterPass<T2>::R)t2);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2>*)Pointer())+=*((VDelegate<void,T1,T2>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2>*)Pointer())-=*((VDelegate<void,T1,T2>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��2���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2)
		{return Invoke(t1,t2);}
	};
	template<class T1>class XDelegate<void,T1,void,void,void,void,void,void,void>:public XBase
	{
		friend XAction<void,T1,void,void,void,void,void,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<void,T1,void,void,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1)const):XBase(new VDelegate<void,T1,void,void,void,void,void,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,void(T::* fun)(T1)):XBase(new VDelegate<void,T1,void,void,void,void,void,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<void,T1,void,void,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1>(2)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<void,T1,void,void,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate(typename VDelegate<void,T1,void,void,void,void,void,void,void>::PCdeclFun fun):XBase(new VDelegate<void,T1,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate(typename VDelegate<void,T1,void,void,void,void,void,void,void>::PStdCallFun fun):XBase(new VDelegate<void,T1,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate(typename VDelegate<void,T1,void,void,void,void,void,void,void>::PFastCallFun fun):XBase(new VDelegate<void,T1,void,void,void,void,void,void,void>(fun)){}
#endif

		XAction<void,T1,void,void,void,void,void,void,void> MakeAction(ParameterStore<T1>t1);
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1>(2)!=t)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��1���������޷���ֵ
		void Invoke(typename ParameterPass<T1>::RC t1)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1>(2);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<void,T1>*)Pointer())->VInvoke((typename ParameterPass<T1>::R)t1);
		}

		//�첽���ã�ί��1���������޷���ֵ
		DWORD BeginInvoke(typename ParameterPass<T1>::RC t1)
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void,T1>(2);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<void,T1>*)Pointer())->VBeginInvoke((typename ParameterPass<T1>::R)t1);
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1>*)Pointer())+=*((VDelegate<void,T1>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1>*)Pointer())-=*((VDelegate<void,T1>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��1���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1){return Invoke(t1);}
	};
	template<>class XDelegate<void,void,void,void,void,void,void,void,void>:public XBase
	{
		friend XAction<void,void,void,void,void,void,void,void,void>;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XDelegate,IDelegate);
		//XDelegateͨ�÷���
		XDelegateIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XDelegate(const VDelegate<void,void,void,void,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XDelegate(T* t,void(T::* fun)()const):XBase(new VDelegate<void,void,void,void,void,void,void,void,void>(t,fun)){}
		template<class T>XDelegate(T* t,void(T::* fun)()):XBase(new VDelegate<void,void,void,void,void,void,void,void,void>(t,fun)){}
		//��ί�е��Զ�ת��
		operator VDelegate<void,void,void,void,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void>(1)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VDelegate<void,void,void,void,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XDelegate( VDelegate<void,void,void,void,void,void,void,void,void>::PCdeclFun fun):XBase(new VDelegate<void,void,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XDelegate( VDelegate<void,void,void,void,void,void,void,void,void>::PStdCallFun fun):XBase(new VDelegate<void,void,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XDelegate( VDelegate<void,void,void,void,void,void,void,void,void>::PFastCallFun fun):XBase(new VDelegate<void,void,void,void,void,void,void,void,void>(fun)){}
#endif

		XAction<void,void,void,void,void,void,void,void,void> MakeAction();
		//��IDelegateָ���ʼ��
		XDelegate(IDelegate* p)
		{
			if(p)
			{
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void>(1)!=t)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��0���������޷���ֵ
		void Invoke()
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void>(1);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));}
#endif
			return ((VDelegate<void>*)Pointer())->VInvoke();
		}

		//�첽���ã�ί��0���������޷���ֵ
		DWORD BeginInvoke()
		{
#ifdef _DEBUG
			TypesCheckingObject tc = TypesCheckingObject::MakeObject<void>(1);
			if(tc!=GetTypesChecking()){
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(tc));
				return NULL;
			}
#endif
			return ((VDelegate<void>*)Pointer())->VBeginInvoke();
		}

		XDelegate& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void>*)Pointer())+=*((VDelegate<void>*)x.Pointer());
			return *this;
		}
		XDelegate& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XDelegate*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void>*)Pointer())-=*((VDelegate<void>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��0���������޷���ֵ
		void operator()(){return Invoke();}
	};

	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>const XTypes& XDelegate<T1,T2,T3,T4,T5,T6,T7,T8,T9>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<T1,T2,T3,T4,T5,T6,T7,T8,T9>>(),TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,T6,T7,T8,T9>(9),typeid(LJ::XBase));
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>const XTypes& XDelegate<T1,T2,T3,T4,T5,T6,T7,T8,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<T1,T2,T3,T4,T5,T6,T7,T8,void>>(),TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,T6,T7,T8,void>(9),typeid(LJ::XBase));
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7>const XTypes& XDelegate<T1,T2,T3,T4,T5,T6,T7,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<T1,T2,T3,T4,T5,T6,T7,void,void>>(),TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,T6,T7,void,void>(9),typeid(LJ::XBase));
	template<class T1,class T2,class T3,class T4,class T5,class T6>const XTypes& XDelegate<T1,T2,T3,T4,T5,T6,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<T1,T2,T3,T4,T5,T6,void,void,void>>(),TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,T6,void,void,void>(9),typeid(LJ::XBase));
	template<class T1,class T2,class T3,class T4,class T5>const XTypes& XDelegate<T1,T2,T3,T4,T5,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<T1,T2,T3,T4,T5,void,void,void,void>>(),TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T1,class T2,class T3,class T4>const XTypes& XDelegate<T1,T2,T3,T4,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<T1,T2,T3,T4,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<T1,T2,T3,T4,void,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T1,class T2,class T3>const XTypes& XDelegate<T1,T2,T3,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<T1,T2,T3,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<T1,T2,T3,void,void,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T1,class T2>const XTypes& XDelegate<T1,T2,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<T1,T2,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<T1,T2,void,void,void,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T1>const XTypes& XDelegate<T1,void,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<T1,void,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<T1,void,void,void,void,void,void,void,void>(9),typeid(LJ::XBase));

	template<class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>const XTypes& XDelegate<void,T2,T3,T4,T5,T6,T7,T8,T9>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<void,T2,T3,T4,T5,T6,T7,T8,T9>>(),TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,T6,T7,T8,T9>(9),typeid(LJ::XBase));
	template<class T2,class T3,class T4,class T5,class T6,class T7,class T8>const XTypes& XDelegate<void,T2,T3,T4,T5,T6,T7,T8,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<void,T2,T3,T4,T5,T6,T7,T8,void>>(),TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,T6,T7,T8,void>(9),typeid(LJ::XBase));
	template<class T2,class T3,class T4,class T5,class T6,class T7>const XTypes& XDelegate<void,T2,T3,T4,T5,T6,T7,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<void,T2,T3,T4,T5,T6,T7,void,void>>(),TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,T6,T7,void,void>(9),typeid(LJ::XBase));
	template<class T2,class T3,class T4,class T5,class T6>const XTypes& XDelegate<void,T2,T3,T4,T5,T6,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<void,T2,T3,T4,T5,T6,void,void,void>>(),TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,T6,void,void,void>(9),typeid(LJ::XBase));
	template<class T2,class T3,class T4,class T5>const XTypes& XDelegate<void,T2,T3,T4,T5,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<void,T2,T3,T4,T5,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T2,class T3,class T4>const XTypes& XDelegate<void,T2,T3,T4,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<void,T2,T3,T4,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T2,T3,T4,void,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T2,class T3>const XTypes& XDelegate<void,T2,T3,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<void,T2,T3,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T2,T3,void,void,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T2>const XTypes& XDelegate<void,T2,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<void,T2,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T2,void,void,void,void,void,void,void>(9),typeid(LJ::XBase));
	const XTypes& XDelegate<void,void,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XDelegate",Types<LJ::XDelegate<void,void,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,void,void,void,void,void,void,void,void>(9),typeid(LJ::XBase));

#define XActionIRMethods()\
	/*��ȡ����������id*/\
	XTypes GetParameterType(int index)const{return Pointer()->GetParameterType(index);}\
	/*��ȡί�в�������*/\
	int GetParametersCount()const{return Pointer()->GetParametersCount();}\
	/*���ز������ͼ�����*/\
	TypesCheckingObject GetTypesChecking()const{return Pointer()->GetTypesChecking();}\
	/*�з���ֵ*/\
	bool CanReturnValue()const{return Pointer()->CanReturnValue();}\
	/*ͬ������*/\
	void Do(){Pointer()->Do();}\
	/*�첽����*/\
	void DoSync(){Pointer()->DoSync();}\
	/*��ĳ����������Ϊĳ��ֵ*/\
	template<class T>void SetParameter(int index,T& t)\
	{\
		if(Pointer()->GetParameterType()!=XTypes(new Types<T>))throw XException(E_INVALIDARG);\
		ParameterStore<T>::PointerToReference(Pointer()->GetParameterPointer(index))=t;\
	}\
	/*��ȡĳ��������ֵ*/\
	template<class T>T GetParameter(int index)\
	{\
		if(Pointer()->GetParameterType()!=XTypes(new Types<T>))throw XException(E_INVALIDARG);\
		return ParameterStore<T>::PointerToReference(Pointer()->GetParameterPointer(index));\
	}\
	/*��XActions����*/\
	XAction(const XActions& x){*this = (IDelegate*)((XAction&)x).pObject;}\
	/*��ȡί��*/\
	XDelegate GetDelegate(){return Pointer();}\
	/*��ȡί�и���*/\
	XDelegate MakeDelegate(){return Pointer()->NewDelegate();}\
	/*���������*/\
	XAction MakeCopy(){return (IDelegate*)Pointer()->NewCopy();}\
	/*��ת*/\
	void Reverse(){return Pointer()->Reverse();}

	template<class R=void,class T1=void,class T2=void,class T3=void,class T4=void,class T5=void,class T6=void,class T7=void,class T8=void>class XAction:public XBase
	{
		typedef typename XDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		R _paramrefr()const{return ParameterStore<R>::PointerToReference(Pointer()->GetParameterPointer(0));}
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		ParameterStore<T3>& _paramref3(){return ParameterStore<T3>::PointerToReference(Pointer()->GetParameterPointer(3));}
		ParameterStore<T4>& _paramref4(){return ParameterStore<T4>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T5>& _paramref5(){return ParameterStore<T5>::PointerToReference(Pointer()->GetParameterPointer(5));}
		ParameterStore<T6>& _paramref6(){return ParameterStore<T6>::PointerToReference(Pointer()->GetParameterPointer(6));}
		ParameterStore<T7>& _paramref7(){return ParameterStore<T7>::PointerToReference(Pointer()->GetParameterPointer(7));}
		ParameterStore<T8>& _paramref8(){return ParameterStore<T8>::PointerToReference(Pointer()->GetParameterPointer(8));}
		union{
			//ֻ�����ԣ�����ֵ
			PROPERTY_GET(R,XAction,_paramrefr,Ret);
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
			//��д���ԣ�����3
			PROPERTY_REF(ParameterStore<T3>,XAction,_paramref3,P3);
			//��д���ԣ�����4
			PROPERTY_REF(ParameterStore<T4>,XAction,_paramref4,P4);
			//��д���ԣ�����5
			PROPERTY_REF(ParameterStore<T5>,XAction,_paramref5,P5);
			//��д���ԣ�����6
			PROPERTY_REF(ParameterStore<T6>,XAction,_paramref6,P6);
			//��д���ԣ�����7
			PROPERTY_REF(ParameterStore<T7>,XAction,_paramref7,P7);
			//��д���ԣ�����8
			PROPERTY_REF(ParameterStore<T8>,XAction,_paramref8,P8);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2,T3,T4,T5,T6,T7,T8)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>(t,fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2,T3,T4,T5,T6,T7,T8),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>(t,fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
#ifdef CANUSECDECL
		XAction(typename VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
#endif
#ifdef _CLR
		XAction(typename VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>(fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
#endif
		//���������Զ�ת��
		operator VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,T8>(9)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer();
		}

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,T8>(9)!=t
					)throw XException(L"����Ķ�������ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��8���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,t5,t6,t7,t8,pr);}
		//ͬ�����ã�ί��8���������з���ֵ��������ֱֵ�ӷ��أ�
		inline R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2	,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,t5,t6,t7,t8);}

		//�첽���ã�ί��8���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,t5,t6,t7,t8,pr);}
		//�첽���ã�ί��8���������з���ֵ��������ֱֵ�ӷ��أ�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2	,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,t5,t6,t7,t8);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer())+=*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer())-=*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��8���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8,typename ParameterPass<typename Types<R>::Normal*>::RC pr){return Invoke(t1,t2,t3,t4,t5,t6,t7,t8,pr);}
		//ͬ�����ã�ί��8���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8){return Invoke(t1,t2,t3,t4,t5,t6,t7,t8);}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>class XAction<R,T1,T2,T3,T4,T5,T6,T7,void>:public XBase
	{
		typedef typename XDelegate<R,T1,T2,T3,T4,T5,T6,T7,void> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		R _paramrefr()const{return ParameterStore<R>::PointerToReference(Pointer()->GetParameterPointer(0));}
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		ParameterStore<T3>& _paramref3(){return ParameterStore<T3>::PointerToReference(Pointer()->GetParameterPointer(3));}
		ParameterStore<T4>& _paramref4(){return ParameterStore<T4>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T5>& _paramref5(){return ParameterStore<T5>::PointerToReference(Pointer()->GetParameterPointer(5));}
		ParameterStore<T6>& _paramref6(){return ParameterStore<T6>::PointerToReference(Pointer()->GetParameterPointer(6));}
		ParameterStore<T7>& _paramref7(){return ParameterStore<T7>::PointerToReference(Pointer()->GetParameterPointer(7));}
		union{
			//ֻ�����ԣ�����ֵ
			PROPERTY_GET(R,XAction,_paramrefr,Ret);
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
			//��д���ԣ�����3
			PROPERTY_REF(ParameterStore<T3>,XAction,_paramref3,P3);
			//��д���ԣ�����4
			PROPERTY_REF(ParameterStore<T4>,XAction,_paramref4,P4);
			//��д���ԣ�����5
			PROPERTY_REF(ParameterStore<T5>,XAction,_paramref5,P5);
			//��д���ԣ�����6
			PROPERTY_REF(ParameterStore<T6>,XAction,_paramref6,P6);
			//��д���ԣ�����7
			PROPERTY_REF(ParameterStore<T7>,XAction,_paramref7,P7);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<R,T1,T2,T3,T4,T5,T6,T7,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2,T3,T4,T5,T6,T7)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,void>(t,fun,t1,t2,t3,t4,t5,t6,t7)){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2,T3,T4,T5,T6,T7),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,void>(t,fun,t1,t2,t3,t4,t5,t6,t7)){}
		//��ί�е��Զ�ת��
		operator VAction<R,T1,T2,T3,T4,T5,T6,T7,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7>(8)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<R,T1,T2,T3,T4,T5,T6,T7,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<R,T1,T2,T3,T4,T5,T6,T7,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,void>(fun,t1,t2,t3,t4,t5,t6,t7)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<R,T1,T2,T3,T4,T5,T6,T7,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,void>(fun,t1,t2,t3,t4,t5,t6,t7)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<R,T1,T2,T3,T4,T5,T6,T7,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,void>(fun,t1,t2,t3,t4,t5,t6,t7)){}
#endif
#ifdef _CLR
		XAction(typename VAction<R,T1,T2,T3,T4,T5,T6,T7,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,T7,void>(fun,t1,t2,t3,t4,t5,t6,t7)){}
#endif
		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7>(8)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��7���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,t5,t6,t7,pr);}
		//ͬ�����ã�ί��7���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,t5,t6,t7);}

		//�첽���ã�ί��7���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,t5,t6,t7,pr);}
		//�첽���ã�ί��7���������з���ֵ��������ֱֵ�ӷ��أ�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,t5,t6,t7);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7>*)Pointer())+=*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7>*)Pointer())-=*((VDelegate<R,T1,T2,T3,T4,T5,T6,T7>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��7���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return Invoke(t1,t2,t3,t4,t5,t6,t7,pr);}
		//ͬ�����ã�ί��7���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7)
		{return Invoke(t1,t2,t3,t4,t5,t6,t7);}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6>class XAction<R,T1,T2,T3,T4,T5,T6,void,void>:public XBase
	{
		typedef typename XDelegate<R,T1,T2,T3,T4,T5,T6,void,void> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		R _paramrefr()const{return ParameterStore<R>::PointerToReference(Pointer()->GetParameterPointer(0));}
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		ParameterStore<T3>& _paramref3(){return ParameterStore<T3>::PointerToReference(Pointer()->GetParameterPointer(3));}
		ParameterStore<T4>& _paramref4(){return ParameterStore<T4>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T5>& _paramref5(){return ParameterStore<T5>::PointerToReference(Pointer()->GetParameterPointer(5));}
		ParameterStore<T6>& _paramref6(){return ParameterStore<T6>::PointerToReference(Pointer()->GetParameterPointer(6));}
		union{
			//ֻ�����ԣ�����ֵ
			PROPERTY_GET(R,XAction,_paramrefr,Ret);
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
			//��д���ԣ�����3
			PROPERTY_REF(ParameterStore<T3>,XAction,_paramref3,P3);
			//��д���ԣ�����4
			PROPERTY_REF(ParameterStore<T4>,XAction,_paramref4,P4);
			//��д���ԣ�����5
			PROPERTY_REF(ParameterStore<T5>,XAction,_paramref5,P5);
			//��д���ԣ�����6
			PROPERTY_REF(ParameterStore<T6>,XAction,_paramref6,P6);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<R,T1,T2,T3,T4,T5,T6,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2,T3,T4,T5,T6)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,void,void>(t,fun,t1,t2,t3,t4,t5,t6)){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2,T3,T4,T5,T6),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,void,void>(t,fun,t1,t2,t3,t4,t5,t6)){}
		//��ί�е��Զ�ת��
		operator VAction<R,T1,T2,T3,T4,T5,T6,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6>(7)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<R,T1,T2,T3,T4,T5,T6,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<R,T1,T2,T3,T4,T5,T6,void,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,void,void>(fun,t1,t2,t3,t4,t5,t6)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<R,T1,T2,T3,T4,T5,T6,void,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,void,void>(fun,t1,t2,t3,t4,t5,t6)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<R,T1,T2,T3,T4,T5,T6,void,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,void,void>(fun,t1,t2,t3,t4,t5,t6)){}
#endif
#ifdef _CLR
		XAction(typename VAction<R,T1,T2,T3,T4,T5,T6,void,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,T6,void,void>(fun,t1,t2,t3,t4,t5,t6)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6>(7)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��6���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,t5,t6,pr);}
		//ͬ�����ã�ί��6���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,t5,t6);}

		//�첽���ã�ί��6���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,t5,t6,pr);}
		//�첽���ã�ί��6���������з���ֵ��������ֱֵ�ӷ��أ�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,t5,t6);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5,T6>*)Pointer())+=*((VDelegate<R,T1,T2,T3,T4,T5,T6>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5,T6>*)Pointer())-=*((VDelegate<R,T1,T2,T3,T4,T5,T6>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��6���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return Invoke(t1,t2,t3,t4,t5,t6,pr);}
		//ͬ�����ã�ί��6���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6)
		{return Invoke(t1,t2,t3,t4,t5,t6);}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5>class XAction<R,T1,T2,T3,T4,T5,void,void,void>:public XBase
	{
		typedef typename XDelegate<R,T1,T2,T3,T4,T5,void,void,void> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		R _paramrefr()const{return ParameterStore<R>::PointerToReference(Pointer()->GetParameterPointer(0));}
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		ParameterStore<T3>& _paramref3(){return ParameterStore<T3>::PointerToReference(Pointer()->GetParameterPointer(3));}
		ParameterStore<T4>& _paramref4(){return ParameterStore<T4>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T5>& _paramref5(){return ParameterStore<T5>::PointerToReference(Pointer()->GetParameterPointer(5));}
		union{
			//ֻ�����ԣ�����ֵ
			PROPERTY_GET(R,XAction,_paramrefr,Ret);
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
			//��д���ԣ�����3
			PROPERTY_REF(ParameterStore<T3>,XAction,_paramref3,P3);
			//��д���ԣ�����4
			PROPERTY_REF(ParameterStore<T4>,XAction,_paramref4,P4);
			//��д���ԣ�����5
			PROPERTY_REF(ParameterStore<T5>,XAction,_paramref5,P5);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<R,T1,T2,T3,T4,T5,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2,T3,T4,T5)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,void,void,void>(t,fun,t1,t2,t3,t4,t5)){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2,T3,T4,T5),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,void,void,void>(t,fun,t1,t2,t3,t4,t5)){}
		//��ί�е��Զ�ת��
		operator VAction<R,T1,T2,T3,T4,T5,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5>(6)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<R,T1,T2,T3,T4,T5,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<R,T1,T2,T3,T4,T5,void,void,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,void,void,void>(fun,t1,t2,t3,t4,t5)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<R,T1,T2,T3,T4,T5,void,void,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,void,void,void>(fun,t1,t2,t3,t4,t5)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<R,T1,T2,T3,T4,T5,void,void,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,void,void,void>(fun,t1,t2,t3,t4,t5)){}
#endif
#ifdef _CLR
		XAction(typename VAction<R,T1,T2,T3,T4,T5,void,void,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<R,T1,T2,T3,T4,T5,void,void,void>(fun,t1,t2,t3,t4,t5)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5>(6)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��5���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,t5,pr);}
		//ͬ�����ã�ί��5���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,t5);}

		//�첽���ã�ί��5���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,t5,pr);}
		//�첽���ã�ί��5���������з���ֵ��������ֱֵ�ӷ��أ�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,t5);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5>*)Pointer())+=*((VDelegate<R,T1,T2,T3,T4,T5>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4,T5>*)Pointer())-=*((VDelegate<R,T1,T2,T3,T4,T5>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��5���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return Invoke(t1,t2,t3,t4,t5,pr);}
		//ͬ�����ã�ί��5���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5)
		{return Invoke(t1,t2,t3,t4,t5);}
	};
	template<class R,class T1,class T2,class T3,class T4>class XAction<R,T1,T2,T3,T4,void,void,void,void>:public XBase
	{
		typedef typename XDelegate<R,T1,T2,T3,T4,void,void,void,void> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		R _paramrefr()const{return ParameterStore<R>::PointerToReference(Pointer()->GetParameterPointer(0));}
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		ParameterStore<T3>& _paramref3(){return ParameterStore<T3>::PointerToReference(Pointer()->GetParameterPointer(3));}
		ParameterStore<T4>& _paramref4(){return ParameterStore<T4>::PointerToReference(Pointer()->GetParameterPointer(1));}
		union{
			//ֻ�����ԣ�����ֵ
			PROPERTY_GET(R,XAction,_paramrefr,Ret);
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
			//��д���ԣ�����3
			PROPERTY_REF(ParameterStore<T3>,XAction,_paramref3,P3);
			//��д���ԣ�����4
			PROPERTY_REF(ParameterStore<T4>,XAction,_paramref4,P4);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<R,T1,T2,T3,T4,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2,T3,T4)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<R,T1,T2,T3,T4,void,void,void,void>(t,fun,t1,t2,t3,t4)){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2,T3,T4),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<R,T1,T2,T3,T4,void,void,void,void>(t,fun,t1,t2,t3,t4)){}
		//��ί�е��Զ�ת��
		operator VAction<R,T1,T2,T3,T4,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4>(5)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<R,T1,T2,T3,T4,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<R,T1,T2,T3,T4,void,void,void,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<R,T1,T2,T3,T4,void,void,void,void>(fun,t1,t2,t3,t4)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<R,T1,T2,T3,T4,void,void,void,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<R,T1,T2,T3,T4,void,void,void,void>(fun,t1,t2,t3,t4)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<R,T1,T2,T3,T4,void,void,void,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<R,T1,T2,T3,T4,void,void,void,void>(fun,t1,t2,t3,t4)){}
#endif
#ifdef _CLR
		XAction(typename VAction<R,T1,T2,T3,T4,void,void,void,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<R,T1,T2,T3,T4,void,void,void,void>(fun,t1,t2,t3,t4)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2,T3,T4>(5)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��4���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,pr);}
		//ͬ�����ã�ί��4���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4);}

		//�첽���ã�ί��4���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,pr);}
		//�첽���ã�ί��4���������з���ֵ��������ֱֵ�ӷ��أ�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4>*)Pointer())+=*((VDelegate<R,T1,T2,T3,T4>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3,T4>*)Pointer())-=*((VDelegate<R,T1,T2,T3,T4>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��4���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return Invoke(t1,t2,t3,t4,pr);}
		//ͬ�����ã�ί��4���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4)
		{return Invoke(t1,t2,t3,t4);}
	};
	template<class R,class T1,class T2,class T3>class XAction<R,T1,T2,T3,void,void,void,void,void>:public XBase
	{
		typedef typename XDelegate<R,T1,T2,T3,void,void,void,void,void> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		R _paramrefr()const{return ParameterStore<R>::PointerToReference(Pointer()->GetParameterPointer(0));}
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		ParameterStore<T3>& _paramref3(){return ParameterStore<T3>::PointerToReference(Pointer()->GetParameterPointer(3));}
		union{
			//ֻ�����ԣ�����ֵ
			PROPERTY_GET(R,XAction,_paramrefr,Ret);
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
			//��д���ԣ�����3
			PROPERTY_REF(ParameterStore<T3>,XAction,_paramref3,P3);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<R,T1,T2,T3,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2,T3)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<R,T1,T2,T3,void,void,void,void,void>(t,fun,t1,t2,t3)){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2,T3),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<R,T1,T2,T3,void,void,void,void,void>(t,fun,t1,t2,t3)){}
		//��ί�е��Զ�ת��
		operator VAction<R,T1,T2,T3,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2,T3>(4)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<R,T1,T2,T3,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<R,T1,T2,T3,void,void,void,void,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<R,T1,T2,T3,void,void,void,void,void>(fun,t1,t2,t3)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<R,T1,T2,T3,void,void,void,void,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<R,T1,T2,T3,void,void,void,void,void>(fun,t1,t2,t3)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<R,T1,T2,T3,void,void,void,void,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<R,T1,T2,T3,void,void,void,void,void>(fun,t1,t2,t3)){}
#endif
#ifdef _CLR
		XAction(typename VAction<R,T1,T2,T3,void,void,void,void,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<R,T1,T2,T3,void,void,void,void,void>(fun,t1,t2,t3)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2,T3>(4)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��3���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,pr);}
		//ͬ�����ã�ί��3���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3);}

		//�첽���ã�ί��3���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,pr);}
		//�첽���ã�ί��3���������з���ֵ��������ֱֵ�ӷ��أ�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3>*)Pointer())+=*((VDelegate<R,T1,T2,T3>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2,T3>*)Pointer())-=*((VDelegate<R,T1,T2,T3>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��3���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return Invoke(t1,t2,t3,pr);}
		//ͬ�����ã�ί��3���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3)
		{return Invoke(t1,t2,t3);}
	};
	template<class R,class T1,class T2>class XAction<R,T1,T2,void,void,void,void,void,void>:public XBase
	{
		typedef typename XDelegate<R,T1,T2,void,void,void,void,void,void> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,Ret);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		R _paramrefr()const{return ParameterStore<R>::PointerToReference(Pointer()->GetParameterPointer(0));}
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		union{
			//ֻ�����ԣ�����ֵ
			PROPERTY_GET(R,XAction,_paramrefr,Ret);
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<R,T1,T2,void,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<R,T1,T2,void,void,void,void,void,void>(t,fun,t1,t2)){}
		template<class T>XAction(T* t,R(T::* fun)(T1,T2),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<R,T1,T2,void,void,void,void,void,void>(t,fun,t1,t2)){}
		//��ί�е��Զ�ת��
		operator VAction<R,T1,T2,void,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1,T2>(3)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<R,T1,T2,void,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<R,T1,T2,void,void,void,void,void,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<R,T1,T2,void,void,void,void,void,void>(fun,t1,t2)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<R,T1,T2,void,void,void,void,void,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<R,T1,T2,void,void,void,void,void,void>(fun,t1,t2)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<R,T1,T2,void,void,void,void,void,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<R,T1,T2,void,void,void,void,void,void>(fun,t1,t2)){}
#endif
#ifdef _CLR
		XAction(typename VAction<R,T1,T2,void,void,void,void,void,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<R,T1,T2,void,void,void,void,void,void>(fun,t1,t2)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1,T2>(3)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��2���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->Invoke(t1,t2,pr);}
		//ͬ�����ã�ί��2���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2)
		{return ((XDelegate*)this)->Invoke(t1,t2);}

		//�첽���ã�ί��2���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,pr);}
		//�첽���ã�ί��2���������з���ֵ��������ֱֵ�ӷ��أ�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2>*)Pointer())+=*((VDelegate<R,T1,T2>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1,T2>*)Pointer())-=*((VDelegate<R,T1,T2>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��2���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return Invoke(t1,t2,pr);}
		//ͬ�����ã�ί��2���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2)
		{return Invoke(t1,t2);}
	};
	template<class R,class T1>class XAction<R,T1,void,void,void,void,void,void,void>:public XBase
	{
		typedef typename XDelegate<R,T1,void,void,void,void,void,void,void>XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		R _paramrefr()const{return ParameterStore<R>::PointerToReference(Pointer()->GetParameterPointer(0));}
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		union{
			//ֻ�����ԣ�����ֵ
			PROPERTY_GET(R,XAction,_paramrefr,Ret);
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
		};
		//�ӿ��ܵļ���ί��ʵ����й���
		XAction(const VAction<R,T1,void,void,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,R(T::* fun)(T1)const,typename ParameterStore<T1>::RC t1):XBase(new VAction<R,T1,void,void,void,void,void,void,void>(t,fun,t1)){}
		template<class T>XAction(T* t,R(T::* fun)(T1),typename ParameterStore<T1>::RC t1):XBase(new VAction<R,T1,void,void,void,void,void,void,void>(t,fun,t1)){}
		//���������Զ�ת��
		operator VAction<R,T1,void,void,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R,T1>(2)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<R,T1,void,void,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<R,T1,void,void,void,void,void,void,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1):XBase(new VAction<R,T1,void,void,void,void,void,void,void>(fun,t1)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<R,T1,void,void,void,void,void,void,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1):XBase(new VAction<R,T1,void,void,void,void,void,void,void>(fun,t1)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<R,T1,void,void,void,void,void,void,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1):XBase(new VAction<R,T1,void,void,void,void,void,void,void>(fun,t1)){}
#endif
#ifdef _CLR
		XAction(typename VAction<R,T1,void,void,void,void,void,void,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1)
			:XBase(new VAction<R,T1,void,void,void,void,void,void,void>(fun,t1)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R,T1>(2)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��1���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->Invoke(t1,pr);}
		//ͬ�����ã�ί��1���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke(typename ParameterPass<T1>::RC t1)
		{return ((XDelegate*)this)->Invoke(t1);}

		//�첽���ã�ί��1���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->BeginInvoke(t1,pr);}
		//�첽���ã�ί��1���������з���ֵ��������ֱֵ�ӷ��أ�
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1)
		{return ((XDelegate*)this)->BeginInvoke(t1);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1>*)Pointer())+=*((VDelegate<R,T1>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R,T1>*)Pointer())-=*((VDelegate<R,T1>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��1���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<typename Types<R>::Normal*>::RC pr){return Invoke(t1,pr);}
		//ͬ�����ã�ί��1���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(typename ParameterPass<T1>::RC t1){return Invoke(t1);}
	};
	template<class R>class XAction<R,void,void,void,void,void,void,void,void>:public XBase
	{
		typedef typename XDelegate<R,void,void,void,void,void,void,void,void>XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,Ret);
	public:
		//���Է���
		R _paramrefr()const{return ParameterStore<R>::PointerToReference(Pointer()->GetParameterPointer(0));}
		union{
			//ֻ�����ԣ�����ֵ
			PROPERTY_GET(R,XAction,_paramrefr,Ret);
		};
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XAction(const VAction<R,void,void,void,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,R(T::* fun)()const):XBase(new VAction<R,void,void,void,void,void,void,void,void>(t,fun)){}
		template<class T>XAction(T* t,R(T::* fun)()):XBase(new VAction<R,void,void,void,void,void,void,void,void>(t,fun)){}
		//���������Զ�ת��
		operator VAction<R,void,void,void,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<R>(1)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<R,void,void,void,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<R,void,void,void,void,void,void,void,void>::PCdeclFun fun):XBase(new VAction<R,void,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<R,void,void,void,void,void,void,void,void>::PStdCallFun fun):XBase(new VAction<R,void,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<R,void,void,void,void,void,void,void,void>::PFastCallFun fun):XBase(new VAction<R,void,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef _CLR
		XAction(typename VAction<R,void,void,void,void,void,void,void,void>::PClrCallFun fun):XBase(new VAction<R,void,void,void,void,void,void,void,void>(fun)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<R>(1)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��0���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline void Invoke(typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->Invoke(pr);}
		//ͬ�����ã�ί��0���������з���ֵ��������ֱֵ�ӷ��أ�
		R Invoke()
		{return ((XDelegate*)this)->Invoke();}

		//�첽���ã�ί��0���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		inline DWORD BeginInvoke(typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{return ((XDelegate*)this)->BeginInvoke(pr);}
		//�첽���ã�ί��0���������з���ֵ��������ֱֵ�ӷ��أ�
		inline DWORD BeginInvoke()
		{return ((XDelegate*)this)->BeginInvoke();}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R>*)Pointer())+=*((VDelegate<R>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<R>*)Pointer())-=*((VDelegate<R>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��0���������з���ֵ����������ֵ�����ã�����ֵ��ŵ�prָ��Ŀռ��У�������ֵΪ�������ͣ��򷵻ؽ����ָ�뽫ֱ��д��pr�У�
		void operator()(typename ParameterPass<typename Types<R>::Normal*>::RC pr){return Invoke(pr);}
		//ͬ�����ã�ί��0���������з���ֵ��������ֱֵ�ӷ��أ�
		R operator()(){return Invoke();}
	};

	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>class XAction<void,T1,T2,T3,T4,T5,T6,T7,T8>:public XBase
	{
		typedef typename XDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		ParameterStore<T3>& _paramref3(){return ParameterStore<T3>::PointerToReference(Pointer()->GetParameterPointer(3));}
		ParameterStore<T4>& _paramref4(){return ParameterStore<T4>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T5>& _paramref5(){return ParameterStore<T5>::PointerToReference(Pointer()->GetParameterPointer(5));}
		ParameterStore<T6>& _paramref6(){return ParameterStore<T6>::PointerToReference(Pointer()->GetParameterPointer(6));}
		ParameterStore<T7>& _paramref7(){return ParameterStore<T7>::PointerToReference(Pointer()->GetParameterPointer(7));}
		ParameterStore<T8>& _paramref8(){return ParameterStore<T8>::PointerToReference(Pointer()->GetParameterPointer(8));}
		union{
			
			
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
			//��д���ԣ�����3
			PROPERTY_REF(ParameterStore<T3>,XAction,_paramref3,P3);
			//��д���ԣ�����4
			PROPERTY_REF(ParameterStore<T4>,XAction,_paramref4,P4);
			//��д���ԣ�����5
			PROPERTY_REF(ParameterStore<T5>,XAction,_paramref5,P5);
			//��д���ԣ�����6
			PROPERTY_REF(ParameterStore<T6>,XAction,_paramref6,P6);
			//��д���ԣ�����7
			PROPERTY_REF(ParameterStore<T7>,XAction,_paramref7,P7);
			//��д���ԣ�����8
			PROPERTY_REF(ParameterStore<T8>,XAction,_paramref8,P8);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2,T3,T4,T5,T6,T7,T8)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>(t,fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2,T3,T4,T5,T6,T7,T8),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>(t,fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
#ifdef CANUSECDECL
		XAction(typename VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>(fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>(fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>(fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
#endif
#ifdef _CLR
		XAction(typename VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>(fun,t1,t2,t3,t4,t5,t6,t7,t8)){}
#endif
		//���������Զ�ת��
		operator VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7,T8>(9)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer();
		}

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7,T8>(9)!=t
					)throw XException(L"����Ķ�������ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��8���������޷���ֵ
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2	,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,t5,t6,t7,t8);}

		//�첽���ã�ί��8���������޷���ֵ
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2	,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,t5,t6,t7,t8);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer())+=*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>*)Pointer())-=*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��8���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8){return Invoke(t1,t2,t3,t4,t5,t6,t7,t8);}
	};
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7>class XAction<void,T1,T2,T3,T4,T5,T6,T7,void>:public XBase
	{
		typedef typename XDelegate<void,T1,T2,T3,T4,T5,T6,T7,void> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		ParameterStore<T3>& _paramref3(){return ParameterStore<T3>::PointerToReference(Pointer()->GetParameterPointer(3));}
		ParameterStore<T4>& _paramref4(){return ParameterStore<T4>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T5>& _paramref5(){return ParameterStore<T5>::PointerToReference(Pointer()->GetParameterPointer(5));}
		ParameterStore<T6>& _paramref6(){return ParameterStore<T6>::PointerToReference(Pointer()->GetParameterPointer(6));}
		ParameterStore<T7>& _paramref7(){return ParameterStore<T7>::PointerToReference(Pointer()->GetParameterPointer(7));}
		union{
			
			
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
			//��д���ԣ�����3
			PROPERTY_REF(ParameterStore<T3>,XAction,_paramref3,P3);
			//��д���ԣ�����4
			PROPERTY_REF(ParameterStore<T4>,XAction,_paramref4,P4);
			//��д���ԣ�����5
			PROPERTY_REF(ParameterStore<T5>,XAction,_paramref5,P5);
			//��д���ԣ�����6
			PROPERTY_REF(ParameterStore<T6>,XAction,_paramref6,P6);
			//��д���ԣ�����7
			PROPERTY_REF(ParameterStore<T7>,XAction,_paramref7,P7);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<void,T1,T2,T3,T4,T5,T6,T7,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2,T3,T4,T5,T6,T7)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,T7,void>(t,fun,t1,t2,t3,t4,t5,t6,t7)){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2,T3,T4,T5,T6,T7),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,T7,void>(t,fun,t1,t2,t3,t4,t5,t6,t7)){}
		//��ί�е��Զ�ת��
		operator VAction<void,T1,T2,T3,T4,T5,T6,T7,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7>(8)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<void,T1,T2,T3,T4,T5,T6,T7,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<void,T1,T2,T3,T4,T5,T6,T7,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,T7,void>(fun,t1,t2,t3,t4,t5,t6,t7)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<void,T1,T2,T3,T4,T5,T6,T7,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,T7,void>(fun,t1,t2,t3,t4,t5,t6,t7)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<void,T1,T2,T3,T4,T5,T6,T7,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,T7,void>(fun,t1,t2,t3,t4,t5,t6,t7)){}
#endif
#ifdef _CLR
		XAction(typename VAction<void,T1,T2,T3,T4,T5,T6,T7,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,T7,void>(fun,t1,t2,t3,t4,t5,t6,t7)){}
#endif
		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7>(8)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��7���������޷���ֵ
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,t5,t6,t7);}

		//�첽���ã�ί��7���������޷���ֵ
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,t5,t6,t7);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7>*)Pointer())+=*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7>*)Pointer())-=*((VDelegate<void,T1,T2,T3,T4,T5,T6,T7>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��7���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7)
		{return Invoke(t1,t2,t3,t4,t5,t6,t7);}
	};
	template<class T1,class T2,class T3,class T4,class T5,class T6>class XAction<void,T1,T2,T3,T4,T5,T6,void,void>:public XBase
	{
		typedef typename XDelegate<void,T1,T2,T3,T4,T5,T6,void,void> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		ParameterStore<T3>& _paramref3(){return ParameterStore<T3>::PointerToReference(Pointer()->GetParameterPointer(3));}
		ParameterStore<T4>& _paramref4(){return ParameterStore<T4>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T5>& _paramref5(){return ParameterStore<T5>::PointerToReference(Pointer()->GetParameterPointer(5));}
		ParameterStore<T6>& _paramref6(){return ParameterStore<T6>::PointerToReference(Pointer()->GetParameterPointer(6));}
		union{
			
			
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
			//��д���ԣ�����3
			PROPERTY_REF(ParameterStore<T3>,XAction,_paramref3,P3);
			//��д���ԣ�����4
			PROPERTY_REF(ParameterStore<T4>,XAction,_paramref4,P4);
			//��д���ԣ�����5
			PROPERTY_REF(ParameterStore<T5>,XAction,_paramref5,P5);
			//��д���ԣ�����6
			PROPERTY_REF(ParameterStore<T6>,XAction,_paramref6,P6);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<void,T1,T2,T3,T4,T5,T6,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2,T3,T4,T5,T6)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,void,void>(t,fun,t1,t2,t3,t4,t5,t6)){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2,T3,T4,T5,T6),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,void,void>(t,fun,t1,t2,t3,t4,t5,t6)){}
		//��ί�е��Զ�ת��
		operator VAction<void,T1,T2,T3,T4,T5,T6,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6>(7)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<void,T1,T2,T3,T4,T5,T6,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<void,T1,T2,T3,T4,T5,T6,void,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,void,void>(fun,t1,t2,t3,t4,t5,t6)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<void,T1,T2,T3,T4,T5,T6,void,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,void,void>(fun,t1,t2,t3,t4,t5,t6)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<void,T1,T2,T3,T4,T5,T6,void,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,void,void>(fun,t1,t2,t3,t4,t5,t6)){}
#endif
#ifdef _CLR
		XAction(typename VAction<void,T1,T2,T3,T4,T5,T6,void,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,T6,void,void>(fun,t1,t2,t3,t4,t5,t6)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6>(7)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��6���������޷���ֵ
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,t5,t6);}

		//�첽���ã�ί��6���������޷���ֵ
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,t5,t6);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5,T6>*)Pointer())+=*((VDelegate<void,T1,T2,T3,T4,T5,T6>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5,T6>*)Pointer())-=*((VDelegate<void,T1,T2,T3,T4,T5,T6>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��6���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6)
		{return Invoke(t1,t2,t3,t4,t5,t6);}
	};
	template<class T1,class T2,class T3,class T4,class T5>class XAction<void,T1,T2,T3,T4,T5,void,void,void>:public XBase
	{
		typedef typename XDelegate<void,T1,T2,T3,T4,T5,void,void,void> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		ParameterStore<T3>& _paramref3(){return ParameterStore<T3>::PointerToReference(Pointer()->GetParameterPointer(3));}
		ParameterStore<T4>& _paramref4(){return ParameterStore<T4>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T5>& _paramref5(){return ParameterStore<T5>::PointerToReference(Pointer()->GetParameterPointer(5));}
		union{
			
			
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
			//��д���ԣ�����3
			PROPERTY_REF(ParameterStore<T3>,XAction,_paramref3,P3);
			//��д���ԣ�����4
			PROPERTY_REF(ParameterStore<T4>,XAction,_paramref4,P4);
			//��д���ԣ�����5
			PROPERTY_REF(ParameterStore<T5>,XAction,_paramref5,P5);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<void,T1,T2,T3,T4,T5,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2,T3,T4,T5)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,void,void,void>(t,fun,t1,t2,t3,t4,t5)){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2,T3,T4,T5),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,void,void,void>(t,fun,t1,t2,t3,t4,t5)){}
		//��ί�е��Զ�ת��
		operator VAction<void,T1,T2,T3,T4,T5,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5>(6)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<void,T1,T2,T3,T4,T5,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<void,T1,T2,T3,T4,T5,void,void,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,void,void,void>(fun,t1,t2,t3,t4,t5)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<void,T1,T2,T3,T4,T5,void,void,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,void,void,void>(fun,t1,t2,t3,t4,t5)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<void,T1,T2,T3,T4,T5,void,void,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,void,void,void>(fun,t1,t2,t3,t4,t5)){}
#endif
#ifdef _CLR
		XAction(typename VAction<void,T1,T2,T3,T4,T5,void,void,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:XBase(new VAction<void,T1,T2,T3,T4,T5,void,void,void>(fun,t1,t2,t3,t4,t5)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5>(6)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��5���������޷���ֵ
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4,t5);}

		//�첽���ã�ί��5���������޷���ֵ
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4,t5);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5>*)Pointer())+=*((VDelegate<void,T1,T2,T3,T4,T5>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4,T5>*)Pointer())-=*((VDelegate<void,T1,T2,T3,T4,T5>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��5���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5)
		{return Invoke(t1,t2,t3,t4,t5);}
	};
	template<class T1,class T2,class T3,class T4>class XAction<void,T1,T2,T3,T4,void,void,void,void>:public XBase
	{
		typedef typename XDelegate<void,T1,T2,T3,T4,void,void,void,void> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		ParameterStore<T3>& _paramref3(){return ParameterStore<T3>::PointerToReference(Pointer()->GetParameterPointer(3));}
		ParameterStore<T4>& _paramref4(){return ParameterStore<T4>::PointerToReference(Pointer()->GetParameterPointer(1));}
		union{
			
			
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
			//��д���ԣ�����3
			PROPERTY_REF(ParameterStore<T3>,XAction,_paramref3,P3);
			//��д���ԣ�����4
			PROPERTY_REF(ParameterStore<T4>,XAction,_paramref4,P4);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<void,T1,T2,T3,T4,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2,T3,T4)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<void,T1,T2,T3,T4,void,void,void,void>(t,fun,t1,t2,t3,t4)){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2,T3,T4),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<void,T1,T2,T3,T4,void,void,void,void>(t,fun,t1,t2,t3,t4)){}
		//��ί�е��Զ�ת��
		operator VAction<void,T1,T2,T3,T4,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4>(5)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<void,T1,T2,T3,T4,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<void,T1,T2,T3,T4,void,void,void,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<void,T1,T2,T3,T4,void,void,void,void>(fun,t1,t2,t3,t4)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<void,T1,T2,T3,T4,void,void,void,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<void,T1,T2,T3,T4,void,void,void,void>(fun,t1,t2,t3,t4)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<void,T1,T2,T3,T4,void,void,void,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<void,T1,T2,T3,T4,void,void,void,void>(fun,t1,t2,t3,t4)){}
#endif
#ifdef _CLR
		XAction(typename VAction<void,T1,T2,T3,T4,void,void,void,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:XBase(new VAction<void,T1,T2,T3,T4,void,void,void,void>(fun,t1,t2,t3,t4)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2,T3,T4>(5)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��4���������޷���ֵ
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3,t4);}

		//�첽���ã�ί��4���������޷���ֵ
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3,t4);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4>*)Pointer())+=*((VDelegate<void,T1,T2,T3,T4>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3,T4>*)Pointer())-=*((VDelegate<void,T1,T2,T3,T4>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��4���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4)
		{return Invoke(t1,t2,t3,t4);}
	};
	template<class T1,class T2,class T3>class XAction<void,T1,T2,T3,void,void,void,void,void>:public XBase
	{
		typedef typename XDelegate<void,T1,T2,T3,void,void,void,void,void> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		ParameterStore<T3>& _paramref3(){return ParameterStore<T3>::PointerToReference(Pointer()->GetParameterPointer(3));}
		union{
			
			
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
			//��д���ԣ�����3
			PROPERTY_REF(ParameterStore<T3>,XAction,_paramref3,P3);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<void,T1,T2,T3,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2,T3)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<void,T1,T2,T3,void,void,void,void,void>(t,fun,t1,t2,t3)){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2,T3),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<void,T1,T2,T3,void,void,void,void,void>(t,fun,t1,t2,t3)){}
		//��ί�е��Զ�ת��
		operator VAction<void,T1,T2,T3,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2,T3>(4)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<void,T1,T2,T3,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<void,T1,T2,T3,void,void,void,void,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<void,T1,T2,T3,void,void,void,void,void>(fun,t1,t2,t3)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<void,T1,T2,T3,void,void,void,void,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<void,T1,T2,T3,void,void,void,void,void>(fun,t1,t2,t3)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<void,T1,T2,T3,void,void,void,void,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<void,T1,T2,T3,void,void,void,void,void>(fun,t1,t2,t3)){}
#endif
#ifdef _CLR
		XAction(typename VAction<void,T1,T2,T3,void,void,void,void,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:XBase(new VAction<void,T1,T2,T3,void,void,void,void,void>(fun,t1,t2,t3)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2,T3>(4)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��3���������޷���ֵ
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3)
		{return ((XDelegate*)this)->Invoke(t1,t2,t3);}

		//�첽���ã�ί��3���������޷���ֵ
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2,t3);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3>*)Pointer())+=*((VDelegate<void,T1,T2,T3>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2,T3>*)Pointer())-=*((VDelegate<void,T1,T2,T3>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��3���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3)
		{return Invoke(t1,t2,t3);}
	};
	template<class T1,class T2>class XAction<void,T1,T2,void,void,void,void,void,void>:public XBase
	{
		typedef typename XDelegate<void,T1,T2,void,void,void,void,void,void> XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		ParameterStore<T2>& _paramref2(){return ParameterStore<T2>::PointerToReference(Pointer()->GetParameterPointer(2));}
		union{
			
			
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
			//��д���ԣ�����2
			PROPERTY_REF(ParameterStore<T2>,XAction,_paramref2,P2);
		};
		//�ӿ��ܵļ��ֶ���ʵ����й���
		XAction(const VAction<void,T1,T2,void,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<void,T1,T2,void,void,void,void,void,void>(t,fun,t1,t2)){}
		template<class T>XAction(T* t,void(T::* fun)(T1,T2),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<void,T1,T2,void,void,void,void,void,void>(t,fun,t1,t2)){}
		//��ί�е��Զ�ת��
		operator VAction<void,T1,T2,void,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1,T2>(3)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<void,T1,T2,void,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<void,T1,T2,void,void,void,void,void,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<void,T1,T2,void,void,void,void,void,void>(fun,t1,t2)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<void,T1,T2,void,void,void,void,void,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<void,T1,T2,void,void,void,void,void,void>(fun,t1,t2)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<void,T1,T2,void,void,void,void,void,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<void,T1,T2,void,void,void,void,void,void>(fun,t1,t2)){}
#endif
#ifdef _CLR
		XAction(typename VAction<void,T1,T2,void,void,void,void,void,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:XBase(new VAction<void,T1,T2,void,void,void,void,void,void>(fun,t1,t2)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1,T2>(3)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��2���������޷���ֵ
		inline void Invoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2)
		{return ((XDelegate*)this)->Invoke(t1,t2);}

		//�첽���ã�ί��2���������޷���ֵ
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2)
		{return ((XDelegate*)this)->BeginInvoke(t1,t2);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2>*)Pointer())+=*((VDelegate<void,T1,T2>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1,T2>*)Pointer())-=*((VDelegate<void,T1,T2>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��2���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2)
		{return Invoke(t1,t2);}
	};
	template<class T1>class XAction<void,T1,void,void,void,void,void,void,void>:public XBase
	{
		typedef typename XDelegate<void,T1,void,void,void,void,void,void,void>XDelegate;
		friend XDelegate;
		PROPERTY_OFFSET(XAction,P1);
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//���Է���
		
		ParameterStore<T1>& _paramref1(){return ParameterStore<T1>::PointerToReference(Pointer()->GetParameterPointer(1));}
		union{
			
			
			//��д���ԣ�����1
			PROPERTY_REF(ParameterStore<T1>,XAction,_paramref1,P1);
		};
		//�ӿ��ܵļ���ί��ʵ����й���
		XAction(const VAction<void,T1,void,void,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,void(T::* fun)(T1)const,typename ParameterStore<T1>::RC t1):XBase(new VAction<void,T1,void,void,void,void,void,void,void>(t,fun,t1)){}
		template<class T>XAction(T* t,void(T::* fun)(T1),typename ParameterStore<T1>::RC t1):XBase(new VAction<void,T1,void,void,void,void,void,void,void>(t,fun,t1)){}
		//���������Զ�ת��
		operator VAction<void,T1,void,void,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void,T1>(2)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<void,T1,void,void,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction(typename VAction<void,T1,void,void,void,void,void,void,void>::PCdeclFun fun,typename ParameterStore<T1>::RC t1):XBase(new VAction<void,T1,void,void,void,void,void,void,void>(fun,t1)){}
#endif
#ifdef CANUSESTDCALL
		XAction(typename VAction<void,T1,void,void,void,void,void,void,void>::PStdCallFun fun,typename ParameterStore<T1>::RC t1):XBase(new VAction<void,T1,void,void,void,void,void,void,void>(fun,t1)){}
#endif
#ifdef CANUSEFASTCALL
		XAction(typename VAction<void,T1,void,void,void,void,void,void,void>::PFastCallFun fun,typename ParameterStore<T1>::RC t1):XBase(new VAction<void,T1,void,void,void,void,void,void,void>(fun,t1)){}
#endif
#ifdef _CLR
		XAction(typename VAction<void,T1,void,void,void,void,void,void,void>::PClrCallFun fun,typename ParameterStore<T1>::RC t1)
			:XBase(new VAction<void,T1,void,void,void,void,void,void,void>(fun,t1)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void,T1>(2)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��1���������޷���ֵ
		inline void Invoke(typename ParameterPass<T1>::RC t1)
		{return ((XDelegate*)this)->Invoke(t1);}

		//�첽���ã�ί��1���������޷���ֵ
		inline DWORD BeginInvoke(typename ParameterPass<T1>::RC t1)
		{return ((XDelegate*)this)->BeginInvoke(t1);}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1>*)Pointer())+=*((VDelegate<void,T1>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void,T1>*)Pointer())-=*((VDelegate<void,T1>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��1���������޷���ֵ
		void operator()(typename ParameterPass<T1>::RC t1){return Invoke(t1);}
	};
	template<>class XAction<void,void,void,void,void,void,void,void,void>:public XBase
	{
		typedef  XDelegate<void,void,void,void,void,void,void,void,void>XDelegate;
		friend XDelegate;
	public:
		//XBase�ӿ�������ͨ�÷���
		XBaseIRTypeMethods_H(XAction,IDelegate);
		//XActionͨ�÷���
		XActionIRMethods();
		//�ӿ��ܵļ���ί��ʵ����й���
		XAction(const VAction<void,void,void,void,void,void,void,void,void>& d):XBase(d.NewCopy()){}
		template<class T>XAction(T* t,void(T::* fun)()const):XBase(new VAction<void,void,void,void,void,void,void,void,void>(t,fun)){}
		template<class T>XAction(T* t,void(T::* fun)()):XBase(new VAction<void,void,void,void,void,void,void,void,void>(t,fun)){}
		//���������Զ�ת��
		operator VAction<void,void,void,void,void,void,void,void,void>&()
		{
			if(TypesCheckingObject::MakeObject<void>(1)!=GetTypesChecking())throw XException(E_ILLEGAL_METHOD_CALL);
			return *(VAction<void,void,void,void,void,void,void,void,void>*)Pointer();
		}
#ifdef CANUSECDECL
		XAction( VAction<void,void,void,void,void,void,void,void,void>::PCdeclFun fun):XBase(new VAction<void,void,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSESTDCALL
		XAction( VAction<void,void,void,void,void,void,void,void,void>::PStdCallFun fun):XBase(new VAction<void,void,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef CANUSEFASTCALL
		XAction( VAction<void,void,void,void,void,void,void,void,void>::PFastCallFun fun):XBase(new VAction<void,void,void,void,void,void,void,void,void>(fun)){}
#endif
#ifdef _CLR
		XAction( VAction<void,void,void,void,void,void,void,void,void>::PClrCallFun fun):XBase(new VAction<void,void,void,void,void,void,void,void,void>(fun)){}
#endif

		//��IDelegateָ���ʼ��
		XAction(IDelegate* p)
		{
			if(p)
			{
				if(!p->IsAction())throw XException(L"�����ί�в���������",E_INVALIDARG);
				TypesCheckingObject t=p->GetTypesChecking();
				if(TypesCheckingObject::MakeObject<void>(1)!=t
					)throw XException(L"�����ί�и���ǰʵ���޷�ƥ��",E_INVALIDARG,ToString());
				(XBase&)*this = p;
			}
		}

		//ͬ�����ã�ί��0���������޷���ֵ
		inline void Invoke()
		{return ((XDelegate*)this)->Invoke();}

		//�첽���ã�ί��0���������޷���ֵ
		inline DWORD BeginInvoke()
		{return ((XDelegate*)this)->BeginInvoke();}

		XAction& operator+=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void>*)Pointer())+=*((VDelegate<void>*)x.Pointer());
			return *this;
		}
		XAction& operator-=(const XDelegate&x)
		{
			if(IsNull())throw XException(E_POINTER);
			if(x.IsNull())return *this;
#ifdef _DEBUG
			if(GetTypesChecking()!=x.GetTypesChecking())
			{
				IDelegate::ShowParamertersTypeError(GetTypesChecking().FindDifferenceWith(x.GetTypesChecking()));
				return *this;
			}
#endif
			if(((XAction*)Pointer())->referenceCount!=1)*this = (IDelegate*)Pointer()->NewCopy();
			*((VDelegate<void>*)Pointer())-=*((VDelegate<void>*)x.Pointer());
			return *this;
		}

		//ͬ�����ã�ί��0���������޷���ֵ
		void operator()(){return Invoke();}
	};

	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>const XTypes& XAction<T1,T2,T3,T4,T5,T6,T7,T8,T9>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<T1,T2,T3,T4,T5,T6,T7,T8,T9>>(),TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,T6,T7,T8,T9>(9),typeid(LJ::XBase));
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>const XTypes& XAction<T1,T2,T3,T4,T5,T6,T7,T8,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<T1,T2,T3,T4,T5,T6,T7,T8,void>>(),TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,T6,T7,T8,void>(9),typeid(LJ::XBase));
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7>const XTypes& XAction<T1,T2,T3,T4,T5,T6,T7,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<T1,T2,T3,T4,T5,T6,T7,void,void>>(),TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,T6,T7,void,void>(9),typeid(LJ::XBase));
	template<class T1,class T2,class T3,class T4,class T5,class T6>const XTypes& XAction<T1,T2,T3,T4,T5,T6,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<T1,T2,T3,T4,T5,T6,void,void,void>>(),TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,T6,void,void,void>(9),typeid(LJ::XBase));
	template<class T1,class T2,class T3,class T4,class T5>const XTypes& XAction<T1,T2,T3,T4,T5,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<T1,T2,T3,T4,T5,void,void,void,void>>(),TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T1,class T2,class T3,class T4>const XTypes& XAction<T1,T2,T3,T4,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<T1,T2,T3,T4,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<T1,T2,T3,T4,void,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T1,class T2,class T3>const XTypes& XAction<T1,T2,T3,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<T1,T2,T3,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<T1,T2,T3,void,void,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T1,class T2>const XTypes& XAction<T1,T2,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<T1,T2,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<T1,T2,void,void,void,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T1>const XTypes& XAction<T1,void,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<T1,void,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<T1,void,void,void,void,void,void,void,void>(9),typeid(LJ::XBase));

	template<class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>const XTypes& XAction<void,T2,T3,T4,T5,T6,T7,T8,T9>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<void,T2,T3,T4,T5,T6,T7,T8,T9>>(),TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,T6,T7,T8,T9>(9),typeid(LJ::XBase));
	template<class T2,class T3,class T4,class T5,class T6,class T7,class T8>const XTypes& XAction<void,T2,T3,T4,T5,T6,T7,T8,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<void,T2,T3,T4,T5,T6,T7,T8,void>>(),TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,T6,T7,T8,void>(9),typeid(LJ::XBase));
	template<class T2,class T3,class T4,class T5,class T6,class T7>const XTypes& XAction<void,T2,T3,T4,T5,T6,T7,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<void,T2,T3,T4,T5,T6,T7,void,void>>(),TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,T6,T7,void,void>(9),typeid(LJ::XBase));
	template<class T2,class T3,class T4,class T5,class T6>const XTypes& XAction<void,T2,T3,T4,T5,T6,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<void,T2,T3,T4,T5,T6,void,void,void>>(),TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,T6,void,void,void>(9),typeid(LJ::XBase));
	template<class T2,class T3,class T4,class T5>const XTypes& XAction<void,T2,T3,T4,T5,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<void,T2,T3,T4,T5,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T2,class T3,class T4>const XTypes& XAction<void,T2,T3,T4,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<void,T2,T3,T4,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T2,T3,T4,void,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T2,class T3>const XTypes& XAction<void,T2,T3,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<void,T2,T3,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T2,T3,void,void,void,void,void,void>(9),typeid(LJ::XBase));
	template<class T2>const XTypes& XAction<void,T2,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<void,T2,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T2,void,void,void,void,void,void,void>(9),typeid(LJ::XBase));
	const XTypes& XAction<void,void,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::XAction",Types<LJ::XAction<void,void,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,void,void,void,void,void,void,void,void>(9),typeid(LJ::XBase));

	template<class X1,class X2,class X3,class X4,class X5,class X6,class X7,class X8>XActions XDelegates::MakeAction(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& x6,const X7& x7,const X8& x8)const
	{
		int i = GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7,X8>(9),1);
		if(i>0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		ParameterStore<X1> t1(x1);ParameterStore<X2> t2(x2);ParameterStore<X3> t3(x3);ParameterStore<X4> t4(x4);ParameterStore<X5> t5(x5);ParameterStore<X6> t6(x6);ParameterStore<X7> t7(x7);ParameterStore<X8> t8(x8);
		return Pointer()->NewAction(t1.GetPointer(),t2.GetPointer(),t3.GetPointer(),t4.GetPointer(),t5.GetPointer(),t6.GetPointer(),t7.GetPointer(),t8.GetPointer());
	}
	template<class X1,class X2,class X3,class X4,class X5,class X6,class X7>XActions XDelegates::MakeAction(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& x6,const X7& x7)const
	{
		int i = GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6,X7>(8),1);
		if(i>0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		ParameterStore<X1> t1(x1);ParameterStore<X2> t2(x2);ParameterStore<X3> t3(x3);ParameterStore<X4> t4(x4);ParameterStore<X5> t5(x5);ParameterStore<X6> t6(x6);ParameterStore<X7> t7(x7);
		return Pointer()->NewAction(t1.GetPointer(),t2.GetPointer(),t3.GetPointer(),t4.GetPointer(),t5.GetPointer(),t6.GetPointer(),t7.GetPointer());
	}
	template<class X1,class X2,class X3,class X4,class X5,class X6>XActions XDelegates::MakeAction(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5,const X6& x6)const
	{
		int i = GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5,X6>(7),1);
		if(i>0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		ParameterStore<X1> t1(x1);ParameterStore<X2> t2(x2);ParameterStore<X3> t3(x3);ParameterStore<X4> t4(x4);ParameterStore<X5> t5(x5);ParameterStore<X6> t6(x6);
		return Pointer()->NewAction(t1.GetPointer(),t2.GetPointer(),t3.GetPointer(),t4.GetPointer(),t5.GetPointer(),t6.GetPointer());
	}
	template<class X1,class X2,class X3,class X4,class X5>XActions XDelegates::MakeAction(const X1& x1,const X2& x2,const X3& x3,const X4& x4,const X5& x5)const
	{
		int i = GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4,X5>(6),1);
		if(i>0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		ParameterStore<X1> t1(x1);ParameterStore<X2> t2(x2);ParameterStore<X3> t3(x3);ParameterStore<X4> t4(x4);ParameterStore<X5> t5(x5);
		return Pointer()->NewAction(t1.GetPointer(),t2.GetPointer(),t3.GetPointer(),t4.GetPointer(),t5.GetPointer());
	}
	template<class X1,class X2,class X3,class X4>XActions XDelegates::MakeAction(const X1& x1,const X2& x2,const X3& x3,const X4& x4)const
	{
		int i = GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3,X4>(5),1);
		if(i>0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		ParameterStore<X1> t1(x1);ParameterStore<X2> t2(x2);ParameterStore<X3> t3(x3);ParameterStore<X4> t4(x4);
		return Pointer()->NewAction(t1.GetPointer(),t2.GetPointer(),t3.GetPointer(),t4.GetPointer());
	}
	template<class X1,class X2,class X3>XActions XDelegates::MakeAction(const X1& x1,const X2& x2,const X3& x3)const
	{
		int i = GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2,X3>(4),1);
		if(i>0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		ParameterStore<X1> t1(x1);ParameterStore<X2> t2(x2);ParameterStore<X3> t3(x3);
		return Pointer()->NewAction(t1.GetPointer(),t2.GetPointer(),t3.GetPointer());
	}
	template<class X1,class X2>XActions XDelegates::MakeAction(const X1& x1,const X2& x2)const
	{
		int i = GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1,X2>(3),1);
		if(i>0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		ParameterStore<X1> t1(x1);ParameterStore<X2> t2(x2);
		return Pointer()->NewAction(t1.GetPointer(),t2.GetPointer());
	}
	template<class X1>XActions XDelegates::MakeAction(const X1& x1)const
	{
		int i = GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void,X1>(2),1);
		if(i>0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		ParameterStore<X1> t1(x1);
		return Pointer()->NewAction(t1.GetPointer());
	}
	XActions XDelegates::MakeAction()const
	{
		int i = GetTypesChecking().AppFindDifferenceWith(TypesCheckingObject::MakeObject<void>(1),1);
		if(i>0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return Pointer()->NewAction();
	}

	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>XAction<T1,T2,T3,T4,T5,T6,T7,T8,T9> XDelegate<T1,T2,T3,T4,T5,T6,T7,T8,T9>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2,ParameterStore<T4>t3,ParameterStore<T5>t4,ParameterStore<T6>t5,ParameterStore<T7>t6,ParameterStore<T8>t7,ParameterStore<T9>t8)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,T6,T7,T8,T9>(9));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<T1,T2,T3,T4,T5,T6,T7,T8,T9>(*(VDelegate<T1,T2,T3,T4,T5,T6,T7,T8,T9>*)Pointer(),t1,t2,t3,t4,t5,t6,t7,t8);
	}
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>XAction<T1,T2,T3,T4,T5,T6,T7,T8,void> XDelegate<T1,T2,T3,T4,T5,T6,T7,T8,void>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2,ParameterStore<T4>t3,ParameterStore<T5>t4,ParameterStore<T6>t5,ParameterStore<T7>t6,ParameterStore<T8>t7)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,T6,T7,T8>(8));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<T1,T2,T3,T4,T5,T6,T7,T8,void>(*(VDelegate<T1,T2,T3,T4,T5,T6,T7,T8,void>*)Pointer(),t1,t2,t3,t4,t5,t6,t7);
	}
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7>XAction<T1,T2,T3,T4,T5,T6,T7,void,void> XDelegate<T1,T2,T3,T4,T5,T6,T7,void,void>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2,ParameterStore<T4>t3,ParameterStore<T5>t4,ParameterStore<T6>t5,ParameterStore<T7>t6)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,T6,T7>(7));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<T1,T2,T3,T4,T5,T6,T7,void,void>(*(VDelegate<T1,T2,T3,T4,T5,T6,T7,void,void>*)Pointer(),t1,t2,t3,t4,t5,t6);
	}
	template<class T1,class T2,class T3,class T4,class T5,class T6>XAction<T1,T2,T3,T4,T5,T6,void,void,void> XDelegate<T1,T2,T3,T4,T5,T6,void,void,void>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2,ParameterStore<T4>t3,ParameterStore<T5>t4,ParameterStore<T6>t5)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5,T6>(6));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<T1,T2,T3,T4,T5,T6,void,void,void>(*(VDelegate<T1,T2,T3,T4,T5,T6,void,void,void>*)Pointer(),t1,t2,t3,t4,t5);
	}
	template<class T1,class T2,class T3,class T4,class T5>XAction<T1,T2,T3,T4,T5,void,void,void,void> XDelegate<T1,T2,T3,T4,T5,void,void,void,void>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2,ParameterStore<T4>t3,ParameterStore<T5>t4)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<T1,T2,T3,T4,T5>(5));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<T1,T2,T3,T4,T5,void,void,void,void>(*(VDelegate<T1,T2,T3,T4,T5,void,void,void,void>*)Pointer(),t1,t2,t3,t4);
	}
	template<class T1,class T2,class T3,class T4>XAction<T1,T2,T3,T4,void,void,void,void,void> XDelegate<T1,T2,T3,T4,void,void,void,void,void>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2,ParameterStore<T4>t3)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<T1,T2,T3,T4>(4));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<T1,T2,T3,T4,void,void,void,void,void>(*(VDelegate<T1,T2,T3,T4,void,void,void,void,void>*)Pointer(),t1,t2,t3);
	}
	template<class T1,class T2,class T3>XAction<T1,T2,T3,void,void,void,void,void,void> XDelegate<T1,T2,T3,void,void,void,void,void,void>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<T1,T2,T3>(3));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<T1,T2,T3,void,void,void,void,void,void>(*(VDelegate<T1,T2,T3,void,void,void,void,void,void>*)Pointer(),t1,t2);
	}
	template<class T1,class T2>XAction<T1,T2,void,void,void,void,void,void,void> XDelegate<T1,T2,void,void,void,void,void,void,void>::MakeAction(ParameterStore<T2>t1)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<T1,T2>(2));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<T1,T2,void,void,void,void,void,void,void>(*(VDelegate<T1,T2,void,void,void,void,void,void,void>*)Pointer(),t1);
	}
	template<class T1>XAction<T1,void,void,void,void,void,void,void,void> XDelegate<T1,void,void,void,void,void,void,void,void>::MakeAction()
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<T1>(1));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;}
		return new VAction<T1,void,void,void,void,void,void,void,void>(*(VDelegate<T1,void,void,void,void,void,void,void,void>*)Pointer());
	}

	template<class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>XAction<void,T2,T3,T4,T5,T6,T7,T8,T9> XDelegate<void,T2,T3,T4,T5,T6,T7,T8,T9>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2,ParameterStore<T4>t3,ParameterStore<T5>t4,ParameterStore<T6>t5,ParameterStore<T7>t6,ParameterStore<T8>t7,ParameterStore<T9>t8)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,T6,T7,T8,T9>(9));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<void,T2,T3,T4,T5,T6,T7,T8,T9>(*(VDelegate<void,T2,T3,T4,T5,T6,T7,T8,T9>*)Pointer(),t1,t2,t3,t4,t5,t6,t7,t8);
	}
	template<class T2,class T3,class T4,class T5,class T6,class T7,class T8>XAction<void,T2,T3,T4,T5,T6,T7,T8,void> XDelegate<void,T2,T3,T4,T5,T6,T7,T8,void>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2,ParameterStore<T4>t3,ParameterStore<T5>t4,ParameterStore<T6>t5,ParameterStore<T7>t6,ParameterStore<T8>t7)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,T6,T7,T8>(8));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<void,T2,T3,T4,T5,T6,T7,T8,void>(*(VDelegate<void,T2,T3,T4,T5,T6,T7,T8,void>*)Pointer(),t1,t2,t3,t4,t5,t6,t7);
	}
	template<class T2,class T3,class T4,class T5,class T6,class T7>XAction<void,T2,T3,T4,T5,T6,T7,void,void> XDelegate<void,T2,T3,T4,T5,T6,T7,void,void>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2,ParameterStore<T4>t3,ParameterStore<T5>t4,ParameterStore<T6>t5,ParameterStore<T7>t6)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,T6,T7>(7));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<void,T2,T3,T4,T5,T6,T7,void,void>(*(VDelegate<void,T2,T3,T4,T5,T6,T7,void,void>*)Pointer(),t1,t2,t3,t4,t5,t6);
	}
	template<class T2,class T3,class T4,class T5,class T6>XAction<void,T2,T3,T4,T5,T6,void,void,void> XDelegate<void,T2,T3,T4,T5,T6,void,void,void>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2,ParameterStore<T4>t3,ParameterStore<T5>t4,ParameterStore<T6>t5)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<void,T2,T3,T4,T5,T6>(6));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<void,T2,T3,T4,T5,T6,void,void,void>(*(VDelegate<void,T2,T3,T4,T5,T6,void,void,void>*)Pointer(),t1,t2,t3,t4,t5);
	}
	template<class T2,class T3,class T4,class T5>XAction<void,T2,T3,T4,T5,void,void,void,void> XDelegate<void,T2,T3,T4,T5,void,void,void,void>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2,ParameterStore<T4>t3,ParameterStore<T5>t4)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<void,T2,T3,T4,T5>(5));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<void,T2,T3,T4,T5,void,void,void,void>(*(VDelegate<void,T2,T3,T4,T5,void,void,void,void>*)Pointer(),t1,t2,t3,t4);
	}
	template<class T2,class T3,class T4>XAction<void,T2,T3,T4,void,void,void,void,void> XDelegate<void,T2,T3,T4,void,void,void,void,void>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2,ParameterStore<T4>t3)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<void,T2,T3,T4>(4));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<void,T2,T3,T4,void,void,void,void,void>(*(VDelegate<void,T2,T3,T4,void,void,void,void,void>*)Pointer(),t1,t2,t3);
	}
	template<class T2,class T3>XAction<void,T2,T3,void,void,void,void,void,void> XDelegate<void,T2,T3,void,void,void,void,void,void>::MakeAction(ParameterStore<T2>t1,ParameterStore<T3>t2)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<void,T2,T3>(3));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<void,T2,T3,void,void,void,void,void,void>(*(VDelegate<void,T2,T3,void,void,void,void,void,void>*)Pointer(),t1,t2);
	}
	template<class T2>XAction<void,T2,void,void,void,void,void,void,void> XDelegate<void,T2,void,void,void,void,void,void,void>::MakeAction(ParameterStore<T2>t1)
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<void,T2>(2));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;;}
		return new VAction<void,T2,void,void,void,void,void,void,void>(*(VDelegate<void,T2,void,void,void,void,void,void,void>*)Pointer(),t1);
	}
	XAction<void,void,void,void,void,void,void,void,void> XDelegate<void,void,void,void,void,void,void,void,void>::MakeAction()
	{
		int i= GetTypesChecking().FindDifferenceWith(TypesCheckingObject::MakeObject<void>(1));
		if(i>=0){IDelegate::ShowParamertersTypeError(i);return (IDelegate*)NULL;}
		return new VAction<void,void,void,void,void,void,void,void,void>(*(VDelegate<void,void,void,void,void,void,void,void,void>*)Pointer());
	}

}