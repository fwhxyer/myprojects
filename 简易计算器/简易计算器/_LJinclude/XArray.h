#ifndef XARRAY_
#define XARRAY_
namespace LJ
{
	template<typename T,typename AnyT>void VArrayCopyConstructMethod(AnyT*source,T* pDestination,unsigned long size)
	{
		T* pEnd = pDestination+size;
		while(pDestination!=pEnd){placementnew(pDestination++,*source++);}//构造
	}
	//默认构造方法
	template<typename T>void VArrayDefaultConstructMethod(T* pDestination,unsigned long size)
	{
		T* pEnd = pDestination+size;
		while(pDestination!=pEnd)placementnew(pDestination++);//默认构造
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
	//析构方法
	template<typename T>void VArrayDeconstructMethod(T* pDestination,unsigned long size)
	{
		T* pEnd = pDestination+size;
		while(pDestination!=pEnd)(pDestination++)->T::~T();//析构
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
	//赋值构造方法
	template<typename T>void VArrayConstructMethod(const T& source,T* pDestination,unsigned long size)
	{
		T* pEnd = pDestination+size;
		while(pDestination!=pEnd)placementnew(pDestination++,source);//复制构造
	}
	//复制方法
	template<typename T>void VArrayCopyMethod(const T* pSource, T* pDestination, unsigned long size)
	{
		T* pEnd = pDestination+size;
		while(pDestination!=pEnd)*pDestination++=*pSource++;
	}
	template<typename T>void VArrayCopyMethod(T*const * pSource,T** pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,sizeof(T*)*size);
	}

	void VArrayCopyMethod(const char*, char*, unsigned long );//特殊化
	void VArrayCopyMethod(const short*, short*, unsigned long );//特殊化
	void VArrayCopyMethod(const long*, long*, unsigned long );//特殊化
	void VArrayCopyMethod(const int*, int*, unsigned long );//特殊化
	void VArrayCopyMethod(const long long*, long long*, unsigned long );//特殊化
	void VArrayCopyMethod(const unsigned char*, unsigned char*, unsigned long );//特殊化
	void VArrayCopyMethod(const unsigned short*, unsigned short*, unsigned long );//特殊化
	void VArrayCopyMethod(const unsigned long*, unsigned long*, unsigned long );//特殊化
	void VArrayCopyMethod(const unsigned int*, unsigned int*, unsigned long );//特殊化
	void VArrayCopyMethod(const unsigned long long*, unsigned long long*, unsigned long );//特殊化
	void VArrayCopyMethod(const WCHAR*, WCHAR*, unsigned long );//特殊化
	enum XArrayType:signed char
	{
		Normal = 0,//正常类型，通过delete删除
		Reference = 1,//引用类型，不需要进行删除
		SelfConstruct =2//自构造类型，内部调用析构函数
	};
	template<typename T>struct IArrayIterator;
	template<typename T>class VArray:public XBase//仅1维数组
	{
	protected:
		//具体数据
		T *pData;
		//当前最大元素数
		int maxSize;
		//数组类型(决定内存管理方式)
		XArrayType type;
	public:
		PROPERTY_OFFSET(VArray,Length);
		XBaseVTypeMethods_H(VArray);
		//交换
		virtual void SwapWith(XBase& x)
		{
			VArray* p=dynamic_cast<VArray*>(&x);
			if(p==NULL)throw XException(L"引用为空或非法",E_POINTER);
			SwapWith(*p);
		}
		//与另一个实体数组交换
		void  SwapWith(VArray& v)
		{
			T*p = pData;pData = v.pData;v.pData=p;
			int len = Length;const_cast<int&>(Length) = v.Length;const_cast<int&>(v.Length)=len;
			len = MinDecrease;MinDecrease = v.MinDecrease;v.MinDecrease=len;
		}
		//内存分配
		static T* Malloc(int count);
		//元素数减小时，元素数变化超过此值才重新申请空间
		int MinDecrease;
		//默认的最小减小变化值
		static int MinDecreaseDefault;
		//获取数组按字节计算的长度
		int GetLengthOfBytes()const;
		union
		{
			//当前元素数
			const int Length;
			//只读字节长度属性
			PROPERTY_GET(int,VArray,GetLengthOfBytes,LengthOfBytes);
		};
		//虚析构函数，释放数据
		virtual ~VArray();
		//默认构造函数，构造一个空数组
		VArray();
		//传入数组长度，构造一个未初始化的数组，得到的
		VArray(int);
		//复制构造函数，复制除了type之外的数据
		VArray(const VArray&);
		//从引用类型数组构造，复制除了type之外的数据
		VArray(const XArray<T>&);
		//传入数组长度，并使用一个参考元素来初始化所有元素
		VArray(int,const T&);
		//使用迭代器构造
		template<class AnyT>VArray(const Iterator<AnyT>&first,const Iterator<AnyT>&end);
		//直接传入指针和元素数,如果type设置为Normal，则p必须指向用new分配的空间,并交由该对象执行delete, 如果p为NULL或则不进行初始化,如果type设置为Reference则该对象将不执行删除
		explicit VArray(int,typename Types<T>::Normal*,XArrayType type=Normal);
		//直接传入指针和元素数,如果type设置为Normal，则p必须指向用new分配的空间,并交由该对象执行delete, 如果p为NULL或则不进行初始化,如果type设置为Reference则该对象将不执行删除
		explicit VArray(int,typename Types<T>::Normal const*,XArrayType type=Reference);
		//直接转换成指针形式
		operator const T*const& ()const;
		//转换成指针形式
		operator T*const &();
		//迭代器，位置定位到第一个元素
		Iterator<T> First();
		//迭代器，位置定位到第一个元素
		Iterator<const T> First()const;
		//迭代器，位置定位到第一个元素,同First()
		Iterator<T> begin(){return First();}
		//迭代器，位置定位到第一个元素,同First()
		Iterator<const T> begin()const{return First();}
		//迭代器，位置定位到最后一个元素
		Iterator<T> Last();
		//迭代器，位置定位到最后一个元素
		Iterator<const T> Last()const;
		//迭代器，位置定位到末尾
		Iterator<T> End();
		//迭代器，位置定位到末尾
		Iterator<const T> End()const;
		//迭代器，位置定位到末尾,同End();
		Iterator<T> end(){return End();}
		//迭代器，位置定位到末尾,同End();
		Iterator<const T> end()const{return End();}
		//复制一个数组的数据，该数组原来数据的将被丢弃
		VArray& operator=(const VArray&);
		//获取该数组的一部分（子数组）
		VArray SubArray(int,int,XArrayType type=SelfConstruct)const;
		//从任意类型数据pdata复制所有元素形成T作为元素的数组
		template<typename AnyT>static VArray<T> CopyFrom(const VArray<AnyT>&);
		//从任意类型数据pdata的startIndex索引对应的元素起复制到数组结尾，形成T作为元素的数组
		template<typename AnyT>static VArray<T> CopyFrom(const VArray<AnyT>&,int startIndex);
		//从数据pdata的startIndex元素起复制length个元素形成T作为元素的数组
		template<typename AnyT>static VArray<T> CopyFrom(const VArray<AnyT>&,int startIndex, int length);
		//从任意类型迭代器形成T类型元素的数组
		template<typename AnyT>static VArray<T> CopyFrom(const Iterator<const T>&first,const Iterator<const T>&end);
		//从数据pdata按字节复制所有内容形成数组，如果内容非整则生成的数组可能会有部分内容未初始化
		template<typename AnyT>static VArray<T> CopyFromByBytes(const VArray<AnyT>&pdata);
		//从数据pdata的startByte字节处起按字节复制到结尾形成新数组，如果内容非整则生成的数组可能会有部分内容未初始化
		template<typename AnyT>static VArray<T> CopyFromByBytes(const VArray<AnyT>&pdata,int startByte);
		//从数据pdata的startByte字节处复制length个字节形成数组，如果内容非整则生成的数组可能会有部分内容未初始化
		template<typename AnyT>static VArray<T> CopyFromByBytes(const VArray<AnyT>&pdata,int startByte,int length);
		//将该数组的内容复制一部分到另一个数组，返回实际复制的元素数
		template<typename AnyT>int CopyTo(VArray<AnyT>& pdata,int startIndex=0,int destinationStartIndex=0)const;
		//将该数组的内容复制一部分到另一个数组，返回实际复制的元素数
		template<typename AnyT>int CopyTo(VArray<AnyT>& pdata,int startIndex,int destinationStartIndex,int length)const;
		//向任意一种类型的数组复制一定的字节数
		template<typename AnyT>int CopyToByBytes(VArray<AnyT>& pdata,int startByte=0,int destinationStartByte=0)const;
		//向任意一种类型的数组复制一定的字节数
		template<typename AnyT>int CopyToByBytes(VArray<AnyT>& pdata,int startByte,int destinationStartByte,int lengthOfBytes)const;
		//将数组中一系列元素的值设置为t
		template<typename AnyT>void ResetTo(const AnyT& t);
		//将数组中一系列元素的值设置为t
		template<typename AnyT>void ResetTo(const AnyT& t, int index, int length);
		//在数组的某个用索引指定的位置插入元素
		template<typename AnyT>Iterator<T> Insert(int index,const AnyT&t);
		//在数组的某个用迭代器指定的位置插入元素
		template<typename AnyT>Iterator<T> Insert(const Iterator<T>& it,const AnyT&t);
		//在数组的某个用索引指定的位置插入数组
		template<typename AnyT>Iterator<T> InsertArray(int index,const VArray<AnyT>&xArray);
		//在数组的某个用迭代器指定的位置插入数组
		template<typename AnyT>Iterator<T> InsertArray(const Iterator<T>& it,const VArray<AnyT>&xArray);
		//在数组结尾添加元素
		template<typename AnyT>Iterator<T> Append(const AnyT&t);
		//在数组结尾添加数组
		template<typename AnyT>Iterator<T> AppendArray(const VArray<AnyT>&xArray);
		//在数组中删除指定区域的元素，startIndex为起始移除索引位置，从startIndex到末尾的数据都将移除
		Iterator<T> Remove(int startIndex);
		//在数组中删除指定位置的元素，index为移除索引位置
		Iterator<T> RemoveAt(int index);
		//在数组中删除指定区域的元素，startIndex为起始移除索引位置，length为要移除的元素数
		Iterator<T> Remove(int startIndex,int length);
		//在数组中删除指定区域的元素，startIndex为起始移除索引位置，length为要移除的元素数
		Iterator<T> Remove(const Iterator<T>& firstIterator,const Iterator<T>& endIterator);
		//移除数组指定区域中第一个与指定值相等的元素（使用==进行比较），返回的迭代器为移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveOneOf(const AnyT&,int startIndex=0);
		//移除数组指定区域中第一个与指定值相等的元素（使用==进行比较），length为元素数，返回的迭代器为移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveOneOf(const AnyT&,int startIndex,int length);
		//移除数组指定区域中第一个与指定值相等的元素（使用==进行比较），返回的迭代器为移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveOneOf(const AnyT&,const Iterator<T>&start ,const Iterator<T>&end);
		//移除数组指定区域中出现的所有与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveAllOf(const AnyT&,int startIndex=0);
		//移除数组指定区域中出现的所有与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveAllOf(const AnyT&,int startIndex,int length);
		//移除数组指定区域中出现的所有与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveAllOf(const AnyT&,const Iterator<T>&start ,const Iterator<T>&end);
		//移除数组指定区域中出现的最多count个与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveSomeOf(const AnyT&,int startIndex,int length,int count);
		//移除数组指定区域中出现的最多count个与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveSomeOf(const AnyT&,const Iterator<T>&first ,const Iterator<T>&end,int count);
		//替换数组中某个元素为另一个元素
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex=0);
		//替换数组中某个元素为另一个元素
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex,int length);
		//替换数组中某个元素为另一个元素，返回的迭代器为最后一个替换位置
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceOneOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end);
		//替换数组中所有与t相等的元素为另一个元素
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex=0);
		//替换数组中所有与t相等的元素为另一个元素
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex,int length);
		//替换数组中某个元素为另一个元素，返回的迭代器为最后一个替换位置
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceAllOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end);
		//替换数组中某些元素为另一个元素
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceSomeOf(const AnyT1& t, const AnyT2& to,int startIndex,int length,int count);
		//替换数组中某个元素为另一个元素，返回的迭代器为最后一个替换位置
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceSomeOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end,int count);
		//随机乱序排列,startIndex和length分别表示起始下标和打乱内容长度
		void SortRandom(int startIndex,int length);
		//随机乱序排列
		void SortRandom(int startIndex=0);
		//调整大小并尽量保存数据,返回实际占用的最大空间
		int Resize( int);
		//调整大小并不一定保存数据，与Resize相比少了一个复制的过程
		int ResizeAndDestroy( int);
		//查找与指定值相等的第一个元素，找不到则返回-1
		template<typename AnyT>int IndexOf(const AnyT&t, int startIndex=0)const;
		//在指定区域查找与指定值相等的第一个元素，找不到则返回-1
		template<typename AnyT>int IndexOf(const AnyT&t, int startIndex,int length)const;
		//在用迭代器指定的区域查找与指定值相等的第一个元素，找不到则返回-1
		template<typename AnyT>int IndexOf(const AnyT&t, const Iterator<const T>& start,const Iterator<const T>& end)const;
		//查找与指定值相等的最后一个元素，找不到则返回-1
		template<typename AnyT>int LastIndexOf(const AnyT&t,int startIndex=0)const;
		//在指定区域查找与指定值相等的最后一个元素，找不到则返回-1
		template<typename AnyT>int LastIndexOf(const AnyT&t,int startIndex,int length)const;
		//在用迭代器指定的区域查找与指定值相等的最后一个元素，找不到则返回-1
		template<typename AnyT>int LastIndexOf(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const;
		//查找指定元素的位置，找不到返回end
		template<typename AnyT>Iterator<T> Find(const AnyT&t,int startIndex=0)const;
		//在指定区域查找指定元素的位置，找不到返回end
		template<typename AnyT>Iterator<T> Find(const AnyT&t,int startIndex,int length)const;
		//在用迭代器指定的区域查找指定元素的位置，找不到返回end
		template<typename AnyT>Iterator<T> Find(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const;
		//查找与指定变量相等的元素数
		template<class AnyT>int CountOf(const AnyT&t,int startIndex=0)const;
		//在指定区域查找与指定变量相等的元素数
		template<class AnyT>int CountOf(const AnyT&t,int startIndex,int length)const;
		//在用迭代器指定的区域查找与指定变量相等的元素数
		template<class AnyT>int CountOf(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const;
		//获取最后一个元素的引用
		T& LastElement();
		//获取最后一个元素的引用
		const T& LastElement()const;
		//获取第一个元素的引用
		T& FirstElement();
		//获取第一个元素的引用
		const T& FirstElement()const;
		//获取数组数据保存方式，有普通、引用、自构造
		XArrayType GetArrayType()const {return type;}
	};

	template<typename T>class XArray:public XBase
	{
	public:
		PROPERTY_OFFSET(XArray,Length);
		//通用基类方法
		XBaseRTypeMethods_H(XArray,VArray<T>);
		static inline int GetMinDecreaseDefault(){return VArray<T>::MinDecreaseDefault;}
		static inline void SetMinDecreaseDefault(int v){VArray<T>::MinDecreaseDefault = v;}
		//读写属性默认的最小减小变化值（间接修改VArray::MinDecreaseDefault）
		static StaticProperty<int> MinDecreaseDefault;
		//由实型数组构造
		XArray(const VArray<T>& v)
			:XBase(new VArray<T>(v)){}
		//传入数组长度，构造一个未初始化的数组
		XArray(int length):XBase(new VArray<T>(length)){		}
		//传入数组长度，并使用一个参考元素来初始化所有元素
		XArray(int length,const T& t):XBase(new VArray<T>(length,t)){		}
		//使用迭代器构造
		template<class AnyT>XArray(const Iterator<AnyT>&first,const Iterator<AnyT>&end):XBase(new VArray<T>(first,end)){	}
		//直接传入指针和元素数,对于type=Normal，p必须是使用new分配的空间,并交由该对象执行delete, 如果p为NULL或则不进行初始化,对于type=Reference则该对象将不执行删除
		explicit XArray(int length,typename Types<T>::Normal* p,XArrayType type=Normal):XBase(new VArray<T>(length,p,type)){		}
		//直接传入指针和元素数,对于type=Normal，p必须是使用new分配的空间,并交由该对象执行delete, 如果p为NULL或则不进行初始化,对于type=Reference则该对象将不执行删除
		explicit XArray(int length,typename Types<T>::Normal const* p,XArrayType type=Reference):XBase(new VArray<T>(length,p,type)){}
		//获取数组的元素数
		int GetLength()const;
		//获取数组按字节计算的长度
		int GetLengthOfBytes()const;
		//获取最小重申空间变化值
		int GetMinDecrease()const;
		//设置最小重申空间变化值
		void SetMinDecrease(int);
		union
		{
			//只读长度属性：数组的元素数
			PROPERTY_GET(int,XArray,GetLength,Length);
			//只读属性：数组的字节长度
			PROPERTY_GET(int,XArray,GetLengthOfBytes,LengthOfBytes);
			//读写属性：最小重申空间变化值
			PROPERTY_GETSET(int,XArray,GetMinDecrease,SetMinDecrease,MinDecrease);
		};
		//直接转换成指针形式
		operator const T*const&()const;
		operator T*const &();
		T&operator[](int index){if(IsNull())throw XException(E_POINTER);return ((T*const &)*this)[index];}
		const T&operator[](int index)const{if(IsNull())throw XException(E_POINTER);return ((const T*const &)*this)[index];}
		//迭代器，位置定位到第一个元素
		Iterator<T> First();
		//迭代器，位置定位到第一个元素
		Iterator<const T> First()const;
		//迭代器，位置定位到第一个元素,同First();
		Iterator<T> begin(){return First();}
		//迭代器，位置定位到第一个元素,同First();
		Iterator<const T> begin()const{return First();}
		//迭代器，位置定位到最后一个元素
		Iterator<T> Last();
		//迭代器，位置定位到最后一个元素
		Iterator<const T> Last()const;
		//迭代器，位置定位到末尾
		Iterator<T> End();
		//迭代器，位置定位到末尾
		Iterator<const T> End()const;
		//迭代器，位置定位到末尾,同End();
		Iterator<T> end(){return End();}
		//迭代器，位置定位到末尾,同End();
		Iterator<const T> end()const{return End();}
		//获取该数组的一部分（子数组）
		XArray SubArray(int startIndex,int length,XArrayType type=SelfConstruct)const;
		//从数据pdata复制所有元素形成T作为元素的数组
		template<typename AnyT>static XArray<T> CopyFrom(const XArray<AnyT>&);
		//从数据pdata的startIndex索引对应的元素起复制到数组结尾，形成T作为元素的数组
		template<typename AnyT>static XArray<T> CopyFrom(const XArray<AnyT>&,int startIndex);
		//从数据pdata的startIndex元素起复制length个元素形成T作为元素的数组
		template<typename AnyT>static XArray<T> CopyFrom(const XArray<AnyT>&,int startIndex, int length);
		//从迭代器指定的区域复制length个元素形成T作为元素的数组
		template<typename AnyT>static XArray<T> CopyFrom(const Iterator<const T>&first,const Iterator<const T>&end);
		//从数据pdata按字节复制所有内容形成数组，如果内容非整则生成的数组可能会有部分内容由0填充
		template<typename AnyT>static XArray<T> CopyFromByBytes(const XArray<AnyT>&pdata);
		//从数据pdata的startByte字节处起按字节复制到结尾形成新数组，如果内容非整则生成的数组可能会有部分内容由0填充
		template<typename AnyT>static XArray<T> CopyFromByBytes(const XArray<AnyT>&pdata,int startByte);
		//从数据pdata的startByte字节处复制length个字节形成数组，如果内容非整则生成的数组可能会有部分内容由0填充
		template<typename AnyT>static XArray<T> CopyFromByBytes(const XArray<AnyT>&pdata,int startByte,int length);
		//将该数组的内容复制一部分到另一个数组，返回实际复制的元素数
		template<typename AnyT>int CopyTo(XArray<AnyT>& pdata,int startIndex=0,int destinationStartIndex=0)const;
		//将该数组的内容复制一部分到另一个数组，返回实际复制的元素数
		template<typename AnyT>int CopyTo(XArray<AnyT>& pdata,int startIndex,int destinationStartIndex,int length)const;
		//向任意一种类型的数组复制一定的字节数
		template<typename AnyT>int CopyToByBytes(XArray<AnyT>& pdata,int startByte=0,int destinationStartByte=0)const;
		//向任意一种类型的数组复制一定的字节数
		template<typename AnyT>int CopyToByBytes(XArray<AnyT>& pdata,int startByte,int destinationStartByte,int lengthOfBytes)const;
		//将数组中一系列元素的值设置为t
		template<typename AnyT>void ResetTo(const AnyT& t);
		//将数组中一系列元素的值设置为t
		template<typename AnyT>void ResetTo(const AnyT& t, int index, int length);
		//在数组的某个用索引指定的位置插入元素
		template<typename AnyT>Iterator<T> Insert(int index,const AnyT&t);
		//在数组的某个用迭代器指定的位置插入元素
		template<typename AnyT>Iterator<T> Insert(const Iterator<T>& it,const AnyT&t);
		//在数组的某个用索引指定的位置插入数组
		template<typename AnyT>Iterator<T> InsertArray(int index,const XArray<AnyT>&xArray);
		//在数组的某个用迭代器指定的位置插入数组
		template<typename AnyT>Iterator<T> InsertArray(const Iterator<T>& it,const XArray<AnyT>&xArray);
		//在数组结尾添加元素
		template<typename AnyT>Iterator<T> Append(const AnyT&t);
		//在数组结尾添加数组
		template<typename AnyT>Iterator<T> AppendArray(const XArray<AnyT>&xArray);
		//在数组中删除指定区域的元素，startIndex为起始移除位置索引，从startIndex到末尾的数据都将被移除
		Iterator<T> Remove(int startIndex);
		//在数组中删除指定区域的元素，startIndex为起始移除索引位置，length为要移除的元素数
		Iterator<T> Remove(int startIndex,int length);
		//在数组中删除指定区域的元素，startIndex为起始移除索引位置，length为要移除的元素数
		Iterator<T> Remove(const Iterator<T>& firstIterator,const Iterator<T>& endIterator);
		//在数组中删除指定位置的元素，index为移除位置的索引，直到末尾
		Iterator<T> RemoveAt(int index);
		//移除数组指定区域中第一个与指定值相等的元素（使用==进行比较），返回的迭代器为移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveOneOf(const AnyT&,int startIndex=0);
		//移除数组指定区域中第一个与指定值相等的元素（使用==进行比较），length为元素数，返回的迭代器为移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveOneOf(const AnyT&,int startIndex,int length);
		//移除数组指定区域中第一个与指定值相等的元素（使用==进行比较），返回的迭代器为移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveOneOf(const AnyT&,const Iterator<T>&start ,const Iterator<T>&end);
		//移除数组指定区域中出现的所有与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveAllOf(const AnyT&,int startIndex=0);
		//移除数组指定区域中出现的所有与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveAllOf(const AnyT&,int startIndex,int length);
		//移除数组指定区域中出现的所有与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveAllOf(const AnyT&,const Iterator<T>&start ,const Iterator<T>&end);
		//移除数组指定区域中出现的最多count个与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveSomeOf(const AnyT&,int startIndex,int length,int count);
		//移除数组指定区域中出现的最多count个与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
		template<typename AnyT>Iterator<T> RemoveSomeOf(const AnyT&,const Iterator<T>&first ,const Iterator<T>&end,int count);
		//替换数组中某个元素为另一个元素
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex=0);
		//替换数组中某个元素为另一个元素
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex,int length);
		//替换数组中所有与指定元素相等的元素为另一个元素，返回的迭代器为最后一个替换位置
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceOneOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end);
		//替换数组中所有与t相等的元素为另一个元素
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex=0);
		//替换数组中所有与t相等的元素为另一个元素
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex,int length);
		//替换数组中某个元素为另一个元素，返回的迭代器为最后一个替换位置
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceAllOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end);
		//替换数组中某些元素为另一个元素
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceSomeOf(const AnyT1& t, const AnyT2& to,int startIndex,int length,int count);
		//替换数组中某个元素为另一个元素，返回的迭代器为最后一个替换位置
		template<typename AnyT1,typename AnyT2>Iterator<T> ReplaceSomeOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end,int count);
		//随机乱序排列,startIndex和length分别表示起始下标和打乱内容长度
		void SortRandom(int startIndex,int length){return Pointer()->SortRandom(startIndex,length);}
		//随机乱序排列
		void SortRandom(int startIndex=0){return Pointer()->SortRandom(startIndex);};
		//调整大小并尽量保存数据，返回实际占用的最大元素数，不是数据元素数
		int Resize( int);
		//调整大小并不一定保存数据，与Resize相比少了一个复制的过程
		int ResizeAndDestroy( int);
		//查找与指定值相等的第一个元素，找不到则返回-1
		template<typename AnyT>int IndexOf(const AnyT&t, int startIndex=0)const;
		//在指定区域查找与指定值相等的第一个元素，找不到则返回-1
		template<typename AnyT>int IndexOf(const AnyT&t, int startIndex,int length)const;
		//在用迭代器指定的区域查找与指定值相等的第一个元素，找不到则返回-1
		template<typename AnyT>int IndexOf(const AnyT&t, const Iterator<const T>& start,const Iterator<const T>& end)const;
		//查找与指定值相等的最后一个元素，找不到则返回-1
		template<typename AnyT>int LastIndexOf(const AnyT&t,int startIndex=0)const;
		//在指定区域查找与指定值相等的最后一个元素，找不到则返回-1
		template<typename AnyT>int LastIndexOf(const AnyT&t,int startIndex,int length)const;
		//在用迭代器指定的区域查找与指定值相等的最后一个元素，找不到则返回-1
		template<typename AnyT>int LastIndexOf(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const;
		//查找指定元素的位置，找不到返回end
		template<typename AnyT>Iterator<T> Find(const AnyT&t,int startIndex=0)const;
		//在指定区域查找指定元素的位置，找不到返回end
		template<typename AnyT>Iterator<T> Find(const AnyT&t,int startIndex,int length)const;
		//在用迭代器指定的区域查找指定元素的位置，找不到返回end
		template<typename AnyT>Iterator<T> Find(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const;
		//查找与指定变量相等的元素数
		template<class AnyT>int CountOf(const AnyT&t,int startIndex=0)const;
		//在指定区域查找与指定变量相等的元素数
		template<class AnyT>int CountOf(const AnyT&t,int startIndex,int length)const;
		//在用迭代器指定的区域查找与指定变量相等的元素数
		template<class AnyT>int CountOf(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const;
		//获取最后一个元素的引用
		T& LastElement();
		//获取最后一个元素的引用
		const T& LastElement()const;
		//获取第一个元素的引用
		T& FirstElement();
		//获取第一个元素的引用
		const T& FirstElement()const;
		//获取数组类型
		XArrayType GetArrayType()const;
		//获取浅表副本
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
		//遍历下一个元素
		virtual void Next(){++pCurrent;}
		//遍历上一个元素
		virtual void Fore(){--pCurrent;}
		//遍历下n个元素
		virtual void NextN(int n){pCurrent+=n;}
		//遍历上n个元素
		virtual void ForeN(int n){pCurrent-=n;}
		//相减
		virtual int Minus(IIterator*p){return int(pCurrent-reinterpret_cast<IArrayIterator*&>(p)->pCurrent);}
		//跳转到最后一个
		virtual bool ToLast(){pCurrent = pEnd==NULL?NULL:pEnd-1;return pFirst!=pEnd;}
		//跳转到终结位置
		virtual bool ToEnd(){pCurrent = pEnd;return pFirst!=pEnd;}
		//重置到开头
		virtual void Reset(){pCurrent = pFirst;}
		//产生一个副本
		virtual IIterator* NewCopy(){return new IArrayIterator<T>(pFirst,pCurrent,pEnd);}
		//获取当前的索引号
		virtual int GetCurrentIndex(){return int(pCurrent-pFirst);}
		//索引
		virtual T& Index(int index){return *(pCurrent+index);}
		//获取当前指针
		virtual T*Current(){return pCurrent;}
		//获取最后一个元素的指针
		virtual T*Last(){return pEnd==NULL?NULL:pEnd-1;}
		//获取第一个元素的指针
		virtual T*First(){return pFirst;}
		//获取终结元素的指针
		virtual T*End(){return pEnd;}
		//比较
		virtual int CompareWith(IIterator<T>*p)
		{
			if(pFirst!=reinterpret_cast<IArrayIterator<T>*&>(p)->pFirst)throw XException(L"所比较的迭代器不一致",E_INVALIDARG);
			return int(pCurrent-reinterpret_cast<IArrayIterator<T>*&>(p)->pCurrent);
		}
		//析构
		virtual ~IArrayIterator(){}
	};
	template<class T>int VArray<T>::MinDecreaseDefault = INT_MAX;//当设置为这个值时，数组减小大小时将不会重新申请内存
	template<class T>StaticProperty<int> XArray<T>::MinDecreaseDefault = StaticProperty<int>(XArray<T>::GetMinDecreaseDefault,XArray<T>::SetMinDecreaseDefault);//当设置为这个值时，数组减小大小时将不会重新申请内存

	template<typename T>T* VArray<T>::Malloc(int size)
	{
		if(!size)return NULL;
		void*p;
		if((p = malloc(sizeof(T)*(size_t)size))==NULL)
		{
			Sleep(30);//暂停一下再试
			if((p = malloc(sizeof(T)*(size_t)size))==NULL)
				throw XException(L"申请内存失败",E_OUTOFMEMORY);
		}
		return reinterpret_cast<T*&>(p);
	}
	//获取数组当前的字节数
	template<typename T>int VArray<T>::GetLengthOfBytes()const
	{
		return Length*sizeof(T);
	}
	//析构函数
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
	//默认构造函数，等同于VArray(0)
	template<typename T>VArray<T>::VArray()
		:pData(NULL),maxSize(0),MinDecrease(MinDecreaseDefault),Length(0),type(SelfConstruct)
	{    }
	//直接传入元素数量
	template<typename T>VArray<T>::VArray(int count)
		:pData(NULL),maxSize(0),MinDecrease(MinDecreaseDefault),Length(0),type(SelfConstruct)
	{
		if(count<0)throw XException(E_INVALIDARG);//count<0时参数无效
		if(count>0)
		{
			pData = Malloc(count);
			maxSize = const_cast<int&>(Length) = count;
			VArrayDefaultConstructMethod(pData,count);
		}
	}
	//复制构造函数
	template<typename T>VArray<T>::VArray(const VArray& xArray)
		:pData(NULL),maxSize(xArray.Length),MinDecrease(xArray.MinDecrease),Length(xArray.Length),type(SelfConstruct)
	{
		if(xArray.Length)
		{
			pData=Malloc(maxSize);
		}
		if(maxSize)VArrayCopyMethod(xArray.pData,pData,maxSize);
	}
	//从引用类型数组构造
	template<typename T>VArray<T>::VArray(const XArray<T>& xArray)
		:pData(NULL),maxSize(xArray.Length),MinDecrease(xArray.MinDecrease),Length(xArray.Length),type(SelfConstruct)
	{
		if(xArray.Length>0)
		{
			pData=Malloc(maxSize);
		}
		if(maxSize)VArrayCopyMethod((const T*)xArray,pData,maxSize);
	}
	//传入数组长度，并使用一个参考元素来初始化所有元素，type将被设置为Malloc
	template<typename T>VArray<T>::VArray(int count,const T& t)
		:pData(NULL),maxSize(count),MinDecrease(MinDecreaseDefault),Length(count),type(SelfConstruct)
	{
		if(count<0)throw XException(E_INVALIDARG);//count<0时参数无效
		if(count!=0)
		{
			pData=Malloc(count);
			VArrayConstructMethod(t,pData,count);
		}
	}
	//使用迭代器构造
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
	//直接传入指针和元素数量来构造数组,p为NULL时创建count个元素的数组,type指定对p指向内存的管理方式
	template<typename T>VArray<T>::VArray(int count,typename Types<T>::Normal* p,XArrayType type)
		:pData(NULL),maxSize(count),MinDecrease(MinDecreaseDefault),Length(count),type(type)
	{
		if(count<0)throw XException(E_INVALIDARG);//count<0时参数无效
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
	//直接传入指针和元素数量来构造数组,p为NULL时创建count个元素的数组,type指定对p指向内存的管理方式
	template<typename T>VArray<T>::VArray(int count,typename Types<T>::Normal const* p,XArrayType type)
		:pData(NULL),maxSize(count),MinDecrease(MinDecreaseDefault),Length(count),type(type)
	{
		if(count<0)throw XException(E_INVALIDARG);//count<0时参数无效
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
	//直接转换成const指针形式
	template<typename T>VArray<T>::operator const T*const&()const
	{
		return pData;
	}
	//直接转换成指针形式
	template<typename T>VArray<T>::operator T*const &()
	{
		return pData;
	}
	//迭代器
	template<typename T>Iterator<T> VArray<T>::First()
	{
		return new IArrayIterator<T>(pData,pData,pData+Length);
	}
	//迭代器
	template<typename T>Iterator<const T> VArray<T>::First()const
	{
		return new IArrayIterator<const T>(pData,pData,pData+Length);
	}
	//迭代器
	template<typename T>Iterator<T> VArray<T>::Last()
	{
		return new IArrayIterator<T>(pData,Length?pData+Length-1:NULL,pData+Length);
	}
	//迭代器
	template<typename T>Iterator<const T> VArray<T>::Last()const
	{
		return new IArrayIterator<const T>(pData,Length?pData+Length-1:NULL,pData+Length);
	}
	//迭代器
	template<typename T>Iterator<T> VArray<T>::End()
	{
		return new IArrayIterator<T>(pData,pData+Length,pData+Length);
	}
	//迭代器
	template<typename T>Iterator<const T> VArray<T>::End()const
	{
		return new IArrayIterator<const T>(pData,pData+Length,pData+Length);
	}
	//复制里一个数组的数据(复制构造)，该数组的数据将被丢弃
	template<typename T>VArray<T>& VArray<T>::operator=(const VArray<T>& xArray)
	{
		if(type==Reference)//引用模式
		{
			type = SelfConstruct;
			maxSize = const_cast<int&>(Length) = xArray.Length;
			pData=Malloc(Length);
			T*p(pData),*end(pData+Length),*px(xArray.pData);
			while(p<end)placementnew(p++,*px++);
		}
		else if(type==SelfConstruct)//自构造模式
		{
			if(xArray.Length>Length)
			{
				VArrayDeconstructMethod(pData,Length);//析构
				void * tmp = realloc(pData,sizeof(T)*xArray.Length);
				if(tmp==NULL)throw XException(L"申请内存失败",E_OUTOFMEMORY);
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
				VArrayDeconstructMethod(pData,Length);//析构
				void * tmp = realloc(pData,sizeof(T)*xArray.Length);
				if(xArray.Length>0 && tmp==NULL)throw XException(L"申请内存失败",E_OUTOFMEMORY);
				pData = (T*)tmp;
				maxSize = const_cast<int&>(Length) = xArray.Length;
				T* p(pData),*end(pData+Length),*px(xArray.pData);
				while(p<end)placementnew(p++,*px++);
			}
			else
			{
				VArrayDeconstructMethod(pData+xArray.Length,Length-xArray.Length);//析构
				const_cast<int&>(Length) = xArray.Length;
				T* p(pData),*end(pData+Length),*px(xArray.pData);
				while(p<end)(*p++)=(*px++);
			}
		}
		else//普通模式
		{
			ResizeAndDestroy(xArray.Length);
			VArrayCopyMethod(xArray.pData,pData,Length);
		}
		return *this;
	}
	//获取该数组的一部分（子数组）
	template<typename T>VArray<T> VArray<T>::SubArray(int startIndex,int length,XArrayType type)const
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);//参数无效
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
	//从数据pdata复制len个元素形成数组
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
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
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
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);//参数无效
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
	//从数据pdata的startByte字节处复制len个字节形成数组
	template<typename T>template<typename AnyT>VArray<T> VArray<T>::CopyFromByBytes(const VArray<AnyT>&source)
	{
		if(source.Length==0)return VArray<T>();
		T* p = Malloc(((sizeof(AnyT)*source.Length)%sizeof(T))?sizeof(AnyT)*source.Length/sizeof(T)+1:sizeof(AnyT)*source.Length/sizeof(T));
		XBase::Memory::Copy(p,source,source.GetLengthOfBytes());
		return VArray<T>((source.GetLengthOfBytes()%sizeof(T))?source.GetLengthOfBytes()/sizeof(T)+1:source.GetLengthOfBytes()/sizeof(T),p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>VArray<T> VArray<T>::CopyFromByBytes(const VArray<AnyT>&source, int startByte)
	{
		if(startByte<0)throw XException(E_INVALIDARG);//参数无效
		if(startByte>source.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);//参数无效
		if(startByte==source.GetLengthOfBytes())return VArray<T>();
		T* p = Malloc(((source.GetLengthOfBytes()-startByte)%sizeof(T))?(source.GetLengthOfBytes()-startByte)/sizeof(T)+1:(source.GetLengthOfBytes()-startByte)/sizeof(T));
		XBase::Memory::Copy(p,source,sizeof(AnyT)*source.Length-startByte);
		return VArray<T>(((source.GetLengthOfBytes()-startByte)%sizeof(T))?(source.GetLengthOfBytes()-startByte)/sizeof(T)+1:(source.GetLengthOfBytes()-startByte)/sizeof(T),p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>VArray<T> VArray<T>::CopyFromByBytes(const VArray<AnyT>&source, int startByte,int lengthOfBytes)
	{
		if(startByte<0 || lengthOfBytes<0)throw XException(E_INVALIDARG);//参数无效
		if(startByte+lengthOfBytes>source.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);//参数无效
		if(!lengthOfBytes)return VArray<T>();
		T* p = Malloc((lengthOfBytes%sizeof(T))?lengthOfBytes/sizeof(T)+1:lengthOfBytes/sizeof(T));
		XBase::Memory::Copy(p,source,lengthOfBytes);
		return VArray<T>((lengthOfBytes%sizeof(T))?lengthOfBytes/sizeof(T)+1:lengthOfBytes/sizeof(T),p,SelfConstruct);
	}
	//将该数组的内容复制一部分到另一个数组
	template<typename T>template<typename AnyT>int VArray<T>::CopyTo(VArray<AnyT>& destination,int sourceIndex, int destinationIndex)const
	{
		if(sourceIndex<0 || destinationIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(sourceIndex>Length  || destinationIndex>destination.Length)throw XException(COR_E_INDEXOUTOFRANGE);
		int length = (Length-sourceIndex > destination.Length-destinationIndex)?destination.Length-destinationIndex:Length-sourceIndex;
		T* p = *this+sourceIndex;
		T* pEnd = p+length;
		AnyT* pd = destination+destinationIndex;
		while(p<pEnd){*pd = *p;++p;++pd;}//强制转换
		return length;
	}
	template<typename T>template<typename AnyT>int VArray<T>::CopyTo(VArray<AnyT>& destination,int sourceIndex, int destinationIndex, int length)const
	{
		if(sourceIndex<0 || destinationIndex<0 || length<0)throw XException(E_INVALIDARG);//参数无效
		if(sourceIndex+length>Length  || destinationIndex+length>destination.Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T* p = *this+sourceIndex;
		T* pEnd = p+length;
		AnyT* pd = destination+destinationIndex;
		while(p<pEnd){*pd = *p;++p;++pd;}//强制转换
		return length;
	}
	//向任意一种类型的数组复制一定的字节数
	template<typename T>template<typename AnyT>int VArray<T>::CopyToByBytes(VArray<AnyT>& dest, int sourceByte, int destinationByte)const
	{
		if(sourceByte<0 || destinationByte<0)throw XException(E_INVALIDARG);//参数无效
		if(sourceByte>GetLengthOfBytes() || destinationByte>dest.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);
		int lengthOfByte =  (GetLengthOfBytes()-sourceByte > dest.GetLengthOfBytes()-destinationByte)?dest.GetLengthOfBytes()-destinationByte:GetLengthOfBytes()-sourceByte;
		XBase::Memory::Copy(((unsigned char*)(AnyT*)dest)+destinationByte,((unsigned char*)pData)+sourceByte,lengthOfByte);
		return lengthOfByte;
	}
	template<typename T>template<typename AnyT>int VArray<T>::CopyToByBytes(VArray<AnyT>& dest, int sourceByte, int destinationByte, int lengthOfByte)const
	{
		if(sourceByte<0 || destinationByte<0 || lengthOfByte<0)throw XException(E_INVALIDARG);//参数无效
		if(sourceByte + lengthOfByte>GetLengthOfBytes() || lengthOfByte+destinationByte>dest.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);
		XBase::Memory::Copy(((unsigned char*)(AnyT*)dest)+destinationByte,((unsigned char*)pData)+sourceByte,lengthOfByte);
		return lengthOfByte;
	}
	//加法重载
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
	//关系运算符
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
	//将数组中一系列元素的值设置为t
	template<typename T>template<typename AnyT>void  VArray<T>::ResetTo(const AnyT& t)
	{
		T*p(pData);
		T*end(pData+Length);
		while(p<end)*p++=t;
	}
	template<typename T>template<typename AnyT>void  VArray<T>::ResetTo(const AnyT& t,  int index, int length)
	{
		if(index<0 || length<0)throw XException(E_INVALIDARG);//参数无效
		if(index+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(!length)return;
		T*p(pData+index);
		T*end(pData+Length);
		while(p<end)*p++=t;
	}
	//在数组的某个位置插入元素或数组
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::Insert(int index,const AnyT&t)
	{
		if(index<0)throw XException(E_INVALIDARG);//参数无效
		if(index>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(type==Reference)//新建一块内存区域用以保存数据
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
			if(maxSize>Length)//不需要重新申请空间
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
			else//需要重新申请空间
			{
				maxSize = ++const_cast<int&>(Length);
				T* p = Malloc(Length);
				T* px(p);
				T* end(p+index);
				T* ps(pData);
				while(px!=end)placementnew(px++,*ps++);//复制
				placementnew(px++,t);
				end = p+Length;
				while(px!=end)placementnew(px++,*ps++);//复制
				VArrayDeconstructMethod(pData,Length-1);
				free(pData);
				pData = p;
			}
		}
		else if(type==Normal)
		{
			if(maxSize>Length)//不需要重新申请空间
			{
				++const_cast<int&>(Length);
				T*p(pData+Length);
				T*end(pData+index);
				while(--p!=end)*p = *(p-1);
				*p=t;
			}
			else//需要重新申请空间
			{
				maxSize = ++const_cast<int&>(Length);
				T* p = new T[Length];
				T* px(p);
				T* end(p+index);
				T* ps(pData);
				while(px!=end)*px++ = *ps++;//复制
				*px++ = t;
				end = p+Length;
				while(px!=end)*px++ = *ps++;//复制
				delete []pData;
				pData = p;
			}
		}
		return new IArrayIterator<T>(pData,pData+index,pData+Length);
	}
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::Insert(const Iterator<T>&it,const AnyT&t)
	{
		if(it.GetLength()!=Length)throw XException(L"指定的迭代器已经失效",E_INVALIDARG);
		return Insert(it-pData,t);
	}
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::InsertArray(int index,const VArray<AnyT>&xArray)
	{
		if(index<0)throw XException(E_INVALIDARG);//参数无效
		if(index>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(xArray.Length==0)return new IArrayIterator<T>(pData,pData+index,pData+Length);
		if(type==Reference)//新建一块内存区域用以保存数据
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
			if(maxSize>=Length+xArray.Length)//不需要重新申请空间
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
			else//需要重新申请空间
			{
				maxSize = (const_cast<int&>(Length)+=xArray.Length);
				T* p = Malloc(Length);
				T* pt(p);
				T* end(p+index);
				T* ps(pData);
				while(pt!=end)placementnew(pt++,*ps++);//复制
				const T*px(xArray);
				end = const_cast<T*>(xArray+xArray.Length);
				while(px!=end)placementnew(pt++,*px++);
				end = p+Length;
				while(pt!=end)placementnew(pt++,*ps++);//复制
				VArrayDeconstructMethod(pData,Length-xArray.Length);
				free(pData);
				pData = p;
			}
		}
		else if(type==Normal)
		{
			if(maxSize>=Length+xArray.Length)//不需要重新申请空间
			{
				const_cast<int&>(Length)+=xArray.Length;
				T*p(pData+Length);
				T*end(pData+index);
				T*ps(p-xArray.Length);
				while(ps!=end)*--p=*--ps;
				const T* px(xArray+Length);
				while(p!=end)*--p=*--px;
			}
			else//需要重新申请空间
			{
				maxSize = (const_cast<int&>(Length)+=xArray.Length);
				T* p = new T[Length];
				T* px(p);
				T* end(p+index);
				T* ps(pData);
				while(px!=end)*px++ = *ps++;//复制
				const T*pxx(xArray);
				end = const_cast<T*>(xArray+xArray.Length);
				while(px!=end)*px++ = *pxx++;
				end = p+Length;
				while(px!=end)*px++ = *ps++;//复制
				delete []pData;
				pData = p;
			}
		}
		return new IArrayIterator<T>(pData,pData+index,pData+Length);
	}
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::InsertArray(const Iterator<T>&it,const VArray<AnyT>&xArray)
	{
		if(it.GetLength()!=Length || it.GetFirstElementPointer()!=pData)throw XException(L"指定的迭代器已经失效",E_INVALIDARG);
		return InsertArray(it-pData,xArray);
	}
	//在数组结尾添加元素
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::Append(const AnyT&t)
	{
		return Insert(Length,t);
	}
	//在数组结尾添加数组
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::AppendArray(const VArray<AnyT>&xArray)
	{
		return InsertArray(Length,xArray);
	}
	//在数组中删除指定区域的元素
	template<typename T>Iterator<T>  VArray<T>::Remove(int startIndex)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(startIndex==0)//全部移除
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
			if(MinDecrease+startIndex<maxSize)//需要重新申请空间
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
		if(index<0 )throw XException(E_INVALIDARG);//参数无效
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
			if(MinDecrease+Length-1<maxSize)//需要重新申请空间
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
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);//参数无效
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
			if(MinDecrease+Length-length<maxSize)//需要重新申请空间
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
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"指定的迭代器已经失效",E_INVALIDARG);
		return Remove(int((T*)first-pData),int((T*)end-(T*)first));
	}
	//移除数组指定区域中第一个与指定值相等的元素
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::RemoveOneOf(const AnyT&t,int startIndex)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T*end(pData+Length);
		T*pt(pData+startIndex);
		while(pt!=end && !(*pt==t))++pt;//查找相同元素的位置
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
		while(pt!=end && !(*pt==t))++pt;//查找相同元素的位置
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
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"指定的迭代器已经失效",E_INVALIDARG);
		return RemoveOneOf(t,int((T*)first-pData),int((T*)end-(T*)first));
	}
	//移除数组指定区域中出现的所有与指定值相等的元素（使用==进行比较）
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::RemoveAllOf(const AnyT&t,int startIndex)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(type == Reference)
		{
			T*end(pData+Length);
			T*pt(pData+startIndex);
			while(pt!=end && !(*pt==t))++pt;//查找相同元素的位置
			if(pt==end)return End();//没找到需要移除的元素
			T* p = Malloc(Length-1);//直接分配空间（多出）
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
			while(pt!=end && !(*pt==t))++pt;//查找相同元素的位置
			if(pt==end)return new IArrayIterator<T>(pData,pt,pData+Length);//没找到需要移除的元素
			T* p = Malloc(Length-1);//直接分配空间（多出）
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
		T*end(pData+Length);//数据终止点
		T*pt(pData+startIndex);//起始查找点
		T*pe(pt+length);//查找截断点
		T*pc(pt);//复制数据起始点
		T*pindex=pData+Length;//返回迭代器位置
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
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"指定的迭代器已经失效",E_INVALIDARG);
		return RemoveAllOf(t,int((T*)first-pData),int((T*)end-(T*)first));
	}
	//移除数组指定区域中出现的所有与指定值相等的最多count个元素（使用==进行比较）
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::RemoveSomeOf(const AnyT&t,int startIndex,int length,int count)
	{
		if(startIndex<0 || length<0 || count<0)throw XException(E_INVALIDARG);
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(count==0)return End();
		if(type == Reference)
		{
			T*pt(pData+startIndex);
			T*end(pt+length);
			while(pt!=end && !(*pt==t))++pt;//查找相同元素的位置
			if(pt==end)return new IArrayIterator<T>(pData,pt,pData+Length);//没找到需要移除的元素
			--count;
			T* p = Malloc(Length-1);//直接分配空间（多出）
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
		T*end(pData+Length);//数据终止点
		T*pt(pData+startIndex);//起始查找点
		T*pe(pt+length);//查找截断点
		T*pc(pt);//复制数据起始点
		T*pindex=pData+Length;//返回迭代器位置
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
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"指定的迭代器已经失效",E_INVALIDARG);
		return RemoveSomeOf(t,int((T*)first-pData),int((T*)end-(T*)first),count);
	}
	//替换数组中某个元素为另一个元素
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> VArray<T>::ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(type == Reference)
		{
			T*end(pData+Length);
			T*pt(pData+startIndex);
			while(pt!=end && !(*pt==t))++pt;//查找相同元素的位置
			if(pt==end)return End();//没找到需要移除的元素
			T* p = Malloc(Length);//直接分配空间
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
			while(pt!=end && !(*pt==t))++pt;//查找相同元素的位置
			if(pt==end)return End();//没找到需要移除的元素
			T* p = Malloc(Length);//直接分配空间
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
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"指定的迭代器已经失效",E_INVALIDARG);
		return ReplaceOneOf(t,to,int((T*)first-pData),int((T*)end-(T*)first));
	}
	//替换数组中所有与t相等的元素为另一个元素
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> VArray<T>::ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(type == Reference)
		{
			T*end(pData+Length);
			T*pt(pData+startIndex);
			while(pt!=end && !(*pt==t))++pt;//查找相同元素的位置
			if(pt==end)return End();//没找到需要移除的元素
			T* p = Malloc(Length);//直接分配空间（多出）
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
			while(pt!=end && !(*pt==t))++pt;//查找相同元素的位置
			if(pt==end)return End();//没找到需要移除的元素
			T* p = Malloc(Length);//直接分配空间（多出）
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
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"指定的迭代器已经失效",E_INVALIDARG);
		return ReplaceAllOf(t,to,int((T*)first-pData),int((T*)end-(T*)first));
	}
	//替换数组中某些元素为另一个元素
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> VArray<T>::ReplaceSomeOf(const AnyT1& t, const AnyT2& to,int startIndex,int length,int count)
	{
		if(startIndex<0 || length<0 || count<0)throw XException(E_INVALIDARG);
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(count==0)return End();
		if(type == Reference)
		{
			T*pt(pData+startIndex);
			T*end(pt+length);
			while(pt!=end && !(*pt==t))++pt;//查找相同元素的位置
			if(pt==end)return End();//没找到需要移除的元素
			T* p = Malloc(Length);//直接分配空间（多出）
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
		if(first.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetLength()!=Length || end.GetFirstElementPointer()!=pData)throw XException(L"指定的迭代器已经失效",E_INVALIDARG);
		return ReplaceSomeOf(t,to,int((T*)first-pData),int((T*)end-(T*)first),count);
	}
		//随机乱序排列
	template<typename T>void VArray<T>::SortRandom(int startIndex,int len)
	{
		if(startIndex<0 || len<0)throw XException(E_INVALIDARG);
		if(startIndex+len>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		for(int i=1;i<len;++i)
		{
			XBase::Swap(*(pData+i),*(pData+XRandom::Default.Rand()%(i+1)));
		}
	}
	//随机乱序排列
	template<typename T>void VArray<T>::SortRandom(int startIndex=0){return SortRandom(startIndex,Length-startIndex);}
	//调整大小并尽量保存数据
	template<typename T>int VArray<T>::Resize(int count)
	{
		if(count<0)throw XException(E_INVALIDARG);//参数无效
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
		else if(type == Reference || count>maxSize || count<maxSize-MinDecrease)//重新分配
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
	//调整大小并不一定保存数据
	template<typename T>int VArray<T>::ResizeAndDestroy(int count)
	{
		if(count<0)throw XException(E_INVALIDARG);//参数无效
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
		else if(type == Reference || count>maxSize || count<maxSize-MinDecrease)//重新分配
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
	//查找与指定值相等的第一个元素，找不到则返回-1
	template<typename T>template<typename AnyT>int VArray<T>::IndexOf(const AnyT&t, int startIndex)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T* p(pData+startIndex);
		T* end(pData+Length);
		while(p!=end)if(*p++==t)return int(p-pData-1);
		return -1;
	}
	template<typename T>template<typename AnyT>int VArray<T>::IndexOf(const AnyT&t, int startIndex,int length)const
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);//参数无效
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T* p(pData+startIndex);
		T* end(p+length);
		while(p!=end)if(*p++==t)return int(p-pData-1);
		return -1;
	}
	template<typename T>template<typename AnyT>int VArray<T>::IndexOf(const AnyT&t, const Iterator<const T>& first,const Iterator<const T>&end)const
	{
		if(first.GetLength()!=Length || end.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetFirstElementPointer()!=pData)throw XException(L"指定的迭代器不适用于本数组",E_INVALIDARG);//参数无效
		return IndexOf(t,(const T*)first-pData,(const T*)end-(const T*)first);
	}
	//查找与指定值相等的最后一个元素，找不到则返回-1
	template<typename T>template<typename AnyT>int VArray<T>::LastIndexOf(const AnyT&t, int startIndex)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T* p(pData+Length);
		T* end(pData+startIndex);
		while(p--!=end)if(*p==t)return int(p-pData);
		return -1;
	}
	template<typename T>template<typename AnyT>int VArray<T>::LastIndexOf(const AnyT&t, int startIndex,int length)const
	{
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);//参数无效
		if(startIndex+length>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		T* end(pData+startIndex);
		T* p(end+length);
		while(p--!=end)if(*p==t)return int(p-pData);
		return -1;
	}
	template<typename T>template<typename AnyT>int VArray<T>::LastIndexOf(const AnyT&t, const Iterator<const T>& first,const Iterator<const T>&end)const
	{
		if(first.GetLength()!=Length || end.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetFirstElementPointer()!=pData)throw XException(L"指定的迭代器不适用于本数组",E_INVALIDARG);//参数无效
		return LastIndexOf(t,(const T*)first-pData,(const T*)end-(const T*)first);
	}
	//查找指定元素的位置，找不到返回end
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
	//在指定区域查找指定元素的位置，找不到返回end
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
	//在用迭代器指定的区域查找指定元素的位置，找不到返回end
	template<typename T>template<typename AnyT>Iterator<T> VArray<T>::Find(const AnyT&t,const Iterator<const T>& first,const Iterator<const T>& end)const
	{
		if(first.GetLength()!=Length || end.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetFirstElementPointer()!=pData)throw XException(L"指定的迭代器不适用于本数组",E_INVALIDARG);//参数无效
		return Find(t,(const T*)first-pData,(const T*)end-(const T*)first);
	}
	//查找与指定变量相等的元素数
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
	//在指定区域查找与指定变量相等的元素数
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
	//在用迭代器指定的区域查找与指定变量相等的元素数
	template<typename T>template<class AnyT>int VArray<T>::CountOf(const AnyT&t,const Iterator<const T>& first,const Iterator<const T>& end)const
	{
		if(first.GetLength()!=Length || end.GetLength()!=Length || first.GetFirstElementPointer()!=pData || end.GetFirstElementPointer()!=pData)throw XException(L"指定的迭代器不适用于本数组",E_INVALIDARG);//参数无效
		return CountOf(t,(const T*)first-pData,(const T*)end-(const T*)first);
	}
	//获取第一个元素的引用
	template<typename T>T& VArray<T>::FirstElement()
	{
		if(Length==0)throw XException("数组为空",COR_E_INDEXOUTOFRANGE);
		return pData[0];
	}
	template<typename T>const T& VArray<T>::FirstElement()const
	{
		if(Length==0)throw XException("数组为空",COR_E_INDEXOUTOFRANGE);
		return pData[0];
	}
	//获取最后一个元素的引用
	template<typename T>T& VArray<T>::LastElement()
	{
		if(Length==0)throw XException("数组为空",COR_E_INDEXOUTOFRANGE);
		return pData[Length-1];
	}
	template<typename T>const T& VArray<T>::LastElement()const
	{
		if(Length==0)throw XException("数组为空",COR_E_INDEXOUTOFRANGE);
		return pData[Length-1];
	}



	//XArray
	template<typename T>int XArray<T>::GetLength()const
	{
		return Pointer()->Length;
	}
	//获取数组按字节计算的长度
	template<typename T>int XArray<T>::GetLengthOfBytes()const
	{
		return Pointer()->Length;
	}
	//获取最小重申空间变化值
	template<typename T>int XArray<T>::GetMinDecrease()const
	{
		return Pointer()->MinDecrease;
	}
	//设置最小重申空间变化值
	template<typename T>void XArray<T>::SetMinDecrease(int min)
	{
		Pointer()->MinDecrease = min;
	}
	//直接转换成指针形式
	template<typename T>XArray<T>::operator const T*const& ()const
	{
		return *Pointer();
	}
	//直接转换成指针形式
	template<typename T>XArray<T>::operator T*const &()
	{
		return *Pointer();
	}
	//迭代器
	template<typename T>Iterator<T> XArray<T>::First()
	{
		return new IArrayIterator<T>((T*)*this,(T*)*this,*this+Length);
	}
	//迭代器
	template<typename T>Iterator<const T> XArray<T>::First()const
	{
		return new IArrayIterator<T>((const T*)*this,(const T*)*this,*this+Length);
	}
	//迭代器
	template<typename T>Iterator<T> XArray<T>::Last()
	{
		return new IArrayIterator<T>((T*)*this,Length==0?NULL:*this+Length-1,*this+Length);
	}
	//迭代器
	template<typename T>Iterator<const T> XArray<T>::Last()const
	{
		return new IArrayIterator<T>((const T*)*this,Length==0?NULL:*this+Length-1,*this+Length);
	}
	//迭代器
	template<typename T>Iterator<T> XArray<T>::End()
	{
		return new IArrayIterator<T>((T*)*this,*this+Length,*this+Length);
	}
	//迭代器
	template<typename T>Iterator<const T> XArray<T>::End()const
	{
		return new IArrayIterator<T>((const T*)*this,*this+Length,*this+Length);
	}

	//加法重载
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
	//关系运算符
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
	//获取该数组的一部分（子数组）
	template<typename T>XArray<T> XArray<T>::SubArray(int startIndex,int length,XArrayType type)const
	{
		if(IsNull())throw XException(E_POINTER);
		if(length<0 || startIndex<0)throw XException(E_INVALIDARG);
		if(length+startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		return new VArray<T>(length,(const T*const&)*this+startIndex,type);
	}
	//从数据pdata的startIndex元素起复制len个元素形成T作为元素的数组
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
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
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
		if(startIndex<0 || length<0)throw XException(E_INVALIDARG);//参数无效
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
	//从数据pdata的startByte字节处复制len个字节形成数组
	template<typename T>template<typename AnyT>XArray<T> XArray<T>::CopyFromByBytes(const XArray<AnyT>&source)
	{
		if(source.Length==0)return new VArray<T>();
		T* p = VArray<T>::Malloc(((sizeof(AnyT)*source.Length)%sizeof(T))?sizeof(AnyT)*source.Length/sizeof(T)+1:sizeof(AnyT)*source.Length/sizeof(T));
		XBase::Memory::Copy(p,(const AnyT*)source,source.GetLengthOfBytes());
		return new VArray<T>((source.GetLengthOfBytes()%sizeof(T))?source.GetLengthOfBytes()/sizeof(T)+1:source.GetLengthOfBytes()/sizeof(T),p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>XArray<T> XArray<T>::CopyFromByBytes(const XArray<AnyT>&source, int startByte)
	{
		if(startByte<0)throw XException(E_INVALIDARG);//参数无效
		if(startByte>source.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);//参数无效
		if(startByte==source.GetLengthOfBytes())return new VArray<T>();
		T* p = VArray<T>::Malloc(((source.GetLengthOfBytes()-startByte)%sizeof(T))?(source.GetLengthOfBytes()-startByte)/sizeof(T)+1:(source.GetLengthOfBytes()-startByte)/sizeof(T));
		XBase::Memory::Copy(p,(const AnyT*)source,sizeof(AnyT)*source.Length-startByte);
		return new VArray<T>(((source.GetLengthOfBytes()-startByte)%sizeof(T))?(source.GetLengthOfBytes()-startByte)/sizeof(T)+1:(source.GetLengthOfBytes()-startByte)/sizeof(T),p,SelfConstruct);
	}
	template<typename T>template<typename AnyT>XArray<T> XArray<T>::CopyFromByBytes(const XArray<AnyT>&source, int startByte,int lengthOfBytes)
	{
		if(startByte<0 || lengthOfBytes<0)throw XException(E_INVALIDARG);//参数无效
		if(startByte+lengthOfBytes>source.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);//参数无效
		if(!lengthOfBytes)return new VArray<T>();
		T* p = VArray<T>::Malloc((lengthOfBytes%sizeof(T))?lengthOfBytes/sizeof(T)+1:lengthOfBytes/sizeof(T));
		XBase::Memory::Copy(p,source,lengthOfBytes);
		return new VArray<T>((lengthOfBytes%sizeof(T))?lengthOfBytes/sizeof(T)+1:lengthOfBytes/sizeof(T),p,SelfConstruct);
	}
	//将该数组的内容复制一部分到另一个数组
	template<typename T>template<typename AnyT>int XArray<T>::CopyTo(XArray<AnyT>& destination,int sourceIndex, int destinationIndex)const
	{
		if(sourceIndex<0 || destinationIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(sourceIndex>Length  || destinationIndex>destination.Length)throw XException(COR_E_INDEXOUTOFRANGE);
		int length = (Length-sourceIndex > destination.Length-destinationIndex)?destination.Length-destinationIndex:Length-sourceIndex;
		const T* p = *this+sourceIndex;
		T* pEnd = p+length;
		AnyT* pd = destination+destinationIndex;
		while(p<pEnd){*pd = *p;++p;++pd;}//强制转换
		return length;
	}
	template<typename T>template<typename AnyT>int XArray<T>::CopyTo(XArray<AnyT>& destination,int sourceIndex, int destinationIndex, int length)const
	{
		if(sourceIndex<0 || destinationIndex<0 || length<0)throw XException(E_INVALIDARG);//参数无效
		if(sourceIndex+length>Length  || destinationIndex+length>destination.Length)throw XException(COR_E_INDEXOUTOFRANGE);
		const T* p = *this+sourceIndex;
		const T* pEnd = p+length;
		AnyT* pd = destination+destinationIndex;
		while(p<pEnd){*pd = *p;++p;++pd;}//强制转换
		return length;
	}
	//向任意一种类型的数组复制一定的字节数
	template<typename T>template<typename AnyT>int XArray<T>::CopyToByBytes(XArray<AnyT>& dest, int sourceByte, int destinationByte)const
	{
		if(sourceByte<0 || destinationByte<0)throw XException(E_INVALIDARG);//参数无效
		if(sourceByte>GetLengthOfBytes() || destinationByte>dest.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);
		int lengthOfByte =  (GetLengthOfBytes()-sourceByte > dest.GetLengthOfBytes()-destinationByte)?dest.GetLengthOfBytes()-destinationByte:GetLengthOfBytes()-sourceByte;
		XBase::Memory::Copy(((unsigned char*)(AnyT*)dest)+destinationByte,((unsigned char*)pData)+sourceByte,lengthOfByte);
		return lengthOfByte;
	}
	template<typename T>template<typename AnyT>int XArray<T>::CopyToByBytes(XArray<AnyT>& dest, int sourceByte, int destinationByte, int lengthOfByte)const
	{
		if(sourceByte<0 || destinationByte<0 || lengthOfByte<0)throw XException(E_INVALIDARG);//参数无效
		if(sourceByte + lengthOfByte>GetLengthOfBytes() || lengthOfByte+destinationByte>dest.GetLengthOfBytes())throw XException(COR_E_INDEXOUTOFRANGE);
		XBase::Memory::Copy(((unsigned char*)(AnyT*)dest)+destinationByte,((unsigned char*)pData)+sourceByte,lengthOfByte);
		return lengthOfByte;
	}
	//将数组中一系列元素的值设置为t
	template<typename T>template<typename AnyT>void XArray<T>::ResetTo(const AnyT& t)
	{
		return Pointer()->ResetTo(t);
	}
	template<typename T>template<typename AnyT>void XArray<T>::ResetTo(const AnyT& t, int index, int length)
	{
		return Pointer()->ResetTo(t,index,length);
	}
	//在数组的某个位置插入元素或数组
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::Insert(int index,const AnyT&t)
	{
		return Pointer()->Insert(index,t);
	}
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::Insert(const Iterator<T>&it,const AnyT&t)
	{
		if(it.GetLength()!=Length)throw XException(L"指定的迭代器已经失效",E_INVALIDARG);
		return Insert(it-(T*)*this,t);
	}
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::InsertArray(int index,const XArray<AnyT>&xArray)
	{
		if(xArray.IsNull())throw XException(E_POINTER);
		return Pointer()->InsertArray(index,*reinterpret_cast<VArray<AnyT>*const&>(reinterpret_cast<XArray<T>*>(&xArray)->pObject));
	}
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::InsertArray(const Iterator<T>&it,const XArray<AnyT>&xArray)
	{
		if(it.GetLength()!=Length || it.GetFirstElementPointer()!=(T*)*this)throw XException(L"指定的迭代器已经失效",E_INVALIDARG);
		return InsertArray(it-(T*)*this,xArray);
	}
	//在数组结尾添加元素或数组
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::Append(const AnyT&t)
	{
		return Pointer()->Append(t);
	}
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::AppendArray(const XArray<AnyT>& rArray)
	{
		if(rArray.IsNull())throw XException(E_POINTER);
		return Pointer()->AppendArray(*reinterpret_cast<VArray<AnyT>*const&>(reinterpret_cast<XArray<T>*>(&rArray)->pObject));
	}
	//在数组中删除指定区域的元素，startIndex为起始移除索引位置，直到末尾
	template<typename T>Iterator<T> XArray<T>::Remove(int startIndex)
	{
		return Pointer()->Remove(startIndex);
	}
	//在数组中删除指定位置的元素，index为起始移除位置索引
	template<typename T>Iterator<T> XArray<T>::RemoveAt(int index)
	{
		return Pointer()->RemoveAt(index);
	}
	//在数组中删除指定区域的元素，startIndex为起始移除索引位置，length为要移除的元素数
	template<typename T>Iterator<T> XArray<T>::Remove(int startIndex,int length)
	{
		return Pointer()->Remove(startIndex,length);
	}
	//在数组中删除指定区域的元素，startIndex为起始移除索引位置，length为要移除的元素数
	template<typename T>Iterator<T> XArray<T>::Remove(const Iterator<T>& firstIterator,const Iterator<T>& endIterator)
	{
		return Pointer()->Remove(firstIterator,endIterator);
	}
	//移除数组指定区域中第一个与指定值相等的元素（使用==进行比较），返回的迭代器为移除后替代原元素位置
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveOneOf(const AnyT&t,int startIndex)
	{
		return Pointer()->RemoveOneOf(t,startIndex);
	}
	//移除数组指定区域中第一个与指定值相等的元素（使用==进行比较），length为元素数，返回的迭代器为移除后替代原元素位置
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveOneOf(const AnyT&t,int startIndex,int length)
	{
		return Pointer()->RemoveOneOf(t,startIndex,length);
	}
	//移除数组指定区域中第一个与指定值相等的元素（使用==进行比较），返回的迭代器为移除后替代原元素位置
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveOneOf(const AnyT&t,const Iterator<T>&start ,const Iterator<T>&end)
	{
		return Pointer()->RemoveOneOf(t,start,end);
	}
	//移除数组指定区域中出现的所有与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveAllOf(const AnyT&t,int startIndex)
	{
		return Pointer()->RemoveAllOf(t,startIndex);
	}
	//移除数组指定区域中出现的所有与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveAllOf(const AnyT&t,int startIndex,int length)
	{
		return Pointer()->RemoveAllOf(t,startIndex,length);
	}
	//移除数组指定区域中出现的所有与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveAllOf(const AnyT&t,const Iterator<T>&start ,const Iterator<T>&end)
	{
		return Pointer()->RemoveAllOf(t,start,end);
	}
	//移除数组指定区域中出现的最多count个与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveSomeOf(const AnyT&t,int startIndex,int length,int count)
	{
		return Pointer()->RemoveSomeOf(t,startIndex,length,count);
	}
	//移除数组指定区域中出现的最多count个与指定值相等的元素（使用==进行比较），返回的迭代器为最后一个移除后替代原元素位置
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::RemoveSomeOf(const AnyT&t,const Iterator<T>&first ,const Iterator<T>&end,int count)
	{
		return Pointer()->RemoveSomeOf(t,first,end,count);
	}
	//替换数组中某个元素为另一个元素
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex)
	{
		return Pointer()->ReplaceOneOf(t,to,startIndex);
	}
	//替换数组中某个元素为另一个元素
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceOneOf(const AnyT1& t, const AnyT2& to,int startIndex,int length)
	{
		return Pointer()->ReplaceOneOf(t,to,startIndex,length);
	}
	//替换数组中某个元素为另一个元素，返回的迭代器为最后一个替换位置
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceOneOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end)
	{
		return Pointer()->ReplaceOneOf(t,to,start,end);
	}
	//替换数组中所有与t相等的元素为另一个元素
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex)
	{
		return Pointer()->ReplaceAllOf(t,to,startIndex);
	}
	//替换数组中所有与t相等的元素为另一个元素
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceAllOf(const AnyT1& t, const AnyT2& to,int startIndex,int length)
	{
		return Pointer()->ReplaceAllOf(t,to,startIndex,length);
	}
	//替换数组中某个元素为另一个元素，返回的迭代器为最后一个替换位置
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceAllOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end)
	{
		return Pointer()->ReplaceAllOf(t,to,start,end);
	}
	//替换数组中某些元素为另一个元素
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceSomeOf(const AnyT1& t, const AnyT2& to,int startIndex,int length,int count)
	{
		return Pointer()->ReplaceSomeOf(t,to,startIndex,length,count);
	}
	//替换数组中某个元素为另一个元素，返回的迭代器为最后一个替换位置
	template<typename T>template<typename AnyT1,typename AnyT2>Iterator<T> XArray<T>::ReplaceSomeOf(const AnyT1& t, const AnyT2& to,const Iterator<T>&start ,const Iterator<T>&end,int count)
	{
		return Pointer()->ReplaceSomeOf(t,to,start,end,count);
	}
	//调整大小并尽量保存数据
	template<typename T>int XArray<T>::Resize( int count)
	{
		return Pointer()->Resize(count);
	}
	//调整大小并不一定保存数据，与Resize相比少了一个复制的过程
	template<typename T>int XArray<T>::ResizeAndDestroy( int count)
	{
		return Pointer()->ResizeAndDestroy(count);
	}
	//查找与指定值相等的第一个元素，找不到则返回-1
	template<typename T>template<typename AnyT>int XArray<T>::IndexOf(const AnyT&t, int startIndex)const
	{
		return Pointer()->IndexOf(t,startIndex);
	}
	//在指定区域查找与指定值相等的第一个元素，找不到则返回-1
	template<typename T>template<typename AnyT>int XArray<T>::IndexOf(const AnyT&t, int startIndex,int length)const
	{
		return Pointer()->IndexOf(t,startIndex,length);
	}
	//在用迭代器指定的区域查找与指定值相等的第一个元素，找不到则返回-1
	template<typename T>template<typename AnyT>int XArray<T>::IndexOf(const AnyT&t, const Iterator<const T>& start,const Iterator<const T>& end)const
	{
		return Pointer()->IndexOf(t,start,end);
	}
	//查找与指定值相等的最后一个元素，找不到则返回-1
	template<typename T>template<typename AnyT>int XArray<T>::LastIndexOf(const AnyT&t,int startIndex)const
	{
		return Pointer()->LastIndexOf(t,startIndex);
	}
	//在指定区域查找与指定值相等的最后一个元素，找不到则返回-1
	template<typename T>template<typename AnyT>int XArray<T>::LastIndexOf(const AnyT&t,int startIndex,int length)const
	{
		return Pointer()->LastIndexOf(t,startIndex,length);
	}
	//在用迭代器指定的区域查找与指定值相等的最后一个元素，找不到则返回-1
	template<typename T>template<typename AnyT>int XArray<T>::LastIndexOf(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const
	{
		return Pointer()->LastIndexOf(t,start,end);
	}
	//查找指定元素的位置，找不到返回end
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::Find(const AnyT&t,int startIndex)const
	{
		return Pointer()->Find(t,startIndex);
	}
	//在指定区域查找指定元素的位置，找不到返回end
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::Find(const AnyT&t,int startIndex,int length)const
	{
		return Pointer()->Find(t,startIndex,length);
	}
	//在用迭代器指定的区域查找指定元素的位置，找不到返回end
	template<typename T>template<typename AnyT>Iterator<T> XArray<T>::Find(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const
	{
		return Pointer()->Find(t,start,end);
	}
	//查找与指定变量相等的元素数
	template<typename T>template<class AnyT>int XArray<T>::CountOf(const AnyT&t,int startIndex)const
	{
		return Pointer()->CountOf(t,startIndex);
	}
	//在指定区域查找与指定变量相等的元素数
	template<typename T>template<class AnyT>int XArray<T>::CountOf(const AnyT&t,int startIndex,int length)const
	{
		return Pointer()->CountOf(t,startIndex,length);
	}
	//在用迭代器指定的区域查找与指定变量相等的元素数
	template<typename T>template<class AnyT>int XArray<T>::CountOf(const AnyT&t,const Iterator<const T>& start,const Iterator<const T>& end)const
	{
		return Pointer()->CountOf(t,start,end);
	}
	//获取第一个元素的引用
	template<typename T>T& XArray<T>::FirstElement()
	{
		return Pointer()->FirstElement();
	}
	template<typename T>const T& XArray<T>::FirstElement()const
	{
		return Pointer()->FirstElement();
	}
	//获取最后一个元素的引用
	template<typename T>T& XArray<T>::LastElement()
	{
		return Pointer()->LastElement();
	}
	template<typename T>const T& XArray<T>::LastElement()const
	{
		return Pointer()->LastElement();
	}
	//获取数组类型
	template<typename T>XArrayType XArray<T>::GetArrayType()const
	{
		return Pointer()->GetArrayType();
	}
	//获取浅表副本
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