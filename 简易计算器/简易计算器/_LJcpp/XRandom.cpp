#include "stdafx.h"
#ifdef XRANDOM_
namespace LJ
{

	const XTypes& XRandom::CurrentType = CREATECLASSTYPE(LJ::XRandom,LJ::XBase);
	XRandom XRandom::MakeDefaultXRandom()
	{
		XBase tmp;
		char* p = new char[sizeof(XRandom)];
		XBase::Memory::Copy(p,&tmp,sizeof(tmp));
		XRandom t = *((XRandom*)p);
		delete []p;
		t.SetNextRand(XTime::GetLocal());
		do{
		t.ml1 = (t.Rand()&62)+1;t.mr1 = 64 - t.ml1;
		t.ml2 = (t.Rand()&62)+1;t.mr2 = 64 - t.ml2;
		t.ml3 = (t.Rand()&62)+1;t.mr3 = 64 - t.ml3;
		if(t.r1==0 && t.r2==0 && t.r3==0)t.r1=t.r2=t.r3=XTime::GetLocal();
		}while(t.ml1==t.ml2 || t.ml2==t.ml3 || t.ml1==t.ml3);
		return t;
	}
	XRandom::XRandom()
	{
		SetNextRand(Default);
		do{
		ml1 = (Rand()&62)+1;mr1 = 64 - ml1;
		ml2 = (Rand()&62)+1;mr2 = 64 - ml2;
		ml3 = (Rand()&62)+1;mr3 = 64 - ml3;
		if(r1==0 && r2==0 && r3==0)r1=r2=r3=XTime::GetLocal();
		}while(ml1==ml2 || ml2==ml3 || ml1==ml3);
	}
	XRandom::XRandom(unsigned long long seed)
	{
		SetNextRand(seed);
		do{
		ml1 = (Rand()&62)+1;mr1 = 64 - ml1;
		ml2 = (Rand()&62)+1;mr2 = 64 - ml2;
		ml3 = (Rand()&62)+1;mr3 = 64 - ml3;
		if(r1==0 && r2==0 && r3==0)r1=r2=r3=XTime::GetLocal();
		}while(ml1==ml2 || ml2==ml3 || ml1==ml3);
	}
	void XRandom::SetNextRand(unsigned long long seed)
	{
		long long time = XTime::GetLocal();
		baseValue = (unsigned short)XTime::CpuCounterReference().QuadPart;
		r2 = (time>>11)^(time<<53);
		r3 = (seed-baseValue)^r2^r1;
	}
	void XRandom::SetNextRandStatic(unsigned long long seed)
	{
		baseValue = 0;
		r1 = 0;
		r2 = 1;
		r3 = seed^1;
		ml1 = 13;mr1 = 64 - ml1;
		ml2 = 3;mr2 = 64 - ml2;
		ml3 = 23;mr3 = 64 - ml3;
	}
	unsigned long long XRandom::Rand()
	{
		if(r1==0 && r2==0 && r3==0)*this = MakeDefaultXRandom();
		unsigned long long t(r1^r2^r3);
		r1 = ((r1<<ml1) | (r1>>mr1)) + r2;
		r2 = ((r2<<ml2) | (r2>>mr2)) + r3;
		r3 = ((r3<<ml3) | (r3>>mr3)) + r1;
		return t+baseValue;
	}
	unsigned long long XRandom::SecretRand()
	{
		if(r1==0 && r2==0 && r3==0)*this = MakeDefaultXRandom();
		unsigned long long t(r1^r2^r3);
		r1 = ((r1<<ml1) | (r1>>mr1)) + r2;
		r2 = ((r2<<ml2) | (r2>>mr2)) + r3;
		r3 = ((r3<<ml3) | (r3>>mr3)) + r1;
		return t+baseValue+XTime::CpuCounterReference().QuadPart;
	}
	XRandom::operator unsigned long long()const
	{
		return const_cast<XRandom*>(this)->Rand();
	}

	double XRandom::NextDouble()
	{
		unsigned long long tmp = Rand();
		if(tmp<0xfff)return 0;
		int zerocount = Bits::LeftZeroCount64(tmp);
		tmp ^= unsigned long long(1) << (63^zerocount);
		if(zerocount<11)tmp>>=(11-zerocount);
		else if(zerocount>11)tmp = (tmp<<(zerocount-11)) | (Rand()>>(64-(zerocount-11)));
		tmp |= unsigned long long(1022-zerocount)<<52;
		return *(double*)&tmp;
	}
	//获取一个[0,2147483647]的随机数
	signed int XRandom::NextInt()
	{
		return 0x7fffffff&Rand();
	}
	//获取一个[0,32767]的随机数
	signed short XRandom::NextShort()
	{
		return 0x7fff&Rand();
	}
	//获取一个[0,127]的随机数
	signed char XRandom::NextChar()
	{
		return 0x7f&Rand();
	}
	unsigned int XRandom::NextUInt()
	{
		return unsigned int(Rand());
	}
	unsigned short XRandom::NextUShort()
	{
		return unsigned short(Rand());
	}
	unsigned char XRandom::NextUChar()
	{
		return unsigned char(Rand());
	}
#ifdef _CLR //托管支持
		XRandom& XRandom::operator=(System::Random^r)
		{
			SetNextRand(unsigned long long(r->NextDouble()*XBase::MaxValues::UnsignedLongLong));
			return *this;
		}
#endif
}
#endif