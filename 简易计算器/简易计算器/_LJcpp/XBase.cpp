#include "stdafx.h"
namespace LJ
{
	const float MaxValues::Float = 3.402823466e+38F;
	const double MaxValues::Double = 1.7976931348623158e+308;
	const float MinValues::Float = 1.175494351e-38F;
	const double MinValues::Double = 2.2250738585072014e-308;

	//XBase
	//增加该对象被引用的次数，应采用原子操作，返回该对象指针。如果referenceCount小于0，则该方法返回NULL，并且引用计数不变
	XBase* XBase::ReferenceIncrement()const
	{
		if(referenceCount<0)return NULL;
		InterlockedIncrement(&referenceCount);
		return const_cast<XBase*>(this);
	}
	//减少该对象被引用的次数，应采用原子操作，如果引用计数被减小为0，则进行自删除操作
	void XBase::ReferenceDecrement()const
	{
		if(0==InterlockedDecrement(&referenceCount))
			delete const_cast<XBase*>(this);
	}
	//获取指针的引用，当IsNull()时，调用该方法将抛出异常
	XBase* XBase::Pointer()const{if(pObject==NULL)throw XException(L"该引用为空或非法。",E_POINTER);return pObject;}
	//取地址
	XBase*XBase::operator&(){if(referenceCount==0)ReferenceIncrement();return this;}
	const XBase*XBase::operator&()const{if(referenceCount==0)ReferenceIncrement();return this;}
	//类型信息
	const XTypes& XBase::CurrentType = NodeOfRoot::Add(L"LJ::XBase",Types<LJ::XBase>());
	//获取对象类型信息
	const XTypes& XBase::GetType()const
	{
		return CurrentType;
	}
	//比较该对象与object对象是否是同一个对象
	bool XBase::Equals(const XBase& object)const
	{
		return this == object.ThisPointer();
	}
	//输出该对象的字符串描述
	XString XBase::ToString()const
	{
		return GetType().GetFullName();
	}
	//判断该对象是否为空引用（仅当pObject为NULL时返回true）
	bool XBase::IsNull()const
	{
		return !pObject;
	}
	void XBase::SwapWith(XBase& x)
	{
		if(GetType()!=x.GetType())throw XException(L"指定的交换对象与当前对象类型不一致",E_INVALIDARG);
		if(pObject!=this){XBase*tmp = pObject;pObject=x.pObject;x.pObject=tmp;}//只交换指针
	}
	//判断该对象是否可以被引用，如果referenceCount小于0则返回false
	bool XBase::CanBeReferenced()const
	{
		return referenceCount>=0;
	}
	//判断该对象是否是引用终结点（即原始值），如果pObject指向自身则返回true
	bool XBase::IsReferenceEnding()const
	{
		return pObject==this;
	}
	//判断对象与object对象引用的是否是同一个对象，即pObject相等时返回true
	bool XBase::ReferenceEquals(const XBase& object)const
	{
		return pObject==object.pObject;
	}
	//赋值
	XBase& XBase::operator=(const XBase& xbase)
	{
		if(this == xbase.ThisPointer())return *this;
		//自身为原始值，则不能变为引用
		if(this == pObject)
		{
			//直接返回
			return *this;
		}
		//自身为引用，如果referenceCount<0则不允许变为自身的引用
		if(referenceCount<0)
		{
			//如果对方引用自己则抛出异常（实际上不可能发生）
			if(xbase.pObject==this)throw XException(L"检测到该实例被非法引用。",E_INVALIDARG);
		}
		if(pObject)pObject->ReferenceDecrement();
		pObject = xbase.pObject;
		if(pObject)pObject->ReferenceIncrement();
		return *this;
	}
	//默认构造函数，被引用数为0，指针为NULL，也就是该实例默认即可以被引用，又可以引用其它实体
	XBase::XBase()
		:referenceCount(0),pObject(NULL)
	{}
	//制作一个副本，并返回该副本的指针
	XBase* XBase::NewCopy()const
	{
		return new XBase(*this);
	}
	//使用指定的指针和引用计数来构造
	XBase::XBase(XBase*x,long refCount)
		:referenceCount(refCount),pObject(x)
	{}
	//使用一个指针来构造一个引用，该过程是非线程安全的
	XBase::XBase(XBase* pBase)
		:pObject(pBase),referenceCount(0)
	{
		if(pObject)
		{
			if(pObject->referenceCount<0)
			{
				pObject = NULL;
				throw XException(L"指定的对象无法被引用。",E_INVALIDARG);
			}
			pObject->ReferenceIncrement();//增加引用计数，值得注意的是请不要通过对局部变量取地址来构建引用
		}
	}
	//复制构造函数
	XBase::XBase(const XBase& xBase)
		:pObject(xBase.pObject),
		referenceCount(xBase.referenceCount>0?0:xBase.referenceCount)
	{
		if(pObject)
		{
			if(pObject==xBase.ThisPointer())
			{
				pObject = this;
			}
			else
			{
				if(pObject->referenceCount<0)
				{
					pObject = NULL;
					throw XException(L"指定的对象无法被引用。",E_INVALIDARG);
				}
				pObject->ReferenceIncrement();
			}
		}
	}
	//右值复制构造函数
#ifdef _USE_RIGHT_VALUE_REFERENCE
	XBase::XBase(const XBase&& xBase)
		:pObject(xBase.pObject),
		referenceCount(xBase.referenceCount>0?0:xBase.referenceCount)
	{
		if(pObject)
		{
			if(pObject==xBase.ThisPointer())
			{
				pObject = this;
			}
			else
			{
				if(pObject->referenceCount<0)
				{
					pObject = NULL;
					throw XException(L"指定的对象无法被引用。",E_INVALIDARG);
				}
				const_cast<XBase*&>(xBase.pObject)=NULL;
			}
		}
	}
#endif
	//虚析构函数，使得该类可以被继承
	XBase::~XBase()
	{
		if(pObject && pObject!=this)
		{
			pObject->ReferenceDecrement();
		}
	}
	//内存复制,pDestination指向目标内存，pSource指向源数据，sizeInBytes是按字节数表示的大小，源数据数和目标内存不能重叠
	void Memory::Copy(void* pDestination,const void* pSource,size_t SizeInBytes)
		{
			while(SizeInBytes>=8){*(reinterpret_cast<structSize<8>*&>(pDestination)++) = *(reinterpret_cast<structSize<8>*&>(const_cast<void*&>(pSource))++);SizeInBytes-=8;}
			switch(SizeInBytes&7)
			{
			case 7:*reinterpret_cast<structSize<7>*&>(pDestination) = *reinterpret_cast<structSize<7>*&>(const_cast<void*&>(pSource));return;
			case 6:*reinterpret_cast<structSize<6>*&>(pDestination) = *reinterpret_cast<structSize<6>*&>(const_cast<void*&>(pSource));return;
			case 5:*reinterpret_cast<structSize<5>*&>(pDestination) = *reinterpret_cast<structSize<5>*&>(const_cast<void*&>(pSource));return;
			case 4:*reinterpret_cast<structSize<4>*&>(pDestination) = *reinterpret_cast<structSize<4>*&>(const_cast<void*&>(pSource));return;
			case 3:*reinterpret_cast<structSize<3>*&>(pDestination) = *reinterpret_cast<structSize<3>*&>(const_cast<void*&>(pSource));return;
			case 2:*reinterpret_cast<structSize<2>*&>(pDestination) = *reinterpret_cast<structSize<2>*&>(const_cast<void*&>(pSource));return;
			case 1:*reinterpret_cast<structSize<1>*&>(pDestination) = *reinterpret_cast<structSize<1>*&>(const_cast<void*&>(pSource));return;
			}
		}
	//内存移动（内存复制的可能有重叠版本）
	void Memory::Move(void* pDestination,const void* pSource,size_t sizeInBytes)
		{
			if(reinterpret_cast<char*&>(pDestination)>reinterpret_cast<char*&>(const_cast<void*&>(pSource)))
			{//倒序复制
				reinterpret_cast<structSize<1>*&>(pDestination)+=sizeInBytes;
				reinterpret_cast<structSize<1>*&>(const_cast<void*&>(pSource))+=sizeInBytes;
				while(sizeInBytes>=8){*(--reinterpret_cast<structSize<8>*&>(pDestination)) = *(--reinterpret_cast<structSize<8>*&>(const_cast<void*&>(pSource)));sizeInBytes-=8;}
				switch(sizeInBytes&7)
				{
				case 7:*--reinterpret_cast<structSize<7>*&>(pDestination) = *--reinterpret_cast<structSize<7>*&>(const_cast<void*&>(pSource));return;
				case 6:*--reinterpret_cast<structSize<6>*&>(pDestination) = *--reinterpret_cast<structSize<6>*&>(const_cast<void*&>(pSource));return;
				case 5:*--reinterpret_cast<structSize<5>*&>(pDestination) = *--reinterpret_cast<structSize<5>*&>(const_cast<void*&>(pSource));return;
				case 4:*--reinterpret_cast<structSize<4>*&>(pDestination) = *--reinterpret_cast<structSize<4>*&>(const_cast<void*&>(pSource));return;
				case 3:*--reinterpret_cast<structSize<3>*&>(pDestination) = *--reinterpret_cast<structSize<3>*&>(const_cast<void*&>(pSource));return;
				case 2:*--reinterpret_cast<structSize<2>*&>(pDestination) = *--reinterpret_cast<structSize<2>*&>(const_cast<void*&>(pSource));return;
				case 1:*--reinterpret_cast<structSize<1>*&>(pDestination) = *--reinterpret_cast<structSize<1>*&>(const_cast<void*&>(pSource));return;
				}
				return;
			}
			while(sizeInBytes>=8){*(reinterpret_cast<structSize<8>*&>(pDestination)++) = *(reinterpret_cast<structSize<8>*&>(const_cast<void*&>(pSource))++);sizeInBytes-=8;}
			switch(sizeInBytes&7)
			{
			case 7:*reinterpret_cast<structSize<7>*&>(pDestination) = *reinterpret_cast<structSize<7>*&>(const_cast<void*&>(pSource));return;
			case 6:*reinterpret_cast<structSize<6>*&>(pDestination) = *reinterpret_cast<structSize<6>*&>(const_cast<void*&>(pSource));return;
			case 5:*reinterpret_cast<structSize<5>*&>(pDestination) = *reinterpret_cast<structSize<5>*&>(const_cast<void*&>(pSource));return;
			case 4:*reinterpret_cast<structSize<4>*&>(pDestination) = *reinterpret_cast<structSize<4>*&>(const_cast<void*&>(pSource));return;
			case 3:*reinterpret_cast<structSize<3>*&>(pDestination) = *reinterpret_cast<structSize<3>*&>(const_cast<void*&>(pSource));return;
			case 2:*reinterpret_cast<structSize<2>*&>(pDestination) = *reinterpret_cast<structSize<2>*&>(const_cast<void*&>(pSource));return;
			case 1:*reinterpret_cast<structSize<1>*&>(pDestination) = *reinterpret_cast<structSize<1>*&>(const_cast<void*&>(pSource));return;
			}
		}
	int Bits::LeftZeroCount64(unsigned long long i)
	{
	if(    i<0x0000000100000000)//很有意思的感觉，呵呵
	{	if(i<0x0000000000010000)
	{	if(i<0x0000000000000100)
	{	if(i<0x0000000000000010)
	{	if(i<0x0000000000000004)
	{	if(i<0x0000000000000002)return 64-(int)i;return 62;
	}	if(i<0x0000000000000008)return 61;return 60;
	}	if(i<0x0000000000000040)
	{	if(i<0x0000000000000020)return 59;return 58;
	}	if(i<0x0000000000000080)return 57;return 56;
	}	if(i<0x0000000000001000)
	{	if(i<0x0000000000000400)
	{	if(i<0x0000000000000200)return 55;return 54;
	}	if(i<0x0000000000000800)return 53;return 52;
	}	if(i<0x0000000000004000)
	{	if(i<0x0000000000002000)return 51;return 50;
	}	if(i<0x0000000000008000)return 49;return 48;
	}	if(i<0x0000000001000000)
	{	if(i<0x0000000000100000)
	{	if(i<0x0000000000040000)
	{	if(i<0x0000000000020000)return 47;return 46;
	}	if(i<0x0000000000080000)return 45;return 44;
	}	if(i<0x0000000000400000)
	{	if(i<0x0000000000200000)return 43;return 42;
	}	if(i<0x0000000000800000)return 41;return 40;
	}	if(i<0x0000000010000000)
	{	if(i<0x0000000004000000)
	{	if(i<0x0000000002000000)return 39;return 38;
	}	if(i<0x0000000008000000)return 37;return 36;
	}	if(i<0x0000000040000000)
	{	if(i<0x0000000020000000)return 35;return 34;
	}	if(i<0x0000000080000000)return 33;return 32;
	}	if(i<0x0001000000000000)
	{	if(i<0x0000010000000000)
	{	if(i<0x0000001000000000)
	{	if(i<0x0000000400000000)
	{	if(i<0x0000000200000000)return 31;return 30;
	}	if(i<0x0000000800000000)return 29;return 28;
	}	if(i<0x0000004000000000)
	{	if(i<0x0000002000000000)return 27;return 26;
	}	if(i<0x0000008000000000)return 25;return 24;
	}	if(i<0x0000100000000000)
	{	if(i<0x0000040000000000)
	{	if(i<0x0000020000000000)return 23;return 22;
	}	if(i<0x0000080000000000)return 21;return 20;
	}	if(i<0x0000400000000000)
	{	if(i<0x0000200000000000)return 19;return 18;
	}	if(i<0x0000800000000000)return 17;return 16;
	}	if(i<0x0100000000000000)
	{	if(i<0x0010000000000000)
	{	if(i<0x0004000000000000)
	{	if(i<0x0002000000000000)return 15;return 14;
	}	if(i<0x0008000000000000)return 13;return 12;
	}	if(i<0x0040000000000000)
	{	if(i<0x0020000000000000)return 11;return 10;
	}	if(i<0x0080000000000000)return 9;return 8;
	}	if(i<0x1000000000000000)
	{	if(i<0x0400000000000000)
	{	if(i<0x0200000000000000)return 7;return 6;
	}	if(i<0x0800000000000000)return 5;return 4;
	}	if(i<0x4000000000000000)
	{	if(i<0x2000000000000000)return 3;return 2;
	}	if(i<0x8000000000000000)return 1;return 0;
	}
	void Bits::Copy(void* pSource,unsigned startBitPosition,unsigned bitsCount,void* pDestination,unsigned destinationBitPosition)
	{//从pSource指向的内存的startBitPositon位起，复制bitsCount比特覆盖到pDestination的destinationBitPosition比特位置上
		if(!bitsCount || !pSource || !pDestination)return;
		if(startBitPosition>=8 || destinationBitPosition>=8)//使得操作首字节号都是0
			return Bits::Copy((unsigned char*)pSource+(startBitPosition>>3),startBitPosition&7,bitsCount,(unsigned char*)pDestination+(destinationBitPosition>>3),destinationBitPosition&7);
		unsigned int sourceBytes = (startBitPosition+bitsCount+7)>>3;//计算源数据涉及字节数
		unsigned int destinationBytes = (destinationBitPosition+bitsCount+7)>>3;//计算目标数据涉及字节数
		unsigned char c_start=*(unsigned char*)pDestination,c_end = *((unsigned char*)pDestination+destinationBytes-1);//临时字节,起始修饰和终止修饰
		short bitmov;//相对位移-7~+7，正为左移
		if(bitmov = destinationBitPosition - startBitPosition)//中间部分操作
		{
			if(bitmov<0)
			{
				unsigned int i(0);//从目标0字节写起
				while(i+7<destinationBytes)
				{
					*((unsigned long long*)((unsigned char*)pDestination+i)) = *((unsigned long long*)((unsigned char*)pSource+i))>>(-bitmov);
					i+=7;
				}
				while(i+3<destinationBytes)
				{
					*((unsigned int*)((unsigned char*)pDestination+i)) = *((unsigned int*)((unsigned char*)pSource+i))>>(-bitmov);
					i+=3;
				}
				while(i+1<sourceBytes)
				{
					*((unsigned char*)pDestination+i) = *((unsigned short*)((unsigned char*)pSource+i))>>(-bitmov);
					++i;
				}
				if(i<destinationBytes)*((unsigned char*)pDestination+i) = *((unsigned char*)pSource+i)>>(-bitmov);
			}
			else
			{
				unsigned int i(sourceBytes-1);//从目标末尾写起
				if(sourceBytes<destinationBytes)*((unsigned char*)pDestination+sourceBytes) = *((unsigned char*)pSource+sourceBytes-1)>>(8-bitmov);
				while(i>=7)
				{
					*((unsigned long long*)((unsigned char*)pDestination+i-7)) = *((unsigned long long*)((unsigned char*)pSource+i-7))<<bitmov;
					i-=7;
				}
				while(i>=3)
				{
					*((unsigned int*)((unsigned char*)pDestination+i-3)) = *((unsigned int*)((unsigned char*)pSource+i-3))<<bitmov;
					i-=3;
				}
				while(i>=1)
				{
					*((unsigned short*)((unsigned char*)pDestination+i-1)) = *((unsigned short*)((unsigned char*)pSource+i-1))<<bitmov;
					--i;
				}
				*(unsigned char*)pDestination= *(unsigned char*)pSource<<bitmov;
			}
		}
		else Memory::Copy(pDestination,pSource,destinationBytes);
		if(destinationBitPosition)//首端处理
			*(unsigned char*)pDestination = (c_start & (0xff>>(8-destinationBitPosition))) | (*(unsigned char*)pDestination & (0xff<<destinationBitPosition));
		if(bitsCount = (destinationBitPosition+bitsCount)&7)//尾端处理
			*((unsigned char*)pDestination+destinationBytes-1) = (c_end & (0xff<<bitsCount)) | (*((unsigned char*)pDestination+destinationBytes-1) & (0xff>>(8-bitsCount)));
	}
	void Bits::Set(void* p,unsigned startBitPosition,unsigned bitsCount,bool bitValue)//将p所指向的内存的startBitPosition比特起的bitsCount比特置为bit的值
	{
		if(startBitPosition>=8)return Bits::Set((unsigned char*)p+(startBitPosition>>3),startBitPosition&7,bitsCount,bitValue);
		unsigned int bytes = (startBitPosition+bitsCount+7)>>3;
		unsigned char c_start = *(unsigned char*)p;
		unsigned char c_end = *((unsigned char*)p+bytes-1);
		//中间字节处理
		if(bitValue)memset(p,0xff,bytes);
		else memset(p,0,bytes);
		//首字节处理
		if(startBitPosition)
			if(bitValue) *(unsigned char*)p &= c_start & (0xff>>(8-startBitPosition));
			else *(unsigned char*)p |=  c_start & (0xff>>(8-startBitPosition));
			//尾字节处理
			if(bitsCount = (bitsCount+startBitPosition) & 7)
			{
				if(bitValue)*((unsigned char*)p+bytes-1) &= c_end & (0xff << bitsCount);
				else *((unsigned char*)p+bytes-1) |= c_end & (0xff << bitsCount);
			}
	}
	bool Bits::Get(const void* pSource,long long bitPosition)
	{
		if(bitPosition<0)
		{
			return Get((unsigned char*)pSource + bitPosition/8-1,bitPosition%8==0?0:8+bitPosition%8);
		}
		if(bitPosition>=8)
		{
			return Get((unsigned char*)pSource + bitPosition/8,bitPosition%8);
		}
		switch(bitPosition)
		{
		case 7:return (*(unsigned char*)pSource & 0x80)>0;
		case 6:return (*(unsigned char*)pSource & 0x40)>0;
		case 5:return (*(unsigned char*)pSource & 0x20)>0;
		case 4:return (*(unsigned char*)pSource & 0x10)>0;
		case 3:return (*(unsigned char*)pSource & 0x08)>0;
		case 2:return (*(unsigned char*)pSource & 0x04)>0;
		case 1:return (*(unsigned char*)pSource & 0x02)>0;
		}
		return *(unsigned char*)pSource & 0x01;
	}
	void Bits::Move(void* p,unsigned startBitPosition,unsigned bitsCount,int mov)//将p指向的内存的startBitPosition比特位起bitsCount比特的数据进行mov比特位移，正为左移，负为右移
	{
		if(!p || !bitsCount || !mov)return;
		if(startBitPosition>=8)return Bits::Move((unsigned char*)p+(startBitPosition>>3),startBitPosition&7,bitsCount,mov);
		if(mov>(int)bitsCount || -mov>(int)bitsCount)return Bits::Set(p,startBitPosition,bitsCount,false);//过度位移
		unsigned int bytes = (startBitPosition+bitsCount+7)>>3;//影响字节数
		unsigned char c_start = *(unsigned char*)p;//起始字节
		unsigned char c_end = *((unsigned char*)p+bytes-1);//终止字节
		if(mov&7)
		{
			int Bmov = mov<0?(-mov)>>3:mov>>3;
			unsigned long long tmp;//临时数据存放
			if(mov>0)//左移
			{
				int i=bytes-Bmov;
				mov &= 7;
				while(i>7)
				{
					Memory::Copy(&tmp,(unsigned char*)p+i-8,8);
					tmp <<= mov;
					Memory::Copy((unsigned char*)p+i+Bmov-7,&tmp,7);
					i -= 7;
				}
				tmp = 0;
				Memory::Copy(&tmp,(unsigned char*)p,i);
				tmp <<= mov;
				Memory::Copy((unsigned char*)p+Bmov,&tmp,i);
				if(Bmov)memset(p,0,Bmov);
			}
			else//右移
			{
				int i=0;
				mov = (-mov)&7;
				while(i+Bmov+8<=(int)bytes)
				{
					Memory::Copy(&tmp,(unsigned char*)p+i+Bmov,8);
					tmp >>= mov;
					Memory::Copy((unsigned char*)p+i,&tmp,7);
					i += 7;
				}
				tmp = 0;
				Memory::Copy(&tmp,(unsigned char*)p+i+Bmov,bytes-i-Bmov);
				tmp >>= mov;
				Memory::Copy((unsigned char*)p+i,&tmp,bytes-i-Bmov);
				if(Bmov)memset((unsigned char*)p+bytes-Bmov,0,Bmov);
			}
		}
		else
		{
			mov>>=3;
			if(mov>0)//左移
			{
				int i=bytes-mov;
				while(i>=mov)
				{
					memcpy_s((unsigned char*)p+i,mov,(unsigned char*)p+i-mov,mov);
					i -= mov;
				}
				if(i)memcpy_s((unsigned char*)p+i,i,p,i);
				memset(p,0,mov);
			}
			else//右移
			{
				mov = -mov;
				int i=0;
				while(i+mov+mov<=(int)bytes)
				{
					Memory::Copy((unsigned char*)p+i,(unsigned char*)p+i+mov,mov);
					i += mov;
				}
				if(i+mov+mov<(int)bytes)Memory::Copy((unsigned char*)p+i,(unsigned char*)p+i+mov,bytes-i-mov);
				memset((unsigned char*)p+bytes-mov,0,mov);
			}
		}
		//首字节处理
		if(startBitPosition)
			*(unsigned char*)p |=  c_start & (0xff>>(8-startBitPosition));
		//尾字节处理
		if(bitsCount = (bitsCount+startBitPosition) & 7)
			*((unsigned char*)p+bytes-1) |= c_end & (0xff << bitsCount);
	}
	int Bits::Compare(void* pSource,unsigned startBitPositon,unsigned bitsCount,void* pDestination,unsigned destinationBitPosition)//比较两串二进制序列大小，从高位往低位比较
	{
		unsigned long long num1,num2;
		while(bitsCount)
		{
			if(bitsCount>=64)
			{Bits::Copy(pSource,startBitPositon+bitsCount-64,64,&num1);Bits::Copy(pDestination,destinationBitPosition+bitsCount-64,64,&num2);bitsCount-=64;}
			else{num1 = num2 = 0;Bits::Copy(pSource,startBitPositon,bitsCount,&num1);Bits::Copy(pDestination,destinationBitPosition,bitsCount,&num2);bitsCount=0;}
			if(num1>num2)return 1;
			if(num1<num2)return -1;
		}
		return 0;
	}



}