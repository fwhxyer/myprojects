#include "stdafx.h"
#ifdef XSTRING_
namespace LJ
{
	//VString
	LPCWSTR VString::ppNumWChs[ChsNumMaxCount] = 
	{L"0零〇０",
	L"1一壹①㈠⑴⒈Ⅰⅰ１",L"2二贰②㈡⑵⒉Ⅱⅱ２貮",
	L"3三叁③㈢⑶⒊Ⅲⅲ３",L"4四肆④㈣⑷⒋Ⅳⅳ４",
	L"5五伍⑤㈤⑸⒌Ⅴⅴ５",L"6六陆⑥㈥⑹⒍Ⅵⅵ６",
	L"7七柒⑦㈦⑺⒎Ⅶⅶ７",L"8八捌⑧㈧⑻⒏Ⅷⅷ８",
	L"9九玖⑨㈨⑼⒐Ⅸⅸ９",L"⑩㈩⑽⒑Ⅹⅹ",
	L"⑾⒒",L"⑿⒓",L"⒀⒔",L"⒁⒕",L"⒂⒖",L"⒃⒗",L"⒄⒘",L"⒅⒙",L"⒆⒚",L"⒇⒛"
	};//记录数字字符
	unsigned char VString::pNumCounts[ChsNumMaxCount] = {4,10,11,10,10,10,10,10,10,10,6,2,2,2,2,2,2,2,2,2,2};//记实每个数字字符数
	LPCWSTR VString::ppUnitWChs[9] = {L"十拾",L"廿念",L"百佰",L"千仟kK",L"万",L"兆mM",L"亿",L"吉gG",L"太tT"};//记录单位字符
	unsigned long long VString::pUnitValue[9] = {10,20,100,1000,10000,1000000,100000000,1000000000,1000000000000};//记录每个单位对应的数值
	unsigned char VString::pUnitCounts[9] = {2,2,2,4,1,3,1,3,3};//记录每个单位对应的字符数量

	const XTypes& VString::CurrentType = CREATECLASSTYPE(LJ::VString,LJ::XBase);
	LPWSTR VString::StrRepeat(LPCWSTR wString,int count)
	{
		if(wString==NULL)return NULL;
		if(count<0)throw XException(E_INVALIDARG);//参数无效
		int length = Strlen(wString);
		LPWSTR p = new WCHAR[length*count+1];
		p[length*count]=0;
		while(count--)Memory::Copy(p+count*length,wString,length*2);
		return p;
	}
	LPSTR VString::StrRepeat(LPCSTR mString,int count)
	{
		if(mString==NULL)return NULL;
		if(count<0)throw XException(E_INVALIDARG);//参数无效
		int length = Strlen(mString);
		LPSTR p = new CHAR[length*count+1];
		p[length*count]=0;
		while(count--)Memory::Copy(p+count*length,mString,length);
		return p;
	}
	LPWSTR VString::StrRepeat(LPCWSTR wString,int length,int count)
	{
		if(wString==NULL)return NULL;
		if(count<0 || length<0)throw XException(E_INVALIDARG);//参数无效
		LPWSTR p = new WCHAR[length*count+1];
		p[length*count]=0;
		while(count--)Memory::Copy(p+count*length,wString,length*2);
		return p;
	}
	LPSTR VString::StrRepeat(LPCSTR mString,int length,int count)
	{
		if(mString==NULL)return NULL;
		if(count<0 || length<0)throw XException(E_INVALIDARG);//参数无效
		LPSTR p = new CHAR[length*count+1];
		p[length*count]=0;
		while(count--)Memory::Copy(p+count*length,mString,length);
		return p;
	}
	//多字节转换为Unicode，length表示的是source除终止字符'\0'的字符数（字节数），小玉0代表自动计算，返回转换后的长度
	LPWSTR VString::AnsiToUnicode(LPCSTR source,int* outLength,int length)
	{
		if(length<0)length = (int)strlen(source);
		int len=0;
		for(int i=0;i<length;++i,++len)//统计字符数
			if(source[i]<0)++i;
		LPWSTR tmp = new WCHAR[len+1];
		if(len)len = MultiByteToWideChar(CP_ACP,NULL,source,length,tmp,len+len+2);
		tmp[len]=0;
		if(outLength)*outLength = len;
		return tmp;
	}
	LPWSTR VString::AnsiToUnicode(LPCSTR source,int length)
	{
		return AnsiToUnicode(source,0,length);
	}
	//Unicode转换为多字节，length表示的是source除终止字符'\0'的字符数(字节数/2)，返回转换后的长度
	LPSTR VString::UnicodeToAnsi(LPCWSTR source,int* outLength,int length)
	{
		if(length<0)length = Strlen(source);
		int len=0;
		for(int i=0;i<length;++i,++len)//统计字符数
			if(source[i]>127)++len;
		LPSTR tmp = new CHAR[len+1];
		CHAR c = '_';//无法转换的字符使用下划线替换
		if(len)len = WideCharToMultiByte(CP_ACP,NULL,source,length,tmp,len+1,&c,NULL);
		tmp[len] = 0;
		return tmp;
	}
	LPSTR VString::UnicodeToAnsi(LPCWSTR source,int length)
	{
		return UnicodeToAnsi(source,0,length);
	}
	//查看vString2在vString1的位置
	int VString::Find(const VString& vString1,int index1,const VString& vString2,int index2,int maxLength1,int maxLength2,bool ignoreCase)
	{
		if(index1<0 || index2<0)throw XException(E_INVALIDARG);//参数无效
		int tmp;
		if(ignoreCase)
		{
			LPWSTR tmp1 = VString::Strcpy(vString1.wString+index1,maxLength1-index1);
			LPWSTR tmp2 = VString::Strcpy(vString2.wString+index2,maxLength2-index2);
			if(maxLength1<0)maxLength1 = VString::Strlen(tmp1);
			else maxLength1-=index1;
			if(maxLength2<0)maxLength2 = VString::Strlen(tmp2);
			else maxLength2-=index2;
			if(maxLength1)_wcslwr_s(tmp1,maxLength1+1);
			if(maxLength2)_wcslwr_s(tmp2,maxLength2+1);
			tmp = VString::Strstr(tmp1,tmp2,maxLength1,maxLength2);
			delete []tmp1;
			delete []tmp2;
		}
		else tmp = VString::Strstr(vString1.wString+index1,vString2.wString+index2,maxLength1-index1,maxLength2-index2);
		if(tmp<0)return tmp;
		return tmp+index1;
	}
	//查找vString2在vString1最后出现的位置
	int VString::Last(const VString& vString1,int index1,const VString& vString2,int index2,int maxLength1,int maxLength2,bool ignoreCase)
	{
		if(index1<0 || index2<0)throw XException(E_INVALIDARG);//参数无效
		LPWSTR tmp1 = VString::Strcpy(vString1.wString+index1,maxLength1-index1);
		LPWSTR tmp2 = VString::Strcpy(vString2.wString+index2,maxLength2-index2);
		if(maxLength1<0)maxLength1 = VString::Strlen(tmp1);
		else maxLength1-=index1;
		if(maxLength2<0)maxLength2 = VString::Strlen(tmp2);
		else maxLength2-=index2;
		if(ignoreCase)
		{
			_wcslwr_s(tmp1,maxLength1+1);
			_wcslwr_s(tmp2,maxLength2+1);
		}
		int tmp;
		for(tmp=maxLength1-maxLength2;tmp>=0;--tmp)
		{
			if(tmp1[tmp]==*tmp2)
			{
				if(!memcmp(tmp1+tmp,tmp2,maxLength2+maxLength2))break;
			}
		}
		delete tmp1;
		delete tmp2;
		if(tmp<0)return -1;
		return tmp+index1;
	}
	//析构函数
	VString::~VString()
	{
		delete []wString;
		delete []mString;
	}
	//构造函数
	VString::VString():Length(0),wString(&(*new WCHAR[1]=0)),mString(&(*new CHAR[1]=0))
	{	}
	//由数字创建字符串，format使用字符串指定格式
	VString::VString(float number,LPCWSTR format):Length(0),wString(NULL),mString(NULL)
	{
		WCHAR str[1024];
		swprintf_s(str,format,number);
		const_cast<int&>(Length)=Strlen(str);
		wString = new WCHAR[1+Length];
		Memory::Copy(wString,str,2+Length*2);
		wString[Length]=0;
	}
	//由数字创建字符串，format使用字符串指定格式
	VString::VString(double number,LPCWSTR format):Length(0),wString(NULL),mString(NULL)
	{
		WCHAR str[1024];
		swprintf_s(str,format,number);
		const_cast<int&>(Length)=Strlen(str);
		wString = new WCHAR[1+Length];
		Memory::Copy(wString,str,2+Length*2);
		wString[Length]=0;
	}
	//由数字创建字符串，format使用字符串指定格式
	VString::VString(unsigned long long number,LPCWSTR format):Length(0),wString(NULL),mString(NULL)
	{
		WCHAR str[1024];
		swprintf_s(str,format,number);
		const_cast<int&>(Length)=Strlen(str);
		wString = new WCHAR[1+Length];
		Memory::Copy(wString,str,2+Length*2);
		wString[Length]=0;
	}
	//由数字创建字符串，format使用字符串指定格式
	VString::VString(unsigned long number,LPCWSTR format):Length(0),wString(NULL),mString(NULL)
	{
		WCHAR str[1024];
		swprintf_s(str,format,number);
		const_cast<int&>(Length)=Strlen(str);
		wString = new WCHAR[1+Length];
		Memory::Copy(wString,str,2+Length*2);
		wString[Length]=0;
	}
	//由数字创建字符串，format使用字符串指定格式
	VString::VString(unsigned int number,LPCWSTR format):Length(0),wString(NULL),mString(NULL)
	{
		WCHAR str[1024];
		swprintf_s(str,format,number);
		const_cast<int&>(Length)=Strlen(str);
		wString = new WCHAR[1+Length];
		Memory::Copy(wString,str,2+Length*2);
		wString[Length]=0;
	}
	//由数字创建字符串，format使用字符串指定格式
	VString::VString(long long number,LPCWSTR format):Length(0),wString(NULL),mString(NULL)
	{
		WCHAR str[1024];
		swprintf_s(str,format,number);
		const_cast<int&>(Length)=Strlen(str);
		wString = new WCHAR[1+Length];
		Memory::Copy(wString,str,2+Length*2);
		wString[Length]=0;
	}
	//由数字创建字符串，format使用字符串指定格式
	VString::VString(long number,LPCWSTR format):Length(0),wString(NULL),mString(NULL)
	{
		WCHAR str[1024];
		swprintf_s(str,format,number);
		const_cast<int&>(Length)=Strlen(str);
		wString = new WCHAR[1+Length];
		Memory::Copy(wString,str,2+Length*2);
		wString[Length]=0;
	}
	//由数字创建字符串，format使用字符串指定格式
	VString::VString(int number,LPCWSTR format):Length(0),wString(NULL),mString(NULL)
	{
		WCHAR str[1024];
		swprintf_s(str,format,number);
		const_cast<int&>(Length)=Strlen(str);
		wString = new WCHAR[1+Length];
		Memory::Copy(wString,str,2+Length*2);
		wString[Length]=0;
	}
	//由数字创建字符串，format使用字符串指定格式
	VString::VString(unsigned short number,LPCWSTR format):Length(0),wString(NULL),mString(NULL)
	{
		WCHAR str[1024];
		swprintf_s(str,format,number);
		const_cast<int&>(Length)=Strlen(str);
		wString = new WCHAR[1+Length];
		Memory::Copy(wString,str,2+Length*2);
		wString[Length]=0;
	}
	//由数字创建字符串，format使用字符串指定格式
	VString::VString(short number,LPCWSTR format):Length(0),wString(NULL),mString(NULL)
	{
		WCHAR str[1024];
		swprintf_s(str,format,number);
		const_cast<int&>(Length)=Strlen(str);
		wString = new WCHAR[1+Length];
		Memory::Copy(wString,str,2+Length*2);
		wString[Length]=0;
	}
	//由数字创建字符串，format使用字符串指定格式
	VString::VString(unsigned char number,LPCWSTR format):Length(0),wString(NULL),mString(NULL)
	{
		WCHAR str[1024];
		swprintf_s(str,format,number);
		const_cast<int&>(Length)=Strlen(str);
		wString = new WCHAR[1+Length];
		Memory::Copy(wString,str,2+Length*2);
		wString[Length]=0;
	}
	//由数字创建字符串，format使用字符串指定格式
	VString::VString(signed char number,LPCWSTR format):Length(0),wString(NULL),mString(NULL)
	{
		WCHAR str[1024];
		swprintf_s(str,format,number);
		const_cast<int&>(Length)=Strlen(str);
		wString = new WCHAR[1+Length];
		Memory::Copy(wString,str,2+Length*2);
		wString[Length]=0;
	}
	VString::VString(const XString str,int count)
		:Length(str.pObject?((VString*)str.pObject)->Length*count:throw XException(E_POINTER)),
		wString(StrRepeat(str.pObject?((VString*)str.pObject)->wString:throw XException(E_POINTER),str.pObject?((VString*)str.pObject)->Length:throw XException(E_POINTER),count)),
		mString(NULL){}
	//由count个LPSTR构造
	VString::VString(LPCSTR str,int count):Length(count<0?throw XException(E_INVALIDARG):0),wString(NULL),mString(NULL)
	{
		LPWSTR p=NULL;
		int len=0;
		if(str)p = AnsiToUnicode(str,&len);
		const_cast<int&>(Length) = len*count;
		wString=StrRepeat(p,len,count);
		delete[]p;
	}
	VString::VString(CHAR c,int count):Length(count),wString(new WCHAR[count<0?throw XException(E_INVALIDARG):count+1]),mString(NULL)
	{
		wmemset(wString,c,count);
		wString[count]=0;
	}
	VString::VString(WCHAR wc,int count):Length(count),wString(new WCHAR[count<0?throw XException(E_INVALIDARG):count+1]),mString(NULL)
	{
		wmemset(wString,wc,count);
		wString[count]=0;
	}
	VString::VString(const XArray<WCHAR> wstr,int count):Length(count<0?throw XException(E_INVALIDARG):0),wString(NULL),mString(NULL)
	{
		int len = Strlen(wstr);
		if(len>wstr.Length)len = wstr.Length;
		const_cast<int&>(Length) = len*count;
		wString = StrRepeat(wstr,len,count);
	}
	VString::VString(const XArray<CHAR> mstr,int count):Length(count<0?throw XException(E_INVALIDARG):0),wString(NULL),mString(NULL)
	{
		int len = Strlen(mstr);
		if(len>mstr.Length)len = mstr.Length;
		LPWSTR wstr = AnsiToUnicode(mstr,&len,len);
		const_cast<int&>(Length) = len*count;
		wString = StrRepeat(wstr,len,count);
		delete []wstr;
	}
	const WCHAR VString::operator[](int index)const
	{
		if(index<0)throw XException(E_INVALIDARG);
		if(index>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		return wString[index];
	}
	WCHAR& VString::operator[](int index)
	{
		if(index<0)throw XException(E_INVALIDARG);
		if(index>Length)throw XException(COR_E_INDEXOUTOFRANGE);
		return wString[index];
	}

	VString& VString::operator=(const VString& vString)//赋值运算
	{
		delete[] wString;
		delete[]mString;
		const_cast<int&>(Length) = vString.Length;
		wString = Strcpy(vString.wString,vString.Length);
		mString = NULL;
		return *this;
	}
	VString& VString::operator=(LPCSTR mstr)
	{
		delete []wString;
		delete []mString;
		wString = AnsiToUnicode(mstr,&const_cast<int&>(Length));
		mString = NULL;
		return *this;
	}
	VString& VString::operator=(LPCWSTR wstr)
	{
		delete []wString;
		delete []mString;
		const_cast<int&>(Length) = Strlen(wString);
		wString = new WCHAR[Length+1];
		Memory::Copy(wString,wstr,Length*2+2);
		mString = NULL;
		return *this;
	}
	VString& VString::operator+=(const VString& vString)//串接运算
	{
		LPWSTR p = Strcat(wString,vString.wString,Length,vString.Length);
		const_cast<int&>(Length)+=vString.Length;
		delete []wString;
		delete []mString;
		wString = p;
		mString = NULL;
		return *this;
	}
	VString& VString::operator+=(LPCSTR mstr)
	{
		int length;
		LPWSTR p = AnsiToUnicode(mstr,&length);
		LPWSTR tmp = Strcat(wString,p,Length,length);
		delete []p;
		delete []wString;
		delete []mString;
		wString = tmp;
		mString = NULL;
		const_cast<int&>(Length)+=length;
		return *this;
	}
	VString& VString::operator+=(LPCWSTR wstr)
	{
		int length=Strlen(wstr);
		LPWSTR tmp = Strcat(wString,wstr,Length,length);
		delete []wString;
		delete []mString;
		wString = tmp;
		mString = NULL;
		const_cast<int&>(Length)+=length;
		return *this;
	}
	LPCSTR const VString::ToAnsi()const//转换成原始的多字节字符串，const型
	{
		if(wString && nullptr==mString)//转换
		{
			LPSTR p= UnicodeToAnsi(wString,Length);
			p = (LPSTR)InterlockedExchangePointer((PVOID*)&const_cast<volatile LPSTR&>(mString),p);
			delete []p;
		}
		return mString;
	}
	XString VString::ToString()const
	{return new VString(*this);}
	double VString::ToIntDouble(LPWSTR p)
	{
		bool nagtive=false;
		double num = 0;
		while(*p==L'+' || *p==L'-')
		{
			if(*p==L'-')nagtive = !nagtive;
			++p;
		}
		while(*p>=L'0' && *p<=L'9')//十进制表示
		{
			num = num *10 + *p - L'0';
			++p;
		}
		return nagtive?-num:num;
	}
	double VString::IntPow10(int i)
	{
		if(i>DBL_MAX_10_EXP)return DBL_MAX;
		if(i<-DBL_MAX_10_EXP)return 0;
		static double pw10[1+DBL_MAX_10_EXP] = {0};
		if(!*pw10){*pw10=1;for(int i=1;i<=DBL_MAX_10_EXP;++i)pw10[i]=pw10[i-1]*10;}
		return i>=0?pw10[i]:1/pw10[-i];
	}
	unsigned long long VString::GetChsValue(unsigned char* ptype,unsigned long long* pvalue,unsigned int len)const
    {
        unsigned long long result(0);
        unsigned int lastpt(len);//指针指向后一个单位
        if(len>1 && 0==ptype[len-1] && 1==ptype[len-2] && pvalue[len-2]>=100)//关注如二百五的情况
        {
            pvalue[len-1] *= pvalue[len-2]/10;
        }
        for(int i(len-1);i>=0;--i)//从后向前扫描
        {
            if(1==ptype[i])
            {
                if(lastpt<len && pvalue[i]<=pvalue[lastpt])//需要递归
                {
                    int j(i-1);
                    while(j>=0 && pvalue[j]<=pvalue[lastpt])--j;//寻找大单位，两个大单位之间递归
                    if(j<0 || (1==ptype[j] && pvalue[j]>pvalue[lastpt]))++j;
                    pvalue[j] = GetChsValue(ptype+j,pvalue+j,lastpt-j);
                    ptype[j] = 0;//变成数字处理
                    for(unsigned int k=1;lastpt+k<=len;++k)
                    {
                        ptype[j+k] = ptype[lastpt+k-1];
                        pvalue[j+k] = pvalue[lastpt+k-1];
                    }
                    len -= lastpt-1-j;
                    lastpt = j+1;
                    i = j;
                }
                else
                {
                    lastpt = i;
                }
            }
        }
        //扫描完毕，开始计算
        for(unsigned int i=0;i<len;++i)
        {
            if(1==ptype[i])//遇到单位
            {
                if(i)
                {
                    if(1==ptype[i-1] && 10==pvalue[i] && 20==pvalue[i-1])//非常规处理：“廿十”
                        continue;
                    if(1==ptype[i-1] || !pvalue[i-1])//非常规处理：单位紧挨如“千百”，或数值为0如“万零百”
                        result += pvalue[i];
                    else
                        result += pvalue[i-1]*pvalue[i];//正常赋值
                }
                else//单位打头
                    result = pvalue[i];
            }
            else if(i && !ptype[i-1])//遇到数字叠加
                pvalue[i] += pvalue[i-1]*10;
        }
        if(!ptype[len-1])
            result += pvalue[len-1];
        return result;
    }
	unsigned long long VString::ChsToUInt64(LPCWSTR wstr,unsigned int len)const
	{
		if(!wstr)wstr=wString;
		if(!len)len=Length;
        unsigned char* ptype = new unsigned char[len];//0代表数字，1代表单位
        unsigned long long* pvalue = new unsigned long long[len];//0~9代表0到9
        //数字字符串信息记录
        for(unsigned int k(0);k<len;++k)
        {
            unsigned int i(0);
            while(i<ChsNumMaxCount)//支持的数字字符查找
            {
                unsigned int j(0);
                while(j<pNumCounts[i])
                {
                    if(ppNumWChs[i][j]==wstr[k])
                    {
                        ptype[k] = 0;
                        pvalue[k] = i;
                        break;
                    }
                    ++j;
                }
                if(j<pNumCounts[i])break;
                ++i;
            }
            if(ChsNumMaxCount==i)//支持的单位字符查找
            {
                for(i=0;i<ChsUnitMaxCount;++i)
                {
                    unsigned int j(0);
                    while(j<pUnitCounts[i])
                    {
                        if(wstr[k]==ppUnitWChs[i][j])
                        {
                            ptype[k] = 1;
                            pvalue[k] = pUnitValue[i];
                            break;
                        }
                        ++j;
                    }
                    if(j<pUnitCounts[i])break;
                }
                if(ChsUnitMaxCount==i)//非数字非单位字符
                {
                    len = k;
                    break;
                }
            }
        }
        unsigned long long result = GetChsValue(ptype,pvalue,len);
        delete []ptype;
        delete []pvalue;
        return result;
	}
	long long VString::ChsToInt64()const
	{
		bool nagtive=false;
		LPWSTR p = const_cast<LPWSTR>(wString);
		int len = Length;
		while(*p==L'+' || *p==L'-' || *p==L'正' || *p==L'负' || *p==L'＋' ||*p==L'－')
		{
			if(*p==L'-' || *p==L'负' || *p==L'－')nagtive = !nagtive;
			++p;
			--len;
		}
		return nagtive?-(long long)ChsToUInt64(p,len):(long long)ChsToUInt64(p,len);
	}

	unsigned long long VString::ToUInt64()const
	{
		bool nagtive=false;
		unsigned long long num = 0;
		LPCWSTR p = ToUnicode();
		while(*p==L'+' || *p==L'-')
		{
			if(*p==L'-')nagtive = !nagtive;
			++p;
		}
		if(*p==L'0' && (*(p+1)==L'x' || *(p+1)==L'X'))//十六进制表示
		{
			p+=2;
			while(*p>=L'0' && *p<=L'9' || *p>=L'A'&&*p<=L'F' || *p>=L'a'&&*p<=L'f')
			{
				num = num *16 + ((*p>=L'0' && *p<=L'9')?*p-L'0':((*p>=L'A'&&*p<=L'F')?*p-L'A'+10:*p-L'a'+10));
				++p;
			}
		}
		else	while(*p>=L'0' && *p<=L'9')//十进制表示
		{
			num = num *10 + *p - L'0';
			++p;
		}
		return nagtive?-(signed long long)num:num;
	}
	long long VString::ToInt64()const
	{
		bool nagtive=false;
		long long num = 0;
		LPCWSTR p = ToUnicode();
		while(*p==L'+' || *p==L'-')
		{
			if(*p==L'-')nagtive = !nagtive;
			++p;
		}
		if(*p==L'0' && (*(p+1)==L'x' || *(p+1)==L'X'))//十六进制表示
		{
			p+=2;
			while(*p>=L'0' && *p<=L'9' || *p>=L'A'&&*p<=L'F' || *p>=L'a'&&*p<=L'f')
			{
				num = num *16 + ((*p>=L'0' && *p<=L'9')?*p-L'0':((*p>=L'A'&&*p<=L'F')?*p-L'A'+10:*p-L'a'+10));
				++p;
			}
		}
		else	while(*p>=L'0' && *p<=L'9')//十进制表示
		{
			num = num *10 + *p - L'0';
			++p;
		}
		return nagtive?-num:num;
	}
	double VString::ToDouble()const
	{
		LPWSTR p;
		LPWSTR endPosition=0;
		LPWSTR pointPosition;
		int length = Length;
		LPWSTR tmp = Strcpy(ToUnicode(),length);
		if(!tmp)return 0;
		pointPosition = tmp+length;
		for(p = tmp;*p;++p)//寻找小数点
		{	if(*p==L'.'){pointPosition = p;break;}}
		p = tmp;endPosition = p+length;
		for(LPWSTR i =tmp;i<endPosition;++i)//移除小数点
		{
			if(*i==L'.')continue;
			*p=*i;++p;
		}
		*p = 0;
		endPosition = p;
		LPWSTR startPosition = endPosition;
		LPWSTR expPosition = endPosition;
		for(p = tmp;*p;++p)//寻找起始数字
		{	if(*p<=L'9' && *p>L'0'){startPosition = p;break;}}
		for(p = tmp;*p;++p)//寻找指数
		{	if(*p==L'e' || *p==L'E'){expPosition = p+1;break;}}
		if(startPosition>=expPosition){delete []tmp;return 0;}
		double num = VString::ToIntDouble(tmp);//有效数字
		double exp =  VString::IntPow10(int( VString::ToIntDouble(expPosition)+(pointPosition<expPosition?(pointPosition-expPosition):0)));//指数
		delete []tmp;
		return num*exp;
	}
	bool operator==(const VString& vString1,const VString& vString2)//字符串比较
	{
		return !VString::Strcmp(vString1.wString,vString2.wString);
	}
	bool operator!=(const VString& vString1,const VString& vString2)
	{
		return VString::Strcmp(vString1.wString,vString2.wString)!=0;
	}
	bool operator>(const VString& vString1,const VString& vString2)
	{
		return VString::Strcmp(vString1.wString,vString2.wString)>0;
	}
	bool operator<(const VString& vString1,const VString& vString2)
	{
		return VString::Strcmp(vString1.wString,vString2.wString)<0;
	}
	bool operator>=(const VString& vString1,const VString& vString2)
	{
		return VString::Strcmp(vString1.wString,vString2.wString)>=0;
	}
	bool operator<=(const VString& vString1,const VString& vString2)
	{
		return VString::Strcmp(vString1.wString,vString2.wString)<=0;
	}

	VString operator+(const VString& vString1,const VString& vString2)
	{
		LPWSTR p = VString::Strcat(vString1.wString,vString2.wString);
		return VString(VString::Strlen(p),p,NULL);
	}
	VString operator+(const VString& vString,const XBase& xBase)
		{
			LPWSTR p = VString::Strcat(vString.wString,xBase.ToString().ToUnicode());
			return VString(VString::Strlen(p),p,NULL);
		}
	VString operator+(const XBase& xBase,const VString& vString)
	{
		LPWSTR p = VString::Strcat(xBase.ToString().ToUnicode(),vString.wString);
		return VString(VString::Strlen(p),p,NULL);
	}
	Iterator<WCHAR> VString::First(){return new IArrayIterator<WCHAR>(wString,wString,wString+Length);}
	Iterator<const WCHAR> VString::First()const{return new IArrayIterator<WCHAR>(wString,wString,wString+Length);}
	Iterator<WCHAR> VString::Last(){return new IArrayIterator<WCHAR>(wString,wString?wString+Length-1:NULL,wString+Length);}
	Iterator<const WCHAR> VString::Last()const{return new IArrayIterator<WCHAR>(wString,wString?wString+Length-1:NULL,wString+Length);}
	Iterator<WCHAR> VString::End(){return new IArrayIterator<WCHAR>(wString,wString+Length,wString+Length);}
	Iterator<const WCHAR> VString::End()const{return new IArrayIterator<WCHAR>(wString,wString+Length,wString+Length);}

	int VString::CompareTo(const XBase& object)const
	{
		return Strcmp(wString,object.ToString().ToUnicode());
	}

	//复制到多字节数组，返回复制的字节数，结尾的'\0'算一个字节
	int VString::CopyTo(XArray<char>& destination,int sourceByteIndex,int destinationByteIndex,int lengthOfByte)const
	{
		int maxlen = VString::Strlen(ToAnsi());
		if(maxlen<0)return 0;
		if(sourceByteIndex<0 || destinationByteIndex<0 )throw XException(E_INVALIDARG);//参数无效
		if(sourceByteIndex>maxlen  || destinationByteIndex>destination.GetLength())throw XException(COR_E_INDEXOUTOFRANGE);//越界
		if(lengthOfByte<0)
		{
			lengthOfByte = (int)destination.GetLength()-destinationByteIndex<=maxlen-sourceByteIndex?destination.GetLength()-destinationByteIndex:maxlen+1-sourceByteIndex;
		}
		if(!lengthOfByte)return 0;
		Memory::Copy(destination+destinationByteIndex,ToAnsi()+sourceByteIndex,lengthOfByte);
		return lengthOfByte;
	}
	//复制到Unicode数组，返回复制的字符数，结尾的'\0'算一个字符(两个字节)
	int VString::CopyTo(XArray<wchar_t> destination,int sourceIndex,int destinationIndex,int length)const
	{
		if(sourceIndex<0 || destinationIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(sourceIndex>Length ||  destinationIndex>destination.GetLength())throw XException(COR_E_INDEXOUTOFRANGE);//越界
		if(length<0)
		{
			length = (int)destination.GetLength()-destinationIndex<=Length-sourceIndex?destination.GetLength()-destinationIndex:Length+1-sourceIndex;
		}
		if(!length)return 0;
		Memory::Copy(destination+destinationIndex,ToUnicode()+sourceIndex,length*2);
		return length;
	}
	bool VString::Contains(const VString& xString)const
	{
		return VString::Find(*this,0,xString,0,Length,xString.Length,false)>=0;
	}
	int VString::CountOf(const VString& str)const
	{
		int count=0;
		for(int i=0;i+str.Length<=Length;)
		{
			if(memcmp(wString+i,str.wString,str.Length*2)==0)
			{
				i+=str.Length;
				count++;
			}
			else ++i;
		}
		return count;
	}
	int VString::CountOf(WCHAR wch)const
	{
		int count=0;
		for(int i=0;i<Length;++i)
		{
			if(wString[i]==wch)
			count++;
		}
		return count;
	}
	bool VString::EndsWith(const VString& xString)const//判断该字符串是否以xString结尾
	{
		if(Length<xString.Length || ! xString.Length)
			return false;
		return !memcmp(ToUnicode()+Length-xString.Length,xString.ToUnicode(),xString.Length);
	}
	bool VString::StartsWith(const VString& xString)const//判断该字符串是否以xString开头
	{
		if(Length<xString.Length)return false;
		return !memcmp(ToUnicode(),xString.ToUnicode(),xString.Length*2);
	}

	int VString::IndexOf(WCHAR wc)const//查找指定 Unicode 字符在此字符串中的第一个匹配项的索引。 
	{
		return VString::Strchr(wString,wc);
	}
	int VString::IndexOf(WCHAR wc,int startIndex,bool ignoreCase)const//指定起始位置并指定是否忽略大小写
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(Length<startIndex)throw XException(COR_E_INDEXOUTOFRANGE);//越界
		if(ignoreCase&&(wc>=L'A'&&wc<=L'Z' || wc>='a' && wc<='z'))
		{
			wc &= 0xcf;
			int i=startIndex;
			int len = Length;
			LPCWSTR p = ToUnicode();
			while(i<len)
			{
				if(p[i]==wc || p[i]==wc+32)break;
				++i;
			}
			if(i==len)return -1;
			return i;
		}
		int tmp =  VString::Strchr(ToUnicode()+startIndex,wc);
		if(tmp<0)return tmp;
		return tmp+startIndex;
	}
	int VString::IndexOf(WCHAR wc,int startIndex,int length,bool ignoreCase)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(Length<startIndex || Length<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);//越界
		if(ignoreCase&&(wc>=L'A'&&wc<=L'Z' || wc>='a' && wc<='z'))
		{
			wc &= 0xcf;
			int i=startIndex;
			int len = startIndex+length;
			LPCWSTR p = ToUnicode();
			while(i<len)
			{
				if(p[i]==wc || p[i]==wc+32)break;
				++i;
			}
			if(i==len)return -1;
			return i;
		}
		int tmp = VString::Strchr(ToUnicode()+startIndex,wc,length);
		if(tmp<0)return tmp;
		return tmp+startIndex;
	}

	int VString::IndexOf(const VString& xString)const//查找指定 字符串在此字符串中的第一个匹配项的索引。 
	{
		return VString::Find(*this,0,xString,0,Length,xString.Length,false);
	}
	int VString::IndexOf(const VString& xString,int startIndex,bool ignoreCase)const//指定起始位置并指定是否忽略大小写
	{
		if(Length<startIndex)throw XException(COR_E_INDEXOUTOFRANGE);//参数无效
		return VString::Find(*this,startIndex,xString,0,Length-startIndex,xString.Length,ignoreCase);
	}
	int VString::IndexOf(const VString& xString,int startIndex,int length,bool ignoreCase)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(Length<startIndex || Length<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);//越界
		return VString::Find(*this,startIndex,xString,0,length,xString.Length,ignoreCase);
	}
	//寻找wArray数组中任意字符在此字符串首次出现的位置（不包含结尾字符）
	int VString::IndexOfAny(const XArray<wchar_t> wArray, int startIndex,int length)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(Length<startIndex || Length<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);//越界
		if(length<0)length = Length-startIndex;
		if(!length)return -1;
		const wchar_t* p = wArray;
		const wchar_t* pd = ToUnicode();
		int len = wArray.GetLength();
		for(int i=startIndex;i<startIndex+length;++i)
		{
			for(int j=0;j<len;++j)
			{
				if(p[j]==pd[i])
					return i;
			}
		}
		return -1;
	}
	int VString::IndexOfAny(const XArray<wchar_t> wArray, int startIndex)const
	{
		return IndexOfAny( wArray,startIndex,-1);
	}

	VString& VString::Insert(int startIndex,const VString& xString)//返回在startIndex位置插入xString的新字符串，该字符串不变
	{
		return *this = VString(Length+xString.Length,VString::Strins(ToUnicode(),xString.ToUnicode(),startIndex,Length,xString.Length),NULL);
	}

	int VString::LastIndexOf(WCHAR wc)const//查找指定 Unicode 字符在此字符串中的最后一个匹配项的索引。 
	{
		LPCWSTR tmp = wcsrchr(wString,wc);
		if(tmp==NULL)
			return -1;
		return (int)(tmp-wString);
	}
	int VString::LastIndexOf(WCHAR wc,int startIndex,bool ignoreCase)const//指定起始位置并指定是否忽略大小写
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(ignoreCase&&(wc>=L'A'&&wc<=L'Z' || wc>='a' && wc<='z'))
		{
			LPCWSTR tmp = ToUnicode();
			wc&=0xcf;
			for(int i=Length-1;i>=startIndex;--i)
			{
				if(tmp[i]==wc || tmp[i]==wc+32)return i;
			}
			return -1;
		}
		LPCWSTR tmp = wcsrchr(ToUnicode()+startIndex,wc);
		if(tmp==NULL)
			return -1;
		return (int)(tmp-ToUnicode());
	}
	int VString::LastIndexOf(WCHAR wc,int startIndex,int length,bool ignoreCase)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(Length<startIndex || Length<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);//越界
		if(length<0)length = Length;
		else length+=startIndex;
		LPCWSTR tmp = ToUnicode();
		if(ignoreCase&&(wc>=L'A'&&wc<=L'Z' || wc>='a' && wc<='z'))
		{
			wc&=0xcf;
			for(int i=length-1;i>=startIndex;--i)
			{
				if(tmp[i]==wc || tmp[i]==wc+32)return i;
			}
		}
		else
			for(int i=length-1;i>=startIndex;--i)
			{
				if(tmp[i]==wc)return i;
			}
			return -1;
	}
	int VString::LastIndexOf(const VString& xString)const//查找指定 字符串在此字符串中的最后一个匹配项的索引。 
	{
		return VString::Last(*this,0,xString,0,Length,xString.Length,false);
	}
	int VString::LastIndexOf(const VString& xString,int startIndex,bool ignoreCase)const//指定起始位置并指定是否忽略大小写
	{
		if(startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);//参数无效
		return VString::Last(*this,startIndex,xString,0,Length,xString.Length,ignoreCase);
	}
	int VString::LastIndexOf(const VString& xString,int startIndex,int length,bool ignoreCase)const
	{
		if(Length<startIndex+length || startIndex>Length)throw XException(COR_E_INDEXOUTOFRANGE);//参数无效
		if(length<0)return VString::Last(*this,startIndex,xString,0,Length,xString.Length,ignoreCase);
		return VString::Last(*this,startIndex,xString,0,length+startIndex,xString.Length,ignoreCase);
	}
	//寻找wArray数组中任意字符在此字符串最后出现的位置（不包含结尾字符）
	int VString::LastIndexOfAny(const XArray<wchar_t> wArray,int startIndex,int length)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(Length<startIndex || Length<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);//越界
		if(length<0)length = Length-startIndex;
		if(!length)return -1;
		const wchar_t* p = wArray;
		const wchar_t* pd = ToUnicode();
		int len = wArray.GetLength();
		for(int i=startIndex+length-1;i>=startIndex;--i)
		{
			for(int j=0;j<len;++j)
			{
				if(p[j]==pd[i])
					return i;
			}
		}
		return -1;
	}
	int VString::LastIndexOfAny(const XArray<wchar_t> wArray, int startIndex)const
	{
		return LastIndexOfAny( wArray,startIndex,-1);
	}


	VString& VString::PadLeft(int totalWidth,WCHAR wc)//在左边插入一定数量的wc，使字符串右对齐,返回该字符串
	{
		if(totalWidth<0)throw XException(E_INVALIDARG);//参数无效
		if((totalWidth -= Length)<=0)return *this;
		return *this=VString(wc,totalWidth)+*this;
	}
	VString& VString::PadRight(int totalWidth,WCHAR wc)//在右边插入一定数量的wc，使字符串左对齐，
	{
		if(totalWidth<0)throw XException(E_INVALIDARG);//参数无效
		if((totalWidth-=Length)<=0)return *this;
		return *this+=VString(wc,totalWidth);
	}

	VString& VString::Remove(int startIndex,int length)//从startIndex起移除一定长度的内容，length小于0则表示移除后面所有的字符串
	{
		if(length<0)length = Length-startIndex;
		if(startIndex<0 || Length<=startIndex || startIndex+length>Length)return *this=Empty;
		if(startIndex==0 && length==Length)return *this=Empty;
		if(length==0)return *this;
		LPWSTR p = new WCHAR[startIndex+length+1];
		p[startIndex+length] = 0;
		Memory::Copy(p,ToUnicode(),startIndex*2);
		Memory::Copy(p+startIndex,ToUnicode()+startIndex+length,(Length-length-startIndex)*2);
		const_cast<int&>(Length) = startIndex+length;
		wString = p;
		mString = NULL;
		return *this;
	}
	VString& VString::Replace(WCHAR wc1,WCHAR wc2,bool ignoreCase)//返回一个新字符串，内容为原字符串中的wc1全替换为wc2
	{
		int len;
		if((len=Length)==0)return *this;
		LPCWSTR ws = ToUnicode();
		LPWSTR tmp= new WCHAR[len+1];
		if(ignoreCase && (wc1>=L'A'&&wc1<=L'Z' || wc1>='a' && wc1<='z'))
		{
			wc1&=0xcf;
			for(int i=0;i<len;++i)
			{
				if(ws[i]==wc1 || ws[i]==wc1+32)tmp[i]=wc2;
				else tmp[i]=ws[i];
			}
		}
		else for(int i=0;i<len;++i)
		{
			if(ws[i]==wc1)tmp[i]=wc2;
			else tmp[i]=ws[i];
		}
		tmp[len]=0;
		const_cast<int&>(Length) = len;
		wString = tmp;
		mString = NULL;
		return *this;
	}
	VString& VString::Replace(const VString& xString1 ,const VString& xString2,bool ignoreCase)//返回一个新字符串，内容为原字符串中的xString1全替换为xString2
	{
		int len=Length,count=0;//len表示该字符串长度，count表示替换次数
		if(!xString1.Length)return *this=Empty;
		if(len<xString1.Length)return *this;
		LPWSTR ws = VString::Strcpy(ToUnicode(),len);
		int len1 = xString1.Length;
		int len2 = xString2.Length;
		LPWSTR ws1 = VString::Strcpy(xString1.ToUnicode(),len1);
		LPWSTR ws2 = VString::Strcpy(xString2.ToUnicode(),len2);
		if(ignoreCase)
		{
			_wcslwr_s(ws,len+1);
			_wcslwr_s(ws1,len1+1);
		}
		for(int i=0;i+len1<=len;)
		{
			if(!memcmp(ws+i,ws1,len1))
			{
				++count;
				i+=len1;
				continue;
			}
			++i;
		}
		count = len+count*(len2-len1);
		LPWSTR tmp = new WCHAR[count+1];
		int t=0,tt=0;
		for(int i=0;i+len1<=len;)
		{
			if(!memcmp(ws+i,ws1,len1))
			{
				if(i>t)Memory::Copy(tmp+tt,ToUnicode()+t,(i-t)*2);
				tt+=i-t;
				if(len2)Memory::Copy(tmp+tt,xString2.ToUnicode(),len2*2);
				tt+=len2;
				i+=len1;
				t=i;
				continue;
			}
			++i;
		}
		if(len>t)Memory::Copy(tmp+tt,ToUnicode()+t,(len-t)*2);
		tmp[count]=0;
		delete []ws;
		delete []ws1;
		delete []ws2;
		delete []wString;
		delete []mString;
		const_cast<int&>(Length) = count;
		wString = tmp;
		mString = NULL;
		return *this;
	}

	VString& VString::ToUpper()//返回一个新字符串，新字符串为该所有的小写字母都变成大写
	{
		_wcsupr_s(wString,Length+1);
		return *this;
	}
	VString& VString::ToLower()//返回一个新字符串，新字符串为该字符串所有的大写字母都变成小写
	{
		_wcslwr_s(wString,Length+1);
		return *this;
	}
	//获取字符串中的英文单词（数字不算，比如“G2 VS2010”得到：“G”“VS”）
	XArray<VString> VString::GetWords()const
	{
		XArray<VString>strs;
		LPCWSTR pStart = ToUnicode();
		LPCWSTR pEnd = pStart+Length;
		LPWSTR p = const_cast<LPWSTR>(pStart);
		LPCWSTR start = pStart;
		bool alpha = *p>=L'a' && *p<=L'z' || *p>=L'A' && *p<=L'Z';
		while(++p<pEnd)
		{
			if(alpha)
			{
				if(alpha= *p>=L'a' && *p<=L'z' || *p>=L'A' && *p<=L'Z')continue;
				strs.Append(Substring(int(start-pStart),int(p-start)));
				continue;
			}
			if(!(alpha= *p>=L'a' && *p<=L'z' || *p>=L'A' && *p<=L'Z'))continue;
			start = p;
		}
		if(alpha)strs.Append(Substring(int(start-pStart),int(p-start)));
		return strs;
	}
	//获取字符串中的数字，比如“G2 VS2010”得到：“2010”
	XArray<VString> VString::GetNumbers()const
	{
		XArray<VString>strs;
		LPCWSTR pStart = ToUnicode();
		LPCWSTR pEnd = pStart+Length;
		LPWSTR p = const_cast<LPWSTR>(pStart);
		LPCWSTR start = pStart;
		bool alpha = *p>=L'0' && *p<=L'9';
		while(++p<pEnd)
		{
			if(alpha)
			{
				if(alpha=*p>=L'0' && *p<=L'9')continue;
				strs.Append(Substring(int(start-pStart),int(p-start)));
				continue;
			}
			if(!(alpha=*p>=L'0' && *p<=L'9'))continue;
			start = p;
		}
		if(alpha)strs.Append(Substring(int(start-pStart),int(p-start)));
		return strs;
	}
	//获取字符串中的英文和数字（英文和数字可连在一起，比如“G2 VS2010”得到：“G2”、“VS2010”）
	XArray<VString> VString::GetWordsAndNumbers()const
	{
		XArray<VString>strs;
		LPCWSTR pStart = ToUnicode();
		LPCWSTR pEnd = pStart+Length;
		LPWSTR p = const_cast<LPWSTR>(pStart);
		LPCWSTR start = pStart;
		bool alpha =  *p>=L'a' && *p<=L'z' || *p>=L'A' && *p<=L'Z' || *p>=L'0' && *p<=L'9';
		while(++p<pEnd)
		{
			if(alpha)
			{
				if(alpha=*p>=L'a' && *p<=L'z' || *p>=L'A' && *p<=L'Z' || *p>=L'0' && *p<=L'9')continue;
				strs.Append(Substring(int(start-pStart),int(p-start)));
				continue;
			}
			if(!(alpha=*p>=L'a' && *p<=L'z' || *p>=L'A' && *p<=L'Z' || *p>=L'0' && *p<=L'9'))continue;
			start = p;
		}
		if(alpha)strs.Append(Substring(int(start-pStart),int(p-start)));
		return strs;
	}
	//返回该字符串的数组表示（不包含结尾字符'\0'）
	XArray<WCHAR> VString::ToWCharArray(int startIndex,int length)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(Length<startIndex || Length<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);//越界
		if(length<0)length = Length-startIndex;
		if(!length)return XArray<WCHAR>(0);
		XArray<WCHAR>tmp(new VArray<WCHAR>(length));
		Memory::Copy(tmp,ToUnicode()+startIndex,sizeof(WCHAR)*length);
		return tmp;
	}
	VString VString::Substring(int startIndex,int length)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(Length<startIndex || Length<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);//越界
		if(length<0)length = Length-startIndex;
		if(length<=0)return Empty;
		if(length==Length)return *this;
		return VString(length,VString::Strcpy(ToUnicode()+startIndex,length),NULL);
	}
	//检索一个子字符串，当length<0时返回至结尾的子字符串 ,与Substring方法不同，这里的length表示字节长度，而且为了保证字符的完整性，返回的字符串的字节长度有可能小于指定的length。,startIndex<0或startIndex>Length将抛出异常
	VString VString::Cut(int startIndex, int length)const
	{
		if(startIndex<0 || startIndex>Length)throw XException(E_INVALIDARG);//参数无效
		if(length<0)return Substring(startIndex,length);
		if(!Length)return *this;
		int count = 0;
		int i;
		LPCWSTR pstr = ToUnicode();
		for(i=startIndex;i<Length;++i)
		{
			if(pstr[i]==L'\n' ||pstr[i]==L'\r')//回车与换行
			{
				if(pstr[i+1] + pstr[i]== L'\n'+ L'\r')
					++i;
				return Substring(startIndex,i+1-startIndex);
			}
			if(pstr[i]<128 && pstr[i]>0)
			{
				++count;
				if(count>=length)
				{
					if(pstr[i+1]==L'\n' || pstr[i+1]==L'\r')//回车与换行
					{
						++i;
						if(i<Length && pstr[i+1] + pstr[i]== L'\n'+ L'\r')
							++i;
					}
					return Substring(startIndex,i+1-startIndex);
				}
			}
			else
			{
				count+=2;
				if(count>=length)
				{
					if(count>length)return Substring(startIndex,i-startIndex);
					if(pstr[i+1]==L'\n' || pstr[i+1]==L'\r')//回车与换行
					{
						++i;
						if(i<Length && pstr[i+1] + pstr[i]== L'\n'+ L'\r')
							++i;
					}
					return Substring(startIndex,i+1-startIndex);
				}
			}
		}
		return Substring(startIndex,i-startIndex);
	}
	bool VString::Equals(const XBase& object)const
	{
		return !Strcmp(wString,object.ToString());
	}
	bool VString::Equals(const VString& object)const
	{
		return *this==object;
	}
	//返回使用指定字符做分隔符分割形成的字符串数组,并指定最大数量
	XArray<VString> VString::Split(WCHAR ch, int maxCount)const
	{
		if(maxCount<0)throw XException(E_INVALIDARG);//参数无效
		if(!Length || maxCount==0)return XArray<VString>(0);
		int len = Length;
		LPCWSTR p = ToUnicode();
		int count = 0;
		for(int i=0;i<len;++i)if(p[i]==ch)
		{
			if(count+1<maxCount)++count;
			else break;
		}
		VString* pstrs = new VString[count+1];
		int lasti = 0;
		count = 0;
		for(int i=0;i<len;++i)
		{
			if(p[i]==ch)
			{
				pstrs[count] = Substring(lasti,i-lasti);
				lasti = i+1;
				++count;
				if(count>=maxCount)
					break;
			}
		}
		if(count<maxCount)
		{
			pstrs[count] = Substring(lasti,len-lasti);
			return XArray<VString>(count+1,pstrs);
		}
		else
			return XArray<VString>(count,pstrs);
	}
	//返回使用指定字符做分隔符分割形成的字符串数组
	XArray<VString> VString::Split(WCHAR ch)const
	{
		return Split(ch,MaxValues::Int);
	}
	//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量
	XArray<VString> VString::Split(const VString& str,int maxCount)const
	{
		if(maxCount<0)throw XException(E_INVALIDARG);//参数无效
		if(maxCount==0 || str.IsEmpty())return XArray<VString>(0);
		if(Length<str.Length)return  XArray<VString>(1,*this);
		int len = Length-str.Length;
		LPCWSTR p = ToUnicode();
		int count = 0;
		for(int i=0;i<=len;)
			if(!memcmp(p+i,str.ToUnicode(),str.Length*2))
			{
				if(count+1<maxCount)++count;
				else break;
				i+=str.Length;
			}
			else ++i;
			VString* pstrs = new VString[count+1];
			int lasti = 0;
			count = 0;
			for(int i=0;i<=len;)
			{
				if(!memcmp(p+i,str.ToUnicode(),str.Length*2))
				{
					pstrs[count] = Substring(lasti,i-lasti);
					++count;
					if(count>=maxCount)
						break;
					i+=str.Length;
					lasti = i;
				}
				else ++i;
			}
			if(count<maxCount)
			{
				pstrs[count] = Substring(lasti,len+1-lasti);
				return XArray<VString>(count+1,pstrs);
			}
			else
				return XArray<VString>(count,pstrs);
	}
	//返回使用指定字符数组中出现的字符做分隔符分割形成的字符串数组,并指定最大数量,并指明是否移除空字符串
	XArray<VString> VString::Split(const XArray<WCHAR> chs,int maxCount,bool removeEmpty)const
	{
		if(maxCount<0)throw XException(E_INVALIDARG);//参数无效
		if(!Length || maxCount==0)return XArray<VString>(0);
		int len = Length;
		LPCWSTR p = ToUnicode();
		int count = 0;
		int lasti = 0;
		for(int i=0;i<len;++i)
		{
			int j;
			for(j=0;j<chs.Length;++j)
				if(p[i]==chs[j])break;
			if(j<chs.Length)
			{
				if(removeEmpty && lasti==i)
				{
					lasti = i+1;
					continue;
				}
				if(count+1<maxCount)++count;
				else break;
				lasti = i+1;
			}
		}
		VString* pstrs = new VString[count+1];
		count = 0;
		lasti=0;
		for(int i=0;i<len;++i)
		{
			int j;
			for(j=0;j<chs.Length;++j)
				if(p[i]==chs[j])break;
			if(j<chs.Length)
			{
				if(!removeEmpty || i>lasti)
				{
					pstrs[count] = Substring(lasti,i-lasti);
					++count;
				}
				lasti = i+1;
				if(count>=maxCount)
					break;
			}
		}
		if(count<maxCount && (!removeEmpty || len>lasti))
		{
			pstrs[count] = Substring(lasti,len-lasti);
			return XArray<VString>(count+1,pstrs);
		}
		else
			return XArray<VString>(count,pstrs);
	}
	//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量,并指明是否移除空字符串
	XArray<VString> VString::Split(const XArray<VString> strs,int maxCount,bool removeEmpty)const
	{
		if(maxCount<0)throw XException(E_INVALIDARG);//参数无效
		if(!Length || maxCount==0)return XArray<VString>(0);
		int len = Length;
		LPCWSTR p = ToUnicode();

		int count = 0;//分隔字符串数量（如果removeEmpty为true则连续的分隔符表示1个分隔符）
		int lasti = 0;//上一个分隔符末尾+1的位置
		for(int i=0;i<len;)
		{
			int j;
			for(j=0;j<strs.Length;++j)
				if(strs[j].Length && i+strs[j].Length<len && !memcmp(i+p,strs[j].ToUnicode(),strs[j].Length*2))break;
			if(j<strs.Length)
			{
				if(removeEmpty && lasti==i)
				{
					i += strs[j].Length;
					lasti = i;
					continue;
				}
				if(count+1<maxCount)++count;
				else break;
				i += strs[j].Length;
				lasti = i;
			}
			else ++i;
		}
		VString* pstrs = new VString[count+1];
		count = 0;
		lasti=0;
		for(int i=0;i<len;)
		{
			int j;
			for(j=0;j<strs.Length;++j)
				if(strs[j].Length && i+strs[j].Length<len && !memcmp(i+p,strs[j].ToUnicode(),strs[j].Length*2))break;
			if(j<strs.Length)
			{
				if(!removeEmpty || i>lasti)
				{
					pstrs[count] = Substring(lasti,i-lasti);
					++count;
				}
				i += strs[j].Length;
				lasti = i;
				if(count>=maxCount)
					break;
			}
			else ++i;
		}
		if(count<maxCount && (!removeEmpty || len>lasti))
		{
			pstrs[count] = Substring(lasti,len-lasti);
			return XArray<VString>(count+1,pstrs);
		}
		else
			return XArray<VString>(count,pstrs);
	}
	//返回使用指定字符数组中出现的字符做分隔符分割形成的字符串数组,并指定最大数量
	XArray<VString> VString::Split(const XArray<WCHAR> chs, int maxCount)const
	{
		return Split(chs,maxCount,false);
	}
	//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量
	XArray<VString> VString::Split(const XArray<VString> strs, int maxCount)const
	{
		return Split(strs, maxCount,false);
	}

#ifdef _CLR //托管支持
	VString::VString(volatile const System::String^string, int count)//创建由count个字符string串接而成的字符串
		:wString(NULL),mString(NULL),Length(0)
	{
		if(count<0)throw XException(E_INVALIDARG);//参数无效
		if(string)
		{
			IntPtr p = Marshal::StringToHGlobalUni((System::String^)string);
			LPCWSTR ws = (LPCWSTR)p.ToPointer();
			int len = ((System::String^)string)->Length;//单个字符串长度
			if(len+1)
			{
				const_cast<int&>(Length) = len*count;
				wString = new WCHAR[Length+1];
				if(len)
					while(count--)Memory::Copy(wString+len*count,ws,len+len);
				wString[Length]=0;
			}
			Marshal::FreeHGlobal(p);
		}
	}
	VString& VString::operator=(System::String^string)
	{
		if(string)
		{
			delete []wString;
			delete []mString;
			mString = 0;
			IntPtr p = Marshal::StringToHGlobalUni((System::String^)string);
			LPCWSTR ws = (LPCWSTR)p.ToPointer();
			const_cast<int&>(Length) = ((System::String^)string)->Length;//单个字符串长度
			wString = new WCHAR[Length+1];
			Memory::Copy(wString,ws,Length*2);
			wString[Length]=0;
			Marshal::FreeHGlobal(p);
			return *this;
		}
			throw XException(E_POINTER);
		}
	VString operator+(const VString& xString,System::Object^ obj)
	{
		return xString+VString(obj->ToString());
	}
	VString operator+(System::Object^ obj,const VString& xString)
	{
		return VString(obj->ToString())+xString;
	}
	VString operator+(const VString& xString,volatile const System::String^ string)
	{
		return xString+VString(string);
	}
	VString operator+(volatile const System::String^ string,const VString& xString)
	{
		return VString(string)+xString;
	}
#endif



	//XString
	VString* XString::Pointer()const{return reinterpret_cast<VString*const>(XBase::Pointer());}

	const XTypes& XString::CurrentType = CREATECLASSTYPE(LJ::XString,LJ::XBase);
	int XString::Compare(const XString xString1,const XString xString2,bool ignoreCase)//比较两个字符串的大小,指定是否考虑大小写
	{
		if(xString1.IsNull() || xString2.IsNull())throw XException(E_POINTER);
		if(ignoreCase)return _wcsicmp(((VString*)xString1.pObject)->ToUnicode(),((VString*)xString2.pObject)->ToUnicode());
		return VString::Strcmp(((VString*)xString1.pObject)->ToUnicode(),((VString*)xString2.pObject)->ToUnicode());
	}
	int XString::Compare(const XString xString1,int index1,const XString xString2,int index2,int length,bool ignoreCase)//比较两个字符串的大小，指定是否忽略大小写
	{
		if(index1<0 || index2<0)throw XException(E_INVALIDARG);//参数无效
		if(xString1.IsNull() || xString2.IsNull())throw XException(E_POINTER);
		if(ignoreCase)return _wcsnicmp(((VString*)xString1.pObject)->ToUnicode()+index1,((VString*)xString2.pObject)->ToUnicode()+index2,length);
		return VString::Strcmp(((VString*)xString1.pObject)->ToUnicode()+index1,((VString*)xString2.pObject)->ToUnicode()+index2,length);
	}
	XString XString::Concat(const XBase& object1,const XBase& object2)
	{
		return XString(object1.ToString(),object2.ToString());
	}
	XString XString::Concat(const XBase& object1,const XBase& object2,const XBase& object3)
	{
		return XString(object1.ToString(),object2.ToString(),object3.ToString());
	}
	XString XString::Concat(const XBase& object1,const XBase& object2,const XBase& object3,const XBase& object4)
	{
		return XString(object1.ToString(),object2.ToString(),object3.ToString(),object4.ToString());
	}
	XString XString::Concat(const XArray<XString> strings)
	{
		int len =0;
		for(int i=0;i<(int)strings.GetLength();++i)len += strings[i].GetLength();
		LPWSTR p = new WCHAR[len+1];
		len = 0;
		for(int i=0;i<(int)strings.GetLength();++i)
		{
			if(strings[i].GetLength())Memory::Copy(p+len,strings[i].ToUnicode(),strings[i].GetLength()*2);
			len+=strings[i].GetLength();
		}
		p[len]=0;
		return XString(new VString(len,p));
	}
	XString XString::Concat(const XArray<XBase*> strings)
	{
		int len =0;
		for(int i=0;i<(int)strings.GetLength();++i)if(strings[i])len += strings[i]->ToString().GetLength();
		LPWSTR p = new WCHAR[len+1];
		len = 0;
		for(int i=0;i<(int)strings.GetLength();++i)
		{
			if(strings[i])
			{
				XString tmp(strings[i]->ToString());
				Memory::Copy(p+len,tmp.ToUnicode(),tmp.GetLength()*2);
				len+=tmp.GetLength();
			}
		}
		p[len]=0;
		return XString(new VString(len,p));
	}
	XString XString::Join(const XString str,const XArray<XString> strs,int startIndex,int count)
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(startIndex>strs.GetLength())throw XException(COR_E_INDEXOUTOFRANGE);
		if(!strs.GetLength())return XString();
		if(count<0)count = strs.GetLength()-startIndex;
		int len = (count-1)*str.GetLength();
		for(int i=startIndex;i<startIndex+count;++i)len+=strs[i].GetLength();
		LPWSTR p = new WCHAR[len+1];
		len = 0;
		for(int i=startIndex;i+1<(int)startIndex+count;++i)
		{
			if(strs[i].GetLength())Memory::Copy(p+len,strs[i].ToUnicode(),strs[i].GetLength()*2);
			len+=strs[i].GetLength();
			if(str.GetLength())Memory::Copy(p+len,strs[i].ToUnicode(),str.GetLength()*2);
			len+=str.GetLength();
		}
		if(strs[startIndex+count-1].GetLength())Memory::Copy(p+len,strs[startIndex+count-1].ToUnicode(),strs[startIndex+count-1].GetLength()*2);
		len+=strs[startIndex+count-1].GetLength();
		p[len]=0;
		return XString(new VString(len,p));
	}

	XString::XString(const XString&x):XBase(x){XSTRINGCITEDCHANGE(pString);}
	XString::XString(VString*p):XBase(p){XSTRINGCITEDCHANGE(pString);}
	//由VString创建
	XString::XString(const VString& vs,int count):XBase(new VString(vs,count)){XSTRINGCITEDCHANGE(pString);}
	//由数字创建字符串
	XString::XString(float number,LPCWSTR format):XBase(new VString(number,format)){XSTRINGCITEDCHANGE(pString);}
	//由数字创建字符串
	XString::XString(double number,LPCWSTR format):XBase(new VString(number,format)){XSTRINGCITEDCHANGE(pString);}
	//由数字创建字符串
	XString::XString(unsigned long long number,LPCWSTR format):XBase(new VString(number,format)){XSTRINGCITEDCHANGE(pString);}
	//由数字创建字符串
	XString::XString(unsigned long number,LPCWSTR format):XBase(new VString(number,format)){XSTRINGCITEDCHANGE(pString);}
	//由数字创建字符串
	XString::XString(unsigned int number,LPCWSTR format):XBase(new VString(number,format)){XSTRINGCITEDCHANGE(pString);}
	//由数字创建字符串
	XString::XString(long long number,LPCWSTR format):XBase(new VString(number,format)){XSTRINGCITEDCHANGE(pString);}
	//由数字创建字符串
	XString::XString(long number,LPCWSTR format):XBase(new VString(number,format)){XSTRINGCITEDCHANGE(pString);}
	//由数字创建字符串
	XString::XString(int number,LPCWSTR format):XBase(new VString(number,format)){XSTRINGCITEDCHANGE(pString);}
	//由数字创建字符串
	XString::XString(unsigned short number,LPCWSTR format):XBase(new VString(number,format)){XSTRINGCITEDCHANGE(pString);}
	//由数字创建字符串
	XString::XString(short number,LPCWSTR format):XBase(new VString(number,format)){XSTRINGCITEDCHANGE(pString);}
	//由数字创建字符串
	XString::XString(unsigned char number,LPCWSTR format):XBase(new VString(number,format)){XSTRINGCITEDCHANGE(pString);}
	//由数字创建字符串
	XString::XString(signed char number,LPCWSTR format):XBase(new VString(number,format)){XSTRINGCITEDCHANGE(pString);}
	//创建由count个字符c串接而成的字符串
	XString::XString(CHAR c,int count):XBase(new VString(c,count)){XSTRINGCITEDCHANGE(pString);}
	//创建由count个Unicode字符wc串接而成的字符串
	XString::XString(WCHAR wc,int count):XBase(new VString(wc,count)){XSTRINGCITEDCHANGE(pString);}
	//创建由count个wString字符串串接而成的字符串
	XString::XString(LPCWSTR wString,int count):XBase(new VString(wString,count)){XSTRINGCITEDCHANGE(pString);}
	//创建由count个mString字符串串接而成的字符串
	XString::XString(LPCSTR mString,int count):XBase(new VString(mString,count)){XSTRINGCITEDCHANGE(pString);}
	//创建由count个wString字符串串接而成的字符串
	XString::XString(const XArray<WCHAR> wString,int count):XBase(new VString(wString,count)){XSTRINGCITEDCHANGE(pString);}
	//创建由count个mString字符串串接而成的字符串
	XString::XString(const XArray<CHAR> mString,int count):XBase(new VString(mString,count)){XSTRINGCITEDCHANGE(pString);}
	XString::XString(LPCWSTR wString,int startIndex,int length)//创建由wString字符串startindex字符起数length个字符的字符串，如果length<=-2，则表示到'\0'表示的结尾
		:XBase(length<0?new VString(VString::Strlen(wString+startIndex),VString::Strcpy(wString+startIndex),NULL):
		new VString(length,VString::Strcpy(wString+startIndex,length),NULL))//引用计数自动加1
	{XSTRINGCITEDCHANGE(pString);}
	XString::XString(LPCSTR mString,int startIndex,int length)//创建由mString字符串startindex字符起数length个字符的字符串，如果length<=-2，则表示到'\0'表示的结尾
		:XBase(new VString(0,VString::AnsiToUnicode(mString+startIndex,&length,length),NULL))//引用计数自动加1
	{
		XSTRINGCITEDCHANGE(pString);
		const_cast<int&>(((VString*)pObject)->Length) = length;
	}

	//创建由count个xString字符串串接而成的字符串
	XString::XString(const XString xString,int count)
		:XBase(1==count?xString.pObject:NULL)//引用计数自动加1
	{
		if(count<0)throw XException(E_INVALIDARG);//参数无效
		if(count>1)
		{
			XString xs((VString*)xString.pObject);//防止被释放,以及提供多线程操作的安全性
			LPCWSTR tmp = xs.ToUnicode();
			int length =xs.GetLength();
			LPWSTR p = new WCHAR[length*count+1];
			p[length*count] = 0;
			pObject = (new VString(length*count,p,NULL))->ReferenceIncrement();
			while(count--)Memory::Copy(p+count*length,tmp,length*2);
		}
		XSTRINGCITEDCHANGE(pString);
	}
	//创建由两个xString串接而成的字符串
	XString::XString(const XString xs1,const XString xs2)
		:XBase()
	{
		if(xs1.IsNull() || xs2.IsNull())throw XException(E_POINTER);
		pObject = (new VString(xs1.GetLength()+xs2.GetLength(),
			VString::Strcat(xs1.ToUnicode(),xs2.ToUnicode(),
			xs1.GetLength(),xs2.GetLength()),NULL))->ReferenceIncrement();
		XSTRINGCITEDCHANGE(pString);
	}
	//创建由三个xString串接而成的字符串
	XString::XString(const XString xs1,const XString xs2,const  XString xs3)
		:XBase()
	{
		if(xs1.IsNull() || xs2.IsNull() || xs3.IsNull())throw XException(E_POINTER);
		pObject = (new VString(xs1.GetLength()+xs2.GetLength()+xs3.GetLength(),
			VString::Strcat(xs1.ToUnicode(),xs2.ToUnicode(),xs3.ToUnicode(),
			xs1.GetLength(),xs2.GetLength(),xs3.GetLength()),NULL))->ReferenceIncrement();
		XSTRINGCITEDCHANGE(pString);
	}
	//创建由四个xString串接而成的字符串
	XString::XString(const XString xs1,const XString xs2,const  XString xs3,const  XString xs4)
		:XBase()
	{
		if(xs1.IsNull() || xs2.IsNull() || xs3.IsNull() || xs4.IsNull())throw XException(E_POINTER);
		pObject = (new VString(xs1.GetLength()+xs2.GetLength()+xs3.GetLength()+xs4.GetLength(),
			VString::Strcat(xs1.ToUnicode(),xs2.ToUnicode(),xs3.ToUnicode(),xs4.ToUnicode(),
			xs1.GetLength(),xs2.GetLength(),xs3.GetLength(),xs4.GetLength()),NULL))->ReferenceIncrement();
		XSTRINGCITEDCHANGE(pString);
	}
	//创建由xStrings数组串接而成的字符串
	XString::XString(const XArray<XString>xStrings)
		:XBase()
	{
		XArray<XString> xa(xStrings);
		if(xa.Length<0)throw XException(E_INVALIDARG);//参数无效
		else if(xa.Length)
		{
			int length=0;
			for(int i=0;i<xa.Length;++i)length+= xa[i].GetLength();
			LPWSTR p = new WCHAR[length+1];
			p[length]=0;
			length=0;
			for(int i=0;i<xa.Length;++i)
			{
				Memory::Copy(p+length,xa[i].ToUnicode(),xa[i].GetLength());
				length+= xa[i].GetLength();
			}
			pObject = (new VString(length,p,NULL))->ReferenceIncrement();
		}
		XSTRINGCITEDCHANGE(pString);
	}
	WCHAR XString::operator[](int index)const
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		if(index>=0 && index<=GetLength())
		{
			return ((VString*)pObject)->ToUnicode()[index];
		}
		//抛出异常
		throw XException(E_INVALIDARG);//参数无效
	}
	Iterator<const WCHAR> XString::First()const{return new IArrayIterator<WCHAR>(ToUnicode(),ToUnicode(),ToUnicode()+GetLength());}
	Iterator<const WCHAR> XString::Last()const{return new IArrayIterator<WCHAR>(ToUnicode(),ToUnicode()?ToUnicode()+GetLength()-1:NULL,ToUnicode()+GetLength());}
	Iterator<const WCHAR> XString::End()const{return new IArrayIterator<WCHAR>(ToUnicode(),ToUnicode()+GetLength(),ToUnicode()+GetLength());}
	Iterator<const WCHAR> XString::begin()const{return First();}
	Iterator<const WCHAR> XString::end()const{return End();}
	int XString::GetLength()const
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		return ((VString*)pObject)->Length;
	}

	XString XString::ToString()const
	{
		return *this;
	}
	LPCSTR XString::ToAnsi()const//转换成原始的多字节字符串，const型
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		return ((VString*)pObject)->ToAnsi();
	}
	LPCWSTR XString::ToUnicode()const//输出Unicode字符串，const型
	{
		if(!pObject)throw XException("XString的引用为空",E_POINTER);//引用为空
		return ((VString*)pObject)->ToUnicode();
	}
	unsigned long long XString::ToUInt64()const
	{
		return IsNull()?throw XException(E_POINTER):((VString*)pObject)->ToUInt64();
	}
	long long XString::ToInt64()const
	{
		return IsNull()?throw XException(E_POINTER):((VString*)pObject)->ToInt64();
	}
	double XString::ToDouble()const
	{
		return IsNull()?throw XException(E_POINTER):((VString*)pObject)->ToDouble();
	}
	unsigned long long XString::ChsToUInt64()const
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		return ((VString*)pObject)->ChsToUInt64();
	}
	long long XString::ChsToInt64()const
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		return ((VString*)pObject)->ChsToInt64();
	}

	XString::operator LPCSTR()const
	{
		return ToAnsi();
	}
	XString::operator LPCWSTR()const
	{
		return ToUnicode();
	}

	XString& XString::operator=(const XString& xString)//赋值运算
	{
		*static_cast<XBase*const&>(this)=xString;
		XSTRINGCITEDCHANGE(pString);
		return *this;
	}
	XString& XString::operator=(LPCSTR mString)
	{
		*this=XString(mString);
		XSTRINGCITEDCHANGE(pString);
		return *this;
	}
	XString& XString::operator=(LPCWSTR wString)
	{
		*this=XString(wString);
		XSTRINGCITEDCHANGE(pString);
		return *this;
	}
	XString& XString::operator+=(const XString& xString)//串接运算
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		*this=XString(*this,xString);
		XSTRINGCITEDCHANGE(pString);
		return *this;
	}
	XString& XString::operator+=(const XBase& xBase)
	{
		*this+=xBase.ToString();
		XSTRINGCITEDCHANGE(pString);
		return *this;
	}
	bool operator==(const XString& xString1,const XString& xString2)//字符串比较
	{
		if(xString1.IsNull() || xString2.IsNull())throw XException(E_POINTER);//字符串为空
		return xString1.pObject==xString2.pObject || *reinterpret_cast<VString*const &>(xString1.pObject) == *reinterpret_cast<VString*const &>(xString2.pObject);
	}
	bool operator!=(const XString& xString1,const XString& xString2)
	{
		if(xString1.IsNull() || xString2.IsNull())throw XException(E_POINTER);//字符串为空
		return *(VString*)xString1.pObject != *(VString*)xString2.pObject;
	}
	bool operator>(const XString& xString1,const XString& xString2)
	{
		if(xString1.IsNull() || xString2.IsNull())throw XException(E_POINTER);//字符串为空
		return *(VString*)xString1.pObject > *(VString*)xString2.pObject;
	}
	bool operator<(const XString& xString1,const XString& xString2)
	{
		if(xString1.IsNull() || xString2.IsNull())throw XException(E_POINTER);//字符串为空
		return *(VString*)xString1.pObject < *(VString*)xString2.pObject;
	}
	bool operator>=(const XString& xString1,const XString& xString2)
	{
		if(xString1.IsNull() || xString2.IsNull())throw XException(E_POINTER);//字符串为空
		return *(VString*)xString1.pObject >= *(VString*)xString2.pObject;
	}
	bool operator<=(const XString& xString1,const XString& xString2)
	{
		if(xString1.IsNull() || xString2.IsNull())throw XException(E_POINTER);//字符串为空
		return *(VString*)xString1.pObject <= *(VString*)xString2.pObject;
	}
	bool operator==(const XString& xString1,LPCWSTR xString2){return VString::Strcmp(xString1,xString2)==0;}
	bool operator==(LPCWSTR xString1,const XString& xString2){return VString::Strcmp(xString1,xString2)==0;}
	bool operator==(const XString& xString1,LPCSTR xString2){return VString::Strcmp(xString1,xString2)==0;}
	bool operator==(LPCSTR xString1,const XString& xString2){return VString::Strcmp(xString1,xString2)==0;}
	bool operator!=(const XString& xString1,LPCWSTR xString2){return VString::Strcmp(xString1,xString2)!=0;}
	bool operator!=(LPCWSTR xString1,const XString& xString2){return VString::Strcmp(xString1,xString2)!=0;}
	bool operator!=(const XString& xString1,LPCSTR xString2){return VString::Strcmp(xString1,xString2)!=0;}
	bool operator!=(LPCSTR xString1,const XString& xString2){return VString::Strcmp(xString1,xString2)!=0;}
	bool operator>(const XString& xString1,LPCWSTR xString2){return VString::Strcmp(xString1,xString2)>0;}
	bool operator>(LPCWSTR xString1,const XString& xString2){return VString::Strcmp(xString1,xString2)>0;}
	bool operator>(const XString& xString1,LPCSTR xString2){return VString::Strcmp(xString1,xString2)>0;}
	bool operator>(LPCSTR xString1,const XString& xString2){return VString::Strcmp(xString1,xString2)>0;}
	bool operator<(const XString& xString1,LPCWSTR xString2){return VString::Strcmp(xString1,xString2)<0;}
	bool operator<(LPCWSTR xString1,const XString& xString2){return VString::Strcmp(xString1,xString2)<0;}
	bool operator<(const XString& xString1,LPCSTR xString2){return VString::Strcmp(xString1,xString2)<0;}
	bool operator<(LPCSTR xString1,const XString& xString2){return VString::Strcmp(xString1,xString2)<0;}
	bool operator>=(const XString& xString1,LPCWSTR xString2){return VString::Strcmp(xString1,xString2)>=0;}
	bool operator>=(LPCWSTR xString1,const XString& xString2){return VString::Strcmp(xString1,xString2)>=0;}
	bool operator>=(const XString& xString1,LPCSTR xString2){return VString::Strcmp(xString1,xString2)>=0;}
	bool operator>=(LPCSTR xString1,const XString& xString2){return VString::Strcmp(xString1,xString2)>=0;}
	bool operator<=(const XString& xString1,LPCWSTR xString2){return VString::Strcmp(xString1,xString2)<=0;}
	bool operator<=(LPCWSTR xString1,const XString& xString2){return VString::Strcmp(xString1,xString2)<=0;}
	bool operator<=(const XString& xString1,LPCSTR xString2){return VString::Strcmp(xString1,xString2)<=0;}
	bool operator<=(LPCSTR xString1,const XString& xString2){return VString::Strcmp(xString1,xString2)<=0;}

	XString operator+(const XString& xString1,const XString& xString2)
	{
		return XString(xString1,xString2);
	}

	XString operator+(const XString& xString,const XBase& xBase)
	{
		return xString+xBase.ToString();
	}
	XString operator+(const XBase& xBase,const XString& xString)
	{
		return xBase.ToString()+xString;
	}
	XString operator+(const XString& xString1,LPCWSTR xString2)
	{return xString1+XString(xString2);}
	XString operator+(LPCWSTR xString1,const XString& xString2)
	{return XString(xString1)+xString2;}
	XString operator+(const XString& xString1,LPCSTR xString2)
	{return xString1+XString(xString2);}
	XString operator+(LPCSTR xString1,const XString& xString2)
	{return XString(xString1)+xString2;}

	int XString::CompareTo(const XBase& object)const
	{
		return Compare(*this,object.ToString());
	}
	int XString::CompareTo(const XString& string)const
	{
		return Compare(*this,string);
	}
	//复制到多字节数组，返回复制的字节数，结尾的'\0'算一个字节
	int XString::CopyTo(XArray<char> destination,int sourceByteIndex,int destinationByteIndex,int lengthOfByte)const
	{
		int maxlen = VString::Strlen(ToAnsi());
		if(maxlen<0)return 0;
		if(sourceByteIndex<0 ||  destinationByteIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(sourceByteIndex>maxlen  || destinationByteIndex>destination.GetLength())throw XException(COR_E_INDEXOUTOFRANGE);
		if(lengthOfByte<0)
		{
			lengthOfByte = destination.GetLength()-destinationByteIndex<=maxlen-sourceByteIndex?destination.GetLength()-destinationByteIndex:maxlen+1-sourceByteIndex;
		}
		if(!lengthOfByte)return 0;
		Memory::Copy(destination+destinationByteIndex,ToAnsi()+sourceByteIndex,lengthOfByte);
		return lengthOfByte;
	}
	//复制到Unicode数组，返回复制的字符数，结尾的'\0'算一个字符(两个字节)
	int XString::CopyTo(XArray<wchar_t> destination,int sourceIndex,int destinationIndex,int length)const
	{
		if(sourceIndex<0 || destinationIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(sourceIndex>GetLength() || destinationIndex>destination.GetLength())throw XException(COR_E_INDEXOUTOFRANGE);
		if(length<0)
		{
			length = (int)destination.GetLength()-destinationIndex<=GetLength()-sourceIndex?destination.GetLength()-destinationIndex:GetLength()+1-sourceIndex;
		}
		if(!length)return 0;
		Memory::Copy(destination+destinationIndex,ToUnicode()+sourceIndex,length*2);
		return length;
	}
	bool XString::Contains(const XString& xString)const
	{
		return VString::Find(*(VString*)pObject,0,*(VString*)xString.pObject,0,GetLength(),xString.GetLength(),false)>=0;
	}
	int XString::CountOf(WCHAR wch)const
	{
		return Pointer()->CountOf(wch);
	}
	int XString::CountOf(const XString& str)const
	{
		return Pointer()->CountOf(*str.Pointer());
	}
	bool XString::EndsWith(const XString& xString)const//判断该字符串是否以xString结尾
	{
		int len = xString.GetLength();
		if(GetLength()<len || ! len)
			return false;
		return !memcmp(ToUnicode()+GetLength()-len,xString.ToUnicode(),len);
	}
	bool XString::StartsWith(const XString& xString)const//判断该字符串是否以xString开头
	{
		if(GetLength()<xString.GetLength())return false;
		return !memcmp(ToUnicode(),xString.ToUnicode(),xString.GetLength()*2);
	}

	int XString::IndexOf(WCHAR wc)const//查找指定 Unicode 字符在此字符串中的第一个匹配项的索引。 
	{
		return VString::Strchr(ToUnicode(),wc);
	}
	int XString::IndexOf(WCHAR wc,int startIndex,bool ignoreCase)const//指定起始位置并指定是否忽略大小写
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(GetLength()<startIndex)throw XException(COR_E_INDEXOUTOFRANGE);
		if(ignoreCase&&(wc>=L'A'&&wc<=L'Z' || wc>='a' && wc<='z'))
		{
			wc &= 0xcf;
			int i=startIndex;
			int len = GetLength();
			LPCWSTR p = ToUnicode();
			while(i<len)
			{
				if(p[i]==wc || p[i]==wc+32)break;
				++i;
			}
			if(i==len)return -1;
			return i;
		}
		int tmp =  VString::Strchr(ToUnicode()+startIndex,wc);
		if(tmp<0)return tmp;
		return tmp+startIndex;
	}
	int XString::IndexOf(WCHAR wc,int startIndex,int length,bool ignoreCase)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(GetLength()<startIndex || GetLength()<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(ignoreCase&&(wc>=L'A'&&wc<=L'Z' || wc>='a' && wc<='z'))
		{
			wc &= 0xcf;
			int i=startIndex;
			int len = startIndex+length;
			LPCWSTR p = ToUnicode();
			while(i<len)
			{
				if(p[i]==wc || p[i]==wc+32)break;
				++i;
			}
			if(i==len)return -1;
			return i;
		}
		int tmp = VString::Strchr(ToUnicode()+startIndex,wc,length);
		if(tmp<0)return tmp;
		return tmp+startIndex;
	}

	int XString::IndexOf(const XString& xString)const//查找指定 字符串在此字符串中的第一个匹配项的索引。 
	{
		return VString::Find(*(VString*)pObject,0,*(VString*)xString.pObject,0,GetLength(),xString.GetLength(),false);
	}
	int XString::IndexOf(const XString& xString,int startIndex,bool ignoreCase)const//指定起始位置并指定是否忽略大小写
	{
		if(GetLength()<startIndex)throw XException(COR_E_INDEXOUTOFRANGE);//参数无效
		return VString::Find(*(VString*)pObject,startIndex,*(VString*)xString.pObject,0,GetLength()-startIndex,xString.GetLength(),ignoreCase);
	}
	int XString::IndexOf(const XString& xString,int startIndex,int length,bool ignoreCase)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(GetLength()<startIndex || GetLength()<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);
		return VString::Find(*(VString*)pObject,startIndex,*(VString*)xString.pObject,0,length,xString.GetLength(),ignoreCase);
	}
	//寻找wArray数组中任意字符在此字符串首次出现的位置（不包含结尾字符）
	int XString::IndexOfAny(const XArray<wchar_t> wArray, int startIndex,int length)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(GetLength()<startIndex || GetLength()<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(length<0)length = GetLength()-startIndex;
		if(!length)return -1;
		const wchar_t* p = wArray;
		const wchar_t* pd = ToUnicode();
		int len = wArray.GetLength();
		for(int i=startIndex;i<startIndex+length;++i)
		{
			for(int j=0;j<len;++j)
			{
				if(p[j]==pd[i])
					return i;
			}
		}
		return -1;
	}
	int XString::IndexOfAny(const XArray<wchar_t> wArray, int startIndex)const
	{
		return IndexOfAny( wArray,startIndex,-1);
	}

	XString XString::Insert(int startIndex,const XString& xString)const//返回在startIndex位置插入xString的新字符串，该字符串不变
	{
		if(IsNull() || xString.IsNull())throw XException(E_POINTER);
		return XString(new VString(GetLength()+xString.GetLength(),VString::Strins(ToUnicode(),xString.ToUnicode(),startIndex,GetLength(),xString.GetLength()),NULL));
	}

	int XString::LastIndexOf(WCHAR wc)const//查找指定 Unicode 字符在此字符串中的最后一个匹配项的索引。 
	{
		LPCWSTR tmp = wcsrchr(ToUnicode(),wc);
		if(tmp==NULL)
			return -1;
		return (int)(tmp-ToUnicode());
	}
	int XString::LastIndexOf(WCHAR wc,int startIndex,bool ignoreCase)const//指定起始位置并指定是否忽略大小写
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(ignoreCase&&(wc>=L'A'&&wc<=L'Z' || wc>='a' && wc<='z'))
		{
			LPCWSTR tmp = ToUnicode();
			wc&=0xcf;
			for(int i=GetLength()-1;i>=startIndex;--i)
			{
				if(tmp[i]==wc || tmp[i]==wc+32)return i;
			}
			return -1;
		}
		LPCWSTR tmp = wcsrchr(ToUnicode()+startIndex,wc);
		if(tmp==NULL)
			return -1;
		return (int)(tmp-ToUnicode());
	}
	int XString::LastIndexOf(WCHAR wc,int startIndex,int length,bool ignoreCase)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(GetLength()<startIndex || GetLength()<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(length<0)length = GetLength();
		else length+=startIndex;
		LPCWSTR tmp = ToUnicode();
		if(ignoreCase&&(wc>=L'A'&&wc<=L'Z' || wc>='a' && wc<='z'))
		{
			wc&=0xcf;
			for(int i=length-1;i>=startIndex;--i)
			{
				if(tmp[i]==wc || tmp[i]==wc+32)return i;
			}
		}
		else
			for(int i=length-1;i>=startIndex;--i)
			{
				if(tmp[i]==wc)return i;
			}
			return -1;
	}
	int XString::LastIndexOf(const XString xString)const//查找指定 字符串在此字符串中的最后一个匹配项的索引。 
	{
		return VString::Last(*(VString*)pObject,0,*(VString*)xString.pObject,0,GetLength(),xString.GetLength(),false);
	}
	int XString::LastIndexOf(const XString xString,int startIndex,bool ignoreCase)const//指定起始位置并指定是否忽略大小写
	{
		if(startIndex>GetLength())throw XException(COR_E_INDEXOUTOFRANGE);//参数无效
		return VString::Last(*(VString*)pObject,startIndex,*(VString*)xString.pObject,0,GetLength(),xString.GetLength(),ignoreCase);
	}
	int XString::LastIndexOf(const XString xString,int startIndex,int length,bool ignoreCase)const
	{
		if(GetLength()<startIndex+length || startIndex>GetLength())throw XException(COR_E_INDEXOUTOFRANGE);//参数无效
		if(length<0)return VString::Last(*(VString*)pObject,startIndex,*(VString*)xString.pObject,0,GetLength(),xString.GetLength(),ignoreCase);
		return VString::Last(*(VString*)pObject,startIndex,*(VString*)xString.pObject,0,length+startIndex,xString.GetLength(),ignoreCase);
	}
	//寻找wArray数组中任意字符在此字符串最后出现的位置（不包含结尾字符）
	int XString::LastIndexOfAny(const XArray<wchar_t> wArray,int startIndex,int length)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(GetLength()<startIndex || GetLength()<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(length<0)length = GetLength()-startIndex;
		if(!length)return -1;
		const wchar_t* p = wArray;
		const wchar_t* pd = ToUnicode();
		int len = wArray.GetLength();
		for(int i=startIndex+length-1;i>=startIndex;--i)
		{
			for(int j=0;j<len;++j)
			{
				if(p[j]==pd[i])
					return i;
			}
		}
		return -1;
	}
	int XString::LastIndexOfAny(const XArray<wchar_t> wArray, int startIndex)const
	{
		return LastIndexOfAny( wArray,startIndex,-1);
	}


	XString XString::PadLeft(int totalWidth,WCHAR wc)const//在左边插入一定数量的wc，使字符串右对齐，返回一个有totalWidth个字符的字符串，该字符串不变，如果原字符串的长度大于totalWidth，则直接返回该字符串
	{
		if(totalWidth<0)throw XException(E_INVALIDARG);//参数无效
		if((totalWidth -= GetLength())<=0)return *this;
		return XString(wc,totalWidth)+*this;
	}
	XString XString::PadRight(int totalWidth,WCHAR wc)const//在右边插入一定数量的wc，使字符串左对齐，
	{
		if(totalWidth<0)throw XException(E_INVALIDARG);//参数无效
		if((totalWidth-=GetLength())<=0)return *this;
		return *this+XString(wc,totalWidth);
	}

	XString XString::Remove(int startIndex,int length)const//从startIndex起移除一定长度的内容，返回得到的新字符串，length小于0则表示移除后面所有的字符串
	{
		if(length<0)length = GetLength()-startIndex;
		if(startIndex<0 || GetLength()<=startIndex || startIndex+length>GetLength())return Empty;
		if(startIndex==0 && length==GetLength())return Empty;
		if(length==0)return *this;
		LPWSTR p = new WCHAR[startIndex+length+1];
		p[startIndex+length] = 0;
		Memory::Copy(p,ToUnicode(),startIndex*2);
		Memory::Copy(p+startIndex,ToUnicode()+startIndex+length,(GetLength()-length-startIndex)*2);
		return XString(new VString(startIndex+length,p,NULL));
	}
	XString XString::Replace(WCHAR wc1,WCHAR wc2,bool ignoreCase)const//返回一个新字符串，内容为原字符串中的wc1全替换为wc2
	{
		int len;
		if((len=GetLength())==0)return *this;
		LPCWSTR ws = ToUnicode();
		LPWSTR tmp= new WCHAR[len+1];
		if(ignoreCase && (wc1>=L'A'&&wc1<=L'Z' || wc1>='a' && wc1<='z'))
		{
			wc1&=0xcf;
			for(int i=0;i<len;++i)
			{
				if(ws[i]==wc1 || ws[i]==wc1+32)tmp[i]=wc2;
				else tmp[i]=ws[i];
			}
		}
		else for(int i=0;i<len;++i)
		{
			if(ws[i]==wc1)tmp[i]=wc2;
			else tmp[i]=ws[i];
		}
		tmp[len]=0;
		return XString(new VString(len,tmp,NULL));
	}
	XString XString::Replace(const XString& xString1 ,const XString& xString2,bool ignoreCase)const//返回一个新字符串，内容为原字符串中的xString1全替换为xString2
	{
		int len=GetLength(),count=0;//len表示该字符串长度，count表示替换次数
		if(!xString1.GetLength())return Empty;
		if(len<xString1.GetLength())return *this;
		LPWSTR ws = VString::Strcpy(ToUnicode(),len);
		int len1 = xString1.GetLength();
		int len2 = xString2.GetLength();
		LPWSTR ws1 = VString::Strcpy(xString1.ToUnicode(),len1);
		LPWSTR ws2 = VString::Strcpy(xString2.ToUnicode(),len2);
		if(ignoreCase)
		{
			_wcslwr_s(ws,len+1);
			_wcslwr_s(ws1,len1+1);
		}
		for(int i=0;i+len1<=len;)
		{
			if(!memcmp(ws+i,ws1,len1))
			{
				++count;
				i+=len1;
				continue;
			}
			++i;
		}
		count = len+count*(len2-len1);
		LPWSTR tmp = new WCHAR[count+1];
		int t=0,tt=0;
		for(int i=0;i+len1<=len;)
		{
			if(!memcmp(ws+i,ws1,len1))
			{
				if(i>t)Memory::Copy(tmp+tt,ToUnicode()+t,(i-t)*2);
				tt+=i-t;
				if(len2)Memory::Copy(tmp+tt,xString2.ToUnicode(),len2*2);
				tt+=len2;
				i+=len1;
				t=i;
				continue;
			}
			++i;
		}
		if(len>t)Memory::Copy(tmp+tt,ToUnicode()+t,(len-t)*2);
		tmp[count]=0;
		delete []ws;
		delete []ws1;
		delete []ws2;
		return XString(new VString(count,tmp,NULL));
	}

	XString XString::ToUpper()const//返回一个新字符串，新字符串为该所有的小写字母都变成大写
	{
		LPCWSTR tmp;
		if((tmp= ToUnicode())==NULL)return *this;
		int length = GetLength();
		LPWSTR ws = VString::Strcpy(tmp);
		_wcsupr_s(ws,length+1);
		return XString(new VString(length,ws,NULL));
	}
	XString XString::ToLower()const//返回一个新字符串，新字符串为该字符串所有的大写字母都变成小写
	{
		LPCWSTR tmp;
		if((tmp= ToUnicode())==NULL)return *this;
		int length = GetLength();
		LPWSTR ws = VString::Strcpy(tmp);
		_wcslwr_s(ws,length+1);
		return XString(new VString(length,ws,NULL));
	}
	//获取字符串中的英文单词（数字不算，比如“G2 VS2010”得到：“G”“VS”）
	XArray<XString> XString::GetWords()const
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		XArray<XString>strs;
		LPCWSTR pStart = ToUnicode();
		LPCWSTR pEnd = pStart+Length;
		LPWSTR p = const_cast<LPWSTR>(pStart);
		LPCWSTR start = pStart;
		bool alpha = *p>=L'a' && *p<=L'z' || *p>=L'A' && *p<=L'Z';
		while(++p<pEnd)
		{
			if(alpha)
			{
				if(alpha= *p>=L'a' && *p<=L'z' || *p>=L'A' && *p<=L'Z')continue;
				strs.Append(Substring(int(start-pStart),int(p-start)));
				continue;
			}
			if(!(alpha= *p>=L'a' && *p<=L'z' || *p>=L'A' && *p<=L'Z'))continue;
			start = p;
		}
		if(alpha)strs.Append(Substring(int(start-pStart),int(p-start)));
		return strs;
	}
	//获取字符串中的数字，比如“G2 VS2010”得到：“2010”
	XArray<XString> XString::GetNumbers()const
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		XArray<XString>strs;
		LPCWSTR pStart = ToUnicode();
		LPCWSTR pEnd = pStart+Length;
		LPWSTR p = const_cast<LPWSTR>(pStart);
		LPCWSTR start = pStart;
		bool alpha = *p>=L'0' && *p<=L'9';
		while(++p<pEnd)
		{
			if(alpha)
			{
				if(alpha=*p>=L'0' && *p<=L'9')continue;
				strs.Append(Substring(int(start-pStart),int(p-start)));
				continue;
			}
			if(!(alpha=*p>=L'0' && *p<=L'9'))continue;
			start = p;
		}
		if(alpha)strs.Append(Substring(int(start-pStart),int(p-start)));
		return strs;
	}
	//获取字符串中的英文和数字（英文和数字可连在一起，比如“G2 VS2010”得到：“G2”、“VS2010”）
	XArray<XString> XString::GetWordsAndNumbers()const
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		XArray<XString>strs;
		LPCWSTR pStart = ToUnicode();
		LPCWSTR pEnd = pStart+Length;
		LPWSTR p = const_cast<LPWSTR>(pStart);
		LPCWSTR start = pStart;
		bool alpha =  *p>=L'a' && *p<=L'z' || *p>=L'A' && *p<=L'Z' || *p>=L'0' && *p<=L'9';
		while(++p<pEnd)
		{
			if(alpha)
			{
				if(alpha=*p>=L'a' && *p<=L'z' || *p>=L'A' && *p<=L'Z' || *p>=L'0' && *p<=L'9')continue;
				strs.Append(Substring(int(start-pStart),int(p-start)));
				continue;
			}
			if(!(alpha=*p>=L'a' && *p<=L'z' || *p>=L'A' && *p<=L'Z' || *p>=L'0' && *p<=L'9'))continue;
			start = p;
		}
		if(alpha)strs.Append(Substring(int(start-pStart),int(p-start)));
		return strs;
	}
	//返回该字符串的数组表示（不包含结尾字符'\0'）
	XArray<WCHAR> XString::ToWCharArray(int startIndex,int length)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(GetLength()<startIndex || GetLength()<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(length<0)length = GetLength()-startIndex;
		if(!length)return XArray<WCHAR>(0);
		XArray<WCHAR> tmp(new VArray<WCHAR>(length));
		Memory::Copy(tmp,ToUnicode()+startIndex,length*sizeof(WCHAR));
		return tmp;
	}
	XString XString::Substring(int startIndex,int length)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(GetLength()<startIndex || GetLength()<startIndex+length)throw XException(COR_E_INDEXOUTOFRANGE);
		if(length<0)length = GetLength()-startIndex;
		if(length<=0)return Empty;
		if(length==GetLength())return *this;
		return XString(new VString(length,VString::Strcpy(ToUnicode()+startIndex,length),NULL));
	}
	//检索一个子字符串，当length<0时返回至结尾的子字符串 ,与Substring方法不同，这里的length表示字节长度，而且为了保证字符的完整性，返回的字符串的字节长度有可能小于指定的length。,startIndex<0或startIndex>Length将抛出异常
	XString XString::Cut(int startIndex, int length)const
	{
		if(startIndex<0)throw XException(E_INVALIDARG);//参数无效
		if(startIndex>GetLength())throw XException(COR_E_INDEXOUTOFRANGE); 
		if(length<0)return Substring(startIndex,length);
		if(!Length)return *this;
		int count = 0;
		int i;
		LPCWSTR pstr = ToUnicode();
		for(i=startIndex;i<Length;++i)
		{
			if(pstr[i]==L'\n' ||pstr[i]==L'\r')//回车与换行
			{
				if(pstr[i+1] + pstr[i]== L'\n'+ L'\r')
					++i;
				return Substring(startIndex,i+1-startIndex);
			}
			if(pstr[i]<128 && pstr[i]>0)
			{
				++count;
				if(count>=length)
				{
					if(pstr[i+1]==L'\n' || pstr[i+1]==L'\r')//回车与换行
					{
						++i;
						if(i<Length && pstr[i+1] + pstr[i]== L'\n'+ L'\r')
							++i;
					}
					return Substring(startIndex,i+1-startIndex);
				}
			}
			else
			{
				count+=2;
				if(count>=length)
				{
					if(count>length)return Substring(startIndex,i-startIndex);
					if(pstr[i+1]==L'\n' || pstr[i+1]==L'\r')//回车与换行
					{
						++i;
						if(i<Length && pstr[i+1] + pstr[i]== L'\n'+ L'\r')
							++i;
					}
					return Substring(startIndex,i+1-startIndex);
				}
			}
		}
		return Substring(startIndex,i-startIndex);
	}
	bool XString::IsNullOrEmpty()const//返回一个值，指使该字符串是否为空（包括NULL和""）
	{return IsNull() || ((VString*)pObject)->Length==0;}
	bool XString::Equals(const XBase& object)const
	{
		return !Compare(*this,object.ToString());
	}
	bool XString::Equals(const XString& object)const
	{
		return !Compare(*this,object);
	}
	//返回使用指定字符做分隔符分割形成的字符串数组,并指定最大数量
	XArray<XString> XString::Split(WCHAR ch, int maxCount)const
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		if(maxCount<0)throw XException(E_INVALIDARG);//参数无效
		if(!GetLength() || maxCount==0)return XArray<XString>(0);
		int len = GetLength();
		LPCWSTR p = ToUnicode();
		int count = 0;
		for(int i=0;i<len;++i)if(p[i]==ch)
		{
			if(count+1<maxCount)++count;
			else break;
		}
		XString* pstrs = new XString[count+1];
		int lasti = 0;
		count = 0;
		for(int i=0;i<len;++i)
		{
			if(p[i]==ch)
			{
				pstrs[count] = Substring(lasti,i-lasti);
				lasti = i+1;
				++count;
				if(count>=maxCount)
					break;
			}
		}
		if(count<maxCount)
		{
			pstrs[count] = Substring(lasti,len-lasti);
			return XArray<XString>(count+1,pstrs);
		}
		else
			return XArray<XString>(count,pstrs);
	}
	//返回使用指定字符做分隔符分割形成的字符串数组
	XArray<XString> XString::Split(WCHAR ch)const
	{
		return Split(ch,MaxValues::Int);
	}
	//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量
	XArray<XString> XString::Split(const XString& str,int maxCount)const
	{
		if(IsNull() || str.IsNull())throw XException(E_POINTER);
		if(maxCount<0)throw XException(E_INVALIDARG);//参数无效
		if(maxCount==0 || str.IsNullOrEmpty())return XArray<XString>(0);
		if(GetLength()<str.GetLength())return  XArray<XString>(1,*this);
		int len = GetLength()-str.GetLength();
		LPCWSTR p = ToUnicode();
		int count = 0;
		for(int i=0;i<=len;)
			if(!memcmp(p+i,str.ToUnicode(),str.GetLength()*2))
			{
				if(count+1<maxCount)++count;
				else break;
				i+=str.GetLength();
			}
			else ++i;
			XString* pstrs = new XString[count+1];
			int lasti = 0;
			count = 0;
			for(int i=0;i<=len;)
			{
				if(!memcmp(p+i,str.ToUnicode(),str.GetLength()*2))
				{
					pstrs[count] = Substring(lasti,i-lasti);
					++count;
					if(count>=maxCount)
						break;
					i+=str.GetLength();
					lasti = i;
				}
				else ++i;
			}
			if(count<maxCount)
			{
				pstrs[count] = Substring(lasti,len+1-lasti);
				return XArray<XString>(count+1,pstrs);
			}
			else
				return XArray<XString>(count,pstrs);
	}
	//返回使用指定字符做分隔符分割形成的字符串数组,并指定最大数量,是否移除空字符串
	XArray<XString> XString::Split(WCHAR ch, int maxCount,bool removeEmpty)const
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		if(maxCount<0)throw XException(E_INVALIDARG);//参数无效
		if(!GetLength() || maxCount==0)return XArray<XString>(0);
		int len = GetLength();
		LPCWSTR p = ToUnicode();
		int count = 0;
		int lasti = 0;
		for(int i=0;i<len;++i)
		{
			if(p[i]==ch)
			{
				if(removeEmpty && lasti==i)
				{
					lasti = i+1;
					continue;
				}
				if(count+1<maxCount)++count;
				else break;
				lasti = i+1;
			}
		}
		XString* pstrs = new XString[count+1];
		count = 0;
		lasti=0;
		for(int i=0;i<len;++i)
		{
			if(p[i]==ch)
			{
				if(!removeEmpty || i>lasti)
				{
					pstrs[count] = Substring(lasti,i-lasti);
					++count;
				}
				lasti = i+1;
				if(count>=maxCount)
					break;
			}
		}
		if(count<maxCount && (!removeEmpty || len>lasti))
		{
			pstrs[count] = Substring(lasti,len-lasti);
			return XArray<XString>(count+1,pstrs);
		}
		else
			return XArray<XString>(count,pstrs);
	}
	//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量,是否移除空字符串
	XArray<XString> XString::Split(const XString& str,int maxCount,bool removeEmpty)const
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		if(maxCount<0)throw XException(E_INVALIDARG);//参数无效
		if(!GetLength() || maxCount==0)return XArray<XString>(0);
		int len = GetLength();
		LPCWSTR p = ToUnicode();

		int count = 0;//分隔字符串数量（如果removeEmpty为true则连续的分隔符表示1个分隔符）
		int lasti = 0;//上一个分隔符末尾+1的位置
		for(int i=0;i<len;)
		{
			if(i+str.Length<len && !memcmp(i+p,str.ToUnicode(),str.Length*2))
			{
				if(removeEmpty && lasti==i)
				{
					i += str.Length;
					lasti = i;
					continue;
				}
				if(count+1<maxCount)++count;
				else break;
				i += str.GetLength();
				lasti = i;
			}
			else ++i;
		}
		XString* pstrs = new XString[count+1];
		count = 0;
		lasti=0;
		for(int i=0;i<len;)
		{
			if(i+str.Length<len && !memcmp(i+p,str.ToUnicode(),str.Length*2))
			{
				if(!removeEmpty || i>lasti)
				{
					pstrs[count] = Substring(lasti,i-lasti);
					++count;
				}
				i += str.GetLength();
				lasti = i;
				if(count>=maxCount)
					break;
			}
			else ++i;
		}
		if(count<maxCount && (!removeEmpty || len>lasti))
		{
			pstrs[count] = Substring(lasti,len-lasti);
			return XArray<XString>(count+1,pstrs);
		}
		else
			return XArray<XString>(count,pstrs);
	}
	//返回使用指定字符数组中出现的字符做分隔符分割形成的字符串数组,并指定最大数量,并指明是否移除空字符串
	XArray<XString> XString::Split(const XArray<WCHAR> chs,int maxCount,bool removeEmpty)const
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		if(maxCount<0)throw XException(E_INVALIDARG);//参数无效
		if(!GetLength() || maxCount==0)return XArray<XString>(0);
		int len = GetLength();
		LPCWSTR p = ToUnicode();
		int count = 0;
		int lasti = 0;
		for(int i=0;i<len;++i)
		{
			int j;
			for(j=0;j<chs.Length;++j)
				if(p[i]==chs[j])break;
			if(j<chs.Length)
			{
				if(removeEmpty && lasti==i)
				{
					lasti = i+1;
					continue;
				}
				if(count+1<maxCount)++count;
				else break;
				lasti = i+1;
			}
		}
		XString* pstrs = new XString[count+1];
		count = 0;
		lasti=0;
		for(int i=0;i<len;++i)
		{
			int j;
			for(j=0;j<chs.Length;++j)
				if(p[i]==chs[j])break;
			if(j<chs.Length)
			{
				if(!removeEmpty || i>lasti)
				{
					pstrs[count] = Substring(lasti,i-lasti);
					++count;
				}
				lasti = i+1;
				if(count>=maxCount)
					break;
			}
		}
		if(count<maxCount && (!removeEmpty || len>lasti))
		{
			pstrs[count] = Substring(lasti,len-lasti);
			return XArray<XString>(count+1,pstrs);
		}
		else
			return XArray<XString>(count,pstrs);
	}
	//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量,并指明是否移除空字符串
	XArray<XString> XString::Split(const XArray<XString> strs,int maxCount,bool removeEmpty)const
	{
		if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
		if(maxCount<0)throw XException(E_INVALIDARG);//参数无效
		if(!GetLength() || maxCount==0)return XArray<XString>(0);
		int len = GetLength();
		LPCWSTR p = ToUnicode();

		int count = 0;//分隔字符串数量（如果removeEmpty为true则连续的分隔符表示1个分隔符）
		int lasti = 0;//上一个分隔符末尾+1的位置
		for(int i=0;i<len;)
		{
			int j;
			for(j=0;j<strs.Length;++j)
				if(strs[j].Length && i+strs[j].Length<len && !memcmp(i+p,strs[j].ToUnicode(),strs[j].Length*2))break;
			if(j<strs.Length)
			{
				if(removeEmpty && lasti==i)
				{
					i += strs[j].Length;
					lasti = i;
					continue;
				}
				if(count+1<maxCount)++count;
				else break;
				i += strs[j].GetLength();
				lasti = i;
			}
			else ++i;
		}
		XString* pstrs = new XString[count+1];
		count = 0;
		lasti=0;
		for(int i=0;i<len;)
		{
			int j;
			for(j=0;j<strs.Length;++j)
				if(strs[j].Length && i+strs[j].Length<len && !memcmp(i+p,strs[j].ToUnicode(),strs[j].Length*2))break;
			if(j<strs.Length)
			{
				if(!removeEmpty || i>lasti)
				{
					pstrs[count] = Substring(lasti,i-lasti);
					++count;
				}
				i += strs[j].GetLength();
				lasti = i;
				if(count>=maxCount)
					break;
			}
			else ++i;
		}
		if(count<maxCount && (!removeEmpty || len>lasti))
		{
			pstrs[count] = Substring(lasti,len-lasti);
			return XArray<XString>(count+1,pstrs);
		}
		else
			return XArray<XString>(count,pstrs);
	}
	//返回使用指定字符数组中出现的字符做分隔符分割形成的字符串数组,并指定最大数量
	XArray<XString> XString::Split(const XArray<WCHAR> chs, int maxCount)const
	{
		return Split(chs,maxCount,false);
	}
	//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量
	XArray<XString> XString::Split(const XArray<XString> strs, int maxCount)const
	{
		return Split(strs, maxCount,false);
	}
#ifdef _CLR //托管支持
	XString::XString(volatile const System::String^string, int count)//创建由count个字符string串接而成的字符串
		:XBase(string?new VString(string,count):NULL)//引用计数自动加1
	{XSTRINGCITEDCHANGE(pString);}
	System::String^ XString::ToGcString()const //定义到托管字符串的转换
	{
		if(pObject)return ((VString*)pObject)->ToGcString();
		return nullptr;
	}
	XString& XString::operator=(System::String^s)
	{
		return *this = XString(s);
	}
	XString::operator System::String^()const 
	{
		return ToGcString();
	}
	System::String^ XString::operator->()const
	{
		return (System::String^)*this;
	}
	XString& XString::operator+=(System::String^ string)
	{
		return *this+=XString(string);
	}
	XString& XString::operator+=(System::Object^ obj)
	{
		return *this+=XString(obj->ToString());
	}
	XString operator+(const XString xString,System::Object^ obj)
	{
		return XString(xString,XString(obj->ToString()));
	}
	XString operator+(System::Object^ obj,const XString xString)
	{
		return XString(XString(obj->ToString()),xString);
	}
	XString operator+(const XString xString,volatile const System::String^ string)
	{
		return XString(xString,XString(string));
	}
	XString operator+(volatile const System::String^ string,const XString xString)
	{
		return XString(XString(string),xString);
	}
#endif

}
#endif