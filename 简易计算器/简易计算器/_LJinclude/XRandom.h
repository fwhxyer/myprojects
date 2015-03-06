#pragma once
#define XRANDOM_
namespace LJ
{
	//�����
	class XRandom:public XBase
	{
		unsigned char mr1,ml1,mr2,ml2,mr3,ml3;
		unsigned short baseValue;
	public:
		unsigned long long r1,r2,r3;
		//����ͨ�÷���
		XBaseVTypeMethods_H(XRandom);
		//������һ��ֵ�������õ������н��ǲ��̶���
		void SetNextRand(unsigned long long seed);
		//����׼��ʽ������һ��ֵ�������õ������н��ǹ̶���
		void SetNextRandStatic(unsigned long long seed);
		//Ĭ�Ϲ��죬ÿ�ι�������ж��п��ܲ�һ��
		XRandom();
		//ʹ��һ�����ӽ��г�ʼ�����൱�ڵ���SetNextRand()
		XRandom(unsigned long long seed);
		//��ȡһ��unsigned long long�����ֵ
		unsigned long long Rand();
		//��ȡһ��unsigned long long�����ֵ������̶Ƚ���Rand��
		unsigned long long SecretRand();
		//��ȡһ��[0,MaxValues::LongLong]�������
		signed long long NextInt64(){return Rand()&MaxValues::LongLong;}
		//��ȡһ��[minValue,maxValue]�������
		signed long long NextInt64(long long minValue,long long maxValue){return Rand()%unsigned long long(maxValue-minValue+1)+minValue;}
		//��ȡһ��[0,MaxValues::UnsignedLongLong]�������
		unsigned long long NextUInt64(){return Rand();}
		//��ȡһ��[minValue,maxValue]�������
		unsigned long long NextUInt64(long long minValue,long long maxValue){return Rand()%unsigned long long(maxValue-minValue+1)+minValue;}
		//��ȡһ��[0,1)�����С��
		double NextDouble();
		//��ȡһ��[minValue,maxValue)�����С��
		double NextDouble(double minValue,double maxValue){return (maxValue-minValue)*NextDouble()+minValue;}
		//��ȡһ��[0,2147483647]�������
		signed int NextInt();
		//��ȡһ��[minValue,maxValue]�������
		signed int NextInt(int minValue,int maxValue){return (int)NextInt64(minValue,maxValue);}
		//��ȡһ��[0,32767]�������
		signed short NextShort();
		//��ȡһ��[minValue,maxValue]�������
		signed short NextShort(short minValue,short maxValue){return (short)NextInt64(minValue,maxValue);}
		//��ȡһ��[0,127]�������
		signed char NextChar();
		//��ȡһ��[minValue,maxValue]�������
		signed char NextChar(char minValue,char maxValue){return (char)NextInt64(minValue,maxValue);}
		//��ȡһ���޷���Int�������
		unsigned int NextUInt();
		//��ȡһ��[minValue,maxValue]�������
		unsigned int NextUInt(unsigned int minValue,unsigned int maxValue){return (unsigned int)NextUInt64(minValue,maxValue);}
		unsigned short NextUShort();
		//��ȡһ��[minValue,maxValue]�������
		unsigned short NextUShort(unsigned short minValue,unsigned short maxValue){return (unsigned short)NextUInt64(minValue,maxValue);}
		unsigned char NextUChar();
		//��ȡһ��[minValue,maxValue]�������
		unsigned char NextUChar(unsigned char minValue,unsigned char maxValue){return (unsigned char)NextUInt64(minValue,maxValue);}
		//long long�Զ�ת��
		operator unsigned long long()const;
		//Ĭ�ϵ��������
		static XRandom Default;
		//����Ĭ������
		static XRandom MakeDefaultXRandom();
#ifdef _CLR //�й�֧��
		//���й��������ʼ��
		XRandom& operator=(System::Random^);
#endif
	};
}