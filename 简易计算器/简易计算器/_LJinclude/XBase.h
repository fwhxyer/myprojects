#pragma once
namespace LJ
{
	template<class T,class T1,class T2,class T3>inline T* placementnew(T*const& t,T1&t1,T2&t2,T3&t3){return new(t)T(t1,t2,t3);}
	template<class T,class T1,class T2,class T3>inline T* placementnew(T*const& t,const T1&t1,const T2&t2,const T3&t3){return new(t)T(t1,t2,t3);}
	template<class T,class T1,class T2,class T3>inline T* placementnew(T*const& t,T1&t1,const T2&t2,const T3&t3){return new(t)T(t1,t2,t3);}
	template<class T,class T1,class T2,class T3>inline T* placementnew(T*const& t,const T1&t1,T2&t2,const T3&t3){return new(t)T(t1,t2,t3);}
	template<class T,class T1,class T2,class T3>inline T* placementnew(T*const& t,const T1&t1,const T2&t2,T3&t3){return new(t)T(t1,t2,t3);}
	template<class T,class T1,class T2,class T3>inline T* placementnew(T*const& t,T1&t1,T2&t2,const T3&t3){return new(t)T(t1,t2,t3);}
	template<class T,class T1,class T2,class T3>inline T* placementnew(T*const& t,const T1&t1,T2&t2,T3&t3){return new(t)T(t1,t2,t3);}
	template<class T,class T1,class T2,class T3>inline T* placementnew(T*const& t,T1&t1,const T2&t2,T3&t3){return new(t)T(t1,t2,t3);}
	template<class T,class T1,class T2>inline T* placementnew(T*const& t,T1&t1,T2&t2){return new(t)T(t1,t2);}
	template<class T,class T1,class T2>inline T* placementnew(T*const& t,const T1&t1,const T2&t2){return new(t)T(t1,t2);}
	template<class T,class T1,class T2>inline T* placementnew(T*const& t,T1&t1,const T2&t2){return new(t)T(t1,t2);}
	template<class T,class T1,class T2>inline T* placementnew(T*const& t,const T1&t1,T2&t2){return new(t)T(t1,t2);}
	template<class T,class T1>inline T* placementnew(T*const& t,T1&t1){return new(t)T(t1);}
	template<class T,class T1>inline T* placementnew(T*const& t,const T1&t1){return new(t)T(t1);}
	template<class T>inline T* placementnew(T*const& t){return new(t)T();}
#ifdef _DEBUG//这一段是Debug模式下的内存泄露检测机制，很有用的哈，如果有内存泄露，程序结束时将弹窗

	//注意 要把“代码生成”中的运行时库设置为/MDd或/MTd，否则将出现链接错误

#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <assert.h>
#define new DEBUG_CLIENTBLOCK
#if (_M_CEE == 1) ||  (1==_MANAGED) //托管支持
	static int __clrcall _Exit_L_()
	{
		//int i = _CrtDumpMemoryLeaks();//内存泄露检测结果将在输出的调试页，双击即可找到泄露位置
		//assert( i == 0);//对于全局的静态对象，可能在该语句后才会被释放，所以提示的内存泄露可能有误
		//所以请将int i = _CrtDumpMemoryLeaks();放到认为是离程序结束最近的位置
		//现在已经迁移到NodeOfClassType的析构函数中
		return 0;
	}
	static _onexit_m_t _d_e_b_ug = (
		_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF),//启用内存泄露检测报告
		_onexit_m(&_Exit_L_));//程序结束时检查
#else
	static void _Exit_L_()//跟下面的atexit();配合使用
	{
		//int i = _CrtDumpMemoryLeaks();//内存泄露检测结果将在输出的调试页，双击即可找到泄露位置
		//assert( i == 0);//对于全局的静态对象，可能在该语句后才会被释放，所以提示的内存泄露可能有误
		//所以请将int i = _CrtDumpMemoryLeaks();放到认为是离程序结束最近的位置
		//现在已经迁移到NodeOfClassType的析构函数中
	}
	static int _d_e_b_ug = (
		_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF),//启用内存泄露检测报告
		//_CrtSetBreakAlloc(15),//设置自动断点位置
		atexit(_Exit_L_));//程序结束时检查
#endif
#endif
	template<const int SizeInBytes>struct structSize	{char tmp[SizeInBytes];};
	struct MaxValues
	{
		static enum:char{Char =127};
		static enum:wchar_t{WChar=0xffff};
		static enum:signed char{SignedChar=127};
		static enum:unsigned char{UnsignedChar=0xff};
		static enum:short{Short=0x7fff};
		static enum:short{Int16=0x7fff};
		static enum:unsigned short{UnsignedShort=0xffff};
		static enum:unsigned short{UInt16=0xffff};
		static enum:int{Int=0x7fffffff};
		static enum:int{Int32=0x7fffffff};
		static enum:unsigned int{UnsignedInt=0xffffffff};
		static enum:unsigned int{UInt32=0xffffffff};
		static enum:long{Long=0x7fffffff};
		static enum:unsigned long{UnsignedLong=0xffffffff};
		static enum:long long{LongLong=0x7fffffffffffffff};
		static enum:long long{Int64=0x7fffffffffffffff};
		static enum:unsigned long long{UnsignedLongLong=0xffffffffffffffff};
		static enum:unsigned long long{UInt64=0xffffffffffffffff};
		const static float Float;
		const static double Double;
	};
	struct MinValues
	{
		static enum:char{Char=-128};
		static enum:wchar_t{WChar=0};
		static enum:signed char{SignedChar=-128};
		static enum:unsigned char{UnsignedChar=0};
		static enum:short{Short=-32768};
		static enum:short{Int16=-32768};
		static enum:unsigned short{UnsignedShort=0};
		static enum:unsigned short{UInt16=0};
		static enum:int{Int=(int)0x80000000};
		static enum:int{Int32=(int)0x80000000};
		static enum:unsigned int{UnsignedInt=0};
		static enum:unsigned int{UInt32=0};
		static enum:long{Long=(long)0x80000000};
		static enum:unsigned long{UnsignedLong=0};
		static enum:long long{LongLong=(long long)0x8000000000000000};
		static enum:long long{Int64=(long long)0x8000000000000000};
		static enum:unsigned long long{UnsignedLongLong=0};
		static enum:unsigned long long{UInt64=0};
		const static float Float;
		const static double Double;
	};
	struct Bits
	{
		//获取i前导0的比特数
		static int LeftZeroCount64(unsigned long long i);
		//从pSource指向内存的startBitPositon位起复制bitsCount比特到pDestination指向内存的destinationBitPosition位处。源内存跟目标内存不能重叠
		static void Copy(void* pSource,unsigned startBitPositon,unsigned bitsCount,void* pDestination,unsigned destinationBitPosition=0);
		//从pSource指向内存起复制bitsCount比特到pDestination指向内存的destinationBitPosition位处。源内存跟目标内存不能重叠
		static void Copy(void* pSource,unsigned bitsCount,void* pDestination,unsigned destinationBitPosition=0){Bits::Copy(pSource,0,bitsCount, pDestination,destinationBitPosition);}
		//将p所指向的内存的startBitPosition比特起的bitsCount比特置为bit的值
		static void Set(void* p,unsigned startBitPosition,unsigned bitsCount,bool bitValue=false);
		//将p指向的内存的startBitPosition比特位起bitsCount比特的数据进行mov比特位移，正为左移，负为右移
		static void Move(void* p,unsigned startBitPosition,unsigned bitsCount,int mov);
		//比较两块内存区的大小，从高位往低位比较，跟strcmp的顺序相反
		static int Compare(void* pSource,unsigned startBitPositon,unsigned bitsCount,void* pDestination,unsigned destinationBitPosition=0);
		//比较两块内存区的大小，从高位往低位比较，跟strcmp的顺序相反
		static int  Compare(void* pSource,unsigned bitsCount,void* pDestination,unsigned destinationBitPosition=0){return Bits::Compare(pSource,0,bitsCount, pDestination,destinationBitPosition);}
		//获取某比特位上的内容
		static bool Get(const void* pSource,long long bitPosition);
	};
	struct Memory
	{
		//内存复制,pDestination指向目标内存，pSource指向源数据，sizeInBytes是按字节数表示的大小，源数据数和目标内存不能重叠
		static void Copy(void* pDestination,const void* pSource,size_t SizeInBytes);
		//内存移动（内存复制的可能有重叠版本）
		static void Move(void* pDestination,const void* pSource,size_t sizeInBytes);
		//最快的内存复制法，虽然比较难看
		template<const int SizeInBytes,class T1,class T2>static inline void Copy(T1 *const & pDestination,const T2*const& pSource)
		{
			*reinterpret_cast<structSize<SizeInBytes>*>(pDestination) = *reinterpret_cast<const structSize<SizeInBytes>*>(pSource);
		}
	};
	//基类
	class XBase
	{
	protected:
		//一个指向Xbase对象的指针该指针值为NULL时，表示该引用为空引用；如果pObject指向自身，则表示该对象为被引用的终结点 
		XBase* pObject;
		//获取指针的引用，当IsNull()时，调用该方法将抛出异常
		XBase* Pointer()const;
		//获取this指针
		inline XBase* ThisPointer()const{return const_cast<XBase*>(this);}
		//该对象被引用的次数。如果此数的值小于0，表示该对象不能被引用。 如果在生命周期中，此值持续为0，则表示该对象未被引用。
		mutable volatile long referenceCount;
	public:
		//判断该对象是否可以被引用，如果referenceCount小于0则返回false。对于referenceCount<0的实例，不能通过赋值转变为原始值
		bool CanBeReferenced()const;
		//当前类的类型
		static const XTypes& CurrentType;
		//比较该对象与object对象是否是同一个对象
		virtual bool Equals(const XBase& object)const;
		//比较
		bool operator==(const XBase& object)const{return Equals(object);}
		//获取对象类型信息
		virtual const XTypes& GetType()const;
		//判断该对象是否为空引用（仅当pObject为NULL时返回true）
		bool IsNull()const;
		//判断该对象是否是引用终结点（即原始值），如果pObject指向自身则返回true。对于pObject指向自身的实例，不能通过赋值转变为引用
		bool IsReferenceEnding()const;
		//制作一个副本，并返回该副本的指针
		virtual XBase* NewCopy()const;
		//减少该对象被引用的次数，应采用原子操作，如果引用计数被减小为0，则进行自删除操作
		void ReferenceDecrement()const;
		//判断对象与object对象引用的是否是同一个对象，即pObject相等时返回true
		bool ReferenceEquals(const XBase& object)const;
		//增加该对象被引用的次数，应采用原子操作，返回该对象指针。如果referenceCount小于0，则该方法返回NULL，并且引用计数不变
		XBase* ReferenceIncrement()const;
		//与指定对象交换内容
		virtual void SwapWith(XBase&);
		//输出该对象的字符串描述
		virtual XString ToString()const;
		//赋值
		XBase& operator=(const XBase&);
		//默认构造函数
		XBase();
		//使用指定的指针和引用计数来构造
		XBase(XBase*,long refCount);
		//使用一个指针来构造一个引用
		XBase(XBase*);
		//复制构造函数
		XBase(const XBase&);
		//右值复制构造函数
#ifdef _USE_RIGHT_VALUE_REFERENCE
		XBase(const XBase&&);
#endif
		//从只读属性构造
		//template<typename R,typename C,R (C::*PFnGet)()const,ptrdiff_t (*off)()>XBase(const property_get<R,C,PFnGet,off>& x):pObject(NULL),referenceCount(0){*this=XBase((V)x);}
		//从读写属性构造
		//template<typename V,typename C,V (C::*PFnGet)()const,ptrdiff_t (*off)(),void (C::*PFnSet)(V)>XBase(const property_getset<V,C,PFnGet,PFnSet,off>& x):pObject(NULL),referenceCount(0){*this=XBase((V)x);}
		//虚析构函数，使得该类可以被继承
		virtual ~XBase();
		//取地址
		XBase* operator&();
		const XBase* operator&()const;
		//交换方法
		template<typename T1,typename T2>static inline void Swap(T1&t1,T2&t2)
		{
#ifdef _USE_RIGHT_VALUE_REFERENCE
			T1 t((T1&&)t1); t1=t2;t2=(T1&&)t;
#else
			T1 t(t1);t1=t2;t2=t;
#endif
		}
		typedef LJ::MaxValues MaxValues;
		typedef LJ::MinValues MinValues;
		typedef LJ::Bits Bits;
		typedef LJ::Memory Memory;
	};
	//对于一个基于XBase的引用类型（比如XXX类,引用的VXX类），重载和重写的成员函数有：
	//构造空引用			XXX(){}
	//复制构造			XXX(const XXX&x):XBase(x){}
	//构造函数			XXX(VXX*p):XBase(p){}
	//虚析构函数			virtual ~XXX(){}
	//获取指针的引用	VXX* Pointer()const{return reinterpret_cast<VXX*const>(XBase::Pointer());}
	//取地址				XXX* operator&(){return reinterpret_cast<XXX*>(XBase:: operator&());}
	//取地址				const XXX* operator&()const{return reinterpret_cast<const XXX*>(XBase:: operator&());}
	//生成副本指针		virtual XXX* NewCopy()const{return new XXX(*this);}
	//赋值					XXX& operator=(const XXX& x){return reinterpret_cast<XXX&>(XBase::operator=(x));}
	//当前类类型			static const XTypes& CurrentType;
	//获取当前类类型	virtual const XTypes& GetType()const{return CurrentType;}
	//从只读属性构造(已取消)	template<typename R,typename C,ptrdiff_t (*PFnOff)(),R (C::*PFnGet)()const>XXX(const property_get<R,C,PFnGet,PFnOff>& x){*this=XXX((V)x);}
	//从读写属性构造(已取消)	template<typename V,typename C,ptrdiff_t (*PFnOff)(),V (C::*PFnGet)()const,void (C::*PFnSet)(V)>XXX(const property_getset<R,C,PFnGet,PFnSet,PFnOff>& x){*this=XXX((V)x);}
	//从读写属性构造 template<typename T,typename ObjectT>XXX(const Property<T,ObjectT>& p){*this = (T)p;}
	//从只读属性构造 template<typename T,typename ObjectT>XXX(const PropertyReadOnly<T,ObjectT>& p){*this = (T)p;}
	//从读写属性构造 template<typename T,typename ObjectT>XXX(const StaticProperty<T,ObjectT>& p){*this = (T)p;}
	//从只读属性构造 template<typename T,typename ObjectT>XXX(const StaticPropertyReadOnly<T,ObjectT>& p){*this = (T)p;}
#define XBaseRTypeMethods_H(XXX,VXX)\
	/*默认的构造函数*/\
	XXX(){}\
	/*复制构造函数*/\
	XXX(const XXX&x):XBase(x){}\
	/*由被引用类型的指针构造*/\
	XXX(VXX*p):XBase(p){}\
	/*虚析构函数*/\
	virtual ~XXX(){}\
	/*获取pObject,并在其为空时抛出异常*/\
	VXX* Pointer()const{return reinterpret_cast<VXX*const>(XBase::Pointer());}\
	/*重载operator&*/\
	XXX* operator&(){return reinterpret_cast<XXX*>(XBase:: operator&());}\
	/*重载operator&*/\
	const XXX* operator&()const{return reinterpret_cast<const XXX*>(XBase:: operator&());}\
	/*重载operator=*/\
	XXX& operator=(const XXX& x){return reinterpret_cast<XXX&>(XBase::operator=(x));}\
	/*生成该类型的副本并返回其指针。该方法适用于将该类型视作实体类型时*/\
	virtual XXX* NewCopy()const{return new XXX(*this);}\
	/*当前类的类型信息*/\
	static const XTypes& CurrentType;\
	/*动态获取类型信息*/\
	virtual const XTypes& GetType()const{return CurrentType;}\
	/*从属性构造*/\
	template<typename T,typename ObjectT>XXX(const Property<T,ObjectT>& p){*this = (T)p;}\
	/*从属性构造*/\
	template<typename T,typename ObjectT>XXX(const PropertyReadOnly<T,ObjectT>& p){*this = (T)p;}\
	/*从属性构造*/\
	template<typename T,typename ObjectT>XXX(const StaticProperty<T>& p){*this = (T)p;}\
	/*从属性构造*/\
	template<typename T,typename ObjectT>XXX(const StaticPropertyReadOnly<T>& p){*this = (T)p;}\
	/*从属性构造*/
	//template<typename R,typename C,ptrdiff_t (*off)(),R (C::*PFnGet)()const>XXX(const property_get<R,C,PFnGet,off>& x){*this=XXX((R)x);}
	/*从属性构造*/
	//template<typename V,typename C,ptrdiff_t (*off)(),V (C::*PFnGet)()const,void (C::*PFnSet)(V)>XXX(const property_getset<V,C,PFnGet,PFnSet,off>& x){*this=XXX((V)x);}


	#define XBaseIRTypeMethods_H(XXX,IXX)\
	/*默认的构造函数*/\
	XXX(){}\
	/*复制构造函数*/\
	XXX(const XXX&x):XBase(x){}\
	/*虚析构函数*/\
	virtual ~XXX(){}\
	/*获取pObject,并在其为空时抛出异常*/\
	IXX* Pointer()const{return reinterpret_cast<IXX*const>(XBase::Pointer());}\
	/*重载operator&*/\
	XXX* operator&(){return reinterpret_cast<XXX*>(XBase:: operator&());}\
	/*重载operator&*/\
	const XXX* operator&()const{return reinterpret_cast<const XXX*>(XBase:: operator&());}\
	/*重载operator=*/\
	XXX& operator=(const XXX& x){return reinterpret_cast<XXX&>(XBase::operator=(x));}\
	/*生成该类型的副本并返回其指针。该方法适用于将该类型视作实体类型时*/\
	virtual XXX* NewCopy()const{return new XXX(*this);}\
	/*当前类的类型信息*/\
	static const XTypes& CurrentType;\
	/*动态获取类型信息*/\
	virtual const XTypes& GetType()const{return CurrentType;}\
	/*从属性构造*/\
	template<typename T,typename ObjectT>XXX(const Property<T,ObjectT>& p){*this = (T)p;}\
	/*从属性构造*/\
	template<typename T,typename ObjectT>XXX(const PropertyReadOnly<T,ObjectT>& p){*this = (T)p;}\
	/*从属性构造*/\
	template<typename T,typename ObjectT>XXX(const StaticProperty<T>& p){*this = (T)p;}\
	/*从属性构造*/\
	template<typename T,typename ObjectT>XXX(const StaticPropertyReadOnly<T>& p){*this = (T)p;}\


	//对于一个基于XBase的值类型（实体），比如VXX类
	//当前类类型			static const XTypes& CurrentType;
	//获取当前类类型	virtual const XTypes& GetType()const{return CurrentType;}
	//取地址				VXX* operator&(){return reinterpret_cast<VXX*>(XBase:: operator&());}
	//取地址				const VXX* operator&()const{return reinterpret_cast<const VXX*>(XBase:: operator&());}
	//生成副本指针		virtual VXX* NewCopy()const{return new VXX(*this);}
	//从属性构造			template<typename R,typename C,ptrdiff_t (*off)(),R (C::*PFnGet)()const>XXX(const property_get<R,C,PFnGet,off>& x){*this=XXX((R)x);}
	//从属性构造			template<typename V,typename C,ptrdiff_t (*off)(),V (C::*PFnGet)()const,void (C::*PFnSet)(V)>XXX(const property_getset<V,C,PFnGet,PFnSet,off>& x){*this=XXX((V)x);}
	//从属性构造			template<typename T,typename ObjectT>XXX(const Property<T,ObjectT>& p){*this = (T)p;}
	//从属性构造			template<typename T,typename ObjectT>XXX(const PropertyReadOnly<T,ObjectT>& p){*this = (T)p;}
	//从属性构造			template<typename T,typename ObjectT>XXX(const StaticProperty<T>& p){*this = (T)p;}
	//从属性构造			template<typename T,typename ObjectT>XXX(const StaticPropertyReadOnly<T>& p){*this = (T)p;}
#define XBaseVTypeMethods_H(VXX)\
	/*当前类的类型信息*/\
	static const XTypes& CurrentType;\
	/*动态获取类型信息*/\
	virtual const XTypes& GetType()const{return CurrentType;}\
	/*重载operator&*/\
	VXX* operator&(){return reinterpret_cast<VXX*>(XBase:: operator&());}\
	/*重载operator&*/\
	const VXX* operator&()const{return reinterpret_cast<const VXX*>(XBase:: operator&());}\
	/*生成该类型的副本并返回其指针。该方法适用于将该类型视作实体类型时*/\
	virtual VXX* NewCopy()const{return new VXX(*this);}\
	/*从属性构造*/\
	template<typename T,typename ObjectT>VXX(const Property<T,ObjectT>& p){*this = (T)p;}\
	/*从属性构造*/\
	template<typename T,typename ObjectT>VXX(const PropertyReadOnly<T,ObjectT>& p){*this = (T)p;}\
	/*从属性构造*/\
	template<typename T,typename ObjectT>VXX(const StaticProperty<T>& p){*this = (T)p;}\
	/*从属性构造*/\
	template<typename T,typename ObjectT>VXX(const StaticPropertyReadOnly<T>& p){*this = (T)p;}\
	/*从属性构造*/
	//template<typename R,typename C,ptrdiff_t (*off)(),R (C::*PFnGet)()const>VXX(const property_get<R,C,PFnGet,off>& x){*this=VXX((R)x);}
	/*从属性构造*/
	//template<typename V,typename C,ptrdiff_t (*off)(),V (C::*PFnGet)()const,void (C::*PFnSet)(V)>VXX(const property_getset<V,C,PFnGet,PFnSet,off>& x){*this=XXX((V)x);}
	//以下方法需要手动补充
	//虚析构函数			virtual ~VXX(){。。。}
	//复制构造函数		VXX(const VXX& x){。。。}
	//交换内容			virtual void SwapWith(XBase& x){。。。}
	//赋值					VXX& operator=(const VXX& x){。。。return *this;}


	//对于一个基于XBase的接口类型，比如IXX类
	//当前类类型			static const XTypes& CurrentType;
	//获取当前类类型	virtual const XTypes& GetType()const{return CurrentType;}
	//取地址				IXX* operator&(){return reinterpret_cast<IXX*>(XBase:: operator&());}
	//取地址				const IXX* operator&()const{return reinterpret_cast<const IXX*>(XBase:: operator&());}
#define XBaseITypeMethods_H(IXX)\
	/*当前类的类型信息*/\
	static const XTypes& CurrentType;\
	/*动态获取类型信息*/\
	virtual const XTypes& GetType()const{return CurrentType;}\
	/*重载operator&*/\
	IXX* operator&(){return reinterpret_cast<IXX*>(XBase:: operator&());}\
	/*重载operator&*/\
	const IXX* operator&()const{return reinterpret_cast<const IXX*>(XBase:: operator&());}\
	//以下方法需要手动补充
	//虚析构函数			virtual ~VXX(){。。。}
}