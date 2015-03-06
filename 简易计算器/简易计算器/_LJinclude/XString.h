#pragma once//由W意波(LuoJun)编写
#define XSTRING_
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

		bool operator==(const VString& vString1,const VString& vString2);//字符串比较
		bool operator!=(const VString& vString1,const VString& vString2);
		bool operator>(const VString& vString1,const VString& vString2);
		bool operator<(const VString& vString1,const VString& vString2);
		bool operator>=(const VString& vString1,const VString& vString2);
		bool operator<=(const VString& vString1,const VString& vString2);

		VString operator+(const VString& vString1,const VString& vString2);
		VString operator+(const VString& vString,const XBase& xBase);
		VString operator+(const XBase& xBase,const VString& vString);

	//字符串具体数据，该类中定义的静态方法为对原始字符串的操作，该类中的方法将直接改变字符串本身的内容，多线程操作将不安全
	class VString:public XBase
	{
#define ChsNumMaxCount 21
#define ChsUnitMaxCount 9
		static LPCWSTR ppNumWChs[ChsNumMaxCount];//记录数字字符
		static unsigned char pNumCounts[ChsNumMaxCount];//记实每个数字字符数
		static LPCWSTR ppUnitWChs[ChsUnitMaxCount];//记录单位字符
		static unsigned long long pUnitValue[ChsUnitMaxCount];//记录每个单位对应的数值
		static unsigned char pUnitCounts[ChsUnitMaxCount];//记录每个单位对应的字符数量

		//多字节字符串，即char* mString;
		volatile LPSTR mString;
		//宽字节字符串，即wchar_t* wString;
		LPWSTR wString;
	public:
		//wmemchr
		static inline const wchar_t * wmemchr(const wchar_t *_S, wchar_t _C, size_t _N){for (; 0 < _N; ++_S, --_N)if (*_S == _C)return _S;return (0); }
		//基类通用方法
		XBaseVTypeMethods_H(VString);
		//使用宽字节存储，需要的时候转换成多字节
		//wString数组中的字符数
		const int Length;
		//针对原始字符串的操作方法：

		//测量多字节字符串字符数，如果传入NULL则报错
		static inline int Strlen(LPCSTR mString){return mString==NULL?0:(int)strlen(mString);}
		//测量宽字节字符串字符数，如果传入NULL则报错
		static inline int Strlen(LPCWSTR wString){return wString==NULL?0:(int)wcslen(wString);}
		//复制字符串到一个new申请的新空间，并返回一个指向该空间的指针，使用完毕请delete[]删除。length(可选)为指定要复制的长度
		static inline LPSTR Strcpy(LPCSTR mString,int length){CHAR* p = new CHAR[length+1];Memory::Copy(p,mString,length);p[length]=0;return p;}
		//复制字符串到一个new申请的新空间，并返回一个指向该空间的指针，使用完毕请delete[]删除。length(可选)为指定要复制的长度
		static inline LPWSTR Strcpy(LPCWSTR wString,int length){WCHAR* p = new WCHAR[length+1];Memory::Copy(p,wString,length*2);	p[length]=0;return p;}
		//复制字符串到一个new申请的新空间，并返回一个指向该空间的指针，使用完毕请delete[]删除。length(可选)为指定要复制的长度
		static inline LPSTR Strcpy(LPCSTR mString){int length = (int)strlen(mString);	CHAR* p = new CHAR[length+1];Memory::Copy(p,mString,length);p[length]=0;return p;}
		//复制字符串到一个new申请的新空间，并返回一个指向该空间的指针，使用完毕请delete[]删除。length(可选)为指定要复制的长度
		static inline LPWSTR Strcpy(LPCWSTR wString)	{int length = (int)wcslen(wString);WCHAR* p = new WCHAR[length+1];Memory::Copy(p,wString,length*2);p[length]=0;return p;}
		//比较两个字符串的大小，可选择给出字符串长度
		static inline int Strcmp(LPCSTR mString1, LPCSTR mString2,int length){return memcmp(mString1,mString2,length);}
		//比较两个字符串的大小，可选择给出字符串长度
		static inline int Strcmp(LPCSTR mString1, LPCSTR mString2){return strcmp(mString1,mString2);}
		//比较两个字符串的大小，可选择给出字符串长度
		static inline int Strcmp(const wchar_t* wString1, const wchar_t* wString2,int length){return wcsncmp(wString1,wString2,length);}
		//比较两个字符串的大小，可选择给出字符串长度
		static inline int Strcmp(LPCWSTR wString1, LPCWSTR wString2){return wcscmp(wString1,wString2);}
		//串接字符串,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static inline LPSTR Strcat(LPCSTR mString1,LPCSTR mString2,int length1,int length2){LPSTR p = new CHAR[length1+length2+1];Memory::Copy(p,mString1,length1);Memory::Copy(p+length1,mString2,length2);p[length1+length2]=0;return p;}
		//串接字符串,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static inline LPSTR Strcat(LPCSTR mString1,LPCSTR mString2){	return Strcat(mString1,mString2,Strlen(mString1),Strlen(mString2));}
		//串接字符串,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static inline LPSTR Strcat(LPCSTR mString1,LPCSTR mString2,LPCSTR mString3,int length1,int length2,int length3){LPSTR p = new CHAR[length1+length2+length3+1];Memory::Copy(p,mString1,length1);Memory::Copy(p+length1,mString2,length2);Memory::Copy(p+length1+length2,mString3,length3);p[length1+length2+length3]=0;return p;}
		//串接字符串,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static inline LPSTR Strcat(LPCSTR mString1,LPCSTR mString2,LPCSTR mString3){return Strcat(mString1,mString2,mString3,Strlen(mString1),Strlen(mString2),Strlen(mString3));}
		//串接字符串,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static inline LPSTR Strcat(LPCSTR mString1,LPCSTR mString2,LPCSTR mString3,LPCSTR mString4,int length1,int length2,int length3,int length4){LPSTR p = new CHAR[length1+length2+length3+length4+1];Memory::Copy(p,mString1,length1);Memory::Copy(p+length1,mString2,length2);Memory::Copy(p+length1+length2,mString3,length3);Memory::Copy(p+length1+length2+length3,mString4,length4);p[length1+length2+length3+length4]=0;return p;}
		//串接字符串,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static inline LPSTR Strcat(LPCSTR mString1,LPCSTR mString2,LPCSTR mString3,LPCSTR mString4){return Strcat(mString1,mString2,mString3,mString4,Strlen(mString1),Strlen(mString2),Strlen(mString3),(int)strlen(mString4));}
		//串接字符串,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static inline LPWSTR Strcat(LPCWSTR wString1,LPCWSTR wString2,int length1,int length2){LPWSTR p = new WCHAR[length1+length2+1];Memory::Copy(p,wString1,length1*2);Memory::Copy(p+length1,wString2,length2*2);p[length1+length2]=0;return p;}
		//串接字符串,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static inline LPWSTR Strcat(LPCWSTR wString1,LPCWSTR wString2){return Strcat(wString1,wString2,Strlen(wString1),Strlen(wString2));}
		//串接字符串,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static inline LPWSTR Strcat(LPCWSTR wString1,LPCWSTR wString2,LPCWSTR wString3,int length1,int length2,int length3){LPWSTR p = new WCHAR[length1+length2+length3+1];Memory::Copy(p,wString1,length1*2);Memory::Copy(p+length1,wString2,length2*2);Memory::Copy(p+length1+length2,wString3,length3*2);p[length1+length2+length3]=0;return p;}
		//串接字符串,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static inline LPWSTR Strcat(LPCWSTR wString1,LPCWSTR wString2,LPCWSTR wString3){return Strcat(wString1,wString2,wString3,Strlen(wString1),Strlen(wString2),Strlen(wString3));}
		//串接字符串,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static inline LPWSTR Strcat(LPCWSTR wString1,LPCWSTR wString2,LPCWSTR wString3,LPCWSTR wString4,int length1,int length2,int length3,int length4){LPWSTR p = new WCHAR[length1+length2+length3+length4+1];Memory::Copy(p,wString1,length1*2);Memory::Copy(p+length1,wString2,length2*2);Memory::Copy(p+length1+length2,wString3,length3*2);Memory::Copy(p+length1+length2+length3,wString4,length4*2);p[length1+length2+length3+length4]=0;	return p;}
		//串接字符串,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static inline LPWSTR Strcat(LPCWSTR wString1,LPCWSTR wString2,LPCWSTR wString3,LPCWSTR wString4){return Strcat(wString1,wString2,wString3,wString4,Strlen(wString1),Strlen(wString2),Strlen(wString3),Strlen(wString4));}
		//字符串串接count次,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static LPWSTR StrRepeat(LPCWSTR wString,int count);
		//字符串串接count次,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static LPSTR StrRepeat(LPCSTR mString,int count);
		//字符串串接count次,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static LPWSTR StrRepeat(LPCWSTR wString,int length,int count);
		//字符串串接count次,返回一个new申请的空间，串接所得的新字符串将放到其中，使用完毕请delete[]删除
		static LPSTR StrRepeat(LPCSTR mString,int length,int count);
		//返回一个使用new申请的空间，内容为将string2字符串插入到string1的strtIndex位置处所得字符串，需指定字符串长度
		static inline LPSTR Strins(LPCSTR mString1, LPCSTR mString2,int startIndex,int length1,int length2){LPSTR p = new CHAR[length1+length2+1];Memory::Copy(p,mString1,startIndex);Memory::Copy(p+startIndex,mString2,length2);Memory::Copy(p+startIndex+length2,mString1+startIndex,length1-startIndex);p[length1+length2]=0;return p;}
		//返回一个使用new申请的空间，内容为将string2字符串插入到string1的strtIndex位置处所得字符串，需指定字符串长度
		static inline LPWSTR Strins(LPCWSTR mString1, LPCWSTR mString2,int startIndex,int length1,int length2){LPWSTR p = new WCHAR[length1+length2+1];Memory::Copy(p,mString1,startIndex*2);Memory::Copy(p+startIndex,mString2,length2*2);Memory::Copy(p+startIndex+length2,mString1+startIndex,(length1-startIndex)*2);	p[length1+length2]=0;	return p;}
		//查找字符在字符串出现的位置,可选择指定长度，找不到返回-1
		static inline int Strchr(LPCSTR mString,CHAR ch,int length){const void* p = memchr(mString,ch,length);return p?int((LPCSTR)p-mString):-1;}
		//查找字符在字符串出现的位置,可选择指定长度，找不到返回-1
		static inline int Strchr(LPCSTR mString,CHAR ch){LPCSTR p = strchr(mString,ch);return p?int(p-mString):-1;}
		//查找字符在字符串出现的位置,可选择指定长度，找不到返回-1
		static inline int Strchr(LPCWSTR wString, WCHAR ch,int length){const void* p = wmemchr(wString,ch,length);return p?int((LPCWSTR)p-wString):-1;}
		//查找字符在字符串出现的位置,可选择指定长度，找不到返回-1
		static inline int Strchr(LPCWSTR wString, WCHAR ch){LPCWSTR p = wcschr(wString,ch);return p?int(p-wString):-1;}
		//查找字符串在字符串出现的位置,可选择指定长度，找不到返回-1
		static inline int Strstr(LPCSTR mString1, LPCSTR mString2){LPCSTR p = strstr(mString1,mString2);return p?int(p-mString1):-1;}
		//查找字符串在字符串出现的位置,可选择指定长度，找不到返回-1
		static inline int Strstr(LPCSTR mString1, LPCSTR mString2,int length1,int length2){void* p = (void*)mString1;while(length1>(LPSTR)p-mString1){p = memchr(p,*mString2,length1);if(p==NULL || length1-((LPSTR)p-mString1)<length2)return -1;if(memcmp(p,mString2,length2))p = (LPSTR)p+1;else return (int)((LPSTR)p-mString1);}return -1;}
		//查找字符串在字符串出现的位置,可选择指定长度，找不到返回-1
		static inline int Strstr(LPCWSTR wString1, LPCWSTR wString2){LPCWSTR p = wcsstr(wString1,wString2);	if(p)return int(p-wString1);return -1;}
		//查找字符串在字符串出现的位置,可选择指定长度，找不到返回-1
		static inline int Strstr(LPCWSTR wString1, LPCWSTR wString2,int length1,int length2){LPCWSTR p =wString1;while(length1>p-wString1){p = (LPCWSTR)wmemchr(p,*wString2,length1);if(p==NULL || length1-(p-wString1)<length2)return -1;if(memcmp(p,wString2,length2*2))p = p+1;else return int(p-wString1);}return -1;}
		//多字节转换为宽字节，length表示的是source除终止字符'\0'的字符数（字节数），-1代表NULL，-2代表自动计算，返回转换后的字符串，可通过outputlength获取转换后的字符串长度
		static LPWSTR AnsiToUnicode(LPCSTR source,int* outLength,int length=-2);
		//多字节转换为宽字节，length表示的是source除终止字符'\0'的字符数（字节数），-1代表NULL，-2代表自动计算，返回转换后的字符串，可通过outputlength获取转换后的字符串长度
		static LPWSTR AnsiToUnicode(LPCSTR source,int length=-2);
		//宽字节转换为多字节，length表示的是source除终止字符'\0'的字符数(字节数/2)，返回转换后的字符串
		static LPSTR UnicodeToAnsi(LPCWSTR source,int* outLength,int length=-2);
		//宽字节转换为多字节，length表示的是source除终止字符'\0'的字符数(字节数/2)，返回转换后的字符串
		static LPSTR UnicodeToAnsi(LPCWSTR source,int length=-2);

		//查找vString2在vString1的位置，maxLength1、maxLength2分别代表各字符串的长度
		static int Find(const VString& vString1,int index1,const VString& vString2,int index2,int maxLength1,int maxLength2,bool ignoreCase);
		//查找vString2在vString1最后出现的位置
		static int Last(const VString& vString1,int index1,const VString& vString2,int index2,int maxLength1,int maxLength2,bool ignoreCase);

		//一个空字符串：“”
		const static VString Empty;

		//析构函数，释放占用的空间
		virtual ~VString();
		//构造函数
		VString();
		//直接传入指定的参数来构造字符串，字符串ws必须通过new分配，并将托由VString来执行delete，ms可以为NULL
		inline VString(int length,LPWSTR ws,LPSTR ms):Length(length),wString(ws),mString(ms){}
		//复制构造
		inline VString(const VString& str,int count=1):Length(str.Length*count),wString(StrRepeat(str.wString,str.Length,count)),mString(NULL){}
		//由count个XString构造
		explicit VString(const XString str,int count=1);
		//由count个LPWSTR构造
		inline VString(LPCWSTR str,int count=1):Length(Strlen(str)*count),wString(StrRepeat(str,count)),mString(NULL){}
		//由count个LPSTR构造
		VString(LPCSTR str,int count=1);
		//由count个CHAR构造
		VString(CHAR c,int count=1);
		//由count个WCHAR构造
		VString(WCHAR wc,int count=1);
		//由字符数组构造如果wstr中有\0则其后面部分将被忽略
		VString(const XArray<WCHAR> wstr,int count=1);
		//由字符数组构造如果mstr中有\0则其后面部分将被忽略
		VString(const XArray<CHAR> mstr,int count=1);

		//由数字创建字符串，format使用字符串指定格式
		explicit VString(float number,LPCWSTR format=L"%g");
		//由数字创建字符串，format使用字符串指定格式
		explicit VString(double number,LPCWSTR format=L"%g");
		//由数字创建字符串，format使用字符串指定格式
		explicit VString(unsigned long long number,LPCWSTR format);
		//由数字创建字符串，format使用字符串指定格式
		explicit VString(unsigned long number,LPCWSTR format=L"%d");
		//由数字创建字符串，format使用字符串指定格式
		explicit VString(unsigned int number,LPCWSTR format=L"%d");
		//由数字创建字符串，format使用字符串指定格式
		explicit VString(long long number,LPCWSTR format=L"%d");
		//由数字创建字符串，format使用字符串指定格式
		explicit VString(long number,LPCWSTR format=L"%d");
		//由数字创建字符串，format使用字符串指定格式
		explicit VString(int number,LPCWSTR format=L"%d");
		//由数字创建字符串，format使用字符串指定格式
		explicit VString(unsigned short number,LPCWSTR format);
		//由数字创建字符串，format使用字符串指定格式
		explicit VString(short number,LPCWSTR format);
		//由数字创建字符串，format使用字符串指定格式
		explicit VString(unsigned char number,LPCWSTR format);
		//由数字创建字符串，format使用字符串指定格式
		explicit VString(signed char number,LPCWSTR format);
		//输出一个引用该字符串实体副本的XString
		virtual XString ToString()const;
		//转换成原始的多字节字符串，const型
		LPCSTR const ToAnsi()const;
		//转换成原始的宽字节字符串，const型
		inline LPCWSTR const& ToUnicode()const{return wString;}
		//索引
		const WCHAR operator[](int index)const;
		//索引
		WCHAR& operator[](int index);
		//迭代器
		Iterator<WCHAR> First();
		//迭代器
		Iterator<const WCHAR> First()const;
		//迭代器
		inline Iterator<WCHAR> begin(){return First();}
		//迭代器
		inline Iterator<const WCHAR> begin()const{return First();}
		//迭代器
		Iterator<WCHAR> Last();
		//迭代器
		Iterator<const WCHAR> Last()const;
		//迭代器
		Iterator<WCHAR> End();
		//迭代器
		Iterator<const WCHAR> End()const;
		//迭代器
		inline Iterator<WCHAR> end(){return End();}
		//迭代器
		inline Iterator<const WCHAR> end()const{return End();}
		operator LPCSTR const()const{return ToAnsi();}
		operator LPCWSTR const&()const{return wString;}
		//转换为一个unsigned long long
		unsigned long long ToUInt64()const;
		//转换为一个long long
		long long ToInt64()const;
		//转换为一个double
		double ToDouble()const;
		//转换为一个unsigned long long，使用汉字支持
		unsigned long long ChsToUInt64(LPCWSTR p=0,unsigned int len=0)const;
		//转换为一个long long，使用汉字支持
		long long ChsToInt64()const;

		VString& operator=(const VString& vString);//赋值运算
		VString& operator=(LPCSTR mstr);
		VString& operator=(LPCWSTR wstr);
		VString& operator+=(const VString& vString);//串接运算
		VString& operator+=(LPCSTR mstr);
		VString& operator+=(LPCWSTR wstr);
		friend bool operator==(const VString& vString1,const VString& vString2);//字符串比较
		friend bool operator!=(const VString& vString1,const VString& vString2);
		friend bool operator>(const VString& vString1,const VString& vString2);
		friend bool operator<(const VString& vString1,const VString& vString2);
		friend bool operator>=(const VString& vString1,const VString& vString2);
		friend bool operator<=(const VString& vString1,const VString& vString2);
		friend bool operator==(const VString& xString1,LPCWSTR xString2){return VString::Strcmp(xString1,xString2)==0;}
		friend bool operator==(LPCWSTR xString1,const VString& xString2){return VString::Strcmp(xString1,xString2)==0;}
		friend bool operator==(const VString& xString1,LPCSTR xString2){return VString::Strcmp(xString1,xString2)==0;}
		friend bool operator==(LPCSTR xString1,const VString& xString2){return VString::Strcmp(xString1,xString2)==0;}
		friend bool operator!=(const VString& xString1,LPCWSTR xString2){return VString::Strcmp(xString1,xString2)!=0;}
		friend bool  operator!=(LPCWSTR xString1,const VString& xString2){return VString::Strcmp(xString1,xString2)!=0;}
		friend bool  operator!=(const VString& xString1,LPCSTR xString2){return VString::Strcmp(xString1,xString2)!=0;}
		friend bool  operator!=(LPCSTR xString1,const VString& xString2){return VString::Strcmp(xString1,xString2)!=0;}
		friend bool  operator>(const VString& xString1,LPCWSTR xString2){return VString::Strcmp(xString1,xString2)>0;}
		friend bool  operator>(LPCWSTR xString1,const VString& xString2){return VString::Strcmp(xString1,xString2)>0;}
		friend bool  operator>(const VString& xString1,LPCSTR xString2){return VString::Strcmp(xString1,xString2)>0;}
		friend bool  operator>(LPCSTR xString1,const VString& xString2){return VString::Strcmp(xString1,xString2)>0;}
		friend bool  operator<(const VString& xString1,LPCWSTR xString2){return VString::Strcmp(xString1,xString2)<0;}
		friend bool  operator<(LPCWSTR xString1,const VString& xString2){return VString::Strcmp(xString1,xString2)<0;}
		friend bool  operator<(const VString& xString1,LPCSTR xString2){return VString::Strcmp(xString1,xString2)<0;}
		friend bool  operator<(LPCSTR xString1,const VString& xString2){return VString::Strcmp(xString1,xString2)<0;}
		friend bool  operator>=(const VString& xString1,LPCWSTR xString2){return VString::Strcmp(xString1,xString2)>=0;}
		friend bool  operator>=(LPCWSTR xString1,const VString& xString2){return VString::Strcmp(xString1,xString2)>=0;}
		friend bool  operator>=(const VString& xString1,LPCSTR xString2){return VString::Strcmp(xString1,xString2)>=0;}
		friend bool  operator>=(LPCSTR xString1,const VString& xString2){return VString::Strcmp(xString1,xString2)>=0;}
		friend bool  operator<=(const VString& xString1,LPCWSTR xString2){return VString::Strcmp(xString1,xString2)<=0;}
		friend bool  operator<=(LPCWSTR xString1,const VString& xString2){return VString::Strcmp(xString1,xString2)<=0;}
		friend bool  operator<=(const VString& xString1,LPCSTR xString2){return VString::Strcmp(xString1,xString2)<=0;}
		friend bool  operator<=(LPCSTR xString1,const VString& xString2){return VString::Strcmp(xString1,xString2)<=0;}

		friend VString operator+(const VString& vString1,const VString& vString2);
		friend VString operator+(const VString& vString,const XBase& xBase);
		friend VString operator+(const XBase& xBase,const VString& vString);

		//与object的字符串表示比较
		int CompareTo(const XBase& object)const;
		//与string字符串表示比较
		int CompareTo(const VString& string)const{	return Strcmp(wString,string.ToUnicode());}
		//复制到多字节数组，返回复制的字节数,lengthOfByte<0将自动判断字节数，sourceByteIndex<0或destinationByteIndex<0将抛出异常
		int CopyTo(XArray<char>& destination,int sourceByteIndex=0,int destinationByteIndex=0,int lengthOfByte=-1)const;
		//复制到宽字节数组，返回复制的字符数,length<0将自动判断字节数，sourceIndex<0或destinationIndex<0将抛出异常
		int CopyTo(XArray<wchar_t> destination,int sourceIndex=0,int destinationIndex=0,int length=-1)const;
		//判断该字符串是否包含xString
		bool Contains(const VString& xString)const;
		//获取该字符串中字符wch出现的次数
		int CountOf(WCHAR wch)const;
		//获取该字符串中字符串str出现的次数
		int CountOf(const VString& str)const;
		//判断该字符串是否以xString结尾
		bool EndsWith(const VString& xString)const;
		//判断该字符串是否以xString开头
		bool StartsWith(const VString& xString)const;
		//与object的字符串表示比较，看是否相等
		virtual bool Equals(const XBase& object)const;
		//与指定字符串比较，看是否相等
		virtual bool Equals(const VString&)const;
		//检索一个子字符串，当length<0时返回至结尾的子字符串 ，startIndex<0或startIndex+length>Length将抛出异常
		VString Substring(int startIndex, int length=-2)const;
		//检索一个子字符串，当length<0时返回至结尾的子字符串 ,与Substring方法不同，遇到换行符将自动返回。这里的length表示字节长度，而且为了保证字符的完整性，返回的字符串的字节长度有可能小于指定的length。,startIndex<0或startIndex>Length将抛出异常
		VString Cut(int startIndex, int length=-2)const;
		//返回在startIndex位置插入xString的新字符串，该字符串不变，startIndex<0将抛出异常
		VString& Insert(int startIndex,const VString& xString);
		//在左边插入一定数量的wc，使字符串右对齐，返回一个有totalWidth个字符的字符串，该字符串不变，如果原字符串的长度大于totalWidth，则直接返回该字符串
		VString& PadLeft(int totalWidth,WCHAR wc=' ');
		//在右边插入一定数量的wc，使字符串左对齐，
		VString& PadRight(int totalWidth,WCHAR wc=' ');
		//从startIndex起移除一定长度的内容，返回得到的新字符串，length小于0则表示移除后面所有的字符串，startIndex<0或startIndex+length>Length将抛出异常
		VString& Remove(int startIndex,int length=-1);
		//返回一个新字符串，内容为原字符串中的wc1全替换为wc2,并指定比较时是否忽略大小写
		VString& Replace(WCHAR wc1,WCHAR wc2,bool ignoreCase=false);
		//返回一个新字符串，内容为原字符串中的xString1全替换为xString2，并指定比较时是否忽略大小写
		VString& Replace(const VString& xString1 ,const VString& xString2,bool ignoreCase=false);
		//返回一个新字符串，新字符串为该所有的小写字母都变成大写
		VString& ToUpper();
		//返回一个新字符串，新字符串为该所有的大写字母都变成小写
		VString& ToLower();
		//获取字符串中的英文单词（数字不算，比如“G2 VS2010”得到：“G”“VS”）
		XArray<VString> GetWords()const;
		//获取字符串中的数字，比如“G2 VS2010”得到：“2010”
		XArray<VString> GetNumbers()const;
		//获取字符串中的英文和数字（英文和数字可连在一起，比如“G2 VS2010”得到：“G2”、“VS2010”）
		XArray<VString> GetWordsAndNumbers()const;
		//返回该字符串的宽字节数组表示（不包含结尾字符'\0'），startIndex<0或startIndex+length>Length将抛出异常
		XArray<WCHAR> ToWCharArray( int startIndex=0,int length=-1)const;
		//返回使用指定字符做分隔符分割形成的字符串数组,并指定最大数量(-1表示不限制)
		XArray<VString> Split(WCHAR ch, int maxCount)const;
		//返回使用指定字符做分隔符分割形成的字符串数组
		XArray<VString> Split(WCHAR ch = L' ')const;
		//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量(-1表示不限制)
		XArray<VString> Split(const VString& str,int maxCount=MaxValues::Int)const;
		//返回使用指定字符数组中出现的字符做分隔符分割形成的字符串数组,并指定最大数量(-1表示不限制),并指明是否移除空字符串
		XArray<VString> Split(const XArray<WCHAR> chs,int maxCount,bool removeEmpty)const;
		//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量(-1表示不限制),并指明是否移除空字符串
		XArray<VString> Split(const XArray<VString> strs,int maxCount,bool removeEmpty)const;
		//返回使用指定字符数组中出现的字符做分隔符分割形成的字符串数组,并指定最大数量(-1表示不限制)
		XArray<VString> Split(const XArray<WCHAR> chs,int maxCount=MaxValues::Int)const;
		//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量(-1表示不限制)
		XArray<VString> Split(const XArray<VString> strs,int maxCount=MaxValues::Int)const;
		//返回一个值，指使该字符串是否为空（""）
		bool IsEmpty()const{return Length==0;}

		//查找指定 Unicode 字符在此字符串中的第一个匹配项的索引。 
		int IndexOf(WCHAR wc)const;
		//指定起始位置并指定是否忽略大小写，startIndex<0或>Length将抛出异常
		int IndexOf(WCHAR wc,int startIndex,bool ignoreCase=false)const;
		//指定起始位置并指定是否忽略大小写，length<0表示查找全部，startIndex<0或startIndex+length>Length将抛出异常
		int IndexOf(WCHAR wc,int startIndex,int length,bool ignoreCase)const;
		//查找指定 字符串在此字符串中的第一个匹配项的索引。 
		int IndexOf(const VString& xString)const;
		//指定起始位置并指定是否忽略大小写，startIndex<0或>Length将抛出异常
		int IndexOf(const VString& xString,int startIndex,bool ignoreCase=false)const;
		//指定起始位置并指定是否忽略大小写，length<0表示查找全部，startIndex<0或startIndex+length>Length将抛出异常
		int IndexOf(const VString& xString,int startIndex,int length,bool ignoreCase)const;
		//寻找wArray数组中任意字符在此字符串首次出现的位置（不包含结尾字符），length<0表示查找全部，startIndex<0或startIndex+length>Length将抛出异常
		int IndexOfAny(const XArray<wchar_t> wArray,int startIndex,int length)const;
		//寻找wArray数组中任意字符在此字符串首次出现的位置（不包含结尾字符），startIndex<0或startIndex+length>Length将抛出异常
		int IndexOfAny(const XArray<wchar_t> wArray,int startIndex=0)const;

		//查找指定 Unicode 字符在此字符串中的最后一个匹配项的索引，找不到返回-1
		int LastIndexOf(WCHAR wc)const;
		//指定起始位置并指定是否忽略大小写，startIndex<0或>Length将抛出异常
		int LastIndexOf(WCHAR wc,int startIndex,bool ignoreCase=false)const;
		//指定起始位置并指定是否忽略大小写，length<0表示查找全部，startIndex<0或startIndex+length>Length将抛出异常
		int LastIndexOf(WCHAR wc,int startIndex,int length,bool ignoreCase)const;
		//查找指定 字符串在此字符串中的最后一个匹配项的索引。 
		int LastIndexOf(const VString& xString)const;
		//指定起始位置并指定是否忽略大小写，startIndex<0或>Length将抛出异常
		int LastIndexOf(const VString& xString,int startIndex,bool ignoreCase=false)const;
		//指定起始位置并指定是否忽略大小写，length<0表示查找全部，startIndex<0或startIndex+length>Length将抛出异常
		int LastIndexOf(const VString& xString,int startIndex,int length,bool ignoreCase)const;
		//寻找wArray数组中任意字符在此字符串最后出现的位置（不包含结尾字符），length<0表示查找全部，startIndex<0或>Length将抛出异常
		int LastIndexOfAny(const XArray<wchar_t> wArray,int startIndex,int length)const;
		//寻找wArray数组中任意字符在此字符串最后出现的位置（不包含结尾字符），startIndex<0或startIndex+length>Length将抛出异常
		int LastIndexOfAny(const XArray<wchar_t> wArray,int startIndex=0)const;
		//计算10的i次方
		static double IntPow10(int i);
		//将p转换为一个整数double
		static double ToIntDouble(LPWSTR p);
		//汉字识别后的辅助函数
		unsigned long long GetChsValue(unsigned char* ptype,unsigned long long* pvalue,unsigned int len)const;

#ifdef _IOSFWD_
		friend std::istream& operator>>(std::istream& is, VString& str)
		{
			std::string s;
			std::istream& ss = is>>s;
			str = s.c_str();
			return ss;
		}
		friend std::wistream& operator>>(std::wistream& is, VString& str)
		{
			std::wstring s;
			std::wistream& ss = is>>s;
			str = s.c_str();
			return ss;
		}
		friend std::ostream& operator<<(std::ostream& os,const VString& str )
		{
			return os<<str.ToAnsi();
		}
		friend std::wostream& operator<<(std::wostream& os,const VString& str)
		{
			return os<<str.ToUnicode();
		}
#endif
#ifdef _CLR //托管支持
		//创建由count个字符string串接而成的字符串
		VString(volatile const System::String^string, int count=1);
		//定义到托管字符串的转换
		System::String^ ToGcString()const{return gcnew System::String(wString);}
		operator System::String^()const{return gcnew System::String(wString);}
		System::String^ operator->()const{return gcnew System::String(wString);}
		VString& operator=(System::String^string);
		VString& operator+=(System::String^ string){return *this+=VString(string);}
		VString& operator+=(System::Object^ obj){return *this+=obj->ToString();}
		friend VString operator+(volatile const System::String^ string,const VString& xString);
		friend VString operator+(const VString& xString,volatile const System::String^ string);
#endif
	};
	



	//友元函数声明
	XString operator+(const XString& xString1,const XString& xString2);
	XString operator+(const XString& xString,const XBase& xBase);
	XString operator+(const XBase& xBase,const XString& xString);
	XString operator+(const XString& xString1,LPCWSTR xString2);
	XString operator+(LPCWSTR xString1,const XString& xString2);
	XString operator+(const XString& xString1,LPCSTR xString2);
	XString operator+(LPCSTR xString1,const XString& xString2);
	bool operator==(const XString& xString1,const XString& xString2);//字符串比较
	bool operator==(const XString& xString1,LPCWSTR xString2);//字符串比较
	bool operator==(LPCWSTR xString1,const XString& xString2);//字符串比较
	bool operator==(const XString& xString1,LPCSTR xString2);//字符串比较
	bool operator==(LPCSTR xString1,const XString& xString2);//字符串比较
	bool operator!=(const XString& xString1,const XString& xString2);
	bool operator!=(const XString& xString1,LPCWSTR xString2);
	bool operator!=(LPCWSTR xString1,const XString& xString2);
	bool operator!=(const XString& xString1,LPCSTR xString2);
	bool operator!=(LPCSTR xString1,const XString& xString2);
	bool operator>(const XString& xString1,const XString& xString2);
	bool operator>(const XString& xString1,LPCWSTR xString2);
	bool operator>(LPCWSTR xString1,const XString& xString2);
	bool operator>(const XString& xString1,LPCSTR xString2);
	bool operator>(LPCSTR xString1,const XString& xString2);
	bool operator<(const XString& xString1,const XString& xString2);
	bool operator<(const XString& xString1,LPCWSTR xString2);
	bool operator<(LPCWSTR xString1,const XString& xString2);
	bool operator<(const XString& xString1,LPCSTR xString2);
	bool operator<(LPCSTR xString1,const XString& xString2);
	bool operator>=(const XString& xString1,const XString& xString2);
	bool operator>=(const XString& xString1,LPCWSTR xString2);
	bool operator>=(LPCWSTR xString1,const XString& xString2);
	bool operator>=(const XString& xString1,LPCSTR xString2);
	bool operator>=(LPCSTR xString1,const XString& xString2);
	bool operator<=(const XString& xString1,const XString& xString2);
	bool operator<=(const XString& xString1,LPCWSTR xString2);
	bool operator<=(LPCWSTR xString1,const XString& xString2);
	bool operator<=(const XString& xString1,LPCSTR xString2);
	bool operator<=(LPCSTR xString1,const XString& xString2);
#ifdef _CLR //托管支持
//	XString operator+(System::String^ string,const XString& xString);
//	XString operator+(const XString& xString,System::String^ string);
//	XString operator+(System::Object^ obj,const XString& xString);
//	XString operator+(const XString& xString,System::Object^ obj);
#endif
//debug模式下改变XString中指向目标字符串的指针，方便调试
#ifdef _DEBUG
#define XSTRINGCITEDCHANGE(pString)\
	pString = static_cast<VString*>(pObject)
#else
	#define XSTRINGCITEDCHANGE(pString)
#endif
	//字符串类型，引用类
	class XString:public XBase
	{
		friend VString;
#ifdef _DEBUG
		//debug模式下指向目标字符串的数据，方便调试
		VString* pString;
#endif
	public:
		PROPERTY_OFFSET(XString,Length);
		//默认构造函数
		XString(){}
		//复制构造函数
		XString(const XString&x);
		//从指针构造
		XString(VString*p);
		//析构函数函数
		virtual ~XString(){}
		VString* Pointer()const;
		XString* operator&(){return reinterpret_cast<XString*>(XBase:: operator&());}
		const XString* operator&()const{return reinterpret_cast<const XString*>(XBase:: operator&());}
		virtual XString* NewCopy()const{return new XString(*this);}
		static const XTypes& CurrentType;
		virtual const XTypes& GetType()const{return CurrentType;}
		//template<typename R,typename C,R (C::*PFnGet)(void)const,PFnOff off>XString(const property_get<R,C,PFnGet,off>& x){*this=XString(x.operator R());}
		//template<typename V,typename C,ptrdiff_t (*off)(),V (C::*PFnGet)()const,void (C::*PFnSet)(V)>XString(const property_getset<V,C,PFnGet,PFnSet,off>& x){*this=XString((V)x);}
		template<typename T,typename ObjectT>XString(const Property<T,ObjectT>& p){*this = (T)p;}
		template<typename T,typename ObjectT>XString(const PropertyReadOnly<T,ObjectT>& p){*this = (T)p;}
		template<typename T,typename ObjectT>XString(const StaticProperty<T>& p){*this = (T)p;}
		template<typename T,typename ObjectT>XString(const StaticPropertyReadOnly<T>& p){*this = (T)p;}
		//代表一个空字符串""
		const static XString Empty;
		


		//比较两个字符串的大小，指定是否忽略大小写
		static int Compare(const XString xString1,const XString xString2,bool ignoreCase=false);
		//比较两个子字符串的大小，指定是否忽略大小写
		static int Compare(const XString xString1,int index1,const XString xString2,int index2,int length,bool ignoreCase=false);
		//串接两个对象的字符串表示
		static XString Concat(const XBase& object1,const XBase& object2);
		//串接三个对象的字符串表示
		static XString Concat(const XBase& object1,const XBase& object2,const XBase& object3);
		//串接四个对象的字符串表示
		static XString Concat(const XBase& object1,const XBase& object2,const XBase& object3,const XBase& object4);
		//串接字符串数组
		static XString Concat(const XArray<XString> strings);
		//串接数组中的对象指针指向对象的字符串表示
		static XString Concat(const XArray<XBase*> strings);
		//在几个字符串间加上连接字符串以串接成新的字符串
		static XString Join(const XString str,const XArray<XString> strs,int startIndex=0,int count=-1);

		//由数字创建字符串，format使用字符串指定格式
		explicit XString(float number,LPCWSTR format=L"%g");
		//由数字创建字符串，format使用字符串指定格式
		explicit XString(double number,LPCWSTR format=L"%g");
		//由数字创建字符串，format使用字符串指定格式
		explicit XString(unsigned long long number,LPCWSTR format=L"%d");
		//由数字创建字符串，format使用字符串指定格式
		explicit XString(unsigned long number,LPCWSTR format=L"%d");
		//由数字创建字符串，format使用字符串指定格式
		explicit XString(unsigned int number,LPCWSTR format=L"%d");
		//由数字创建字符串，format使用字符串指定格式
		explicit XString(long long number,LPCWSTR format=L"%d");
		//由数字创建字符串，format使用字符串指定格式
		explicit XString(long number,LPCWSTR format=L"%d");
		//由数字创建字符串，format使用字符串指定格式
		explicit XString(int number,LPCWSTR format=L"%d");
		//由数字创建字符串，format使用字符串指定格式
		explicit XString(unsigned short number,LPCWSTR format);
		//由数字创建字符串，format使用字符串指定格式
		explicit XString(short number,LPCWSTR format);
		//由数字创建字符串，format使用字符串指定格式
		explicit XString(unsigned char number,LPCWSTR format);
		//由数字创建字符串，format使用字符串指定格式
		explicit XString(signed char number,LPCWSTR format);
		//创建由count个字符c串接而成的字符串
		XString(CHAR c,int count =1);
		//创建由count个宽字节字符wc串接而成的字符串
		XString(WCHAR wc,int count =1);
		//创建由count个wString字符串串接而成的字符串
		XString(LPCWSTR wString,int count =1);
		//创建由count个mString字符串串接而成的字符串
		XString(LPCSTR mString,int count =1);
		//创建由count个wString字符串串接而成的字符串
		XString(const XArray<WCHAR> wString,int count =1);
		//创建由count个mString字符串串接而成的字符串
		XString(const XArray<CHAR> mString,int count =1);
		//创建由wString字符串startindex字符起数length个字符的字符串，如果length<=-2，则表示到'\0'表示的结尾
		XString(LPCWSTR wString,int startIndex,int length);
		//创建由mString字符串startindex字符起数length个字符的字符串，如果length<=-2，则表示到'\0'表示的结尾
		XString(LPCSTR mString,int startIndex,int length);
		//由count个VString创建
		XString(const VString& ,int count);
		//创建由count个XString字符串串接而成的字符串
		XString(const XString xString, int count);
		//创建由两个XString串接而成的字符串
		XString(const XString xString1,const XString xString2);
		//创建由三个XString串接而成的字符串
		XString(const XString xString1,const XString xString2,const  XString xString3);
		//创建由四个XString串接而成的字符串
		XString(const XString xString1,const XString xString2,const  XString xString3,const  XString xString4);
		//创建由xStrings数组串接而成的字符串
		XString(const XArray<XString>xStrings);
		//索引
		WCHAR operator[](int index)const;
		//迭代器
		Iterator<const WCHAR> First()const;
		//迭代器
		Iterator<const WCHAR> begin()const;
		//迭代器
		Iterator<const WCHAR> Last()const;
		//迭代器
		Iterator<const WCHAR> End()const;
		//迭代器
		Iterator<const WCHAR> end()const;
		//长度
		int GetLength()const;
		//只读属性：字符串长度
		PROPERTY_GET(int,XString,GetLength,Length);

		//输出一个副本
		virtual XString ToString()const;
		//转换成原始的多字节字符串，const型
		LPCSTR ToAnsi()const;
		//输出宽字节字符串，const型
		LPCWSTR ToUnicode()const;
		//转换为一个unsigned long long
		unsigned long long ToUInt64()const;
		//转换为一个long long
		long long ToInt64()const;
		//转换为一个double
		double ToDouble()const;
		//转换为一个unsigned long long，使用汉字支持
		unsigned long long ChsToUInt64()const;
		//转换为一个long long，使用汉字支持
		long long ChsToInt64()const;
		operator LPCSTR()const;
		operator LPCWSTR()const;

		XString& operator=(const XString& xString);//赋值运算
		XString& operator=(LPCSTR mString);
		XString& operator=(LPCWSTR wString);
		XString& operator+=(const XString& xString);//串接运算
		XString& operator+=(const XBase& xBase);
		friend bool operator==(const XString& xString1,const XString& xString2);//字符串比较
		friend bool operator!=(const XString& xString1,const XString& xString2);
		friend bool operator>(const XString& xString1,const XString& xString2);
		friend bool operator<(const XString& xString1,const XString& xString2);
		friend bool operator>=(const XString& xString1,const XString& xString2);
		friend bool operator<=(const XString& xString1,const XString& xString2);

		friend XString operator+(const XString& xString1,const XString& xString2);
		friend XString operator+(const XString& xString,const XBase& xBase);
		friend XString operator+(const XBase& xBase,const XString& xString);
		friend XString operator+(const XString& xString1,LPCWSTR xString2);
		friend XString operator+(LPCWSTR xString1,const XString& xString2);
		friend XString operator+(const XString& xString1,LPCSTR xString2);
		friend XString operator+(LPCSTR xString1,const XString& xString2);

#ifdef _IOSFWD_
		friend std::istream& operator>>(std::istream& is, XString& str)
		{
			std::string s;
			std::istream& ss = is>>s;
			str = s.c_str();
			return ss;
		}
		friend std::wistream& operator>>(std::wistream& is, XString& str)
		{
			std::wstring s;
			std::wistream& ss = is>>s;
			str = s.c_str();
			return ss;
		}
		friend std::ostream& operator<<(std::ostream& os,const XString& str )
		{
			return os<<str.ToAnsi();
		}
		friend std::wostream& operator<<(std::wostream& os,const XString& str)
		{
			return os<<str.ToUnicode();
		}
#endif
		//与object的字符串表示比较
		int CompareTo(const XBase& object)const;
		//与string字符串表示比较
		int CompareTo(const XString& string)const;
		//复制到多字节数组，返回复制的字节数,lengthOfByte<0将自动判断字节数，sourceByteIndex<0或destinationByteIndex<0将抛出异常
		int CopyTo(XArray<char> destination,int sourceByteIndex=0,int destinationByteIndex=0,int lengthOfByte=-1)const;
		//复制到宽字节数组，返回复制的字符数,length<0将自动判断字节数，sourceIndex<0或destinationIndex<0将抛出异常
		int CopyTo(XArray<wchar_t> destination,int sourceIndex=0,int destinationIndex=0,int length=-1)const;
		//判断该字符串是否包含xString
		bool Contains(const XString& xString)const;
		//获取该字符串中字符wch出现的次数
		int CountOf(WCHAR wch)const;
		//获取该字符串中字符串str出现的次数
		int CountOf(const XString& str)const;
		//判断该字符串是否以xString结尾
		bool EndsWith(const XString& xString)const;
		//判断该字符串是否以xString开头
		bool StartsWith(const XString& xString)const;
		//与object的字符串表示比较，看是否相等
		virtual bool Equals(const XBase& object)const;
		//与指定字符串比较，看是否相等
		virtual bool Equals(const XString&)const;
		//检索一个子字符串，当length<0时返回至结尾的子字符串 ，startIndex<0或startIndex+length>Length将抛出异常
		XString Substring(int startIndex, int length=-2)const;
		//检索一个子字符串，当length<0时返回至结尾的子字符串 ,与Substring方法不同，遇到换行符将自动返回。这里的length表示字节长度，而且为了保证字符的完整性，返回的字符串的字节长度有可能小于指定的length。,startIndex<0或startIndex>Length将抛出异常
		XString Cut(int startIndex, int length=-2)const;
		//返回在startIndex位置插入xString的新字符串，该字符串不变，startIndex<0将抛出异常
		XString Insert(int startIndex,const XString& xString)const;
		//在左边插入一定数量的wc，使字符串右对齐，返回一个有totalWidth个字符的字符串，该字符串不变，如果原字符串的长度大于totalWidth，则直接返回该字符串
		XString PadLeft(int totalWidth,WCHAR wc=' ')const;
		//在右边插入一定数量的wc，使字符串左对齐，
		XString PadRight(int totalWidth,WCHAR wc=' ')const;
		//从startIndex起移除一定长度的内容，返回得到的新字符串，length小于0则表示移除后面所有的字符串，startIndex<0或startIndex+length>Length将抛出异常
		XString Remove(int startIndex,int length=-1)const;
		//返回一个新字符串，内容为原字符串中的wc1全替换为wc2,并指定比较时是否忽略大小写
		XString Replace(WCHAR wc1,WCHAR wc2,bool ignoreCase=false)const;
		//返回一个新字符串，内容为原字符串中的xString1全替换为xString2，并指定比较时是否忽略大小写
		XString Replace(const XString& xString1 ,const XString& xString2,bool ignoreCase=false)const;
		//返回一个新字符串，新字符串为该所有的小写字母都变成大写
		XString ToUpper()const;
		//返回一个新字符串，新字符串为该所有的大写字母都变成小写
		XString ToLower()const;
		//获取字符串中的英文单词（数字不算，比如“G2 VS2010”得到：“G”“VS”）
		XArray<XString> GetWords()const;
		//获取字符串中的数字，比如“G2 VS2010”得到：“2010”
		XArray<XString> GetNumbers()const;
		//获取字符串中的英文和数字（英文和数字可连在一起，比如“G2 VS2010”得到：“G2”、“VS2010”）
		XArray<XString> GetWordsAndNumbers()const;
		//返回该字符串的宽字节数组表示（不包含结尾字符'\0'），startIndex<0或startIndex+length>Length将抛出异常
		XArray<WCHAR> ToWCharArray( int startIndex=0,int length=-1)const;
		//返回使用指定字符做分隔符分割形成的字符串数组,并指定最大数量
		XArray<XString> Split(WCHAR ch, int maxCount)const;
		//返回使用指定字符做分隔符分割形成的字符串数组
		XArray<XString> Split(WCHAR ch = L' ')const;
		//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量
		XArray<XString> Split(const XString& str,int maxCount=MaxValues::Int)const;
		//返回使用指定字符做分隔符分割形成的字符串数组,并指定最大数量,是否移除空字符串
		XArray<XString> Split(WCHAR ch, int maxCount,bool removeEmpty)const;
		//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量,是否移除空字符串
		XArray<XString> Split(const XString& str,int maxCount,bool removeEmpty)const;
		//返回使用指定字符数组中出现的字符做分隔符分割形成的字符串数组,并指定最大数量,并指明是否移除空字符串
		XArray<XString> Split(const XArray<WCHAR> chs,int maxCount,bool removeEmpty)const;
		//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量,并指明是否移除空字符串
		XArray<XString> Split(const XArray<XString> strs,int maxCount,bool removeEmpty)const;
		//返回使用指定字符数组中出现的字符做分隔符分割形成的字符串数组,并指定最大数量
		XArray<XString> Split(const XArray<WCHAR> chs,int maxCount=MaxValues::Int)const;
		//返回使用指定字符串做分隔符分割形成的字符串数组,并指定最大数量
		XArray<XString> Split(const XArray<XString> strs,int maxCount=MaxValues::Int)const;
		//返回一个值，指使该字符串是否为空（包括NULL和""）
		bool IsNullOrEmpty()const;

		//查找指定 Unicode 字符在此字符串中的第一个匹配项的索引。 
		int IndexOf(WCHAR wc)const;
		//指定起始位置并指定是否忽略大小写，startIndex<0或>Length将抛出异常
		int IndexOf(WCHAR wc,int startIndex,bool ignoreCase=false)const;
		//指定起始位置并指定是否忽略大小写，length<0表示查找全部，startIndex<0或startIndex+length>Length将抛出异常
		int IndexOf(WCHAR wc,int startIndex,int length,bool ignoreCase)const;
		//查找指定 字符串在此字符串中的第一个匹配项的索引。 
		int IndexOf(const XString& xString)const;
		//指定起始位置并指定是否忽略大小写，startIndex<0或>Length将抛出异常
		int IndexOf(const XString& xString,int startIndex,bool ignoreCase=false)const;
		//指定起始位置并指定是否忽略大小写，length<0表示查找全部，startIndex<0或startIndex+length>Length将抛出异常
		int IndexOf(const XString& xString,int startIndex,int length,bool ignoreCase)const;
		//寻找wArray数组中任意字符在此字符串首次出现的位置（不包含结尾字符），length<0表示查找全部，startIndex<0或startIndex+length>Length将抛出异常
		int IndexOfAny(const XArray<wchar_t> wArray,int startIndex,int length)const;
		//寻找wArray数组中任意字符在此字符串首次出现的位置（不包含结尾字符），startIndex<0或startIndex+length>Length将抛出异常
		int IndexOfAny(const XArray<wchar_t> wArray,int startIndex=0)const;

		//查找指定 Unicode 字符在此字符串中的最后一个匹配项的索引，找不到返回-1
		int LastIndexOf(WCHAR wc)const;
		//指定起始位置并指定是否忽略大小写，startIndex<0或>Length将抛出异常
		int LastIndexOf(WCHAR wc,int startIndex,bool ignoreCase=false)const;
		//指定起始位置并指定是否忽略大小写，length<0表示查找全部，startIndex<0或startIndex+length>Length将抛出异常
		int LastIndexOf(WCHAR wc,int startIndex,int length,bool ignoreCase)const;
		//查找指定 字符串在此字符串中的最后一个匹配项的索引。 
		int LastIndexOf(const XString xString)const;
		//指定起始位置并指定是否忽略大小写，startIndex<0或>Length将抛出异常
		int LastIndexOf(const XString xString,int startIndex,bool ignoreCase=false)const;
		//指定起始位置并指定是否忽略大小写，length<0表示查找全部，startIndex<0或startIndex+length>Length将抛出异常
		int LastIndexOf(const XString xString,int startIndex,int length,bool ignoreCase)const;
		//寻找wArray数组中任意字符在此字符串最后出现的位置（不包含结尾字符），startIndex<0或>Length将抛出异常
		int LastIndexOfAny(const XArray<wchar_t> wArray,int startIndex,int length)const;
		//寻找wArray数组中任意字符在此字符串最后出现的位置（不包含结尾字符），startIndex<0或startIndex+length>Length将抛出异常
		int LastIndexOfAny(const XArray<wchar_t> wArray,int startIndex=0)const;

#ifdef _CLR //托管支持
		//创建由count个字符string串接而成的字符串
		XString(volatile const System::String^string, int count=1);
		//定义到托管字符串的转换
		System::String^ ToGcString()const ;
		operator System::String^()const;
		System::String^ operator->()const;
		XString& operator=(System::String^);
		XString& operator+=(System::String^ string);
		XString& operator+=(System::Object^ obj);
		friend XString operator+(volatile const System::String^ string,const XString xString);
		friend XString operator+(const XString xString,volatile const System::String^ string);
#endif
	};
	
}