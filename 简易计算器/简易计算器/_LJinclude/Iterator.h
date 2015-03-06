#pragma once
namespace LJ
{
	//迭代器接口，封装操作方法
	template<typename T>struct IIterator
	{
		//迭代器长度
		int Length;
		//构造时必须传入长度
		IIterator(int length):Length(length){}
		//遍历下一个元素
		virtual void Next()=0;
		//遍历上一个元素
		virtual void Fore()=0;
		//跳跃下n个元素
		virtual void NextN(int n)=0;
		//跳跃上n个元素
		virtual void ForeN(int n)=0;
		//相减
		virtual int Minus(IIterator*p)=0;
		//跳转到最后一个
		virtual bool ToLast()=0;
		//跳转到终结位置
		virtual bool ToEnd()=0;
		//重置到开头
		virtual void Reset()=0;
		//产生一个副本
		virtual IIterator* NewCopy()=0;
		//获取当前的索引号
		virtual int GetCurrentIndex()=0;
		//索引
		virtual T& Index(int index)=0;
		//获取当前指针
		virtual T*Current()=0;
		//获取最后一个元素的指针
		virtual T*Last()=0;
		//获取第一个元素的指针
		virtual T*First()=0;
		//获取终结元素的指针
		virtual T*End()=0;
		//迭代器比较
		virtual int CompareWith(IIterator*)=0;
		//析构
		virtual ~IIterator(){}
	};
	template<typename T>class Iterator
	{
		friend Iterator<const T>;
	public:
#ifdef _XUTILITY_
		typedef typename std::random_access_iterator_tag iterator_category;
		typedef typename T value_type;
		typedef int difference_type;
		typedef typename T* pointer;
		typedef typename T& reference;
#endif
		PROPERTY_OFFSET(Iterator,Length);
		//构造函数
		inline Iterator(IIterator<T>* pIterator):pIterator(pIterator){}
		//复制构造函数
		inline Iterator(const Iterator& t):pIterator(t.pIterator->NewCopy()){}
		//构造函数
		inline Iterator(const Iterator<const T>& t)	:pIterator(t.pIterator->NewCopy()){}
		//设置当前项（一般默认初始为第一项）
		void SetCurrent(T t){*pIterator->Current() = t;}
		//获取当前项（一般默认初始为第一项）
		T GetCurrent()const{return *pIterator->Current();}
		//调用++*this，返回pCurrent!=pEnd
		bool MoveNext(){++*this;return pIterator->Current()!=pIterator->End();}
		//指针移动到最后一项
		bool MoveToLast(){return pIterator->ToLast();}
		//指针移动到终结项
		bool MoveToEnd(){return pIterator->ToEnd();}
		//重置为开始项
		Iterator& Reset(){pIterator->Reset();return *this;}
		int GetLength()const{return pIterator->Length;}
		union
		{
			//通用迭代器
			IIterator<T>* pIterator;
			//属性：当前项
			PROPERTY_GETSET(T,Iterator,GetCurrent,SetCurrent,Current);
			//属性：长度
			PROPERTY_GET(int,Iterator,GetLength,Length);
		};
		operator T*const()const{return pIterator->Current();}
		Iterator& operator+=(int move){pIterator->NextN(move);return*this;}
		Iterator& operator-=(int move){pIterator->ForeN(move);return*this;}
		Iterator operator++(int){Iterator<T>tmp(*this);++*this;return tmp;}
		Iterator operator--(int){Iterator<T>tmp(*this);--*this;return tmp;}
		Iterator& operator++(){pIterator->Next();return*this;}
		Iterator& operator--(){pIterator->Fore();return*this;}
		Iterator operator-(int move)const{Iterator<T>tmp(*this);return tmp-=move;}
		int operator-(const Iterator& t)const{return pIterator->Minus(t.pIterator);}
		int operator-(const Iterator<const T>& t)const{return pIterator->Minus(t.pIterator);}
		Iterator operator+(int move)const{Iterator<T>tmp(*this);return tmp+=move;}
		friend Iterator operator+(int move,const Iterator<T>&t){return t+move;}
		int GetCurrentIndex()const{return pIterator->GetCurrentIndex();}
		T& operator[](int index){return pIterator->Index(index);}
		const T& operator[](int index)const{return pIterator->Index(index);}
		bool operator>(const Iterator& x)const{return pIterator->CompareWith(x.pIterator)>0;}
		bool operator>=(const Iterator& x)const{return pIterator->CompareWith(x.pIterator)>=0;}
		bool operator<(const Iterator& x)const{return pIterator->CompareWith(x.pIterator)<0;}
		bool operator<=(const Iterator& x)const{return pIterator->CompareWith(x.pIterator)<=0;}
		bool operator==(const Iterator& x)const{return pIterator->CompareWith(x.pIterator)==0;}
		bool operator!=(const Iterator& x)const{return pIterator->CompareWith(x.pIterator)!=0;}
		bool operator>(const Iterator<const T>& x)const{return pIterator->CompareWith(x.pIterator)>0;}
		bool operator>=(const Iterator<const T>& x)const{return pIterator->CompareWith(x.pIterator)>=0;}
		bool operator<(const Iterator<const T>& x)const{return pIterator->CompareWith(x.pIterator)<0;}
		bool operator<=(const Iterator<const T>& x)const{return pIterator->CompareWith(x.pIterator)<=0;}
		bool operator==(const Iterator<const T>& x)const{return pIterator->CompareWith(x.pIterator)==0;}
		bool operator!=(const Iterator<const T>& x)const{return pIterator->CompareWith(x.pIterator)!=0;}
		T* GetFirstElementPointer(){return pIterator->First();}
		T* GetLastElementPointer(){return pIterator->Last();}
		~Iterator(){delete pIterator;}
	};
	template<typename T>class Iterator<const T>
	{
		friend Iterator<T>;
	public:
#ifdef _XUTILITY_
		typedef typename std::random_access_iterator_tag iterator_category;
		typedef typename T const value_type;
		typedef int difference_type;
		typedef typename T const* pointer;
		typedef typename T const& reference;
#endif
		PROPERTY_OFFSET(Iterator,Length);
		//构造函数
		Iterator(IIterator<T>* pIterator):pIterator(pIterator){}
		//复制构造函数
		Iterator(const Iterator& t):pIterator(t.pIterator->NewCopy()){}
		explicit Iterator(const Iterator<T>& t):pIterator(t.pIterator->NewCopy()){}
		//获取当前项（一般默认初始为第一项）
		const T GetCurrent()const{return *pIterator->Current();}
		//获取元素数
		int GetLength()const{return pIterator->Length;}
		//调用++*this，返回pCurrent!=pEnd
		bool MoveNext(){++*this;return pIterator->Current()!=pIterator->End();}
		//指针移动到最后一项
		bool MoveToLast(){return pIterator->ToLast();}
		//指针移动到终结项
		bool MoveToEnd(){return pIterator->ToEnd();}
		//重置为开始项
		Iterator& Reset(){pIterator->Reset();return *this;}
		union
		{
			//通用迭代器
			IIterator<T>* pIterator;
			//属性：当前项
			PROPERTY_GET(const T,Iterator,GetCurrent,Current);
			//属性：长度
			PROPERTY_GET(int,Iterator,GetLength,Length);
		};
		operator const T*const()const{return pIterator->Current();}
		Iterator& operator+=(int move){pIterator->NextN(move);return*this;}
		Iterator& operator-=(int move){pIterator->ForeN(move);return*this;}
		Iterator operator++(int){Iterator<const T>tmp(*this);++*this;return tmp;}
		Iterator operator--(int){Iterator<const T>tmp(*this);--*this;return tmp;}
		Iterator& operator++(){pIterator->Next();return*this;}
		Iterator& operator--(){pIterator->Fore();return*this;}
		Iterator operator-(int move)const{Iterator<const T>tmp(*this);return tmp-=move;}
		int operator-(const Iterator& t)const{return pIterator->Minus(t.pIterator);}
		int operator-(const Iterator<T>& t)const{return pIterator->Minus(t.pIterator);}
		Iterator operator+(int move)const{Iterator<const T>tmp(*this);return tmp+=move;}
		friend Iterator operator+(int move,const Iterator<const T>&t){return t+move;}
		int GetCurrentIndex()const{return pIterator->GetCurrentIndex();}
		const T& operator[](int index)const{return pIterator->Index(index);}
		bool operator>(const Iterator& x)const{return pIterator->CompareWith(x.pIterator)>0;}
		bool operator>=(const Iterator& x)const{return pIterator->CompareWith(x.pIterator)>=0;}
		bool operator<(const Iterator& x)const{return pIterator->CompareWith(x.pIterator)<0;}
		bool operator<=(const Iterator& x)const{return pIterator->CompareWith(x.pIterator)<=0;}
		bool operator==(const Iterator& x)const{return pIterator->CompareWith(x.pIterator)==0;}
		bool operator!=(const Iterator& x)const{return pIterator->CompareWith(x.pIterator)!=0;}
		bool operator>(const Iterator<T>& x)const{return pIterator->CompareWith(x.pIterator)>0;}
		bool operator>=(const Iterator<T>& x)const{return pIterator->CompareWith(x.pIterator)>=0;}
		bool operator<(const Iterator<T>& x)const{return pIterator->CompareWith(x.pIterator)<0;}
		bool operator<=(const Iterator<T>& x)const{return pIterator->CompareWith(x.pIterator)<=0;}
		bool operator==(const Iterator<T>& x)const{return pIterator->CompareWith(x.pIterator)==0;}
		bool operator!=(const Iterator<T>& x)const{return pIterator->CompareWith(x.pIterator)!=0;}
		const T* GetFirstElementPointer()const{return pIterator->First();}
		const T* GetLastElementPointer()const{return pIterator->Last();}
		~Iterator(){delete pIterator;}
	};
}