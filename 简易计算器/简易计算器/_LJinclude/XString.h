#pragma once//��W�Ⲩ(LuoJun)��д
#define XSTRING_
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

		bool operator==(const VString& vString1,const VString& vString2);//�ַ����Ƚ�
		bool operator!=(const VString& vString1,const VString& vString2);
		bool operator>(const VString& vString1,const VString& vString2);
		bool operator<(const VString& vString1,const VString& vString2);
		bool operator>=(const VString& vString1,const VString& vString2);
		bool operator<=(const VString& vString1,const VString& vString2);

		VString operator+(const VString& vString1,const VString& vString2);
		VString operator+(const VString& vString,const XBase& xBase);
		VString operator+(const XBase& xBase,const VString& vString);

	//�ַ����������ݣ������ж���ľ�̬����Ϊ��ԭʼ�ַ����Ĳ����������еķ�����ֱ�Ӹı��ַ�����������ݣ����̲߳���������ȫ
	class VString:public XBase
	{
#define ChsNumMaxCount 21
#define ChsUnitMaxCount 9
		static LPCWSTR ppNumWChs[ChsNumMaxCount];//��¼�����ַ�
		static unsigned char pNumCounts[ChsNumMaxCount];//��ʵÿ�������ַ���
		static LPCWSTR ppUnitWChs[ChsUnitMaxCount];//��¼��λ�ַ�
		static unsigned long long pUnitValue[ChsUnitMaxCount];//��¼ÿ����λ��Ӧ����ֵ
		static unsigned char pUnitCounts[ChsUnitMaxCount];//��¼ÿ����λ��Ӧ���ַ�����

		//���ֽ��ַ�������char* mString;
		volatile LPSTR mString;
		//���ֽ��ַ�������wchar_t* wString;
		LPWSTR wString;
	public:
		//wmemchr
		static inline const wchar_t * wmemchr(const wchar_t *_S, wchar_t _C, size_t _N){for (; 0 < _N; ++_S, --_N)if (*_S == _C)return _S;return (0); }
		//����ͨ�÷���
		XBaseVTypeMethods_H(VString);
		//ʹ�ÿ��ֽڴ洢����Ҫ��ʱ��ת���ɶ��ֽ�
		//wString�����е��ַ���
		const int Length;
		//���ԭʼ�ַ����Ĳ���������

		//�������ֽ��ַ����ַ������������NULL�򱨴�
		static inline int Strlen(LPCSTR mString){return mString==NULL?0:(int)strlen(mString);}
		//�������ֽ��ַ����ַ������������NULL�򱨴�
		static inline int Strlen(LPCWSTR wString){return wString==NULL?0:(int)wcslen(wString);}
		//�����ַ�����һ��new������¿ռ䣬������һ��ָ��ÿռ��ָ�룬ʹ�������delete[]ɾ����length(��ѡ)Ϊָ��Ҫ���Ƶĳ���
		static inline LPSTR Strcpy(LPCSTR mString,int length){CHAR* p = new CHAR[length+1];Memory::Copy(p,mString,length);p[length]=0;return p;}
		//�����ַ�����һ��new������¿ռ䣬������һ��ָ��ÿռ��ָ�룬ʹ�������delete[]ɾ����length(��ѡ)Ϊָ��Ҫ���Ƶĳ���
		static inline LPWSTR Strcpy(LPCWSTR wString,int length){WCHAR* p = new WCHAR[length+1];Memory::Copy(p,wString,length*2);	p[length]=0;return p;}
		//�����ַ�����һ��new������¿ռ䣬������һ��ָ��ÿռ��ָ�룬ʹ�������delete[]ɾ����length(��ѡ)Ϊָ��Ҫ���Ƶĳ���
		static inline LPSTR Strcpy(LPCSTR mString){int length = (int)strlen(mString);	CHAR* p = new CHAR[length+1];Memory::Copy(p,mString,length);p[length]=0;return p;}
		//�����ַ�����һ��new������¿ռ䣬������һ��ָ��ÿռ��ָ�룬ʹ�������delete[]ɾ����length(��ѡ)Ϊָ��Ҫ���Ƶĳ���
		static inline LPWSTR Strcpy(LPCWSTR wString)	{int length = (int)wcslen(wString);WCHAR* p = new WCHAR[length+1];Memory::Copy(p,wString,length*2);p[length]=0;return p;}
		//�Ƚ������ַ����Ĵ�С����ѡ������ַ�������
		static inline int Strcmp(LPCSTR mString1, LPCSTR mString2,int length){return memcmp(mString1,mString2,length);}
		//�Ƚ������ַ����Ĵ�С����ѡ������ַ�������
		static inline int Strcmp(LPCSTR mString1, LPCSTR mString2){return strcmp(mString1,mString2);}
		//�Ƚ������ַ����Ĵ�С����ѡ������ַ�������
		static inline int Strcmp(const wchar_t* wString1, const wchar_t* wString2,int length){return wcsncmp(wString1,wString2,length);}
		//�Ƚ������ַ����Ĵ�С����ѡ������ַ�������
		static inline int Strcmp(LPCWSTR wString1, LPCWSTR wString2){return wcscmp(wString1,wString2);}
		//�����ַ���,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static inline LPSTR Strcat(LPCSTR mString1,LPCSTR mString2,int length1,int length2){LPSTR p = new CHAR[length1+length2+1];Memory::Copy(p,mString1,length1);Memory::Copy(p+length1,mString2,length2);p[length1+length2]=0;return p;}
		//�����ַ���,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static inline LPSTR Strcat(LPCSTR mString1,LPCSTR mString2){	return Strcat(mString1,mString2,Strlen(mString1),Strlen(mString2));}
		//�����ַ���,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static inline LPSTR Strcat(LPCSTR mString1,LPCSTR mString2,LPCSTR mString3,int length1,int length2,int length3){LPSTR p = new CHAR[length1+length2+length3+1];Memory::Copy(p,mString1,length1);Memory::Copy(p+length1,mString2,length2);Memory::Copy(p+length1+length2,mString3,length3);p[length1+length2+length3]=0;return p;}
		//�����ַ���,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static inline LPSTR Strcat(LPCSTR mString1,LPCSTR mString2,LPCSTR mString3){return Strcat(mString1,mString2,mString3,Strlen(mString1),Strlen(mString2),Strlen(mString3));}
		//�����ַ���,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static inline LPSTR Strcat(LPCSTR mString1,LPCSTR mString2,LPCSTR mString3,LPCSTR mString4,int length1,int length2,int length3,int length4){LPSTR p = new CHAR[length1+length2+length3+length4+1];Memory::Copy(p,mString1,length1);Memory::Copy(p+length1,mString2,length2);Memory::Copy(p+length1+length2,mString3,length3);Memory::Copy(p+length1+length2+length3,mString4,length4);p[length1+length2+length3+length4]=0;return p;}
		//�����ַ���,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static inline LPSTR Strcat(LPCSTR mString1,LPCSTR mString2,LPCSTR mString3,LPCSTR mString4){return Strcat(mString1,mString2,mString3,mString4,Strlen(mString1),Strlen(mString2),Strlen(mString3),(int)strlen(mString4));}
		//�����ַ���,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static inline LPWSTR Strcat(LPCWSTR wString1,LPCWSTR wString2,int length1,int length2){LPWSTR p = new WCHAR[length1+length2+1];Memory::Copy(p,wString1,length1*2);Memory::Copy(p+length1,wString2,length2*2);p[length1+length2]=0;return p;}
		//�����ַ���,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static inline LPWSTR Strcat(LPCWSTR wString1,LPCWSTR wString2){return Strcat(wString1,wString2,Strlen(wString1),Strlen(wString2));}
		//�����ַ���,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static inline LPWSTR Strcat(LPCWSTR wString1,LPCWSTR wString2,LPCWSTR wString3,int length1,int length2,int length3){LPWSTR p = new WCHAR[length1+length2+length3+1];Memory::Copy(p,wString1,length1*2);Memory::Copy(p+length1,wString2,length2*2);Memory::Copy(p+length1+length2,wString3,length3*2);p[length1+length2+length3]=0;return p;}
		//�����ַ���,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static inline LPWSTR Strcat(LPCWSTR wString1,LPCWSTR wString2,LPCWSTR wString3){return Strcat(wString1,wString2,wString3,Strlen(wString1),Strlen(wString2),Strlen(wString3));}
		//�����ַ���,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static inline LPWSTR Strcat(LPCWSTR wString1,LPCWSTR wString2,LPCWSTR wString3,LPCWSTR wString4,int length1,int length2,int length3,int length4){LPWSTR p = new WCHAR[length1+length2+length3+length4+1];Memory::Copy(p,wString1,length1*2);Memory::Copy(p+length1,wString2,length2*2);Memory::Copy(p+length1+length2,wString3,length3*2);Memory::Copy(p+length1+length2+length3,wString4,length4*2);p[length1+length2+length3+length4]=0;	return p;}
		//�����ַ���,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static inline LPWSTR Strcat(LPCWSTR wString1,LPCWSTR wString2,LPCWSTR wString3,LPCWSTR wString4){return Strcat(wString1,wString2,wString3,wString4,Strlen(wString1),Strlen(wString2),Strlen(wString3),Strlen(wString4));}
		//�ַ�������count��,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static LPWSTR StrRepeat(LPCWSTR wString,int count);
		//�ַ�������count��,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static LPSTR StrRepeat(LPCSTR mString,int count);
		//�ַ�������count��,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static LPWSTR StrRepeat(LPCWSTR wString,int length,int count);
		//�ַ�������count��,����һ��new����Ŀռ䣬�������õ����ַ������ŵ����У�ʹ�������delete[]ɾ��
		static LPSTR StrRepeat(LPCSTR mString,int length,int count);
		//����һ��ʹ��new����Ŀռ䣬����Ϊ��string2�ַ������뵽string1��strtIndexλ�ô������ַ�������ָ���ַ�������
		static inline LPSTR Strins(LPCSTR mString1, LPCSTR mString2,int startIndex,int length1,int length2){LPSTR p = new CHAR[length1+length2+1];Memory::Copy(p,mString1,startIndex);Memory::Copy(p+startIndex,mString2,length2);Memory::Copy(p+startIndex+length2,mString1+startIndex,length1-startIndex);p[length1+length2]=0;return p;}
		//����һ��ʹ��new����Ŀռ䣬����Ϊ��string2�ַ������뵽string1��strtIndexλ�ô������ַ�������ָ���ַ�������
		static inline LPWSTR Strins(LPCWSTR mString1, LPCWSTR mString2,int startIndex,int length1,int length2){LPWSTR p = new WCHAR[length1+length2+1];Memory::Copy(p,mString1,startIndex*2);Memory::Copy(p+startIndex,mString2,length2*2);Memory::Copy(p+startIndex+length2,mString1+startIndex,(length1-startIndex)*2);	p[length1+length2]=0;	return p;}
		//�����ַ����ַ������ֵ�λ��,��ѡ��ָ�����ȣ��Ҳ�������-1
		static inline int Strchr(LPCSTR mString,CHAR ch,int length){const void* p = memchr(mString,ch,length);return p?int((LPCSTR)p-mString):-1;}
		//�����ַ����ַ������ֵ�λ��,��ѡ��ָ�����ȣ��Ҳ�������-1
		static inline int Strchr(LPCSTR mString,CHAR ch){LPCSTR p = strchr(mString,ch);return p?int(p-mString):-1;}
		//�����ַ����ַ������ֵ�λ��,��ѡ��ָ�����ȣ��Ҳ�������-1
		static inline int Strchr(LPCWSTR wString, WCHAR ch,int length){const void* p = wmemchr(wString,ch,length);return p?int((LPCWSTR)p-wString):-1;}
		//�����ַ����ַ������ֵ�λ��,��ѡ��ָ�����ȣ��Ҳ�������-1
		static inline int Strchr(LPCWSTR wString, WCHAR ch){LPCWSTR p = wcschr(wString,ch);return p?int(p-wString):-1;}
		//�����ַ������ַ������ֵ�λ��,��ѡ��ָ�����ȣ��Ҳ�������-1
		static inline int Strstr(LPCSTR mString1, LPCSTR mString2){LPCSTR p = strstr(mString1,mString2);return p?int(p-mString1):-1;}
		//�����ַ������ַ������ֵ�λ��,��ѡ��ָ�����ȣ��Ҳ�������-1
		static inline int Strstr(LPCSTR mString1, LPCSTR mString2,int length1,int length2){void* p = (void*)mString1;while(length1>(LPSTR)p-mString1){p = memchr(p,*mString2,length1);if(p==NULL || length1-((LPSTR)p-mString1)<length2)return -1;if(memcmp(p,mString2,length2))p = (LPSTR)p+1;else return (int)((LPSTR)p-mString1);}return -1;}
		//�����ַ������ַ������ֵ�λ��,��ѡ��ָ�����ȣ��Ҳ�������-1
		static inline int Strstr(LPCWSTR wString1, LPCWSTR wString2){LPCWSTR p = wcsstr(wString1,wString2);	if(p)return int(p-wString1);return -1;}
		//�����ַ������ַ������ֵ�λ��,��ѡ��ָ�����ȣ��Ҳ�������-1
		static inline int Strstr(LPCWSTR wString1, LPCWSTR wString2,int length1,int length2){LPCWSTR p =wString1;while(length1>p-wString1){p = (LPCWSTR)wmemchr(p,*wString2,length1);if(p==NULL || length1-(p-wString1)<length2)return -1;if(memcmp(p,wString2,length2*2))p = p+1;else return int(p-wString1);}return -1;}
		//���ֽ�ת��Ϊ���ֽڣ�length��ʾ����source����ֹ�ַ�'\0'���ַ������ֽ�������-1����NULL��-2�����Զ����㣬����ת������ַ�������ͨ��outputlength��ȡת������ַ�������
		static LPWSTR AnsiToUnicode(LPCSTR source,int* outLength,int length=-2);
		//���ֽ�ת��Ϊ���ֽڣ�length��ʾ����source����ֹ�ַ�'\0'���ַ������ֽ�������-1����NULL��-2�����Զ����㣬����ת������ַ�������ͨ��outputlength��ȡת������ַ�������
		static LPWSTR AnsiToUnicode(LPCSTR source,int length=-2);
		//���ֽ�ת��Ϊ���ֽڣ�length��ʾ����source����ֹ�ַ�'\0'���ַ���(�ֽ���/2)������ת������ַ���
		static LPSTR UnicodeToAnsi(LPCWSTR source,int* outLength,int length=-2);
		//���ֽ�ת��Ϊ���ֽڣ�length��ʾ����source����ֹ�ַ�'\0'���ַ���(�ֽ���/2)������ת������ַ���
		static LPSTR UnicodeToAnsi(LPCWSTR source,int length=-2);

		//����vString2��vString1��λ�ã�maxLength1��maxLength2�ֱ������ַ����ĳ���
		static int Find(const VString& vString1,int index1,const VString& vString2,int index2,int maxLength1,int maxLength2,bool ignoreCase);
		//����vString2��vString1�����ֵ�λ��
		static int Last(const VString& vString1,int index1,const VString& vString2,int index2,int maxLength1,int maxLength2,bool ignoreCase);

		//һ�����ַ���������
		const static VString Empty;

		//�����������ͷ�ռ�õĿռ�
		virtual ~VString();
		//���캯��
		VString();
		//ֱ�Ӵ���ָ���Ĳ����������ַ������ַ���ws����ͨ��new���䣬��������VString��ִ��delete��ms����ΪNULL
		inline VString(int length,LPWSTR ws,LPSTR ms):Length(length),wString(ws),mString(ms){}
		//���ƹ���
		inline VString(const VString& str,int count=1):Length(str.Length*count),wString(StrRepeat(str.wString,str.Length,count)),mString(NULL){}
		//��count��XString����
		explicit VString(const XString str,int count=1);
		//��count��LPWSTR����
		inline VString(LPCWSTR str,int count=1):Length(Strlen(str)*count),wString(StrRepeat(str,count)),mString(NULL){}
		//��count��LPSTR����
		VString(LPCSTR str,int count=1);
		//��count��CHAR����
		VString(CHAR c,int count=1);
		//��count��WCHAR����
		VString(WCHAR wc,int count=1);
		//���ַ����鹹�����wstr����\0������沿�ֽ�������
		VString(const XArray<WCHAR> wstr,int count=1);
		//���ַ����鹹�����mstr����\0������沿�ֽ�������
		VString(const XArray<CHAR> mstr,int count=1);

		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit VString(float number,LPCWSTR format=L"%g");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit VString(double number,LPCWSTR format=L"%g");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit VString(unsigned long long number,LPCWSTR format);
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit VString(unsigned long number,LPCWSTR format=L"%d");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit VString(unsigned int number,LPCWSTR format=L"%d");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit VString(long long number,LPCWSTR format=L"%d");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit VString(long number,LPCWSTR format=L"%d");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit VString(int number,LPCWSTR format=L"%d");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit VString(unsigned short number,LPCWSTR format);
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit VString(short number,LPCWSTR format);
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit VString(unsigned char number,LPCWSTR format);
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit VString(signed char number,LPCWSTR format);
		//���һ�����ø��ַ���ʵ�帱����XString
		virtual XString ToString()const;
		//ת����ԭʼ�Ķ��ֽ��ַ�����const��
		LPCSTR const ToAnsi()const;
		//ת����ԭʼ�Ŀ��ֽ��ַ�����const��
		inline LPCWSTR const& ToUnicode()const{return wString;}
		//����
		const WCHAR operator[](int index)const;
		//����
		WCHAR& operator[](int index);
		//������
		Iterator<WCHAR> First();
		//������
		Iterator<const WCHAR> First()const;
		//������
		inline Iterator<WCHAR> begin(){return First();}
		//������
		inline Iterator<const WCHAR> begin()const{return First();}
		//������
		Iterator<WCHAR> Last();
		//������
		Iterator<const WCHAR> Last()const;
		//������
		Iterator<WCHAR> End();
		//������
		Iterator<const WCHAR> End()const;
		//������
		inline Iterator<WCHAR> end(){return End();}
		//������
		inline Iterator<const WCHAR> end()const{return End();}
		operator LPCSTR const()const{return ToAnsi();}
		operator LPCWSTR const&()const{return wString;}
		//ת��Ϊһ��unsigned long long
		unsigned long long ToUInt64()const;
		//ת��Ϊһ��long long
		long long ToInt64()const;
		//ת��Ϊһ��double
		double ToDouble()const;
		//ת��Ϊһ��unsigned long long��ʹ�ú���֧��
		unsigned long long ChsToUInt64(LPCWSTR p=0,unsigned int len=0)const;
		//ת��Ϊһ��long long��ʹ�ú���֧��
		long long ChsToInt64()const;

		VString& operator=(const VString& vString);//��ֵ����
		VString& operator=(LPCSTR mstr);
		VString& operator=(LPCWSTR wstr);
		VString& operator+=(const VString& vString);//��������
		VString& operator+=(LPCSTR mstr);
		VString& operator+=(LPCWSTR wstr);
		friend bool operator==(const VString& vString1,const VString& vString2);//�ַ����Ƚ�
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

		//��object���ַ�����ʾ�Ƚ�
		int CompareTo(const XBase& object)const;
		//��string�ַ�����ʾ�Ƚ�
		int CompareTo(const VString& string)const{	return Strcmp(wString,string.ToUnicode());}
		//���Ƶ����ֽ����飬���ظ��Ƶ��ֽ���,lengthOfByte<0���Զ��ж��ֽ�����sourceByteIndex<0��destinationByteIndex<0���׳��쳣
		int CopyTo(XArray<char>& destination,int sourceByteIndex=0,int destinationByteIndex=0,int lengthOfByte=-1)const;
		//���Ƶ����ֽ����飬���ظ��Ƶ��ַ���,length<0���Զ��ж��ֽ�����sourceIndex<0��destinationIndex<0���׳��쳣
		int CopyTo(XArray<wchar_t> destination,int sourceIndex=0,int destinationIndex=0,int length=-1)const;
		//�жϸ��ַ����Ƿ����xString
		bool Contains(const VString& xString)const;
		//��ȡ���ַ������ַ�wch���ֵĴ���
		int CountOf(WCHAR wch)const;
		//��ȡ���ַ������ַ���str���ֵĴ���
		int CountOf(const VString& str)const;
		//�жϸ��ַ����Ƿ���xString��β
		bool EndsWith(const VString& xString)const;
		//�жϸ��ַ����Ƿ���xString��ͷ
		bool StartsWith(const VString& xString)const;
		//��object���ַ�����ʾ�Ƚϣ����Ƿ����
		virtual bool Equals(const XBase& object)const;
		//��ָ���ַ����Ƚϣ����Ƿ����
		virtual bool Equals(const VString&)const;
		//����һ�����ַ�������length<0ʱ��������β�����ַ��� ��startIndex<0��startIndex+length>Length���׳��쳣
		VString Substring(int startIndex, int length=-2)const;
		//����һ�����ַ�������length<0ʱ��������β�����ַ��� ,��Substring������ͬ���������з����Զ����ء������length��ʾ�ֽڳ��ȣ�����Ϊ�˱�֤�ַ��������ԣ����ص��ַ������ֽڳ����п���С��ָ����length��,startIndex<0��startIndex>Length���׳��쳣
		VString Cut(int startIndex, int length=-2)const;
		//������startIndexλ�ò���xString�����ַ��������ַ������䣬startIndex<0���׳��쳣
		VString& Insert(int startIndex,const VString& xString);
		//����߲���һ��������wc��ʹ�ַ����Ҷ��룬����һ����totalWidth���ַ����ַ��������ַ������䣬���ԭ�ַ����ĳ��ȴ���totalWidth����ֱ�ӷ��ظ��ַ���
		VString& PadLeft(int totalWidth,WCHAR wc=' ');
		//���ұ߲���һ��������wc��ʹ�ַ�������룬
		VString& PadRight(int totalWidth,WCHAR wc=' ');
		//��startIndex���Ƴ�һ�����ȵ����ݣ����صõ������ַ�����lengthС��0���ʾ�Ƴ��������е��ַ�����startIndex<0��startIndex+length>Length���׳��쳣
		VString& Remove(int startIndex,int length=-1);
		//����һ�����ַ���������Ϊԭ�ַ����е�wc1ȫ�滻Ϊwc2,��ָ���Ƚ�ʱ�Ƿ���Դ�Сд
		VString& Replace(WCHAR wc1,WCHAR wc2,bool ignoreCase=false);
		//����һ�����ַ���������Ϊԭ�ַ����е�xString1ȫ�滻ΪxString2����ָ���Ƚ�ʱ�Ƿ���Դ�Сд
		VString& Replace(const VString& xString1 ,const VString& xString2,bool ignoreCase=false);
		//����һ�����ַ��������ַ���Ϊ�����е�Сд��ĸ����ɴ�д
		VString& ToUpper();
		//����һ�����ַ��������ַ���Ϊ�����еĴ�д��ĸ�����Сд
		VString& ToLower();
		//��ȡ�ַ����е�Ӣ�ĵ��ʣ����ֲ��㣬���硰G2 VS2010���õ�����G����VS����
		XArray<VString> GetWords()const;
		//��ȡ�ַ����е����֣����硰G2 VS2010���õ�����2010��
		XArray<VString> GetNumbers()const;
		//��ȡ�ַ����е�Ӣ�ĺ����֣�Ӣ�ĺ����ֿ�����һ�𣬱��硰G2 VS2010���õ�����G2������VS2010����
		XArray<VString> GetWordsAndNumbers()const;
		//���ظ��ַ����Ŀ��ֽ������ʾ����������β�ַ�'\0'����startIndex<0��startIndex+length>Length���׳��쳣
		XArray<WCHAR> ToWCharArray( int startIndex=0,int length=-1)const;
		//����ʹ��ָ���ַ����ָ����ָ��γɵ��ַ�������,��ָ���������(-1��ʾ������)
		XArray<VString> Split(WCHAR ch, int maxCount)const;
		//����ʹ��ָ���ַ����ָ����ָ��γɵ��ַ�������
		XArray<VString> Split(WCHAR ch = L' ')const;
		//����ʹ��ָ���ַ������ָ����ָ��γɵ��ַ�������,��ָ���������(-1��ʾ������)
		XArray<VString> Split(const VString& str,int maxCount=MaxValues::Int)const;
		//����ʹ��ָ���ַ������г��ֵ��ַ����ָ����ָ��γɵ��ַ�������,��ָ���������(-1��ʾ������),��ָ���Ƿ��Ƴ����ַ���
		XArray<VString> Split(const XArray<WCHAR> chs,int maxCount,bool removeEmpty)const;
		//����ʹ��ָ���ַ������ָ����ָ��γɵ��ַ�������,��ָ���������(-1��ʾ������),��ָ���Ƿ��Ƴ����ַ���
		XArray<VString> Split(const XArray<VString> strs,int maxCount,bool removeEmpty)const;
		//����ʹ��ָ���ַ������г��ֵ��ַ����ָ����ָ��γɵ��ַ�������,��ָ���������(-1��ʾ������)
		XArray<VString> Split(const XArray<WCHAR> chs,int maxCount=MaxValues::Int)const;
		//����ʹ��ָ���ַ������ָ����ָ��γɵ��ַ�������,��ָ���������(-1��ʾ������)
		XArray<VString> Split(const XArray<VString> strs,int maxCount=MaxValues::Int)const;
		//����һ��ֵ��ָʹ���ַ����Ƿ�Ϊ�գ�""��
		bool IsEmpty()const{return Length==0;}

		//����ָ�� Unicode �ַ��ڴ��ַ����еĵ�һ��ƥ����������� 
		int IndexOf(WCHAR wc)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��startIndex<0��>Length���׳��쳣
		int IndexOf(WCHAR wc,int startIndex,bool ignoreCase=false)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��length<0��ʾ����ȫ����startIndex<0��startIndex+length>Length���׳��쳣
		int IndexOf(WCHAR wc,int startIndex,int length,bool ignoreCase)const;
		//����ָ�� �ַ����ڴ��ַ����еĵ�һ��ƥ����������� 
		int IndexOf(const VString& xString)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��startIndex<0��>Length���׳��쳣
		int IndexOf(const VString& xString,int startIndex,bool ignoreCase=false)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��length<0��ʾ����ȫ����startIndex<0��startIndex+length>Length���׳��쳣
		int IndexOf(const VString& xString,int startIndex,int length,bool ignoreCase)const;
		//Ѱ��wArray�����������ַ��ڴ��ַ����״γ��ֵ�λ�ã���������β�ַ�����length<0��ʾ����ȫ����startIndex<0��startIndex+length>Length���׳��쳣
		int IndexOfAny(const XArray<wchar_t> wArray,int startIndex,int length)const;
		//Ѱ��wArray�����������ַ��ڴ��ַ����״γ��ֵ�λ�ã���������β�ַ�����startIndex<0��startIndex+length>Length���׳��쳣
		int IndexOfAny(const XArray<wchar_t> wArray,int startIndex=0)const;

		//����ָ�� Unicode �ַ��ڴ��ַ����е����һ��ƥ������������Ҳ�������-1
		int LastIndexOf(WCHAR wc)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��startIndex<0��>Length���׳��쳣
		int LastIndexOf(WCHAR wc,int startIndex,bool ignoreCase=false)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��length<0��ʾ����ȫ����startIndex<0��startIndex+length>Length���׳��쳣
		int LastIndexOf(WCHAR wc,int startIndex,int length,bool ignoreCase)const;
		//����ָ�� �ַ����ڴ��ַ����е����һ��ƥ����������� 
		int LastIndexOf(const VString& xString)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��startIndex<0��>Length���׳��쳣
		int LastIndexOf(const VString& xString,int startIndex,bool ignoreCase=false)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��length<0��ʾ����ȫ����startIndex<0��startIndex+length>Length���׳��쳣
		int LastIndexOf(const VString& xString,int startIndex,int length,bool ignoreCase)const;
		//Ѱ��wArray�����������ַ��ڴ��ַ��������ֵ�λ�ã���������β�ַ�����length<0��ʾ����ȫ����startIndex<0��>Length���׳��쳣
		int LastIndexOfAny(const XArray<wchar_t> wArray,int startIndex,int length)const;
		//Ѱ��wArray�����������ַ��ڴ��ַ��������ֵ�λ�ã���������β�ַ�����startIndex<0��startIndex+length>Length���׳��쳣
		int LastIndexOfAny(const XArray<wchar_t> wArray,int startIndex=0)const;
		//����10��i�η�
		static double IntPow10(int i);
		//��pת��Ϊһ������double
		static double ToIntDouble(LPWSTR p);
		//����ʶ���ĸ�������
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
#ifdef _CLR //�й�֧��
		//������count���ַ�string���Ӷ��ɵ��ַ���
		VString(volatile const System::String^string, int count=1);
		//���嵽�й��ַ�����ת��
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
	



	//��Ԫ��������
	XString operator+(const XString& xString1,const XString& xString2);
	XString operator+(const XString& xString,const XBase& xBase);
	XString operator+(const XBase& xBase,const XString& xString);
	XString operator+(const XString& xString1,LPCWSTR xString2);
	XString operator+(LPCWSTR xString1,const XString& xString2);
	XString operator+(const XString& xString1,LPCSTR xString2);
	XString operator+(LPCSTR xString1,const XString& xString2);
	bool operator==(const XString& xString1,const XString& xString2);//�ַ����Ƚ�
	bool operator==(const XString& xString1,LPCWSTR xString2);//�ַ����Ƚ�
	bool operator==(LPCWSTR xString1,const XString& xString2);//�ַ����Ƚ�
	bool operator==(const XString& xString1,LPCSTR xString2);//�ַ����Ƚ�
	bool operator==(LPCSTR xString1,const XString& xString2);//�ַ����Ƚ�
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
#ifdef _CLR //�й�֧��
//	XString operator+(System::String^ string,const XString& xString);
//	XString operator+(const XString& xString,System::String^ string);
//	XString operator+(System::Object^ obj,const XString& xString);
//	XString operator+(const XString& xString,System::Object^ obj);
#endif
//debugģʽ�¸ı�XString��ָ��Ŀ���ַ�����ָ�룬�������
#ifdef _DEBUG
#define XSTRINGCITEDCHANGE(pString)\
	pString = static_cast<VString*>(pObject)
#else
	#define XSTRINGCITEDCHANGE(pString)
#endif
	//�ַ������ͣ�������
	class XString:public XBase
	{
		friend VString;
#ifdef _DEBUG
		//debugģʽ��ָ��Ŀ���ַ��������ݣ��������
		VString* pString;
#endif
	public:
		PROPERTY_OFFSET(XString,Length);
		//Ĭ�Ϲ��캯��
		XString(){}
		//���ƹ��캯��
		XString(const XString&x);
		//��ָ�빹��
		XString(VString*p);
		//������������
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
		//����һ�����ַ���""
		const static XString Empty;
		


		//�Ƚ������ַ����Ĵ�С��ָ���Ƿ���Դ�Сд
		static int Compare(const XString xString1,const XString xString2,bool ignoreCase=false);
		//�Ƚ��������ַ����Ĵ�С��ָ���Ƿ���Դ�Сд
		static int Compare(const XString xString1,int index1,const XString xString2,int index2,int length,bool ignoreCase=false);
		//��������������ַ�����ʾ
		static XString Concat(const XBase& object1,const XBase& object2);
		//��������������ַ�����ʾ
		static XString Concat(const XBase& object1,const XBase& object2,const XBase& object3);
		//�����ĸ�������ַ�����ʾ
		static XString Concat(const XBase& object1,const XBase& object2,const XBase& object3,const XBase& object4);
		//�����ַ�������
		static XString Concat(const XArray<XString> strings);
		//���������еĶ���ָ��ָ�������ַ�����ʾ
		static XString Concat(const XArray<XBase*> strings);
		//�ڼ����ַ�������������ַ����Դ��ӳ��µ��ַ���
		static XString Join(const XString str,const XArray<XString> strs,int startIndex=0,int count=-1);

		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit XString(float number,LPCWSTR format=L"%g");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit XString(double number,LPCWSTR format=L"%g");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit XString(unsigned long long number,LPCWSTR format=L"%d");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit XString(unsigned long number,LPCWSTR format=L"%d");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit XString(unsigned int number,LPCWSTR format=L"%d");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit XString(long long number,LPCWSTR format=L"%d");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit XString(long number,LPCWSTR format=L"%d");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit XString(int number,LPCWSTR format=L"%d");
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit XString(unsigned short number,LPCWSTR format);
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit XString(short number,LPCWSTR format);
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit XString(unsigned char number,LPCWSTR format);
		//�����ִ����ַ�����formatʹ���ַ���ָ����ʽ
		explicit XString(signed char number,LPCWSTR format);
		//������count���ַ�c���Ӷ��ɵ��ַ���
		XString(CHAR c,int count =1);
		//������count�����ֽ��ַ�wc���Ӷ��ɵ��ַ���
		XString(WCHAR wc,int count =1);
		//������count��wString�ַ������Ӷ��ɵ��ַ���
		XString(LPCWSTR wString,int count =1);
		//������count��mString�ַ������Ӷ��ɵ��ַ���
		XString(LPCSTR mString,int count =1);
		//������count��wString�ַ������Ӷ��ɵ��ַ���
		XString(const XArray<WCHAR> wString,int count =1);
		//������count��mString�ַ������Ӷ��ɵ��ַ���
		XString(const XArray<CHAR> mString,int count =1);
		//������wString�ַ���startindex�ַ�����length���ַ����ַ��������length<=-2�����ʾ��'\0'��ʾ�Ľ�β
		XString(LPCWSTR wString,int startIndex,int length);
		//������mString�ַ���startindex�ַ�����length���ַ����ַ��������length<=-2�����ʾ��'\0'��ʾ�Ľ�β
		XString(LPCSTR mString,int startIndex,int length);
		//��count��VString����
		XString(const VString& ,int count);
		//������count��XString�ַ������Ӷ��ɵ��ַ���
		XString(const XString xString, int count);
		//����������XString���Ӷ��ɵ��ַ���
		XString(const XString xString1,const XString xString2);
		//����������XString���Ӷ��ɵ��ַ���
		XString(const XString xString1,const XString xString2,const  XString xString3);
		//�������ĸ�XString���Ӷ��ɵ��ַ���
		XString(const XString xString1,const XString xString2,const  XString xString3,const  XString xString4);
		//������xStrings���鴮�Ӷ��ɵ��ַ���
		XString(const XArray<XString>xStrings);
		//����
		WCHAR operator[](int index)const;
		//������
		Iterator<const WCHAR> First()const;
		//������
		Iterator<const WCHAR> begin()const;
		//������
		Iterator<const WCHAR> Last()const;
		//������
		Iterator<const WCHAR> End()const;
		//������
		Iterator<const WCHAR> end()const;
		//����
		int GetLength()const;
		//ֻ�����ԣ��ַ�������
		PROPERTY_GET(int,XString,GetLength,Length);

		//���һ������
		virtual XString ToString()const;
		//ת����ԭʼ�Ķ��ֽ��ַ�����const��
		LPCSTR ToAnsi()const;
		//������ֽ��ַ�����const��
		LPCWSTR ToUnicode()const;
		//ת��Ϊһ��unsigned long long
		unsigned long long ToUInt64()const;
		//ת��Ϊһ��long long
		long long ToInt64()const;
		//ת��Ϊһ��double
		double ToDouble()const;
		//ת��Ϊһ��unsigned long long��ʹ�ú���֧��
		unsigned long long ChsToUInt64()const;
		//ת��Ϊһ��long long��ʹ�ú���֧��
		long long ChsToInt64()const;
		operator LPCSTR()const;
		operator LPCWSTR()const;

		XString& operator=(const XString& xString);//��ֵ����
		XString& operator=(LPCSTR mString);
		XString& operator=(LPCWSTR wString);
		XString& operator+=(const XString& xString);//��������
		XString& operator+=(const XBase& xBase);
		friend bool operator==(const XString& xString1,const XString& xString2);//�ַ����Ƚ�
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
		//��object���ַ�����ʾ�Ƚ�
		int CompareTo(const XBase& object)const;
		//��string�ַ�����ʾ�Ƚ�
		int CompareTo(const XString& string)const;
		//���Ƶ����ֽ����飬���ظ��Ƶ��ֽ���,lengthOfByte<0���Զ��ж��ֽ�����sourceByteIndex<0��destinationByteIndex<0���׳��쳣
		int CopyTo(XArray<char> destination,int sourceByteIndex=0,int destinationByteIndex=0,int lengthOfByte=-1)const;
		//���Ƶ����ֽ����飬���ظ��Ƶ��ַ���,length<0���Զ��ж��ֽ�����sourceIndex<0��destinationIndex<0���׳��쳣
		int CopyTo(XArray<wchar_t> destination,int sourceIndex=0,int destinationIndex=0,int length=-1)const;
		//�жϸ��ַ����Ƿ����xString
		bool Contains(const XString& xString)const;
		//��ȡ���ַ������ַ�wch���ֵĴ���
		int CountOf(WCHAR wch)const;
		//��ȡ���ַ������ַ���str���ֵĴ���
		int CountOf(const XString& str)const;
		//�жϸ��ַ����Ƿ���xString��β
		bool EndsWith(const XString& xString)const;
		//�жϸ��ַ����Ƿ���xString��ͷ
		bool StartsWith(const XString& xString)const;
		//��object���ַ�����ʾ�Ƚϣ����Ƿ����
		virtual bool Equals(const XBase& object)const;
		//��ָ���ַ����Ƚϣ����Ƿ����
		virtual bool Equals(const XString&)const;
		//����һ�����ַ�������length<0ʱ��������β�����ַ��� ��startIndex<0��startIndex+length>Length���׳��쳣
		XString Substring(int startIndex, int length=-2)const;
		//����һ�����ַ�������length<0ʱ��������β�����ַ��� ,��Substring������ͬ���������з����Զ����ء������length��ʾ�ֽڳ��ȣ�����Ϊ�˱�֤�ַ��������ԣ����ص��ַ������ֽڳ����п���С��ָ����length��,startIndex<0��startIndex>Length���׳��쳣
		XString Cut(int startIndex, int length=-2)const;
		//������startIndexλ�ò���xString�����ַ��������ַ������䣬startIndex<0���׳��쳣
		XString Insert(int startIndex,const XString& xString)const;
		//����߲���һ��������wc��ʹ�ַ����Ҷ��룬����һ����totalWidth���ַ����ַ��������ַ������䣬���ԭ�ַ����ĳ��ȴ���totalWidth����ֱ�ӷ��ظ��ַ���
		XString PadLeft(int totalWidth,WCHAR wc=' ')const;
		//���ұ߲���һ��������wc��ʹ�ַ�������룬
		XString PadRight(int totalWidth,WCHAR wc=' ')const;
		//��startIndex���Ƴ�һ�����ȵ����ݣ����صõ������ַ�����lengthС��0���ʾ�Ƴ��������е��ַ�����startIndex<0��startIndex+length>Length���׳��쳣
		XString Remove(int startIndex,int length=-1)const;
		//����һ�����ַ���������Ϊԭ�ַ����е�wc1ȫ�滻Ϊwc2,��ָ���Ƚ�ʱ�Ƿ���Դ�Сд
		XString Replace(WCHAR wc1,WCHAR wc2,bool ignoreCase=false)const;
		//����һ�����ַ���������Ϊԭ�ַ����е�xString1ȫ�滻ΪxString2����ָ���Ƚ�ʱ�Ƿ���Դ�Сд
		XString Replace(const XString& xString1 ,const XString& xString2,bool ignoreCase=false)const;
		//����һ�����ַ��������ַ���Ϊ�����е�Сд��ĸ����ɴ�д
		XString ToUpper()const;
		//����һ�����ַ��������ַ���Ϊ�����еĴ�д��ĸ�����Сд
		XString ToLower()const;
		//��ȡ�ַ����е�Ӣ�ĵ��ʣ����ֲ��㣬���硰G2 VS2010���õ�����G����VS����
		XArray<XString> GetWords()const;
		//��ȡ�ַ����е����֣����硰G2 VS2010���õ�����2010��
		XArray<XString> GetNumbers()const;
		//��ȡ�ַ����е�Ӣ�ĺ����֣�Ӣ�ĺ����ֿ�����һ�𣬱��硰G2 VS2010���õ�����G2������VS2010����
		XArray<XString> GetWordsAndNumbers()const;
		//���ظ��ַ����Ŀ��ֽ������ʾ����������β�ַ�'\0'����startIndex<0��startIndex+length>Length���׳��쳣
		XArray<WCHAR> ToWCharArray( int startIndex=0,int length=-1)const;
		//����ʹ��ָ���ַ����ָ����ָ��γɵ��ַ�������,��ָ���������
		XArray<XString> Split(WCHAR ch, int maxCount)const;
		//����ʹ��ָ���ַ����ָ����ָ��γɵ��ַ�������
		XArray<XString> Split(WCHAR ch = L' ')const;
		//����ʹ��ָ���ַ������ָ����ָ��γɵ��ַ�������,��ָ���������
		XArray<XString> Split(const XString& str,int maxCount=MaxValues::Int)const;
		//����ʹ��ָ���ַ����ָ����ָ��γɵ��ַ�������,��ָ���������,�Ƿ��Ƴ����ַ���
		XArray<XString> Split(WCHAR ch, int maxCount,bool removeEmpty)const;
		//����ʹ��ָ���ַ������ָ����ָ��γɵ��ַ�������,��ָ���������,�Ƿ��Ƴ����ַ���
		XArray<XString> Split(const XString& str,int maxCount,bool removeEmpty)const;
		//����ʹ��ָ���ַ������г��ֵ��ַ����ָ����ָ��γɵ��ַ�������,��ָ���������,��ָ���Ƿ��Ƴ����ַ���
		XArray<XString> Split(const XArray<WCHAR> chs,int maxCount,bool removeEmpty)const;
		//����ʹ��ָ���ַ������ָ����ָ��γɵ��ַ�������,��ָ���������,��ָ���Ƿ��Ƴ����ַ���
		XArray<XString> Split(const XArray<XString> strs,int maxCount,bool removeEmpty)const;
		//����ʹ��ָ���ַ������г��ֵ��ַ����ָ����ָ��γɵ��ַ�������,��ָ���������
		XArray<XString> Split(const XArray<WCHAR> chs,int maxCount=MaxValues::Int)const;
		//����ʹ��ָ���ַ������ָ����ָ��γɵ��ַ�������,��ָ���������
		XArray<XString> Split(const XArray<XString> strs,int maxCount=MaxValues::Int)const;
		//����һ��ֵ��ָʹ���ַ����Ƿ�Ϊ�գ�����NULL��""��
		bool IsNullOrEmpty()const;

		//����ָ�� Unicode �ַ��ڴ��ַ����еĵ�һ��ƥ����������� 
		int IndexOf(WCHAR wc)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��startIndex<0��>Length���׳��쳣
		int IndexOf(WCHAR wc,int startIndex,bool ignoreCase=false)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��length<0��ʾ����ȫ����startIndex<0��startIndex+length>Length���׳��쳣
		int IndexOf(WCHAR wc,int startIndex,int length,bool ignoreCase)const;
		//����ָ�� �ַ����ڴ��ַ����еĵ�һ��ƥ����������� 
		int IndexOf(const XString& xString)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��startIndex<0��>Length���׳��쳣
		int IndexOf(const XString& xString,int startIndex,bool ignoreCase=false)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��length<0��ʾ����ȫ����startIndex<0��startIndex+length>Length���׳��쳣
		int IndexOf(const XString& xString,int startIndex,int length,bool ignoreCase)const;
		//Ѱ��wArray�����������ַ��ڴ��ַ����״γ��ֵ�λ�ã���������β�ַ�����length<0��ʾ����ȫ����startIndex<0��startIndex+length>Length���׳��쳣
		int IndexOfAny(const XArray<wchar_t> wArray,int startIndex,int length)const;
		//Ѱ��wArray�����������ַ��ڴ��ַ����״γ��ֵ�λ�ã���������β�ַ�����startIndex<0��startIndex+length>Length���׳��쳣
		int IndexOfAny(const XArray<wchar_t> wArray,int startIndex=0)const;

		//����ָ�� Unicode �ַ��ڴ��ַ����е����һ��ƥ������������Ҳ�������-1
		int LastIndexOf(WCHAR wc)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��startIndex<0��>Length���׳��쳣
		int LastIndexOf(WCHAR wc,int startIndex,bool ignoreCase=false)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��length<0��ʾ����ȫ����startIndex<0��startIndex+length>Length���׳��쳣
		int LastIndexOf(WCHAR wc,int startIndex,int length,bool ignoreCase)const;
		//����ָ�� �ַ����ڴ��ַ����е����һ��ƥ����������� 
		int LastIndexOf(const XString xString)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��startIndex<0��>Length���׳��쳣
		int LastIndexOf(const XString xString,int startIndex,bool ignoreCase=false)const;
		//ָ����ʼλ�ò�ָ���Ƿ���Դ�Сд��length<0��ʾ����ȫ����startIndex<0��startIndex+length>Length���׳��쳣
		int LastIndexOf(const XString xString,int startIndex,int length,bool ignoreCase)const;
		//Ѱ��wArray�����������ַ��ڴ��ַ��������ֵ�λ�ã���������β�ַ�����startIndex<0��>Length���׳��쳣
		int LastIndexOfAny(const XArray<wchar_t> wArray,int startIndex,int length)const;
		//Ѱ��wArray�����������ַ��ڴ��ַ��������ֵ�λ�ã���������β�ַ�����startIndex<0��startIndex+length>Length���׳��쳣
		int LastIndexOfAny(const XArray<wchar_t> wArray,int startIndex=0)const;

#ifdef _CLR //�й�֧��
		//������count���ַ�string���Ӷ��ɵ��ַ���
		XString(volatile const System::String^string, int count=1);
		//���嵽�й��ַ�����ת��
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