#pragma once
namespace LJ
{
	template<typename T>struct ICollectionIterator;
	//��ʾһ����������������������������ƣ�֧�ִ����ֹ���ƹ��캯�����������VArray��Ȳ��ṩoperator T*
	template<class T>class VCollection:public XBase
	{
		friend XCollection<T>;
		//ָ������
		VArray<T*> pArray;
	public:
		//Ĭ�Ϲ���
		VCollection(){}
		//�����鹹��
		template<class AnyT>VCollection(const VArray<AnyT>& x)
		{
			pArray.Resize(x.Length);
			for(int i=0;i<pArray.Length;++i)pArray[i] = new T(x[i]);
		}
		//�����鹹��
		template<class AnyT>VCollection(const XArray<AnyT>& x)
		{
			pArray.Resize(x.Length);
			for(int i=0;i<pArray.Length;++i)pArray[i] = new T(x[i]);
		}
		//��������
		~VCollection()
		{
			for(int i=0;i<pArray.Length;++i)delete pArray[i];
		}
		//���ƹ��캯��
		template<class AnyT>VCollection(const VCollection<AnyT>& x)
		{
			pArray.Resize(x.pArray.Length);
			for(int i=0;i<pArray.Length;++i)pArray[i] = new T(*x.pArray[i]);
		}

		//�ṩʹ���±���е�������ʣ�������̽���ֻ֤��һ���߳��ڲ���
		T& operator[](int index)
		{
			if(index<0 || index>=pArray.Length){throw XException(E_INVALIDARG);}
			T& tmp(*pArray[index]);
			return tmp;
		}
		//������
		XIterator<T> First()
		{
			if(pArray.Length==0)return XIterator<T>(0,0,0);
			return XIterator<T>(new ICollectionIterator<T>(pArray[0],pArray[0],pArray[pArray.Length-1],NULL,pArray));
		}
		//����һ��Ԫ�أ��������б�������Ԫ�ص����ã�������̽���ֻ֤��һ���߳��ڲ���
		template<class AnyT> T& Append(const AnyT& t)
		{
			pArray.Resize(pArray.Length+1);
			T* p = new T(t);
			pArray.LastElement() = p;
			return *p;
		}

		//����ǰcount��Ԫ�ص������У���������������������ƾ����������
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
		//����ǰcount��Ԫ�ص������У���������������������׳��쳣
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
		//�����������ݵ���������
		XArray<T> ToArray()const
		{
			
			XArray<T> rArray(pArray.Length);
			T* p = rArray;
			T* pEnd = p+pArray.Length;
			T*const* pp =pArray;
			while(p<pEnd){*p++=**pp++;}
			
			return rArray;
		}
		//����count��Ԫ�ص���������
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
		//ȡ����Ԫ�ص�ָ�������У����Ƴ���������ĩ�˵�Ԫ���������������������������ƶ������������
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
		//ȡǰcount��Ԫ�ص������У����Ƴ���������ĩ�˵�Ԫ���������������������������׳��쳣
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
		//�Ƴ�һ����ָ��ָ����Ԫ�أ���Ԫ�ؽ�������������������λ�ý���ԭ�б������һ��Ԫ��������ù��̽���ֻ֤��һ���̲߳���
		void RemoveOneOf(T* t,int startIndex=0,int length=-1)
		{
			
			if(startIndex<0 || startIndex>pArray.Length || startIndex+length>pArray.Length){throw XException(E_INVALIDARG);}
			if(length<0)length = pArray.Length-startIndex;
			if(!length)return 
			T** p = pArray+startIndex;
			T** pEnd = pArray+startIndex+length-1;
			while(p<=pEnd){if(*p==t)break;++p;}
			if(p>pEnd)return //�޲���
			int index = pEnd-p+startIndex+length-1;
			delete pArray[index];
			pArray[index] = *pEnd;
			pArray.Resize(pArray.Length-1);
			
		}
		//������ָ��ָ����Ԫ�ص�λ��
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
		//������С����ռ�䶯ֵ
		void SeMinDecrease(unsigned short m){pArray.MinDecrease = m;}
		//�����ٽ���
		void ThreadWait(){}
		//�˳��ٽ���
		void ThreadDone(){}
	};

	//��������������
	template<typename T>class XCollection:public XBase
	{
		PROPERTY_OFFSET(XCollection,Length);
	public:
		//���ݵĳ�������
		CPROPERTY_GET(const int,XCollection,Length);
		//Ĭ�Ϲ���
		XCollection()
			:CPROPERTY_INIT(*this,XCollection<T>::GetLength,Length)
			XBase()
		{}
		//�����鹹��
		XCollection(const VArray<T>& x)
			:CPROPERTY_INIT(*this,XCollection<T>::GetLength,Length)
			XBase(new VCollection<T>(x))
		{		}
		//�����鹹��
		XCollection(const XArray<T> x)
			:CPROPERTY_INIT(*this,XCollection<T>::GetLength,Length)
			XBase(new VCollection<T>(x))
		{		}
		//��������
		~XCollection()
		{		}
		//���ƹ��캯��
		XCollection(const XCollection& x)
			:XBase(x.pObject)
		{		}
		const int GetLength()const
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->Length;
		}
		//���ԣ�Ԫ������
		PROPERTY_GET(const int,XCollection,GetLength,Length);
		//��ֵ
		XCollection& operator=(const XCollection x)
		{
			VCollection<T>* p(pObject);
			pObject = x.pObject;
			const_cast<VCollection<T>*&>(x.pObject) = p;
			return *this;
		}
		//�ṩʹ���±���е�������ʣ�������̽���ֻ֤��һ���߳��ڲ���
		T& operator[](int index)
		{
			XREFERENCE_CHECKPOINTER();
			return *reinterpret_cast<VCollection<T>*const&>(pObject)[index];
		}
		//������
		XIterator<T> GetIterator()
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->GetIterator();
		}
		//����һ��Ԫ�أ��������б�������Ԫ�ص����ã�������̽���ֻ֤��һ���߳��ڲ���
		T& Add(const T& t)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->Add(t);
		}
		//ȡ�����Ƴ����һ��Ԫ��,�������Ϊ�����׳�����
		T PickOut()
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->PickOut();
		}
		//ȡ�����Ƴ�һ��Ԫ�أ��������Ϊ�ջ�index�������Ϸ�Χ�����׳�����
		T PickOut(int index)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->PickOut(index);
		}
		//ȡһ��Ԫ�أ������Ƴ�
		T Pick(int index =0)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->Pick(index);
		}
		//����ǰcount��Ԫ�ص������У���������������������ƾ����������
		XArray<T> CopyToArray(XArray<T> rArray)const
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->CopyToArray(rArray);
		}
		//����ǰcount��Ԫ�ص������У���������������������׳��쳣
		XArray<T> CopyToArray(XArray<T> rArray,int count)const
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->CopyToArray(rArray,count);
		}
		//�����������ݵ���������
		XArray<T> ToArray()const
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->ToArray();
		}
		//����count��Ԫ�ص���������
		XArray<T> ToArray(int count)const
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->ToArray(count);
		}
		//ȡ����Ԫ�ص�ָ�������У����Ƴ���������ĩ�˵�Ԫ���������������������������ƶ������������
		XArray<T> MoveToArray(XArray<T> rArray)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->MoveToArray(rArray);
		}
		//ȡǰcount��Ԫ�ص������У����Ƴ���������ĩ�˵�Ԫ���������������������������׳��쳣
		XArray<T> MoveToArray(XArray<T> rArray,int count)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->MoveToArray(rArray,count);
		}
		//�Ƴ�һ����ָ��ָ����Ԫ�أ���Ԫ�ؽ�������������������λ�ý���ԭ�б������һ��Ԫ��������ù��̽���ֻ֤��һ���̲߳���
		void RemoveOne(T* t,int startIndex=0,int length=-1)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->RemoveOne(t,startIndex,length);
		}
		//������ָ��ָ����Ԫ�ص�λ��
		int IndexOf(T* t ,int startIndex=0,int length=-1)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->IndexOf(t,startIndex,length);
		}
		//������С����ռ�䶯ֵ
		void SeMinDecrease(unsigned short m)
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->SeMinDecrease(m);
		}
		//�����ٽ���
		void ThreadWait()
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->ThreadWait();
		}
		//�˳��ٽ���
		void ThreadDone()
		{
			XREFERENCE_CHECKPOINTER();
			return reinterpret_cast<VCollection<T>*const&>(pObject)->ThreadDone();
		}
		//ǳ����
		XCollection MakeCopy()
		{
			XCollection tmp(*this);
			if(tmp.IsNull())return XCollection();
			return XCollection(reinterpret_cast<VCollection<T>*const&>(tmp.pObject)->pArray);
		}
	};

	//�������ӿ�
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
		//��ȡ��ǰ��������
		virtual int GetCurrentIndex(){return ppCurrent-ppFirst;};
		//����
		virtual T& Index(int index)
		{
			if(ppCurrent+index>=ppEnd || ppCurrent+index<ppFirst)throw XException(COR_E_INDEXOUTOFRANGE);
			return **(ppCurrent+index);
		}
		//��ȡ��ǰָ��
		virtual T*Current(){return ppCurrent==ppEnd?NULL:*ppCurrent;}
		//��ȡ���һ��Ԫ�ص�ָ��
		virtual T*Last(){return *(ppEnd-1);}
		//��ȡ��һ��Ԫ�ص�ָ��
		virtual T*First(){return *ppFirst;}
		//��ȡ�ս�Ԫ�ص�ָ��
		virtual T*End(){return NULL;}
		//�������Ƚ�
		virtual int CompareWith(IIterator<T>*p)
		{
			if(Length!=p->Length || ppFirst != reinterpret_cast<ICollectionIterator<T>*&>(p)->ppFirst)
				throw XException(L"�Ƚϵĵ���������Ӧ",E_INVALIDARG);
			return ppCurrent-reinterpret_cast<ICollectionIterator<T>*&>(p)->ppCurrent;
		}
		virtual ~ICollectionIterator(){}
	};
}