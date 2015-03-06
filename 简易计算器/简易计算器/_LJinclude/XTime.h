#pragma once//������W�Ⲩ(LuoJun)��д
#define XTIME_
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_//�����windows.h�ų�WinSock�ɰ汾
#else
#define ALREADY_WINSOCKAPI_
#endif
#include <windows.h>
#ifndef ALREADY_WINSOCKAPI_
#undef _WINSOCKAPI_
#endif
#undef ALREADY_WINSOCKAPI_
namespace LJ
{
	class XTime:public XBase//XTime���ʾ���Ǵӹ�ԪԪ��Ԫ��1���賿���ʱ��ʱ�䳤�ȣ���100nsΪ��λ
	{
	protected:
		//��ȡ��ԪԪ����ָ��������������
		static long long GetDays(unsigned year,unsigned int month,unsigned int day);
		//������ݺ͵����ѹ�������ȡ�·ݣ��������������Ϊ�����
		static unsigned int GetMonthByDaysInYear(unsigned year,unsigned int& days);
		//���õ�ǰ�ı���ʱ��
		static void SetLocal(const XTime& now);
		//ͬʱ��ȡ��ݺ�������
		unsigned int GetYearAndDaysInYear(unsigned int*)const;
	public:
		//����ƫ��
		PROPERTY_OFFSET(XTime,Year);
		//ͨ�û��෽��
		XBaseVTypeMethods_H(XTime);
		//����
		virtual void SwapWith(XBase& x){XBase::SwapWith(x);return SwapWith(reinterpret_cast<XTime&>(x));}
		//����
		void SwapWith(XTime& x){Swap(time,x.time);}
		//��ȡ��ǰ�ı���ʱ��
		static XTime GetLocal();
		//��ȡCPUʱ��
		static inline LARGE_INTEGER& CpuCounterReference()
		{
			static LARGE_INTEGER f = {0};
			QueryPerformanceCounter(&f);
			return f;
		}
		//ÿ΢���ʱ��
		const static long long EveryMicrosecond = 10;
		//ÿ����ʱ�䳤��
		const static long long EveryMillisecond = 10000;
		//ÿ��ʱ�䳤��
		const static long long EverySecond = 10000000;
		//ÿ��ʱ�䳤��
		const static long long EveryMinute = 600000000;
		//ÿСʱʱ�䳤��
		const static long long EveryHour = 36000000000;
		//ÿ��ʱ�䳤��
		const static long long EveryDay = 864000000000;
		//ÿ��ʱ�䳤��
		const static long long EveryWeek = 6048000000000;
		//ȡ��
		unsigned int GetYear()const;
		//ȡ��
		unsigned int GetMonth()const;
		//ȡ��
		unsigned int GetDay()const;
		//��ȡ���ڼ���0���������죩
		unsigned int GetDayOfWeek()const;
		//ȡʱ
		unsigned int GetHour()const;
		//ȡ��
		unsigned int GetMinute()const;
		//ȡ��
		unsigned int GetSecond()const;
		//ȡ����
		unsigned int GetMillisecond()const;
		//ȡ΢��
		unsigned int GetMicrosecond()const;
		//������
		void SetYear(unsigned int);
		//������
		void SetMonth(unsigned int);
		//������
		void SetDay(unsigned int);
		//����ʱ
		void SetHour(unsigned int);
		//���÷�
		void SetMinute(unsigned int);
		//������
		void SetSecond(unsigned int);
		//���ú���
		void SetMillisecond(unsigned int);
		//����΢��
		void SetMicrosecond(unsigned int);
		union
		{
			//ʹ��һ��64λ�з�����������¼ʱ�䣬��λ100ns
			long long time;
			//��д���ԣ���
			PROPERTY_GETSET(unsigned int,XTime,GetYear,SetYear,Year);
			//��д���ԣ���
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Month);
			//��д���ԣ���
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Day);
			//ֻ�����ԣ�����
			PROPERTY_GET(unsigned int,XTime,GetMonth,DayOfWeek);
			//��д���ԣ�ʱ
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Hour);
			//��д���ԣ���
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Minute);
			//��д���ԣ���
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Second);
			//��д���ԣ�����
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Millisecond);
			//��д���ԣ�΢��
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Microsecond);
		};
		//Ĭ�Ϲ��캯��
		XTime();
		//���ַ�������
		XTime(const XString&str);
		//ʹ��һ������ֵ����ʼ��
		XTime(long long t);
		//ʹ��һ��WindowsAPI�����ϵͳʱ������ʼ��
		XTime(const ::SYSTEMTIME& t);
		//���ԣ���ǰʱ��
		static StaticProperty<XTime> Now;
		//��ȡ��԰Ԫ������ʱ���ѹ�����(����Ϊ��)
		int GetDays()const;
		//��ȡ��԰Ԫ������ʱ���ѹ�Сʱ��(����Ϊ��)
		int GetHours()const;
		//��ȡ��԰Ԫ������ʱ���ѹ�����(����Ϊ��)
		long long GetMinutes()const;
		//��ȡ��԰Ԫ������ʱ���ѹ�����(����Ϊ��)
		long long GetSeconds()const;
		//��ȡ��԰Ԫ������ʱ���ѹ�������(����Ϊ��)
		long long GetMilliseconds()const;
		//��ȡ��԰Ԫ������ʱ���ѹ�΢����(����Ϊ��)
		long long GetMicroseconds()const;
		//ȡʱ��ֵ��ʮ��֮һ΢��Ϊ��λ����Թ�ԪԪ�꣩
		operator long long()const;
		//ת��ΪWindowsAPI��ϵͳʱ��
		operator ::SYSTEMTIME()const;

		//�������������
		XTime&operator+=(long long t){time+=t;return *this;} 
		//�������������
		XTime&operator-=(long long t){time-=t;return *this;}
		//�������������
		XTime&operator%=(long long t){time%=t;return *this;}
		//�������������
		XTime&operator*=(long long t){time*=t;return *this;}
		//�������������
		XTime friend operator+(const XTime t1,const XTime t2){return XTime(t1.time+t2.time);}
		//�������������
		XTime friend operator-(const XTime t1,const XTime t2){return XTime(t1.time-t2.time);}

		//��ֵ����
		XTime& operator=(const XTime& t);
		//��ֵ����
		XTime& operator=(long long t);
		//��ֵ����
		XTime& operator=(const ::SYSTEMTIME& t);

		//�̹߳���һ��ʱ�䣬ע�⣬�÷�����Ҫ����ʵ��������Sleep
		void Wait(const XTime& t);

		//���ַ�����ת����ʱ�䳤�ȣ�����дXBase::ToString()
		virtual XString ToString()const;
		//���ַ�����ת������ʽ����
		XString ToString(const XString&)const;
#ifdef _CLR //�й�֧��
		//���йܵ�ʱ��ת��
		XTime(System::DateTime^time);
		//ת�����йܵ�ʱ��
		System::DateTime^ ToDateTime()const;
		//ʹ���йܵ�DateTime�ķ���
#endif
	};
}