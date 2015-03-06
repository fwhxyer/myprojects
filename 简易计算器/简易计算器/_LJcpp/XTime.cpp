#include "stdafx.h"//��W�Ⲩ(LuoJun)��д����ɳʮ�����ṩ�޸����
#ifdef XTIME_
namespace LJ
{
	//��ȡ��ǰ����

	const XTypes& XTime::CurrentType = CREATECLASSTYPE(LJ::XTime,LJ::XBase);

	long long XTime::GetDays(unsigned year,unsigned int month,unsigned int day)
	{
		if(year%400==0||year%4==0&&year%100!=0)//����
		{
			static unsigned short months[13] = {0,0,31,60,91,121,152,182,213,244,274,305,335};
			return months[month] + day + year*365-366 + (year-1)/4 - (year-1)/100 + (year-1)/400;
		}
		static unsigned short months[13] = {0,0,31,59,90,120,151,181,212,243,273,304,334};
		return months[month] + day + year*365-366 + (year-1)/4 - (year-1)/100 + (year-1)/400;
	}
	unsigned int XTime::GetMonthByDaysInYear(unsigned year,unsigned int& days)
	{
		unsigned int day = days;
		if(year%400==0||year%4==0&&year%100!=0)//����
		{
			static unsigned char d[366] =
			{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
			static unsigned char m[366] = 
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
			5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
			6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
			7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
			8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
			9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
			10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
			11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,
			12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12};
			days = d[day];
			return m[day];
		}
		static unsigned char D[365] =
		{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
		static unsigned char M[365] = 
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
		6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,
		12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12};
		days = D[day];
		return M[day];
	}
	XTime XTime::GetLocal()//��ȡ��ǰ�ı���ʱ��
	{
		static volatile int tryCounter = 0;//0����ʹ��CPU��������1ʹ��CPU��������-1����GetLocalTime
		static volatile short lastday = -1;
		static volatile long long daymns = 0;
		static volatile long long mns = 0;
		static LARGE_INTEGER frequency = {0};//CPUƵ��
		static LARGE_INTEGER last={0};
		if(!tryCounter)
		{
			if(!QueryPerformanceFrequency(&frequency)){tryCounter=-1;return GetLocal();}//��ȡʱ��Ƶ��,ʧ�������
			if(!QueryPerformanceCounter(&last)){tryCounter=-1;return GetLocal();}//������
			::SYSTEMTIME t;
			::GetLocalTime(&t);
			daymns = GetDays(t.wYear,t.wMonth,t.wDay)*EveryDay;
			mns = t.wMilliseconds*EveryMillisecond//����
				+ t.wSecond*EverySecond//��
				+ t.wMinute*EveryMinute//��
				+ t.wHour*EveryHour//ʱ
				+ daymns;
			lastday = t.wDay;
			tryCounter = 1;//����CPUʱ���ʱ
			return mns;
		}
		if(tryCounter<0)
		{
			::SYSTEMTIME t;
			::GetLocalTime(&t);
			if(t.wDay!=lastday)
			{
				daymns = GetDays(t.wYear,t.wMonth,t.wDay)*EveryDay;
				lastday = t.wDay;
			}
			return t.wMilliseconds*EveryMillisecond//����
			+ t.wSecond*EverySecond//��
			+ t.wMinute*EveryMinute//��
			+ t.wHour*EveryHour//ʱ
			+ daymns;
		}
		long long i = CpuCounterReference().QuadPart;
		if((i-=last.QuadPart)>EveryDay)tryCounter = 0;
		return unsigned long long(double(i)/frequency.QuadPart*EverySecond)+ mns;
	}
	void XTime::SetLocal(const XTime& now)//���õ�ǰ�ı���ʱ��
	{
		::SYSTEMTIME t = XTime(now);
		::SetLocalTime(&t);
	}

	XTime::XTime()//����,������
		:time(0)
	{}
	XTime::XTime(long long t)//ʹ��һ������ֵ����ʼ��
		:time(t)
	{}
	XTime::XTime(const ::SYSTEMTIME& t)//ʹ��һ��ϵͳʱ������ʼ��
		:time(t.wMilliseconds*EveryMillisecond//����
		+ t.wSecond*EverySecond//��
		+ t.wMinute*EveryMinute//��
		+ t.wHour*EveryHour//ʱ
		+ GetDays(t.wYear,t.wMonth,t.wDay)*EveryDay)
	{}
	XTime::XTime(const XString&tmpstr)
	{
		//static XString monthString[12]={L"january",L"february",L"march",L"april",L"may",L"june",L"july",L"august",L"september",L"october",L"november",L"december"};
		//static XString monthShortString[12]={L"jan",L"feb",L"mar",L"apr",L"may",L"jun",L"jul",L"aug",L"sept",L"oct",L"nov",L"dec"};
		//static VArray<XString> months(12,monthString,Reference);
		//static VArray<XString> monthsShort(12,monthShortString,Reference);
		static LPCWSTR splitWchars= L" t";
		static VArray<WCHAR> splitWchs(2,splitWchars,Reference);
		//��ȡ��ǰʱ��
		time = GetLocal();
		//ת��ΪСд
		XString str = tmpstr.ToLower();
		//�ַ��������ָ�
		XArray<XString> strs = str.Split(splitWchs);
		//�Ƿ��Ѽ�¼��
		bool hasymd=false;
		bool hashms=false;
		//�ֶμ��
		for(int i=0;i<strs.Length;++i)
		{
			static XString strContains1 = L"-";
			static XString strContains2 = L"/";
			static XString strContains3 = L":";
			static XString strContains4 = L"��";
			static XString strContains5 = L"��";
			static XString strContains6 = L"��";
			if(!hasymd&&(strs[i].Contains(strContains1) || strs[i].Contains(strContains2)))
			{
				XArray<XString> ymd = strs[i].GetNumbers();
				if(ymd.Length==3)
				{
					SetYear((int)ymd[0].ToUInt64());//��
					SetMonth((int)ymd[1].ToUInt64());//��
					SetDay((int)ymd[2].ToUInt64());//��
					hasymd = true;//�Ѽ�¼������
					if(hashms)break;
				}
			}
			else if(!hashms&&strs[i].Contains(strContains3))
			{
				XArray<XString> hms = strs[i].GetNumbers();
				static XString strContains7 = L"pm";
				bool afternoon = strs[i].Contains(strContains7);
				switch(hms.Length)
				{
				case 4:time = (time/EverySecond)*EverySecond+hms[3].PadRight(7,L'0').ToUInt64();
				case 3:SetSecond((int)hms[2].ToUInt64());
				case 2:SetMinute((int)hms[1].ToUInt64());
					if(afternoon)SetHour(12+(int)hms[0].ToUInt64());
					else SetHour((int)hms[0].ToUInt64());
				default:hashms = true;//�Ѽ�¼ʱ����
				}
				if(hasymd)break;
			}
			else if(!hasymd&&(strs[i].Contains(strContains4) || strs[i].Contains(strContains5) || strs[i].Contains(strContains6)))
			{
				int tmp = strs[i].IndexOf(strContains4);
				if(tmp>0)SetYear((int)strs[i].Substring(0,tmp).GetNumbers().LastElement().ToUInt64());
				tmp = strs[i].IndexOf(strContains5);
				if(tmp>0)SetMonth((int)strs[i].Substring(0,tmp).GetNumbers().LastElement().ToUInt64());
				tmp= strs[i].IndexOf(strContains6);
				if(tmp>0)SetDay((int)strs[i].Substring(0,tmp).GetNumbers().LastElement().ToUInt64());
				hasymd = true;
				if(hashms)break;
			}
		}
	}

	XTime& XTime::operator=(const XTime& t)//��ֵ����
	{
		time = t.time;
		return *this;
	}
	XTime& XTime::operator=(long long t)
	{
		time = t;
		return *this;
	}
	XTime& XTime::operator=(const ::SYSTEMTIME& t)
	{
		time = t.wMilliseconds*EveryMillisecond//����
			+ t.wSecond*EverySecond//��
			+ t.wMinute*EveryMinute//��
			+ t.wHour*EveryHour//ʱ
			+ GetDays(t.wYear,t.wMonth,t.wDay)*EveryDay;
		return *this;
	}


	//ͬʱ��ȡ��ݺ�������
	unsigned int XTime::GetYearAndDaysInYear(unsigned int* pday)const
	{
		long long year = (time / EveryDay) / 146097 * 400;//�����
		long long days = (time / EveryDay) % 146097;//��ȡ400�����������400��һ������һ��365*400+97=146097�����
		if(days>=146097-366){if(pday)*pday = unsigned int(days-(146097-366));return unsigned int(year+400);}
		year += days/36524 * 100;//��ȡ100�����������100��һ������һ��365*100+24=36524�����
		days %= 36524;if(days>=36524-365){if(pday)*pday = unsigned int(days-(36524-365));return unsigned int(year+100);}
		year += days/1461 * 4;//��ȡ4�����������4��һ������һ��365*4+1=1461�����
		days %= 1461;if(days>=1461-366){if(pday)*pday = unsigned int(days-(1461-366));return unsigned int(year+4);}
		if(pday)*pday = unsigned int(days%365);return (unsigned int)(year + 1 + days/365);
	}
	unsigned int XTime::GetYear()const
	{
		return (unsigned int)GetYearAndDaysInYear(0);
	}
	unsigned int XTime::GetMonth()const
	{
		unsigned int days;
		unsigned int year = GetYearAndDaysInYear(&days);
		return GetMonthByDaysInYear(year,days);
	}
	unsigned int XTime::GetDay()const
	{
		unsigned int days;
		unsigned int year = GetYearAndDaysInYear(&days);
		GetMonthByDaysInYear(year,days);
		return days;
	}
	unsigned int XTime::GetDayOfWeek()const//ȡ���ڼ���1���Ư��
	{
		return ((time%EveryWeek)/EveryDay+1)%7;
	}
	unsigned int XTime::GetHour()const//ȡʱ
	{
		return (unsigned int)(((time>0?time:-time)%EveryDay)/EveryHour);
	}
	unsigned int XTime::GetMinute()const//ȡ��
	{
		return (unsigned int)(((time>0?time:-time)%EveryHour)/EveryMinute);
	}
	unsigned int XTime::GetSecond()const//ȡ��
	{
		return (unsigned int)(((time>0?time:-time)%EveryMinute)/EverySecond);
	}
	unsigned int XTime::GetMillisecond()const//ȡ����
	{
		return (unsigned int)(((time>0?time:-time)%EverySecond)/EveryMillisecond);
	}
	unsigned int XTime::GetMicrosecond()const//ȡ΢��
	{
		return (unsigned int)(((time>0?time:-time)%EverySecond)/EveryMicrosecond);
	}
	void XTime::SetYear(unsigned int year)//������
	{
		::SYSTEMTIME t = *this;
		t.wYear = (unsigned short)year;
		*this = t;
	}
	void XTime::SetMonth(unsigned int month)//������
	{
		::SYSTEMTIME t = *this;
		t.wMonth = (unsigned short)month;
		*this = t;
	}
	void XTime::SetDay(unsigned int day)//������
	{
		::SYSTEMTIME t = *this;
		t.wDay = (unsigned short)day;
		*this = t;
	}
	void XTime::SetHour(unsigned int hour)//����ʱ
	{
		time = time / EveryDay * EveryDay + time % EveryHour + hour * EveryHour;
	}
	void XTime::SetMinute(unsigned int minute)//���÷�
	{
		time = time / EveryHour * EveryHour + time % EveryMinute + minute * EveryMinute;
	}
	void XTime::SetSecond(unsigned int second)//������
	{
		time = time / EveryMinute * EveryMinute + time % EverySecond + second * EverySecond;
	}
	void XTime::SetMillisecond(unsigned int millisecond)//���ú���
	{
		time = time / EverySecond * EverySecond + time % EveryMillisecond + millisecond * EveryMillisecond;
	}
	void XTime::SetMicrosecond(unsigned int microsecond)//����΢��
	{
		time = time / EveryMillisecond * EveryMillisecond + time % EveryMicrosecond + microsecond * EveryMicrosecond;
	}

	int XTime::GetDays()const//��ȡ��԰�����ѹ�����
	{
		return (int)(time/EveryDay);
	}
	int  XTime::GetHours()const//��ȡ��԰Ԫ������ʱ���ѹ�Сʱ��(����Ϊ��)
	{
		return (int)(time/EveryHour);
	}
	long long XTime::GetMinutes()const//��ȡ��԰Ԫ������ʱ���ѹ�����(����Ϊ��)
	{
		return time/EveryMinute;
	}
	long long XTime::GetSeconds()const//��ȡ��԰Ԫ������ʱ���ѹ�����(����Ϊ��)
	{
		return time/EverySecond;
	}
	long long XTime::GetMilliseconds()const//��ȡ��԰Ԫ������ʱ���ѹ�������(����Ϊ��)
	{
		return time/EveryMillisecond;
	}
	long long XTime::GetMicroseconds()const//��ȡ��԰Ԫ������ʱ���ѹ�΢����(����Ϊ��)
	{
		return time/EveryMicrosecond;
	}

	XTime::operator long long()const//ת��Ϊ��100nsΪ��λ������
	{
		return time;
	}
	XTime::operator ::SYSTEMTIME()const//ת��ΪWindowsAPI�е�����
	{
		SYSTEMTIME t;
		t.wMilliseconds = (unsigned short)GetMillisecond();//����
		t.wSecond = (unsigned short)GetSecond();//��
		t.wMinute = (unsigned short)GetMinute();//��
		t.wHour = (unsigned short)GetHour();//Сʱ
		t.wDayOfWeek = (unsigned short)GetDayOfWeek();//����x

		unsigned int days;
		t.wYear = (unsigned short)GetYearAndDaysInYear(&days);
		t.wMonth = (unsigned short)GetMonthByDaysInYear(t.wYear,days);
		t.wDay = (unsigned short)days;
		return t;
	}

	void XTime::Wait(const XTime& t)
	{
		if(time==0)*this=Now;
		*this+=t;
		if(t<EveryMillisecond)
		{
			if(t<EveryMicrosecond)return;
			SwitchToThread();
			return;
		}
		XTime now=Now;
		if(*this<=now)return;
		::Sleep(DWORD((*this-now)/EveryMillisecond));
	}

	XString XTime::ToString()const
	{
		LPWSTR tmpStr = new WCHAR[32];// = L"+00000000day 00:00:00.0000000";
		LPWSTR pstr = tmpStr;
		unsigned int num = time>0?GetDays():-GetDays();
		if(time<0)*(tmpStr++) = L'-';
		if(num!=0)
		{
			if(num>=10000000)*(tmpStr++) = num / 10000000 + L'0';
			if(num>=1000000)*(tmpStr++) = (num%10000000)/1000000 + L'0';
			if(num>=100000)*(tmpStr++) = (num%1000000)/100000 + L'0';
			if(num>=10000)*(tmpStr++) = (num%100000)/10000 + L'0';
			if(num>=1000)*(tmpStr++) = (num%10000)/1000 + L'0';
			if(num>=100)*(tmpStr++) = (num%1000)/100 + L'0';
			if(num>=10)*(tmpStr++) = (num%100)/10 + L'0';
			*(tmpStr++) = num%10 + L'0';
			*(tmpStr++) = L'D';
			*(tmpStr++) = L'a';
			*(tmpStr++) = L'y';
			*(tmpStr++) = L's';
			*(tmpStr++) = ' ';
		}
		num = GetHour();
		*(tmpStr++) = num/10 + L'0';
		*(tmpStr++) = num%10 + L'0';
		*(tmpStr++) = L':';
		num = GetMinute();
		*(tmpStr++) = num/10 + L'0';
		*(tmpStr++) = num%10 + L'0';
		*(tmpStr++) = L':';
		num = GetSecond();
		*(tmpStr++) = num/10 + L'0';
		*(tmpStr++) = num%10 + L'0';
		num = time%EverySecond;
		*(tmpStr++) = L'.';
		*(tmpStr++) = num/1000000 + L'0';
		*(tmpStr++) = (num%1000000)/100000 + L'0';
		*(tmpStr++) = (num%100000)/10000 + L'0';
		*(tmpStr++) = (num%10000)/1000 + L'0';
		*(tmpStr++) = (num%1000)/100 + L'0';
		*(tmpStr++) = (num%100)/10 + L'0';
		*(tmpStr++) = num%10 + L'0';
		*tmpStr = 0;
		return new VString(int(tmpStr-pstr),pstr,NULL);
		//XString str;
		//if(GetDays())str = XString(GetDays(),L"%dd ")+XString(GetHour()).PadLeft(2,L'0');
		//else str = XString(GetHours());
		//str+=XString(":")+XString(GetMinute()).PadLeft(2,L'0');
		//str+=XString(":")+XString(GetSecond()).PadLeft(2,L'0');
		//return str+XString(".")+XString(time%EverySecond).PadLeft(7,L'0');
	}
	XString XTime::ToString(const XString&str)const
	{
		//static LPCWSTR monthString[12]={L"January",L"February",L"March",L"April",L"May",L"June",L"July",L"August",L"September",L"October",L"November",L"December"};
		//static LPCWSTR monthShortString[12]={L"Jan",L"Feb",L"Mar",L"Apr",L"May",L"Jun",L"Jul",L"Aug",L"Sept",L"Oct",L"Nov",L"Dec"};
		static LPCWSTR weekString[7]={L"Monday",L"Tuesday",L"Wednesday",L"Thursday",L"Friday",L"Saturday",L"Sunday"};
		//static LPCWSTR weekShortString[7]={L"Mon",L"Tues",L"Wed",L"Thur",L"Fri",L"Sat",L"Sun"};
		if(time>=0&&str.Length==1)
		{
			bool hasYear,hasMonth,hasDay,hasDayOfWeek,hasHour,hasMinute,hasSecond,hasNS;
			int ymdType;//0Ϊ����ʾ��1Ϊx��x��x�գ�2Ϊx-x-x��3Ϊx/x/x
			int splitType;//0Ϊ��ʹ�÷ָ���1Ϊ�ո�2ΪL'T'
			switch(str[0])
			{
			case L'y':hasYear=hasMonth=true;hasDay=hasDayOfWeek=hasHour=hasMinute=hasSecond=hasNS=false;ymdType=1;splitType=0;break;
			case L'm':hasMonth=hasDay=true;hasYear=hasDayOfWeek=hasHour=hasMinute=hasSecond=hasNS=false;ymdType=1;splitType=0;break;
			case L'd':hasYear=hasMonth=hasDay=true;hasDayOfWeek=hasHour=hasMinute=hasSecond=hasNS=false;ymdType=3;splitType=0;break;
			case L't':hasHour=hasMinute=true;hasYear=hasMonth=hasDay=hasDayOfWeek=hasSecond=hasNS=false;ymdType=0;splitType=0;break;
			case L'D':hasYear=hasMonth=hasDay=hasDayOfWeek=true;hasHour=hasMinute=hasSecond=hasNS=false;ymdType=1;splitType=0;break;
			case L'T':hasHour=hasMinute=hasSecond=true;hasYear=hasMonth=hasDay=hasDayOfWeek=hasNS=false;ymdType=0;splitType=0;break;
			case L's':hasYear=hasMonth=hasDay=hasHour=hasMinute=hasSecond=true;hasDayOfWeek=hasNS=false;ymdType=2;splitType=2;break;
			case L'g':hasYear=hasMonth=hasDay=hasHour=hasMinute=true;hasSecond=hasDayOfWeek=hasNS=false;ymdType=3;splitType=1;break;
			case L'o':hasYear=hasMonth=hasDay=hasHour=hasMinute=hasSecond=hasNS=true;hasDayOfWeek=false;ymdType=2;splitType=2;break;
			case L'u':hasYear=hasMonth=hasDay=hasHour=hasMinute=hasSecond=true;hasDayOfWeek=hasNS=false;ymdType=2;splitType=1;break;
			case L'f':hasYear=hasMonth=hasDay=hasHour=hasMinute=true;hasSecond=hasDayOfWeek=hasNS=false;ymdType=1;splitType=1;break;
			case L'G':hasYear=hasMonth=hasDay=hasHour=hasMinute=hasSecond=true;hasDayOfWeek=hasNS=false;ymdType=3;splitType=1;break;
			case L'F':hasYear=hasMonth=hasDay=hasHour=hasMinute=hasSecond=hasDayOfWeek=true;hasNS=false;ymdType=1;splitType=1;break;
			default: return ToString();
			}
			LPWSTR tmpStr = new WCHAR[48];
			LPWSTR p = tmpStr;
			unsigned int days;
			unsigned int year = GetYearAndDaysInYear(&days);
			unsigned int month = GetMonthByDaysInYear(year,days);
			if(hasYear)//�����������Ϣ
			{
				if(year>=10000)*(p++) = year/10000+L'0';if(year>=1000)*(p++) = (year%10000)/1000+L'0'; if(year>=100)*(p++) = (year%1000)/100+L'0';if(year>=10)*(p++) = (year%100)/10+L'0';*(p++) = year%10+L'0';
				switch(ymdType)
				{
				case 1:*(p++) = L'��';break;
				case 2:if(hasMonth)*(p++) = L'-';break;
				case 3:if(hasMonth)*(p++) = L'/';break;
				}
			}
			if(hasMonth)//�����������Ϣ
			{
				if(month>=10 || ymdType==2)*(p++) = month/10+L'0';*(p++) = month%10+L'0';
				switch(ymdType)
				{
				case 1:*(p++) = L'��';break;
				case 2:if(hasDay)*(p++) = L'-';break;
				case 3:if(hasDay)*(p++) = L'/';break;
				}
			}
			if(hasDay)//�����������Ϣ
			{
				if(days>=10 || hasMonth)*(p++) = days/10+L'0';	*(p++) = days%10+L'0';
				if(ymdType==1)
				{
					*(p++) = L'��';
				}
			}
			if(ymdType!=0)switch(splitType)//�ָ�
			{
			case 1:*(p++) = L' ';break;
			case 2:*(p++) = L'T';break;
			}
			if(hasHour)//��ʾСʱ��Ϣ
			{
				days = GetHour();	if(days>=10)*(p++) = days/10+L'0';*(p++) = days%10+L'0';if(hasMinute)*(p++) = L':';
			}
			if(hasMinute)//��ʾ����Ϣ
			{
				days = GetMinute();*(p++) = days/10+L'0';*(p++) = days%10+L'0';if(hasSecond)*(p++) = L':';
			}
			if(hasSecond)//��ʾ����Ϣ
			{
				days = GetSecond();*(p++) = days/10+L'0';*(p++) = days%10+L'0';if(hasNS)*(p++) = L'.';
			}
			if(hasNS)//��ʾ������Ϣ
			{
				days = time%EverySecond;*(p++) = days/1000000 + L'0';*(p++) = (days%1000000)/100000 + L'0';*(p++) = (days%100000)/10000 + L'0';	*(p++) = (days%10000)/1000 + L'0';*(p++) = (days%1000)/100 + L'0';*(p++) = (days%100)/10 + L'0';*(p++) = days%10 + L'0';
			}
			if(hasDayOfWeek)
			{
				*(p++) = L' ';
				wcscpy_s(p,10,weekString[GetDayOfWeek()]);
				p+= wcslen(weekString[GetDayOfWeek()]);
			}
			if(str[0]==L'u')*(p++)=L'Z';
			*p = 0;
			return new VString(int(p-tmpStr),tmpStr,NULL);
		}
		return ToString();
	}
#ifdef _CLR //�й�֧��
	XTime::XTime(System::DateTime^time)
		:time(GetDays(time->Year,time->Month,time->Day)*EveryDay+
				time->Hour*EveryHour+
				time->Minute*EveryMinute+
				time->Second*EverySecond+
				time->Millisecond*EveryMillisecond)
		{		}
	System::DateTime^XTime::ToDateTime()const
	{
		return gcnew System::DateTime(time);
	}
#endif
}
#endif