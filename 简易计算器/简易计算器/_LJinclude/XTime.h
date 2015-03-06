#pragma once//该类由W意波(LuoJun)编写
#define XTIME_
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_//这里的windows.h排除WinSock旧版本
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
	class XTime:public XBase//XTime类表示的是从公元元年元月1日凌晨起计时的时间长度，以100ns为单位
	{
	protected:
		//获取公元元年至指定年月日总天数
		static long long GetDays(unsigned year,unsigned int month,unsigned int day);
		//根据年份和当年已过天数获取月份，输入的天数将变为日输出
		static unsigned int GetMonthByDaysInYear(unsigned year,unsigned int& days);
		//设置当前的本地时间
		static void SetLocal(const XTime& now);
		//同时获取年份和年天数
		unsigned int GetYearAndDaysInYear(unsigned int*)const;
	public:
		//属性偏移
		PROPERTY_OFFSET(XTime,Year);
		//通用基类方法
		XBaseVTypeMethods_H(XTime);
		//交换
		virtual void SwapWith(XBase& x){XBase::SwapWith(x);return SwapWith(reinterpret_cast<XTime&>(x));}
		//交换
		void SwapWith(XTime& x){Swap(time,x.time);}
		//获取当前的本地时间
		static XTime GetLocal();
		//获取CPU时钟
		static inline LARGE_INTEGER& CpuCounterReference()
		{
			static LARGE_INTEGER f = {0};
			QueryPerformanceCounter(&f);
			return f;
		}
		//每微秒的时长
		const static long long EveryMicrosecond = 10;
		//每毫秒时间长度
		const static long long EveryMillisecond = 10000;
		//每秒时间长度
		const static long long EverySecond = 10000000;
		//每分时间长度
		const static long long EveryMinute = 600000000;
		//每小时时间长度
		const static long long EveryHour = 36000000000;
		//每天时间长度
		const static long long EveryDay = 864000000000;
		//每周时间长度
		const static long long EveryWeek = 6048000000000;
		//取年
		unsigned int GetYear()const;
		//取月
		unsigned int GetMonth()const;
		//取日
		unsigned int GetDay()const;
		//获取星期几（0代表星期天）
		unsigned int GetDayOfWeek()const;
		//取时
		unsigned int GetHour()const;
		//取分
		unsigned int GetMinute()const;
		//取秒
		unsigned int GetSecond()const;
		//取毫秒
		unsigned int GetMillisecond()const;
		//取微秒
		unsigned int GetMicrosecond()const;
		//设置年
		void SetYear(unsigned int);
		//设置月
		void SetMonth(unsigned int);
		//设置日
		void SetDay(unsigned int);
		//设置时
		void SetHour(unsigned int);
		//设置分
		void SetMinute(unsigned int);
		//设置秒
		void SetSecond(unsigned int);
		//设置毫秒
		void SetMillisecond(unsigned int);
		//设置微秒
		void SetMicrosecond(unsigned int);
		union
		{
			//使用一个64位有符号数字来记录时间，单位100ns
			long long time;
			//读写属性：年
			PROPERTY_GETSET(unsigned int,XTime,GetYear,SetYear,Year);
			//读写属性：月
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Month);
			//读写属性：日
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Day);
			//只读属性：星期
			PROPERTY_GET(unsigned int,XTime,GetMonth,DayOfWeek);
			//读写属性：时
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Hour);
			//读写属性：分
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Minute);
			//读写属性：秒
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Second);
			//读写属性：毫秒
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Millisecond);
			//读写属性：微秒
			PROPERTY_GETSET(unsigned int,XTime,GetMonth,SetMonth,Microsecond);
		};
		//默认构造函数
		XTime();
		//从字符串构造
		XTime(const XString&str);
		//使用一个整数值来初始化
		XTime(long long t);
		//使用一个WindowsAPI定义的系统时间来初始化
		XTime(const ::SYSTEMTIME& t);
		//属性：当前时间
		static StaticProperty<XTime> Now;
		//获取公园元年至该时间已过天数(可能为负)
		int GetDays()const;
		//获取公园元年至该时间已过小时数(可能为负)
		int GetHours()const;
		//获取公园元年至该时间已过分数(可能为负)
		long long GetMinutes()const;
		//获取公园元年至该时间已过秒数(可能为负)
		long long GetSeconds()const;
		//获取公园元年至该时间已过毫秒数(可能为负)
		long long GetMilliseconds()const;
		//获取公园元年至该时间已过微秒数(可能为负)
		long long GetMicroseconds()const;
		//取时间值，十分之一微秒为单位（相对公元元年）
		operator long long()const;
		//转换为WindowsAPI的系统时间
		operator ::SYSTEMTIME()const;

		//重载算数运算符
		XTime&operator+=(long long t){time+=t;return *this;} 
		//重载算数运算符
		XTime&operator-=(long long t){time-=t;return *this;}
		//重载算数运算符
		XTime&operator%=(long long t){time%=t;return *this;}
		//重载算数运算符
		XTime&operator*=(long long t){time*=t;return *this;}
		//重载算数运算符
		XTime friend operator+(const XTime t1,const XTime t2){return XTime(t1.time+t2.time);}
		//重载算数运算符
		XTime friend operator-(const XTime t1,const XTime t2){return XTime(t1.time-t2.time);}

		//赋值运算
		XTime& operator=(const XTime& t);
		//赋值运算
		XTime& operator=(long long t);
		//赋值运算
		XTime& operator=(const ::SYSTEMTIME& t);

		//线程挂起一段时间，注意，该方法主要用于实现连续的Sleep
		void Wait(const XTime& t);

		//到字符串的转换（时间长度），重写XBase::ToString()
		virtual XString ToString()const;
		//到字符串的转换（格式化）
		XString ToString(const XString&)const;
#ifdef _CLR //托管支持
		//从托管的时间转换
		XTime(System::DateTime^time);
		//转换到托管的时间
		System::DateTime^ ToDateTime()const;
		//使用托管的DateTime的方法
#endif
	};
}