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
#ifdef _DEBUG//��һ����Debugģʽ�µ��ڴ�й¶�����ƣ������õĹ���������ڴ�й¶���������ʱ������

	//ע�� Ҫ�ѡ��������ɡ��е�����ʱ������Ϊ/MDd��/MTd�����򽫳������Ӵ���

#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <assert.h>
#define new DEBUG_CLIENTBLOCK
#if (_M_CEE == 1) ||  (1==_MANAGED) //�й�֧��
	static int __clrcall _Exit_L_()
	{
		//int i = _CrtDumpMemoryLeaks();//�ڴ�й¶�������������ĵ���ҳ��˫�������ҵ�й¶λ��
		//assert( i == 0);//����ȫ�ֵľ�̬���󣬿����ڸ�����Żᱻ�ͷţ�������ʾ���ڴ�й¶��������
		//�����뽫int i = _CrtDumpMemoryLeaks();�ŵ���Ϊ���������������λ��
		//�����Ѿ�Ǩ�Ƶ�NodeOfClassType������������
		return 0;
	}
	static _onexit_m_t _d_e_b_ug = (
		_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF),//�����ڴ�й¶��ⱨ��
		_onexit_m(&_Exit_L_));//�������ʱ���
#else
	static void _Exit_L_()//�������atexit();���ʹ��
	{
		//int i = _CrtDumpMemoryLeaks();//�ڴ�й¶�������������ĵ���ҳ��˫�������ҵ�й¶λ��
		//assert( i == 0);//����ȫ�ֵľ�̬���󣬿����ڸ�����Żᱻ�ͷţ�������ʾ���ڴ�й¶��������
		//�����뽫int i = _CrtDumpMemoryLeaks();�ŵ���Ϊ���������������λ��
		//�����Ѿ�Ǩ�Ƶ�NodeOfClassType������������
	}
	static int _d_e_b_ug = (
		_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF),//�����ڴ�й¶��ⱨ��
		//_CrtSetBreakAlloc(15),//�����Զ��ϵ�λ��
		atexit(_Exit_L_));//�������ʱ���
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
		//��ȡiǰ��0�ı�����
		static int LeftZeroCount64(unsigned long long i);
		//��pSourceָ���ڴ��startBitPositonλ����bitsCount���ص�pDestinationָ���ڴ��destinationBitPositionλ����Դ�ڴ��Ŀ���ڴ治���ص�
		static void Copy(void* pSource,unsigned startBitPositon,unsigned bitsCount,void* pDestination,unsigned destinationBitPosition=0);
		//��pSourceָ���ڴ�����bitsCount���ص�pDestinationָ���ڴ��destinationBitPositionλ����Դ�ڴ��Ŀ���ڴ治���ص�
		static void Copy(void* pSource,unsigned bitsCount,void* pDestination,unsigned destinationBitPosition=0){Bits::Copy(pSource,0,bitsCount, pDestination,destinationBitPosition);}
		//��p��ָ����ڴ��startBitPosition�������bitsCount������Ϊbit��ֵ
		static void Set(void* p,unsigned startBitPosition,unsigned bitsCount,bool bitValue=false);
		//��pָ����ڴ��startBitPosition����λ��bitsCount���ص����ݽ���mov����λ�ƣ���Ϊ���ƣ���Ϊ����
		static void Move(void* p,unsigned startBitPosition,unsigned bitsCount,int mov);
		//�Ƚ������ڴ����Ĵ�С���Ӹ�λ����λ�Ƚϣ���strcmp��˳���෴
		static int Compare(void* pSource,unsigned startBitPositon,unsigned bitsCount,void* pDestination,unsigned destinationBitPosition=0);
		//�Ƚ������ڴ����Ĵ�С���Ӹ�λ����λ�Ƚϣ���strcmp��˳���෴
		static int  Compare(void* pSource,unsigned bitsCount,void* pDestination,unsigned destinationBitPosition=0){return Bits::Compare(pSource,0,bitsCount, pDestination,destinationBitPosition);}
		//��ȡĳ����λ�ϵ�����
		static bool Get(const void* pSource,long long bitPosition);
	};
	struct Memory
	{
		//�ڴ渴��,pDestinationָ��Ŀ���ڴ棬pSourceָ��Դ���ݣ�sizeInBytes�ǰ��ֽ�����ʾ�Ĵ�С��Դ��������Ŀ���ڴ治���ص�
		static void Copy(void* pDestination,const void* pSource,size_t SizeInBytes);
		//�ڴ��ƶ����ڴ渴�ƵĿ������ص��汾��
		static void Move(void* pDestination,const void* pSource,size_t sizeInBytes);
		//�����ڴ渴�Ʒ�����Ȼ�Ƚ��ѿ�
		template<const int SizeInBytes,class T1,class T2>static inline void Copy(T1 *const & pDestination,const T2*const& pSource)
		{
			*reinterpret_cast<structSize<SizeInBytes>*>(pDestination) = *reinterpret_cast<const structSize<SizeInBytes>*>(pSource);
		}
	};
	//����
	class XBase
	{
	protected:
		//һ��ָ��Xbase�����ָ���ָ��ֵΪNULLʱ����ʾ������Ϊ�����ã����pObjectָ���������ʾ�ö���Ϊ�����õ��ս�� 
		XBase* pObject;
		//��ȡָ������ã���IsNull()ʱ�����ø÷������׳��쳣
		XBase* Pointer()const;
		//��ȡthisָ��
		inline XBase* ThisPointer()const{return const_cast<XBase*>(this);}
		//�ö������õĴ��������������ֵС��0����ʾ�ö����ܱ����á� ��������������У���ֵ����Ϊ0�����ʾ�ö���δ�����á�
		mutable volatile long referenceCount;
	public:
		//�жϸö����Ƿ���Ա����ã����referenceCountС��0�򷵻�false������referenceCount<0��ʵ��������ͨ����ֵת��Ϊԭʼֵ
		bool CanBeReferenced()const;
		//��ǰ�������
		static const XTypes& CurrentType;
		//�Ƚϸö�����object�����Ƿ���ͬһ������
		virtual bool Equals(const XBase& object)const;
		//�Ƚ�
		bool operator==(const XBase& object)const{return Equals(object);}
		//��ȡ����������Ϣ
		virtual const XTypes& GetType()const;
		//�жϸö����Ƿ�Ϊ�����ã�����pObjectΪNULLʱ����true��
		bool IsNull()const;
		//�жϸö����Ƿ��������ս�㣨��ԭʼֵ�������pObjectָ�������򷵻�true������pObjectָ�������ʵ��������ͨ����ֵת��Ϊ����
		bool IsReferenceEnding()const;
		//����һ�������������ظø�����ָ��
		virtual XBase* NewCopy()const;
		//���ٸö������õĴ�����Ӧ����ԭ�Ӳ�����������ü�������СΪ0���������ɾ������
		void ReferenceDecrement()const;
		//�ж϶�����object�������õ��Ƿ���ͬһ�����󣬼�pObject���ʱ����true
		bool ReferenceEquals(const XBase& object)const;
		//���Ӹö������õĴ�����Ӧ����ԭ�Ӳ��������ظö���ָ�롣���referenceCountС��0����÷�������NULL���������ü�������
		XBase* ReferenceIncrement()const;
		//��ָ�����󽻻�����
		virtual void SwapWith(XBase&);
		//����ö�����ַ�������
		virtual XString ToString()const;
		//��ֵ
		XBase& operator=(const XBase&);
		//Ĭ�Ϲ��캯��
		XBase();
		//ʹ��ָ����ָ������ü���������
		XBase(XBase*,long refCount);
		//ʹ��һ��ָ��������һ������
		XBase(XBase*);
		//���ƹ��캯��
		XBase(const XBase&);
		//��ֵ���ƹ��캯��
#ifdef _USE_RIGHT_VALUE_REFERENCE
		XBase(const XBase&&);
#endif
		//��ֻ�����Թ���
		//template<typename R,typename C,R (C::*PFnGet)()const,ptrdiff_t (*off)()>XBase(const property_get<R,C,PFnGet,off>& x):pObject(NULL),referenceCount(0){*this=XBase((V)x);}
		//�Ӷ�д���Թ���
		//template<typename V,typename C,V (C::*PFnGet)()const,ptrdiff_t (*off)(),void (C::*PFnSet)(V)>XBase(const property_getset<V,C,PFnGet,PFnSet,off>& x):pObject(NULL),referenceCount(0){*this=XBase((V)x);}
		//������������ʹ�ø�����Ա��̳�
		virtual ~XBase();
		//ȡ��ַ
		XBase* operator&();
		const XBase* operator&()const;
		//��������
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
	//����һ������XBase���������ͣ�����XXX��,���õ�VXX�ࣩ�����غ���д�ĳ�Ա�����У�
	//���������			XXX(){}
	//���ƹ���			XXX(const XXX&x):XBase(x){}
	//���캯��			XXX(VXX*p):XBase(p){}
	//����������			virtual ~XXX(){}
	//��ȡָ�������	VXX* Pointer()const{return reinterpret_cast<VXX*const>(XBase::Pointer());}
	//ȡ��ַ				XXX* operator&(){return reinterpret_cast<XXX*>(XBase:: operator&());}
	//ȡ��ַ				const XXX* operator&()const{return reinterpret_cast<const XXX*>(XBase:: operator&());}
	//���ɸ���ָ��		virtual XXX* NewCopy()const{return new XXX(*this);}
	//��ֵ					XXX& operator=(const XXX& x){return reinterpret_cast<XXX&>(XBase::operator=(x));}
	//��ǰ������			static const XTypes& CurrentType;
	//��ȡ��ǰ������	virtual const XTypes& GetType()const{return CurrentType;}
	//��ֻ�����Թ���(��ȡ��)	template<typename R,typename C,ptrdiff_t (*PFnOff)(),R (C::*PFnGet)()const>XXX(const property_get<R,C,PFnGet,PFnOff>& x){*this=XXX((V)x);}
	//�Ӷ�д���Թ���(��ȡ��)	template<typename V,typename C,ptrdiff_t (*PFnOff)(),V (C::*PFnGet)()const,void (C::*PFnSet)(V)>XXX(const property_getset<R,C,PFnGet,PFnSet,PFnOff>& x){*this=XXX((V)x);}
	//�Ӷ�д���Թ��� template<typename T,typename ObjectT>XXX(const Property<T,ObjectT>& p){*this = (T)p;}
	//��ֻ�����Թ��� template<typename T,typename ObjectT>XXX(const PropertyReadOnly<T,ObjectT>& p){*this = (T)p;}
	//�Ӷ�д���Թ��� template<typename T,typename ObjectT>XXX(const StaticProperty<T,ObjectT>& p){*this = (T)p;}
	//��ֻ�����Թ��� template<typename T,typename ObjectT>XXX(const StaticPropertyReadOnly<T,ObjectT>& p){*this = (T)p;}
#define XBaseRTypeMethods_H(XXX,VXX)\
	/*Ĭ�ϵĹ��캯��*/\
	XXX(){}\
	/*���ƹ��캯��*/\
	XXX(const XXX&x):XBase(x){}\
	/*�ɱ��������͵�ָ�빹��*/\
	XXX(VXX*p):XBase(p){}\
	/*����������*/\
	virtual ~XXX(){}\
	/*��ȡpObject,������Ϊ��ʱ�׳��쳣*/\
	VXX* Pointer()const{return reinterpret_cast<VXX*const>(XBase::Pointer());}\
	/*����operator&*/\
	XXX* operator&(){return reinterpret_cast<XXX*>(XBase:: operator&());}\
	/*����operator&*/\
	const XXX* operator&()const{return reinterpret_cast<const XXX*>(XBase:: operator&());}\
	/*����operator=*/\
	XXX& operator=(const XXX& x){return reinterpret_cast<XXX&>(XBase::operator=(x));}\
	/*���ɸ����͵ĸ�����������ָ�롣�÷��������ڽ�����������ʵ������ʱ*/\
	virtual XXX* NewCopy()const{return new XXX(*this);}\
	/*��ǰ���������Ϣ*/\
	static const XTypes& CurrentType;\
	/*��̬��ȡ������Ϣ*/\
	virtual const XTypes& GetType()const{return CurrentType;}\
	/*�����Թ���*/\
	template<typename T,typename ObjectT>XXX(const Property<T,ObjectT>& p){*this = (T)p;}\
	/*�����Թ���*/\
	template<typename T,typename ObjectT>XXX(const PropertyReadOnly<T,ObjectT>& p){*this = (T)p;}\
	/*�����Թ���*/\
	template<typename T,typename ObjectT>XXX(const StaticProperty<T>& p){*this = (T)p;}\
	/*�����Թ���*/\
	template<typename T,typename ObjectT>XXX(const StaticPropertyReadOnly<T>& p){*this = (T)p;}\
	/*�����Թ���*/
	//template<typename R,typename C,ptrdiff_t (*off)(),R (C::*PFnGet)()const>XXX(const property_get<R,C,PFnGet,off>& x){*this=XXX((R)x);}
	/*�����Թ���*/
	//template<typename V,typename C,ptrdiff_t (*off)(),V (C::*PFnGet)()const,void (C::*PFnSet)(V)>XXX(const property_getset<V,C,PFnGet,PFnSet,off>& x){*this=XXX((V)x);}


	#define XBaseIRTypeMethods_H(XXX,IXX)\
	/*Ĭ�ϵĹ��캯��*/\
	XXX(){}\
	/*���ƹ��캯��*/\
	XXX(const XXX&x):XBase(x){}\
	/*����������*/\
	virtual ~XXX(){}\
	/*��ȡpObject,������Ϊ��ʱ�׳��쳣*/\
	IXX* Pointer()const{return reinterpret_cast<IXX*const>(XBase::Pointer());}\
	/*����operator&*/\
	XXX* operator&(){return reinterpret_cast<XXX*>(XBase:: operator&());}\
	/*����operator&*/\
	const XXX* operator&()const{return reinterpret_cast<const XXX*>(XBase:: operator&());}\
	/*����operator=*/\
	XXX& operator=(const XXX& x){return reinterpret_cast<XXX&>(XBase::operator=(x));}\
	/*���ɸ����͵ĸ�����������ָ�롣�÷��������ڽ�����������ʵ������ʱ*/\
	virtual XXX* NewCopy()const{return new XXX(*this);}\
	/*��ǰ���������Ϣ*/\
	static const XTypes& CurrentType;\
	/*��̬��ȡ������Ϣ*/\
	virtual const XTypes& GetType()const{return CurrentType;}\
	/*�����Թ���*/\
	template<typename T,typename ObjectT>XXX(const Property<T,ObjectT>& p){*this = (T)p;}\
	/*�����Թ���*/\
	template<typename T,typename ObjectT>XXX(const PropertyReadOnly<T,ObjectT>& p){*this = (T)p;}\
	/*�����Թ���*/\
	template<typename T,typename ObjectT>XXX(const StaticProperty<T>& p){*this = (T)p;}\
	/*�����Թ���*/\
	template<typename T,typename ObjectT>XXX(const StaticPropertyReadOnly<T>& p){*this = (T)p;}\


	//����һ������XBase��ֵ���ͣ�ʵ�壩������VXX��
	//��ǰ������			static const XTypes& CurrentType;
	//��ȡ��ǰ������	virtual const XTypes& GetType()const{return CurrentType;}
	//ȡ��ַ				VXX* operator&(){return reinterpret_cast<VXX*>(XBase:: operator&());}
	//ȡ��ַ				const VXX* operator&()const{return reinterpret_cast<const VXX*>(XBase:: operator&());}
	//���ɸ���ָ��		virtual VXX* NewCopy()const{return new VXX(*this);}
	//�����Թ���			template<typename R,typename C,ptrdiff_t (*off)(),R (C::*PFnGet)()const>XXX(const property_get<R,C,PFnGet,off>& x){*this=XXX((R)x);}
	//�����Թ���			template<typename V,typename C,ptrdiff_t (*off)(),V (C::*PFnGet)()const,void (C::*PFnSet)(V)>XXX(const property_getset<V,C,PFnGet,PFnSet,off>& x){*this=XXX((V)x);}
	//�����Թ���			template<typename T,typename ObjectT>XXX(const Property<T,ObjectT>& p){*this = (T)p;}
	//�����Թ���			template<typename T,typename ObjectT>XXX(const PropertyReadOnly<T,ObjectT>& p){*this = (T)p;}
	//�����Թ���			template<typename T,typename ObjectT>XXX(const StaticProperty<T>& p){*this = (T)p;}
	//�����Թ���			template<typename T,typename ObjectT>XXX(const StaticPropertyReadOnly<T>& p){*this = (T)p;}
#define XBaseVTypeMethods_H(VXX)\
	/*��ǰ���������Ϣ*/\
	static const XTypes& CurrentType;\
	/*��̬��ȡ������Ϣ*/\
	virtual const XTypes& GetType()const{return CurrentType;}\
	/*����operator&*/\
	VXX* operator&(){return reinterpret_cast<VXX*>(XBase:: operator&());}\
	/*����operator&*/\
	const VXX* operator&()const{return reinterpret_cast<const VXX*>(XBase:: operator&());}\
	/*���ɸ����͵ĸ�����������ָ�롣�÷��������ڽ�����������ʵ������ʱ*/\
	virtual VXX* NewCopy()const{return new VXX(*this);}\
	/*�����Թ���*/\
	template<typename T,typename ObjectT>VXX(const Property<T,ObjectT>& p){*this = (T)p;}\
	/*�����Թ���*/\
	template<typename T,typename ObjectT>VXX(const PropertyReadOnly<T,ObjectT>& p){*this = (T)p;}\
	/*�����Թ���*/\
	template<typename T,typename ObjectT>VXX(const StaticProperty<T>& p){*this = (T)p;}\
	/*�����Թ���*/\
	template<typename T,typename ObjectT>VXX(const StaticPropertyReadOnly<T>& p){*this = (T)p;}\
	/*�����Թ���*/
	//template<typename R,typename C,ptrdiff_t (*off)(),R (C::*PFnGet)()const>VXX(const property_get<R,C,PFnGet,off>& x){*this=VXX((R)x);}
	/*�����Թ���*/
	//template<typename V,typename C,ptrdiff_t (*off)(),V (C::*PFnGet)()const,void (C::*PFnSet)(V)>VXX(const property_getset<V,C,PFnGet,PFnSet,off>& x){*this=XXX((V)x);}
	//���·�����Ҫ�ֶ�����
	//����������			virtual ~VXX(){������}
	//���ƹ��캯��		VXX(const VXX& x){������}
	//��������			virtual void SwapWith(XBase& x){������}
	//��ֵ					VXX& operator=(const VXX& x){������return *this;}


	//����һ������XBase�Ľӿ����ͣ�����IXX��
	//��ǰ������			static const XTypes& CurrentType;
	//��ȡ��ǰ������	virtual const XTypes& GetType()const{return CurrentType;}
	//ȡ��ַ				IXX* operator&(){return reinterpret_cast<IXX*>(XBase:: operator&());}
	//ȡ��ַ				const IXX* operator&()const{return reinterpret_cast<const IXX*>(XBase:: operator&());}
#define XBaseITypeMethods_H(IXX)\
	/*��ǰ���������Ϣ*/\
	static const XTypes& CurrentType;\
	/*��̬��ȡ������Ϣ*/\
	virtual const XTypes& GetType()const{return CurrentType;}\
	/*����operator&*/\
	IXX* operator&(){return reinterpret_cast<IXX*>(XBase:: operator&());}\
	/*����operator&*/\
	const IXX* operator&()const{return reinterpret_cast<const IXX*>(XBase:: operator&());}\
	//���·�����Ҫ�ֶ�����
	//����������			virtual ~VXX(){������}
}