#pragma once
namespace LJ
{
	template<typename T>struct ICollectionIterator;
	//表示一个特殊的容器，该容器与数组类似，支持储存禁止复制构造函数的类对象，与VArray相比不提供operator T*
	template<class T>class VCollection:public XBase
	{
		friend XCollection<T>;
		//指针数组
		VArray<T*> pArray;
	public:
		//默认构造
		VCollection(){}
		//由数组构造
		template<class AnyT>VCollection(const VArray<AnyT>& x)
		{
			pArray.Resize(x.Length);
			for(int i=0;i<pArray.Length;++i)pArray[i] = new T(x[i]);
		}
		//由数组构造
		template<class AnyT>VCollection(const XArray<AnyT>& x)
		{
			pArray.Resize(x.Length);
			for(int i=0;i<pArray.Length;++i)pArray[i] = new T(x[i]);
		}
		//析构函数
		~VCollection()
		{
			for(int i=0;i<pArray.Length;++i)delete pArray[i];
		}
		//复制构造函数
		template<class AnyT>VCollection(const VCollection<AnyT>& x)
		{
			pArray.Resize(x.pArray.Length);
			for(int i=0;i<pArray.Length;++i)pArray[i] = new T(*x.pArray[i]);
		}

		//提供使用下标进行的随机访问，这个过程将保证只有一个线程在操作
		T& operator[](int index)
		{
			if(index<0 || index>=pArray.Length){throw XException(E_INVALIDARG);}
			T& tmp(*pArray[index]);
			return tmp;
		}
		//迭代器
		XIterator<T> First()
		{
			if(pArray.Length==0)return XIterator<T>(0,0,0);
			return XIterator<T>(new ICollectionIterator<T>(pArray[0],pArray[0],pArray[pArray.Length-1],NULL,pArray));
		}
		//放入一个元素，并返回列表中新增元素的引用，这个过程将保证只有一个线程在操作
		template<class AnyT> T& Append(const AnyT& t)
		{
			pArray.Resize(pArray.Length+1);
			T* p = new T(t);
			pArray.LastElement() = p;
			return *p;
		}

		//复制前count个元素到数组中，如果数组容量不够，则复制尽量多的内容
		XArray<T> CopyToArray(XArray<T> rArray)const
		{
			if(rArray.IsNull())throw XException(E_POINTER);
			T* p = rArray;
			T* pEnd = p+rArray.Length;
			T*const* pp =pArray;
			T*const* ppEnd =pArray+pArray.Length;
			while(p<pEnd && pp<ppEnd){*p++=**pp++;}
			return rArray;
		}
		//复制前count个元素到数组中，如果数组容量不够，将抛出异常
		XArray<T> CopyToArray(XArray<T> rArray,int count)const
		{
			if(count<0)throw XException(E_INVALIDARG);
			if(count>pArray.Length || count>rArray.Length){throw XException(COR_E_INDEXOUTOFRANGE);}
			T* p = rArray;
			T* pEnd = p+count;
			T*const* pp =pArray;
			while(p<pEnd){*p++=**pp++;}
			return rArray;
		}
		//复制所有内容到新数组中
		XArray<T> ToArray()const
		{
			
			XArray<T> rArray(pArray.Length);
			T* p = rArray;
			T* pEnd = p+pArray.Length;
			T*const* pp =pArray;
			while(p<pEnd){*p++=**pp++;}
			
			return rArray;
		}
		//复制count个元素到新数组中
		XArray<T> ToArray(int count)const
		{
			if(count<0)throw XException(E_INVALIDARG);
			
			if(count>Length){throw XException(COR_E_INDEXOUTOFRANGE);}
			XArray<T> rArray(count);
			T* p = rArray;
			T* pEnd = p+count;
			T*const* pp =pArray;
			while(p<pEnd){*p++=**pp++;}
			
			return rArray;
		}
		//取所有元素到指定数组中，并移除，用数组末端的元素替代，如果数组容量不够，则移动尽量多的内容
		XArray<T> MoveToArray(XArray<T> rArray)
		{
			if(rArray.IsNull())throw XException(E_POINTER);
			
			T* p = rArray;
			T* pEnd = p+rArray.Length;
			T*const* pp =pArray;
			T*const* ppEnd =pArray+pArray.Length;
			while(p<pEnd && pp<ppEnd){*p++=**pp++;}
			int count = rArray.Length;
			while(count--)pArray[count] = pArray[pArray.Length-count-1];
			pArray.Resize(pArray.Length-rArray.Length);
			
			return rArray;
		}
		//取前count个元素到数组中，并移除，用数组末端的元素替代，如果数组容量不够，则抛出异常
		XArray<T> MoveToArray(XArray<T> rArray,int count)
		{
			if(rArray.IsNull())throw XException(E_POINTER);
			if(count<0)throw XException(E_INVALIDARG);
			
			if(count>pArray.Length || count>rArray.Length){throw XException(COR_E_INDEXOUTOFRANGE);}
			T* p = rArray;
			T* pEnd = p+count;
			T*const* pp =pArray;
			while(p<pEnd){*p++=**pp++;}
			for(int i=0;i<count;++i)pArray[i] = pArray[pArray.Length-i-1];
			pArray.Resize(pArray.Length-count);
			
			return rArray;
		}
		//移除一个用指针指定的元素，该元素将立即被析构，并且其位置将由原列表中最后一个元素替代，该过程将保证只有一个线程操作
		void RemoveOneOf(T* t,int startIndex=0,int length=-1)
		{
			
			if(startIndex<0 || startIndex>pArray.Length || startIndex+length>pArray.Length){throw XException(E_INVALIDARG);}
			if(length<0)length = pArray.Length-startIndex;
			if(!length)return 
			T** p = pArray+startIndex;
			T** pEnd = pArray+startIndex+length-1;
			while(p<=pEnd){if(*p==t)break;++p;}
			if(p>pEnd)return //无操作
			int index = pEnd-p+startIndex+length-1;
			delete pArray[index];
			pArray[index] = *pEnd;
			pArray.Resize(pArray.Length-1);
			
		}
		//查找用指针指定的元素的位置
		int IndexOf(T* t ,int startIndex=0,int length=-1)
		{
			
			if(startIndex<0 || startIndex>pArray.Length || startIndex+length>pArray.Length){throw XException(E_INVALIDARG);}
			if(length<0)length = pArray.Length-startIndex;
			if(!length)return 
			T** pStart(pArray+startIndex);
			T** p(pStart);
			T** pEnd(pArray+startIndex+length-1);
			while(p<=pEnd)
			{
				if(*p==t)break;
				++p;
			}
			int index;
			if(p>pEnd)
				index = -1;
			else index = p-pStart;
			
			return index;
		}
		//设置最小重申空间变动值
		void SeMinDecrease(unsigned short m){pArray.MinDecrease = m;}
		//进入临界区
		void ThreadWait(){}
		//退出临界区
		void ThreadDone(){}
	};

	//无序容器的引用
	template<typename T>class XCollection:public XBase
	{
		PROPERTY_OFFSET(XCollection,Length);
	public:
		//兼容的长度属性
		CPROPERTY_GET(const int,XCollection,Length);
		//默认构造
		XCollection()
			:CPROPERTY_INIT(*this,XCollection<T>::GetLength,Length)
			XBase()
		{}
		//由数组构造
		XCollection(const VArray<T>& x)
			:CPROPERTY_INIT(*this,XCollection<T>::GetLength,Length)
			XBase(new VCollection<T>(x))
		{		}
		//由数组构造
		XCollection(const XArray<T> x)
			:CPROPERTY_INIT(*this,XCollection<T>::GetLength,Length)
			XBase(new VCollection<T>(x))
		{		}
		//析构函数
		~XCollection()
		{		}
		//复制构造函数
		XCollection(const XCollection& x)
			:XBase(x.pObject)
		{		}
		const int GetLength()const
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->Length;
		}
		//属性：元素数量
		PROPERTY_GET(const int,XCollection,GetLength,Length);
		//赋值
		XCollection& operator=(const XCollection x)
		{
			VCollection<T>* p(pObject);
			pObject = x.pObject;
			const_cast<VCollection<T>*&>(x.pObject) = p;
			return *this;
		}
		//提供使用下标进行的随机访问，这个过程将保证只有一个线程在操作
		T& operator[](int index)
		{
			XREFERENCE_CHECKPOINTER();
			return *reinterpret_cast<VCollection<T>*const&>(pObject)[index];
		}
		//迭代器
		XIterator<T> GetIterator()
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->GetIterator();
		}
		//放入一个元素，并返回列表中新增元素的引用，这个过程将保证只有一个线程在操作
		T& Add(const T& t)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->Add(t);
		}
		//取出并移除最后一个元素,如果集合为空则抛出错误
		T PickOut()
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->PickOut();
		}
		//取出并移除一个元素，如果集合为空或index超出集合范围，则抛出错误
		T PickOut(int index)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->PickOut(index);
		}
		//取一个元素，但不移除
		T Pick(int index =0)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->Pick(index);
		}
		//复制前count个元素到数组中，如果数组容量不够，则复制尽量多的内容
		XArray<T> CopyToArray(XArray<T> rArray)const
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->CopyToArray(rArray);
		}
		//复制前count个元素到数组中，如果数组容量不够，将抛出异常
		XArray<T> CopyToArray(XArray<T> rArray,int count)const
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->CopyToArray(rArray,count);
		}
		//复制所有内容到新数组中
		XArray<T> ToArray()const
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->ToArray();
		}
		//复制count个元素到新数组中
		XArray<T> ToArray(int count)const
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->ToArray(count);
		}
		//取所有元素到指定数组中，并移除，用数组末端的元素替代，如果数组容量不够，则移动尽量多的内容
		XArray<T> MoveToArray(XArray<T> rArray)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->MoveToArray(rArray);
		}
		//取前count个元素到数组中，并移除，用数组末端的元素替代，如果数组容量不够，则抛出异常
		XArray<T> MoveToArray(XArray<T> rArray,int count)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->MoveToArray(rArray,count);
		}
		//移除一个用指针指定的元素，该元素将立即被析构，并且其位置将由原列表中最后一个元素替代，该过程将保证只有一个线程操作
		void RemoveOne(T* t,int startIndex=0,int length=-1)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->RemoveOne(t,startIndex,length);
		}
		//查找用指针指定的元素的位置
		int IndexOf(T* t ,int startIndex=0,int length=-1)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->IndexOf(t,startIndex,length);
		}
		//设置最小重申空间变动值
		void SeMinDecrease(unsigned short m)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->SeMinDecrease(m);
		}
		//进入临界区
		void ThreadWait()
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->ThreadWait();
		}
		//退出临界区
		void ThreadDone()
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->ThreadDone();
		}
		//浅表副本
		XCollection MakeCopy()
		{
			XCollection tmp(*this);
			if(tmp.IsNull())return XCollection();
			return XCollection(reinterpret_cast<VCollection<T>*const&>(tmp.pObject)->pArray);
		}
	};

	//迭代器接口
	template<typename T>struct ICollectionIterator:public IIterator<T>
	{
		T** ppFirst;
		T** ppCurrent;
		T** ppEnd;
		ICollectionIterator(const VArray<T*>& pArray)
			:IIterator<T>(pArray.Length),ppCurrent(pArray),ppFirst(pArray),ppEnd(pArray+pArray.Length){}
		virtual void Next()
		{
			if(ppCurrent==ppEnd)return;
			++ppCurrent;
		}
		virtual void Fore()
		{
			if(ppCurrent==ppFirst)return;
			--ppCurrent;
		}
		virtual void NextN(int n)
		{
			if(ppCurrent+n>ppEnd || ppCurrent+n<ppFirst)throw XException(COR_E_INDEXOUTOFRANGE);
			ppCurrent+=n;
		}
		virtual void ForeN(int n)
		{
			if(ppCurrent-n>ppEnd || ppCurrent-n<ppFirst)throw XException(COR_E_INDEXOUTOFRANGE);
			ppCurrent-=n;
		}
		virtual bool ToLast()
		{
			if(ppFirst!=ppEnd)ppCurrent = ppEnd-1;
			return ppFirst!=ppEnd;
		}
		virtual bool ToEnd()
		{
			ppCurrent = ppEnd;
			return ppFirst!=ppEnd;
		}
		virtual void Reset()
		{
			ppCurrent = ppFirst;
		}
		virtual int Minus(IIterator<T>* p)
		{
			return ppCurrent - reinterpret_cast<ICollectionIterator*&>(p)->ppCurrent;
		}
		virtual IIterator<T>* MakeCopy(){return new ICollectionIterator(*this);}
		//获取当前的索引号
		virtual int GetCurrentIndex(){return ppCurrent-ppFirst;};
		//索引
		virtual T& Index(int index)
		{
			if(ppCurrent+index>=ppEnd || ppCurrent+index<ppFirst)throw XException(COR_E_INDEXOUTOFRANGE);
			return **(ppCurrent+index);
		}
		//获取当前指针
		virtual T*Current(){return ppCurrent==ppEnd?NULL:*ppCurrent;}
		//获取最后一个元素的指针
		virtual T*Last(){return *(ppEnd-1);}
		//获取第一个元素的指针
		virtual T*First(){return *ppFirst;}
		//获取终结元素的指针
		virtual T*End(){return NULL;}
		//迭代器比较
		virtual int CompareWith(IIterator<T>*p)
		{
			if(Length!=p->Length || ppFirst != reinterpret_cast<ICollectionIterator<T>*&>(p)->ppFirst)
				throw XException(L"比较的迭代器不对应",E_INVALIDARG);
			return ppCurrent-reinterpret_cast<ICollectionIterator<T>*&>(p)->ppCurrent;
		}
		virtual ~ICollectionIterator(){}
	};
}