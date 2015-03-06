#pragma once
namespace LJ
{
	//�������ӿڣ���װ��������
	template<typename T>struct IIterator
	{
		//����������
		int Length;
		//����ʱ���봫�볤��
		IIterator(int length):Length(length){}
		//������һ��Ԫ��
		virtual void Next()=0;
		//������һ��Ԫ��
		virtual void Fore()=0;
		//��Ծ��n��Ԫ��
		virtual void NextN(int n)=0;
		//��Ծ��n��Ԫ��
		virtual void ForeN(int n)=0;
		//���
		virtual int Minus(IIterator*p)=0;
		//��ת�����һ��
		virtual bool ToLast()=0;
		//��ת���ս�λ��
		virtual bool ToEnd()=0;
		//���õ���ͷ
		virtual void Reset()=0;
		//����һ������
		virtual IIterator* NewCopy()=0;
		//��ȡ��ǰ��������
		virtual int GetCurrentIndex()=0;
		//����
		virtual T& Index(int index)=0;
		//��ȡ��ǰָ��
		virtual T*Current()=0;
		//��ȡ���һ��Ԫ�ص�ָ��
		virtual T*Last()=0;
		//��ȡ��һ��Ԫ�ص�ָ��
		virtual T*First()=0;
		//��ȡ�ս�Ԫ�ص�ָ��
		virtual T*End()=0;
		//�������Ƚ�
		virtual int CompareWith(IIterator*)=0;
		//����
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
		//���캯��
		inline Iterator(IIterator<T>* pIterator):pIterator(pIterator){}
		//���ƹ��캯��
		inline Iterator(const Iterator& t):pIterator(t.pIterator->NewCopy()){}
		//���캯��
		inline Iterator(const Iterator<const T>& t)	:pIterator(t.pIterator->NewCopy()){}
		//���õ�ǰ�һ��Ĭ�ϳ�ʼΪ��һ�
		void SetCurrent(T t){*pIterator->Current() = t;}
		//��ȡ��ǰ�һ��Ĭ�ϳ�ʼΪ��һ�
		T GetCurrent()const{return *pIterator->Current();}
		//����++*this������pCurrent!=pEnd
		bool MoveNext(){++*this;return pIterator->Current()!=pIterator->End();}
		//ָ���ƶ������һ��
		bool MoveToLast(){return pIterator->ToLast();}
		//ָ���ƶ����ս���
		bool MoveToEnd(){return pIterator->ToEnd();}
		//����Ϊ��ʼ��
		Iterator& Reset(){pIterator->Reset();return *this;}
		int GetLength()const{return pIterator->Length;}
		union
		{
			//ͨ�õ�����
			IIterator<T>* pIterator;
			//���ԣ���ǰ��
			PROPERTY_GETSET(T,Iterator,GetCurrent,SetCurrent,Current);
			//���ԣ�����
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
		//���캯��
		Iterator(IIterator<T>* pIterator):pIterator(pIterator){}
		//���ƹ��캯��
		Iterator(const Iterator& t):pIterator(t.pIterator->NewCopy()){}
		explicit Iterator(const Iterator<T>& t):pIterator(t.pIterator->NewCopy()){}
		//��ȡ��ǰ�һ��Ĭ�ϳ�ʼΪ��һ�
		const T GetCurrent()const{return *pIterator->Current();}
		//��ȡԪ����
		int GetLength()const{return pIterator->Length;}
		//����++*this������pCurrent!=pEnd
		bool MoveNext(){++*this;return pIterator->Current()!=pIterator->End();}
		//ָ���ƶ������һ��
		bool MoveToLast(){return pIterator->ToLast();}
		//ָ���ƶ����ս���
		bool MoveToEnd(){return pIterator->ToEnd();}
		//����Ϊ��ʼ��
		Iterator& Reset(){pIterator->Reset();return *this;}
		union
		{
			//ͨ�õ�����
			IIterator<T>* pIterator;
			//���ԣ���ǰ��
			PROPERTY_GET(const T,Iterator,GetCurrent,Current);
			//���ԣ�����
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