#pragma once
#define XDELEGATE_
#include "ThreadControl.h"
namespace LJ
{
	//委托链模板
	struct DFunLists
	{
		DFunLists():pt(NULL),next(NULL){}
		//函数指针类型：0.cdecl，1.stdcall，2.fastcall，3.clrcall，4.delegate，其它thiscall
		void *pt;
		//下一个函数指针
		DFunLists* next;
	};
	template<class T>struct DFunList:public DFunLists
	{
		DFunList():fun(NULL){}
		//调用函数
		union
		{
			T fun;
			unsigned long long vpfun;
		};
	};

	//delegate代表一个委托事件，可通过Invoke方法进行事件的同步执行，通过BeginInvoke进行事件的异步执行，无返回值
	struct IDelegate:public XBase
	{
		XBaseITypeMethods_H(IDelegate);
		
		DFunLists* pFun;
		//复制列表
		static DFunLists* ListCopy(DFunLists*p,DFunLists**pr=NULL)
		{
			if(!p)return NULL;
			DFunLists* pd=NULL;
			pd = new DFunList<int>(*(DFunList<int>*)p);
			DFunLists* pt=pd;
			while(p=pt->next)
			{
				pd = new DFunList<int>(*(DFunList<int>*)p);
				pt = p;
			}
			if(pr)*pr=pt;
			return pd;
		}
		//添加函数指针列表项（复制添加，最后添加的在最前面）
		void ListAdd(DFunLists*p)
		{
			DFunLists* pend;
			p = ListCopy(p,&pend);
			pend->next = pFun;
			pFun = p;
		}
		//比较两个链表是否从p1和p2起进行比较有包含（或相等）,若完全包含或相等，则返回相同项目数，否则返回0
		static int ListInclude(DFunLists*p1,DFunLists*p2)
		{
			if(!p1||!p2)return 0;
			int count=0;
			while(p1&&p2)
			{
				if(p1->pt!=p2->pt)return 0;
				if(((DFunList<int>*)p1)->vpfun != ((DFunList<int>*)p2)->vpfun)return 0;
				p1=p1->next;p2=p2->next;
				++count;
			}
			return count;
		}
		//移除一项
		static void ListRemoveOne(DFunLists*p)
		{
			delete (DFunList<int>*)p;
		}
		//移除列表的所有项
		static void ListRemove(DFunLists*p)
		{
			while(p)
			{
				DFunLists*pt = p->next;
				ListRemoveOne(p);
				p=pt;
			}
		}
		//翻转列表
		void Reverse()
		{
			DFunLists* pt=NULL;
			while(pFun)
			{
				DFunLists* p = pFun ->next;
				pFun->next = pt;
				pt = pFun;
				pFun = p;
			}
			pFun = pt;
		}

		IDelegate():pFun(NULL){}
		IDelegate(DFunLists*p):pFun(p){}
		//调用类型
		static enum DelegateType:long long
		{
			Cdecl=0,
			StdCall=1,
			FastCall=2,
			ClrCall=3,
			ClrDelegate=4,
			ThisCall
		};
		//提示
		static void ShowParamertersCountError(int c)
		{
			wchar_t str[32];
			wsprintfW(str,L"函数的参数数量有：%d个",c);
			MessageBoxW(0,str,L"参数数量错误。",0);
		}
		static void ShowParamertersTypeError(int count)
		{
			wchar_t str[32];
			wsprintfW(str,L"检测到序号为%d的参数类型异常，委托过程将被取消。",count);
			MessageBoxW(NULL,str,L"委托错误",0);
		}
		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const;
		//获取委托参数数量
		virtual int GetParametersCount()const{return 0;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject();}
		//有返回值
		virtual bool CanReturnValue()const{return false;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*,void*,void*,void*);
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*,void*,void*);
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*,void*);
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*);
		virtual IDelegate* NewAction(void*,void*,void*,void*);
		virtual IDelegate* NewAction(void*,void*,void*);
		virtual IDelegate* NewAction(void*,void*);
		virtual IDelegate* NewAction(void*);
		virtual IDelegate* NewAction();
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void*,void*,void*,void*,void*,void*,void*,void*,void*const&);
		virtual void* Invoke(void*,void*,void*,void*,void*,void*,void*,void*const&);
		virtual void* Invoke(void*,void*,void*,void*,void*,void*,void*const&);
		virtual void* Invoke(void*,void*,void*,void*,void*,void*const&);
		virtual void* Invoke(void*,void*,void*,void*,void*const&);
		virtual void* Invoke(void*,void*,void*,void*const&);
		virtual void* Invoke(void*,void*,void*const&);
		virtual void* Invoke(void*,void*const&);
		virtual void* Invoke(void*const&);
		virtual void* Invoke();
		//异步调用，返回执行线程ID，可选择接受返回值，如果返回值为引用，则写入一个指针
		virtual DWORD BeginInvoke(void*,void*,void*,void*,void*,void*,void*,void*,void*const&);
		virtual DWORD BeginInvoke(void*,void*,void*,void*,void*,void*,void*,void*const&);
		virtual DWORD BeginInvoke(void*,void*,void*,void*,void*,void*,void*const&);
		virtual DWORD BeginInvoke(void*,void*,void*,void*,void*,void*const&);
		virtual DWORD BeginInvoke(void*,void*,void*,void*,void*const&);
		virtual DWORD BeginInvoke(void*,void*,void*,void*const&);
		virtual DWORD BeginInvoke(void*,void*,void*const&);
		virtual DWORD BeginInvoke(void*,void*const&);
		virtual DWORD BeginInvoke(void*const&);
		virtual DWORD BeginInvoke();
		//Action方法
		virtual bool IsAction()const;
		virtual void Do();
		DWORD DoSync();
		virtual IDelegate* NewDelegate()const;
		virtual void* GetReturnValuePointer();
		virtual void* GetParameterPointer(int)const;
	};


	//VDelegate

	//返回值非引用
	template<class R=void,class T1=void,class T2=void,class T3=void,class T4=void,class T5=void,class T6=void,class T7=void,class T8=void>struct VDelegate:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl *PCdeclFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall *PStdCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall *PFastCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall *PClrCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2,T3,T4,T5,T6,T7,T8)>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2,T3,T4,T5,T6,T7,T8)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2,T3,T4,T5,T6,T7,T8)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			case 5:return XTypes(new Types<T5>());
			case 6:return XTypes(new Types<T6>());
			case 7:return XTypes(new Types<T7>());
			case 8:return XTypes(new Types<T8>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 8;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,T8>(9);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void* t8,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						else (*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						else (*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						else (*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						else (*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
#endif
				default:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						else (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						return pr;
					}
					(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void* t8,void*const& pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2,T3,T4,T5,T6,T7,T8>::Begin((typename Types<R>::Normal*)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
		}
		//同步调用
		R VInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
				}
				p=p->next;
			}
			return Types<R>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2,T3,T4,T5,T6,T7,T8>::Begin(pr,this,&VDelegate::VInvoke,t1,t2,t3,t4,t5,t6,t7,t8);
		}
		
		//operator,不推荐使用，会产生两次复制
		R operator()(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8){return VInvoke(t1,t2,t3,t4,t5,t6,t7,t8);}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>struct VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl *PCdeclFun)(T1,T2,T3,T4,T5,T6,T7);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall *PStdCallFun)(T1,T2,T3,T4,T5,T6,T7);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall *PFastCallFun)(T1,T2,T3,T4,T5,T6,T7);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall *PClrCallFun)(T1,T2,T3,T4,T5,T6,T7);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7)){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2,T3,T4,T5,T6,T7)>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2,T3,T4,T5,T6,T7)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2,T3,T4,T5,T6,T7)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2,T3,T4,T5,T6,T7)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			case 5:return XTypes(new Types<T5>());
			case 6:return XTypes(new Types<T6>());
			case 7:return XTypes(new Types<T7>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 7;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7>(8);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						else (*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						else (*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						else (*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						else (*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
#endif
				default:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						else (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						return pr;
					}
					(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void*const& pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2,T3,T4,T5,T6,T7>::Begin((typename Types<R>::Normal*)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
		}
		//同步调用
		R VInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
				}
				p=p->next;
			}
			return Types<R>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2,T3,T4,T5,T6,T7>::Begin(pr,this,&VDelegate::VInvoke,t1,t2,t3,t4,t5,t6,t7);
		}
		
		//operator,不推荐使用，会产生两次复制
		R operator()(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7){return VInvoke(t1,t2,t3,t4,t5,t6,t7);}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6>struct VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl *PCdeclFun)(T1,T2,T3,T4,T5,T6);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall *PStdCallFun)(T1,T2,T3,T4,T5,T6);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall *PFastCallFun)(T1,T2,T3,T4,T5,T6);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall *PClrCallFun)(T1,T2,T3,T4,T5,T6);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6)){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2,T3,T4,T5,T6)>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2,T3,T4,T5,T6)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2,T3,T4,T5,T6)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2,T3,T4,T5,T6)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			case 5:return XTypes(new Types<T5>());
			case 6:return XTypes(new Types<T6>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 6;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6>(7);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						else (*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						else (*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						else (*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						else (*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
#endif
				default:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						else (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						return pr;
					}
					(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void*const& pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2,T3,T4,T5,T6>::Begin((typename Types<R>::Normal*)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
		}
		//同步调用
		R VInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
				}
				p=p->next;
			}
			return Types<R>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2,T3,T4,T5,T6>::Begin(pr,this,&VDelegate::VInvoke,t1,t2,t3,t4,t5,t6);
		}
		
		//operator,不推荐使用，会产生两次复制
		R operator()(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6){return VInvoke(t1,t2,t3,t4,t5,t6);}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5>struct VDelegate<R,T1,T2,T3,T4,T5,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl *PCdeclFun)(T1,T2,T3,T4,T5);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall *PStdCallFun)(T1,T2,T3,T4,T5);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall *PFastCallFun)(T1,T2,T3,T4,T5);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall *PClrCallFun)(T1,T2,T3,T4,T5);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5)){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2,T3,T4,T5)>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2,T3,T4,T5)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2,T3,T4,T5)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2,T3,T4,T5)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			case 5:return XTypes(new Types<T5>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 5;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5>(6);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void* t5,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						else (*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						else (*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						else (*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						else (*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
#endif
				default:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						else (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						return pr;
					}
					(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void* t5,void*const& pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2,T3,T4,T5>::Begin((typename Types<R>::Normal*)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
		}
		//同步调用
		R VInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(t1,t2,t3,t4,t5);
					(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(t1,t2,t3,t4,t5);break;
				}
				p=p->next;
			}
			return Types<R>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2,T3,T4,T5>::Begin(pr,this,&VDelegate::VInvoke,t1,t2,t3,t4,t5);
		}
		
		//operator,不推荐使用，会产生两次复制
		R operator()(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5){return VInvoke(t1,t2,t3,t4,t5);}
	};
	template<class R,class T1,class T2,class T3,class T4>struct VDelegate<R,T1,T2,T3,T4,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl *PCdeclFun)(T1,T2,T3,T4);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall *PStdCallFun)(T1,T2,T3,T4);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall *PFastCallFun)(T1,T2,T3,T4);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall *PClrCallFun)(T1,T2,T3,T4);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4)){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2,T3,T4)>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2,T3,T4)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2,T3,T4)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2,T3,T4)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4)const){ListChange(p,fun);}



		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 4;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R,T1,T2,T3,T4>(5);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						else (*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						else (*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						else (*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						else (*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
#endif
				default:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						else (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						return pr;
					}
					(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void*const& pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2,T3,T4>::Begin((typename Types<R>::Normal*)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
		}
		//同步调用
		R VInvoke(T1 t1,T2 t2,T3 t3,T4 t4)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(t1,t2,t3,t4);
					(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(t1,t2,t3,t4);break;
				}
				p=p->next;
			}
			return Types<R>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2,T3,T4>::Begin(pr,this,&VDelegate::VInvoke,t1,t2,t3,t4);
		}
		
		//operator,不推荐使用，会产生两次复制
		R operator()(T1 t1,T2 t2,T3 t3,T4 t4){return VInvoke(t1,t2,t3,t4);}
	};
	template<class R,class T1,class T2,class T3>struct VDelegate<R,T1,T2,T3,void,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl *PCdeclFun)(T1,T2,T3);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall *PStdCallFun)(T1,T2,T3);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall *PFastCallFun)(T1,T2,T3);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall *PClrCallFun)(T1,T2,T3);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3)){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2,T3)>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2,T3)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2,T3)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2,T3)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 3;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R,T1,T2,T3>(4);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						else (*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						else (*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						else (*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						else (*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
#endif
				default:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						else (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						return pr;
					}
					(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void*const& pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2,T3>::Begin((typename Types<R>::Normal*)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
		}
		//同步调用
		R VInvoke(T1 t1,T2 t2,T3 t3)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->fun)(t1,t2,t3);
					(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->fun)(t1,t2,t3);break;
				}
				p=p->next;
			}
			return Types<R>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2,T3>::Begin(pr,this,&VDelegate::VInvoke,t1,t2,t3);
		}
		
		//operator,不推荐使用，会产生两次复制
		R operator()(T1 t1,T2 t2,T3 t3){return VInvoke(t1,t2,t3);}
	};
	template<class R,class T1,class T2>struct VDelegate<R,T1,T2,void,void,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl *PCdeclFun)(T1,T2);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall *PStdCallFun)(T1,T2);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall *PFastCallFun)(T1,T2);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall *PClrCallFun)(T1,T2);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2)){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2)>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1,T2)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1,T2)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1,T2)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1,T2)const){ListChange(p,fun);}

		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 2;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R,T1,T2>(3);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						else (*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						else (*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						else (*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						else (*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
#endif
				default:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(((XBase*)((DFunList<R(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						else (((XBase*)((DFunList<R(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						return pr;
					}
					(((XBase*)((DFunList<R(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void*const& pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2>::Begin((typename Types<R>::Normal*)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
		}
		//同步调用
		R VInvoke(T1 t1,T2 t2)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2)>*)p)->fun)(t1,t2);
					(((XBase*)((DFunList<R(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2)>*)p)->fun)(t1,t2);break;
				}
				p=p->next;
			}
			return Types<R>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
			return ThreadParameters<R,VDelegate,T1,T2>::Begin(pr,this,&VDelegate::VInvoke,t1,t2);
		}
		
		//operator,不推荐使用，会产生两次复制
		R operator()(T1 t1,T2 t2){return VInvoke(t1,t2);}
	};
	template<class R,class T1>struct VDelegate<R,T1,void,void,void,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl *PCdeclFun)(T1);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall *PStdCallFun)(T1);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall *PFastCallFun)(T1);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall *PClrCallFun)(T1);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1)){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1)>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)(T1)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)(T1)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)(T1)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)(T1)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R>());
			
			case 1:return XTypes(new Types<T1>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 1;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R,T1>(2);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1));
						else (*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));
						else (*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));
						else (*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));
						else (*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
#endif
				default:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(((XBase*)((DFunList<R(XBase::*)(T1)>*)p)->pt )->*((DFunList<R(XBase::*)(T1)>*)p)->fun)(Types<T1>::PointerToReference(t1));
						else (((XBase*)((DFunList<R(XBase::*)(T1)>*)p)->pt )->*((DFunList<R(XBase::*)(T1)>*)p)->fun)(Types<T1>::PointerToReference(t1));
						return pr;
					}
					(((XBase*)((DFunList<R(XBase::*)(T1)>*)p)->pt )->*((DFunList<R(XBase::*)(T1)>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void*const& pr)
		{
			return ThreadParameters<R,VDelegate,T1>::Begin((typename Types<R>::Normal*)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1));
		}
		//同步调用
		R VInvoke(T1 t1)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R(XBase::*)(T1)>*)p)->pt )->*((DFunList<R(XBase::*)(T1)>*)p)->fun)(t1);
					(((XBase*)((DFunList<R(XBase::*)(T1)>*)p)->pt )->*((DFunList<R(XBase::*)(T1)>*)p)->fun)(t1);break;
				}
				p=p->next;
			}
			return Types<R>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
			return ThreadParameters<R,VDelegate,T1>::Begin(pr,this,&VDelegate::VInvoke,t1);
		}
		
		//operator,不推荐使用，会产生两次复制
		R operator()(T1 t1){return VInvoke(t1);}
	};
	template<class R>struct VDelegate<R,void,void,void,void,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl *PCdeclFun)();
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall *PStdCallFun)();
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall *PFastCallFun)();
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall *PClrCallFun)();
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)()){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)()>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)()>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R(T::*fun)()const){if(pFun)ListRemove(pFun);pFun=new DFunList<R(T::*)()const>();pFun->next=NULL;pFun->pt=p;((DFunList<R(T::*)()const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)()){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R(T::*fun)()const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R>());
			
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 0;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R>(1);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction();
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PCdeclFun>*)p)->fun)();
						else (*((DFunList<PCdeclFun>*)p)->fun)();
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)();break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PStdCallFun>*)p)->fun)();
						else (*((DFunList<PStdCallFun>*)p)->fun)();
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)();break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PFastCallFun>*)p)->fun)();
						else (*((DFunList<PFastCallFun>*)p)->fun)();
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)();break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(*((DFunList<PClrCallFun>*)p)->fun)();
						else (*((DFunList<PClrCallFun>*)p)->fun)();
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)();break;
#endif
				default:
					if(p->next==NULL){
						if(pr)*(typename Types<R>::Normal*)pr=(((XBase*)((DFunList<R(XBase::*)()>*)p)->pt )->*((DFunList<R(XBase::*)()>*)p)->fun)();
						else (((XBase*)((DFunList<R(XBase::*)()>*)p)->pt )->*((DFunList<R(XBase::*)()>*)p)->fun)();
						return pr;
					}
					(((XBase*)((DFunList<R(XBase::*)()>*)p)->pt )->*((DFunList<R(XBase::*)()>*)p)->fun)();break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void*const& pr)
		{
			return ThreadParameters<R,VDelegate>::Begin((typename Types<R>::Normal*)pr,this,&VDelegate::VInvoke);
		}
		//同步调用
		R VInvoke()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)();
					(*((DFunList<PCdeclFun>*)p)->fun)();break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)();
					(*((DFunList<PStdCallFun>*)p)->fun)();break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)();
					(*((DFunList<PFastCallFun>*)p)->fun)();break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)();
					(*((DFunList<PClrCallFun>*)p)->fun)();break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R(XBase::*)()>*)p)->pt )->*((DFunList<R(XBase::*)()>*)p)->fun)();
					(((XBase*)((DFunList<R(XBase::*)()>*)p)->pt )->*((DFunList<R(XBase::*)()>*)p)->fun)();break;
				}
				p=p->next;
			}
			return Types<R>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(typename ParameterPass<typename Types<R>::Normal*>::RC pr)
		{
			return ThreadParameters<R,VDelegate>::Begin(pr,this,&VDelegate::VInvoke);
		}
		
		//operator,不推荐使用，会产生两次复制
		R operator()(){return VInvoke();}
	};

	//返回值为引用
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>struct VDelegate<R&,T1,T2,T3,T4,T5,T6,T7,T8>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R&(__cdecl *PCdeclFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R&(__stdcall *PStdCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R&(__fastcall *PFastCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R&(__clrcall *PClrCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2,T3,T4,T5,T6,T7,T8)>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2,T3,T4,T5,T6,T7,T8)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2,T3,T4,T5,T6,T7,T8)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)const){ListChange(p,fun);}

		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R&>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			case 5:return XTypes(new Types<T5>());
			case 6:return XTypes(new Types<T6>());
			case 7:return XTypes(new Types<T7>());
			case 8:return XTypes(new Types<T8>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 8;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R&,T1,T2,T3,T4,T5,T6,T7,T8>(9);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R&,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void* t8,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
#endif
				default:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
						return pr;
					}
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void* t8,void*const& pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2,T3,T4,T5,T6,T7,T8>::Begin((typename Types<R&>::Normal*&)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
		}
		//同步调用
		R& VInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
				}
				p=p->next;
			}
			return Types<R&>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8,typename ParameterPass<typename Types<R&>::Normal*>::RC pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2,T3,T4,T5,T6,T7,T8>::Begin(pr,this,&VDelegate::VInvoke,t1,t2,t3,t4,t5,t6,t7,t8);
		}
		
		//operator,不推荐使用，会产生两次复制
		R& operator()(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8){return VInvoke(t1,t2,t3,t4,t5,t6,t7,t8);}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>struct VDelegate<R&,T1,T2,T3,T4,T5,T6,T7,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R&(__cdecl *PCdeclFun)(T1,T2,T3,T4,T5,T6,T7);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R&(__stdcall *PStdCallFun)(T1,T2,T3,T4,T5,T6,T7);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R&(__fastcall *PFastCallFun)(T1,T2,T3,T4,T5,T6,T7);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R&(__clrcall *PClrCallFun)(T1,T2,T3,T4,T5,T6,T7);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5,T6,T7)){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2,T3,T4,T5,T6,T7)>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2,T3,T4,T5,T6,T7)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5,T6,T7)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2,T3,T4,T5,T6,T7)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2,T3,T4,T5,T6,T7)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5,T6,T7)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5,T6,T7)const){ListChange(p,fun);}

		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R&>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			case 5:return XTypes(new Types<T5>());
			case 6:return XTypes(new Types<T6>());
			case 7:return XTypes(new Types<T7>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 7;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R&,T1,T2,T3,T4,T5,T6,T7>(8);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R&,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
#endif
				default:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
						return pr;
					}
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void*const& pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2,T3,T4,T5,T6,T7>::Begin((typename Types<R&>::Normal*&)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
		}
		//同步调用
		R& VInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
				}
				p=p->next;
			}
			return Types<R&>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,typename ParameterPass<typename Types<R&>::Normal*>::RC pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2,T3,T4,T5,T6,T7>::Begin(pr,this,&VDelegate::VInvoke,t1,t2,t3,t4,t5,t6,t7);
		}
		
		//operator,不推荐使用，会产生两次复制
		R& operator()(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7){return VInvoke(t1,t2,t3,t4,t5,t6,t7);}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6>struct VDelegate<R&,T1,T2,T3,T4,T5,T6,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R&(__cdecl *PCdeclFun)(T1,T2,T3,T4,T5,T6);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R&(__stdcall *PStdCallFun)(T1,T2,T3,T4,T5,T6);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R&(__fastcall *PFastCallFun)(T1,T2,T3,T4,T5,T6);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R&(__clrcall *PClrCallFun)(T1,T2,T3,T4,T5,T6);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5,T6)){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2,T3,T4,T5,T6)>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2,T3,T4,T5,T6)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5,T6)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2,T3,T4,T5,T6)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2,T3,T4,T5,T6)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5,T6)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5,T6)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R&>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			case 5:return XTypes(new Types<T5>());
			case 6:return XTypes(new Types<T6>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 6;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R&,T1,T2,T3,T4,T5,T6>(7);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R&,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
#endif
				default:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
						return pr;
					}
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void*const& pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2,T3,T4,T5,T6>::Begin((typename Types<R&>::Normal*&)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
		}
		//同步调用
		R& VInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
				}
				p=p->next;
			}
			return Types<R&>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,typename ParameterPass<typename Types<R&>::Normal*>::RC pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2,T3,T4,T5,T6>::Begin(pr,this,&VDelegate::VInvoke,t1,t2,t3,t4,t5,t6);
		}
		
		//operator,不推荐使用，会产生两次复制
		R& operator()(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6){return VInvoke(t1,t2,t3,t4,t5,t6);}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5>struct VDelegate<R&,T1,T2,T3,T4,T5,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R&(__cdecl *PCdeclFun)(T1,T2,T3,T4,T5);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R&(__stdcall *PStdCallFun)(T1,T2,T3,T4,T5);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R&(__fastcall *PFastCallFun)(T1,T2,T3,T4,T5);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R&(__clrcall *PClrCallFun)(T1,T2,T3,T4,T5);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5)){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2,T3,T4,T5)>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2,T3,T4,T5)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2,T3,T4,T5)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2,T3,T4,T5)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4,T5)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R&>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			case 5:return XTypes(new Types<T5>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 5;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R&,T1,T2,T3,T4,T5>(6);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R&,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void* t5,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
#endif
				default:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
						return pr;
					}
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void* t5,void*const& pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2,T3,T4,T5>::Begin((typename Types<R&>::Normal*&)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
		}
		//同步调用
		R& VInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(t1,t2,t3,t4,t5);
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(t1,t2,t3,t4,t5);break;
				}
				p=p->next;
			}
			return Types<R&>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,typename ParameterPass<typename Types<R&>::Normal*>::RC pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2,T3,T4,T5>::Begin(pr,this,&VDelegate::VInvoke,t1,t2,t3,t4,t5);
		}
		
		//operator,不推荐使用，会产生两次复制
		R& operator()(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5){return VInvoke(t1,t2,t3,t4,t5);}
	};
	template<class R,class T1,class T2,class T3,class T4>struct VDelegate<R&,T1,T2,T3,T4,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R&(__cdecl *PCdeclFun)(T1,T2,T3,T4);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R&(__stdcall *PStdCallFun)(T1,T2,T3,T4);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R&(__fastcall *PFastCallFun)(T1,T2,T3,T4);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R&(__clrcall *PClrCallFun)(T1,T2,T3,T4);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4)){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2,T3,T4)>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2,T3,T4)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2,T3,T4)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2,T3,T4)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3,T4)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R&>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 4;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R&,T1,T2,T3,T4>(5);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R&,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
#endif
				default:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
						return pr;
					}
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void*const& pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2,T3,T4>::Begin((typename Types<R&>::Normal*&)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
		}
		//同步调用
		R& VInvoke(T1 t1,T2 t2,T3 t3,T4 t4)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(t1,t2,t3,t4);
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(t1,t2,t3,t4);break;
				}
				p=p->next;
			}
			return Types<R&>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,typename ParameterPass<typename Types<R&>::Normal*>::RC pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2,T3,T4>::Begin(pr,this,&VDelegate::VInvoke,t1,t2,t3,t4);
		}
		
		//operator,不推荐使用，会产生两次复制
		R& operator()(T1 t1,T2 t2,T3 t3,T4 t4){return VInvoke(t1,t2,t3,t4);}
	};
	template<class R,class T1,class T2,class T3>struct VDelegate<R&,T1,T2,T3,void,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R&(__cdecl *PCdeclFun)(T1,T2,T3);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R&(__stdcall *PStdCallFun)(T1,T2,T3);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R&(__fastcall *PFastCallFun)(T1,T2,T3);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R&(__clrcall *PClrCallFun)(T1,T2,T3);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3)){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2,T3)>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2,T3)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2,T3)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2,T3)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2,T3)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R&>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 3;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R&,T1,T2,T3>(4);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R&,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
#endif
				default:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
						return pr;
					}
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void*const& pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2,T3>::Begin((typename Types<R&>::Normal*&)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
		}
		//同步调用
		R& VInvoke(T1 t1,T2 t2,T3 t3)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3)>*)p)->fun)(t1,t2,t3);
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2,T3)>*)p)->fun)(t1,t2,t3);break;
				}
				p=p->next;
			}
			return Types<R&>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,typename ParameterPass<typename Types<R&>::Normal*>::RC pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2,T3>::Begin(pr,this,&VDelegate::VInvoke,t1,t2,t3);
		}
		
		//operator,不推荐使用，会产生两次复制
		R& operator()(T1 t1,T2 t2,T3 t3){return VInvoke(t1,t2,t3);}
	};
	template<class R,class T1,class T2>struct VDelegate<R&,T1,T2,void,void,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R&(__cdecl *PCdeclFun)(T1,T2);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R&(__stdcall *PStdCallFun)(T1,T2);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R&(__fastcall *PFastCallFun)(T1,T2);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R&(__clrcall *PClrCallFun)(T1,T2);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2)){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2)>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1,T2)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1,T2)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1,T2)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R&>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 2;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R&,T1,T2>(3);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R&,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
#endif
				default:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(((XBase*)((DFunList<R&(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
						return pr;
					}
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void*const& pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2>::Begin((typename Types<R&>::Normal*&)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
		}
		//同步调用
		R& VInvoke(T1 t1,T2 t2)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R&(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2)>*)p)->fun)(t1,t2);
					(((XBase*)((DFunList<R&(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1,T2)>*)p)->fun)(t1,t2);break;
				}
				p=p->next;
			}
			return Types<R&>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,typename ParameterPass<typename Types<R&>::Normal*>::RC pr)
		{
			return ThreadParameters<R&,VDelegate,T1,T2>::Begin(pr,this,&VDelegate::VInvoke,t1,t2);
		}
		
		//operator,不推荐使用，会产生两次复制
		R& operator()(T1 t1,T2 t2){return VInvoke(t1,t2);}
	};
	template<class R,class T1>struct VDelegate<R&,T1,void,void,void,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R&(__cdecl *PCdeclFun)(T1);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R&(__stdcall *PStdCallFun)(T1);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R&(__fastcall *PFastCallFun)(T1);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R&(__clrcall *PClrCallFun)(T1);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1)){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1)>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)(T1)const){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)(T1)const>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)(T1)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)(T1)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R&>());
			
			case 1:return XTypes(new Types<T1>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 1;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R&,T1>(2);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R&,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1));
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
#endif
				default:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(((XBase*)((DFunList<R&(XBase::*)(T1)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1)>*)p)->fun)(Types<T1>::PointerToReference(t1));
						return pr;
					}
					(((XBase*)((DFunList<R&(XBase::*)(T1)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1)>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void*const& pr)
		{
			return ThreadParameters<R&,VDelegate,T1>::Begin((typename Types<R&>::Normal*&)pr,this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1));
		}
		//同步调用
		R& VInvoke(T1 t1)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R&(XBase::*)(T1)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1)>*)p)->fun)(t1);
					(((XBase*)((DFunList<R&(XBase::*)(T1)>*)p)->pt )->*((DFunList<R&(XBase::*)(T1)>*)p)->fun)(t1);break;
				}
				p=p->next;
			}
			return Types<R&>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,typename ParameterPass<typename Types<R&>::Normal*>::RC pr)
		{
			return ThreadParameters<R&,VDelegate,T1>::Begin(pr,this,&VDelegate::VInvoke,t1);
		}
		
		//operator,不推荐使用，会产生两次复制
		R& operator()(T1 t1){return VInvoke(t1);}
	};
	template<class R>struct VDelegate<R&,void,void,void,void,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R&(__cdecl *PCdeclFun)();
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R&(__stdcall *PStdCallFun)();
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R&(__fastcall *PFastCallFun)();
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename R&(__clrcall *PClrCallFun)();
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)()){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)()>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)()>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,R&(T::*fun)()const){if(pFun)ListRemove(pFun);pFun=new DFunList<R&(T::*)()const>();pFun->next=NULL;pFun->pt=p;((DFunList<R&(T::*)()const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)()){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,R&(T::*fun)()const){ListChange(p,fun);}

		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<R&>());
			
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 0;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<R&>(1);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<R&,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction();
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void*const& pr)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PCdeclFun>*)p)->fun)();
						return pr;
					}
					(*((DFunList<PCdeclFun>*)p)->fun)();break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PStdCallFun>*)p)->fun)();
						return pr;
					}
					(*((DFunList<PStdCallFun>*)p)->fun)();break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PFastCallFun>*)p)->fun)();
						return pr;
					}
					(*((DFunList<PFastCallFun>*)p)->fun)();break;
#endif
#ifdef _CLR
				case 3:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(*((DFunList<PClrCallFun>*)p)->fun)();
						return pr;
					}
					(*((DFunList<PClrCallFun>*)p)->fun)();break;
#endif
				default:
					if(p->next==NULL){
						(typename Types<R&>::Normal*&)pr=&(((XBase*)((DFunList<R&(XBase::*)()>*)p)->pt )->*((DFunList<R&(XBase::*)()>*)p)->fun)();
						return pr;
					}
					(((XBase*)((DFunList<R&(XBase::*)()>*)p)->pt )->*((DFunList<R&(XBase::*)()>*)p)->fun)();break;
				}
				p=p->next;
			}
			return pr;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void*const& pr)
		{
			return ThreadParameters<R&,VDelegate>::Begin((typename Types<R&>::Normal*)pr,this,&VDelegate::VInvoke);
		}
		//同步调用
		R& VInvoke()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)();
					(*((DFunList<PCdeclFun>*)p)->fun)();break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)();
					(*((DFunList<PStdCallFun>*)p)->fun)();break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)();
					(*((DFunList<PFastCallFun>*)p)->fun)();break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)();
					(*((DFunList<PClrCallFun>*)p)->fun)();break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<R&(XBase::*)()>*)p)->pt )->*((DFunList<R&(XBase::*)()>*)p)->fun)();
					(((XBase*)((DFunList<R&(XBase::*)()>*)p)->pt )->*((DFunList<R&(XBase::*)()>*)p)->fun)();break;
				}
				p=p->next;
			}
			return Types<R&>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(typename ParameterPass<typename Types<R&>::Normal*>::RC pr)
		{
			return ThreadParameters<R&,VDelegate>::Begin(pr,this,&VDelegate::VInvoke);
		}
		
		//operator,不推荐使用，会产生两次复制
		R& operator()(){return VInvoke();}
	};

	//无返回值
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>struct VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename void(__cdecl *PCdeclFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename void(__stdcall *PStdCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename void(__fastcall *PFastCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename void(__clrcall *PClrCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2,T3,T4,T5,T6,T7,T8)>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)const){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2,T3,T4,T5,T6,T7,T8)const>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2,T3,T4,T5,T6,T7,T8)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<void>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			case 5:return XTypes(new Types<T5>());
			case 6:return XTypes(new Types<T6>());
			case 7:return XTypes(new Types<T7>());
			case 8:return XTypes(new Types<T8>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 8;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7,T8>(9);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<void,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void*const& t8)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
#endif
#ifdef _CLR
				case 3:
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
#endif
				default:
					(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));break;
				}
				p=p->next;
			}
			return 0;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void*const& t8)
		{
			return ThreadParameters<void,VDelegate,T1,T2,T3,T4,T5,T6,T7,T8>::Begin(this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7),Types<T8>::PointerToReference(t8));
		}
		//同步调用
		void VInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);
					(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7,t8);break;
				}
				p=p->next;
			}
			return Types<void>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8)
		{
			return ThreadParameters<void,VDelegate,T1,T2,T3,T4,T5,T6,T7,T8>::Begin(this,&VDelegate::VInvoke,t1,t2,t3,t4,t5,t6,t7,t8);
		}
		
		//operator,不推荐使用，会产生两次复制
		void operator()(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7,T8 t8){return VInvoke(t1,t2,t3,t4,t5,t6,t7,t8);}
	};
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7>struct VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename void(__cdecl *PCdeclFun)(T1,T2,T3,T4,T5,T6,T7);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename void(__stdcall *PStdCallFun)(T1,T2,T3,T4,T5,T6,T7);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename void(__fastcall *PFastCallFun)(T1,T2,T3,T4,T5,T6,T7);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename void(__clrcall *PClrCallFun)(T1,T2,T3,T4,T5,T6,T7);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6,T7)){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2,T3,T4,T5,T6,T7)>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2,T3,T4,T5,T6,T7)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6,T7)const){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2,T3,T4,T5,T6,T7)const>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2,T3,T4,T5,T6,T7)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6,T7)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6,T7)const){ListChange(p,fun);}

		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<void>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			case 5:return XTypes(new Types<T5>());
			case 6:return XTypes(new Types<T6>());
			case 7:return XTypes(new Types<T7>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 7;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7>(8);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<void,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void*const& t7)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
#endif
#ifdef _CLR
				case 3:
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
#endif
				default:
					(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));break;
				}
				p=p->next;
			}
			return 0;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void*const& t7)
		{
			return ThreadParameters<void,VDelegate,T1,T2,T3,T4,T5,T6,T7>::Begin(this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6),Types<T7>::PointerToReference(t7));
		}
		//同步调用
		void VInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);
					(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(t1,t2,t3,t4,t5,t6,t7);break;
				}
				p=p->next;
			}
			return Types<void>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7)
		{
			return ThreadParameters<void,VDelegate,T1,T2,T3,T4,T5,T6,T7>::Begin(this,&VDelegate::VInvoke,t1,t2,t3,t4,t5,t6,t7);
		}
		
		//operator,不推荐使用，会产生两次复制
		void operator()(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6,T7 t7){return VInvoke(t1,t2,t3,t4,t5,t6,t7);}
	};
	template<class T1,class T2,class T3,class T4,class T5,class T6>struct VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename void(__cdecl *PCdeclFun)(T1,T2,T3,T4,T5,T6);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename void(__stdcall *PStdCallFun)(T1,T2,T3,T4,T5,T6);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename void(__fastcall *PFastCallFun)(T1,T2,T3,T4,T5,T6);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename void(__clrcall *PClrCallFun)(T1,T2,T3,T4,T5,T6);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6)){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2,T3,T4,T5,T6)>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2,T3,T4,T5,T6)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6)const){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2,T3,T4,T5,T6)const>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2,T3,T4,T5,T6)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<void>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			case 5:return XTypes(new Types<T5>());
			case 6:return XTypes(new Types<T6>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 6;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6>(7);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<void,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void* t5,void*const& t6)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
#endif
#ifdef _CLR
				case 3:
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
#endif
				default:
					(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));break;
				}
				p=p->next;
			}
			return 0;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void* t5,void*const& t6)
		{
			return ThreadParameters<void,VDelegate,T1,T2,T3,T4,T5,T6>::Begin(this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5),Types<T6>::PointerToReference(t6));
		}
		//同步调用
		void VInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(t1,t2,t3,t4,t5,t6);
					(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(t1,t2,t3,t4,t5,t6);break;
				}
				p=p->next;
			}
			return Types<void>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6)
		{
			return ThreadParameters<void,VDelegate,T1,T2,T3,T4,T5,T6>::Begin(this,&VDelegate::VInvoke,t1,t2,t3,t4,t5,t6);
		}
		
		//operator,不推荐使用，会产生两次复制
		void operator()(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6){return VInvoke(t1,t2,t3,t4,t5,t6);}
	};
	template<class T1,class T2,class T3,class T4,class T5>struct VDelegate<void,T1,T2,T3,T4,T5,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename void(__cdecl *PCdeclFun)(T1,T2,T3,T4,T5);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename void(__stdcall *PStdCallFun)(T1,T2,T3,T4,T5);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename void(__fastcall *PFastCallFun)(T1,T2,T3,T4,T5);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename void(__clrcall *PClrCallFun)(T1,T2,T3,T4,T5);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5)){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2,T3,T4,T5)>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2,T3,T4,T5)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5)const){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2,T3,T4,T5)const>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2,T3,T4,T5)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5)const){ListChange(p,fun);}

		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<void>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			case 5:return XTypes(new Types<T5>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 5;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5>(6);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<void,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void* t4,void*const& t5)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
#endif
#ifdef _CLR
				case 3:
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
#endif
				default:
					(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));break;
				}
				p=p->next;
			}
			return 0;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void* t4,void*const& t5)
		{
			return ThreadParameters<void,VDelegate,T1,T2,T3,T4,T5>::Begin(this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4),Types<T5>::PointerToReference(t5));
		}
		//同步调用
		void VInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4,t5);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4,t5);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4,t5);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4,t5);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(t1,t2,t3,t4,t5);
					(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(t1,t2,t3,t4,t5);break;
				}
				p=p->next;
			}
			return Types<void>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5)
		{
			return ThreadParameters<void,VDelegate,T1,T2,T3,T4,T5>::Begin(this,&VDelegate::VInvoke,t1,t2,t3,t4,t5);
		}
		
		//operator,不推荐使用，会产生两次复制
		void operator()(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5){return VInvoke(t1,t2,t3,t4,t5);}
	};
	template<class T1,class T2,class T3,class T4>struct VDelegate<void,T1,T2,T3,T4,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename void(__cdecl *PCdeclFun)(T1,T2,T3,T4);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename void(__stdcall *PStdCallFun)(T1,T2,T3,T4);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename void(__fastcall *PFastCallFun)(T1,T2,T3,T4);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename void(__clrcall *PClrCallFun)(T1,T2,T3,T4);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4)){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2,T3,T4)>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2,T3,T4)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4)const){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2,T3,T4)const>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2,T3,T4)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<void>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			case 4:return XTypes(new Types<T4>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 4;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<void,T1,T2,T3,T4>(5);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<void,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void* t3,void*const& t4)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
#endif
#ifdef _CLR
				case 3:
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
#endif
				default:
					(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));break;
				}
				p=p->next;
			}
			return 0;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void* t3,void*const& t4)
		{
			return ThreadParameters<void,VDelegate,T1,T2,T3,T4>::Begin(this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3),Types<T4>::PointerToReference(t4));
		}
		//同步调用
		void VInvoke(T1 t1,T2 t2,T3 t3,T4 t4)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3,t4);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3,t4);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3,t4);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3,t4);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(t1,t2,t3,t4);
					(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(t1,t2,t3,t4);break;
				}
				p=p->next;
			}
			return Types<void>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3,T4 t4)
		{
			return ThreadParameters<void,VDelegate,T1,T2,T3,T4>::Begin(this,&VDelegate::VInvoke,t1,t2,t3,t4);
		}
		
		//operator,不推荐使用，会产生两次复制
		void operator()(T1 t1,T2 t2,T3 t3,T4 t4){return VInvoke(t1,t2,t3,t4);}
	};
	template<class T1,class T2,class T3>struct VDelegate<void,T1,T2,T3,void,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename void(__cdecl *PCdeclFun)(T1,T2,T3);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename void(__stdcall *PStdCallFun)(T1,T2,T3);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename void(__fastcall *PFastCallFun)(T1,T2,T3);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename void(__clrcall *PClrCallFun)(T1,T2,T3);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3)){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2,T3)>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2,T3)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3)const){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2,T3)const>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2,T3)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<void>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			case 3:return XTypes(new Types<T3>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 3;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<void,T1,T2,T3>(4);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<void,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void* t2,void*const& t3)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
#endif
#ifdef _CLR
				case 3:
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
#endif
				default:
					(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));break;
				}
				p=p->next;
			}
			return 0;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void* t2,void*const& t3)
		{
			return ThreadParameters<void,VDelegate,T1,T2,T3>::Begin(this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2),Types<T3>::PointerToReference(t3));
		}
		//同步调用
		void VInvoke(T1 t1,T2 t2,T3 t3)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2,t3);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2,t3);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2,t3);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2,t3);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<void(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3)>*)p)->fun)(t1,t2,t3);
					(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3)>*)p)->fun)(t1,t2,t3);break;
				}
				p=p->next;
			}
			return Types<void>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2,T3 t3)
		{
			return ThreadParameters<void,VDelegate,T1,T2,T3>::Begin(this,&VDelegate::VInvoke,t1,t2,t3);
		}
		
		//operator,不推荐使用，会产生两次复制
		void operator()(T1 t1,T2 t2,T3 t3){return VInvoke(t1,t2,t3);}
	};
	template<class T1,class T2>struct VDelegate<void,T1,T2,void,void,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename void(__cdecl *PCdeclFun)(T1,T2);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename void(__stdcall *PStdCallFun)(T1,T2);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename void(__fastcall *PFastCallFun)(T1,T2);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename void(__clrcall *PClrCallFun)(T1,T2);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2)){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2)>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1,T2)const){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1,T2)const>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1,T2)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1,T2)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<void>());
			
			case 1:return XTypes(new Types<T1>());
			case 2:return XTypes(new Types<T2>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 2;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<void,T1,T2>(3);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<void,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*,void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void* t1,void*const& t2)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
#endif
#ifdef _CLR
				case 3:
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
#endif
				default:
					(((XBase*)((DFunList<void(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2)>*)p)->fun)(Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));break;
				}
				p=p->next;
			}
			return 0;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void* t1,void*const& t2)
		{
			return ThreadParameters<void,VDelegate,T1,T2>::Begin(this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1),Types<T2>::PointerToReference(t2));
		}
		//同步调用
		void VInvoke(T1 t1,T2 t2)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1,t2);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1,t2);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1,t2);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1,t2);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1,t2);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1,t2);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1,t2);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1,t2);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<void(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2)>*)p)->fun)(t1,t2);
					(((XBase*)((DFunList<void(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2)>*)p)->fun)(t1,t2);break;
				}
				p=p->next;
			}
			return Types<void>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1,T2 t2)
		{
			return ThreadParameters<void,VDelegate,T1,T2>::Begin(this,&VDelegate::VInvoke,t1,t2);
		}
		
		//operator,不推荐使用，会产生两次复制
		void operator()(T1 t1,T2 t2){return VInvoke(t1,t2);}
	};
	template<class T1>struct VDelegate<void,T1,void,void,void,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename void(__cdecl *PCdeclFun)(T1);
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename void(__stdcall *PStdCallFun)(T1);
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename void(__fastcall *PFastCallFun)(T1);
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef typename void(__clrcall *PClrCallFun)(T1);
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1)){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1)>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1)>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)(T1)const){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)(T1)const>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)(T1)const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1)){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)(T1)const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<void>());
			
			case 1:return XTypes(new Types<T1>());
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 1;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<void,T1>(2);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<void,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction(void*);
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke(void*const& t1)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					(*((DFunList<PCdeclFun>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					(*((DFunList<PStdCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					(*((DFunList<PFastCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
#endif
#ifdef _CLR
				case 3:
					(*((DFunList<PClrCallFun>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
#endif
				default:
					(((XBase*)((DFunList<void(XBase::*)(T1)>*)p)->pt )->*((DFunList<void(XBase::*)(T1)>*)p)->fun)(Types<T1>::PointerToReference(t1));break;
				}
				p=p->next;
			}
			return 0;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke(void*const& t1)
		{
			return ThreadParameters<void,VDelegate,T1>::Begin(this,&VDelegate::VInvoke,Types<T1>::PointerToReference(t1));
		}
		//同步调用
		void VInvoke(T1 t1)
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)(t1);
					(*((DFunList<PCdeclFun>*)p)->fun)(t1);break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)(t1);
					(*((DFunList<PStdCallFun>*)p)->fun)(t1);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)(t1);
					(*((DFunList<PFastCallFun>*)p)->fun)(t1);break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)(t1);
					(*((DFunList<PClrCallFun>*)p)->fun)(t1);break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<void(XBase::*)(T1)>*)p)->pt )->*((DFunList<void(XBase::*)(T1)>*)p)->fun)(t1);
					(((XBase*)((DFunList<void(XBase::*)(T1)>*)p)->pt )->*((DFunList<void(XBase::*)(T1)>*)p)->fun)(t1);break;
				}
				p=p->next;
			}
			return Types<void>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke(T1 t1)
		{
			return ThreadParameters<void,VDelegate,T1>::Begin(this,&VDelegate::VInvoke,t1);
		}
		
		//operator,不推荐使用，会产生两次复制
		void operator()(T1 t1){return VInvoke(t1);}
	};
	template<>struct VDelegate<void,void,void,void,void,void,void,void,void>:public IDelegate
	{
		//通用实体类型方法
		XBaseVTypeMethods_H(VDelegate);
		//复制
		VDelegate(const VDelegate& v):IDelegate(ListCopy(v.pFun)){}
		//右值
#ifdef _USE_RIGHT_VALUE_REFERENCE
		VDelegate(const VDelegate&& v)
		{
			pFun = v.pFun;
			const_cast<DFunLists*&>(v.pFun)=NULL;
		}
#endif
		//析构函数
		virtual ~VDelegate(){ListRemove(pFun);}
		//复制
		VDelegate& operator=(const VDelegate&v)
		{
			ListRemove(pFun);
			pFun = ListCopy(v.pFun);
			return *this;
		}
		
		
		//新建列表
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef void(__cdecl *PCdeclFun)();
		void ListChange(PCdeclFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PCdeclFun>();pFun->next=NULL;pFun->pt=NULL;((DFunList<PCdeclFun>*)pFun)->fun=fun;}
		VDelegate(PCdeclFun fun){ListChange(fun);}
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef void(__stdcall *PStdCallFun)();
		void ListChange(PStdCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PStdCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 1;((DFunList<PStdCallFun>*)pFun)->fun=fun;}
		VDelegate(PStdCallFun fun){ListChange(fun);}
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef void(__fastcall *PFastCallFun)();
		void ListChange(PFastCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PFastCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 2;((DFunList<PFastCallFun>*)pFun)->fun=fun;}
		VDelegate(PFastCallFun fun){ListChange(fun);}
#endif
#ifdef _CLR
		//托管函数指针类型
		typedef void(__clrcall *PClrCallFun)();
		void ListChange(PClrCallFun fun){if(pFun)ListRemove(pFun);pFun=new DFunList<PClrCallFun>();pFun->next=NULL;pFun->pt=NULL;(int&)pFun->pt = 3;((DFunList<PClrCallFun>*)pFun)->fun=fun;}
		VDelegate(PClrCallFun fun){ListChange(fun);}
#endif
		//成员函数指针类型
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)()){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)()>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)()>*)pFun)->fun=fun;}
		template<class T>void ListChange(typename Types<T>::Normal* p,void(T::*fun)()const){if(pFun)ListRemove(pFun);pFun=new DFunList<void(T::*)()const>();pFun->next=NULL;pFun->pt=p;((DFunList<void(T::*)()const>*)pFun)->fun=fun;}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)()){ListChange(p,fun);}
		template<class T>VDelegate(typename Types<T>::Normal* p,void(T::*fun)()const){ListChange(p,fun);}


		VDelegate& operator+=(const VDelegate& vd)
		{
			ListAdd(vd.pFun);
			return *this;
		}
		VDelegate& operator-=(const VDelegate& vd)
		{
			if(!pFun)return *this;
			DFunLists*p0=NULL;
			DFunLists*p1=pFun;
			DFunLists*p2=vd.pFun;
			while(p1&&p2)
			{
				int count=ListInclude(p1,p2);
				if(count>0)
				{
					while(count--)
					{
						if(p0)
						{
							p1=p1->next;
							ListRemoveOne(p0->next);
							p0->next = p1;
						}
						else
						{
							p1=p1->next;
							ListRemoveOne(pFun);
							pFun = p1;
						}
					}
					break;
				}
				p0 = p1;
				p1 = p1->next;
			}
			return *this;
		}

		//获取参数的类型id
		virtual XTypes GetParameterType(int index)const
		{
			switch(index)
			{
			case 0:return XTypes(new Types<void>());
			
			default:return XTypes(new Types<void>());
			}
		}
		//获取委托参数数量
		virtual int GetParametersCount()const{return 0;}
		//返回参数类型检查对象
		virtual TypesCheckingObject GetTypesChecking()const{return TypesCheckingObject::MakeObject<void>(1);}
		//有返回值
		virtual bool CanReturnValue()const{return !TypesEqual<void,void>::isEqual;}
		//通过传入参数来制作XActions动作
		virtual IDelegate* NewAction();
		//同步调用，如果有返回值，则可选择的接受返回值
		virtual void* Invoke()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:
					(*((DFunList<PCdeclFun>*)p)->fun)();break;
#endif
#ifdef CANUSESTDCALL
				case 1:
					(*((DFunList<PStdCallFun>*)p)->fun)();break;
#endif
#ifdef CANUSEFASTCALL
				case 2:
					(*((DFunList<PFastCallFun>*)p)->fun)();break;
#endif
#ifdef _CLR
				case 3:
					(*((DFunList<PClrCallFun>*)p)->fun)();break;
#endif
				default:
					(((XBase*)((DFunList<void(XBase::*)()>*)p)->pt )->*((DFunList<void(XBase::*)()>*)p)->fun)();break;
				}
				p=p->next;
			}
			return 0;
		}
		//异步调用，如果有返回值，则可选择的接受返回值
		virtual DWORD BeginInvoke()
		{
			return ThreadParameters<void,VDelegate>::Begin(this,&VDelegate::VInvoke);
		}
		//同步调用
		void VInvoke()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)return (*((DFunList<PCdeclFun>*)p)->fun)();
					(*((DFunList<PCdeclFun>*)p)->fun)();break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)return (*((DFunList<PStdCallFun>*)p)->fun)();
					(*((DFunList<PStdCallFun>*)p)->fun)();break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)return (*((DFunList<PFastCallFun>*)p)->fun)();
					(*((DFunList<PFastCallFun>*)p)->fun)();break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)return (*((DFunList<PClrCallFun>*)p)->fun)();
					(*((DFunList<PClrCallFun>*)p)->fun)();break;
#endif
				default:if(p->next==NULL)return (((XBase*)((DFunList<void(XBase::*)()>*)p)->pt )->*((DFunList<void(XBase::*)()>*)p)->fun)();
					(((XBase*)((DFunList<void(XBase::*)()>*)p)->pt )->*((DFunList<void(XBase::*)()>*)p)->fun)();break;
				}
				p=p->next;
			}
			return Types<void>::VoidOrWrong();
		}
		//异步调用
		DWORD VBeginInvoke()
		{
			return ThreadParameters<void,VDelegate>::Begin(this,&VDelegate::VInvoke);
		}
		
		//operator
		void operator()(){return VInvoke();}
	};

	//添加类节点信息（模板类，有继承）,比如 NodeOfRoot::Add("LJ::XArray",Types<LJ::XArray<T>>(),TypesCheckingObject::MakeObject<T>(1),typeid(LJ::XBase));
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>const XTypes& VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>>(),TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,T8>(9),typeid(LJ::IDelegate));
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>const XTypes& VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>>(),TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,void>(9),typeid(LJ::IDelegate));
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6>const XTypes& VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>>(),TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,void,void>(9),typeid(LJ::IDelegate));
	template<class R,class T1,class T2,class T3,class T4,class T5>const XTypes& VDelegate<R,T1,T2,T3,T4,T5,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R,T1,T2,T3,T4,T5,void,void,void>>(),TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,void,void,void>(9),typeid(LJ::IDelegate));
	template<class R,class T1,class T2,class T3,class T4>const XTypes& VDelegate<R,T1,T2,T3,T4,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R,T1,T2,T3,T4,void,void,void,void>>(),TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,void,void,void,void>(9),typeid(LJ::IDelegate));
	template<class R,class T1,class T2,class T3>const XTypes& VDelegate<R,T1,T2,T3,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R,T1,T2,T3,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<R,T1,T2,T3,void,void,void,void,void>(9),typeid(LJ::IDelegate));
	template<class R,class T1,class T2>const XTypes& VDelegate<R,T1,T2,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R,T1,T2,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<R,T1,T2,void,void,void,void,void,void>(9),typeid(LJ::IDelegate));
	template<class R,class T1>const XTypes& VDelegate<R,T1,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R,T1,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<R,T1,void,void,void,void,void,void,void>(9),typeid(LJ::IDelegate));
	template<class R>const XTypes& VDelegate<R,void,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R,void,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<R,void,void,void,void,void,void,void,void>(9),typeid(LJ::IDelegate));

	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>const XTypes& VDelegate<R&,T1,T2,T3,T4,T5,T6,T7,T8>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R&,T1,T2,T3,T4,T5,T6,T7,T8>>(),TypesCheckingObject::MakeObject<R&,T1,T2,T3,T4,T5,T6,T7,T8>(9),typeid(LJ::IDelegate));
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>const XTypes& VDelegate<R&,T1,T2,T3,T4,T5,T6,T7,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R&,T1,T2,T3,T4,T5,T6,T7,void>>(),TypesCheckingObject::MakeObject<R&,T1,T2,T3,T4,T5,T6,T7,void>(9),typeid(LJ::IDelegate));
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6>const XTypes& VDelegate<R&,T1,T2,T3,T4,T5,T6,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R&,T1,T2,T3,T4,T5,T6,void,void>>(),TypesCheckingObject::MakeObject<R&,T1,T2,T3,T4,T5,T6,void,void>(9),typeid(LJ::IDelegate));
	template<class R,class T1,class T2,class T3,class T4,class T5>const XTypes& VDelegate<R&,T1,T2,T3,T4,T5,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R&,T1,T2,T3,T4,T5,void,void,void>>(),TypesCheckingObject::MakeObject<R&,T1,T2,T3,T4,T5,void,void,void>(9),typeid(LJ::IDelegate));
	template<class R,class T1,class T2,class T3,class T4>const XTypes& VDelegate<R&,T1,T2,T3,T4,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R&,T1,T2,T3,T4,void,void,void,void>>(),TypesCheckingObject::MakeObject<R&,T1,T2,T3,T4,void,void,void,void>(9),typeid(LJ::IDelegate));
	template<class R,class T1,class T2,class T3>const XTypes& VDelegate<R&,T1,T2,T3,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R&,T1,T2,T3,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<R&,T1,T2,T3,void,void,void,void,void>(9),typeid(LJ::IDelegate));
	template<class R,class T1,class T2>const XTypes& VDelegate<R&,T1,T2,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R&,T1,T2,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<R&,T1,T2,void,void,void,void,void,void>(9),typeid(LJ::IDelegate));
	template<class R,class T1>const XTypes& VDelegate<R&,T1,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R&,T1,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<R&,T1,void,void,void,void,void,void,void>(9),typeid(LJ::IDelegate));
	template<class R>const XTypes& VDelegate<R&,void,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<R&,void,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<R&,void,void,void,void,void,void,void,void>(9),typeid(LJ::IDelegate));

	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>const XTypes& VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>>(),TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7,T8>(9),typeid(LJ::IDelegate));
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7>const XTypes& VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>>(),TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7,void>(9),typeid(LJ::IDelegate));
	template<class T1,class T2,class T3,class T4,class T5,class T6>const XTypes& VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>>(),TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,void,void>(9),typeid(LJ::IDelegate));
	template<class T1,class T2,class T3,class T4,class T5>const XTypes& VDelegate<void,T1,T2,T3,T4,T5,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<void,T1,T2,T3,T4,T5,void,void,void>>(),TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,void,void,void>(9),typeid(LJ::IDelegate));
	template<class T1,class T2,class T3,class T4>const XTypes& VDelegate<void,T1,T2,T3,T4,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<void,T1,T2,T3,T4,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,void,void,void,void>(9),typeid(LJ::IDelegate));
	template<class T1,class T2,class T3>const XTypes& VDelegate<void,T1,T2,T3,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<void,T1,T2,T3,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T1,T2,T3,void,void,void,void,void>(9),typeid(LJ::IDelegate));
	template<class T1,class T2>const XTypes& VDelegate<void,T1,T2,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<void,T1,T2,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T1,T2,void,void,void,void,void,void>(9),typeid(LJ::IDelegate));
	template<class T1>const XTypes& VDelegate<void,T1,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<void,T1,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T1,void,void,void,void,void,void,void>(9),typeid(LJ::IDelegate));
	const XTypes& VDelegate<void,void,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VDelegate",Types<LJ::VDelegate<void,void,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,void,void,void,void,void,void,void,void>(9),typeid(LJ::IDelegate));

	//返回值
	template<class R=void,class T1=void,class T2=void,class T3=void,class T4=void,class T5=void,class T6=void,class T7=void,class T8=void>struct VAction:public VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>
	{
		typedef typename VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
		//保存参数（智能指针）
		ParameterStore<R>pr;ParameterStore<T1>p1;ParameterStore<T2>p2;ParameterStore<T3>p3;ParameterStore<T4>p4;ParameterStore<T5>p5;ParameterStore<T6>p6;ParameterStore<T7>p7;ParameterStore<T8>p8;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)pr= (*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);
					   else(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);
					   break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)pr= (*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);
					else(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);
					break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)pr= (*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);
					else(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);
					break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)pr= (*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);
					else(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);
					break;
#endif
				default:if(p->next==NULL)pr= (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);
					else(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);
					break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 0:return pr.GetPointer();
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			case 3:return p3.GetPointer();
			case 4:return p4.GetPointer();
			case 5:return p5.GetPointer();
			case 6:return p6.GetPointer();
			case 7:return p7.GetPointer();
			case 8:return p8.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>struct VAction<R,T1,T2,T3,T4,T5,T6,T7,void>:public VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>
	{
		typedef typename VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6,T7)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
		//保存参数（智能指针）
		ParameterStore<R>pr;ParameterStore<T1>p1;ParameterStore<T2>p2;ParameterStore<T3>p3;ParameterStore<T4>p4;ParameterStore<T5>p5;ParameterStore<T6>p6;ParameterStore<T7>p7;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)pr= (*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);
					   else(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);
					   break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)pr= (*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);
					else(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);
					break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)pr= (*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);
					else(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);
					break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)pr= (*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);
					else(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);
					break;
#endif
				default:if(p->next==NULL)pr= (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);
					else(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);
					break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 0:return pr.GetPointer();
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			case 3:return p3.GetPointer();
			case 4:return p4.GetPointer();
			case 5:return p5.GetPointer();
			case 6:return p6.GetPointer();
			case 7:return p7.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6>struct VAction<R,T1,T2,T3,T4,T5,T6,void,void>:public VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>
	{
		typedef typename VDelegate<R,T1,T2,T3,T4,T5,T6,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5,T6)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
		//保存参数（智能指针）
		ParameterStore<R>pr;ParameterStore<T1>p1;ParameterStore<T2>p2;ParameterStore<T3>p3;ParameterStore<T4>p4;ParameterStore<T5>p5;ParameterStore<T6>p6;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)pr= (*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4,p5,p6);
					   else(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4,p5,p6);
					   break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)pr= (*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6);
					else(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6);
					break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)pr= (*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6);
					else(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6);
					break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)pr= (*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6);
					else(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6);
					break;
#endif
				default:if(p->next==NULL)pr= (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(p1,p2,p3,p4,p5,p6);
					else(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(p1,p2,p3,p4,p5,p6);
					break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 0:return pr.GetPointer();
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			case 3:return p3.GetPointer();
			case 4:return p4.GetPointer();
			case 5:return p5.GetPointer();
			case 6:return p6.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class R,class T1,class T2,class T3,class T4,class T5>struct VAction<R,T1,T2,T3,T4,T5,void,void,void>:public VDelegate<R,T1,T2,T3,T4,T5,void,void,void>
	{
		typedef typename VDelegate<R,T1,T2,T3,T4,T5,void,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4,T5)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
		//保存参数（智能指针）
		ParameterStore<R>pr;ParameterStore<T1>p1;ParameterStore<T2>p2;ParameterStore<T3>p3;ParameterStore<T4>p4;ParameterStore<T5>p5;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)pr= (*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4,p5);
					   else(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4,p5);
					   break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)pr= (*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4,p5);
					else(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4,p5);
					break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)pr= (*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4,p5);
					else(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4,p5);
					break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)pr= (*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4,p5);
					else(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4,p5);
					break;
#endif
				default:if(p->next==NULL)pr= (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(p1,p2,p3,p4,p5);
					else(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(p1,p2,p3,p4,p5);
					break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 0:return pr.GetPointer();
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			case 3:return p3.GetPointer();
			case 4:return p4.GetPointer();
			case 5:return p5.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class R,class T1,class T2,class T3,class T4>struct VAction<R,T1,T2,T3,T4,void,void,void,void>:public VDelegate<R,T1,T2,T3,T4,void,void,void,void>
	{
		typedef typename VDelegate<R,T1,T2,T3,T4,void,void,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4){}
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3,T4)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4){}
		//保存参数（智能指针）
		ParameterStore<R>pr;ParameterStore<T1>p1;ParameterStore<T2>p2;ParameterStore<T3>p3;ParameterStore<T4>p4;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)pr= (*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4);
					   else(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4);
					   break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)pr= (*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4);
					else(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4);
					break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)pr= (*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4);
					else(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4);
					break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)pr= (*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4);
					else(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4);
					break;
#endif
				default:if(p->next==NULL)pr= (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(p1,p2,p3,p4);
					else(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(p1,p2,p3,p4);
					break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 0:return pr.GetPointer();
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			case 3:return p3.GetPointer();
			case 4:return p4.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class R,class T1,class T2,class T3>struct VAction<R,T1,T2,T3,void,void,void,void,void>:public VDelegate<R,T1,T2,T3,void,void,void,void,void>
	{
		typedef typename VDelegate<R,T1,T2,T3,void,void,void,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3){}
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2,T3)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3){}
		//保存参数（智能指针）
		ParameterStore<R>pr;ParameterStore<T1>p1;ParameterStore<T2>p2;ParameterStore<T3>p3;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)pr= (*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3);
					   else(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3);
					   break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)pr= (*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3);
					else(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3);
					break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)pr= (*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3);
					else(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3);
					break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)pr= (*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3);
					else(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3);
					break;
#endif
				default:if(p->next==NULL)pr= (((XBase*)((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->fun)(p1,p2,p3);
					else(((XBase*)((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2,T3)>*)p)->fun)(p1,p2,p3);
					break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 0:return pr.GetPointer();
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			case 3:return p3.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class R,class T1,class T2>struct VAction<R,T1,T2,void,void,void,void,void,void>:public VDelegate<R,T1,T2,void,void,void,void,void,void>
	{
		typedef typename VDelegate<R,T1,T2,void,void,void,void,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(fun),p1(t1),p2(t2){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(fun),p1(t1),p2(t2){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(fun),p1(t1),p2(t2){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(fun),p1(t1),p2(t2){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(fun),p1(t1),p2(t2){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(p,fun),p1(t1),p2(t2){}
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1,T2)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(p,fun),p1(t1),p2(t2){}
		//保存参数（智能指针）
		ParameterStore<R>pr;ParameterStore<T1>p1;ParameterStore<T2>p2;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)pr= (*((DFunList<PCdeclFun>*)p)->fun)(p1,p2);
					   else(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2);
					   break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)pr= (*((DFunList<PStdCallFun>*)p)->fun)(p1,p2);
					else(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2);
					break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)pr= (*((DFunList<PFastCallFun>*)p)->fun)(p1,p2);
					else(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2);
					break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)pr= (*((DFunList<PClrCallFun>*)p)->fun)(p1,p2);
					else(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2);
					break;
#endif
				default:if(p->next==NULL)pr= (((XBase*)((DFunList<R(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2)>*)p)->fun)(p1,p2);
					else(((XBase*)((DFunList<R(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<R(XBase::*)(T1,T2)>*)p)->fun)(p1,p2);
					break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 0:return pr.GetPointer();
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class R,class T1>struct VAction<R,T1,void,void,void,void,void,void,void>:public VDelegate<R,T1,void,void,void,void,void,void,void>
	{
		typedef typename VDelegate<R,T1,void,void,void,void,void,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1)
			:VDelegate(fun),p1(t1){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1)
			:VDelegate(fun),p1(t1){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1)
			:VDelegate(fun),p1(t1){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1)
			:VDelegate(fun),p1(t1){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1)
			:VDelegate(fun),p1(t1){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1),typename ParameterStore<T1>::RC t1)
			:VDelegate(p,fun),p1(t1){}
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)(T1)const,typename ParameterStore<T1>::RC t1)
			:VDelegate(p,fun),p1(t1){}
		//保存参数（智能指针）
		ParameterStore<R>pr;ParameterStore<T1>p1;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)pr= (*((DFunList<PCdeclFun>*)p)->fun)(p1);
					   else(*((DFunList<PCdeclFun>*)p)->fun)(p1);
					   break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)pr= (*((DFunList<PStdCallFun>*)p)->fun)(p1);
					else(*((DFunList<PStdCallFun>*)p)->fun)(p1);
					break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)pr= (*((DFunList<PFastCallFun>*)p)->fun)(p1);
					else(*((DFunList<PFastCallFun>*)p)->fun)(p1);
					break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)pr= (*((DFunList<PClrCallFun>*)p)->fun)(p1);
					else(*((DFunList<PClrCallFun>*)p)->fun)(p1);
					break;
#endif
				default:if(p->next==NULL)pr= (((XBase*)((DFunList<R(XBase::*)(T1)>*)p)->pt )->*((DFunList<R(XBase::*)(T1)>*)p)->fun)(p1);
					else(((XBase*)((DFunList<R(XBase::*)(T1)>*)p)->pt )->*((DFunList<R(XBase::*)(T1)>*)p)->fun)(p1);
					break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 0:return pr.GetPointer();
			case 1:return p1.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class R>struct VAction<R,void,void,void,void,void,void,void,void>:public VDelegate<R,void,void,void,void,void,void,void,void>
	{
		typedef typename VDelegate<R,void,void,void,void,void,void,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun)
			:VDelegate(fun){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun)
			:VDelegate(fun){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun)
			:VDelegate(fun){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun)
			:VDelegate(fun){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun)
			:VDelegate(fun){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)())
			:VDelegate(p,fun){}
		template<class T>VAction(typename Types<T>::Normal* p,R(T::*fun)()const)
			:VDelegate(p,fun){}
		//保存参数（智能指针）
		ParameterStore<R>pr;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:if(p->next==NULL)pr= (*((DFunList<PCdeclFun>*)p)->fun)();
					   else(*((DFunList<PCdeclFun>*)p)->fun)();
					   break;
#endif
#ifdef CANUSESTDCALL
				case 1:if(p->next==NULL)pr= (*((DFunList<PStdCallFun>*)p)->fun)();
					else(*((DFunList<PStdCallFun>*)p)->fun)();
					break;
#endif
#ifdef CANUSEFASTCALL
				case 2:if(p->next==NULL)pr= (*((DFunList<PFastCallFun>*)p)->fun)();
					else(*((DFunList<PFastCallFun>*)p)->fun)();
					break;
#endif
#ifdef _CLR
				case 3:if(p->next==NULL)pr= (*((DFunList<PClrCallFun>*)p)->fun)();
					else(*((DFunList<PClrCallFun>*)p)->fun)();
					break;
#endif
				default:if(p->next==NULL)pr= (((XBase*)((DFunList<R(XBase::*)()>*)p)->pt )->*((DFunList<R(XBase::*)()>*)p)->fun)();
					else(((XBase*)((DFunList<R(XBase::*)()>*)p)->pt )->*((DFunList<R(XBase::*)()>*)p)->fun)();
					break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 0:return pr.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};

	//无返回值
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>struct VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>:public VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>
	{
		typedef typename VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7,typename ParameterStore<T8>::RC t8)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7),p8(t8){}
		//保存参数（智能指针）
		ParameterStore<T1>p1;ParameterStore<T2>p2;ParameterStore<T3>p3;ParameterStore<T4>p4;ParameterStore<T5>p5;ParameterStore<T6>p6;ParameterStore<T7>p7;ParameterStore<T8>p8;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);break;
#endif
#ifdef CANUSESTDCALL
				case 1:(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);break;
#endif
#ifdef _CLR
				case 3:(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);break;
#endif
				default:(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7,T8)>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7,p8);break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			case 3:return p3.GetPointer();
			case 4:return p4.GetPointer();
			case 5:return p5.GetPointer();
			case 6:return p6.GetPointer();
			case 7:return p7.GetPointer();
			case 8:return p8.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7>struct VAction<void,T1,T2,T3,T4,T5,T6,T7,void>:public VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>
	{
		typedef typename VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6,T7),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6,T7)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6,typename ParameterStore<T7>::RC t7)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6),p7(t7){}
		//保存参数（智能指针）
		ParameterStore<T1>p1;ParameterStore<T2>p2;ParameterStore<T3>p3;ParameterStore<T4>p4;ParameterStore<T5>p5;ParameterStore<T6>p6;ParameterStore<T7>p7;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);break;
#endif
#ifdef CANUSESTDCALL
				case 1:(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);break;
#endif
#ifdef _CLR
				case 3:(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);break;
#endif
				default:(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6,T7)>*)p)->fun)(p1,p2,p3,p4,p5,p6,p7);break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			case 3:return p3.GetPointer();
			case 4:return p4.GetPointer();
			case 5:return p5.GetPointer();
			case 6:return p6.GetPointer();
			case 7:return p7.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class T1,class T2,class T3,class T4,class T5,class T6>struct VAction<void,T1,T2,T3,T4,T5,T6,void,void>:public VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>
	{
		typedef typename VDelegate<void,T1,T2,T3,T4,T5,T6,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5,T6)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5,typename ParameterStore<T6>::RC t6)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5),p6(t6){}
		//保存参数（智能指针）
		ParameterStore<T1>p1;ParameterStore<T2>p2;ParameterStore<T3>p3;ParameterStore<T4>p4;ParameterStore<T5>p5;ParameterStore<T6>p6;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4,p5,p6);break;
#endif
#ifdef CANUSESTDCALL
				case 1:(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6);break;
#endif
#ifdef _CLR
				case 3:(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4,p5,p6);break;
#endif
				default:(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5,T6)>*)p)->fun)(p1,p2,p3,p4,p5,p6);break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			case 3:return p3.GetPointer();
			case 4:return p4.GetPointer();
			case 5:return p5.GetPointer();
			case 6:return p6.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class T1,class T2,class T3,class T4,class T5>struct VAction<void,T1,T2,T3,T4,T5,void,void,void>:public VDelegate<void,T1,T2,T3,T4,T5,void,void,void>
	{
		typedef typename VDelegate<void,T1,T2,T3,T4,T5,void,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4,T5)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4,typename ParameterStore<T5>::RC t5)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4),p5(t5){}
		//保存参数（智能指针）
		ParameterStore<T1>p1;ParameterStore<T2>p2;ParameterStore<T3>p3;ParameterStore<T4>p4;ParameterStore<T5>p5;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4,p5);break;
#endif
#ifdef CANUSESTDCALL
				case 1:(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4,p5);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4,p5);break;
#endif
#ifdef _CLR
				case 3:(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4,p5);break;
#endif
				default:(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4,T5)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4,T5)>*)p)->fun)(p1,p2,p3,p4,p5);break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			case 3:return p3.GetPointer();
			case 4:return p4.GetPointer();
			case 5:return p5.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class T1,class T2,class T3,class T4>struct VAction<void,T1,T2,T3,T4,void,void,void,void>:public VDelegate<void,T1,T2,T3,T4,void,void,void,void>
	{
		typedef typename VDelegate<void,T1,T2,T3,T4,void,void,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3),p4(t4){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4){}
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3,T4)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3,typename ParameterStore<T4>::RC t4)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3),p4(t4){}
		//保存参数（智能指针）
		ParameterStore<T1>p1;ParameterStore<T2>p2;ParameterStore<T3>p3;ParameterStore<T4>p4;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3,p4);break;
#endif
#ifdef CANUSESTDCALL
				case 1:(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3,p4);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3,p4);break;
#endif
#ifdef _CLR
				case 3:(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3,p4);break;
#endif
				default:(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3,T4)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3,T4)>*)p)->fun)(p1,p2,p3,p4);break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			case 3:return p3.GetPointer();
			case 4:return p4.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class T1,class T2,class T3>struct VAction<void,T1,T2,T3,void,void,void,void,void>:public VDelegate<void,T1,T2,T3,void,void,void,void,void>
	{
		typedef typename VDelegate<void,T1,T2,T3,void,void,void,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(fun),p1(t1),p2(t2),p3(t3){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3){}
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2,T3)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2,typename ParameterStore<T3>::RC t3)
			:VDelegate(p,fun),p1(t1),p2(t2),p3(t3){}
		//保存参数（智能指针）
		ParameterStore<T1>p1;ParameterStore<T2>p2;ParameterStore<T3>p3;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2,p3);break;
#endif
#ifdef CANUSESTDCALL
				case 1:(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2,p3);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2,p3);break;
#endif
#ifdef _CLR
				case 3:(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2,p3);break;
#endif
				default:(((XBase*)((DFunList<void(XBase::*)(T1,T2,T3)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2,T3)>*)p)->fun)(p1,p2,p3);break;
				}
				p=p->next;
			}
			return;
		}
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			case 3:return p3.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class T1,class T2>struct VAction<void,T1,T2,void,void,void,void,void,void>:public VDelegate<void,T1,T2,void,void,void,void,void,void>
	{
		typedef typename VDelegate<void,T1,T2,void,void,void,void,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(fun),p1(t1),p2(t2){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(fun),p1(t1),p2(t2){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(fun),p1(t1),p2(t2){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(fun),p1(t1),p2(t2){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(fun),p1(t1),p2(t2){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2),typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(p,fun),p1(t1),p2(t2){}
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1,T2)const,typename ParameterStore<T1>::RC t1,typename ParameterStore<T2>::RC t2)
			:VDelegate(p,fun),p1(t1),p2(t2){}
		//保存参数（智能指针）
		ParameterStore<T1>p1;ParameterStore<T2>p2;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		//同步调用
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:(*((DFunList<PCdeclFun>*)p)->fun)(p1,p2);break;
#endif
#ifdef CANUSESTDCALL
				case 1:(*((DFunList<PStdCallFun>*)p)->fun)(p1,p2);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:(*((DFunList<PFastCallFun>*)p)->fun)(p1,p2);break;
#endif
#ifdef _CLR
				case 3:(*((DFunList<PClrCallFun>*)p)->fun)(p1,p2);break;
#endif
				default:(((XBase*)((DFunList<void(XBase::*)(T1,T2)>*)p)->pt )->*((DFunList<void(XBase::*)(T1,T2)>*)p)->fun)(p1,p2);break;
				}
				p=p->next;
			}
			return;
		}
		//获取参数指针
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 1:return p1.GetPointer();
			case 2:return p2.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<class T1>struct VAction<void,T1,void,void,void,void,void,void,void>:public VDelegate<void,T1,void,void,void,void,void,void,void>
	{
		typedef typename VDelegate<void,T1,void,void,void,void,void,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate和相应参数构造
		VAction(const VDelegate& fun,typename ParameterStore<T1>::RC t1)
			:VDelegate(fun),p1(t1){}
#ifdef CANUSECDECL
		typedef typename VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun,typename ParameterStore<T1>::RC t1)
			:VDelegate(fun),p1(t1){}
#endif
#ifdef CANUSESTDCALL
		typedef typename VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun,typename ParameterStore<T1>::RC t1)
			:VDelegate(fun),p1(t1){}
#endif
#ifdef CANUSEFASTCALL
		typedef typename VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun,typename ParameterStore<T1>::RC t1)
			:VDelegate(fun),p1(t1){}
#endif
#ifdef _CLR
		typedef typename VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun,typename ParameterStore<T1>::RC t1)
			:VDelegate(fun),p1(t1){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1),typename ParameterStore<T1>::RC t1)
			:VDelegate(p,fun),p1(t1){}
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)(T1)const,typename ParameterStore<T1>::RC t1)
			:VDelegate(p,fun),p1(t1){}
		//保存参数（智能指针）
		ParameterStore<T1>p1;
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		//同步调用
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:(*((DFunList<PCdeclFun>*)p)->fun)(p1);break;
#endif
#ifdef CANUSESTDCALL
				case 1:(*((DFunList<PStdCallFun>*)p)->fun)(p1);break;
#endif
#ifdef CANUSEFASTCALL
				case 2:(*((DFunList<PFastCallFun>*)p)->fun)(p1);break;
#endif
#ifdef _CLR
				case 3:(*((DFunList<PClrCallFun>*)p)->fun)(p1);break;
#endif
				default:(((XBase*)((DFunList<void(XBase::*)(T1)>*)p)->pt )->*((DFunList<void(XBase::*)(T1)>*)p)->fun)(p1);break;
				}
				p=p->next;
			}
			return;
		}
		//获取参数指针
		virtual void* GetParameterPointer(int index)const
		{
			switch(index)
			{
			case 1:return p1.GetPointer();
			default:break;
			}
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};
	template<>struct VAction<void,void,void,void,void,void,void,void,void>:public VDelegate<void,void,void,void,void,void,void,void,void>
	{
		typedef VDelegate<void,void,void,void,void,void,void,void,void> VDelegate;
		//通用基类构造方法
		XBaseVTypeMethods_H(VAction);
		//析构函数
		virtual ~VAction(){}
		//使用Delegate
		VAction(const VDelegate& fun)
			:VDelegate(fun){}
#ifdef CANUSECDECL
		typedef VDelegate::PCdeclFun PCdeclFun;
		VAction(PCdeclFun fun)
			:VDelegate(fun){}
#endif
#ifdef CANUSESTDCALL
		typedef VDelegate::PStdCallFun PStdCallFun;
		VAction(PStdCallFun fun)
			:VDelegate(fun){}
#endif
#ifdef CANUSEFASTCALL
		typedef VDelegate::PFastCallFun PFastCallFun;
		VAction(PFastCallFun fun)
			:VDelegate(fun){}
#endif
#ifdef _CLR
		typedef VDelegate::PClrCallFun PClrCallFun;
		VAction(PClrCallFun fun)
			:VDelegate(fun){}
#endif
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)())
			:VDelegate(p,fun){}
		template<class T>VAction(typename Types<T>::Normal* p,void(T::*fun)()const)
			:VDelegate(p,fun){}
		
		//获取委托
		virtual IDelegate* NewDelegate()const{return VDelegate::NewCopy();}
		//同步调用
		virtual void Do()
		{
			DFunLists*p = pFun;
			while(p)
			{
				switch((long long)p->pt)
				{
#ifdef CANUSECDECL
				case 0:(*((DFunList<PCdeclFun>*)p)->fun)();break;
#endif
#ifdef CANUSESTDCALL
				case 1:(*((DFunList<PStdCallFun>*)p)->fun)();break;
#endif
#ifdef CANUSEFASTCALL
				case 2:(*((DFunList<PFastCallFun>*)p)->fun)();break;
#endif
#ifdef _CLR
				case 3:(*((DFunList<PClrCallFun>*)p)->fun)();break;
#endif
				default:(((XBase*)((DFunList<void(XBase::*)()>*)p)->pt )->*((DFunList<void(XBase::*)()>*)p)->fun)();break;
				}
				p=p->next;
			}
			return;
		}
		//获取参数指针
		virtual void* GetParameterPointer(int index)const
		{
			return NULL;
		}
		virtual bool IsAction()const{return true;}
	};

	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>const XTypes& VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>>(),TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,T8>(9),typeid(LJ::VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>));
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>const XTypes& VAction<R,T1,T2,T3,T4,T5,T6,T7,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<R,T1,T2,T3,T4,T5,T6,T7,void>>(),TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,T7,void>(9),typeid(LJ::VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>));
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6>const XTypes& VAction<R,T1,T2,T3,T4,T5,T6,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<R,T1,T2,T3,T4,T5,T6,void,void>>(),TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,T6,void,void>(9),typeid(LJ::VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>));
	template<class R,class T1,class T2,class T3,class T4,class T5>const XTypes& VAction<R,T1,T2,T3,T4,T5,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<R,T1,T2,T3,T4,T5,void,void,void>>(),TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,T5,void,void,void>(9),typeid(LJ::VDelegate<R,T1,T2,T3,T4,T5,void,void,void>));
	template<class R,class T1,class T2,class T3,class T4>const XTypes& VAction<R,T1,T2,T3,T4,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<R,T1,T2,T3,T4,void,void,void,void>>(),TypesCheckingObject::MakeObject<R,T1,T2,T3,T4,void,void,void,void>(9),typeid(LJ::VDelegate<R,T1,T2,T3,T4,void,void,void,void>));
	template<class R,class T1,class T2,class T3>const XTypes& VAction<R,T1,T2,T3,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<R,T1,T2,T3,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<R,T1,T2,T3,void,void,void,void,void>(9),typeid(LJ::VDelegate<R,T1,T2,T3,void,void,void,void,void>));
	template<class R,class T1,class T2>const XTypes& VAction<R,T1,T2,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<R,T1,T2,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<R,T1,T2,void,void,void,void,void,void>(9),typeid(LJ::VDelegate<R,T1,T2,void,void,void,void,void,void>));
	template<class R,class T1>const XTypes& VAction<R,T1,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<R,T1,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<R,T1,void,void,void,void,void,void,void>(9),typeid(LJ::VDelegate<R,T1,void,void,void,void,void,void,void>));
	template<class R>const XTypes& VAction<R,void,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<R,void,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<R,void,void,void,void,void,void,void,void>(9),typeid(LJ::VDelegate<R,void,void,void,void,void,void,void,void>));
	
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>const XTypes& VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>>(),TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7,T8>(9),typeid(LJ::VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>));
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7>const XTypes& VAction<void,T1,T2,T3,T4,T5,T6,T7,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<void,T1,T2,T3,T4,T5,T6,T7,void>>(),TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,T7,void>(9),typeid(LJ::VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>));
	template<class T1,class T2,class T3,class T4,class T5,class T6>const XTypes& VAction<void,T1,T2,T3,T4,T5,T6,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<void,T1,T2,T3,T4,T5,T6,void,void>>(),TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,T6,void,void>(9),typeid(LJ::VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>));
	template<class T1,class T2,class T3,class T4,class T5>const XTypes& VAction<void,T1,T2,T3,T4,T5,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<void,T1,T2,T3,T4,T5,void,void,void>>(),TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,T5,void,void,void>(9),typeid(LJ::VDelegate<void,T1,T2,T3,T4,T5,void,void,void>));
	template<class T1,class T2,class T3,class T4>const XTypes& VAction<void,T1,T2,T3,T4,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<void,T1,T2,T3,T4,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T1,T2,T3,T4,void,void,void,void>(9),typeid(LJ::VDelegate<void,T1,T2,T3,T4,void,void,void,void>));
	template<class T1,class T2,class T3>const XTypes& VAction<void,T1,T2,T3,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<void,T1,T2,T3,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T1,T2,T3,void,void,void,void,void>(9),typeid(LJ::VDelegate<void,T1,T2,T3,void,void,void,void,void>));
	template<class T1,class T2>const XTypes& VAction<void,T1,T2,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<void,T1,T2,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T1,T2,void,void,void,void,void,void>(9),typeid(LJ::VDelegate<void,T1,T2,void,void,void,void,void,void>));
	template<class T1>const XTypes& VAction<void,T1,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<void,T1,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,T1,void,void,void,void,void,void,void>(9),typeid(LJ::VDelegate<void,T1,void,void,void,void,void,void,void>));
	const XTypes& VAction<void,void,void,void,void,void,void,void,void>::CurrentType = NodeOfRoot::Add("LJ::VAction",Types<LJ::VAction<void,void,void,void,void,void,void,void,void>>(),TypesCheckingObject::MakeObject<void,void,void,void,void,void,void,void,void>(9),typeid(LJ::VDelegate<void,void,void,void,void,void,void,void,void>));


	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>IDelegate* VDelegate<R,T1,T2,T3,T4,T5,T6,T7,T8>::NewAction(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void* t8)
	{return new VAction<R,T1,T2,T3,T4,T5,T6,T7,T8>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4),ParameterStore<T5>::PointerToReference(t5),ParameterStore<T6>::PointerToReference(t6),ParameterStore<T7>::PointerToReference(t7),ParameterStore<T8>::PointerToReference(t8));}
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>IDelegate* VDelegate<R,T1,T2,T3,T4,T5,T6,T7,void>::NewAction(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7)
	{return new VAction<R,T1,T2,T3,T4,T5,T6,T7,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4),ParameterStore<T5>::PointerToReference(t5),ParameterStore<T6>::PointerToReference(t6),ParameterStore<T7>::PointerToReference(t7));}
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6>IDelegate* VDelegate<R,T1,T2,T3,T4,T5,T6,void,void>::NewAction(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6)
	{return new VAction<R,T1,T2,T3,T4,T5,T6,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4),ParameterStore<T5>::PointerToReference(t5),ParameterStore<T6>::PointerToReference(t6));}
	template<class R,class T1,class T2,class T3,class T4,class T5>IDelegate* VDelegate<R,T1,T2,T3,T4,T5,void,void,void>::NewAction(void* t1,void* t2,void* t3,void* t4,void* t5)
	{return new VAction<R,T1,T2,T3,T4,T5,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4),ParameterStore<T5>::PointerToReference(t5));}
	template<class R,class T1,class T2,class T3,class T4>IDelegate* VDelegate<R,T1,T2,T3,T4,void,void,void,void>::NewAction(void* t1,void* t2,void* t3,void* t4)
	{return new VAction<R,T1,T2,T3,T4,void,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4));}
	template<class R,class T1,class T2,class T3>IDelegate* VDelegate<R,T1,T2,T3,void,void,void,void,void>::NewAction(void* t1,void* t2,void* t3)
	{return new VAction<R,T1,T2,T3,void,void,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3));}
	template<class R,class T1,class T2>IDelegate* VDelegate<R,T1,T2,void,void,void,void,void,void>::NewAction(void* t1,void* t2)
	{return new VAction<R,T1,T2,void,void,void,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2));}
	template<class R,class T1>IDelegate* VDelegate<R,T1,void,void,void,void,void,void,void>::NewAction(void* t1)
	{return new VAction<R,T1,void,void,void,void,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1));}
	template<class R>IDelegate* VDelegate<R,void,void,void,void,void,void,void,void>::NewAction()
	{return new VAction<R,void,void,void,void,void,void,void,void>(*this);}
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>IDelegate* VDelegate<R&,T1,T2,T3,T4,T5,T6,T7,T8>::NewAction(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void* t8)
	{return new VAction<R&,T1,T2,T3,T4,T5,T6,T7,T8>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4),ParameterStore<T5>::PointerToReference(t5),ParameterStore<T6>::PointerToReference(t6),ParameterStore<T7>::PointerToReference(t7),ParameterStore<T8>::PointerToReference(t8));}
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>IDelegate* VDelegate<R&,T1,T2,T3,T4,T5,T6,T7,void>::NewAction(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7)
	{return new VAction<R&,T1,T2,T3,T4,T5,T6,T7,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4),ParameterStore<T5>::PointerToReference(t5),ParameterStore<T6>::PointerToReference(t6),ParameterStore<T7>::PointerToReference(t7));}
	template<class R,class T1,class T2,class T3,class T4,class T5,class T6>IDelegate* VDelegate<R&,T1,T2,T3,T4,T5,T6,void,void>::NewAction(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6)
	{return new VAction<R&,T1,T2,T3,T4,T5,T6,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4),ParameterStore<T5>::PointerToReference(t5),ParameterStore<T6>::PointerToReference(t6));}
	template<class R,class T1,class T2,class T3,class T4,class T5>IDelegate* VDelegate<R&,T1,T2,T3,T4,T5,void,void,void>::NewAction(void* t1,void* t2,void* t3,void* t4,void* t5)
	{return new VAction<R&,T1,T2,T3,T4,T5,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4),ParameterStore<T5>::PointerToReference(t5));}
	template<class R,class T1,class T2,class T3,class T4>IDelegate* VDelegate<R&,T1,T2,T3,T4,void,void,void,void>::NewAction(void* t1,void* t2,void* t3,void* t4)
	{return new VAction<R&,T1,T2,T3,T4,void,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4));}
	template<class R,class T1,class T2,class T3>IDelegate* VDelegate<R&,T1,T2,T3,void,void,void,void,void>::NewAction(void* t1,void* t2,void* t3)
	{return new VAction<R&,T1,T2,T3,void,void,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3));}
	template<class R,class T1,class T2>IDelegate* VDelegate<R&,T1,T2,void,void,void,void,void,void>::NewAction(void* t1,void* t2)
	{return new VAction<R&,T1,T2,void,void,void,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2));}
	template<class R,class T1>IDelegate* VDelegate<R&,T1,void,void,void,void,void,void,void>::NewAction(void* t1)
	{return new VAction<R&,T1,void,void,void,void,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1));}
	template<class R>IDelegate* VDelegate<R&,void,void,void,void,void,void,void,void>::NewAction()
	{return new VAction<R&,void,void,void,void,void,void,void,void>(*this);}
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>IDelegate* VDelegate<void,T1,T2,T3,T4,T5,T6,T7,T8>::NewAction(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7,void* t8)
	{return new VAction<void,T1,T2,T3,T4,T5,T6,T7,T8>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4),ParameterStore<T5>::PointerToReference(t5),ParameterStore<T6>::PointerToReference(t6),ParameterStore<T7>::PointerToReference(t7),ParameterStore<T8>::PointerToReference(t8));}
	template<class T1,class T2,class T3,class T4,class T5,class T6,class T7>IDelegate* VDelegate<void,T1,T2,T3,T4,T5,T6,T7,void>::NewAction(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6,void* t7)
	{return new VAction<void,T1,T2,T3,T4,T5,T6,T7,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4),ParameterStore<T5>::PointerToReference(t5),ParameterStore<T6>::PointerToReference(t6),ParameterStore<T7>::PointerToReference(t7));}
	template<class T1,class T2,class T3,class T4,class T5,class T6>IDelegate* VDelegate<void,T1,T2,T3,T4,T5,T6,void,void>::NewAction(void* t1,void* t2,void* t3,void* t4,void* t5,void* t6)
	{return new VAction<void,T1,T2,T3,T4,T5,T6,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4),ParameterStore<T5>::PointerToReference(t5),ParameterStore<T6>::PointerToReference(t6));}
	template<class T1,class T2,class T3,class T4,class T5>IDelegate* VDelegate<void,T1,T2,T3,T4,T5,void,void,void>::NewAction(void* t1,void* t2,void* t3,void* t4,void* t5)
	{return new VAction<void,T1,T2,T3,T4,T5,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4),ParameterStore<T5>::PointerToReference(t5));}
	template<class T1,class T2,class T3,class T4>IDelegate* VDelegate<void,T1,T2,T3,T4,void,void,void,void>::NewAction(void* t1,void* t2,void* t3,void* t4)
	{return new VAction<void,T1,T2,T3,T4,void,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3),ParameterStore<T4>::PointerToReference(t4));}
	template<class T1,class T2,class T3>IDelegate* VDelegate<void,T1,T2,T3,void,void,void,void,void>::NewAction(void* t1,void* t2,void* t3)
	{return new VAction<void,T1,T2,T3,void,void,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2),ParameterStore<T3>::PointerToReference(t3));}
	template<class T1,class T2>IDelegate* VDelegate<void,T1,T2,void,void,void,void,void,void>::NewAction(void* t1,void* t2)
	{return new VAction<void,T1,T2,void,void,void,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1),ParameterStore<T2>::PointerToReference(t2));}
	template<class T1>IDelegate* VDelegate<void,T1,void,void,void,void,void,void,void>::NewAction(void* t1)
	{return new VAction<void,T1,void,void,void,void,void,void,void>(*this,ParameterStore<T1>::PointerToReference(t1));}
	IDelegate* VDelegate<void,void,void,void,void,void,void,void,void>::NewAction()
	{return new VAction<void,void,void,void,void,void,void,void,void>(*this);}
}