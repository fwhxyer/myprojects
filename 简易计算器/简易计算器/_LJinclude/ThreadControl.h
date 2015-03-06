#pragma once//由W意波(LuoJun)编写
#define THREADCONTROL_
#ifndef _CLR
#define CANUSEFASTCALL
#endif
#if (_WIN64!=1)
#define CANUSECDECL
#define CANUSESTDCALL
#else//始终使用cdecl
#define CANUSECDECL
#undef CANUSEFASTCALL
#endif
namespace LJ
{
	extern DWORD APIStartThread(void (*fun)(void*),void* pragma,HANDLE* pHandle=NULL);
	template<class T>struct ParameterPass
	{
		typedef typename Types<T>::Normal const& RC;
		typedef typename Types<T>::Normal & R;
		typedef typename Types<T>::Normal N;
		typename Types<T>::Normal* p;
		ParameterPass(RC x):p(&((R)x)){}
	};
	template<class T>struct ParameterPass<const T>
	{
		typedef typename Types<T>::Normal const& RC;
		typedef typename Types<T>::Normal const& R;
		typedef typename Types<T>::Normal const N;
		typename Types<T>::Normal const * p;
		ParameterPass(RC x):p(&((R)x)){}
	};

	template<class T>struct ParameterStore
	{
		typedef typename Types<T>::Normal const& RC;
		typedef typename Types<T>::Normal & R;
		typedef typename Types<T>::Normal N;
		typename Types<T>::Normal* p;
		volatile long *ref;
		ParameterStore():p(NULL),ref(NULL){}
		ParameterStore(const ParameterStore& t):p(t.p),ref(t.ref){Increament();}
		ParameterStore(typename Types<T>::Normal* t):p(t),ref(new volatile long(1)){}
		ParameterStore(typename Types<T>::Normal const& t):p((typename Types<T>::Normal*)new T(t)),ref(new volatile long(1)){}
		~ParameterStore(){Decreament();}
		ParameterStore&operator=(const ParameterStore& t){Decreament();p=t.p;ref=t.ref;Increament();return*this;}
		operator typename Types<T>::Normal&(){return *p;}
		long Increament(){if(p)return InterlockedIncrement(ref);return NULL;}
		long Decreament(){long k=InterlockedDecrement(ref);if(k==0){delete p;delete ref;}return k;}
		void* GetPointer()const{return (void*)this;}
		static ParameterStore&PointerToReference(void*p){return *(ParameterStore*)p;}
	};
	template<class T>struct ParameterStore<T&>
	{
		typedef typename Types<T>::Normal const& RC;
		typedef typename Types<T>::Normal & R;
		typedef typename Types<T>::Normal N;
		T* p;
		ParameterStore():p(NULL){}
		ParameterStore(const ParameterStore& t):p(t.p){}
		ParameterStore(T* t):p(t){}
		ParameterStore(T const& t):p((T*)&t){}
		operator T&(){return *p;}
		void* GetPointer()const{return (void*)this;}
		static ParameterStore&PointerToReference(void*p){return *(ParameterStore*)p;}
	};
	template<class T>struct ParameterStore<T*>
	{
		typedef typename Types<T*>::Normal const& RC;
		typedef typename Types<T*>::Normal & R;
		typedef typename Types<T*>::Normal N;
		T* p;
		ParameterStore():p(NULL){}
		ParameterStore(const ParameterStore& t):p(t.p){}
		ParameterStore(T** t):p(*t){}
		ParameterStore(T* t):p(t){}
		operator T*&(){return p;}
		void* GetPointer()const{return (void*)this;}
		static ParameterStore&PointerToReference(void*p){return *(ParameterStore*)p;}
	};

#ifdef _CLR
	template<class T>struct ParameterPass<T^>
	{
		typedef typename Types<T^>::Normal RC;
		typedef typename Types<T^>::Normal R;
		typedef typename Types<T^>::Normal N;
		gcroot<T^>* p;
		ParameterPass(T^ x):p(NULL)
		{
			p=new gcroot<T^>(x);
		}
		~ParameterPass(){delete p;}
	};
	template<class T>struct ParameterPass<T^%>
	{
		typedef typename Types<T^>::Normal % RC;
		typedef typename Types<T^>::Normal %R;
		typedef typename Types<T^%>::Normal N;
		T^* p;
		ParameterPass(T^% x):p(NULL)
		{
			pin_ptr<T^> pi=&x;
			p=pi;
		}
	};

	template<class T>struct ParameterStore<T^>
	{
		typedef typename Types<T^>::Normal RC;
		typedef typename Types<T^>::Normal R;
		typedef typename Types<T^>::Normal N;
		gcroot<T^> p;//内部有个void*
		
		ParameterStore(){}
		ParameterStore(T^* t):p(*t){}
		ParameterStore(T^t):p(t){}
		operator gcroot<T^>&(){return p;}
		void* GetPointer()const{return (void*)this;}
		static ParameterStore&PointerToReference(void*p){return *(ParameterStore*)p;}
	};
	template<class T>struct ParameterStore<T^%>
	{
		typedef typename Types<T^>::Normal % RC;
		typedef typename Types<T^>::Normal %R;
		typedef typename Types<T^%>::Normal N;
		T^* p;
		ParameterStore():p(NULL){}
		ParameterStore(T^* t):p(t){}
		ParameterStore(T^% t){pin_ptr pin = &t;p = pin;}
		operator T^%(){return *p;}
		void* GetPointer()const{return (void*)this;}
		static ParameterStore&PointerToReference(void*p){return *(ParameterStore*)p;}
	};
#endif
	//函数传参,最多10个参数
	template<class F,class R,class T,class T1=void,class T2=void,class T3=void,class T4=void,class T5=void,class T6=void,class T7=void,class T8=void,class T9=void,class TA=void> struct FunParameters
	{
		//指示参数是否接收完毕
		bool * pNotOK;
		//保存函数指针
		ParameterPass<F>* pf;
		//保存返回值指针（对于void无要求）
		ParameterPass<typename Types<R>::Normal*>* pr;
		//保存调用对象指针（对于void无要求）
		ParameterPass<typename Types<T>::Normal*>* pt;
		//保存参数
		ParameterPass<T1>* pt1;
		ParameterPass<T2>* pt2;
		ParameterPass<T3>* pt3;
		ParameterPass<T4>* pt4;
		ParameterPass<T5>* pt5;
		ParameterPass<T6>* pt6;
		ParameterPass<T7>* pt7;
		ParameterPass<T8>* pt8;
		ParameterPass<T9>* pt9;
		ParameterPass<TA>* pta;
		//交换方法
		void SwapWith(FunParameters& f)
		{
			XBase::Swap(pNotOK,f.pNotOK);XBase::Swap(pf,f.pf);XBase::Swap(pr,f.pr);XBase::Swap(pt,f.pt);
			XBase::Swap(pt1,f.pt1);
			XBase::Swap(pt2,f.pt2);
			XBase::Swap(pt3,f.pt3);
			XBase::Swap(pt4,f.pt4);
			XBase::Swap(pt5,f.pt5);
			XBase::Swap(pt6,f.pt6);
			XBase::Swap(pt7,f.pt7);
			XBase::Swap(pt8,f.pt8);
			XBase::Swap(pt9,f.pt9);
			XBase::Swap(pta,f.pta);
		}
		//复制构造
		FunParameters(const FunParameters& f)
		{
			if(f.pf)pf = new ParameterPass<typename IfTypeIsGcHandle<F,F,F*>::Result>(*f.pf->p);
			if(f.pr)pr = new ParameterPass<typename Types<R>::Normal*>(*f.pr->p);
			if(f.pt)pt = new ParameterPass<typename Types<T>::Normal*>(*f.pt->p);
			pt1 = new ParameterPass<T1>(*f.pt1->p);
			pt2 = new ParameterPass<T2>(*f.pt2->p);
			pt3 = new ParameterPass<T3>(*f.pt3->p);
			pt4 = new ParameterPass<T4>(*f.pt4->p);
			pt5 = new ParameterPass<T5>(*f.pt5->p);
			pt6 = new ParameterPass<T6>(*f.pt6->p);
			pt7 = new ParameterPass<T7>(*f.pt7->p);
			pt8 = new ParameterPass<T8>(*f.pt8->p);
			pt9 = new ParameterPass<T9>(*f.pt9->p);
			pta = new ParameterPass<TA>(*f.pta->p);
		}
		//默认构造
		FunParameters():pNotOK(NULL),pf(NULL),pr(NULL),pt(NULL),pt1(NULL),pt2(NULL),pt3(NULL),pt4(NULL),pt5(NULL),pt6(NULL),pt7(NULL),pt8(NULL),pt9(NULL),pta(NULL){}
		//析构函数
		~FunParameters(){delete pf;delete pr;delete pt;delete pt1;delete pt2;delete pt3;delete pt4;delete pt5;delete pt6;delete pt7;delete pt8;delete pt9;delete pta;}
		//初始化
		FunParameters(
			bool*pok
			,typename ParameterPass<F>::RC f
			,typename ParameterPass<typename Types<R>::Normal*>::RC r
			,typename ParameterPass<typename Types<T>::Normal*>::RC t
			,typename ParameterPass<T1>::RC t1
			,typename ParameterPass<T2>::RC t2
			,typename ParameterPass<T3>::RC t3
			,typename ParameterPass<T4>::RC t4
			,typename ParameterPass<T5>::RC t5
			,typename ParameterPass<T6>::RC t6
			,typename ParameterPass<T7>::RC t7
			,typename ParameterPass<T8>::RC t8
			,typename ParameterPass<T9>::RC t9
			,typename ParameterPass<TA>::RC ta
			)
			:pNotOK(pok),
			pf(new ParameterPass<F>(f))
			,pr(r?new ParameterPass<typename Types<R>::Normal*>(r):NULL)
			,pt(t?new ParameterPass<typename Types<T>::Normal*>(t):NULL)
			,pt1(new ParameterPass<T1>(t1))
			,pt2(new ParameterPass<T2>(t2))
			,pt3(new ParameterPass<T3>(t3))
			,pt4(new ParameterPass<T4>(t4))
			,pt5(new ParameterPass<T5>(t5))
			,pt6(new ParameterPass<T6>(t6))
			,pt7(new ParameterPass<T7>(t7))
			,pt8(new ParameterPass<T8>(t8))
			,pt9(new ParameterPass<T9>(t9))
			,pta(new ParameterPass<TA>(ta))
		{}
	};
	template<class F,class R,class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9> struct FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,void>
	{
		//指示参数是否接收完毕
		bool * pNotOK;
		//保存函数指针
		ParameterPass<F>* pf;
		//保存返回值指针（对于void无要求）
		ParameterPass<typename Types<R>::Normal*>* pr;
		//保存调用对象指针（对于void无要求）
		ParameterPass<typename Types<T>::Normal*>* pt;
		//保存参数
		ParameterPass<T1>* pt1;
		ParameterPass<T2>* pt2;
		ParameterPass<T3>* pt3;
		ParameterPass<T4>* pt4;
		ParameterPass<T5>* pt5;
		ParameterPass<T6>* pt6;
		ParameterPass<T7>* pt7;
		ParameterPass<T8>* pt8;
		ParameterPass<T9>* pt9;
		//交换方法
		void SwapWith(FunParameters& f)
		{
			XBase::Swap(pNotOK,f.pNotOK);XBase::Swap(pf,f.pf);XBase::Swap(pr,f.pr);XBase::Swap(pt,f.pt);
			XBase::Swap(pt1,f.pt1);
			XBase::Swap(pt2,f.pt2);
			XBase::Swap(pt3,f.pt3);
			XBase::Swap(pt4,f.pt4);
			XBase::Swap(pt5,f.pt5);
			XBase::Swap(pt6,f.pt6);
			XBase::Swap(pt7,f.pt7);
			XBase::Swap(pt8,f.pt8);
			XBase::Swap(pt9,f.pt9);
		}
		//复制构造
		FunParameters(const FunParameters& f)
		{
			if(f.pf)pf = new ParameterPass<typename IfTypeIsGcHandle<F,F,F*>::Result>(*f.pf->p);
			if(f.pr)pr = new ParameterPass<typename Types<R>::Normal*>(*f.pr->p);
			if(f.pt)pt = new ParameterPass<typename Types<T>::Normal*>(*f.pt->p);
			pt1 = new ParameterPass<T1>(*f.pt1->p);
			pt2 = new ParameterPass<T2>(*f.pt2->p);
			pt3 = new ParameterPass<T3>(*f.pt3->p);
			pt4 = new ParameterPass<T4>(*f.pt4->p);
			pt5 = new ParameterPass<T5>(*f.pt5->p);
			pt6 = new ParameterPass<T6>(*f.pt6->p);
			pt7 = new ParameterPass<T7>(*f.pt7->p);
			pt8 = new ParameterPass<T8>(*f.pt8->p);
			pt9 = new ParameterPass<T9>(*f.pt9->p);
		}
		//默认构造
		FunParameters():pNotOK(NULL),pf(NULL),pr(NULL),pt(NULL),pt1(NULL),pt2(NULL),pt3(NULL),pt4(NULL),pt5(NULL),pt6(NULL),pt7(NULL),pt8(NULL),pt9(NULL){}
		//析构函数
		~FunParameters(){delete pf;delete pr;delete pt;delete pt1;delete pt2;delete pt3;delete pt4;delete pt5;delete pt6;delete pt7;delete pt8;delete pt9;}
		//初始化
		FunParameters(
			bool*pok
			,typename ParameterPass<F>::RC f
			,typename ParameterPass<typename Types<R>::Normal*>::RC r
			,typename ParameterPass<typename Types<T>::Normal*>::RC t
			,typename ParameterPass<T1>::RC t1
			,typename ParameterPass<T2>::RC t2
			,typename ParameterPass<T3>::RC t3
			,typename ParameterPass<T4>::RC t4
			,typename ParameterPass<T5>::RC t5
			,typename ParameterPass<T6>::RC t6
			,typename ParameterPass<T7>::RC t7
			,typename ParameterPass<T8>::RC t8
			,typename ParameterPass<T9>::RC t9
			)
			:pNotOK(pok),
			pf(new ParameterPass<F>(f))
			,pr(r?new ParameterPass<typename Types<R>::Normal*>(r):NULL)
			,pt(t?new ParameterPass<typename Types<T>::Normal*>(t):NULL)
			,pt1(new ParameterPass<T1>(t1))
			,pt2(new ParameterPass<T2>(t2))
			,pt3(new ParameterPass<T3>(t3))
			,pt4(new ParameterPass<T4>(t4))
			,pt5(new ParameterPass<T5>(t5))
			,pt6(new ParameterPass<T6>(t6))
			,pt7(new ParameterPass<T7>(t7))
			,pt8(new ParameterPass<T8>(t8))
			,pt9(new ParameterPass<T9>(t9))
		{}
	};
	template<class F,class R,class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8> struct FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,void,void>
	{
		//指示参数是否接收完毕
		bool * pNotOK;
		//保存函数指针
		ParameterPass<F>* pf;
		//保存返回值指针（对于void无要求）
		ParameterPass<typename Types<R>::Normal*>* pr;
		//保存调用对象指针（对于void无要求）
		ParameterPass<typename Types<T>::Normal*>* pt;
		//保存参数
		ParameterPass<T1>* pt1;
		ParameterPass<T2>* pt2;
		ParameterPass<T3>* pt3;
		ParameterPass<T4>* pt4;
		ParameterPass<T5>* pt5;
		ParameterPass<T6>* pt6;
		ParameterPass<T7>* pt7;
		ParameterPass<T8>* pt8;
		//交换方法
		void SwapWith(FunParameters& f)
		{
			XBase::Swap(pNotOK,f.pNotOK);XBase::Swap(pf,f.pf);XBase::Swap(pr,f.pr);XBase::Swap(pt,f.pt);
			XBase::Swap(pt1,f.pt1);
			XBase::Swap(pt2,f.pt2);
			XBase::Swap(pt3,f.pt3);
			XBase::Swap(pt4,f.pt4);
			XBase::Swap(pt5,f.pt5);
			XBase::Swap(pt6,f.pt6);
			XBase::Swap(pt7,f.pt7);
			XBase::Swap(pt8,f.pt8);
		}
		//复制构造
		FunParameters(const FunParameters& f)
		{
			if(f.pf)pf = new ParameterPass<typename IfTypeIsGcHandle<F,F,F*>::Result>(*f.pf->p);
			if(f.pr)pr = new ParameterPass<typename Types<R>::Normal*>(*f.pr->p);
			if(f.pt)pt = new ParameterPass<typename Types<T>::Normal*>(*f.pt->p);
			pt1 = new ParameterPass<T1>(*f.pt1->p);
			pt2 = new ParameterPass<T2>(*f.pt2->p);
			pt3 = new ParameterPass<T3>(*f.pt3->p);
			pt4 = new ParameterPass<T4>(*f.pt4->p);
			pt5 = new ParameterPass<T5>(*f.pt5->p);
			pt6 = new ParameterPass<T6>(*f.pt6->p);
			pt7 = new ParameterPass<T7>(*f.pt7->p);
			pt8 = new ParameterPass<T8>(*f.pt8->p);
		}
		//默认构造
		FunParameters():pNotOK(NULL),pf(NULL),pr(NULL),pt(NULL),pt1(NULL),pt2(NULL),pt3(NULL),pt4(NULL),pt5(NULL),pt6(NULL),pt7(NULL),pt8(NULL){}
		//析构函数
		~FunParameters(){delete pf;delete pr;delete pt;delete pt1;delete pt2;delete pt3;delete pt4;delete pt5;delete pt6;delete pt7;delete pt8;}
		//初始化
		FunParameters(
			bool*pok
			,typename ParameterPass<F>::RC f
			,typename ParameterPass<typename Types<R>::Normal*>::RC r
			,typename ParameterPass<typename Types<T>::Normal*>::RC t
			,typename ParameterPass<T1>::RC t1
			,typename ParameterPass<T2>::RC t2
			,typename ParameterPass<T3>::RC t3
			,typename ParameterPass<T4>::RC t4
			,typename ParameterPass<T5>::RC t5
			,typename ParameterPass<T6>::RC t6
			,typename ParameterPass<T7>::RC t7
			,typename ParameterPass<T8>::RC t8
			)
			:pNotOK(pok),
			pf(new ParameterPass<F>(f))
			,pr(r?new ParameterPass<typename Types<R>::Normal*>(r):NULL)
			,pt(t?new ParameterPass<typename Types<T>::Normal*>(t):NULL)
			,pt1(new ParameterPass<T1>(t1))
			,pt2(new ParameterPass<T2>(t2))
			,pt3(new ParameterPass<T3>(t3))
			,pt4(new ParameterPass<T4>(t4))
			,pt5(new ParameterPass<T5>(t5))
			,pt6(new ParameterPass<T6>(t6))
			,pt7(new ParameterPass<T7>(t7))
			,pt8(new ParameterPass<T8>(t8))
		{}
	};
	template<class F,class R,class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7> struct FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,void,void,void>
	{
		//指示参数是否接收完毕
		bool * pNotOK;
		//保存函数指针
		ParameterPass<F>* pf;
		//保存返回值指针（对于void无要求）
		ParameterPass<typename Types<R>::Normal*>* pr;
		//保存调用对象指针（对于void无要求）
		ParameterPass<typename Types<T>::Normal*>* pt;
		//保存参数
		ParameterPass<T1>* pt1;
		ParameterPass<T2>* pt2;
		ParameterPass<T3>* pt3;
		ParameterPass<T4>* pt4;
		ParameterPass<T5>* pt5;
		ParameterPass<T6>* pt6;
		ParameterPass<T7>* pt7;
		//交换方法
		void SwapWith(FunParameters& f)
		{
			XBase::Swap(pNotOK,f.pNotOK);XBase::Swap(pf,f.pf);XBase::Swap(pr,f.pr);XBase::Swap(pt,f.pt);
			XBase::Swap(pt1,f.pt1);
			XBase::Swap(pt2,f.pt2);
			XBase::Swap(pt3,f.pt3);
			XBase::Swap(pt4,f.pt4);
			XBase::Swap(pt5,f.pt5);
			XBase::Swap(pt6,f.pt6);
			XBase::Swap(pt7,f.pt7);
		}
		//复制构造
		FunParameters(const FunParameters& f)
		{
			if(f.pf)pf = new ParameterPass<typename IfTypeIsGcHandle<F,F,F*>::Result>(*f.pf->p);
			if(f.pr)pr = new ParameterPass<typename Types<R>::Normal*>(*f.pr->p);
			if(f.pt)pt = new ParameterPass<typename Types<T>::Normal*>(*f.pt->p);
			pt1 = new ParameterPass<T1>(*f.pt1->p);
			pt2 = new ParameterPass<T2>(*f.pt2->p);
			pt3 = new ParameterPass<T3>(*f.pt3->p);
			pt4 = new ParameterPass<T4>(*f.pt4->p);
			pt5 = new ParameterPass<T5>(*f.pt5->p);
			pt6 = new ParameterPass<T6>(*f.pt6->p);
			pt7 = new ParameterPass<T7>(*f.pt7->p);
		}
		//默认构造
		FunParameters():pNotOK(NULL),pf(NULL),pr(NULL),pt(NULL),pt1(NULL),pt2(NULL),pt3(NULL),pt4(NULL),pt5(NULL),pt6(NULL),pt7(NULL){}
		//析构函数
		~FunParameters(){delete pf;delete pr;delete pt;delete pt1;delete pt2;delete pt3;delete pt4;delete pt5;delete pt6;delete pt7;}
		//初始化
		FunParameters(
			bool*pok
			,typename ParameterPass<F>::RC f
			,typename ParameterPass<typename Types<R>::Normal*>::RC r
			,typename ParameterPass<typename Types<T>::Normal*>::RC t
			,typename ParameterPass<T1>::RC t1
			,typename ParameterPass<T2>::RC t2
			,typename ParameterPass<T3>::RC t3
			,typename ParameterPass<T4>::RC t4
			,typename ParameterPass<T5>::RC t5
			,typename ParameterPass<T6>::RC t6
			,typename ParameterPass<T7>::RC t7
			)
			:pNotOK(pok),
			pf(new ParameterPass<F>(f))
			,pr(r?new ParameterPass<typename Types<R>::Normal*>(r):NULL)
			,pt(t?new ParameterPass<typename Types<T>::Normal*>(t):NULL)
			,pt1(new ParameterPass<T1>(t1))
			,pt2(new ParameterPass<T2>(t2))
			,pt3(new ParameterPass<T3>(t3))
			,pt4(new ParameterPass<T4>(t4))
			,pt5(new ParameterPass<T5>(t5))
			,pt6(new ParameterPass<T6>(t6))
			,pt7(new ParameterPass<T7>(t7))
		{}
	};
	template<class F,class R,class T,class T1,class T2,class T3,class T4,class T5,class T6> struct FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,void,void,void,void>
	{
		//指示参数是否接收完毕
		bool * pNotOK;
		//保存函数指针
		ParameterPass<F>* pf;
		//保存返回值指针（对于void无要求）
		ParameterPass<typename Types<R>::Normal*>* pr;
		//保存调用对象指针（对于void无要求）
		ParameterPass<typename Types<T>::Normal*>* pt;
		//保存参数
		ParameterPass<T1>* pt1;
		ParameterPass<T2>* pt2;
		ParameterPass<T3>* pt3;
		ParameterPass<T4>* pt4;
		ParameterPass<T5>* pt5;
		ParameterPass<T6>* pt6;
		//交换方法
		void SwapWith(FunParameters& f)
		{
			XBase::Swap(pNotOK,f.pNotOK);XBase::Swap(pf,f.pf);XBase::Swap(pr,f.pr);XBase::Swap(pt,f.pt);
			XBase::Swap(pt1,f.pt1);
			XBase::Swap(pt2,f.pt2);
			XBase::Swap(pt3,f.pt3);
			XBase::Swap(pt4,f.pt4);
			XBase::Swap(pt5,f.pt5);
			XBase::Swap(pt6,f.pt6);
		}
		//复制构造
		FunParameters(const FunParameters& f)
		{
			if(f.pf)pf = new ParameterPass<typename IfTypeIsGcHandle<F,F,F*>::Result>(*f.pf->p);
			if(f.pr)pr = new ParameterPass<typename Types<R>::Normal*>(*f.pr->p);
			if(f.pt)pt = new ParameterPass<typename Types<T>::Normal*>(*f.pt->p);
			pt1 = new ParameterPass<T1>(*f.pt1->p);
			pt2 = new ParameterPass<T2>(*f.pt2->p);
			pt3 = new ParameterPass<T3>(*f.pt3->p);
			pt4 = new ParameterPass<T4>(*f.pt4->p);
			pt5 = new ParameterPass<T5>(*f.pt5->p);
			pt6 = new ParameterPass<T6>(*f.pt6->p);
		}
		//默认构造
		FunParameters():pNotOK(NULL),pf(NULL),pr(NULL),pt(NULL),pt1(NULL),pt2(NULL),pt3(NULL),pt4(NULL),pt5(NULL),pt6(NULL){}
		//析构函数
		~FunParameters(){delete pf;delete pr;delete pt;delete pt1;delete pt2;delete pt3;delete pt4;delete pt5;delete pt6;}
		//初始化
		FunParameters(
			bool*pok
			,typename ParameterPass<F>::RC f
			,typename ParameterPass<typename Types<R>::Normal*>::RC r
			,typename ParameterPass<typename Types<T>::Normal*>::RC t
			,typename ParameterPass<T1>::RC t1
			,typename ParameterPass<T2>::RC t2
			,typename ParameterPass<T3>::RC t3
			,typename ParameterPass<T4>::RC t4
			,typename ParameterPass<T5>::RC t5
			,typename ParameterPass<T6>::RC t6
			)
			:pNotOK(pok),
			pf(new ParameterPass<F>(f))
			,pr(r?new ParameterPass<typename Types<R>::Normal*>(r):NULL)
			,pt(t?new ParameterPass<typename Types<T>::Normal*>(t):NULL)
			,pt1(new ParameterPass<T1>(t1))
			,pt2(new ParameterPass<T2>(t2))
			,pt3(new ParameterPass<T3>(t3))
			,pt4(new ParameterPass<T4>(t4))
			,pt5(new ParameterPass<T5>(t5))
			,pt6(new ParameterPass<T6>(t6))
		{}
	};
	template<class F,class R,class T,class T1,class T2,class T3,class T4,class T5> struct FunParameters<F,R,T,T1,T2,T3,T4,T5,void,void,void,void,void>
	{
		//指示参数是否接收完毕
		bool * pNotOK;
		//保存函数指针
		ParameterPass<F>* pf;
		//保存返回值指针（对于void无要求）
		ParameterPass<typename Types<R>::Normal*>* pr;
		//保存调用对象指针（对于void无要求）
		ParameterPass<typename Types<T>::Normal*>* pt;
		//保存参数
		ParameterPass<T1>* pt1;
		ParameterPass<T2>* pt2;
		ParameterPass<T3>* pt3;
		ParameterPass<T4>* pt4;
		ParameterPass<T5>* pt5;
		//交换方法
		void SwapWith(FunParameters& f)
		{
			XBase::Swap(pNotOK,f.pNotOK);XBase::Swap(pf,f.pf);XBase::Swap(pr,f.pr);XBase::Swap(pt,f.pt);
			XBase::Swap(pt1,f.pt1);
			XBase::Swap(pt2,f.pt2);
			XBase::Swap(pt3,f.pt3);
			XBase::Swap(pt4,f.pt4);
			XBase::Swap(pt5,f.pt5);
		}
		//复制构造
		FunParameters(const FunParameters& f)
		{
			if(f.pf)pf = new ParameterPass<typename IfTypeIsGcHandle<F,F,F*>::Result>(*f.pf->p);
			if(f.pr)pr = new ParameterPass<typename Types<R>::Normal*>(*f.pr->p);
			if(f.pt)pt = new ParameterPass<typename Types<T>::Normal*>(*f.pt->p);
			pt1 = new ParameterPass<T1>(*f.pt1->p);
			pt2 = new ParameterPass<T2>(*f.pt2->p);
			pt3 = new ParameterPass<T3>(*f.pt3->p);
			pt4 = new ParameterPass<T4>(*f.pt4->p);
			pt5 = new ParameterPass<T5>(*f.pt5->p);
		}
		//默认构造
		FunParameters():pNotOK(NULL),pf(NULL),pr(NULL),pt(NULL),pt1(NULL),pt2(NULL),pt3(NULL),pt4(NULL),pt5(NULL){}
		//析构函数
		~FunParameters(){delete pf;delete pr;delete pt;delete pt1;delete pt2;delete pt3;delete pt4;delete pt5;}
		//初始化
		FunParameters(
			bool*pok
			,typename ParameterPass<F>::RC f
			,typename ParameterPass<typename Types<R>::Normal*>::RC r
			,typename ParameterPass<typename Types<T>::Normal*>::RC t
			,typename ParameterPass<T1>::RC t1
			,typename ParameterPass<T2>::RC t2
			,typename ParameterPass<T3>::RC t3
			,typename ParameterPass<T4>::RC t4
			,typename ParameterPass<T5>::RC t5
			)
			:pNotOK(pok),
			pf(new ParameterPass<F>(f))
			,pr(r?new ParameterPass<typename Types<R>::Normal*>(r):NULL)
			,pt(t?new ParameterPass<typename Types<T>::Normal*>(t):NULL)
			,pt1(new ParameterPass<T1>(t1))
			,pt2(new ParameterPass<T2>(t2))
			,pt3(new ParameterPass<T3>(t3))
			,pt4(new ParameterPass<T4>(t4))
			,pt5(new ParameterPass<T5>(t5))
		{}
	};
	template<class F,class R,class T,class T1,class T2,class T3,class T4> struct FunParameters<F,R,T,T1,T2,T3,T4,void,void,void,void,void,void>
	{
		//指示参数是否接收完毕
		bool * pNotOK;
		//保存函数指针
		ParameterPass<F>* pf;
		//保存返回值指针（对于void无要求）
		ParameterPass<typename Types<R>::Normal*>* pr;
		//保存调用对象指针（对于void无要求）
		ParameterPass<typename Types<T>::Normal*>* pt;
		//保存参数
		ParameterPass<T1>* pt1;
		ParameterPass<T2>* pt2;
		ParameterPass<T3>* pt3;
		ParameterPass<T4>* pt4;
		//交换方法
		void SwapWith(FunParameters& f)
		{
			XBase::Swap(pNotOK,f.pNotOK);XBase::Swap(pf,f.pf);XBase::Swap(pr,f.pr);XBase::Swap(pt,f.pt);
			XBase::Swap(pt1,f.pt1);
			XBase::Swap(pt2,f.pt2);
			XBase::Swap(pt3,f.pt3);
			XBase::Swap(pt4,f.pt4);
		}
		//复制构造
		FunParameters(const FunParameters& f)
		{
			if(f.pf)pf = new ParameterPass<typename IfTypeIsGcHandle<F,F,F*>::Result>(*f.pf->p);
			if(f.pr)pr = new ParameterPass<typename Types<R>::Normal*>(*f.pr->p);
			if(f.pt)pt = new ParameterPass<typename Types<T>::Normal*>(*f.pt->p);
			pt1 = new ParameterPass<T1>(*f.pt1->p);
			pt2 = new ParameterPass<T2>(*f.pt2->p);
			pt3 = new ParameterPass<T3>(*f.pt3->p);
			pt4 = new ParameterPass<T4>(*f.pt4->p);
		}
		//默认构造
		FunParameters():pNotOK(NULL),pf(NULL),pr(NULL),pt(NULL),pt1(NULL),pt2(NULL),pt3(NULL),pt4(NULL){}
		//析构函数
		~FunParameters(){delete pf;delete pr;delete pt;delete pt1;delete pt2;delete pt3;delete pt4;}
		//初始化
		FunParameters(
			bool*pok
			,typename ParameterPass<F>::RC f
			,typename ParameterPass<typename Types<R>::Normal*>::RC r
			,typename ParameterPass<typename Types<T>::Normal*>::RC t
			,typename ParameterPass<T1>::RC t1
			,typename ParameterPass<T2>::RC t2
			,typename ParameterPass<T3>::RC t3
			,typename ParameterPass<T4>::RC t4
			)
			:pNotOK(pok),
			pf(new ParameterPass<F>(f))
			,pr(r?new ParameterPass<typename Types<R>::Normal*>(r):NULL)
			,pt(t?new ParameterPass<typename Types<T>::Normal*>(t):NULL)
			,pt1(new ParameterPass<T1>(t1))
			,pt2(new ParameterPass<T2>(t2))
			,pt3(new ParameterPass<T3>(t3))
			,pt4(new ParameterPass<T4>(t4))
		{}
	};
	template<class F,class R,class T,class T1,class T2,class T3> struct FunParameters<F,R,T,T1,T2,T3,void,void,void,void,void,void,void>
	{
		//指示参数是否接收完毕
		bool * pNotOK;
		//保存函数指针
		ParameterPass<F>* pf;
		//保存返回值指针（对于void无要求）
		ParameterPass<typename Types<R>::Normal*>* pr;
		//保存调用对象指针（对于void无要求）
		ParameterPass<typename Types<T>::Normal*>* pt;
		//保存参数
		ParameterPass<T1>* pt1;
		ParameterPass<T2>* pt2;
		ParameterPass<T3>* pt3;
		//交换方法
		void SwapWith(FunParameters& f)
		{
			XBase::Swap(pNotOK,f.pNotOK);XBase::Swap(pf,f.pf);XBase::Swap(pr,f.pr);XBase::Swap(pt,f.pt);
			XBase::Swap(pt1,f.pt1);
			XBase::Swap(pt2,f.pt2);
			XBase::Swap(pt3,f.pt3);
		}
		//复制构造
		FunParameters(const FunParameters& f)
		{
			if(f.pf)pf = new ParameterPass<typename IfTypeIsGcHandle<F,F,F*>::Result>(*f.pf->p);
			if(f.pr)pr = new ParameterPass<typename Types<R>::Normal*>(*f.pr->p);
			if(f.pt)pt = new ParameterPass<typename Types<T>::Normal*>(*f.pt->p);
			pt1 = new ParameterPass<T1>(*f.pt1->p);
			pt2 = new ParameterPass<T2>(*f.pt2->p);
			pt3 = new ParameterPass<T3>(*f.pt3->p);
		}
		//默认构造
		FunParameters():pNotOK(NULL),pf(NULL),pr(NULL),pt(NULL),pt1(NULL),pt2(NULL),pt3(NULL){}
		//析构函数
		~FunParameters(){delete pf;delete pr;delete pt;delete pt1;delete pt2;delete pt3;}
		//初始化
		FunParameters(
			bool*pok
			,typename ParameterPass<F>::RC f
			,typename ParameterPass<typename Types<R>::Normal*>::RC r
			,typename ParameterPass<typename Types<T>::Normal*>::RC t
			,typename ParameterPass<T1>::RC t1
			,typename ParameterPass<T2>::RC t2
			,typename ParameterPass<T3>::RC t3
			)
			:pNotOK(pok),
			pf(new ParameterPass<F>(f))
			,pr(r?new ParameterPass<typename Types<R>::Normal*>(r):NULL)
			,pt(t?new ParameterPass<typename Types<T>::Normal*>(t):NULL)
			,pt1(new ParameterPass<T1>(t1))
			,pt2(new ParameterPass<T2>(t2))
			,pt3(new ParameterPass<T3>(t3))
		{}
	};
	template<class F,class R,class T,class T1,class T2> struct FunParameters<F,R,T,T1,T2,void,void,void,void,void,void,void,void>
	{
		//指示参数是否接收完毕
		bool * pNotOK;
		//保存函数指针
		ParameterPass<F>* pf;
		//保存返回值指针（对于void无要求）
		ParameterPass<typename Types<R>::Normal*>* pr;
		//保存调用对象指针（对于void无要求）
		ParameterPass<typename Types<T>::Normal*>* pt;
		//保存参数
		ParameterPass<T1>* pt1;
		ParameterPass<T2>* pt2;
		//交换方法
		void SwapWith(FunParameters& f)
		{
			XBase::Swap(pNotOK,f.pNotOK);XBase::Swap(pf,f.pf);XBase::Swap(pr,f.pr);XBase::Swap(pt,f.pt);
			XBase::Swap(pt1,f.pt1);XBase::Swap(pt2,f.pt2);
		}
		//复制构造
		FunParameters(const FunParameters& f)
		{
			if(f.pf)pf = new ParameterPass<typename IfTypeIsGcHandle<F,F,F*>::Result>(*f.pf->p);
			if(f.pr)pr = new ParameterPass<typename Types<R>::Normal*>(*f.pr->p);
			if(f.pt)pt = new ParameterPass<typename Types<T>::Normal*>(*f.pt->p);
			pt1 = new ParameterPass<T1>(*f.pt1->p);
			pt2 = new ParameterPass<T2>(*f.pt2->p);
		}
		//默认构造
		FunParameters():pNotOK(NULL),pf(NULL),pr(NULL),pt(NULL),pt1(NULL),pt2(NULL){}
		//析构函数
		~FunParameters(){delete pf;delete pr;delete pt;delete pt1;delete pt2;}
		//初始化
		FunParameters(
			bool*pok,
			typename ParameterPass<F>::RC f,
			typename ParameterPass<typename Types<R>::Normal*>::RC r,
			typename ParameterPass<typename Types<T>::Normal*>::RC t,
			typename ParameterPass<T1>::RC t1,
			typename ParameterPass<T2>::RC t2
			)
			:pNotOK(pok),
			pf(new ParameterPass<F>(f)),
			pr(r?new ParameterPass<typename Types<R>::Normal*>(r):NULL),
			pt(t?new ParameterPass<typename Types<T>::Normal*>(t):NULL),
			pt1(new ParameterPass<T1>(t1)),
			pt2(new ParameterPass<T2>(t2))
		{}
	};
	template<class F,class R,class T,class T1> struct FunParameters<F,R,T,T1,void,void,void,void,void,void,void,void,void>
	{
		//指示参数是否接收完毕
		bool * pNotOK;
		//保存函数指针
		ParameterPass<F>* pf;
		//保存返回值指针（对于void无要求）
		ParameterPass<typename Types<R>::Normal*>* pr;
		//保存调用对象指针（对于void无要求）
		ParameterPass<typename Types<T>::Normal*>* pt;
		//保存参数
		ParameterPass<T1>* pt1;
		//交换方法
		void SwapWith(FunParameters& f)
		{
			XBase::Swap(pNotOK,f.pNotOK);XBase::Swap(pf,f.pf);XBase::Swap(pr,f.pr);XBase::Swap(pt,f.pt);
			XBase::Swap(pt1,f.pt1);
		}
		//复制构造
		FunParameters(const FunParameters& f)
		{
			if(f.pf)pf = new ParameterPass<typename IfTypeIsGcHandle<F,F,F*>::Result>(*f.pf->p);
			if(f.pr)pr = new ParameterPass<typename Types<R>::Normal*>(*f.pr->p);
			if(f.pt)pt = new ParameterPass<typename Types<T>::Normal*>(*f.pt->p);
			pt1 = new ParameterPass<T1>(*f.pt1->p);
		}
		//默认构造
		FunParameters():pNotOK(NULL),pf(NULL),pr(NULL),pt(NULL),pt1(NULL){}
		//析构函数
		~FunParameters(){delete pf;delete pr;delete pt;delete pt1;}
		//初始化
		FunParameters(
			bool*pok,
			typename ParameterPass<F>::RC f,
			typename ParameterPass<typename Types<R>::Normal*>::RC r,
			typename ParameterPass<typename Types<T>::Normal*>::RC t,
			typename ParameterPass<T1>::RC t1
			)
			:pNotOK(pok),
			pf(new ParameterPass<F>(f)),
			pr(r?new ParameterPass<typename Types<R>::Normal*>(r):NULL),
			pt(t?new ParameterPass<typename Types<T>::Normal*>(t):NULL),
			pt1(new ParameterPass<T1>(t1))
		{}
	};
	template<class F,class R,class T> struct FunParameters<F,R,T,void,void,void,void,void,void,void,void,void,void>
	{
		//指示参数是否接收完毕
		bool * pNotOK;
		//保存函数指针
		ParameterPass<F>* pf;
		//保存返回值指针（对于void无要求）
		ParameterPass<typename Types<R>::Normal*>* pr;
		//保存调用对象指针（对于void无要求）
		ParameterPass<typename Types<T>::Normal*>* pt;
		//交换方法
		void SwapWith(FunParameters& f)
		{
			XBase::Swap(pNotOK,f.pNotOK);XBase::Swap(pf,f.pf);XBase::Swap(pr,f.pr);XBase::Swap(pt,f.pt);
		}
		//复制构造
		FunParameters(const FunParameters& f)
		{
			if(f.pf)pf = new ParameterPass<typename IfTypeIsGcHandle<F,F,F*>::Result>(*f.pf->p);
			if(f.pr)pr = new ParameterPass<typename Types<R>::Normal*>(*f.pr->p);
			if(f.pt)pt = new ParameterPass<typename Types<T>::Normal*>(*f.pt->p);
		}
		//默认构造
		FunParameters():pNotOK(NULL),pf(NULL),pr(NULL),pt(NULL){}
		//析构函数
		~FunParameters(){delete pf;delete pr;delete pt;}
		//初始化
		FunParameters(
			bool*pok
			,typename ParameterPass<F>::RC f
			,typename ParameterPass<typename Types<R>::Normal*>::RC r
			,typename ParameterPass<typename Types<T>::Normal*>::RC t
			)
			:pNotOK(pok),
			pf(new ParameterPass<F>(f))
			,pr(r?new ParameterPass<typename Types<R>::Normal*>(r):NULL)
			,pt(t?new ParameterPass<typename Types<T>::Normal*>(t):NULL)
		{}
	};
	//线程传参和启动，最多10个参数
	template<class R,class T,class T1=void,class T2=void,class T3=void,class T4=void,class T5=void,class T6=void,class T7=void,class T8=void,class T9=void,class TA=void> struct ThreadParameters
	{
		//所有函数类型定义
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl CdeclFun)(T1,T2,T3,T4,T5,T6,T7,T8,T9,TA);
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall StdCallFun)(T1,T2,T3,T4,T5,T6,T7,T8,T9,TA);
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall FastCallFun)(T1,T2,T3,T4,T5,T6,T7,T8,T9,TA);
#endif
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PThisCallFun)(T1,T2,T3,T4,T5,T6,T7,T8,T9,TA);
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PCThisCallFun)(T1,T2,T3,T4,T5,T6,T7,T8,T9,TA)const;
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall ClrCallFun)(T1,T2,T3,T4,T5,T6,T7,T8,T9,TA);
		template<class F>static void StartD(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			T9 t9 = *fp.pt9->p;
			TA ta = *fp.pta->p;
			*fp.pNotOK = false;
			f(t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);
		}
		template<class F>static void StartDR(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			T9 t9 = *fp.pt9->p;
			TA ta = *fp.pta->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = f(t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= f(t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);
			}
			else f(t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);
		}
#endif
		template<class F>static void Start(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			T9 t9 = *fp.pt9->p;
			TA ta = *fp.pta->p;
			*fp.pNotOK = false;
			(*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);
		}
		template<class F>static void StartR(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			T9 t9 = *fp.pt9->p;
			TA ta = *fp.pta->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);
			}
			else (*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);
		}
		template<class F>static void StartT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			T9 t9 = *fp.pt9->p;
			TA ta = *fp.pta->p;
			*fp.pNotOK = false;
			(t->*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);
		}
		template<class F>static void StartRT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			T9 t9 = *fp.pt9->p;
			TA ta = *fp.pta->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (t->*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (t->*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);
			}
			else (t->*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);
		}
		typedef typename IfTypeIsGcHandle<T,T,typename IfTypeIsBaseDataType<T,XBase,T>::Result*>::Result TP; 
		typedef typename IfTypeIsGcHandle<T1,T1,typename Types<T1>::Normal const&>::Result RCT1;
		typedef typename IfTypeIsGcHandle<T2,T2,typename Types<T2>::Normal const&>::Result RCT2;
		typedef typename IfTypeIsGcHandle<T3,T3,typename Types<T3>::Normal const&>::Result RCT3;
		typedef typename IfTypeIsGcHandle<T4,T4,typename Types<T4>::Normal const&>::Result RCT4;
		typedef typename IfTypeIsGcHandle<T5,T5,typename Types<T5>::Normal const&>::Result RCT5;
		typedef typename IfTypeIsGcHandle<T6,T6,typename Types<T6>::Normal const&>::Result RCT6;
		typedef typename IfTypeIsGcHandle<T7,T7,typename Types<T7>::Normal const&>::Result RCT7;
		typedef typename IfTypeIsGcHandle<T8,T8,typename Types<T8>::Normal const&>::Result RCT8;
		typedef typename IfTypeIsGcHandle<T9,T9,typename Types<T9>::Normal const&>::Result RCT9;
		typedef typename IfTypeIsGcHandle<TA,TA,typename Types<TA>::Normal const&>::Result RCTA;
#ifdef CANUSECDECL
		static DWORD Begin(CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
			pin_ptr<typename Types<RCTA>::Normal > pina =  &const_cast<typename Types<RCTA>::Normal%>(ta);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<CdeclFun>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
			pin_ptr<typename Types<RCTA>::Normal > pina =  &const_cast<typename Types<RCTA>::Normal%>(ta);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),CdeclFun>::Result>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSESTDCALL
		static DWORD Begin(StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
			pin_ptr<typename Types<RCTA>::Normal > pina =  &const_cast<typename Types<RCTA>::Normal%>(ta);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<StdCallFun>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
			pin_ptr<typename Types<RCTA>::Normal > pina =  &const_cast<typename Types<RCTA>::Normal%>(ta);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),StdCallFun>::Result>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSEFASTCALL
		static DWORD Begin(FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
			pin_ptr<typename Types<RCTA>::Normal > pina =  &const_cast<typename Types<RCTA>::Normal%>(ta);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<FastCallFun>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
			pin_ptr<typename Types<RCTA>::Normal > pina =  &const_cast<typename Types<RCTA>::Normal%>(ta);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),FastCallFun>::Result>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
		static DWORD Begin(TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
			pin_ptr<typename Types<RCTA>::Normal > pina =  &const_cast<typename Types<RCTA>::Normal%>(ta);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartT<PThisCallFun>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>(&notOK,fun,0,t,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
			pin_ptr<typename Types<RCTA>::Normal > pina =  &const_cast<typename Types<RCTA>::Normal%>(ta);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartRT<typename IfTypesEqual<R,void,int (XBase::*)(),PThisCallFun>::Result>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>(&notOK,fun,r,t,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta){return Begin(t,(PThisCallFun) fun,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta){return Begin(r,t,(PThisCallFun) fun,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);}
#ifdef _CLR
		static DWORD Begin(ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
			pin_ptr<typename Types<RCTA>::Normal > pina =  &const_cast<typename Types<RCTA>::Normal%>(ta);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<ClrCallFun>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
			pin_ptr<typename Types<RCTA>::Normal > pina =  &const_cast<typename Types<RCTA>::Normal%>(ta);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),ClrCallFun>::Result>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
			pin_ptr<typename Types<RCTA>::Normal > pina =  &const_cast<typename Types<RCTA>::Normal%>(ta);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartD<ClrDelFun^>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(typename Types<R>::Normal* const& r,ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9,RCTA ta)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
			pin_ptr<typename Types<RCTA>::Normal > pina =  &const_cast<typename Types<RCTA>::Normal%>(ta);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartDR<typename IfTypesEqual<R,void,int (),ClrDelFun^>::Result>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
	};
	template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9> struct ThreadParameters<R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,void>
	{
		//所有函数类型定义
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl CdeclFun)(T1,T2,T3,T4,T5,T6,T7,T8,T9);
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall StdCallFun)(T1,T2,T3,T4,T5,T6,T7,T8,T9);
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall FastCallFun)(T1,T2,T3,T4,T5,T6,T7,T8,T9);
#endif
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PThisCallFun)(T1,T2,T3,T4,T5,T6,T7,T8,T9);
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PCThisCallFun)(T1,T2,T3,T4,T5,T6,T7,T8,T9)const;
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall ClrCallFun)(T1,T2,T3,T4,T5,T6,T7,T8,T9);
		template<class F>static void StartD(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			T9 t9 = *fp.pt9->p;
			*fp.pNotOK = false;
			f(t1,t2,t3,t4,t5,t6,t7,t8,t9);
		}
		template<class F>static void StartDR(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			T9 t9 = *fp.pt9->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = f(t1,t2,t3,t4,t5,t6,t7,t8,t9);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= f(t1,t2,t3,t4,t5,t6,t7,t8,t9);
			}
			else f(t1,t2,t3,t4,t5,t6,t7,t8,t9);
		}
#endif
		template<class F>static void Start(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			T9 t9 = *fp.pt9->p;
			*fp.pNotOK = false;
			(*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
		}
		template<class F>static void StartR(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			T9 t9 = *fp.pt9->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
			}
			else (*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
		}
		template<class F>static void StartT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			T9 t9 = *fp.pt9->p;
			*fp.pNotOK = false;
			(t->*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
		}
		template<class F>static void StartRT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			T9 t9 = *fp.pt9->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (t->*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (t->*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
			}
			else (t->*f)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
		}
		typedef typename IfTypeIsGcHandle<T,T,typename IfTypeIsBaseDataType<T,XBase,T>::Result*>::Result TP; 
		typedef typename IfTypeIsGcHandle<T1,T1,typename Types<T1>::Normal const&>::Result RCT1;
		typedef typename IfTypeIsGcHandle<T2,T2,typename Types<T2>::Normal const&>::Result RCT2;
		typedef typename IfTypeIsGcHandle<T3,T3,typename Types<T3>::Normal const&>::Result RCT3;
		typedef typename IfTypeIsGcHandle<T4,T4,typename Types<T4>::Normal const&>::Result RCT4;
		typedef typename IfTypeIsGcHandle<T5,T5,typename Types<T5>::Normal const&>::Result RCT5;
		typedef typename IfTypeIsGcHandle<T6,T6,typename Types<T6>::Normal const&>::Result RCT6;
		typedef typename IfTypeIsGcHandle<T7,T7,typename Types<T7>::Normal const&>::Result RCT7;
		typedef typename IfTypeIsGcHandle<T8,T8,typename Types<T8>::Normal const&>::Result RCT8;
		typedef typename IfTypeIsGcHandle<T9,T9,typename Types<T9>::Normal const&>::Result RCT9;
#ifdef CANUSECDECL
		static DWORD Begin(CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<CdeclFun>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8,t9));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),CdeclFun>::Result>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8,t9));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSESTDCALL
		static DWORD Begin(StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<StdCallFun>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8,t9));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),StdCallFun>::Result>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8,t9));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSEFASTCALL
		static DWORD Begin(FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<FastCallFun>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8,t9));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),FastCallFun>::Result>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8,t9));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
		static DWORD Begin(TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartT<PThisCallFun>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>(&notOK,fun,0,t,t1,t2,t3,t4,t5,t6,t7,t8,t9));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartRT<typename IfTypesEqual<R,void,int (XBase::*)(),PThisCallFun>::Result>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>(&notOK,fun,r,t,t1,t2,t3,t4,t5,t6,t7,t8,t9));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9){return Begin(t,(PThisCallFun) fun,t1,t2,t3,t4,t5,t6,t7,t8,t9);}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9){return Begin(r,t,(PThisCallFun) fun,t1,t2,t3,t4,t5,t6,t7,t8,t9);}
#ifdef _CLR
		static DWORD Begin(ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<ClrCallFun>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8,t9));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),ClrCallFun>::Result>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8,t9));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartD<ClrDelFun^>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8,t9));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(typename Types<R>::Normal* const& r,ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8,RCT9 t9)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
			pin_ptr<typename Types<RCT9>::Normal > pin9 =  &const_cast<typename Types<RCT9>::Normal%>(t9);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartDR<typename IfTypesEqual<R,void,int (),ClrDelFun^>::Result>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4,T5,T6,T7,T8,T9>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8,t9));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
	};
	template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8> struct ThreadParameters<R,T,T1,T2,T3,T4,T5,T6,T7,T8,void,void>
	{
		//所有函数类型定义
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl CdeclFun)(T1,T2,T3,T4,T5,T6,T7,T8);
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall StdCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall FastCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
#endif
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PThisCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PCThisCallFun)(T1,T2,T3,T4,T5,T6,T7,T8)const;
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall ClrCallFun)(T1,T2,T3,T4,T5,T6,T7,T8);
		template<class F>static void StartD(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			*fp.pNotOK = false;
			f(t1,t2,t3,t4,t5,t6,t7,t8);
		}
		template<class F>static void StartDR(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = f(t1,t2,t3,t4,t5,t6,t7,t8);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= f(t1,t2,t3,t4,t5,t6,t7,t8);
			}
			else f(t1,t2,t3,t4,t5,t6,t7,t8);
		}
#endif
		template<class F>static void Start(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			*fp.pNotOK = false;
			(*f)(t1,t2,t3,t4,t5,t6,t7,t8);
		}
		template<class F>static void StartR(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7,T8>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (*f)(t1,t2,t3,t4,t5,t6,t7,t8);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (*f)(t1,t2,t3,t4,t5,t6,t7,t8);
			}
			else (*f)(t1,t2,t3,t4,t5,t6,t7,t8);
		}
		template<class F>static void StartT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			*fp.pNotOK = false;
			(t->*f)(t1,t2,t3,t4,t5,t6,t7,t8);
		}
		template<class F>static void StartRT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7,T8>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			T8 t8 = *fp.pt8->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (t->*f)(t1,t2,t3,t4,t5,t6,t7,t8);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (t->*f)(t1,t2,t3,t4,t5,t6,t7,t8);
			}
			else (t->*f)(t1,t2,t3,t4,t5,t6,t7,t8);
		}
		typedef typename IfTypeIsGcHandle<T,T,typename IfTypeIsBaseDataType<T,XBase,T>::Result*>::Result TP; 
		typedef typename IfTypeIsGcHandle<T1,T1,typename Types<T1>::Normal const&>::Result RCT1;
		typedef typename IfTypeIsGcHandle<T2,T2,typename Types<T2>::Normal const&>::Result RCT2;
		typedef typename IfTypeIsGcHandle<T3,T3,typename Types<T3>::Normal const&>::Result RCT3;
		typedef typename IfTypeIsGcHandle<T4,T4,typename Types<T4>::Normal const&>::Result RCT4;
		typedef typename IfTypeIsGcHandle<T5,T5,typename Types<T5>::Normal const&>::Result RCT5;
		typedef typename IfTypeIsGcHandle<T6,T6,typename Types<T6>::Normal const&>::Result RCT6;
		typedef typename IfTypeIsGcHandle<T7,T7,typename Types<T7>::Normal const&>::Result RCT7;
		typedef typename IfTypeIsGcHandle<T8,T8,typename Types<T8>::Normal const&>::Result RCT8;
#ifdef CANUSECDECL
		static DWORD Begin(CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<CdeclFun>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),CdeclFun>::Result>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSESTDCALL
		static DWORD Begin(StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<StdCallFun>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),StdCallFun>::Result>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSEFASTCALL
		static DWORD Begin(FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<FastCallFun>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),FastCallFun>::Result>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
		static DWORD Begin(TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartT<PThisCallFun>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4,T5,T6,T7,T8>(&notOK,fun,0,t,t1,t2,t3,t4,t5,t6,t7,t8));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartRT<typename IfTypesEqual<R,void,int (XBase::*)(),PThisCallFun>::Result>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4,T5,T6,T7,T8>(&notOK,fun,r,t,t1,t2,t3,t4,t5,t6,t7,t8));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8){return Begin(t,(PThisCallFun) fun,t1,t2,t3,t4,t5,t6,t7,t8);}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8){return Begin(r,t,(PThisCallFun) fun,t1,t2,t3,t4,t5,t6,t7,t8);}
#ifdef _CLR
		static DWORD Begin(ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<ClrCallFun>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),ClrCallFun>::Result>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7,T8>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartD<ClrDelFun^>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4,T5,T6,T7,T8>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7,t8));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(typename Types<R>::Normal* const& r,ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7,RCT8 t8)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
			pin_ptr<typename Types<RCT8>::Normal > pin8 =  &const_cast<typename Types<RCT8>::Normal%>(t8);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartDR<typename IfTypesEqual<R,void,int (),ClrDelFun^>::Result>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4,T5,T6,T7,T8>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7,t8));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
	};
	template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7> struct ThreadParameters<R,T,T1,T2,T3,T4,T5,T6,T7,void,void,void>
	{
		//所有函数类型定义
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl CdeclFun)(T1,T2,T3,T4,T5,T6,T7);
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall StdCallFun)(T1,T2,T3,T4,T5,T6,T7);
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall FastCallFun)(T1,T2,T3,T4,T5,T6,T7);
#endif
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PThisCallFun)(T1,T2,T3,T4,T5,T6,T7);
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PCThisCallFun)(T1,T2,T3,T4,T5,T6,T7)const;
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall ClrCallFun)(T1,T2,T3,T4,T5,T6,T7);
		template<class F>static void StartD(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			*fp.pNotOK = false;
			f(t1,t2,t3,t4,t5,t6,t7);
		}
		template<class F>static void StartDR(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = f(t1,t2,t3,t4,t5,t6,t7);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= f(t1,t2,t3,t4,t5,t6,t7);
			}
			else f(t1,t2,t3,t4,t5,t6,t7);
		}
#endif
		template<class F>static void Start(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			*fp.pNotOK = false;
			(*f)(t1,t2,t3,t4,t5,t6,t7);
		}
		template<class F>static void StartR(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6,T7>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (*f)(t1,t2,t3,t4,t5,t6,t7);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (*f)(t1,t2,t3,t4,t5,t6,t7);
			}
			else (*f)(t1,t2,t3,t4,t5,t6,t7);
		}
		template<class F>static void StartT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			*fp.pNotOK = false;
			(t->*f)(t1,t2,t3,t4,t5,t6,t7);
		}
		template<class F>static void StartRT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6,T7>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			T7 t7 = *fp.pt7->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (t->*f)(t1,t2,t3,t4,t5,t6,t7);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (t->*f)(t1,t2,t3,t4,t5,t6,t7);
			}
			else (t->*f)(t1,t2,t3,t4,t5,t6,t7);
		}
		typedef typename IfTypeIsGcHandle<T,T,typename IfTypeIsBaseDataType<T,XBase,T>::Result*>::Result TP; 
		typedef typename IfTypeIsGcHandle<T1,T1,typename Types<T1>::Normal const&>::Result RCT1;
		typedef typename IfTypeIsGcHandle<T2,T2,typename Types<T2>::Normal const&>::Result RCT2;
		typedef typename IfTypeIsGcHandle<T3,T3,typename Types<T3>::Normal const&>::Result RCT3;
		typedef typename IfTypeIsGcHandle<T4,T4,typename Types<T4>::Normal const&>::Result RCT4;
		typedef typename IfTypeIsGcHandle<T5,T5,typename Types<T5>::Normal const&>::Result RCT5;
		typedef typename IfTypeIsGcHandle<T6,T6,typename Types<T6>::Normal const&>::Result RCT6;
		typedef typename IfTypeIsGcHandle<T7,T7,typename Types<T7>::Normal const&>::Result RCT7;
#ifdef CANUSECDECL
		static DWORD Begin(CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<CdeclFun>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4,T5,T6,T7>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),CdeclFun>::Result>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4,T5,T6,T7>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSESTDCALL
		static DWORD Begin(StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<StdCallFun>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),StdCallFun>::Result>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSEFASTCALL
		static DWORD Begin(FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<FastCallFun>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),FastCallFun>::Result>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
		static DWORD Begin(TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartT<PThisCallFun>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4,T5,T6,T7>(&notOK,fun,0,t,t1,t2,t3,t4,t5,t6,t7));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartRT<typename IfTypesEqual<R,void,int (XBase::*)(),PThisCallFun>::Result>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4,T5,T6,T7>(&notOK,fun,r,t,t1,t2,t3,t4,t5,t6,t7));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7){return Begin(t,(PThisCallFun) fun,t1,t2,t3,t4,t5,t6,t7);}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7){return Begin(r,t,(PThisCallFun) fun,t1,t2,t3,t4,t5,t6,t7);}
#ifdef _CLR
		static DWORD Begin(ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<ClrCallFun>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),ClrCallFun>::Result>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4,T5,T6,T7>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartD<ClrDelFun^>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4,T5,T6,T7>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6,t7));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(typename Types<R>::Normal* const& r,ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6,RCT7 t7)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
			pin_ptr<typename Types<RCT7>::Normal > pin7 =  &const_cast<typename Types<RCT7>::Normal%>(t7);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartDR<typename IfTypesEqual<R,void,int (),ClrDelFun^>::Result>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4,T5,T6,T7>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6,t7));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
	};
	template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6> struct ThreadParameters<R,T,T1,T2,T3,T4,T5,T6,void,void,void,void>
	{
		//所有函数类型定义
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl CdeclFun)(T1,T2,T3,T4,T5,T6);
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall StdCallFun)(T1,T2,T3,T4,T5,T6);
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall FastCallFun)(T1,T2,T3,T4,T5,T6);
#endif
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PThisCallFun)(T1,T2,T3,T4,T5,T6);
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PCThisCallFun)(T1,T2,T3,T4,T5,T6)const;
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall ClrCallFun)(T1,T2,T3,T4,T5,T6);
		template<class F>static void StartD(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			*fp.pNotOK = false;
			f(t1,t2,t3,t4,t5,t6);
		}
		template<class F>static void StartDR(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = f(t1,t2,t3,t4,t5,t6);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= f(t1,t2,t3,t4,t5,t6);
			}
			else f(t1,t2,t3,t4,t5,t6);
		}
#endif
		template<class F>static void Start(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			*fp.pNotOK = false;
			(*f)(t1,t2,t3,t4,t5,t6);
		}
		template<class F>static void StartR(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4,T5,T6>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (*f)(t1,t2,t3,t4,t5,t6);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (*f)(t1,t2,t3,t4,t5,t6);
			}
			else (*f)(t1,t2,t3,t4,t5,t6);
		}
		template<class F>static void StartT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			*fp.pNotOK = false;
			(t->*f)(t1,t2,t3,t4,t5,t6);
		}
		template<class F>static void StartRT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5,T6> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5,T6>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5,T6>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			T6 t6 = *fp.pt6->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (t->*f)(t1,t2,t3,t4,t5,t6);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (t->*f)(t1,t2,t3,t4,t5,t6);
			}
			else (t->*f)(t1,t2,t3,t4,t5,t6);
		}
		typedef typename IfTypeIsGcHandle<T,T,typename IfTypeIsBaseDataType<T,XBase,T>::Result*>::Result TP; 
		typedef typename IfTypeIsGcHandle<T1,T1,typename Types<T1>::Normal const&>::Result RCT1;
		typedef typename IfTypeIsGcHandle<T2,T2,typename Types<T2>::Normal const&>::Result RCT2;
		typedef typename IfTypeIsGcHandle<T3,T3,typename Types<T3>::Normal const&>::Result RCT3;
		typedef typename IfTypeIsGcHandle<T4,T4,typename Types<T4>::Normal const&>::Result RCT4;
		typedef typename IfTypeIsGcHandle<T5,T5,typename Types<T5>::Normal const&>::Result RCT5;
		typedef typename IfTypeIsGcHandle<T6,T6,typename Types<T6>::Normal const&>::Result RCT6;
#ifdef CANUSECDECL
		static DWORD Begin(CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<CdeclFun>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4,T5,T6>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),CdeclFun>::Result>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4,T5,T6>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSESTDCALL
		static DWORD Begin(StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<StdCallFun>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4,T5,T6>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),StdCallFun>::Result>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4,T5,T6>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSEFASTCALL
		static DWORD Begin(FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<FastCallFun>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4,T5,T6>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),FastCallFun>::Result>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4,T5,T6>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
		static DWORD Begin(TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartT<PThisCallFun>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4,T5,T6>(&notOK,fun,0,t,t1,t2,t3,t4,t5,t6));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartRT<typename IfTypesEqual<R,void,int (XBase::*)(),PThisCallFun>::Result>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4,T5,T6>(&notOK,fun,r,t,t1,t2,t3,t4,t5,t6));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6){return Begin(t,(PThisCallFun) fun,t1,t2,t3,t4,t5,t6);}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6){return Begin(r,t,(PThisCallFun) fun,t1,t2,t3,t4,t5,t6);}
#ifdef _CLR
		static DWORD Begin(ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<ClrCallFun>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4,T5,T6>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),ClrCallFun>::Result>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4,T5,T6>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartD<ClrDelFun^>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4,T5,T6>(&notOK,fun,0,0,t1,t2,t3,t4,t5,t6));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(typename Types<R>::Normal* const& r,ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5,RCT6 t6)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
			pin_ptr<typename Types<RCT6>::Normal > pin6 =  &const_cast<typename Types<RCT6>::Normal%>(t6);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartDR<typename IfTypesEqual<R,void,int (),ClrDelFun^>::Result>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4,T5,T6>(&notOK,fun,r,0,t1,t2,t3,t4,t5,t6));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
	};
	template<class R,class T,class T1,class T2,class T3,class T4,class T5> struct ThreadParameters<R,T,T1,T2,T3,T4,T5,void,void,void,void,void>
	{
		//所有函数类型定义
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl CdeclFun)(T1,T2,T3,T4,T5);
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall StdCallFun)(T1,T2,T3,T4,T5);
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall FastCallFun)(T1,T2,T3,T4,T5);
#endif
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PThisCallFun)(T1,T2,T3,T4,T5);
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PCThisCallFun)(T1,T2,T3,T4,T5)const;
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall ClrCallFun)(T1,T2,T3,T4,T5);
		template<class F>static void StartD(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			*fp.pNotOK = false;
			f(t1,t2,t3,t4,t5);
		}
		template<class F>static void StartDR(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = f(t1,t2,t3,t4,t5);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= f(t1,t2,t3,t4,t5);
			}
			else f(t1,t2,t3,t4,t5);
		}
#endif
		template<class F>static void Start(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4,T5> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4,T5>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4,T5>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			*fp.pNotOK = false;
			(*f)(t1,t2,t3,t4,t5);
		}
		template<class F>static void StartR(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4,T5> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4,T5>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4,T5>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (*f)(t1,t2,t3,t4,t5);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (*f)(t1,t2,t3,t4,t5);
			}
			else (*f)(t1,t2,t3,t4,t5);
		}
		template<class F>static void StartT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			*fp.pNotOK = false;
			(t->*f)(t1,t2,t3,t4,t5);
		}
		template<class F>static void StartRT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4,T5> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4,T5>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4,T5>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			T5 t5 = *fp.pt5->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (t->*f)(t1,t2,t3,t4,t5);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (t->*f)(t1,t2,t3,t4,t5);
			}
			else (t->*f)(t1,t2,t3,t4,t5);
		}
		typedef typename IfTypeIsGcHandle<T,T,typename IfTypeIsBaseDataType<T,XBase,T>::Result*>::Result TP; 
		typedef typename IfTypeIsGcHandle<T1,T1,typename Types<T1>::Normal const&>::Result RCT1;
		typedef typename IfTypeIsGcHandle<T2,T2,typename Types<T2>::Normal const&>::Result RCT2;
		typedef typename IfTypeIsGcHandle<T3,T3,typename Types<T3>::Normal const&>::Result RCT3;
		typedef typename IfTypeIsGcHandle<T4,T4,typename Types<T4>::Normal const&>::Result RCT4;
		typedef typename IfTypeIsGcHandle<T5,T5,typename Types<T5>::Normal const&>::Result RCT5;
#ifdef CANUSECDECL
		static DWORD Begin(CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<CdeclFun>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4,T5>(&notOK,fun,0,0,t1,t2,t3,t4,t5));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),CdeclFun>::Result>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4,T5>(&notOK,fun,r,0,t1,t2,t3,t4,t5));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSESTDCALL
		static DWORD Begin(StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<StdCallFun>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4,T5>(&notOK,fun,0,0,t1,t2,t3,t4,t5));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),StdCallFun>::Result>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4,T5>(&notOK,fun,r,0,t1,t2,t3,t4,t5));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSEFASTCALL
		static DWORD Begin(FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<FastCallFun>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4,T5>(&notOK,fun,0,0,t1,t2,t3,t4,t5));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),FastCallFun>::Result>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4,T5>(&notOK,fun,r,0,t1,t2,t3,t4,t5));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
		static DWORD Begin(TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartT<PThisCallFun>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4,T5>(&notOK,fun,0,t,t1,t2,t3,t4,t5));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartRT<typename IfTypesEqual<R,void,int (XBase::*)(),PThisCallFun>::Result>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4,T5>(&notOK,fun,r,t,t1,t2,t3,t4,t5));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5){return Begin(t,(PThisCallFun) fun,t1,t2,t3,t4,t5);}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5){return Begin(r,t,(PThisCallFun) fun,t1,t2,t3,t4,t5);}
#ifdef _CLR
		static DWORD Begin(ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<ClrCallFun>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4,T5>(&notOK,fun,0,0,t1,t2,t3,t4,t5));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),ClrCallFun>::Result>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4,T5>(&notOK,fun,r,0,t1,t2,t3,t4,t5));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartD<ClrDelFun^>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4,T5>(&notOK,fun,0,0,t1,t2,t3,t4,t5));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(typename Types<R>::Normal* const& r,ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4,RCT5 t5)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
			pin_ptr<typename Types<RCT5>::Normal > pin5 =  &const_cast<typename Types<RCT5>::Normal%>(t5);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartDR<typename IfTypesEqual<R,void,int (),ClrDelFun^>::Result>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4,T5>(&notOK,fun,r,0,t1,t2,t3,t4,t5));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
	};
	template<class R,class T,class T1,class T2,class T3,class T4> struct ThreadParameters<R,T,T1,T2,T3,T4,void,void,void,void,void,void>
	{
		//所有函数类型定义
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl CdeclFun)(T1,T2,T3,T4);
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall StdCallFun)(T1,T2,T3,T4);
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall FastCallFun)(T1,T2,T3,T4);
#endif
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PThisCallFun)(T1,T2,T3,T4);
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PCThisCallFun)(T1,T2,T3,T4)const;
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall ClrCallFun)(T1,T2,T3,T4);
		template<class F>static void StartD(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			*fp.pNotOK = false;
			f(t1,t2,t3,t4);
		}
		template<class F>static void StartDR(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = f(t1,t2,t3,t4);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= f(t1,t2,t3,t4);
			}
			else f(t1,t2,t3,t4);
		}
#endif
		template<class F>static void Start(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			*fp.pNotOK = false;
			(*f)(t1,t2,t3,t4);
		}
		template<class F>static void StartR(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3,T4> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3,T4>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3,T4>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (*f)(t1,t2,t3,t4);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (*f)(t1,t2,t3,t4);
			}
			else (*f)(t1,t2,t3,t4);
		}
		template<class F>static void StartT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			*fp.pNotOK = false;
			(t->*f)(t1,t2,t3,t4);
		}
		template<class F>static void StartRT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3,T4> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3,T4>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3,T4>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			T4 t4 = *fp.pt4->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (t->*f)(t1,t2,t3,t4);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (t->*f)(t1,t2,t3,t4);
			}
			else (t->*f)(t1,t2,t3,t4);
		}
		typedef typename IfTypeIsGcHandle<T,T,typename IfTypeIsBaseDataType<T,XBase,T>::Result*>::Result TP; 
		typedef typename IfTypeIsGcHandle<T1,T1,typename Types<T1>::Normal const&>::Result RCT1;
		typedef typename IfTypeIsGcHandle<T2,T2,typename Types<T2>::Normal const&>::Result RCT2;
		typedef typename IfTypeIsGcHandle<T3,T3,typename Types<T3>::Normal const&>::Result RCT3;
		typedef typename IfTypeIsGcHandle<T4,T4,typename Types<T4>::Normal const&>::Result RCT4;
#ifdef CANUSECDECL
		static DWORD Begin(CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<CdeclFun>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4>(&notOK,fun,0,0,t1,t2,t3,t4));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),CdeclFun>::Result>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3,T4>(&notOK,fun,r,0,t1,t2,t3,t4));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSESTDCALL
		static DWORD Begin(StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<StdCallFun>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4>(&notOK,fun,0,0,t1,t2,t3,t4));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),StdCallFun>::Result>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3,T4>(&notOK,fun,r,0,t1,t2,t3,t4));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSEFASTCALL
		static DWORD Begin(FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<FastCallFun>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4>(&notOK,fun,0,0,t1,t2,t3,t4));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),FastCallFun>::Result>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3,T4>(&notOK,fun,r,0,t1,t2,t3,t4));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
		static DWORD Begin(TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartT<PThisCallFun>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4>(&notOK,fun,0,t,t1,t2,t3,t4));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartRT<typename IfTypesEqual<R,void,int (XBase::*)(),PThisCallFun>::Result>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3,T4>(&notOK,fun,r,t,t1,t2,t3,t4));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4){return Begin(t,(PThisCallFun) fun,t1,t2,t3,t4);}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4){return Begin(r,t,(PThisCallFun) fun,t1,t2,t3,t4);}
#ifdef _CLR
		static DWORD Begin(ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<ClrCallFun>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4>(&notOK,fun,0,0,t1,t2,t3,t4));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),ClrCallFun>::Result>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3,T4>(&notOK,fun,r,0,t1,t2,t3,t4));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartD<ClrDelFun^>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4>(&notOK,fun,0,0,t1,t2,t3,t4));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(typename Types<R>::Normal* const& r,ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3,RCT4 t4)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
			pin_ptr<typename Types<RCT4>::Normal > pin4 =  &const_cast<typename Types<RCT4>::Normal%>(t4);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartDR<typename IfTypesEqual<R,void,int (),ClrDelFun^>::Result>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3,T4>(&notOK,fun,r,0,t1,t2,t3,t4));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
	};
	template<class R,class T,class T1,class T2,class T3> struct ThreadParameters<R,T,T1,T2,T3,void,void,void,void,void,void,void>
	{
		//所有函数类型定义
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl CdeclFun)(T1,T2,T3);
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall StdCallFun)(T1,T2,T3);
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall FastCallFun)(T1,T2,T3);
#endif
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PThisCallFun)(T1,T2,T3);
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PCThisCallFun)(T1,T2,T3)const;
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall ClrCallFun)(T1,T2,T3);
		template<class F>static void StartD(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			*fp.pNotOK = false;
			f(t1,t2,t3);
		}
		template<class F>static void StartDR(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = f(t1,t2,t3);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= f(t1,t2,t3);
			}
			else f(t1,t2,t3);
		}
#endif
		template<class F>static void Start(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			*fp.pNotOK = false;
			(*f)(t1,t2,t3);
		}
		template<class F>static void StartR(void* p)
		{
			FunParameters<F*,R,T,T1,T2,T3> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2,T3>*)p);
			delete (FunParameters<F*,R,T,T1,T2,T3>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (*f)(t1,t2,t3);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (*f)(t1,t2,t3);
			}
			else (*f)(t1,t2,t3);
		}
		template<class F>static void StartT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			*fp.pNotOK = false;
			(t->*f)(t1,t2,t3);
		}
		template<class F>static void StartRT(void* p)
		{
			FunParameters<F,R,T,T1,T2,T3> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2,T3>*)p);
			delete (FunParameters<F,R,T,T1,T2,T3>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			T3 t3 = *fp.pt3->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (t->*f)(t1,t2,t3);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (t->*f)(t1,t2,t3);
			}
			else (t->*f)(t1,t2,t3);
		}
		typedef typename IfTypeIsGcHandle<T,T,typename IfTypeIsBaseDataType<T,XBase,T>::Result*>::Result TP; 
		typedef typename IfTypeIsGcHandle<T1,T1,typename Types<T1>::Normal const&>::Result RCT1;
		typedef typename IfTypeIsGcHandle<T2,T2,typename Types<T2>::Normal const&>::Result RCT2;
		typedef typename IfTypeIsGcHandle<T3,T3,typename Types<T3>::Normal const&>::Result RCT3;
#ifdef CANUSECDECL
		static DWORD Begin(CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<CdeclFun>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3>(&notOK,fun,0,0,t1,t2,t3));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,CdeclFun* fun,RCT1 t1,RCT2 t2,RCT3 t3)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),CdeclFun>::Result>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2,T3>(&notOK,fun,r,0,t1,t2,t3));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSESTDCALL
		static DWORD Begin(StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<StdCallFun>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3>(&notOK,fun,0,0,t1,t2,t3));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,StdCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),StdCallFun>::Result>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2,T3>(&notOK,fun,r,0,t1,t2,t3));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSEFASTCALL
		static DWORD Begin(FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<FastCallFun>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3>(&notOK,fun,0,0,t1,t2,t3));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,FastCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),FastCallFun>::Result>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2,T3>(&notOK,fun,r,0,t1,t2,t3));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
		static DWORD Begin(TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartT<PThisCallFun>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3>(&notOK,fun,0,t,t1,t2,t3));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartRT<typename IfTypesEqual<R,void,int (XBase::*)(),PThisCallFun>::Result>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2,T3>(&notOK,fun,r,t,t1,t2,t3));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3){return Begin(t,(PThisCallFun) fun,t1,t2,t3);}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2,RCT3 t3){return Begin(r,t,(PThisCallFun) fun,t1,t2,t3);}
#ifdef _CLR
		static DWORD Begin(ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<ClrCallFun>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3>(&notOK,fun,0,0,t1,t2,t3));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,ClrCallFun* fun,RCT1 t1,RCT2 t2,RCT3 t3)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),ClrCallFun>::Result>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2,T3>(&notOK,fun,r,0,t1,t2,t3));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartD<ClrDelFun^>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3>(&notOK,fun,0,0,t1,t2,t3));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(typename Types<R>::Normal* const& r,ClrDelFun^ fun,RCT1 t1,RCT2 t2,RCT3 t3)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
			pin_ptr<typename Types<RCT3>::Normal > pin3 =  &const_cast<typename Types<RCT3>::Normal%>(t3);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartDR<typename IfTypesEqual<R,void,int (),ClrDelFun^>::Result>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2,T3>(&notOK,fun,r,0,t1,t2,t3));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
	};
	template<class R,class T,class T1,class T2> struct ThreadParameters<R,T,T1,T2,void,void,void,void,void,void,void,void>
	{
		//所有函数类型定义
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl CdeclFun)(T1,T2);
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall StdCallFun)(T1,T2);
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall FastCallFun)(T1,T2);
#endif
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PThisCallFun)(T1,T2);
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PCThisCallFun)(T1,T2)const;
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall ClrCallFun)(T1,T2);
		template<class F>static void StartD(void* p)
		{
			FunParameters<F,R,T,T1,T2> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2>*)p);
			delete (FunParameters<F,R,T,T1,T2>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			*fp.pNotOK = false;
			f(t1,t2);
		}
		template<class F>static void StartDR(void* p)
		{
			FunParameters<F,R,T,T1,T2> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2>*)p);
			delete (FunParameters<F,R,T,T1,T2>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = f(t1,t2);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= f(t1,t2);
			}
			else f(t1,t2);
		}
#endif
		template<class F>static void Start(void* p)
		{
			FunParameters<F*,R,T,T1,T2> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2>*)p);
			delete (FunParameters<F*,R,T,T1,T2>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			*fp.pNotOK = false;
			(*f)(t1,t2);
		}
		template<class F>static void StartR(void* p)
		{
			FunParameters<F*,R,T,T1,T2> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1,T2>*)p);
			delete (FunParameters<F*,R,T,T1,T2>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (*f)(t1,t2);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (*f)(t1,t2);
			}
			else (*f)(t1,t2);
		}
		template<class F>static void StartT(void* p)
		{
			FunParameters<F,R,T,T1,T2> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2>*)p);
			delete (FunParameters<F,R,T,T1,T2>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			*fp.pNotOK = false;
			(t->*f)(t1,t2);
		}
		template<class F>static void StartRT(void* p)
		{
			FunParameters<F,R,T,T1,T2> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1,T2>*)p);
			delete (FunParameters<F,R,T,T1,T2>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			T2 t2 = *fp.pt2->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (t->*f)(t1,t2);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (t->*f)(t1,t2);
			}
			else (t->*f)(t1,t2);
		}
		typedef typename IfTypeIsGcHandle<T,T,typename IfTypeIsBaseDataType<T,XBase,T>::Result*>::Result TP; 
		typedef typename IfTypeIsGcHandle<T1,T1,typename Types<T1>::Normal const&>::Result RCT1;
		typedef typename IfTypeIsGcHandle<T2,T2,typename Types<T2>::Normal const&>::Result RCT2;
#ifdef CANUSECDECL
		static DWORD Begin(CdeclFun* fun,RCT1 t1,RCT2 t2)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<CdeclFun>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2>(&notOK,fun,0,0,t1,t2));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,CdeclFun* fun,RCT1 t1,RCT2 t2)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),CdeclFun>::Result>,(void*)new FunParameters<CdeclFun*,R,void,T1,T2>(&notOK,fun,r,0,t1,t2));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSESTDCALL
		static DWORD Begin(StdCallFun* fun,RCT1 t1,RCT2 t2)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<StdCallFun>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2>(&notOK,fun,0,0,t1,t2));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,StdCallFun* fun,RCT1 t1,RCT2 t2)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),StdCallFun>::Result>,(void*)new FunParameters<StdCallFun*,R,void,T1,T2>(&notOK,fun,r,0,t1,t2));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSEFASTCALL
		static DWORD Begin(FastCallFun* fun,RCT1 t1,RCT2 t2)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<FastCallFun>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2>(&notOK,fun,0,0,t1,t2));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,FastCallFun* fun,RCT1 t1,RCT2 t2)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),FastCallFun>::Result>,(void*)new FunParameters<FastCallFun*,R,void,T1,T2>(&notOK,fun,r,0,t1,t2));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
		static DWORD Begin(TP t,PThisCallFun fun,RCT1 t1,RCT2 t2)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartT<PThisCallFun>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2>(&notOK,fun,0,t,t1,t2));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PThisCallFun fun,RCT1 t1,RCT2 t2)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartRT<typename IfTypesEqual<R,void,int (XBase::*)(),PThisCallFun>::Result>,(void*)new FunParameters<PThisCallFun,R,T,T1,T2>(&notOK,fun,r,t,t1,t2));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2){return Begin(t,(PThisCallFun) fun,t1,t2);}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PCThisCallFun fun,RCT1 t1,RCT2 t2){return Begin(r,t,(PThisCallFun) fun,t1,t2);}
#ifdef _CLR
		static DWORD Begin(ClrCallFun* fun,RCT1 t1,RCT2 t2)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<ClrCallFun>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2>(&notOK,fun,0,0,t1,t2));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,ClrCallFun* fun,RCT1 t1,RCT2 t2)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),ClrCallFun>::Result>,(void*)new FunParameters<ClrCallFun*,R,void,T1,T2>(&notOK,fun,r,0,t1,t2));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(ClrDelFun^ fun,RCT1 t1,RCT2 t2)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartD<ClrDelFun^>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2>(&notOK,fun,0,0,t1,t2));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(typename Types<R>::Normal* const& r,ClrDelFun^ fun,RCT1 t1,RCT2 t2)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
			pin_ptr<typename Types<RCT2>::Normal > pin2 =  &const_cast<typename Types<RCT2>::Normal%>(t2);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartDR<typename IfTypesEqual<R,void,int (),ClrDelFun^>::Result>,(void*)new FunParameters<ClrDelFun^,R,void,T1,T2>(&notOK,fun,r,0,t1,t2));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
	};
	template<class R,class T,class T1> struct ThreadParameters<R,T,T1,void,void,void,void,void,void,void,void,void>
	{
		//所有函数类型定义
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl CdeclFun)(T1);
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall StdCallFun)(T1);
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall FastCallFun)(T1);
#endif
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PThisCallFun)(T1);
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PCThisCallFun)(T1)const;
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall ClrCallFun)(T1);
		template<class F>static void StartD(void* p)
		{
			FunParameters<F,R,T,T1> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1>*)p);
			delete (FunParameters<F,R,T,T1>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			*fp.pNotOK = false;
			f(t1);
		}
		template<class F>static void StartDR(void* p)
		{
			FunParameters<F,R,T,T1> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1>*)p);
			delete (FunParameters<F,R,T,T1>*)p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = f(t1);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= f(t1);
			}
			else f(t1);
		}
#endif
		template<class F>static void Start(void* p)
		{
			FunParameters<F*,R,T,T1> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1>*)p);
			delete (FunParameters<F*,R,T,T1>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			*fp.pNotOK = false;
			(*f)(t1);
		}
		template<class F>static void StartR(void* p)
		{
			FunParameters<F*,R,T,T1> fp;
			fp.SwapWith(*(FunParameters<F*,R,T,T1>*)p);
			delete (FunParameters<F*,R,T,T1>*)p;
			F* f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (*f)(t1);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (*f)(t1);
			}
			else (*f)(t1);
		}
		template<class F>static void StartT(void* p)
		{
			FunParameters<F,R,T,T1> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1>*)p);
			delete (FunParameters<F,R,T,T1>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			*fp.pNotOK = false;
			(t->*f)(t1);
		}
		template<class F>static void StartRT(void* p)
		{
			FunParameters<F,R,T,T1> fp;
			fp.SwapWith(*(FunParameters<F,R,T,T1>*)p);
			delete (FunParameters<F,R,T,T1>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			T1 t1 = *fp.pt1->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (t->*f)(t1);
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (t->*f)(t1);
			}
			else (t->*f)(t1);
		}
		typedef typename IfTypeIsGcHandle<T,T,typename IfTypeIsBaseDataType<T,XBase,T>::Result*>::Result TP; 
		typedef typename IfTypeIsGcHandle<T1,T1,typename Types<T1>::Normal const&>::Result RCT1;
#ifdef CANUSECDECL
		static DWORD Begin(CdeclFun* fun,RCT1 t1)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<CdeclFun>,(void*)new FunParameters<CdeclFun*,R,void,T1>(&notOK,fun,0,0,t1));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,CdeclFun* fun,RCT1 t1)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),CdeclFun>::Result>,(void*)new FunParameters<CdeclFun*,R,void,T1>(&notOK,fun,r,0,t1));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSESTDCALL
		static DWORD Begin(StdCallFun* fun,RCT1 t1)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<StdCallFun>,(void*)new FunParameters<StdCallFun*,R,void,T1>(&notOK,fun,0,0,t1));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,StdCallFun* fun,RCT1 t1)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),StdCallFun>::Result>,(void*)new FunParameters<StdCallFun*,R,void,T1>(&notOK,fun,r,0,t1));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSEFASTCALL
		static DWORD Begin(FastCallFun* fun,RCT1 t1)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<FastCallFun>,(void*)new FunParameters<FastCallFun*,R,void,T1>(&notOK,fun,0,0,t1));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,FastCallFun* fun,RCT1 t1)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),FastCallFun>::Result>,(void*)new FunParameters<FastCallFun*,R,void,T1>(&notOK,fun,r,0,t1));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
		static DWORD Begin(TP t,PThisCallFun fun,RCT1 t1)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartT<PThisCallFun>,(void*)new FunParameters<PThisCallFun,R,T,T1>(&notOK,fun,0,t,t1));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PThisCallFun fun,RCT1 t1)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartRT<typename IfTypesEqual<R,void,int (XBase::*)(),PThisCallFun>::Result>,(void*)new FunParameters<PThisCallFun,R,T,T1>(&notOK,fun,r,t,t1));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(TP t,PCThisCallFun fun,RCT1 t1){return Begin(t,(PThisCallFun) fun,t1);}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PCThisCallFun fun,RCT1 t1){return Begin(r,t,(PThisCallFun) fun,t1);}
#ifdef _CLR
		static DWORD Begin(ClrCallFun* fun,RCT1 t1)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&Start<ClrCallFun>,(void*)new FunParameters<ClrCallFun*,R,void,T1>(&notOK,fun,0,0,t1));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,ClrCallFun* fun,RCT1 t1)
		{
#ifdef _CLR
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),ClrCallFun>::Result>,(void*)new FunParameters<ClrCallFun*,R,void,T1>(&notOK,fun,r,0,t1));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(ClrDelFun^ fun,RCT1 t1)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartD<ClrDelFun^>,(void*)new FunParameters<ClrDelFun^,R,void,T1>(&notOK,fun,0,0,t1));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(typename Types<R>::Normal* const& r,ClrDelFun^ fun,RCT1 t1)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
			pin_ptr<typename Types<RCT1>::Normal > pin1 =  &const_cast<typename Types<RCT1>::Normal%>(t1);//打钉
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartDR<typename IfTypesEqual<R,void,int (),ClrDelFun^>::Result>,(void*)new FunParameters<ClrDelFun^,R,void,T1>(&notOK,fun,r,0,t1));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
	};
	template<class R,class T> struct ThreadParameters<R,T,void,void,void,void,void,void,void,void,void,void>
	{
		//所有函数类型定义
#ifdef CANUSECDECL
		//默认调用函数指针类型
		typedef typename R(__cdecl CdeclFun)();
#endif
#ifdef CANUSESTDCALL
		//标准调用函数指针类型
		typedef typename R(__stdcall StdCallFun)();
#endif
#ifdef CANUSEFASTCALL
		//快速调用函数指针类型
		typedef typename R(__fastcall FastCallFun)();
#endif
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PThisCallFun)();
		//成员函数指针类型
		typedef typename R(IfTypeIsBaseDataType<T,XBase,T>::Result::*PCThisCallFun)()const;
#ifdef _CLR
		//托管函数指针类型
		typedef typename R(__clrcall ClrCallFun)();
		template<class F>static void StartD(void* p)
		{
			FunParameters<F,R,T> fp;
			fp.SwapWith(*(FunParameters<F,R,T>*)p);
			delete (FunParameters<F,R,T>*)p;
			F f = *fp.pf->p;
			*fp.pNotOK = false;
			f();
		}
		template<class F>static void StartDR(void* p)
		{
			FunParameters<F,R,T> fp;
			fp.SwapWith(*(FunParameters<F,R,T>*)p);
			delete (FunParameters<F,R,T>*)p;
			F f = *fp.pf->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = f();
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= f();
			}
			else f();
		}
#endif
		template<class F>static void Start(void* p)
		{
			FunParameters<F*,R,T> fp;
			fp.SwapWith(*(FunParameters<F*,R,T>*)p);
			delete (FunParameters<F*,R,T>*)p;
			F* f = *fp.pf->p;
			*fp.pNotOK = false;
			(*f)();
		}
		template<class F>static void StartR(void* p)
		{
			FunParameters<F*,R,T> fp;
			fp.SwapWith(*(FunParameters<F*,R,T>*)p);
			delete (FunParameters<F*,R,T>*)p;
			F* f = *fp.pf->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (*f)();
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (*f)();
			}
			else (*f)();
		}
		template<class F>static void StartT(void* p)
		{
			FunParameters<F,R,T> fp;
			fp.SwapWith(*(FunParameters<F,R,T>*)p);
			delete (FunParameters<F,R,T>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			*fp.pNotOK = false;
			(t->*f)();
		}
		template<class F>static void StartRT(void* p)
		{
			FunParameters<F,R,T> fp;
			fp.SwapWith(*(FunParameters<F,R,T>*)p);
			delete (FunParameters<F,R,T>*)p;
			typename Types<T>::Normal* t = *fp.pt->p;
			F f = *fp.pf->p;
			*fp.pNotOK = false;
			if(Types<R>::isReference)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				typename ParameterPass<R>::RC rc = (t->*f)();
#ifdef _CLR
				pin_ptr<typename Types<R>::Normal> pinr = &(typename Types<R>::Normal&)rc;
				r = pinr;
#else
				r = &(typename Types<R>::Normal&)rc;
#endif
			}
			else if(fp.pr)
			{
				typename Types<R>::Normal*& r = *fp.pr->p;
				*r= (t->*f)();
			}
			else (t->*f)();
		}
		typedef typename IfTypeIsGcHandle<T,T,typename IfTypeIsBaseDataType<T,XBase,T>::Result*>::Result TP; 
#ifdef CANUSECDECL
		static DWORD Begin(CdeclFun* fun)
		{
			bool notOK = true;
			DWORD d = APIStartThread(&Start<CdeclFun>,(void*)new FunParameters<CdeclFun*,R,void>(&notOK,fun,0,0));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,CdeclFun* fun)
		{
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),CdeclFun>::Result>,(void*)new FunParameters<CdeclFun*,R,void>(&notOK,fun,r,0));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSESTDCALL
		static DWORD Begin(StdCallFun* fun)
		{
			bool notOK = true;
			DWORD d = APIStartThread(&Start<StdCallFun>,(void*)new FunParameters<StdCallFun*,R,void>(&notOK,fun,0,0));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,StdCallFun* fun)
		{
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),StdCallFun>::Result>,(void*)new FunParameters<StdCallFun*,R,void>(&notOK,fun,r,0));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
#ifdef CANUSEFASTCALL
		static DWORD Begin(FastCallFun* fun)
		{
			bool notOK = true;
			DWORD d = APIStartThread(&Start<FastCallFun>,(void*)new FunParameters<FastCallFun*,R,void>(&notOK,fun,0,0));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,FastCallFun* fun)
		{
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),FastCallFun>::Result>,(void*)new FunParameters<FastCallFun*,R,void>(&notOK,fun,r,0));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
		static DWORD Begin(TP t,PThisCallFun fun)
		{
			bool notOK = true;
			DWORD d = APIStartThread(&StartT<PThisCallFun>,(void*)new FunParameters<PThisCallFun,R,T>(&notOK,fun,0,t));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PThisCallFun fun)
		{
			bool notOK = true;
			DWORD d = APIStartThread(&StartRT<typename IfTypesEqual<R,void,int (XBase::*)(),PThisCallFun>::Result>,(void*)new FunParameters<PThisCallFun,R,T>(&notOK,fun,r,t));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(TP t,PCThisCallFun fun){return Begin(t,(PThisCallFun) fun);}
		static DWORD Begin(typename Types<R>::Normal* const& r,TP t,PCThisCallFun fun){return Begin(r,t,(PThisCallFun) fun);}
#ifdef _CLR
		static DWORD Begin(ClrCallFun* fun)
		{
			bool notOK = true;
			DWORD d = APIStartThread(&Start<ClrCallFun>,(void*)new FunParameters<ClrCallFun*,R,void>(&notOK,fun,0,0));
			while(notOK)SwitchToThread();
			return d;
		}
		static DWORD Begin(typename Types<R>::Normal* const& r,ClrCallFun* fun)
		{
			bool notOK = true;
			DWORD d = APIStartThread(&StartR<typename IfTypesEqual<R,void,int (),ClrCallFun>::Result>,(void*)new FunParameters<ClrCallFun*,R,void>(&notOK,fun,r,0));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(ClrDelFun^ fun)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartD<ClrDelFun^>,(void*)new FunParameters<ClrDelFun^,R,void>(&notOK,fun,0,0));
			while(notOK)SwitchToThread();
			return d;
		}
		template<class  ClrDelFun>static DWORD Begin(typename Types<R>::Normal* const& r,ClrDelFun^ fun)
		{
#ifdef _CLR
			pin_ptr<ClrDelFun^> pinf = &fun;
#endif
			bool notOK = true;
			DWORD d = APIStartThread(&StartDR<typename IfTypesEqual<R,void,int (),ClrDelFun^>::Result>,(void*)new FunParameters<ClrDelFun^,R,void>(&notOK,fun,r,0));
			while(notOK)SwitchToThread();
			return d;
		}
#endif
	};


	//提供线程间的同步功能
	class ThreadControl
	{
		ThreadControl&operator=(const ThreadControl&){return *this;}
		ThreadControl(const ThreadControl&){}
	protected:
		CRITICAL_SECTION cs;
	public:
		//在进入临界区前总是等待其他线程
		void ThreadWait();
		//尝试进入临界区并立即返回，成功返回true
		bool ThreadTry();
		//线程操作完毕，出临界区
		void ThreadDone();

		//默认构造函数
		ThreadControl();
		//析构函数
		~ThreadControl();
		//检测某线程是否存活
		static bool IsThreadAlive(DWORD id);
		//使用一个void()(void*)型函数新建并启动一个线程，并返回线程id
		static DWORD StartThread(void (* fun)(void *),void *prameters,HANDLE* pHandle){return APIStartThread(fun,prameters,pHandle);}
		//使用一个void()(void*)型函数新建并启动一个线程，并返回线程id
		static inline DWORD StartThread(void (* fun)(void *),void *pv){return StartThread(fun,pv,(HANDLE*)0);}
		//使用一个静态的void()()型函数新建并启动一个线程，并返回线程id
		static DWORD StartThread(void (* fun)(void)){return ThreadParameters<void,void>::Begin(fun);}
		//使用一个静态的void()(T1)型函数新建并启动一个线程，并返回线程id
		template<class T1>static DWORD StartThread(void (* fun)(T1),typename ParameterPass<T1>::RC t1){return ThreadParameters<void,void,T1>::Begin(fun,t1);}
		//使用一个静态的void()(T1,T2)型函数新建并启动一个线程，并返回线程id
		template<class T1,class T2>static DWORD StartThread(void (* fun)(T1,T2),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2){return ThreadParameters<void,void,T1,T2>::Begin(fun,t1,t2);}
		//使用一个静态的void()(T1,T2,T3)型函数新建并启动一个线程，并返回线程id
		template<class T1,class T2,class T3>static DWORD StartThread(void (* fun)(T1,T2,T3),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3){return ThreadParameters<void,void,T1,T2,T3>::Begin(fun,t1,t2,t3);}
		//使用一个静态的void()(T1,T2,T3,T4)型函数新建并启动一个线程，并返回线程id
		template<class T1,class T2,class T3,class T4>static DWORD StartThread(void (* fun)(T1,T2,T3,T4),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4){return ThreadParameters<void,void,T1,T2,T3,T4>::Begin(fun,t1,t2,t3,t4);}
		//使用一个静态的void()(T1,T2,T3,T4,T5)型函数新建并启动一个线程，并返回线程id
		template<class T1,class T2,class T3,class T4,class T5>static DWORD StartThread(void (* fun)(T1,T2,T3,T4,T5),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5){return ThreadParameters<void,void,T1,T2,T3,T4,T5>::Begin(fun,t1,t2,t3,t4,t5);}
		//使用一个静态的void()(T1,T2,T3,T4,T5,T6)型函数新建并启动一个线程，并返回线程id
		template<class T1,class T2,class T3,class T4,class T5,class T6>static DWORD StartThread(void (* fun)(T1,T2,T3,T4,T5,T6),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6){return ThreadParameters<void,void,T1,T2,T3,T4,T5,T6>::Begin(fun,t1,t2,t3,t4,t5,t6);}
		//使用一个静态的void()(T1,T2,T3,T4,T5,T6,T7)型函数新建并启动一个线程，并返回线程id
		template<class T1,class T2,class T3,class T4,class T5,class T6,class T7>static DWORD StartThread(void (* fun)(T1,T2,T3,T4,T5,T6,T7),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7){return ThreadParameters<void,void,T1,T2,T3,T4,T5,T6,T7>::Begin(fun,t1,t2,t3,t4,t5,t6,t7);}
		//使用一个静态的void()(T1,T2,T3,T4,T5,T6,T7,T8)型函数新建并启动一个线程，并返回线程id
		template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>static DWORD StartThread(void (* fun)(T1,T2,T3,T4,T5,T6,T7,T8),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8){return ThreadParameters<void,void,T1,T2,T3,T4,T5,T6,T7,T8>::Begin(fun,t1,t2,t3,t4,t5,t6,t7,t8);}
		//使用类中一个void()()型成员函数新建并启动一个线程，并返回线程id
		template<class T>static DWORD StartThread(T* const t,void (T::*fun)(void)){return ThreadParameters<void,T>::Begin(t,fun);}
		//使用类中一个void()(T1)型成员函数新建并启动一个线程，并返回线程id
		template<class T,class T1>static DWORD StartThread(T* const t,void (T::*fun)(T1),typename ParameterPass<T1>::RC t1){return ThreadParameters<void,T,T1>::Begin(t,fun,t1);}
		//使用类中一个void()(T1,T2)型成员函数新建并启动一个线程，并返回线程id
		template<class T,class T1,class T2>static DWORD StartThread(T* const t,void (T::*fun)(T1,T2),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2){return ThreadParameters<void,T,T1,T2>::Begin(t,fun,t1,t2);}
		//使用类中一个void()(T1,T2,T3)型成员函数新建并启动一个线程，并返回线程id
		template<class T,class T1,class T2,class T3>static DWORD StartThread(T* const t,void (T::*fun)(T1,T2,T3),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3){return ThreadParameters<void,T,T1,T2,T3>::Begin(t,fun,t1,t2,t3);}
		//使用类中一个void()(T1,T2,T3,T4)型成员函数新建并启动一个线程，并返回线程id
		template<class T,class T1,class T2,class T3,class T4>static DWORD StartThread(T* const t,void (T::*fun)(T1,T2,T3,T4),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4){return ThreadParameters<void,T,T1,T2,T3,T4>::Begin(t,fun,t1,t2,t3,t4);}
		//使用类中一个void()(T1,T2,T3,T4,T5)型成员函数新建并启动一个线程，并返回线程id
		template<class T,class T1,class T2,class T3,class T4,class T5>static DWORD StartThread(T* const t,void (T::*fun)(T1,T2,T3,T4,T5),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5){return ThreadParameters<void,T,T1,T2,T3,T4,T5>::Begin(t,fun,t1,t2,t3,t4,t5);}
		//使用类中一个void()(T1,T2,T3,T4,T5,T6)型成员函数新建并启动一个线程，并返回线程id
		template<class T,class T1,class T2,class T3,class T4,class T5,class T6>static DWORD StartThread(T* const t,void (T::*fun)(T1,T2,T3,T4,T5,T6),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6){return ThreadParameters<void,T,T1,T2,T3,T4,T5,T6>::Begin(t,fun,t1,t2,t3,t4,t5,t6);}
		//使用类中一个void()(T1,T2,T3,T4,T5,T6,T7)型成员函数新建并启动一个线程，并返回线程id
		template<class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7>static DWORD StartThread(T* const t,void (T::*fun)(T1,T2,T3,T4,T5,T6,T7),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7){return ThreadParameters<void,T,T1,T2,T3,T4,T5,T6,T7>::Begin(t,fun,t1,t2,t3,t4,t5,t6,t7);}
		//使用类中一个void()(T1,T2,T3,T4,T5,T6,T7,T8)型成员函数新建并启动一个线程，并返回线程id
		template<class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>static DWORD StartThread(T* const t,void (T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8){return ThreadParameters<void,T,T1,T2,T3,T4,T5,T6,T7,T8>::Begin(t,fun,t1,t2,t3,t4,t5,t6,t7,t8);}
		//使用类中一个void()(T1,T2,T3,T4,T5,T6,T7,T8,T9)型成员函数新建并启动一个线程，并返回线程id
		template<class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>static DWORD StartThread(T* const t,void (T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8,T9),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8,typename ParameterPass<T9>::RC t9){return ThreadParameters<void,T,T1,T2,T3,T4,T5,T6,T7,T8,T9>::Begin(t,fun,t1,t2,t3,t4,t5,t6,t7,t8,t9);}
		//使用类中一个void()(T1,T2,T3,T4,T5,T6,T7,T8,T9,TA)型成员函数新建并启动一个线程，并返回线程id
		template<class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9,class TA>static DWORD StartThread(T* const t,void (T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8,T9,TA),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8,typename ParameterPass<T9>::RC t9,typename ParameterPass<TA>::RC ta){return ThreadParameters<void,T,T1,T2,T3,T4,T5,T6,T7,T8,T9,TA>::Begin(t,fun,t1,t2,t3,t4,t5,t6,t7,t8,t9,ta);}
		//使用一个静态的R()()型函数新建并启动一个线程，并返回线程id
		template<class R>static DWORD StartThread(R (* fun)(void),typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,void>::Begin(r,fun);}
		//使用一个静态的R()(T1)型函数新建并启动一个线程，并返回线程id
		template<class R,class T1>static DWORD StartThread(R (* fun)(T1),typename ParameterPass<T1>::RC t1,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,void,T1>::Begin(r,fun,t1);}
		//使用一个静态的R()(T1,T2)型函数新建并启动一个线程，并返回线程id
		template<class R,class T1,class T2>static DWORD StartThread(R (* fun)(T1,T2),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,void,T1,T2>::Begin(r,fun,t1,t2);}
		//使用一个静态的R()(T1,T2,T3)型函数新建并启动一个线程，并返回线程id
		template<class R,class T1,class T2,class T3>static DWORD StartThread(R (* fun)(T1,T2,T3),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,void,T1,T2,T3>::Begin(r,fun,t1,t2,t3);}
		//使用一个静态的R()(T1,T2,T3,T4)型函数新建并启动一个线程，并返回线程id
		template<class R,class T1,class T2,class T3,class T4>static DWORD StartThread(R (* fun)(T1,T2,T3,T4),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,void,T1,T2,T3,T4>::Begin(r,fun,t1,t2,t3,t4);}
		//使用一个静态的R()(T1,T2,T3,T4,T5)型函数新建并启动一个线程，并返回线程id
		template<class R,class T1,class T2,class T3,class T4,class T5>static DWORD StartThread(R (* fun)(T1,T2,T3,T4,T5),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,void,T1,T2,T3,T4,T5>::Begin(r,fun,t1,t2,t3,t4,t5);}
		//使用一个静态的R()(T1,T2,T3,T4,T5,T6)型函数新建并启动一个线程，并返回线程id
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6>static DWORD StartThread(R (* fun)(T1,T2,T3,T4,T5,T6),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,void,T1,T2,T3,T4,T5,T6>::Begin(r,fun,t1,t2,t3,t4,t5,t6);}
		//使用一个静态的R()(T1,T2,T3,T4,T5,T6,T7)型函数新建并启动一个线程，并返回线程id
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7>static DWORD StartThread(R (* fun)(T1,T2,T3,T4,T5,T6,T7),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,void,T1,T2,T3,T4,T5,T6,T7>::Begin(r,fun,t1,t2,t3,t4,t5,t6,t7);}
		//使用一个静态的R()(T1,T2,T3,T4,T5,T6,T7,T8)型函数新建并启动一个线程，并返回线程id
		template<class R,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>static DWORD StartThread(R (* fun)(T1,T2,T3,T4,T5,T6,T7,T8),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,void,T1,T2,T3,T4,T5,T6,T7,T8>::Begin(r,fun,t1,t2,t3,t4,t5,t6,t7,t8);}
		//使用类中一个R()()型成员函数新建并启动一个线程，并返回线程id
		template<class R,class T>static DWORD StartThread(T* const t,R (T::*fun)(void),typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,T>::Begin(r,t,fun);}
		//使用类中一个R()(T1)型成员函数新建并启动一个线程，并返回线程id
		template<class R,class T,class T1>static DWORD StartThread(T* const t,R (T::*fun)(T1),typename ParameterPass<T1>::RC t1,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,T,T1>::Begin(r,t,fun,t1);}
		//使用类中一个R()(T1,T2)型成员函数新建并启动一个线程，并返回线程id
		template<class R,class T,class T1,class T2>static DWORD StartThread(T* const t,R (T::*fun)(T1,T2),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,T,T1,T2>::Begin(r,t,fun,t1,t2);}
		//使用类中一个R()(T1,T2,T3)型成员函数新建并启动一个线程，并返回线程id
		template<class R,class T,class T1,class T2,class T3>static DWORD StartThread(T* const t,R (T::*fun)(T1,T2,T3),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,T,T1,T2,T3>::Begin(r,t,fun,t1,t2,t3);}
		//使用类中一个R()(T1,T2,T3,T4)型成员函数新建并启动一个线程，并返回线程id
		template<class R,class T,class T1,class T2,class T3,class T4>static DWORD StartThread(T* const t,R (T::*fun)(T1,T2,T3,T4),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,T,T1,T2,T3,T4>::Begin(r,t,fun,t1,t2,t3,t4);}
		//使用类中一个R()(T1,T2,T3,T4,T5)型成员函数新建并启动一个线程，并返回线程id
		template<class R,class T,class T1,class T2,class T3,class T4,class T5>static DWORD StartThread(T* const t,R (T::*fun)(T1,T2,T3,T4,T5),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,T,T1,T2,T3,T4,T5>::Begin(r,t,fun,t1,t2,t3,t4,t5);}
		//使用类中一个R()(T1,T2,T3,T4,T5,T6)型成员函数新建并启动一个线程，并返回线程id
		template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6>static DWORD StartThread(T* const t,R (T::*fun)(T1,T2,T3,T4,T5,T6),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,T,T1,T2,T3,T4,T5,T6>::Begin(r,t,fun,t1,t2,t3,t4,t5,t6);}
		//使用类中一个R()(T1,T2,T3,T4,T5,T6,T7)型成员函数新建并启动一个线程，并返回线程id
		template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7>static DWORD StartThread(T* const t,R (T::*fun)(T1,T2,T3,T4,T5,T6,T7),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,T,T1,T2,T3,T4,T5,T6,T7>::Begin(r,t,fun,t1,t2,t3,t4,t5,t6,t7);}
		//使用类中一个R()(T1,T2,T3,T4,T5,T6,T7,T8)型成员函数新建并启动一个线程，并返回线程id
		template<class R,class T,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>static DWORD StartThread(T* const t,R (T::*fun)(T1,T2,T3,T4,T5,T6,T7,T8),typename ParameterPass<T1>::RC t1,typename ParameterPass<T2>::RC t2,typename ParameterPass<T3>::RC t3,typename ParameterPass<T4>::RC t4,typename ParameterPass<T5>::RC t5,typename ParameterPass<T6>::RC t6,typename ParameterPass<T7>::RC t7,typename ParameterPass<T8>::RC t8,typename ParameterPass<typename Types<R>::Normal*>::RC r){return ThreadParameters<R,T,T1,T2,T3,T4,T5,T6,T7,T8>::Begin(r,t,fun,t1,t2,t3,t4,t5,t6,t7,t8);}
		//重置线程参数
		void ThreadReset();
		//获取当前线程重复进入临界区次数
		int GetThreadDeep();
		//获取当前线程id
		DWORD GetThreadID();
		//默认的线程控制器
		static ThreadControl Default;
	};

}