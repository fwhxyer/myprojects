#ifndef XARRAY_
#define XARRAY_
namespace LJ
{
	template<typename T,typename AnyT>void VArrayCopyConstructMethod(AnyT*source,T* pDestination,unsigned long size)
	{
		T* pEnd = pDestination+size;
		while(pDestination!=pEnd){placementnew(pDestination++,*source++);}//����
	}
	//Ĭ�Ϲ��췽��
	template<typename T>void VArrayDefaultConstructMethod(T* pDestination,unsigned long size)
	{
		T* pEnd = pDestination+size;
		while(pDestination!=pEnd)placementnew(pDestination++);//Ĭ�Ϲ���
	}
	template<typename T>void VArrayDefaultConstructMethod(T**,unsigned long){}
	void VArrayDefaultConstructMethod(char*,unsigned long);
	void VArrayDefaultConstructMethod(signed char*,unsigned long);
	void VArrayDefaultConstructMethod(unsigned char*,unsigned long);
	void VArrayDefaultConstructMethod(short*,unsigned long);
	void VArrayDefaultConstructMethod(unsigned short*,unsigned long);
	void VArrayDefaultConstructMethod(long*,unsigned long);
	void VArrayDefaultConstructMethod(unsigned int*,unsigned long);
	void VArrayDefaultConstructMethod(int*,unsigned long);
	void VArrayDefaultConstructMethod(unsigned long*,unsigned long);
	void VArrayDefaultConstructMethod(long long*,unsigned long);
	void VArrayDefaultConstructMethod(unsigned long long*,unsigned long);
	//��������
	template<typename T>void VArrayDeconstructMethod(T* pDestination,unsigned long size)
	{
		T* pEnd = pDestination+size;
		while(pDestination!=pEnd)(pDestination++)->T::~T();//����
	}
	template<typename T>void VArrayDeconstructMethod(T**,unsigned long){}
	void VArrayDeconstructMethod(char*,unsigned long);
	void VArrayDeconstructMethod(signed char*,unsigned long);
	void VArrayDeconstructMethod(unsigned char*,unsigned long);
	void VArrayDeconstructMethod(short*,unsigned long);
	void VArrayDeconstructMethod(unsigned short*,unsigned long);
	void VArrayDeconstructMethod(long*,unsigned long);
	void VArrayDeconstructMethod(unsigned long*,unsigned long);
	void VArrayDeconstructMethod(int*,unsigned long);
	void VArrayDeconstructMethod(unsigned int*,unsigned long);
	void VArrayDeconstructMethod(long long*,unsigned long);
	void VArrayDeconstructMethod(unsigned long long*,unsigned long);
	//��ֵ���췽��
	template<typename T>void VArrayConstructMethod(const T& source,T* pDestination,unsigned long size)
	{
		T* pEnd = pDestination+size;
		while(pDestination!=pEnd)placementnew(pDestination++,source);//���ƹ���
	}
	//���Ʒ���
	template<typename T>void VArrayCopyMethod(const T* pSource, T* pDestination, unsigned long size)
	{
		T* pEnd = pDestination+size;
		while(pDestination!=pEnd)*pDestination++=*pSource++;
	}
	template<typename T>void VArrayCopyMethod(T*const * pSource,T** pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,sizeof(T*)*size);
	}

	void VArrayCopyMethod(const char*, char*, unsigned long );//���⻯
	void VArrayCopyMethod(const short*, short*, unsigned long );//���⻯
	void VArrayCopyMethod(const long*, long*, unsigned long );//���⻯
	void VArrayCopyMethod(const int*, int*, unsigned long );//���⻯
	void VArrayCopyMethod(const long long*, long long*, unsigned long );//���⻯
	void VArrayCopyMethod(const unsigned char*, unsigned char*, unsigned long );//���⻯
	void VArrayCopyMethod(const unsigned short*, unsigned short*, unsigned long );//���⻯
	void VArrayCopyMethod(const unsigned long*, unsigned long*, unsigned long );//���⻯
	void VArrayCopyMethod(const unsigned int*, unsigned int*, unsigned long );//���⻯
	void VArrayCopyMethod(const unsigned long long*, unsigned long long*, unsigned long );//���⻯
	void VArrayCopyMethod(const WCHAR*, WCHAR*, unsigned long );//���⻯
	enum XArrayType:signed char
	{
		Normal = 0,//�������ͣ�ͨ��deleteɾ��
		Reference = 1,//�������ͣ�����Ҫ����ɾ��
		SelfConstruct =2//�Թ������ͣ��ڲ�������������
	};
	template<typename T>struct IArrayIterator;
	template<typename T>class VArray:public XBase//��1ά����
	{
	protected:
		//��������
		T *pData;
		//��ǰ���Ԫ����
		int maxSize;
		//��������(�����ڴ����ʽ)
		XArrayType type;
	public:
		PROPERTY_OFFSET(VArray,Length);
		XBaseVTypeMethods_H(VArray);
		//����
		virtual void SwapWith(XBase& x)
		{
			VArray* p=dynamic_cast<VArray*>(&x);
			if(p==NULL)throw XException(L"����Ϊ�ջ�Ƿ�",E_POINTER);
			SwapWith(*p);
		}
		//����һ��ʵ�����齻��
		void  SwapWith(VArray& v)
		{
			T*p = pData;pData = v.pData;v.pData=p;
			int len = Length;const_cast<int&>(Length) = v.Length;const_cast<int&>(v.Length)=len;
			len = MinDecrease;MinDecrease = v.MinDecrease;v.MinDecrease=len;
		}
		//�ڴ����
		static T* Malloc(int count);
		//Ԫ������Сʱ��Ԫ�����仯������ֵ����������ռ�
		int MinDecrease;
		//Ĭ�ϵ���С��С�仯ֵ
		static int MinDecreaseDefault;
		//��ȡ���鰴�ֽڼ���ĳ���
		int GetLengthOfBytes()const;
		union
		{
			//��ǰԪ����
			const int Length;
			//ֻ���ֽڳ�������
			PROPERTY_GET(int,VArray,GetLengthOfBytes,LengthOfBytes);
		};
		//�������������ͷ�����
		virtual ~VArray();
		//Ĭ�Ϲ��캯��������һ��������
		VArray();
		//�������鳤�ȣ�����һ��δ��ʼ�������飬�õ���
		VArray(int);
		//���ƹ��캯�������Ƴ���type֮�������
		VArray(const VArray&);
		//�������������鹹�죬���Ƴ���type֮�������
		VArray(const XArray<T>&);
		//�������鳤�ȣ���ʹ��һ���ο�Ԫ������ʼ������Ԫ��
		VArray(int,const T&);
		//ʹ�õ���������
		template<class AnyT>VArray(const Iterator<AnyT>&first,const Iterator<AnyT>&end);
		//ֱ�Ӵ���ָ���Ԫ����,���type����ΪNormal����p����ָ����new����Ŀռ�,�����ɸö���ִ��delete, ���pΪNULL���򲻽��г�ʼ��,���type����ΪReference��ö��󽫲�ִ��ɾ��
		explicit VArray(int,typename Types<T>::Normal*,XArrayType type=Normal);
		//ֱ�Ӵ���ָ���Ԫ����,���type����ΪNormal����p����ָ����new����Ŀռ�,�����ɸö���ִ��delete, ���pΪNULL���򲻽��г�ʼ��,���type����ΪReference��ö��󽫲�ִ��ɾ��
		explicit VArray(int,typename Types<T>::Normal const*,XArrayType type=Reference);
		//ֱ��ת����ָ����ʽ
		operator const T*const& ()const;
		//ת����ָ����ʽ
		operator T*const &();
		//��������λ�ö�λ����һ��Ԫ��
		Iterator<T> First();
		//��������λ�ö�λ����һ��Ԫ��
		Iterator<const T> First()const;
		//��������λ�ö�λ����һ��Ԫ��,ͬFirst()
		Iterator<T> begin(){return First();}
		//��������λ�ö�λ����һ��Ԫ��,ͬFirst()
		Iterator<const T> begin()const{return First();}
		//��������λ�ö�λ�����һ��Ԫ��
		Iterator<T> Last();
		//��������λ�ö�λ�����һ��Ԫ��
		Iterator<const T> Last()const;
		//��������λ�ö�λ��ĩβ
		Iterator<T> End();
		//��������λ�ö�λ��ĩβ
		Iterator<const T> End()const;
		//��������λ�ö�λ��ĩβ,ͬEnd();
		Iterator<T> end(){return End();}
		//��������λ�ö�λ��ĩβ,ͬEnd();
		Iterator<const T> end()const{return End();}
		//����һ����������ݣ�������ԭ�����ݵĽ�������
		VArray& operator=(const VArray&);
		//��ȡ�������һ���֣������飩
		VArray SubArray(int,int,XArrayType type=SelfConstruct)const;
		//��������������pdata��������Ԫ���γ�T��ΪԪ�ص�����
		template<typename AnyT>static VArray<T> CopyFrom(const VArray<AnyT>&);
		//��������������pdata��startIndex������Ӧ��Ԫ�����Ƶ������β���γ�T��ΪԪ�ص�����
		template<typename AnyT>static VArray<T> CopyFrom(const VArray<AnyT>&,int startIndex);
		//������pdata��startIndexԪ������length��Ԫ���γ�T��ΪԪ�ص�����
		template<typename AnyT>static VArray<T> CopyFrom(const VArray<AnyT>&,int startIndex, int length);
		//���������͵������γ�T����Ԫ�ص�����
		template<typename AnyT>static VArray<T> CopyFrom(const Iterator<const T>&first,const Iterator<const T>&end);
		//������pdata���ֽڸ������������γ����飬������ݷ��������ɵ�������ܻ��в�������δ��ʼ��
		template<typename AnyT>static VArray<T> CopyFromByBytes(const VArray<AnyT>&pdata);
		//������pdata��startByte�ֽڴ����ֽڸ��Ƶ���β�γ������飬������ݷ��������ɵ�������ܻ��в�������δ��ʼ��
		template<typename AnyT>static VArray<T> CopyFromByBytes(const VArray<AnyT>&pdata,int startByte);
		//������pdata��startByte�ֽڴ�����length���ֽ��γ����飬������ݷ��������ɵ�������ܻ��в�������δ��ʼ��
		template<typename AnyT>static VArray<T> CopyFromByBytes(const VArray<AnyT>&pdata,int startByte,int length);
		//������������ݸ���һ���ֵ���һ�����飬����ʵ�ʸ��Ƶ�Ԫ����
		template<typename AnyT>int CopyTo(VArray<AnyT>& pdata,int startIndex=0,int destinationStartIndex=0)const;
		//������������ݸ���һ���ֵ���һ�����飬����ʵ�ʸ��Ƶ�Ԫ����
		template<typename AnyT>int CopyTo(VArray<AnyT>& pdata,int startIndex,int destinationStartIndex,int length)const;
		//������һ�����͵����鸴��һ�����ֽ���
		template<typename AnyT>int CopyToByBytes(VArray<AnyT>& pdata,int startByte=0,int destinationStartByte=0)const;
		//������һ�����͵����鸴��һ�����ֽ���
		template<typename AnyT>int CopyToByBytes(VArray<AnyT>& pdata,int startByte,int destinationStartByte,int lengthOfBytes)const;
		//��������һϵ��Ԫ�ص�ֵ����Ϊt
		template<typename AnyT>void ResetTo(const AnyT& t);
		//��������һϵ��Ԫ�ص�ֵ����Ϊt
		template<typename AnyT>void ResetTo(const AnyT& t, int index, int length);
		//�������ĳ��������ָ����λ�ò���Ԫ��
		template<typename AnyT>Iterator<T> Insert(int index,const AnyT&t);
		//�������ĳ���õ�����ָ����λ�ò���Ԫ��
		template<typename AnyT>Iterator<T> Insert(const Iterator<T>& it,const AnyT&t);
		//�������ĳ��������ָ����λ�ò�������
		template<typename AnyT>Iterator<T> InsertArray(int index,const VArray<AnyT>&xArray);
		//�������ĳ���õ�����ָ����λ�ò�������
		template<typename AnyT>Iterator<T> InsertArray(const Iterator<T>& it,const VArray<AnyT>&xArray);
		//�������β���Ԫ��
		template<typename AnyT>Iterator<T> Append(const AnyT&t);
		//�������β�������
		template<typename AnyT>Iterator<T> AppendArray(const VArray<AnyT>&xArray);
		//��������ɾ��ָ�������Ԫ�أ�startIndexΪ��ʼ�Ƴ�����λ�ã���startIndex��ĩβ�����ݶ����Ƴ�
		Iterator<T> Remove(int startIndex);
		//��������ɾ��ָ��λ�õ�Ԫ�أ�indexΪ�Ƴ�����λ��
		Iterator<T> RemoveAt(int index);
		//��������ɾ��ָ�������Ԫ�أ�startIndexΪ��ʼ�Ƴ�����λ�ã�lengthΪҪ�Ƴ���Ԫ����
		Iterator<T> Remove(int startIndex,int length);
		//��������ɾ��ָ�������Ԫ�أ�startIndexΪ��ʼ�Ƴ�����λ�ã�lengthΪҪ�Ƴ���Ԫ����
		Iterator<T> Remove(const Iterator<T>& firstIterator,const Iterator<T>& endIterator);
		//�Ƴ�����ָ�������е�һ����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ�Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveOneOf(const AnyT&,int startIndex=0);
		//�Ƴ�����ָ�������е�һ����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ���lengthΪԪ���������صĵ�����Ϊ�Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveOneOf(const AnyT&,int startIndex,int length);
		//�Ƴ�����ָ�������е�һ����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ�Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveOneOf(const AnyT&,const Iterator<T>&start ,const Iterator<T>&end);
		//�Ƴ�����ָ�������г��ֵ�������ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveAllOf(const AnyT&,int startIndex=0);
		//�Ƴ�����ָ�������г��ֵ�������ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveAllOf(const AnyT&,int startIndex,int length);
		//�Ƴ�����ָ�������г��ֵ�������ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveAllOf(const AnyT&,const Iterator<T>&start ,const Iterator<T>&end);
		//�Ƴ�����ָ�������г��ֵ����count����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveSomeOf(const AnyT&,int startIndex,int length,int count);
		//�Ƴ�����ָ�������г��ֵ����count����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveSomeOf(const AnyT&,const Iterator<T>&first ,const Iterator<T>&end,int count);
		//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex=0);
		//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex,int length);
		//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ�أ����صĵ�����Ϊ���һ���滻λ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceOneOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end);
		//�滻������������t��ȵ�Ԫ��Ϊ��һ��Ԫ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex=0);
		//�滻������������t��ȵ�Ԫ��Ϊ��һ��Ԫ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex,int length);
		//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ�أ����صĵ�����Ϊ���һ���滻λ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceAllOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end);
		//�滻������ĳЩԪ��Ϊ��һ��Ԫ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceSomeOf(const AnyT1& t, const AnyT2& to,int startIndex,int length,int count);
		//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ�أ����صĵ�����Ϊ���һ���滻λ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceSomeOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end,int count);
		//�����������,startIndex��length�ֱ��ʾ��ʼ�±�ʹ������ݳ���
		void SortRandom(int startIndex,int length);
		//�����������
		void SortRandom(int startIndex=0);
		//������С��������������,����ʵ��ռ�õ����ռ�
		int Resize( int);
		//������С����һ���������ݣ���Resize�������һ�����ƵĹ���
		int ResizeAndDestroy( int);
		//������ָ��ֵ��ȵĵ�һ��Ԫ�أ��Ҳ����򷵻�-1
		template<typename AnyT>int IndexOf(const AnyT&t, int startIndex=0)const;
		//��ָ�����������ָ��ֵ��ȵĵ�һ��Ԫ�أ��Ҳ����򷵻�-1
		template<typename AnyT>int IndexOf(const AnyT&t, int startIndex,int length)const;
		//���õ�����ָ�������������ָ��ֵ��ȵĵ�һ��Ԫ�أ��Ҳ����򷵻�-1
		template<typename AnyT>int IndexOf(const AnyT&t, const Iterator<const T>& start,const Iterator<const T>& end)const;
		//������ָ��ֵ��ȵ����һ��Ԫ�أ��Ҳ����򷵻�-1
		template<typename AnyT>int LastIndexOf(const AnyT&t,int startIndex=0)const;
		//��ָ�����������ָ��ֵ��ȵ����һ��Ԫ�أ��Ҳ����򷵻�-1
		template<typename AnyT>int LastIndexOf(const AnyT&t,int startIndex,int length)const;
		//���õ�����ָ�������������ָ��ֵ��ȵ����һ��Ԫ�أ��Ҳ����򷵻�-1
		template<typename AnyT>int LastIndexOf(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const;
		//����ָ��Ԫ�ص�λ�ã��Ҳ�������end
		template<typename AnyT>Iterator<T> Find(const AnyT&t,int startIndex=0)const;
		//��ָ���������ָ��Ԫ�ص�λ�ã��Ҳ�������end
		template<typename AnyT>Iterator<T> Find(const AnyT&t,int startIndex,int length)const;
		//���õ�����ָ�����������ָ��Ԫ�ص�λ�ã��Ҳ�������end
		template<typename AnyT>Iterator<T> Find(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const;
		//������ָ��������ȵ�Ԫ����
		template<class AnyT>int CountOf(const AnyT&t,int startIndex=0)const;
		//��ָ�����������ָ��������ȵ�Ԫ����
		template<class AnyT>int CountOf(const AnyT&t,int startIndex,int length)const;
		//���õ�����ָ�������������ָ��������ȵ�Ԫ����
		template<class AnyT>int CountOf(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const;
		//��ȡ���һ��Ԫ�ص�����
		T& LastElement();
		//��ȡ���һ��Ԫ�ص�����
		const T& LastElement()const;
		//��ȡ��һ��Ԫ�ص�����
		T& FirstElement();
		//��ȡ��һ��Ԫ�ص�����
		const T& FirstElement()const;
		//��ȡ�������ݱ��淽ʽ������ͨ�����á��Թ���
		XArrayType GetArrayType()const {return type;}
	};

	template<typename T>class XArray:public XBase
	{
	public:
		PROPERTY_OFFSET(XArray,Length);
		//ͨ�û��෽��
		XBaseRTypeMethods_H(XArray,VArray<T>);
		static inline int GetMinDecreaseDefault(){return VArray<T>::MinDecreaseDefault;}
		static inline void SetMinDecreaseDefault(int v){VArray<T>::MinDecreaseDefault = v;}
		//��д����Ĭ�ϵ���С��С�仯ֵ������޸�VArray::MinDecreaseDefault��
		static StaticProperty<int> MinDecreaseDefault;
		//��ʵ�����鹹��
		XArray(const VArray<T>& v)
			:XBase(new VArray<T>(v)){}
		//�������鳤�ȣ�����һ��δ��ʼ��������
		XArray(int length):XBase(new VArray<T>(length)){		}
		//�������鳤�ȣ���ʹ��һ���ο�Ԫ������ʼ������Ԫ��
		XArray(int length,const T& t):XBase(new VArray<T>(length,t)){		}
		//ʹ�õ���������
		template<class AnyT>XArray(const Iterator<AnyT>&first,const Iterator<AnyT>&end):XBase(new VArray<T>(first,end)){	}
		//ֱ�Ӵ���ָ���Ԫ����,����type=Normal��p������ʹ��new����Ŀռ�,�����ɸö���ִ��delete, ���pΪNULL���򲻽��г�ʼ��,����type=Reference��ö��󽫲�ִ��ɾ��
		explicit XArray(int length,typename Types<T>::Normal* p,XArrayType type=Normal):XBase(new VArray<T>(length,p,type)){		}
		//ֱ�Ӵ���ָ���Ԫ����,����type=Normal��p������ʹ��new����Ŀռ�,�����ɸö���ִ��delete, ���pΪNULL���򲻽��г�ʼ��,����type=Reference��ö��󽫲�ִ��ɾ��
		explicit XArray(int length,typename Types<T>::Normal const* p,XArrayType type=Reference):XBase(new VArray<T>(length,p,type)){}
		//��ȡ�����Ԫ����
		int GetLength()const;
		//��ȡ���鰴�ֽڼ���ĳ���
		int GetLengthOfBytes()const;
		//��ȡ��С����ռ�仯ֵ
		int GetMinDecrease()const;
		//������С����ռ�仯ֵ
		void SetMinDecrease(int);
		union
		{
			//ֻ���������ԣ������Ԫ����
			PROPERTY_GET(int,XArray,GetLength,Length);
			//ֻ�����ԣ�������ֽڳ���
			PROPERTY_GET(int,XArray,GetLengthOfBytes,LengthOfBytes);
			//��д���ԣ���С����ռ�仯ֵ
			PROPERTY_GETSET(int,XArray,GetMinDecrease,SetMinDecrease,MinDecrease);
		};
		//ֱ��ת����ָ����ʽ
		operator const T*const&()const;
		operator T*const &();
		T&operator[](int index){if(IsNull())throw XException(E_POINTER);return ((T*const &)*this)[index];}
		const T&operator[](int index)const{if(IsNull())throw XException(E_POINTER);return ((const T*const &)*this)[index];}
		//��������λ�ö�λ����һ��Ԫ��
		Iterator<T> First();
		//��������λ�ö�λ����һ��Ԫ��
		Iterator<const T> First()const;
		//��������λ�ö�λ����һ��Ԫ��,ͬFirst();
		Iterator<T> begin(){return First();}
		//��������λ�ö�λ����һ��Ԫ��,ͬFirst();
		Iterator<const T> begin()const{return First();}
		//��������λ�ö�λ�����һ��Ԫ��
		Iterator<T> Last();
		//��������λ�ö�λ�����һ��Ԫ��
		Iterator<const T> Last()const;
		//��������λ�ö�λ��ĩβ
		Iterator<T> End();
		//��������λ�ö�λ��ĩβ
		Iterator<const T> End()const;
		//��������λ�ö�λ��ĩβ,ͬEnd();
		Iterator<T> end(){return End();}
		//��������λ�ö�λ��ĩβ,ͬEnd();
		Iterator<const T> end()const{return End();}
		//��ȡ�������һ���֣������飩
		XArray SubArray(int startIndex,int length,XArrayType type=SelfConstruct)const;
		//������pdata��������Ԫ���γ�T��ΪԪ�ص�����
		template<typename AnyT>static XArray<T> CopyFrom(const XArray<AnyT>&);
		//������pdata��startIndex������Ӧ��Ԫ�����Ƶ������β���γ�T��ΪԪ�ص�����
		template<typename AnyT>static XArray<T> CopyFrom(const XArray<AnyT>&,int startIndex);
		//������pdata��startIndexԪ������length��Ԫ���γ�T��ΪԪ�ص�����
		template<typename AnyT>static XArray<T> CopyFrom(const XArray<AnyT>&,int startIndex, int length);
		//�ӵ�����ָ����������length��Ԫ���γ�T��ΪԪ�ص�����
		template<typename AnyT>static XArray<T> CopyFrom(const Iterator<const T>&first,const Iterator<const T>&end);
		//������pdata���ֽڸ������������γ����飬������ݷ��������ɵ�������ܻ��в���������0���
		template<typename AnyT>static XArray<T> CopyFromByBytes(const XArray<AnyT>&pdata);
		//������pdata��startByte�ֽڴ����ֽڸ��Ƶ���β�γ������飬������ݷ��������ɵ�������ܻ��в���������0���
		template<typename AnyT>static XArray<T> CopyFromByBytes(const XArray<AnyT>&pdata,int startByte);
		//������pdata��startByte�ֽڴ�����length���ֽ��γ����飬������ݷ��������ɵ�������ܻ��в���������0���
		template<typename AnyT>static XArray<T> CopyFromByBytes(const XArray<AnyT>&pdata,int startByte,int length);
		//������������ݸ���һ���ֵ���һ�����飬����ʵ�ʸ��Ƶ�Ԫ����
		template<typename AnyT>int CopyTo(XArray<AnyT>& pdata,int startIndex=0,int destinationStartIndex=0)const;
		//������������ݸ���һ���ֵ���һ�����飬����ʵ�ʸ��Ƶ�Ԫ����
		template<typename AnyT>int CopyTo(XArray<AnyT>& pdata,int startIndex,int destinationStartIndex,int length)const;
		//������һ�����͵����鸴��һ�����ֽ���
		template<typename AnyT>int CopyToByBytes(XArray<AnyT>& pdata,int startByte=0,int destinationStartByte=0)const;
		//������һ�����͵����鸴��һ�����ֽ���
		template<typename AnyT>int CopyToByBytes(XArray<AnyT>& pdata,int startByte,int destinationStartByte,int lengthOfBytes)const;
		//��������һϵ��Ԫ�ص�ֵ����Ϊt
		template<typename AnyT>void ResetTo(const AnyT& t);
		//��������һϵ��Ԫ�ص�ֵ����Ϊt
		template<typename AnyT>void ResetTo(const AnyT& t, int index, int length);
		//�������ĳ��������ָ����λ�ò���Ԫ��
		template<typename AnyT>Iterator<T> Insert(int index,const AnyT&t);
		//�������ĳ���õ�����ָ����λ�ò���Ԫ��
		template<typename AnyT>Iterator<T> Insert(const Iterator<T>& it,const AnyT&t);
		//�������ĳ��������ָ����λ�ò�������
		template<typename AnyT>Iterator<T> InsertArray(int index,const XArray<AnyT>&xArray);
		//�������ĳ���õ�����ָ����λ�ò�������
		template<typename AnyT>Iterator<T> InsertArray(const Iterator<T>& it,const XArray<AnyT>&xArray);
		//�������β���Ԫ��
		template<typename AnyT>Iterator<T> Append(const AnyT&t);
		//�������β�������
		template<typename AnyT>Iterator<T> AppendArray(const XArray<AnyT>&xArray);
		//��������ɾ��ָ�������Ԫ�أ�startIndexΪ��ʼ�Ƴ�λ����������startIndex��ĩβ�����ݶ������Ƴ�
		Iterator<T> Remove(int startIndex);
		//��������ɾ��ָ�������Ԫ�أ�startIndexΪ��ʼ�Ƴ�����λ�ã�lengthΪҪ�Ƴ���Ԫ����
		Iterator<T> Remove(int startIndex,int length);
		//��������ɾ��ָ�������Ԫ�أ�startIndexΪ��ʼ�Ƴ�����λ�ã�lengthΪҪ�Ƴ���Ԫ����
		Iterator<T> Remove(const Iterator<T>& firstIterator,const Iterator<T>& endIterator);
		//��������ɾ��ָ��λ�õ�Ԫ�أ�indexΪ�Ƴ�λ�õ�������ֱ��ĩβ
		Iterator<T> RemoveAt(int index);
		//�Ƴ�����ָ�������е�һ����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ�Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveOneOf(const AnyT&,int startIndex=0);
		//�Ƴ�����ָ�������е�һ����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ���lengthΪԪ���������صĵ�����Ϊ�Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveOneOf(const AnyT&,int startIndex,int length);
		//�Ƴ�����ָ�������е�һ����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ�Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveOneOf(const AnyT&,const Iterator<T>&start ,const Iterator<T>&end);
		//�Ƴ�����ָ�������г��ֵ�������ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveAllOf(const AnyT&,int startIndex=0);
		//�Ƴ�����ָ�������г��ֵ�������ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveAllOf(const AnyT&,int startIndex,int length);
		//�Ƴ�����ָ�������г��ֵ�������ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveAllOf(const AnyT&,const Iterator<T>&start ,const Iterator<T>&end);
		//�Ƴ�����ָ�������г��ֵ����count����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveSomeOf(const AnyT&,int startIndex,int length,int count);
		//�Ƴ�����ָ�������г��ֵ����count����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
		template<typename AnyT>Iterator<T> RemoveSomeOf(const AnyT&,const Iterator<T>&first ,const Iterator<T>&end,int count);
		//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex=0);
		//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex,int length);
		//�滻������������ָ��Ԫ����ȵ�Ԫ��Ϊ��һ��Ԫ�أ����صĵ�����Ϊ���һ���滻λ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceOneOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end);
		//�滻������������t��ȵ�Ԫ��Ϊ��һ��Ԫ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex=0);
		//�滻������������t��ȵ�Ԫ��Ϊ��һ��Ԫ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex,int length);
		//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ�أ����صĵ�����Ϊ���һ���滻λ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceAllOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end);
		//�滻������ĳЩԪ��Ϊ��һ��Ԫ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceSomeOf(const AnyT1& t, const AnyT2& to,int startIndex,int length,int count);
		//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ�أ����صĵ�����Ϊ���һ���滻λ��
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceSomeOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end,int count);
		//�����������,startIndex��length�ֱ��ʾ��ʼ�±�ʹ������ݳ���
		void SortRandom(int startIndex,int length){return Pointer()->SortRandom(startIndex,length);}
		//�����������
		void SortRandom(int startIndex=0){return Pointer()->SortRandom(startIndex);};
		//������С�������������ݣ�����ʵ��ռ�õ����Ԫ��������������Ԫ����
		int Resize( int);
		//������С����һ���������ݣ���Resize�������һ�����ƵĹ���
		int ResizeAndDestroy( int);
		//������ָ��ֵ��ȵĵ�һ��Ԫ�أ��Ҳ����򷵻�-1
		template<typename AnyT>int IndexOf(const AnyT&t, int startIndex=0)const;
		//��ָ�����������ָ��ֵ��ȵĵ�һ��Ԫ�أ��Ҳ����򷵻�-1
		template<typename AnyT>int IndexOf(const AnyT&t, int startIndex,int length)const;
		//���õ�����ָ�������������ָ��ֵ��ȵĵ�һ��Ԫ�أ��Ҳ����򷵻�-1
		template<typename AnyT>int IndexOf(const AnyT&t, const Iterator<const T>& start,const Iterator<const T>& end)const;
		//������ָ��ֵ��ȵ����һ��Ԫ�أ��Ҳ����򷵻�-1
		template<typename AnyT>int LastIndexOf(const AnyT&t,int startIndex=0)const;
		//��ָ�����������ָ��ֵ��ȵ����һ��Ԫ�أ��Ҳ����򷵻�-1
		template<typename AnyT>int LastIndexOf(const AnyT&t,int startIndex,int length)const;
		//���õ�����ָ�������������ָ��ֵ��ȵ����һ��Ԫ�أ��Ҳ����򷵻�-1
		template<typename AnyT>int LastIndexOf(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const;
		//����ָ��Ԫ�ص�λ�ã��Ҳ�������end
		template<typename AnyT>Iterator<T> Find(const AnyT&t,int startIndex=0)const;
		//��ָ���������ָ��Ԫ�ص�λ�ã��Ҳ�������end
		template<typename AnyT>Iterator<T> Find(const AnyT&t,int startIndex,int length)const;
		//���õ�����ָ�����������ָ��Ԫ�ص�λ�ã��Ҳ�������end
		template<typename AnyT>Iterator<T> Find(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const;
		//������ָ��������ȵ�Ԫ����
		template<class AnyT>int CountOf(const AnyT&t,int startIndex=0)const;
		//��ָ�����������ָ��������ȵ�Ԫ����
		template<class AnyT>int CountOf(const AnyT&t,int startIndex,int length)const;
		//���õ�����ָ�������������ָ��������ȵ�Ԫ����
		template<class AnyT>int CountOf(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const;
		//��ȡ���һ��Ԫ�ص�����
		T& LastElement();
		//��ȡ���һ��Ԫ�ص�����
		const T& LastElement()const;
		//��ȡ��һ��Ԫ�ص�����
		T& FirstElement();
		//��ȡ��һ��Ԫ�ص�����
		const T& FirstElement()const;
		//��ȡ��������
		XArrayType GetArrayType()const;
		//��ȡǳ����
		XArray MakeCopy()const;
	};
	template<typename T>const XTypes& VArray<T>::CurrentType = NodeOfRoot::Add(L"LJ::VArray",Types<LJ::VArray<T> >(),TypesCheckingObject::MakeObject<T>(1),typeid(LJ::XBase));
	template<typename T>const XTypes& XArray<T>::CurrentType = NodeOfRoot::Add(L"LJ::XArray",Types<LJ::XArray<T> >(),TypesCheckingObject::MakeObject<T>(1),typeid(LJ::XBase));
	template<typename T>struct IArrayIterator:public IIterator<T>
	{
		T* pFirst;
		T* pCurrent;
		T* pEnd;
		IArrayIterator(const T*const first,const T*const current,const T*const end)
			:IIterator<T>(int(end-first)),pFirst(const_cast<T*>(first)),pCurrent(const_cast<T*>(current)),pEnd(const_cast<T*>(end)){}
		//������һ��Ԫ��
		virtual void Next(){++pCurrent;}
		//������һ��Ԫ��
		virtual void Fore(){--pCurrent;}
		//������n��Ԫ��
		virtual void NextN(int n){pCurrent+=n;}
		//������n��Ԫ��
		virtual void ForeN(int n){pCurrent-=n;}
		//���
		virtual int Minus(IIterator*p){return int(pCurrent-reinterpret_cast<IArrayIterator*&>(p)->pCurrent);}
		//��ת�����һ��
		virtual bool ToLast(){pCurrent = pEnd==NULL?NULL:pEnd-1;return pFirst!=pEnd;}
		//��ת���ս�λ��
		virtual bool ToEnd(){pCurrent = pEnd;return pFirst!=pEnd;}
		//���õ���ͷ
		virtual void Reset(){pCurrent = pFirst;}
		//����һ������
		virtual IIterator* NewCopy(){return new IArrayIterator<T>(pFirst,pCurrent,pEnd);}
		//��ȡ��ǰ��������
		virtual int GetCurrentIndex(){return int(pCurrent-pFirst);}
		//����
		virtual T& Index(int index){return *(pCurrent+index);}
		//��ȡ��ǰָ��
		virtual T*Current(){return pCurrent;}
		//��ȡ���һ��Ԫ�ص�ָ��
		virtual T*Last(){return pEnd==NULL?NULL:pEnd-1;}
		//��ȡ��һ��Ԫ�ص�ָ��
		virtual T*First(){return pFirst;}
		//��ȡ�ս�Ԫ�ص�ָ��
		virtual T*End(){return pEnd;}
		//�Ƚ�
		virtual int CompareWith(IIterator<T>*p)
		{
			if(pFirst!=reinterpret_cast<IArrayIterator<T>*&>(p)->pFirst)throw XException(L"���Ƚϵĵ�������һ��",E_INVALIDARG);
			return int(pCurrent-reinterpret_cast<IArrayIterator<T>*&>(p)->pCurrent);
		}
		//����
		virtual ~IArrayIterator(){}
	};
	template<class T>int VArray<T>::MinDecreaseDefault = INT_MAX;//������Ϊ���ֵʱ�������С��Сʱ���������������ڴ�
	template<class T>StaticProperty<int> XArray<T>::MinDecreaseDefault = StaticProperty<int>(XArray<T>::GetMinDecreaseDefault,XArray<T>::SetMinDecreaseDefault);//������Ϊ���ֵʱ�������С��Сʱ���������������ڴ�

	template<typename T>T* VArray<T>::Malloc(int size)
	{
		if(!size)return NULL;
		void*p;
		if((p = malloc(sizeof(T)*(size_t)size))==NULL)
		{
			Sleep(30);//��ͣһ������
			if((p = malloc(sizeof(T)*(size_t)size))==NULL)
				throw XException(L"�����ڴ�ʧ��",E_OUTOFMEMORY);
		}
		return reinterpret_cast<T*&>(p);
	}
	//��ȡ���鵱ǰ���ֽ���
	template<typename T>int VArray<T>::GetLengthOfBytes()const
	{
		return Length*sizeof(T);
	}
	//��������
	template<typename T>VArray<T>::~VArray()
	{
		if(type==SelfConstruct)
		{
			VArrayDeconstructMethod(pData,Length);
			free(pData);
		}
		else if(type==Normal)
		{
			delete []pData;
		}
	}
	//Ĭ�Ϲ��캯������ͬ��VArray(0)
	template<typename T>VArray<T>::VArray()
		:pData(NULL),maxSize(0),MinDecrease(MinDecreaseDefault),Length(0),type(SelfConstruct)
	{    }
	//ֱ�Ӵ���Ԫ������
	template<typename T>VArray<T>::VArray(int count)
		:pData(NULL),maxSize(0),MinDecrease(MinDecreaseDefault),Length(0),type(SelfConstruct)
	{
		if(count<0)throw XException(E_INVALIDARG);//count<0ʱ������Ч
		if(count>0)
		{
			pData = Malloc(count);
			maxSize = const_cast<int&>(Length) = count;
			VArrayDefaultConstructMethod(pData,count);
		}
	}
	//���ƹ��캯��
	template<typename T>VArray<T>::VArray(const VArray& xArray)
		:pData(NULL),maxSize(xArray.Length),MinDecrease(xArray.MinDecrease),Length(xArray.Length),type(SelfConstruct)
	{
		if(xArray.Length)
		{
			pData=Malloc(maxSize);
		}
		if(maxSize)VArrayCopyMethod(xArray.pData,pData,maxSize);
	}
	//�������������鹹��
	template<typename T>VArray<T>::VArray(const XArray<T>& xArray)
		:pData(NULL),maxSize(xArray.Length),MinDecrease(xArray.MinDecrease),Length(xArray.Length),type(SelfConstruct)
	{
		if(xArray.Length>0)
		{
			pData=Malloc(maxSize);
		}
		if(maxSize)VArrayCopyMethod((const T*)xArray,pData,maxSize);
	}
	//�������鳤�ȣ���ʹ��һ���ο�Ԫ������ʼ������Ԫ�أ�type��������ΪMalloc
	template<typename T>VArray<T>::VArray(int count,const T& t)
		:pData(NULL),maxSize(count),MinDecrease(MinDecreaseDefault),Length(count),type(SelfConstruct)
	{
		if(count<0)throw XException(E_INVALIDARG);//count<0ʱ������Ч
		if(count!=0)
		{
			pData=Malloc(count);
			VArrayConstructMethod(t,pData,count);
		}
	}
	//ʹ�õ���������
	template<typename T>template<class AnyT>VArray<T>::VArray(const Iterator<AnyT>&first,const Iterator<AnyT>&end)
		:pData(NULL),maxSize(end-first),MinDecrease(MinDecreaseDefault),Length(end-first),type(SelfConstruct)
	{
		if(maxSize)
		{
			pData=Malloc(maxSize);
			T* p(pData);
			Iterator<AnyT>pAny(first);
			while(pAny!=end)placementnew(p++,*pAny++);
		}
	}
	//ֱ�Ӵ���ָ���Ԫ����������������,pΪNULLʱ����count��Ԫ�ص�����,typeָ����pָ���ڴ�Ĺ���ʽ
	template<typename T>VArray<T>::VArray(int count,typename Types<T>::Normal* p,XArrayType type)
		:pData(NULL),maxSize(count),MinDecrease(MinDecreaseDefault),Length(count),type(type)
	{
		if(count<0)throw XException(E_INVALIDARG);//count<0ʱ������Ч
		if(count!=0)
		{
			if(!p)
			{
				pData=Malloc(maxSize);
				VArrayDefaultConstructMethod(pData,count);
				this->type = SelfConstruct;
			}
			else
			{
				pData = (typename Types<T>::Normal*)p;
			}
		}
	}
	//ֱ�Ӵ���ָ���Ԫ����������������,pΪNULLʱ����count��Ԫ�ص�����,typeָ����pָ���ڴ�Ĺ���ʽ
	template<typename T>VArray<T>::VArray(int count,typename Types<T>::Normal const* p,XArrayType type)
		:pData(NULL),maxSize(count),MinDecrease(MinDecreaseDefault),Length(count),type(type)
	{
		if(count<0)throw XException(E_INVALIDARG);//count<0ʱ������Ч
		if(count!=0)
		{
			if(!p)
			{
				pData=Malloc(maxSize);
				VArrayDefaultConstructMethod(pData,count);
				this->type = SelfConstruct;
			}
			else
			{
				if(type==Reference)
				{
					pData = const_cast<T*>(p);
				}
				else if(type==SelfConstruct)
				{
					pData=Malloc(count);
					VArrayCopyConstructMethod(p,pData,count);
				}
				else if(type==Normal)
				{
					pData = new T[count];
					VArrayCopyMethod(p,pData,count);
				}
			}
		}
	}
	//ֱ��ת����constָ����ʽ
	template<typename T>VArray<T>::operator const T*const&()const
	{
		return pData;
	}
	//ֱ��ת����ָ����ʽ
	template<typename T>VArray<T>::operator T*const &()
	{
		return pData;
	}
	//������
	template<typename T>Iterator<T> VArray<T>::First()
	{
		return new IArrayIterator<T>(pData,pData,pData+Length);
	}
	//������
	template<typename T>Iterator<const T> VArray<T>::First()const
	{
		return new IArrayIterator<const T>(pData,pData,pData+Length);
	}
	//������
	template<typename T>Iterator<T> VArray<T>::Last()
	{
		return new IArrayIterator<T>(pData,Length?pData+Length-1:NULL,pData+Length);
	}
	//������
	template<typename T>Iterator<const T> VArray<T>::Last()const
	{
		return new IArrayIterator<const T>(pData,Length?pData+Length-1:NULL,pData+Length);
	}
	//������
	template<typename T>Iterator<T> VArray<T>::End()
	{
		return new IArrayIterator<T>(pData,pData+Length,pData+Length);
	}
	//������
	template<typename T>Iterator<const T> VArray<T>::End()const
	{
		return new IArrayIterator<const T>(pData,pData+Length,pData+Length);
	}
	//������һ�����������(���ƹ���)������������ݽ�������
	template<typename T>VArray<T>& VArray<T>::operator=(const VArray<T>& xArray)
	{
		if(type==Reference)//����ģʽ
		{
			type = SelfConstruct;
			maxSize = const_cast<int&>(Length) = xArray.Length;
			pData=Malloc(Length);
			T*p(pData),*end(pData+Length),*px(xArray.pData);
			while(p<end)placementnew(p++,*px++);
		}
		else if(type==SelfConstruct)//�Թ���ģʽ
		{
			if(xArray.Length>Length)
			{
				VArrayDeconstructMethod(pData,Length);//����
				void * tmp = realloc(pData,sizeof(T)*xArray.Length);
				if(tmp==NULL)throw XException(L"�����ڴ�ʧ��",E_OUTOFMEMORY);
				pData = (T*)tmp;
				maxSize = const_cast<int&>(Length) = xArray.Length;
				T* p(pData),*end(pData+Length),*px(xArray.pData);
				while(p<end)placementnew(p++,*px++);
			}
			else if(xArray.Length==Length)
			{
				T* p(pData),*end(pData+Length),*px(xArray.pData);
				while(p<end)(*p++)=(*px++);
			}
			else if(maxSize-xArray.Length>MinDecrease)
			{
				VArrayDeconstructMethod(pData,Length);//����
				void * tmp = realloc(pData,sizeof(T)*xArray.Length);
				if(xArray.Length>0 && tmp==NULL)throw XException(L"�����ڴ�ʧ��",E_OUTOFMEMORY);
				pData = (T*)tmp;
				maxSize = const_cast<int&>(Length) = xArray.Length;
				T* p(pData),*end(pData+Length),*px(xArray.pData);
				while(p<end)placementnew(p++,*px++);
			}
			else
			{
				VArrayDeconstructMethod(pData+xArray.Length,Length-xArray.Length);//����
				const_cast<int&>(Length) = xArray.Length;
				T* p(pData),*end(pData+Length),*px(xArray.pData);
				while(p<end)(*p++)=(*px++);
			}
		}
		else//��ͨģʽ
		{
			ResizeAndDestroy(xArray.Length);
			VArrayCopyMethod(xArray.pData,pData,Length);
		}
		return *this;
	}
	//��ȡ�������һ���֣������飩
	template<typename T>VArray<T> VArray<T>::SubArray(int startIndex,int length,XArrayType type)const
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);//������Ч
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(length==0)return VArray<T>(0,(const T *)0,type);
		T* tmp = NULL;
		if(type==Reference)
		{
			tmp = pData+startIndex;
		}
		else if(type == Normal)
		{
			tmp = new T[length];
			VArrayCopyMethod(pData+startIndex,tmp,length);
		}
		else if(type == SelfConstruct)
		{
			tmp = Malloc(length);
			VArrayCopyConstructMethod(pData+startIndex,tmp,length);
		}
		return VArray<T>(length,tmp,type);
	}
	//������pdata����len��Ԫ���γ�����
	template<typename T>template<typename AnyT>VArray<T> VArray<T>::CopyFrom(const VArray<AnyT>&source)
	{
		if(source.Length==0)return VArray<T>();
		T* p = Malloc(source.Length);
		T* pt(p);
		T* end(p+source.Length);
		const AnyT* px(source);
		while(pt!=end)placementnew(pt++,*px++);
		return VArray<T>(source.Length,p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>VArray<T> VArray<T>::CopyFrom(const VArray<AnyT>&source, int startIndex)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//������Ч
		if(startIndex>source.Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(source.Length==startIndex)return  VArray<T>();
		T* p = Malloc(source.Length-startIndex);
		T* pt(p);
		T* end(p+source.Length-startIndex);
		const AnyT* px(source+startIndex);
		while(pt!=end)placementnew(pt++,*px++);
		return VArray<T>(source.Length-startIndex,p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>VArray<T> VArray<T>::CopyFrom(const VArray<AnyT>&source, int startIndex,int length)
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);//������Ч
		if(startIndex + length>source.Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(!length)return  VArray<T>();
		T* p = Malloc(length);
		T* pt(p);
		T* end(p+length);
		const AnyT* px(source+startIndex);
		while(pt!=end)placementnew(pt++,*px++);
		return VArray<T>(length,p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>VArray<T> VArray<T>::CopyFrom(const Iterator<const T>&first,const Iterator<const T>&end)
	{
		int length = end-first;
		if(length==0)return VArray<T>();
		T* p = Malloc(length);
		T* pt(p);
		T* end(p+length);
		Iterator<const T> px(first);
		while(pt!=end)placementnew(pt++,*px++);
		return VArray<T>(length,p,SelfConstruct);
	}
	//������pdata��startByte�ֽڴ�����len���ֽ��γ�����
	template<typename T>template<typename AnyT>VArray<T> VArray<T>::CopyFromByBytes(const VArray<AnyT>&source)
	{
		if(source.Length==0)return VArray<T>();
		T* p = Malloc(((sizeof(AnyT)*source.Length)%sizeof(T))?sizeof(AnyT)*source.Length/sizeof(T)+1:sizeof(AnyT)*source.Length/sizeof(T));
		XBase::Memory::Copy(p,source,source.GetLengthOfBytes());
		return VArray<T>((source.GetLengthOfBytes()%sizeof(T))?source.GetLengthOfBytes()/sizeof(T)+1:source.GetLengthOfBytes()/sizeof(T),p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>VArray<T> VArray<T>::CopyFromByBytes(const VArray<AnyT>&source, int startByte)
	{
		if(startByte<0)throw XException(E_INVALIDARG);//������Ч
		if(startByte>source.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);//������Ч
		if(startByte==source.GetLengthOfBytes())return VArray<T>();
		T* p = Malloc(((source.GetLengthOfBytes()-startByte)%sizeof(T))?(source.GetLengthOfBytes()-startByte)/sizeof(T)+1:(source.GetLengthOfBytes()-startByte)/sizeof(T));
		XBase::Memory::Copy(p,source,sizeof(AnyT)*source.Length-startByte);
		return VArray<T>(((source.GetLengthOfBytes()-startByte)%sizeof(T))?(source.GetLengthOfBytes()-startByte)/sizeof(T)+1:(source.GetLengthOfBytes()-startByte)/sizeof(T),p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>VArray<T> VArray<T>::CopyFromByBytes(const VArray<AnyT>&source, int startByte,int lengthOfBytes)
	{
		if(startByte<0 || lengthOfBytes<0)throw XException(E_INVALIDARG);//������Ч
		if(startByte+lengthOfBytes>source.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);//������Ч
		if(!lengthOfBytes)return VArray<T>();
		T* p = Malloc((lengthOfBytes%sizeof(T))?lengthOfBytes/sizeof(T)+1:lengthOfBytes/sizeof(T));
		XBase::Memory::Copy(p,source,lengthOfBytes);
		return VArray<T>((lengthOfBytes%sizeof(T))?lengthOfBytes/sizeof(T)+1:lengthOfBytes/sizeof(T),p,SelfConstruct);
	}
	//������������ݸ���һ���ֵ���һ������
	template<typename T>template<typename AnyT>int VArray<T>::CopyTo(VArray<AnyT>& destination,int sourceIndex, int destinationIndex)const
	{
		if(sourceIndex<0 || destinationIndex<0)throw XException(E_INVALIDARG);//������Ч
		if(sourceIndex>Length  || destinationIndex>destination.Length)throw XException(COR_E_INDEXOUTOFRANGE);
		int length = (Length-sourceIndex > destination.Length-destinationIndex)?destination.Length-destinationIndex:Length-sourceIndex;
		T* p = *this+sourceIndex;
		T* pEnd = p+length;
		AnyT* pd = destination+destinationIndex;
		while(p<pEnd){*pd = *p;++p;++pd;}//ǿ��ת��
		return length;
	}
	template<typename T>template<typename AnyT>int VArray<T>::CopyTo(VArray<AnyT>& destination,int sourceIndex, int destinationIndex, int length)const
	{
		if(sourceIndex<0 || destinationIndex<0 || length<0)throw XException(E_INVALIDARG);//������Ч
		if(sourceIndex+length>Length  || destinationIndex+length>destination.Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T* p = *this+sourceIndex;
		T* pEnd = p+length;
		AnyT* pd = destination+destinationIndex;
		while(p<pEnd){*pd = *p;++p;++pd;}//ǿ��ת��
		return length;
	}
	//������һ�����͵����鸴��һ�����ֽ���
	template<typename T>template<typename AnyT>int VArray<T>::CopyToByBytes(VArray<AnyT>& dest, int sourceByte, int destinationByte)const
	{
		if(sourceByte<0 || destinationByte<0)throw XException(E_INVALIDARG);//������Ч
		if(sourceByte>GetLengthOfBytes() || destinationByte>dest.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);
		int lengthOfByte =  (GetLengthOfBytes()-sourceByte > dest.GetLengthOfBytes()-destinationByte)?dest.GetLengthOfBytes()-destinationByte:GetLengthOfBytes()-sourceByte;
		XBase::Memory::Copy(((unsigned char*)(AnyT*)dest)+destinationByte,((unsigned char*)pData)+sourceByte,lengthOfByte);
		return lengthOfByte;
	}
	template<typename T>template<typename AnyT>int VArray<T>::CopyToByBytes(VArray<AnyT>& dest, int sourceByte, int destinationByte, int lengthOfByte)const
	{
		if(sourceByte<0 || destinationByte<0 || lengthOfByte<0)throw XException(E_INVALIDARG);//������Ч
		if(sourceByte + lengthOfByte>GetLengthOfBytes() || lengthOfByte+destinationByte>dest.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);
		XBase::Memory::Copy(((unsigned char*)(AnyT*)dest)+destinationByte,((unsigned char*)pData)+sourceByte,lengthOfByte);
		return lengthOfByte;
	}
	//�ӷ�����
	template<typename T> T* operator+(VArray<T>& xArray,int mov)
	{
		return (T*)xArray+mov;
	}
	template<typename T> const T* operator+(const VArray<T>& xArray,int mov)
	{
		return (const T*)xArray+mov;
	}
	template<typename T> T* operator-(VArray<T>& xArray,int mov)
	{
		return (T*)xArray-mov;
	}
	template<typename T> const T* operator-(const VArray<T>& xArray,int mov)
	{
		return (const T*)xArray-mov;
	}
	template<typename T> T* operator+(int mov,VArray<T>& xArray)
	{
		return (T*)xArray+mov;
	}
	template<typename T> const T* operator+(int mov,const VArray<T>& xArray)
	{
		return (const T*)xArray+mov;
	}
	//��ϵ�����
	template<typename T> bool operator==(const VArray<T>& x1,const VArray<T>& x2)
	{
		if(x1.Length!=x2.Length)return false;
		const T* p1=x1;const pe1=p1+x1.Length;
		const T* p2=x2;
		while(p1!=pe1)if(*p1++!=*p2++)return false;
		return true;
	}
	template<typename T> bool operator!=(const VArray<T>& x1,const VArray<T>& x2)
	{
		if(x1.Length!=x2.Length)return true;
		const T* p1=x1;const pe1=p1+x1.Length;
		const T* p2=x2;
		while(p1!=pe1)if(*p1++!=*p2++)return true;
		return false;
	}
	template<typename T> bool operator>=(const VArray<T>& x1,const VArray<T>& x2)
	{
		const T* p1=x1;const pe1=p1+x1.Length;
		const T* p2=x2;const pe2=p2+x2.Length;
		while(p1!=pe1&& pe2!=pe2){if(*p1!=*p2)break;++p1;++p2;}
		if(p1==pe1)return p2==pe2;
		if(p2==pe2)return true;
		return *p1>=*p2;
	}
	template<typename T> bool operator<=(const VArray<T>& x1,const VArray<T>& x2)
	{
		const T* p1=x1;const pe1=p1+x1.Length;
		const T* p2=x2;const pe2=p2+x2.Length;
		while(p1!=pe1&& pe2!=pe2){if(*p1!=*p2)break;++p1;++p2;}
		if(p1==pe1)return p2!=pe2;
		if(p2==pe2)return false;
		return *p1<=*p2;
	}
	template<typename T> bool operator>(const VArray<T>& x1,const VArray<T>& x2)
	{
		const T* p1=x1;const pe1=p1+x1.Length;
		const T* p2=x2;const pe2=p2+x2.Length;
		while(p1!=pe1&& pe2!=pe2){if(*p1!=*p2)break;++p1;++p2;}
		if(p1==pe1)return false;
		if(p2==pe2)return true;
		return *p1>*p2;
	}
	template<typename T> bool operator<(const VArray<T>& x1,const VArray<T>& x2)
	{
		const T* p1=x1;const pe1=p1+x1.Length;
		const T* p2=x2;const pe2=p2+x2.Length;
		while(p1!=pe1&& pe2!=pe2){if(*p1!=*p2)break;++p1;++p2;}
		if(p1==pe1)return true;
		if(p2==pe2)return false;
		return *p1<*p2;
	}
	//��������һϵ��Ԫ�ص�ֵ����Ϊt
	template<typename T>template<typename AnyT>void  VArray<T>::ResetTo(const AnyT& t)
	{
		T*p(pData);
		T*end(pData+Length);
		while(p<end)*p++=t;
	}
	template<typename T>template<typename AnyT>void  VArray<T>::ResetTo(const AnyT& t,  int index, int length)
	{
		if(index<0 || length<0)throw XException(E_INVALIDARG);//������Ч
		if(index+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(!length)return;
		T*p(pData+index);
		T*end(pData+Length);
		while(p<end)*p++=t;
	}
	//�������ĳ��λ�ò���Ԫ�ػ�����
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::Insert(int index,const AnyT&t)
	{
		if(index<0)throw XException(E_INVALIDARG);//������Ч
		if(index>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(type==Reference)//�½�һ���ڴ��������Ա�������
		{
			T*p=Malloc(Length+1);
			type = SelfConstruct;
			T* pt(p);
			T* ps(pData);
			T* end(pData+index);
			while(ps<end)placementnew(pt++,*ps++);
			placementnew(pt++,t);
			end = pData+Length;
			while(ps!=end)placementnew(pt++,*ps++);
			pData = p;
			maxSize = ++const_cast<int&>(Length);
		}
		else if(type==SelfConstruct)
		{
			if(maxSize>Length)//����Ҫ��������ռ�
			{
				++const_cast<int&>(Length);
				if(index+1==Length)
				{
					placementnew(pData+index,t);
				}
				else
				{
					T*p(pData+Length);
					T*end(pData+index);
					placementnew(--p,*(p-1));
					while(--p!=end)*p = *(p-1);
					VArrayDeconstructMethod(p,1);
					placementnew(p,t);
				}
			}
			else//��Ҫ��������ռ�
			{
				maxSize = ++const_cast<int&>(Length);
				T* p = Malloc(Length);
				T* px(p);
				T* end(p+index);
				T* ps(pData);
				while(px!=end)placementnew(px++,*ps++);//����
				placementnew(px++,t);
				end = p+Length;
				while(px!=end)placementnew(px++,*ps++);//����
				VArrayDeconstructMethod(pData,Length-1);
				free(pData);
				pData = p;
			}
		}
		else if(type==Normal)
		{
			if(maxSize>Length)//����Ҫ��������ռ�
			{
				++const_cast<int&>(Length);
				T*p(pData+Length);
				T*end(pData+index);
				while(--p!=end)*p = *(p-1);
				*p=t;
			}
			else//��Ҫ��������ռ�
			{
				maxSize = ++const_cast<int&>(Length);
				T* p = new T[Length];
				T* px(p);
				T* end(p+index);
				T* ps(pData);
				while(px!=end)*px++ = *ps++;//����
				*px++ = t;
				end = p+Length;
				while(px!=end)*px++ = *ps++;//����
				delete []pData;
				pData = p;
			}
		}
		return new IArrayIterator<T>(pData,pData+index,pData+Length);
	}
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::Insert(const Iterator<T>&it,const AnyT&t)
	{
		if(it.GetLength()!=Length)throw XException(L"ָ���ĵ������Ѿ�ʧЧ",E_INVALIDARG);
		return Insert(it-pData,t);
	}
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::InsertArray(int index,const VArray<AnyT>&xArray)
	{
		if(index<0)throw XException(E_INVALIDARG);//������Ч
		if(index>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(xArray.Length==0)return new IArrayIterator<T>(pData,pData+index,pData+Length);
		if(type==Reference)//�½�һ���ڴ��������Ա�������
		{
			T*p=Malloc(Length+xArray.Length);
			type = SelfConstruct;
			T* pt(p);
			T* ps(pData);
			T* end(pData+index);
			while(ps<end)placementnew(pt++,*ps++);
			const T* px(xArray);
			end = pt + xArray.Length;
			while(pt<end)placementnew(pt++,*px++);
			end = pData+Length;
			while(ps!=end)placementnew(pt++,*ps++);
			pData = p;
			maxSize = (const_cast<int&>(Length)+=xArray.Length);
		}
		else if(type==SelfConstruct)
		{
			if(maxSize>=Length+xArray.Length)//����Ҫ��������ռ�
			{
				const_cast<int&>(Length)+=xArray.Length;
				if(index+xArray.Length==Length)
				{
					const T* px(xArray);
					T*p(pData+index);
					T*end(pData+Length);
					while(p!=end)placementnew(p++,*px++);
				}
				else
				{
					T*p(pData+Length);
					T*end(p+index);
					T*ps(pData+Length-xArray.Length);
					T*pm(ps);
					while(ps!=end){if(p>pm)placementnew(--p,*--ps);else *--p=*--ps;}
					const T*px(xArray);
					end = const_cast<T*>(xArray+xArray.Length);
					while(px!=end){if(p<pm)(*p++)=(*px++);else placementnew(p++,*px++);}
				}
			}
			else//��Ҫ��������ռ�
			{
				maxSize = (const_cast<int&>(Length)+=xArray.Length);
				T* p = Malloc(Length);
				T* pt(p);
				T* end(p+index);
				T* ps(pData);
				while(pt!=end)placementnew(pt++,*ps++);//����
				const T*px(xArray);
				end = const_cast<T*>(xArray+xArray.Length);
				while(px!=end)placementnew(pt++,*px++);
				end = p+Length;
				while(pt!=end)placementnew(pt++,*ps++);//����
				VArrayDeconstructMethod(pData,Length-xArray.Length);
				free(pData);
				pData = p;
			}
		}
		else if(type==Normal)
		{
			if(maxSize>=Length+xArray.Length)//����Ҫ��������ռ�
			{
				const_cast<int&>(Length)+=xArray.Length;
				T*p(pData+Length);
				T*end(pData+index);
				T*ps(p-xArray.Length);
				while(ps!=end)*--p=*--ps;
				const T* px(xArray+Length);
				while(p!=end)*--p=*--px;
			}
			else//��Ҫ��������ռ�
			{
				maxSize = (const_cast<int&>(Length)+=xArray.Length);
				T* p = new T[Length];
				T* px(p);
				T* end(p+index);
				T* ps(pData);
				while(px!=end)*px++ = *ps++;//����
				const T*pxx(xArray);
				end = const_cast<T*>(xArray+xArray.Length);
				while(px!=end)*px++ = *pxx++;
				end = p+Length;
				while(px!=end)*px++ = *ps++;//����
				delete []pData;
				pData = p;
			}
		}
		return new IArrayIterator<T>(pData,pData+index,pData+Length);
	}
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::InsertArray(const Iterator<T>&it,const VArray<AnyT>&xArray)
	{
		if(it.GetLength()!=Length || it.GetFirstElementPointer()!=pData)throw XException(L"ָ���ĵ������Ѿ�ʧЧ",E_INVALIDARG);
		return InsertArray(it-pData,xArray);
	}
	//�������β���Ԫ��
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::Append(const AnyT&t)
	{
		return Insert(Length,t);
	}
	//�������β�������
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::AppendArray(const VArray<AnyT>&xArray)
	{
		return InsertArray(Length,xArray);
	}
	//��������ɾ��ָ�������Ԫ��
	template<typename T>Iterator<T>  VArray<T>::Remove(int startIndex)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//������Ч
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(startIndex==0)//ȫ���Ƴ�
		{
			if(type==SelfConstruct)
			{
				VArrayDeconstructMethod(pData,Length);
				if(MinDecrease<maxSize)
				{
					free(pData);
					maxSize=0;
				}
			}
			else if(type==Normal)
			{
				if(MinDecrease<maxSize)
				{
					delete[]pData;
					maxSize=0;
				}
			}
			else maxSize=0;
			pData = NULL;
			const_cast<int&>(Length)=0;
			return End();
		}
		if(type == Reference)
		{
			T*p =Malloc(startIndex);
			VArrayCopyConstructMethod(pData,p,startIndex);
			pData = p;
			type = SelfConstruct;
			maxSize = startIndex;
		}
		else if(type==SelfConstruct)
		{
			if(MinDecrease+startIndex<maxSize)//��Ҫ��������ռ�
			{
				T* p = Malloc(startIndex);
				VArrayCopyConstructMethod(pData,p,startIndex);
				VArrayDeconstructMethod(pData,Length);
				free(pData);
				pData = p;
				maxSize=startIndex;
			}
			else VArrayDeconstructMethod(pData+startIndex,Length-startIndex);
		}
		else if(type==Normal)
		{
			if(MinDecrease+startIndex<maxSize)
			{
				T* p = new T[startIndex];
				VArrayCopyMethod(pData,p,startIndex);
				delete[]pData;
				pData = p;
				maxSize=startIndex;
			}
		}
		const_cast<int&>(Length)=startIndex;
		return End();
	}
	template<typename T>Iterator<T>  VArray<T>::RemoveAt(int index)
	{
		if(index<0 )throw XException(E_INVALIDARG);//������Ч
		if(index>=Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(index+1==Length)return Remove(index);

		if(type == Reference)
		{
			T*p =Malloc(Length-1);
			VArrayCopyConstructMethod(pData,p,index);
			VArrayCopyConstructMethod(pData+index+1,p+index,Length-index-1);
			pData = p;
			type = SelfConstruct;
			maxSize = Length-1;
		}
		else if(type==SelfConstruct)
		{
			if(MinDecrease+Length-1<maxSize)//��Ҫ��������ռ�
			{
				T* p = Malloc(Length-1);
				VArrayCopyConstructMethod(pData,p,index);
				VArrayCopyConstructMethod(pData+index+1,p+index,Length-index-1);
				VArrayDeconstructMethod(pData,Length);
				free(pData);
				pData = p;
				maxSize=Length-1;
			}
			else
			{
				T*ps(pData+index+1);
				T*p(pData+index);
				T*end(pData+Length);
				while(ps!=end)*p++ = *ps++;
				VArrayDeconstructMethod(p,1);
			}
		}
		else if(type==Normal)
		{
			if(MinDecrease+Length<=maxSize)
			{
				T* p = new T[Length-1];
				VArrayCopyMethod(pData,p,index);
				VArrayCopyMethod(pData+index+1,p+index,Length-index-1);
				delete[]pData;
				pData = p;
				maxSize=index;
			}
		}
		--const_cast<int&>(Length);
		return new IArrayIterator<T>(pData,pData+index,pData+Length);
	}
	template<typename T>Iterator<T>  VArray<T>::Remove(int startIndex,int length)
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);//������Ч
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(startIndex+length==Length)return Remove(startIndex);

		if(type == Reference)
		{
			T*p =Malloc(Length-length);
			VArrayCopyConstructMethod(pData,p,startIndex);
			VArrayCopyConstructMethod(pData+startIndex+length,p+startIndex,Length-startIndex-length);
			pData = p;
			type = SelfConstruct;
			maxSize = Length-length;
		}
		else if(type==SelfConstruct)
		{
			if(MinDecrease+Length-length<maxSize)//��Ҫ��������ռ�
			{
				T* p = Malloc(Length-length);
				VArrayCopyConstructMethod(pData,p,startIndex);
				VArrayCopyConstructMethod(pData+startIndex+length,p+startIndex,Length-startIndex-length);
				VArrayDeconstructMethod(pData,Length);
				free(pData);
				pData = p;
				maxSize=Length-length;
			}
			else
			{
				T*ps(pData+startIndex+length);
				T*p(pData+startIndex);
				T*end(pData+Length);
				while(ps!=end)*p++ = *ps++;
				VArrayDeconstructMethod(p,length);
			}
		}
		else if(type==Normal)
		{
			if(MinDecrease+Length-length<maxSize)
			{
				T* p = new T[Length-length];
				VArrayCopyMethod(pData,p,startIndex);
				VArrayCopyMethod(pData+startIndex+length,p+startIndex,Length-startIndex-length);
				delete[]pData;
				pData = p;
				maxSize=startIndex;
			}
		}
		const_cast<int&>(Length)-=length;
		return new IArrayIterator<T>(pData,pData+startIndex,pData+Length);
	}
	template<typename T>Iterator<T>  VArray<T>::Remove(const Iterator<T>&first,const Iterator<T>&end)
	{
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"ָ���ĵ������Ѿ�ʧЧ",E_INVALIDARG);
		return Remove(int((T*)first-pData),int((T*)end-(T*)first));
	}
	//�Ƴ�����ָ�������е�һ����ָ��ֵ��ȵ�Ԫ��
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::RemoveOneOf(const AnyT&t,int startIndex)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T*end(pData+Length);
		T*pt(pData+startIndex);
		while(pt!=end && !(*pt==t))++pt;//������ͬԪ�ص�λ��
		if(pt==end)return End();
		int index = int(pt-pData);
		if(type == Reference)
		{
			T* p = Malloc(Length-1);
			VArrayCopyMethod(pData,p,index);
			VArrayCopyMethod(pt+1,p+index,Length-index-1);
			pData = p;
			--const_cast<int&>(Length);
			type = SelfConstruct;
		}
		else
		{
			while(++pt!=end)*(pt-1)=*pt;
			Resize(Length-1);
		}
		return new IArrayIterator<T>(pData,pData+index,pData+Length);
	}
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::RemoveOneOf(const AnyT&t,int startIndex,int length)
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T*pt(pData+startIndex);
		T*end(pt+length);
		while(pt!=end && !(*pt==t))++pt;//������ͬԪ�ص�λ��
		if(pt==end)return new IArrayIterator<T>(pData,pt,pData+Length);
		int index = int(pt-pData);
		if(type == Reference)
		{
			T* p = Malloc(Length-1);
			VArrayCopyMethod(pData,p,index);
			VArrayCopyMethod(pt+1,p+index,Length-index-1);
			pData = p;
			--const_cast<int&>(Length);
			type = SelfConstruct;
		}
		else
		{
			end = pData+Length;
			while(++pt!=end)*(pt-1)=*pt;
			Resize(Length-1);
		}
		return new IArrayIterator<T>(pData,pData+index,pData+Length);
	}
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::RemoveOneOf(const AnyT&t,const Iterator<T>&first,const Iterator<T>&end)
	{
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"ָ���ĵ������Ѿ�ʧЧ",E_INVALIDARG);
		return RemoveOneOf(t,int((T*)first-pData),int((T*)end-(T*)first));
	}
	//�Ƴ�����ָ�������г��ֵ�������ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ�
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::RemoveAllOf(const AnyT&t,int startIndex)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(type == Reference)
		{
			T*end(pData+Length);
			T*pt(pData+startIndex);
			while(pt!=end && !(*pt==t))++pt;//������ͬԪ�ص�λ��
			if(pt==end)return End();//û�ҵ���Ҫ�Ƴ���Ԫ��
			T* p = Malloc(Length-1);//ֱ�ӷ���ռ䣨�����
			maxSize=Length-1;
			int index = int(pt-pData);
			VArrayCopyConstructMethod(pData,p,index);
			T* pc(p+index);
			while(++pt!=end)if(*pt==t)index=int(pc-p);else placementnew(pc++,*pt);
			pData = p;
			const_cast<int&>(Length) = pc-p;
			type = SelfConstruct;
			return new IArrayIterator<T>(pData,pData+index,pData+Length);
		}
		T*end(pData+Length);
		T*pt(pData+startIndex);
		T*pc(pt);
		T*pindex=pData+Length;
		while(pt!=end)
		{
			if(*pt==t){pindex = pc;++pt;}
			else if(pc!=pt)*pc++=*pt++;
		}
		Resize(Length-int(pt-pc));
		return new IArrayIterator<T>(pData,pindex,pData+Length);
	}
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::RemoveAllOf(const AnyT&t,int startIndex,int length)
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(type == Reference)
		{
			T*pt(pData+startIndex);
			T*end(pt+length);
			while(pt!=end && !(*pt==t))++pt;//������ͬԪ�ص�λ��
			if(pt==end)return new IArrayIterator<T>(pData,pt,pData+Length);//û�ҵ���Ҫ�Ƴ���Ԫ��
			T* p = Malloc(Length-1);//ֱ�ӷ���ռ䣨�����
			maxSize=Length-1;
			int index = int(pt-pData);
			VArrayCopyConstructMethod(pData,p,index);
			T* pc(p+index);
			while(++pt!=end)if(*pt==t)index=int(pc-p);else placementnew(pc++,*pt);
			pData = p;
			const_cast<int&>(Length) = pc-p;
			type = SelfConstruct;
			return new IArrayIterator<T>(pData,pData+index,pData+Length);
		}
		T*end(pData+Length);//������ֹ��
		T*pt(pData+startIndex);//��ʼ���ҵ�
		T*pe(pt+length);//���ҽضϵ�
		T*pc(pt);//����������ʼ��
		T*pindex=pData+Length;//���ص�����λ��
		while(pt!=end)
		{
			if(pt<pe && *pt==t){pindex = pc;++pt;}
			else if(pc!=pt)*pc++=*pt++;
		}
		Resize(Length-int(pt-pc));
		return new IArrayIterator<T>(pData,pindex,pData+Length);
	}
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::RemoveAllOf(const AnyT&t,const Iterator<T>&first,const Iterator<T>&end)
	{
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"ָ���ĵ������Ѿ�ʧЧ",E_INVALIDARG);
		return RemoveAllOf(t,int((T*)first-pData),int((T*)end-(T*)first));
	}
	//�Ƴ�����ָ�������г��ֵ�������ָ��ֵ��ȵ����count��Ԫ�أ�ʹ��==���бȽϣ�
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::RemoveSomeOf(const AnyT&t,int startIndex,int length,int count)
	{
		if(startIndex<0 || length<0 || count<0)throw XException(E_INVALIDARG);
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(count==0)return End();
		if(type == Reference)
		{
			T*pt(pData+startIndex);
			T*end(pt+length);
			while(pt!=end && !(*pt==t))++pt;//������ͬԪ�ص�λ��
			if(pt==end)return new IArrayIterator<T>(pData,pt,pData+Length);//û�ҵ���Ҫ�Ƴ���Ԫ��
			--count;
			T* p = Malloc(Length-1);//ֱ�ӷ���ռ䣨�����
			maxSize=Length-1;
			int index = int(pt-pData);
			VArrayCopyConstructMethod(pData,p,index);
			T* pc(p+index);
			while(++pt!=end)if(*pt==t&& count>0){index=int(pc-p);--count;}else placementnew(pc++,*pt);
			pData = p;
			const_cast<int&>(Length) = pc-p;
			type = SelfConstruct;
			return new IArrayIterator<T>(pData,pData+index,pData+Length);
		}
		T*end(pData+Length);//������ֹ��
		T*pt(pData+startIndex);//��ʼ���ҵ�
		T*pe(pt+length);//���ҽضϵ�
		T*pc(pt);//����������ʼ��
		T*pindex=pData+Length;//���ص�����λ��
		while(pt!=end)
		{
			if(pt<pe && *pt==t &&count>0){pindex = pc;++pt;--count;}
			else if(pc!=pt)*pc++=*pt++;
		}
		Resize(Length-int(pt-pc));
		return new IArrayIterator<T>(pData,pindex,pData+Length);
	}
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::RemoveSomeOf(const AnyT&t,const Iterator<T>&first,const Iterator<T>&end,int count)
	{
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"ָ���ĵ������Ѿ�ʧЧ",E_INVALIDARG);
		return RemoveSomeOf(t,int((T*)first-pData),int((T*)end-(T*)first),count);
	}
	//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ��
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> VArray<T>::ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(type == Reference)
		{
			T*end(pData+Length);
			T*pt(pData+startIndex);
			while(pt!=end && !(*pt==t))++pt;//������ͬԪ�ص�λ��
			if(pt==end)return End();//û�ҵ���Ҫ�Ƴ���Ԫ��
			T* p = Malloc(Length);//ֱ�ӷ���ռ�
			maxSize=Length;
			int index = int(pt-pData);
			VArrayCopyConstructMethod(pData,p,Length);
			*(pt-pData+p)=to;
			pData = p;
			type = SelfConstruct;
			return new IArrayIterator<T>(pData,pData+index,pData+Length);
		}
		T*end(pData+Length);
		T*pt(pData+startIndex);
		T*pindex=pData+Length;
		while(pt!=end)
		{
			if(*pt==t)
			{
				pindex = pt;
				*pt = to;
				break;
			}
			++pt;
		}
		return new IArrayIterator<T>(pData,pindex,pData+Length);
	}
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> VArray<T>::ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex,int length)
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(type == Reference)
		{
			T*pt(pData+startIndex);
			T*end(pt+length);
			while(pt!=end && !(*pt==t))++pt;//������ͬԪ�ص�λ��
			if(pt==end)return End();//û�ҵ���Ҫ�Ƴ���Ԫ��
			T* p = Malloc(Length);//ֱ�ӷ���ռ�
			maxSize=Length;
			int index = int(pt-pData);
			VArrayCopyConstructMethod(pData,p,Length);
			*(pt-pData+p)=to;
			pData = p;
			type = SelfConstruct;
			return new IArrayIterator<T>(pData,pData+index,pData+Length);
		}
		T*pt(pData+startIndex);
		T*end(pt+length);
		T*pindex=pData+Length;
		while(pt!=end)
		{
			if(*pt==t)
			{
				pindex = pt;
				*pt = to;
				break;
			}
			++pt;
		}
		return new IArrayIterator<T>(pData,pindex,pData+Length);
	}
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> VArray<T>::ReplaceOneOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&first ,const Iterator<T>&end)
	{
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"ָ���ĵ������Ѿ�ʧЧ",E_INVALIDARG);
		return ReplaceOneOf(t,to,int((T*)first-pData),int((T*)end-(T*)first));
	}
	//�滻������������t��ȵ�Ԫ��Ϊ��һ��Ԫ��
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> VArray<T>::ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(type == Reference)
		{
			T*end(pData+Length);
			T*pt(pData+startIndex);
			while(pt!=end && !(*pt==t))++pt;//������ͬԪ�ص�λ��
			if(pt==end)return End();//û�ҵ���Ҫ�Ƴ���Ԫ��
			T* p = Malloc(Length);//ֱ�ӷ���ռ䣨�����
			maxSize=Length;
			int index = int(pt-pData);
			VArrayCopyConstructMethod(pData,p,Length);
			end = p+Length;
			pt = p+pt-pData;
			while(pt!=end)
			{
				if(*pt==t)
				{
					index=int(pt-p);
					*pt = to;
				}
				++pt;
			}
			pData = p;
			type = SelfConstruct;
			return new IArrayIterator<T>(pData,pData+index,pData+Length);
		}
		T*end(pData+Length);
		T*pt(pData+startIndex);
		T*pindex=pData+Length;
		while(pt!=end)
		{
			if(*pt==t)
			{
				pindex = pt;
				*pt = to;
			}
			++pt;
		}
		return new IArrayIterator<T>(pData,pindex,pData+Length);
	}
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> VArray<T>::ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex,int length)
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(type == Reference)
		{
			T*pt(pData+startIndex);
			T*end(pt+length);
			while(pt!=end && !(*pt==t))++pt;//������ͬԪ�ص�λ��
			if(pt==end)return End();//û�ҵ���Ҫ�Ƴ���Ԫ��
			T* p = Malloc(Length);//ֱ�ӷ���ռ䣨�����
			maxSize=Length;
			int index = int(pt-pData);
			VArrayCopyConstructMethod(pData,p,Length);
			pt = p+pt-pData;
			end = p+startIndex+length;
			while(pt!=end)
			{
				if(*pt==t)
				{
					index=int(pt-p);
					*pt = to;
				}
				++pt;
			}
			pData = p;
			type = SelfConstruct;
			return new IArrayIterator<T>(pData,pData+index,pData+Length);
		}
		T*pt(pData+startIndex);
		T*end(pt+length);
		T*pindex=pData+Length;
		while(pt!=end)
		{
			if(*pt==t)
			{
				pindex = pt;
				*pt = to;
			}
			++pt;
		}
		return new IArrayIterator<T>(pData,pindex,pData+Length);
	}
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> VArray<T>::ReplaceAllOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&first ,const Iterator<T>&end)
	{
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"ָ���ĵ������Ѿ�ʧЧ",E_INVALIDARG);
		return ReplaceAllOf(t,to,int((T*)first-pData),int((T*)end-(T*)first));
	}
	//�滻������ĳЩԪ��Ϊ��һ��Ԫ��
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> VArray<T>::ReplaceSomeOf(const AnyT1& t, const AnyT2& to,int startIndex,int length,int count)
	{
		if(startIndex<0 || length<0 || count<0)throw XException(E_INVALIDARG);
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(count==0)return End();
		if(type == Reference)
		{
			T*pt(pData+startIndex);
			T*end(pt+length);
			while(pt!=end && !(*pt==t))++pt;//������ͬԪ�ص�λ��
			if(pt==end)return End();//û�ҵ���Ҫ�Ƴ���Ԫ��
			T* p = Malloc(Length);//ֱ�ӷ���ռ䣨�����
			maxSize=Length;
			int index = int(pt-pData);
			VArrayCopyConstructMethod(pData,p,Length);
			pt = p+(pt-pData);
			end = p+startIndex+length;
			while(pt!=end)
			{
				if(*pt==t)
				{
					index=int(pt-p);
					*pt = to;
					if(--count==0)break;
				}
				++pt;
			}
			pData = p;
			type = SelfConstruct;
			return new IArrayIterator<T>(pData,pData+index,pData+Length);
		}
		T*pt(pData+startIndex);
		T*end(pt+length);
		T*pindex=pData+Length;
		while(pt!=end)
		{
			if(*pt==t)
			{
				pindex = pt;
				*pt = to;
				if(--count==0)break;
			}
			++pt;
		}
		return new IArrayIterator<T>(pData,pindex,pData+Length);
	}
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> VArray<T>::ReplaceSomeOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&first ,const Iterator<T>&end,int count)
	{
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"ָ���ĵ������Ѿ�ʧЧ",E_INVALIDARG);
		return ReplaceSomeOf(t,to,int((T*)first-pData),int((T*)end-(T*)first),count);
	}
		//�����������
	template<typename T>void VArray<T>::SortRandom(int startIndex,int len)
	{
		if(startIndex<0 || len<0)throw XException(E_INVALIDARG);
		if(startIndex+len>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		for(int i=1;i<len;++i)
		{
			XBase::Swap(*(pData+i),*(pData+XRandom::Default.Rand()%(i+1)));
		}
	}
	//�����������
	template<typename T>void VArray<T>::SortRandom(int startIndex=0){return SortRandom(startIndex,Length-startIndex);}
	//������С��������������
	template<typename T>int VArray<T>::Resize(int count)
	{
		if(count<0)throw XException(E_INVALIDARG);//������Ч
		if(type == SelfConstruct)
		{
			if(count>maxSize)
			{
				T* p=Malloc(count);
				VArrayCopyConstructMethod(pData,p,Length);
				VArrayDefaultConstructMethod(p+Length,count-Length);
				VArrayDeconstructMethod(pData,Length);
				free(pData);
				pData = p;
				maxSize = count;
			}
			else if(MinDecrease+count<maxSize)
			{
				T* p=Malloc(count);
				VArrayCopyConstructMethod(pData,p,count);
				VArrayDeconstructMethod(pData,Length);
				free(pData);
				pData = p;
				maxSize = count;
			}
			else
			{
				VArrayDeconstructMethod(pData+count,Length-count);
			}
		}
		else if(type == Reference || count>maxSize || count<maxSize-MinDecrease)//���·���
		{
			if(type == Reference || type==Normal)
			{
				T* p(NULL);
				if(count)p = new T[count];
				if(const_cast<int&>(Length) = Length<count?Length:count)
				{
					VArrayCopyMethod(pData,p,Length);
					if(type==Normal)delete []pData;
				}
				pData = p;
				type = Normal;
			}
			maxSize = count;
		}
		const_cast<int&>(Length) = count;
		return maxSize;
	}
	//������С����һ����������
	template<typename T>int VArray<T>::ResizeAndDestroy(int count)
	{
		if(count<0)throw XException(E_INVALIDARG);//������Ч
		if(type == SelfConstruct)
		{
			if(count>maxSize || MinDecrease+count<maxSize)
			{
				T* p=Malloc(count);
				VArrayDefaultConstructMethod(p,count);
				VArrayDeconstructMethod(pData,Length);
				free(pData);
				pData = p;
				maxSize = count;
			}
			else
			{
				VArrayDeconstructMethod(pData+count,Length-count);
			}
		}
		else if(type == Reference || count>maxSize || count<maxSize-MinDecrease)//���·���
		{
			if(type == Reference || type==Normal)
			{
				if(type==Normal)delete []pData;
				if(count)pData = new T[count];
				else pData = NULL;
				type = Normal;
			}
			maxSize = count;
		}
		const_cast<int&>(Length) = count;
		return maxSize;
	}
	//������ָ��ֵ��ȵĵ�һ��Ԫ�أ��Ҳ����򷵻�-1
	template<typename T>template<typename AnyT>int VArray<T>::IndexOf(const AnyT&t, int startIndex)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//������Ч
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T* p(pData+startIndex);
		T* end(pData+Length);
		while(p!=end)if(*p++==t)return int(p-pData-1);
		return -1;
	}
	template<typename T>template<typename AnyT>int VArray<T>::IndexOf(const AnyT&t, int startIndex,int length)const
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);//������Ч
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T* p(pData+startIndex);
		T* end(p+length);
		while(p!=end)if(*p++==t)return int(p-pData-1);
		return -1;
	}
	template<typename T>template<typename AnyT>int VArray<T>::IndexOf(const AnyT&t, const Iterator<const T>& first,const Iterator<const T>&end)const
	{
		if(first.GetLength()!=Length || end.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetFirstElementPointer()!=pData)throw XException(L"ָ���ĵ������������ڱ�����",E_INVALIDARG);//������Ч
		return IndexOf(t,(const T*)first-pData,(const T*)end-(const T*)first);
	}
	//������ָ��ֵ��ȵ����һ��Ԫ�أ��Ҳ����򷵻�-1
	template<typename T>template<typename AnyT>int VArray<T>::LastIndexOf(const AnyT&t, int startIndex)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//������Ч
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T* p(pData+Length);
		T* end(pData+startIndex);
		while(p--!=end)if(*p==t)return int(p-pData);
		return -1;
	}
	template<typename T>template<typename AnyT>int VArray<T>::LastIndexOf(const AnyT&t, int startIndex,int length)const
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);//������Ч
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T* end(pData+startIndex);
		T* p(end+length);
		while(p--!=end)if(*p==t)return int(p-pData);
		return -1;
	}
	template<typename T>template<typename AnyT>int VArray<T>::LastIndexOf(const AnyT&t, const Iterator<const T>& first,const Iterator<const T>&end)const
	{
		if(first.GetLength()!=Length || end.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetFirstElementPointer()!=pData)throw XException(L"ָ���ĵ������������ڱ�����",E_INVALIDARG);//������Ч
		return LastIndexOf(t,(const T*)first-pData,(const T*)end-(const T*)first);
	}
	//����ָ��Ԫ�ص�λ�ã��Ҳ�������end
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::Find(const AnyT&t,int startIndex)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		int count(0);
		T*p(pData+startIndex);
		T*end(pData+Length);
		while(p!=end)if(*p++==t)return new IArrayIterator<T>(pData,p-1,pData+Length);
		return End();
	}
	//��ָ���������ָ��Ԫ�ص�λ�ã��Ҳ�������end
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::Find(const AnyT&t,int startIndex,int length)const
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		int count(0);
		T*p(pData+startIndex);
		T*end(p+length);
		while(p!=end)if(*p++==t)return new IArrayIterator<T>(pData,p-1,pData+Length);
		return End();
	}
	//���õ�����ָ�����������ָ��Ԫ�ص�λ�ã��Ҳ�������end
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::Find(const AnyT&t,const Iterator<const T>& first,const Iterator<const T>& end)const
	{
		if(first.GetLength()!=Length || end.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetFirstElementPointer()!=pData)throw XException(L"ָ���ĵ������������ڱ�����",E_INVALIDARG);//������Ч
		return Find(t,(const T*)first-pData,(const T*)end-(const T*)first);
	}
	//������ָ��������ȵ�Ԫ����
	template<typename T>template<class AnyT>int VArray<T>::CountOf(const AnyT&t,int startIndex)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		int count(0);
		T*p(pData+startIndex);
		T*end(pData+Length);
		while(p!=end)if(*p++==t)++count;
		return count;
	}
	//��ָ�����������ָ��������ȵ�Ԫ����
	template<typename T>template<class AnyT>int VArray<T>::CountOf(const AnyT&t,int startIndex,int length)const
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		int count(0);
		T*p(pData+startIndex);
		T*end(p+length);
		while(p!=end)if(*p++==t)++count;
		return count;
	}
	//���õ�����ָ�������������ָ��������ȵ�Ԫ����
	template<typename T>template<class AnyT>int VArray<T>::CountOf(const AnyT&t,const Iterator<const T>& first,const Iterator<const T>& end)const
	{
		if(first.GetLength()!=Length || end.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetFirstElementPointer()!=pData)throw XException(L"ָ���ĵ������������ڱ�����",E_INVALIDARG);//������Ч
		return CountOf(t,(const T*)first-pData,(const T*)end-(const T*)first);
	}
	//��ȡ��һ��Ԫ�ص�����
	template<typename T>T& VArray<T>::FirstElement()
	{
		if(Length==0)throw XException("����Ϊ��",COR_E_INDEXOUTOFRANGE);
		return pData[0];
	}
	template<typename T>const T& VArray<T>::FirstElement()const
	{
		if(Length==0)throw XException("����Ϊ��",COR_E_INDEXOUTOFRANGE);
		return pData[0];
	}
	//��ȡ���һ��Ԫ�ص�����
	template<typename T>T& VArray<T>::LastElement()
	{
		if(Length==0)throw XException("����Ϊ��",COR_E_INDEXOUTOFRANGE);
		return pData[Length-1];
	}
	template<typename T>const T& VArray<T>::LastElement()const
	{
		if(Length==0)throw XException("����Ϊ��",COR_E_INDEXOUTOFRANGE);
		return pData[Length-1];
	}



	//XArray
	template<typename T>int XArray<T>::GetLength()const
	{
		return Pointer()->Length;
	}
	//��ȡ���鰴�ֽڼ���ĳ���
	template<typename T>int XArray<T>::GetLengthOfBytes()const
	{
		return Pointer()->Length;
	}
	//��ȡ��С����ռ�仯ֵ
	template<typename T>int XArray<T>::GetMinDecrease()const
	{
		return Pointer()->MinDecrease;
	}
	//������С����ռ�仯ֵ
	template<typename T>void XArray<T>::SetMinDecrease(int min)
	{
		Pointer()->MinDecrease = min;
	}
	//ֱ��ת����ָ����ʽ
	template<typename T>XArray<T>::operator const T*const& ()const
	{
		return *Pointer();
	}
	//ֱ��ת����ָ����ʽ
	template<typename T>XArray<T>::operator T*const &()
	{
		return *Pointer();
	}
	//������
	template<typename T>Iterator<T> XArray<T>::First()
	{
		return new IArrayIterator<T>((T*)*this,(T*)*this,*this+Length);
	}
	//������
	template<typename T>Iterator<const T> XArray<T>::First()const
	{
		return new IArrayIterator<T>((const T*)*this,(const T*)*this,*this+Length);
	}
	//������
	template<typename T>Iterator<T> XArray<T>::Last()
	{
		return new IArrayIterator<T>((T*)*this,Length==0?NULL:*this+Length-1,*this+Length);
	}
	//������
	template<typename T>Iterator<const T> XArray<T>::Last()const
	{
		return new IArrayIterator<T>((const T*)*this,Length==0?NULL:*this+Length-1,*this+Length);
	}
	//������
	template<typename T>Iterator<T> XArray<T>::End()
	{
		return new IArrayIterator<T>((T*)*this,*this+Length,*this+Length);
	}
	//������
	template<typename T>Iterator<const T> XArray<T>::End()const
	{
		return new IArrayIterator<T>((const T*)*this,*this+Length,*this+Length);
	}

	//�ӷ�����
	template<typename T> T* operator+(XArray<T>& xArray,int mov)
	{
		return (T*)xArray+mov;
	}
	template<typename T> const T* operator+(const XArray<T>& xArray,int mov)
	{
		return (const T*)xArray+mov;
	}
	template<typename T> T* operator-(XArray<T>& xArray,int mov)
	{
		return (T*)xArray-mov;
	}
	template<typename T> const T* operator-(const XArray<T>& xArray,int mov)
	{
		return (const T*)xArray-mov;
	}
	template<typename T> T* operator+(int mov,XArray<T>& xArray)
	{
		return (T*)xArray+mov;
	}
	template<typename T> const T* operator+(int mov,const XArray<T>& xArray)
	{
		return (const T*)xArray+mov;
	}
	//��ϵ�����
	template<typename T> bool operator==(const XArray<T>& x1,const XArray<T>& x2)
	{
		if(x1.IsNull() && x2.IsNull())return true;
		if(x1.IsNull() || x2.IsNull())return false;
		if(x1.Length!=x2.Length)return false;
		const T* p1=x1;const pe1=p1+x1.Length;
		const T* p2=x2;
		while(p1!=pe1)if(*p1++!=*p2++)return false;
		return true;
	}
	template<typename T> bool operator!=(const XArray<T>& x1,const XArray<T>& x2)
	{
		if(x1.IsNull() && x2.IsNull())return false;
		if(x1.IsNull() || x2.IsNull())return true;
		if(x1.Length!=x2.Length)return true;
		const T* p1=x1;const pe1=p1+x1.Length;
		const T* p2=x2;
		while(p1!=pe1)if(*p1++!=*p2++)return true;
		return false;
	}
	template<typename T> bool operator>=(const XArray<T>& x1,const XArray<T>& x2)
	{
		if(x1.IsNull() && x2.IsNull())return true;
		if(x1.IsNull() || x2.IsNull())return x2.IsNull();
		const T* p1=x1;const pe1=p1+x1.Length;
		const T* p2=x2;const pe2=p2+x2.Length;
		while(p1!=pe1&& pe2!=pe2){if(*p1!=*p2)break;++p1;++p2;}
		if(p1==pe1)return p2==pe2;
		if(p2==pe2)return true;
		return *p1>=*p2;
	}
	template<typename T> bool operator<=(const XArray<T>& x1,const XArray<T>& x2)
	{
		if(x1.IsNull() && x2.IsNull())return true;
		if(x1.IsNull() || x2.IsNull())return x1.IsNull();
		const T* p1=x1;const pe1=p1+x1.Length;
		const T* p2=x2;const pe2=p2+x2.Length;
		while(p1!=pe1&& pe2!=pe2){if(*p1!=*p2)break;++p1;++p2;}
		if(p1==pe1)return p2!=pe2;
		if(p2==pe2)return false;
		return *p1<=*p2;
	}
	template<typename T> bool operator>(const XArray<T>& x1,const XArray<T>& x2)
	{
		if(x1.IsNull() && x2.IsNull())return false;
		if(x1.IsNull() || x2.IsNull())return x2.IsNull();
		const T* p1=x1;const pe1=p1+x1.Length;
		const T* p2=x2;const pe2=p2+x2.Length;
		while(p1!=pe1&& pe2!=pe2){if(*p1!=*p2)break;++p1;++p2;}
		if(p1==pe1)return false;
		if(p2==pe2)return true;
		return *p1>*p2;
	}
	template<typename T> bool operator<(const XArray<T>& x1,const XArray<T>& x2)
	{
		if(x1.IsNull() && x2.IsNull())return false;
		if(x1.IsNull() || x2.IsNull())return x1.IsNull();
		const T* p1=x1;const pe1=p1+x1.Length;
		const T* p2=x2;const pe2=p2+x2.Length;
		while(p1!=pe1&& pe2!=pe2){if(*p1!=*p2)break;++p1;++p2;}
		if(p1==pe1)return true;
		if(p2==pe2)return false;
		return *p1<*p2;
	}
	//��ȡ�������һ���֣������飩
	template<typename T>XArray<T> XArray<T>::SubArray(int startIndex,int length,XArrayType type)const
	{
		if(IsNull())throw XException(E_POINTER);
		if(length<0 || startIndex<0)throw XException(E_INVALIDARG);
		if(length+startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		return new VArray<T>(length,(const T*const&)*this+startIndex,type);
	}
	//������pdata��startIndexԪ������len��Ԫ���γ�T��ΪԪ�ص�����
	template<typename T>template<typename AnyT>XArray<T> XArray<T>::CopyFrom(const XArray<AnyT>&source)
	{
		if(source.Length==0)return new VArray<T>();
		T* p = VArray<T>::Malloc(source.Length);
		T* pt(p);
		T* end(p+source.Length);
		const AnyT* px(source);
		while(pt!=end)placementnew(pt++,*px++);
		return new VArray<T>(source.Length,p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>XArray<T> XArray<T>::CopyFrom(const XArray<AnyT>&source, int startIndex)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//������Ч
		if(startIndex>source.Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(source.Length==startIndex)return new VArray<T>();
		T* p = VArray<T>::Malloc(source.Length-startIndex);
		T* pt(p);
		T* end(p+source.Length-startIndex);
		const AnyT* px(source+startIndex);
		while(pt!=end)placementnew(pt++,*px++);
		return new VArray<T>(source.Length-startIndex,p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>XArray<T> XArray<T>::CopyFrom(const XArray<AnyT>&source, int startIndex,int length)
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);//������Ч
		if(startIndex + length>source.Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(!length)return new VArray<T>();
		T* p = VArray<T>::Malloc(length);
		T* pt(p);
		T* end(p+length);
		const AnyT* px(source+startIndex);
		while(pt!=end)placementnew(pt++,*px++);
		return new VArray<T>(length,p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>XArray<T> XArray<T>::CopyFrom(const Iterator<const T>&first,const Iterator<const T>&end)
	{
		int length = end-first;
		if(length==0)return new VArray<T>();
		T* p = VArray<T>::Malloc(length);
		T* pt(p);
		T* end(p+length);
		Iterator<const T> px(first);
		while(pt!=end)placementnew(pt++,*px++);
		return new VArray<T>(length,p,SelfConstruct);
	}
	//������pdata��startByte�ֽڴ�����len���ֽ��γ�����
	template<typename T>template<typename AnyT>XArray<T> XArray<T>::CopyFromByBytes(const XArray<AnyT>&source)
	{
		if(source.Length==0)return new VArray<T>();
		T* p = VArray<T>::Malloc(((sizeof(AnyT)*source.Length)%sizeof(T))?sizeof(AnyT)*source.Length/sizeof(T)+1:sizeof(AnyT)*source.Length/sizeof(T));
		XBase::Memory::Copy(p,(const AnyT*)source,source.GetLengthOfBytes());
		return new VArray<T>((source.GetLengthOfBytes()%sizeof(T))?source.GetLengthOfBytes()/sizeof(T)+1:source.GetLengthOfBytes()/sizeof(T),p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>XArray<T> XArray<T>::CopyFromByBytes(const XArray<AnyT>&source, int startByte)
	{
		if(startByte<0)throw XException(E_INVALIDARG);//������Ч
		if(startByte>source.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);//������Ч
		if(startByte==source.GetLengthOfBytes())return new VArray<T>();
		T* p = VArray<T>::Malloc(((source.GetLengthOfBytes()-startByte)%sizeof(T))?(source.GetLengthOfBytes()-startByte)/sizeof(T)+1:(source.GetLengthOfBytes()-startByte)/sizeof(T));
		XBase::Memory::Copy(p,(const AnyT*)source,sizeof(AnyT)*source.Length-startByte);
		return new VArray<T>(((source.GetLengthOfBytes()-startByte)%sizeof(T))?(source.GetLengthOfBytes()-startByte)/sizeof(T)+1:(source.GetLengthOfBytes()-startByte)/sizeof(T),p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>XArray<T> XArray<T>::CopyFromByBytes(const XArray<AnyT>&source, int startByte,int lengthOfBytes)
	{
		if(startByte<0 || lengthOfBytes<0)throw XException(E_INVALIDARG);//������Ч
		if(startByte+lengthOfBytes>source.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);//������Ч
		if(!lengthOfBytes)return new VArray<T>();
		T* p = VArray<T>::Malloc((lengthOfBytes%sizeof(T))?lengthOfBytes/sizeof(T)+1:lengthOfBytes/sizeof(T));
		XBase::Memory::Copy(p,source,lengthOfBytes);
		return new VArray<T>((lengthOfBytes%sizeof(T))?lengthOfBytes/sizeof(T)+1:lengthOfBytes/sizeof(T),p,SelfConstruct);
	}
	//������������ݸ���һ���ֵ���һ������
	template<typename T>template<typename AnyT>int XArray<T>::CopyTo(XArray<AnyT>& destination,int sourceIndex, int destinationIndex)const
	{
		if(sourceIndex<0 || destinationIndex<0)throw XException(E_INVALIDARG);//������Ч
		if(sourceIndex>Length  || destinationIndex>destination.Length)throw XException(COR_E_INDEXOUTOFRANGE);
		int length = (Length-sourceIndex > destination.Length-destinationIndex)?destination.Length-destinationIndex:Length-sourceIndex;
		const T* p = *this+sourceIndex;
		T* pEnd = p+length;
		AnyT* pd = destination+destinationIndex;
		while(p<pEnd){*pd = *p;++p;++pd;}//ǿ��ת��
		return length;
	}
	template<typename T>template<typename AnyT>int XArray<T>::CopyTo(XArray<AnyT>& destination,int sourceIndex, int destinationIndex, int length)const
	{
		if(sourceIndex<0 || destinationIndex<0 || length<0)throw XException(E_INVALIDARG);//������Ч
		if(sourceIndex+length>Length  || destinationIndex+length>destination.Length)throw XException(COR_E_INDEXOUTOFRANGE);
		const T* p = *this+sourceIndex;
		const T* pEnd = p+length;
		AnyT* pd = destination+destinationIndex;
		while(p<pEnd){*pd = *p;++p;++pd;}//ǿ��ת��
		return length;
	}
	//������һ�����͵����鸴��һ�����ֽ���
	template<typename T>template<typename AnyT>int XArray<T>::CopyToByBytes(XArray<AnyT>& dest, int sourceByte, int destinationByte)const
	{
		if(sourceByte<0 || destinationByte<0)throw XException(E_INVALIDARG);//������Ч
		if(sourceByte>GetLengthOfBytes() || destinationByte>dest.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);
		int lengthOfByte =  (GetLengthOfBytes()-sourceByte > dest.GetLengthOfBytes()-destinationByte)?dest.GetLengthOfBytes()-destinationByte:GetLengthOfBytes()-sourceByte;
		XBase::Memory::Copy(((unsigned char*)(AnyT*)dest)+destinationByte,((unsigned char*)pData)+sourceByte,lengthOfByte);
		return lengthOfByte;
	}
	template<typename T>template<typename AnyT>int XArray<T>::CopyToByBytes(XArray<AnyT>& dest, int sourceByte, int destinationByte, int lengthOfByte)const
	{
		if(sourceByte<0 || destinationByte<0 || lengthOfByte<0)throw XException(E_INVALIDARG);//������Ч
		if(sourceByte + lengthOfByte>GetLengthOfBytes() || lengthOfByte+destinationByte>dest.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);
		XBase::Memory::Copy(((unsigned char*)(AnyT*)dest)+destinationByte,((unsigned char*)pData)+sourceByte,lengthOfByte);
		return lengthOfByte;
	}
	//��������һϵ��Ԫ�ص�ֵ����Ϊt
	template<typename T>template<typename AnyT>void XArray<T>::ResetTo(const AnyT& t)
	{
		return Pointer()->ResetTo(t);
	}
	template<typename T>template<typename AnyT>void XArray<T>::ResetTo(const AnyT& t, int index, int length)
	{
		return Pointer()->ResetTo(t,index,length);
	}
	//�������ĳ��λ�ò���Ԫ�ػ�����
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::Insert(int index,const AnyT&t)
	{
		return Pointer()->Insert(index,t);
	}
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::Insert(const Iterator<T>&it,const AnyT&t)
	{
		if(it.GetLength()!=Length)throw XException(L"ָ���ĵ������Ѿ�ʧЧ",E_INVALIDARG);
		return Insert(it-(T*)*this,t);
	}
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::InsertArray(int index,const XArray<AnyT>&xArray)
	{
		if(xArray.IsNull())throw XException(E_POINTER);
		return Pointer()->InsertArray(index,*reinterpret_cast<VArray<AnyT>*const&>(reinterpret_cast<XArray<T>*>(&xArray)->pObject));
	}
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::InsertArray(const Iterator<T>&it,const XArray<AnyT>&xArray)
	{
		if(it.GetLength()!=Length || it.GetFirstElementPointer()!=(T*)*this)throw XException(L"ָ���ĵ������Ѿ�ʧЧ",E_INVALIDARG);
		return InsertArray(it-(T*)*this,xArray);
	}
	//�������β���Ԫ�ػ�����
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::Append(const AnyT&t)
	{
		return Pointer()->Append(t);
	}
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::AppendArray(const XArray<AnyT>& rArray)
	{
		if(rArray.IsNull())throw XException(E_POINTER);
		return Pointer()->AppendArray(*reinterpret_cast<VArray<AnyT>*const&>(reinterpret_cast<XArray<T>*>(&rArray)->pObject));
	}
	//��������ɾ��ָ�������Ԫ�أ�startIndexΪ��ʼ�Ƴ�����λ�ã�ֱ��ĩβ
	template<typename T>Iterator<T> XArray<T>::Remove(int startIndex)
	{
		return Pointer()->Remove(startIndex);
	}
	//��������ɾ��ָ��λ�õ�Ԫ�أ�indexΪ��ʼ�Ƴ�λ������
	template<typename T>Iterator<T> XArray<T>::RemoveAt(int index)
	{
		return Pointer()->RemoveAt(index);
	}
	//��������ɾ��ָ�������Ԫ�أ�startIndexΪ��ʼ�Ƴ�����λ�ã�lengthΪҪ�Ƴ���Ԫ����
	template<typename T>Iterator<T> XArray<T>::Remove(int startIndex,int length)
	{
		return Pointer()->Remove(startIndex,length);
	}
	//��������ɾ��ָ�������Ԫ�أ�startIndexΪ��ʼ�Ƴ�����λ�ã�lengthΪҪ�Ƴ���Ԫ����
	template<typename T>Iterator<T> XArray<T>::Remove(const Iterator<T>& firstIterator,const Iterator<T>& endIterator)
	{
		return Pointer()->Remove(firstIterator,endIterator);
	}
	//�Ƴ�����ָ�������е�һ����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ�Ƴ������ԭԪ��λ��
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveOneOf(const AnyT&t,int startIndex)
	{
		return Pointer()->RemoveOneOf(t,startIndex);
	}
	//�Ƴ�����ָ�������е�һ����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ���lengthΪԪ���������صĵ�����Ϊ�Ƴ������ԭԪ��λ��
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveOneOf(const AnyT&t,int startIndex,int length)
	{
		return Pointer()->RemoveOneOf(t,startIndex,length);
	}
	//�Ƴ�����ָ�������е�һ����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ�Ƴ������ԭԪ��λ��
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveOneOf(const AnyT&t,const Iterator<T>&start ,const Iterator<T>&end)
	{
		return Pointer()->RemoveOneOf(t,start,end);
	}
	//�Ƴ�����ָ�������г��ֵ�������ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveAllOf(const AnyT&t,int startIndex)
	{
		return Pointer()->RemoveAllOf(t,startIndex);
	}
	//�Ƴ�����ָ�������г��ֵ�������ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveAllOf(const AnyT&t,int startIndex,int length)
	{
		return Pointer()->RemoveAllOf(t,startIndex,length);
	}
	//�Ƴ�����ָ�������г��ֵ�������ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveAllOf(const AnyT&t,const Iterator<T>&start ,const Iterator<T>&end)
	{
		return Pointer()->RemoveAllOf(t,start,end);
	}
	//�Ƴ�����ָ�������г��ֵ����count����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveSomeOf(const AnyT&t,int startIndex,int length,int count)
	{
		return Pointer()->RemoveSomeOf(t,startIndex,length,count);
	}
	//�Ƴ�����ָ�������г��ֵ����count����ָ��ֵ��ȵ�Ԫ�أ�ʹ��==���бȽϣ������صĵ�����Ϊ���һ���Ƴ������ԭԪ��λ��
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveSomeOf(const AnyT&t,const Iterator<T>&first ,const Iterator<T>&end,int count)
	{
		return Pointer()->RemoveSomeOf(t,first,end,count);
	}
	//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ��
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex)
	{
		return Pointer()->ReplaceOneOf(t,to,startIndex);
	}
	//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ��
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex,int length)
	{
		return Pointer()->ReplaceOneOf(t,to,startIndex,length);
	}
	//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ�أ����صĵ�����Ϊ���һ���滻λ��
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceOneOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end)
	{
		return Pointer()->ReplaceOneOf(t,to,start,end);
	}
	//�滻������������t��ȵ�Ԫ��Ϊ��һ��Ԫ��
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex)
	{
		return Pointer()->ReplaceAllOf(t,to,startIndex);
	}
	//�滻������������t��ȵ�Ԫ��Ϊ��һ��Ԫ��
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex,int length)
	{
		return Pointer()->ReplaceAllOf(t,to,startIndex,length);
	}
	//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ�أ����صĵ�����Ϊ���һ���滻λ��
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceAllOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end)
	{
		return Pointer()->ReplaceAllOf(t,to,start,end);
	}
	//�滻������ĳЩԪ��Ϊ��һ��Ԫ��
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceSomeOf(const AnyT1& t, const AnyT2& to,int startIndex,int length,int count)
	{
		return Pointer()->ReplaceSomeOf(t,to,startIndex,length,count);
	}
	//�滻������ĳ��Ԫ��Ϊ��һ��Ԫ�أ����صĵ�����Ϊ���һ���滻λ��
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceSomeOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end,int count)
	{
		return Pointer()->ReplaceSomeOf(t,to,start,end,count);
	}
	//������С��������������
	template<typename T>int XArray<T>::Resize( int count)
	{
		return Pointer()->Resize(count);
	}
	//������С����һ���������ݣ���Resize�������һ�����ƵĹ���
	template<typename T>int XArray<T>::ResizeAndDestroy( int count)
	{
		return Pointer()->ResizeAndDestroy(count);
	}
	//������ָ��ֵ��ȵĵ�һ��Ԫ�أ��Ҳ����򷵻�-1
	template<typename T>template<typename AnyT>int XArray<T>::IndexOf(const AnyT&t, int startIndex)const
	{
		return Pointer()->IndexOf(t,startIndex);
	}
	//��ָ�����������ָ��ֵ��ȵĵ�һ��Ԫ�أ��Ҳ����򷵻�-1
	template<typename T>template<typename AnyT>int XArray<T>::IndexOf(const AnyT&t, int startIndex,int length)const
	{
		return Pointer()->IndexOf(t,startIndex,length);
	}
	//���õ�����ָ�������������ָ��ֵ��ȵĵ�һ��Ԫ�أ��Ҳ����򷵻�-1
	template<typename T>template<typename AnyT>int XArray<T>::IndexOf(const AnyT&t, const Iterator<const T>& start,const Iterator<const T>& end)const
	{
		return Pointer()->IndexOf(t,start,end);
	}
	//������ָ��ֵ��ȵ����һ��Ԫ�أ��Ҳ����򷵻�-1
	template<typename T>template<typename AnyT>int XArray<T>::LastIndexOf(const AnyT&t,int startIndex)const
	{
		return Pointer()->LastIndexOf(t,startIndex);
	}
	//��ָ�����������ָ��ֵ��ȵ����һ��Ԫ�أ��Ҳ����򷵻�-1
	template<typename T>template<typename AnyT>int XArray<T>::LastIndexOf(const AnyT&t,int startIndex,int length)const
	{
		return Pointer()->LastIndexOf(t,startIndex,length);
	}
	//���õ�����ָ�������������ָ��ֵ��ȵ����һ��Ԫ�أ��Ҳ����򷵻�-1
	template<typename T>template<typename AnyT>int XArray<T>::LastIndexOf(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const
	{
		return Pointer()->LastIndexOf(t,start,end);
	}
	//����ָ��Ԫ�ص�λ�ã��Ҳ�������end
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::Find(const AnyT&t,int startIndex)const
	{
		return Pointer()->Find(t,startIndex);
	}
	//��ָ���������ָ��Ԫ�ص�λ�ã��Ҳ�������end
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::Find(const AnyT&t,int startIndex,int length)const
	{
		return Pointer()->Find(t,startIndex,length);
	}
	//���õ�����ָ�����������ָ��Ԫ�ص�λ�ã��Ҳ�������end
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::Find(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const
	{
		return Pointer()->Find(t,start,end);
	}
	//������ָ��������ȵ�Ԫ����
	template<typename T>template<class AnyT>int XArray<T>::CountOf(const AnyT&t,int startIndex)const
	{
		return Pointer()->CountOf(t,startIndex);
	}
	//��ָ�����������ָ��������ȵ�Ԫ����
	template<typename T>template<class AnyT>int XArray<T>::CountOf(const AnyT&t,int startIndex,int length)const
	{
		return Pointer()->CountOf(t,startIndex,length);
	}
	//���õ�����ָ�������������ָ��������ȵ�Ԫ����
	template<typename T>template<class AnyT>int XArray<T>::CountOf(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const
	{
		return Pointer()->CountOf(t,start,end);
	}
	//��ȡ��һ��Ԫ�ص�����
	template<typename T>T& XArray<T>::FirstElement()
	{
		return Pointer()->FirstElement();
	}
	template<typename T>const T& XArray<T>::FirstElement()const
	{
		return Pointer()->FirstElement();
	}
	//��ȡ���һ��Ԫ�ص�����
	template<typename T>T& XArray<T>::LastElement()
	{
		return Pointer()->LastElement();
	}
	template<typename T>const T& XArray<T>::LastElement()const
	{
		return Pointer()->LastElement();
	}
	//��ȡ��������
	template<typename T>XArrayType XArray<T>::GetArrayType()const
	{
		return Pointer()->GetArrayType();
	}
	//��ȡǳ����
	template<typename T>XArray<T> XArray<T>::MakeCopy()const
	{
		XArray<T> tmp(*this);
		if(tmp.IsNull())return XArray<T>();
		VArray<T>* p = new VArray<T>(*reinterpret_cast<VArray<T>*&>(tmp.pObject));
		tmp=p;
		return tmp;
	}

}
#endif