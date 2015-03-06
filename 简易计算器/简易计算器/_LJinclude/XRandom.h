#pragma once
#define XRANDOM_
namespace LJ
{
	//随机数
	class XRandom:public XBase
	{
		unsigned char mr1,ml1,mr2,ml2,mr3,ml3;
		unsigned short baseValue;
	public:
		unsigned long long r1,r2,r3;
		//基类通用方法
		XBaseVTypeMethods_H(XRandom);
		//设置下一个值，这样得到的序列将是不固定的
		void SetNextRand(unsigned long long seed);
		//按标准形式设置下一个值，这样得到的序列将是固定的
		void SetNextRandStatic(unsigned long long seed);
		//默认构造，每次构造的序列都有可能不一样
		XRandom();
		//使用一个种子进行初始化，相当于调用SetNextRand()
		XRandom(unsigned long long seed);
		//获取一个unsigned long long型随机值
		unsigned long long Rand();
		//获取一个unsigned long long型随机值，随机程度将比Rand高
		unsigned long long SecretRand();
		//获取一个[0,MaxValues::LongLong]的随机数
		signed long long NextInt64(){return Rand()&MaxValues::LongLong;}
		//获取一个[minValue,maxValue]的随机数
		signed long long NextInt64(long long minValue,long long maxValue){return Rand()%unsigned long long(maxValue-minValue+1)+minValue;}
		//获取一个[0,MaxValues::UnsignedLongLong]的随机数
		unsigned long long NextUInt64(){return Rand();}
		//获取一个[minValue,maxValue]的随机数
		unsigned long long NextUInt64(long long minValue,long long maxValue){return Rand()%unsigned long long(maxValue-minValue+1)+minValue;}
		//获取一个[0,1)的随机小数
		double NextDouble();
		//获取一个[minValue,maxValue)的随机小数
		double NextDouble(double minValue,double maxValue){return (maxValue-minValue)*NextDouble()+minValue;}
		//获取一个[0,2147483647]的随机数
		signed int NextInt();
		//获取一个[minValue,maxValue]的随机数
		signed int NextInt(int minValue,int maxValue){return (int)NextInt64(minValue,maxValue);}
		//获取一个[0,32767]的随机数
		signed short NextShort();
		//获取一个[minValue,maxValue]的随机数
		signed short NextShort(short minValue,short maxValue){return (short)NextInt64(minValue,maxValue);}
		//获取一个[0,127]的随机数
		signed char NextChar();
		//获取一个[minValue,maxValue]的随机数
		signed char NextChar(char minValue,char maxValue){return (char)NextInt64(minValue,maxValue);}
		//获取一个无符号Int型随机数
		unsigned int NextUInt();
		//获取一个[minValue,maxValue]的随机数
		unsigned int NextUInt(unsigned int minValue,unsigned int maxValue){return (unsigned int)NextUInt64(minValue,maxValue);}
		unsigned short NextUShort();
		//获取一个[minValue,maxValue]的随机数
		unsigned short NextUShort(unsigned short minValue,unsigned short maxValue){return (unsigned short)NextUInt64(minValue,maxValue);}
		unsigned char NextUChar();
		//获取一个[minValue,maxValue]的随机数
		unsigned char NextUChar(unsigned char minValue,unsigned char maxValue){return (unsigned char)NextUInt64(minValue,maxValue);}
		//long long自动转换
		operator unsigned long long()const;
		//默认的随机算子
		static XRandom Default;
		//创建默认算子
		static XRandom MakeDefaultXRandom();
#ifdef _CLR //托管支持
		//从托管随机数初始化
		XRandom& operator=(System::Random^);
#endif
	};
}