#include "stdafx.h"
namespace LJ
{
	const float MaxValues::Float = 3.402823466e+38F;
	const double MaxValues::Double = 1.7976931348623158e+308;
	const float MinValues::Float = 1.175494351e-38F;
	const double MinValues::Double = 2.2250738585072014e-308;

	//XBase
	//���Ӹö������õĴ�����Ӧ����ԭ�Ӳ��������ظö���ָ�롣���referenceCountС��0����÷�������NULL���������ü�������
	XBase* XBase::ReferenceIncrement()const
	{
		if(referenceCount<0)return NULL;
		InterlockedIncrement(&referenceCount);
		return const_cast<XBase*>(this);
	}
	//���ٸö������õĴ�����Ӧ����ԭ�Ӳ�����������ü�������СΪ0���������ɾ������
	void XBase::ReferenceDecrement()const
	{
		if(0==InterlockedDecrement(&referenceCount))
			delete const_cast<XBase*>(this);
	}
	//��ȡָ������ã���IsNull()ʱ�����ø÷������׳��쳣
	XBase* XBase::Pointer()const{if(pObject==NULL)throw XException(L"������Ϊ�ջ�Ƿ���",E_POINTER);return pObject;}
	//ȡ��ַ
	XBase*XBase::operator&(){if(referenceCount==0)ReferenceIncrement();return this;}
	const XBase*XBase::operator&()const{if(referenceCount==0)ReferenceIncrement();return this;}
	//������Ϣ
	const XTypes& XBase::CurrentType = NodeOfRoot::Add(L"LJ::XBase",Types<LJ::XBase>());
	//��ȡ����������Ϣ
	const XTypes& XBase::GetType()const
	{
		return CurrentType;
	}
	//�Ƚϸö�����object�����Ƿ���ͬһ������
	bool XBase::Equals(const XBase& object)const
	{
		return this == object.ThisPointer();
	}
	//����ö�����ַ�������
	XString XBase::ToString()const
	{
		return GetType().GetFullName();
	}
	//�жϸö����Ƿ�Ϊ�����ã�����pObjectΪNULLʱ����true��
	bool XBase::IsNull()const
	{
		return !pObject;
	}
	void XBase::SwapWith(XBase& x)
	{
		if(GetType()!=x.GetType())throw XException(L"ָ���Ľ��������뵱ǰ�������Ͳ�һ��",E_INVALIDARG);
		if(pObject!=this){XBase*tmp = pObject;pObject=x.pObject;x.pObject=tmp;}//ֻ����ָ��
	}
	//�жϸö����Ƿ���Ա����ã����referenceCountС��0�򷵻�false
	bool XBase::CanBeReferenced()const
	{
		return referenceCount>=0;
	}
	//�жϸö����Ƿ��������ս�㣨��ԭʼֵ�������pObjectָ�������򷵻�true
	bool XBase::IsReferenceEnding()const
	{
		return pObject==this;
	}
	//�ж϶�����object�������õ��Ƿ���ͬһ�����󣬼�pObject���ʱ����true
	bool XBase::ReferenceEquals(const XBase& object)const
	{
		return pObject==object.pObject;
	}
	//��ֵ
	XBase& XBase::operator=(const XBase& xbase)
	{
		if(this == xbase.ThisPointer())return *this;
		//����Ϊԭʼֵ�����ܱ�Ϊ����
		if(this == pObject)
		{
			//ֱ�ӷ���
			return *this;
		}
		//����Ϊ���ã����referenceCount<0�������Ϊ���������
		if(referenceCount<0)
		{
			//����Է������Լ����׳��쳣��ʵ���ϲ����ܷ�����
			if(xbase.pObject==this)throw XException(L"��⵽��ʵ�����Ƿ����á�",E_INVALIDARG);
		}
		if(pObject)pObject->ReferenceDecrement();
		pObject = xbase.pObject;
		if(pObject)pObject->ReferenceIncrement();
		return *this;
	}
	//Ĭ�Ϲ��캯������������Ϊ0��ָ��ΪNULL��Ҳ���Ǹ�ʵ��Ĭ�ϼ����Ա����ã��ֿ�����������ʵ��
	XBase::XBase()
		:referenceCount(0),pObject(NULL)
	{}
	//����һ�������������ظø�����ָ��
	XBase* XBase::NewCopy()const
	{
		return new XBase(*this);
	}
	//ʹ��ָ����ָ������ü���������
	XBase::XBase(XBase*x,long refCount)
		:referenceCount(refCount),pObject(x)
	{}
	//ʹ��һ��ָ��������һ�����ã��ù����Ƿ��̰߳�ȫ��
	XBase::XBase(XBase* pBase)
		:pObject(pBase),referenceCount(0)
	{
		if(pObject)
		{
			if(pObject->referenceCount<0)
			{
				pObject = NULL;
				throw XException(L"ָ���Ķ����޷������á�",E_INVALIDARG);
			}
			pObject->ReferenceIncrement();//�������ü�����ֵ��ע������벻Ҫͨ���Ծֲ�����ȡ��ַ����������
		}
	}
	//���ƹ��캯��
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
					throw XException(L"ָ���Ķ����޷������á�",E_INVALIDARG);
				}
				pObject->ReferenceIncrement();
			}
		}
	}
	//��ֵ���ƹ��캯��
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
					throw XException(L"ָ���Ķ����޷������á�",E_INVALIDARG);
				}
				const_cast<XBase*&>(xBase.pObject)=NULL;
			}
		}
	}
#endif
	//������������ʹ�ø�����Ա��̳�
	XBase::~XBase()
	{
		if(pObject && pObject!=this)
		{
			pObject->ReferenceDecrement();
		}
	}
	//�ڴ渴��,pDestinationָ��Ŀ���ڴ棬pSourceָ��Դ���ݣ�sizeInBytes�ǰ��ֽ�����ʾ�Ĵ�С��Դ��������Ŀ���ڴ治���ص�
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
	//�ڴ��ƶ����ڴ渴�ƵĿ������ص��汾��
	void Memory::Move(void* pDestination,const void* pSource,size_t sizeInBytes)
		{
			if(reinterpret_cast<char*&>(pDestination)>reinterpret_cast<char*&>(const_cast<void*&>(pSource)))
			{//������
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
	if(    i<0x0000000100000000)//������˼�ĸо����Ǻ�
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
	{//��pSourceָ����ڴ��startBitPositonλ�𣬸���bitsCount���ظ��ǵ�pDestination��destinationBitPosition����λ����
		if(!bitsCount || !pSource || !pDestination)return;
		if(startBitPosition>=8 || destinationBitPosition>=8)//ʹ�ò������ֽںŶ���0
			return Bits::Copy((unsigned char*)pSource+(startBitPosition>>3),startBitPosition&7,bitsCount,(unsigned char*)pDestination+(destinationBitPosition>>3),destinationBitPosition&7);
		unsigned int sourceBytes = (startBitPosition+bitsCount+7)>>3;//����Դ�����漰�ֽ���
		unsigned int destinationBytes = (destinationBitPosition+bitsCount+7)>>3;//����Ŀ�������漰�ֽ���
		unsigned char c_start=*(unsigned char*)pDestination,c_end = *((unsigned char*)pDestination+destinationBytes-1);//��ʱ�ֽ�,��ʼ���κ���ֹ����
		short bitmov;//���λ��-7~+7����Ϊ����
		if(bitmov = destinationBitPosition - startBitPosition)//�м䲿�ֲ���
		{
			if(bitmov<0)
			{
				unsigned int i(0);//��Ŀ��0�ֽ�д��
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
				unsigned int i(sourceBytes-1);//��Ŀ��ĩβд��
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
		if(destinationBitPosition)//�׶˴���
			*(unsigned char*)pDestination = (c_start & (0xff>>(8-destinationBitPosition))) | (*(unsigned char*)pDestination & (0xff<<destinationBitPosition));
		if(bitsCount = (destinationBitPosition+bitsCount)&7)//β�˴���
			*((unsigned char*)pDestination+destinationBytes-1) = (c_end & (0xff<<bitsCount)) | (*((unsigned char*)pDestination+destinationBytes-1) & (0xff>>(8-bitsCount)));
	}
	void Bits::Set(void* p,unsigned startBitPosition,unsigned bitsCount,bool bitValue)//��p��ָ����ڴ��startBitPosition�������bitsCount������Ϊbit��ֵ
	{
		if(startBitPosition>=8)return Bits::Set((unsigned char*)p+(startBitPosition>>3),startBitPosition&7,bitsCount,bitValue);
		unsigned int bytes = (startBitPosition+bitsCount+7)>>3;
		unsigned char c_start = *(unsigned char*)p;
		unsigned char c_end = *((unsigned char*)p+bytes-1);
		//�м��ֽڴ���
		if(bitValue)memset(p,0xff,bytes);
		else memset(p,0,bytes);
		//���ֽڴ���
		if(startBitPosition)
			if(bitValue) *(unsigned char*)p &= c_start & (0xff>>(8-startBitPosition));
			else *(unsigned char*)p |=  c_start & (0xff>>(8-startBitPosition));
			//β�ֽڴ���
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
	void Bits::Move(void* p,unsigned startBitPosition,unsigned bitsCount,int mov)//��pָ����ڴ��startBitPosition����λ��bitsCount���ص����ݽ���mov����λ�ƣ���Ϊ���ƣ���Ϊ����
	{
		if(!p || !bitsCount || !mov)return;
		if(startBitPosition>=8)return Bits::Move((unsigned char*)p+(startBitPosition>>3),startBitPosition&7,bitsCount,mov);
		if(mov>(int)bitsCount || -mov>(int)bitsCount)return Bits::Set(p,startBitPosition,bitsCount,false);//����λ��
		unsigned int bytes = (startBitPosition+bitsCount+7)>>3;//Ӱ���ֽ���
		unsigned char c_start = *(unsigned char*)p;//��ʼ�ֽ�
		unsigned char c_end = *((unsigned char*)p+bytes-1);//��ֹ�ֽ�
		if(mov&7)
		{
			int Bmov = mov<0?(-mov)>>3:mov>>3;
			unsigned long long tmp;//��ʱ���ݴ��
			if(mov>0)//����
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
			else//����
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
			if(mov>0)//����
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
			else//����
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
		//���ֽڴ���
		if(startBitPosition)
			*(unsigned char*)p |=  c_start & (0xff>>(8-startBitPosition));
		//β�ֽڴ���
		if(bitsCount = (bitsCount+startBitPosition) & 7)
			*((unsigned char*)p+bytes-1) |= c_end & (0xff << bitsCount);
	}
	int Bits::Compare(void* pSource,unsigned startBitPositon,unsigned bitsCount,void* pDestination,unsigned destinationBitPosition)//�Ƚ��������������д�С���Ӹ�λ����λ�Ƚ�
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