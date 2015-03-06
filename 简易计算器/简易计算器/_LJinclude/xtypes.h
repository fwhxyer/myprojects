#pragma once
#define XTYPES_
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
#include "typeinfo.h"
namespace LJ
{
#ifdef _CLR
	//�й����ͱ��
	template<class T>struct GcType
	{
		typedef typename T Type;
		static const type_info* GetId(){return &typeid(T);}
	};
	template<class T>struct GcType<T^>
	{
		typedef typename T Type;
		static const type_info* GetId(){return &typeid(GcType<T^>);}
	};
	template<class T>struct GcType<T^%>
	{
		typedef typename T Type;
		static const type_info* GetId(){return &typeid(GcType<T^%>);}
	};
#endif
	struct TypesCheckingObject
	{

		TypesCheckingObject(const TypesCheckingObject& t)
			:count(t.count),pTypes(t.count?(type_info**)Malloc(t.count*sizeof(type_info*)):NULL),pCR(t.count?(char*)Malloc(t.count):NULL)
		{
			Memory::Copy(pTypes,t.pTypes,sizeof(type_info*)*t.count);
			Memory::Copy(pCR,t.pCR,t.count);
		}
#ifdef _USE_RIGHT_VALUE_REFERENCE
		TypesCheckingObject(const TypesCheckingObject&& t)
			:count(t.count),pTypes(t.pTypes),pCR(t.pCR){const_cast<const type_info**&>(t.pTypes) = NULL;const_cast<int&>(t.count)=0;const_cast<char*&>(t.pCR)=NULL;}
#endif
		TypesCheckingObject():count(0),pTypes(NULL),pCR(NULL){}
		TypesCheckingObject(type_info** p,char* pcr,int c):count(c),pTypes(p),pCR(pcr){}
		XString ToString()const;
		static void* Malloc(int c);
		bool AppEquals(const TypesCheckingObject& t);
		template<class T> inline type_info* MakeInfo(int i)
		{
			pCR[i]=Types<T>::isConst;
			pCR[i]+=Types<T>::isReference*2;
#ifdef _CLR
			return (type_info*)GcType<T>::GetId();
#else
			return (type_info*)&typeid(T);
#endif
		}
		const type_info& operator[](int index)const;
		template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9,class TA,class TB>static TypesCheckingObject MakeObject(int c)
		{
			TypesCheckingObject t((type_info**)Malloc(11*sizeof(type_info*)),(char*)Malloc(11),c>11||c<0?11:c);
			t.pTypes[0] = t.MakeInfo<T1>(0);t.pTypes[1] = t.MakeInfo<T2>(1);t.pTypes[2] = t.MakeInfo<T3>(2);t.pTypes[3] = t.MakeInfo<T4>(3);t.pTypes[4] = t.MakeInfo<T5>(4);t.pTypes[5] = t.MakeInfo<T6>(5);t.pTypes[6] = t.MakeInfo<T7>(6);t.pTypes[7] = t.MakeInfo<T8>(7);t.pTypes[8] = t.MakeInfo<T9>(8);t.pTypes[9] = t.MakeInfo<TA>(9);t.pTypes[10] = t.MakeInfo<TB>(10);
			return t;
		}
		template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9,class TA>static TypesCheckingObject MakeObject(int c)
		{
			TypesCheckingObject t((type_info**)Malloc(10*sizeof(type_info*)),(char*)Malloc(10),c>10||c<0?10:c);
			t.pTypes[0] = t.MakeInfo<T1>(0);t.pTypes[1] = t.MakeInfo<T2>(1);t.pTypes[2] = t.MakeInfo<T3>(2);t.pTypes[3] = t.MakeInfo<T4>(3);t.pTypes[4] = t.MakeInfo<T5>(4);t.pTypes[5] = t.MakeInfo<T6>(5);t.pTypes[6] = t.MakeInfo<T7>(6);t.pTypes[7] = t.MakeInfo<T8>(7);t.pTypes[8] = t.MakeInfo<T9>(8);t.pTypes[9] = t.MakeInfo<TA>(9);
			return t;
		}
		template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>static TypesCheckingObject MakeObject(int c)
		{
			TypesCheckingObject t((type_info**)Malloc(9*sizeof(type_info*)),(char*)Malloc(9),c>9||c<0?9:c);
			t.pTypes[0] = t.MakeInfo<T1>(0);t.pTypes[1] = t.MakeInfo<T2>(1);t.pTypes[2] = t.MakeInfo<T3>(2);t.pTypes[3] = t.MakeInfo<T4>(3);t.pTypes[4] = t.MakeInfo<T5>(4);t.pTypes[5] = t.MakeInfo<T6>(5);t.pTypes[6] = t.MakeInfo<T7>(6);t.pTypes[7] = t.MakeInfo<T8>(7);t.pTypes[8] = t.MakeInfo<T9>(8);
			return t;
		}
		template<class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>static TypesCheckingObject MakeObject(int c)
		{
			TypesCheckingObject t((type_info**)Malloc(8*sizeof(type_info*)),(char*)Malloc(8),c>8||c<0?8:c);
			t.pTypes[0] = t.MakeInfo<T1>(0);t.pTypes[1] = t.MakeInfo<T2>(1);t.pTypes[2] = t.MakeInfo<T3>(2);t.pTypes[3] = t.MakeInfo<T4>(3);t.pTypes[4] = t.MakeInfo<T5>(4);t.pTypes[5] = t.MakeInfo<T6>(5);t.pTypes[6] = t.MakeInfo<T7>(6);t.pTypes[7] = t.MakeInfo<T8>(7);
			return t;
		}
		template<class T1,class T2,class T3,class T4,class T5,class T6,class T7>static TypesCheckingObject MakeObject(int c)
		{
			TypesCheckingObject t((type_info**)Malloc(7*sizeof(type_info*)),(char*)Malloc(7),c>7||c<0?7:c);
			t.pTypes[0] = t.MakeInfo<T1>(0);t.pTypes[1] = t.MakeInfo<T2>(1);t.pTypes[2] = t.MakeInfo<T3>(2);t.pTypes[3] = t.MakeInfo<T4>(3);t.pTypes[4] = t.MakeInfo<T5>(4);t.pTypes[5] = t.MakeInfo<T6>(5);t.pTypes[6] = t.MakeInfo<T7>(6);
			return t;
		}
		template<class T1,class T2,class T3,class T4,class T5,class T6>static TypesCheckingObject MakeObject(int c)
		{
			TypesCheckingObject t((type_info**)Malloc(6*sizeof(type_info*)),(char*)Malloc(6),c>6||c<0?6:c);
			t.pTypes[0] = t.MakeInfo<T1>(0);t.pTypes[1] = t.MakeInfo<T2>(1);t.pTypes[2] = t.MakeInfo<T3>(2);t.pTypes[3] = t.MakeInfo<T4>(3);t.pTypes[4] = t.MakeInfo<T5>(4);t.pTypes[5] = t.MakeInfo<T6>(5);
			return t;
		}
		template<class T1,class T2,class T3,class T4,class T5>static TypesCheckingObject MakeObject(int c)
		{
			TypesCheckingObject t((type_info**)Malloc(5*sizeof(type_info*)),(char*)Malloc(5),c>5||c<0?5:c);
			t.pTypes[0] = t.MakeInfo<T1>(0);t.pTypes[1] = t.MakeInfo<T2>(1);t.pTypes[2] = t.MakeInfo<T3>(2);t.pTypes[3] = t.MakeInfo<T4>(3);t.pTypes[4] = t.MakeInfo<T5>(4);
			return t;
		}
		template<class T1,class T2,class T3,class T4>static TypesCheckingObject MakeObject(int c)
		{
			TypesCheckingObject t((type_info**)Malloc(4*sizeof(type_info*)),(char*)Malloc(4),c>4||c<0?4:c);
			t.pTypes[0] = t.MakeInfo<T1>(0);t.pTypes[1] = t.MakeInfo<T2>(1);t.pTypes[2] = t.MakeInfo<T3>(2);t.pTypes[3] = t.MakeInfo<T4>(3);
			return t;
		}
		template<class T1,class T2,class T3>static TypesCheckingObject MakeObject(int c)
		{
			TypesCheckingObject t((type_info**)Malloc(3*sizeof(type_info*)),(char*)Malloc(3),c>3||c<0?3:c);
			t.pTypes[0] = t.MakeInfo<T1>(0);t.pTypes[1] = t.MakeInfo<T2>(1);t.pTypes[2] = t.MakeInfo<T3>(2);
			return t;
		}
		template<class T1,class T2>static TypesCheckingObject MakeObject(int c)
		{
			TypesCheckingObject t((type_info**)Malloc(2*sizeof(type_info*)),(char*)Malloc(2),c>2||c<0?2:c);
			t.pTypes[0] = t.MakeInfo<T1>(0);t.pTypes[1] = t.MakeInfo<T2>(1);
			return t;
		}
		template<class T1>static TypesCheckingObject MakeObject(int c)
		{
			TypesCheckingObject t((type_info**)Malloc(1*sizeof(type_info*)),(char*)Malloc(1),c>1||c<0?1:c);
			t.pTypes[0] = t.MakeInfo<T1>(0);
			return t;
		}
		~TypesCheckingObject(){free(pTypes);free(pCR);}
		int count;
		type_info** pTypes;
		char* pCR;
		TypesCheckingObject& operator=(const TypesCheckingObject& t)
		{
			free(pTypes);
			free(pCR);
			count=t.count;
			pTypes=t.count?(type_info**)Malloc(t.count*sizeof(type_info*)):NULL;
			pCR=t.count?(char*)Malloc(t.count):NULL;
			Memory::Copy(pTypes,t.pTypes,sizeof(type_info*)*t.count);
			Memory::Copy(pCR,t.pCR,t.count);
			return *this;
		}
#ifdef _USE_RIGHT_VALUE_REFERENCE
		TypesCheckingObject& operator=(const TypesCheckingObject&& t)
		{
			free(pTypes);
			free(pCR);
			count=t.count;pTypes=t.pTypes;pCR=t.pCR;
			const_cast<const type_info**&>(t.pTypes) = NULL;
			const_cast<const char*&>(t.pCR) = NULL;
			const_cast<int&>(t.count)=0;
			return *this;
		}
#endif
		bool operator==(const TypesCheckingObject& t)const{return count==t.count&&(0==count || (memcmp(pTypes,t.pTypes,sizeof(const type_info*)*count)==0 && memcmp(pCR,t.pCR,count)==0));}
		bool operator!=(const TypesCheckingObject& t)const{return count!=t.count || (0!=count && (memcmp(pTypes,t.pTypes,sizeof(const type_info*)*count)!=0 || memcmp(pCR,t.pCR,count)!=0));}
		//���Ҳ�ͬ,��i��ʼ
		int FindDifferenceWith(const TypesCheckingObject&t,int i=0)const{while(i<count&&i<t.count){if(pTypes[i]!=t.pTypes[i] || pCR[i]!=t.pCR[i])break;++i;}return (i<count||i<t.count)?i:-1;}
		//���Ҳ�ͬ,��i��ʼ
		int AppFindDifferenceWith(const TypesCheckingObject&t,int i=0)const{while(i<count&&i<t.count){if(pTypes[i]!=t.pTypes[i])break;++i;}return (i<count||i<t.count)?i:-1;}
	};
	//�����1������T���2������TTͬ����,��Result��ʾ��3������T1�������ʾ��4������T2
	template<class T,class TT,class T1,class T2> struct IfTypesEqual{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypesEqual<T,T,T1,T2>{typedef typename T1 Result;};
	//�����1������T��ָ����Result��ʾ��ʾ��2������T1�������ʾ��3������T2
	template<class T,class T1,class T2> struct IfTypeIsPointer{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypeIsPointer<T*,T1,T2>{typedef typename T1 Result;};
	//�����1������T��const��Result��ʾ��ʾ��2������T1�������ʾ��3������T2
	template<class T,class T1,class T2> struct IfTypeIsConst{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypeIsConst<T const,T1,T2>{typedef typename T1 Result;};
	template<class T,class T1,class T2> struct IfTypeIsConst<T &,T1,T2>{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypeIsConst<T const&,T1,T2>{typedef typename T1 Result;};
	//�����1������T��������Result��ʾ��ʾ��2������T1�������ʾ��3������T2
	template<class T,class T1,class T2> struct IfTypeIsReference{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypeIsReference<T const,T1,T2>{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypeIsReference<T &,T1,T2>{typedef typename T1 Result;};
	template<class T,class T1,class T2> struct IfTypeIsReference<T const&,T1,T2>{typedef typename T1 Result;};
#ifdef _CLR
	template<class T,class T1,class T2> struct IfTypeIsReference<T^%,T1,T2>{typedef typename T1 Result;};
#endif
	//���������Ƿ���ͬ
	template<class T1,class T2>struct TypesEqual{static enum:signed char{isEqual=false}; inline operator bool(){return false;}};
	template<class T>struct TypesEqual<T,T>{static enum:signed char{isEqual=true}; inline operator bool(){return true;}};
	//�����1������T�ǻ�������������Result��ʾ��ʾ��2������T1�������ʾ��3������T2
	template<class T,class T1,class T2> struct IfTypeIsBaseDataType{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypeIsBaseDataType<T*,T1,T2>{typedef typename T1 Result;};
	//�����1������T���йܾ����Result��ʾ��ʾ��2������T1�������ʾ��3������T2
	template<class T,class T1,class T2> struct IfTypeIsGcHandle{typedef typename T2 Result;};
#ifdef _CLR
	template<class T,class T1,class T2> struct IfTypeIsGcHandle<T^,T1,T2>{typedef typename T1 Result;};
	template<class T,class T1,class T2> struct IfTypeIsGcHandle<T^%,T1,T2>{typedef typename T1 Result;};
	//�йܾ���㵽��������������
	template<class T,class T1,class T2> struct IfTypeIsBaseDataType<T^,T1,T2>{typedef typename T1 Result;};
	template<class T,class T1,class T2> struct IfTypeIsBaseDataType<T^%,T1,T2>{typedef typename T1 Result;};
#endif
	template<class T1,class T2> struct IfTypeIsBaseDataType<int,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<unsigned int,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<long,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<unsigned long,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<short,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<unsigned short,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<char,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<signed char,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<unsigned char,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<long long,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<unsigned long long,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<double,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<long double,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<float,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<wchar_t,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<void,T1,T2>{typedef typename T1 Result;};
	template<class T,class T1,class T2> struct IfTypeIsBaseDataType<T*&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<int&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<unsigned int&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<long&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<unsigned long&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<short&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<unsigned short&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<char&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<signed char&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<unsigned char&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<long long&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<unsigned long long&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<double&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<long double&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<float&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<wchar_t&,T1,T2>{typedef typename T1 Result;};
	template<class T,class T1,class T2> struct IfTypeIsBaseDataType<T*const,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const int,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const unsigned int,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const long,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const unsigned long,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const short,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const unsigned short,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const char,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const signed char,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const unsigned char,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const long long,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const unsigned long long,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const double,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const long double,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const float,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const wchar_t,T1,T2>{typedef typename T1 Result;};
	template<class T,class T1,class T2> struct IfTypeIsBaseDataType<T*const&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const int&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const unsigned int&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const long&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const unsigned long&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const short&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const unsigned short&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const char&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const signed char&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const unsigned char&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const long long&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const unsigned long long&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const double&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const long double&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const float&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const wchar_t&,T1,T2>{typedef typename T1 Result;};
	template<class T1,class T2> struct IfTypeIsBaseDataType<const void,T1,T2>{typedef typename T1 Result;};
#if _MSC_VER >=1600
	template<class T1,class T2> struct IfTypeIsBaseDataType<std::nullptr_t,T1,T2>{typedef typename T1 Result;};
#endif
	//���������ӿ�
	struct ITypes
	{
		ITypes(const type_info& t):pTypeInfo(&t){}
		virtual ~ITypes(){}
		const type_info* pTypeInfo;
#ifdef _CLR
		ITypes(const type_info& ti,System::Type^t):pTypeInfo(&ti),gcType(t){}
		gcroot<System::Type^> gcType;
#endif
		virtual bool IsReference(){return false;}
		virtual bool IsConst(){return false;}
		virtual bool IsPointer(){return false;}
		virtual long GetPointerLevel(){return 0;}
		virtual ITypes* NewPointedType(){return NULL;}
		virtual ITypes* NewCopy(){return new ITypes(*this);}
	};
	template<typename T>struct Types:public ITypes
	{
		//Ĭ�Ϲ���
		Types():ITypes(typeid(T)){}
		//��������
		virtual ~Types(){}
		static enum:signed char
		{
			isReference = false,
			isConst = false,
			isPointer = false,
			isPointedConst = false,
			isGcHandle = false
		};
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//��ȡָ��ָ�����ݵ�ֵ
		static T& PointerToReference(void *p){return *(T*)p;}
		//��ͨ
		typedef typename T Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef void Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static void VoidOrPointer(void*const&p){}
		//�������void�������������
		static inline Normal& VoidOrWrong(){throw -1;}
	};
	template<typename T>struct Types<const T>:public ITypes
	{
		static enum:signed char
		{
			isReference = false,
			isConst = true,
			isPointer = false,
			isPointedConst = false,
			isGcHandle = false
		};
		//Ĭ�Ϲ���
		Types():ITypes(typeid(T)){}
		//��������
		virtual ~Types(){}
		//�Ƿ���
		virtual bool IsConst(){return true;}
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//��ȡָ��ָ�����ݵ�ֵ
		static T& PointerToReference(void *p){return *(T*)p;}
		//��ͨ
		typedef typename T Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef void Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static void VoidOrPointer(void*const&p){}
		//�������void�������������
		static inline Normal& VoidOrWrong(){throw -1;}
	};
	template<typename T>struct Types<T&>:public ITypes
	{
		static enum:signed char
		{
			isReference = true,
			isConst = false,
			isPointer = false,
			isPointedConst = false,
			isGcHandle = false
		};
		//Ĭ�Ϲ���
		Types():ITypes(typeid(T)){}
		//��������
		virtual ~Types(){}
		//�Ƿ�����
		virtual bool IsReference(){return true;}
		
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//��ȡָ��ָ�����ݵ�ֵ
		static T& PointerToReference(void *p){return *(T*)p;}
		//��ͨ
		typedef typename T Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef void Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static void VoidOrPointer(void*const&p){}
		//�������void�������������
		static inline Normal& VoidOrWrong(){throw -1;}
	};
	template<typename T>struct Types<const T&>:public ITypes
	{
		static enum:signed char
		{
			isReference = true,
			isConst = true,
			isPointer = false,
			isPointedConst = false,
			isGcHandle = false
		};
		//Ĭ�Ϲ���
		Types():ITypes(typeid(T)){}
		//��������
		virtual ~Types(){}
		//�Ƿ���
		virtual bool IsConst(){return true;}
		//�Ƿ�����
		virtual bool IsReference(){return true;}
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//��ȡָ��ָ�����ݵ�ֵ
		static T& PointerToReference(void *p){return *(T*)p;}
		//��ͨ
		typedef typename T Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef void Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static void VoidOrPointer(void*const&p){}
		//�������void�������������
		static inline Normal& VoidOrWrong(){throw -1;}
	};
	template<typename T>struct Types<T*>:public ITypes
	{
		static enum:signed char
		{
			isReference = false,
			isConst = false,
			isPointer = true,
			isPointedConst = false,
			isGcHandle = false
		};
		//Ĭ�Ϲ���
		Types():ITypes(typeid(T*)){}
		//��������
		virtual ~Types(){}
		//�Ƿ�ָ��
		virtual bool IsPointer(){return true;}
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//����ָ�����͵�ָ��
		virtual ITypes* NewPointedType(){return new Types<T>();;}
		//��ȡָ��ȼ�
		virtual long GetPointerLevel(){if(Types<T>().IsPointer()==false)return 1;return Types<T>().GetPointerLevel()+1;}	
		//��ȡָ��ָ�����ݵ�ֵ
		static T*& PointerToReference(void *p){return *(T**)p;}
		//��ͨ
		typedef typename T* Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef T Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static T* VoidOrPointer(void*const&p){return (T*)p;}
		//�������void�������������
		static inline Normal& VoidOrWrong(){throw -1;}
	};
	template<typename T>struct Types<T*&>:public ITypes
	{
		static enum:signed char
		{
			isReference = true,
			isConst = false,
			isPointer = true,
			isPointedConst = false,
			isGcHandle = false
		};
		//Ĭ�Ϲ���
		Types():ITypes(typeid(T*&)){}
		//��������
		virtual ~Types(){}
		//�Ƿ�ָ��
		virtual bool IsPointer(){return true;}
		//�Ƿ�����
		virtual bool IsReference(){return true;}
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//����ָ�����͵�ָ��
		virtual ITypes* NewPointedType(){return new Types<T>();;}
		//��ȡָ��ȼ�
		virtual long GetPointerLevel(){if(Types<T>().IsPointer()==false)return 1;return Types<T>().GetPointerLevel()+1;}	
		//��ȡָ��ָ�����ݵ�ֵ
		static T*& PointerToReference(void *p){return *(T**)p;}
		//��ͨ
		typedef typename T* Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef T Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static T*& VoidOrPointer(void*const&p){return (T*&)p;}
		//�������void�������������
		static inline Normal& VoidOrWrong(){throw -1;}
	};
	template<typename T>struct Types<T*const>:public ITypes
	{
		static enum:signed char
		{
			isReference = false,
			isConst = true,
			isPointer = true,
			isPointedConst = false,
			isGcHandle = false
		};
		//Ĭ�Ϲ���
		Types():ITypes(typeid(T*const)){}
		//��������
		virtual ~Types(){}
		//�Ƿ�ָ��
		virtual bool IsPointer(){return true;}
		//�Ƿ���
		virtual bool IsConst(){return true;}
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//����ָ�����͵�ָ��
		virtual ITypes* NewPointedType(){return new Types<T>();;}
		//��ȡָ��ȼ�
		virtual long GetPointerLevel(){if(Types<T>().IsPointer()==false)return 1;return Types<T>().GetPointerLevel()+1;}	
		//��ȡָ��ָ�����ݵ�ֵ
		static T*& PointerToReference(void *p){return *(T**)p;}
		//��ͨ
		typedef typename T* Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef T Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static T*const VoidOrPointer(void*const&p){return (T*const)p;}
		//�������void�������������
		static inline Normal& VoidOrWrong(){throw -1;}
	};
	template<typename T>struct Types<T*const&>:public ITypes
	{
		static enum:signed char
		{
			isReference = true,
			isConst = true,
			isPointer = true,
			isPointedConst = false,
			isGcHandle = false
		};
		//Ĭ�Ϲ���
		Types():ITypes(typeid(T*const&)){}
		//��������
		virtual ~Types(){}
		//�Ƿ�ָ��
		virtual bool IsPointer(){return true;}
		//�Ƿ���
		virtual bool IsConst(){return true;}
		//�Ƿ�����
		virtual bool IsReference(){return true;}
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//����ָ�����͵�ָ��
		virtual ITypes* NewPointedType(){return new Types<T>();;}
		//��ȡָ��ȼ�
		virtual long GetPointerLevel(){if(Types<T>().IsPointer()==false)return 1;return Types<T>().GetPointerLevel()+1;}	
		//��ȡָ��ָ�����ݵ�ֵ
		static T*& PointerToReference(void *p){return *(T**)p;}
		//��ͨ
		typedef typename T* Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef T Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static T*const& VoidOrPointer(void*const&p){return (T*const&)p;}
		//�������void�������������
		static inline Normal& VoidOrWrong(){throw -1;}
	};
	template<>struct Types<void>:public ITypes
	{
		static enum:signed char
		{
			isReference = false,
			isConst = false,
			isPointer = false,
			isPointedConst = false,
			isGcHandle = false
		};
		//Ĭ�Ϲ���
		Types():ITypes(typeid(void)){}
		//��������
		virtual ~Types(){}
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//��ͨ
		typedef void Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef void Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static void VoidOrPointer(void*const&p){}
		//�������void�������������
		static inline void VoidOrWrong(){}
	};
	template<>struct Types<const void>:public ITypes
	{
		static enum:signed char
		{
			isReference = false,
			isConst = true,
			isPointer = false,
			isPointedConst = false,
			isGcHandle = false
		};
		//Ĭ�Ϲ���
		Types():ITypes(typeid(const void)){}
		//��������
		virtual ~Types(){}
		//�Ƿ���
		virtual bool IsConst(){return true;}
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//��ͨ
		typedef void Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef void Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static void VoidOrPointer(void*const&p){}
		//�������void�������������
		static inline void VoidOrWrong(){}
	};
#ifdef _CLR
	template<typename T>struct Types<T^>:public ITypes
	{
		static enum:signed char
		{
			isReference = false,
			isConst = false,
			isPointer = false,
			isPointedConst = false,
			isGcHandle = true
		};
		//Ĭ�Ϲ���
		Types():ITypes(typeid(GcType<T^>),T::typeid){}
		//��������
		virtual ~Types(){}
		//�Ƿ�ָ��
		virtual bool IsPointer(){return false;}
		//���ݴ�С
		virtual long SizeOfNormalType(){return sizeof(T^);}
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//����ָ�����͵�ָ��
		virtual ITypes* NewPointedType(){return NULL;}
		//��ȡָ��ȼ�
		virtual long GetPointerLevel(){return 0;}	
		//��ȡָ��ָ�����ݵ�ֵ
		static T^% PointerToReference(void *p)
		{
			//System::Runtime::InteropServices::GCHandle g=(System::Runtime::InteropServices::GCHandle::operator System::Runtime::InteropServices::GCHandle(System::IntPtr(p)));
			//GcRefConvert<T>^o= static_cast<GcRefConvert<T>^>(g.Target);
			//g.Free();
			return *(T^*)p;
		}
		//��ͨ
		typedef typename T^ Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef void Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static void VoidOrPointer(void*const&p){}
		//��������Ͳ���void���׳�����
		static T^ VoidOrWrong(){throw -1;}
	};
	template<typename T>struct Types<T^%>:public ITypes
	{
		static enum:signed char
		{
			isReference = true,
			isConst = false,
			isPointer = false,
			isPointedConst = false,
			isGcHandle = true
		};
		//Ĭ�Ϲ���
		Types():ITypes(typeid(GcType<T^%>),T::typeid){}
		//��������
		virtual ~Types(){}
		//�Ƿ�ָ��
		virtual bool IsPointer(){return false;}
		//���ݴ�С
		virtual long SizeOfNormalType(){return sizeof(T^%);}
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//����ָ�����͵�ָ��
		virtual ITypes* NewPointedType(){return NULL;}
		//��ȡָ��ȼ�
		virtual long GetPointerLevel(){return 0;}	
		//��ȡָ��ָ�����ݵ�ֵ
		static T^% PointerToReference(void *p)
		{
			//System::Runtime::InteropServices::GCHandle g=(System::Runtime::InteropServices::GCHandle::operator System::Runtime::InteropServices::GCHandle(System::IntPtr(p)));
			//GcRefConvert<T>^o= static_cast<GcRefConvert<T>^>(g.Target);
			//g.Free();
			return *(T^*)p;
		}
		//��ͨ
		typedef typename T^ Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef void Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static void VoidOrPointer(void*const&p){}
		//��������Ͳ���void���׳�����
		static T^% VoidOrWrong(){throw -1;}
	};
	template<typename T>struct Types<T^*>:public ITypes
	{
		static enum:signed char
		{
			isReference = false,
			isConst = false,
			isPointer = true,
			isPointedConst = false,
			isGcHandle = false
		};
		//Ĭ�Ϲ���
		Types():ITypes(typeid(GcType<T^*>),T::typeid){}
		//��������
		virtual ~Types(){}
		//�Ƿ�ָ��
		virtual bool IsPointer(){return true;}
		//���ɸ����͵ĸ���ָ��
		virtual ITypes* NewCopy(){return new Types();}
		//����ָ�����͵�ָ��
		virtual ITypes* NewPointedType(){return new Types<T^>();;}
		//��ȡָ��ȼ�
		virtual long GetPointerLevel(){return 1;}	
		//��ȡָ��ָ�����ݵ�ֵ
		static T^*& PointerToReference(void *p){return *(T^**)p;}
		//��ͨ
		typedef typename T^* Normal;
		//ָ�������(��ָ����������void��ʾ)
		typedef T^ Pointed;
		//�����ָ����ָ��ת��Ϊ��ǰ���ͣ��������κβ���
		static T^* VoidOrPointer(void*const&p){return (T^*)p;}
		//��������Ͳ���void���׳�����
		static T^* VoidOrWrong(){throw -1;}
	};
#endif
	class XTypes:public XBase
	{
		friend NodeOfRoot;
		//��֮���������ͽڵ�
		NodeOfRoot* pNode;
		//��¼������Ϣ
		ITypes* pType;
	public:
		//����ͨ�÷���
		XBaseVTypeMethods_H(XTypes);
		XTypes(const XTypes&);//���ƹ���
		XTypes(ITypes*);
		XTypes(const type_info&);
		template<class T>XTypes(Types<T>& tmp)
		{
			pNode = 0;
			pType =tmp.NewCopy();
		}
		XString GetName()const;
		XString GetFullName()const;
		virtual XString ToString()const;
		bool IsDerivedFrom(const XTypes&)const;
		bool IsPointer()const{return pType->IsPointer();}
		bool IsReference()const{return pType->IsReference();}
		bool IsConst()const{return pType->IsConst();}
		long GetPointerLevel()const{return pType->GetPointerLevel();}
		XTypes GetPointedType()const;
		virtual ~XTypes();
		operator const type_info&()const;
		bool operator==(const type_info& t)const{return (const type_info&)*this==t;}
		bool operator==(const XTypes& t)const{return (const type_info&)*this==t;}
		friend bool operator==(const type_info& t1,const XTypes& t2){return (const type_info&)t2==t1;}
		bool operator!=(const type_info& t)const{return (const type_info&)*this!=t;}
		bool operator!=(const XTypes& t)const{return (const type_info&)*this!=t;}
		friend bool operator!=(const type_info& t1,const XTypes& t2){return (const type_info&)t2!=t1;}
	};

	//�����ڵ�
	struct NodeOfRoot
	{
		//��Ա�б�
		NodeOfRoot** pNodeList;
		//��Ա�б�����
		union {unsigned long nodeCount:24;
		struct{char _count[3];
		//��ǰ�ڵ�����,0Ϊroot,1Ϊ�����ռ䣬2Ϊģ�壬3Ϊģ���࣬4Ϊ��ͨ��
		unsigned char type;};};
		//��ȡ���ڵ�
		static NodeOfRoot& Root();
		//ʹ��һ�����ͳ�ʼ��
		NodeOfRoot(char type):pNodeList(NULL),nodeCount(0),type(type){}
		//��������
		~NodeOfRoot();
		//��ȡ�ýڵ�����
		XString GetName()const;
		//��ȡ�ýڵ�ȫ�������������ռ䣩
		XString GetFullName()const;
		//������id���ҽڵ�
		NodeOfRoot* FindNodeByTypeInfo(const type_info& t);
		//�жϸýڵ��Ƿ������ָ������ڵ�
		bool IsIncludeIn(NodeOfRoot* p)const;
		//�жϸýڵ��Ƿ����һ���ڵ�̳У���ڵ㣩
		bool IsDerivedFrom(NodeOfRoot* p)const;
		//��������ռ�ڵ�(����Ѵ���ͬ���������ռ�ڵ��򷵻���ָ��)
		NodeOfRoot* AddNamespace(const XString& path);
		//���������ʱ���ڵ�
		static NodeOfRoot*AddUnknown(const type_info& xt);
		//�Ƴ�������ʱ���ڵ�(ƾ���µĽڵ�)
		static void RemoveUnknown(const type_info& xt,NodeOfRoot*p);
		//�����ڵ㣨��ͨ�࣬�޼̳У�,���� Add("LJ::XBase",Types<LJ::XBase>());
		static XTypes& Add(const XString& classPath,const XTypes& xt);
		//�����ڵ㣨��ͨ�࣬�м̳У�,���� Add("LJ::XString",Types<LJ::XString>(),typeid(LJ::XBase));
		static XTypes& Add(const XString& classPath,const XTypes& xt,const type_info& baseid);
		//�����ڵ㣨ģ���࣬�޼̳У�,���� Add("LJ::XTypes",Types<LJ::XTypes<T>>(),TypesCheckingObject::MakeObject<T>(1));
		static XTypes& Add(const XString& classPath,const XTypes& xt,const TypesCheckingObject& tc);
		//�����ڵ㣨ģ���࣬�м̳У�,���� Add("LJ::XArray",Types<LJ::XArray<T>>(),TypesCheckingObject::MakeObject<T>(1),typeid(LJ::XBase));
		static XTypes& Add(const XString& classPath,const XTypes& xt,const TypesCheckingObject& tc,const type_info& baseid);
	};
	//�����ռ�ڵ�
	struct NodeOfNamespace:public NodeOfRoot
	{
		//����
		LPWSTR name;
		//���������ռ�
		NodeOfRoot* pNamespace;
		//��һ����ڵ���ӵ������б��У���������ӵ����б��������
		NodeOfType* AddClassToList(const XString& name,const XTypes& xt);
		//��һ��ģ��ڵ���ӵ������б��У���������ӵ����б��������
		NodeOfTemplate* AddTemplateToList(const XString& name);
		//ʹ�ð����������ռ�������ռ�ڵ�������
		NodeOfNamespace(NodeOfRoot* p):pNamespace(p),name(NULL),NodeOfRoot(1){}
		//��������
		~NodeOfNamespace();
	};
	//ģ��ڵ�
	struct NodeOfTemplate:public NodeOfRoot
	{
		//����
		LPWSTR name;
		//���������ռ�
		NodeOfRoot* pNamespace;
		//��һ��ģ����ڵ���ӵ������б��У���������ӵ����б��������
		NodeOfTemplateClass* AddTemplateClassToList(const TypesCheckingObject&tc ,const XTypes& xt);
		//ʹ�ð�����ģ��������ռ�ڵ��ģ������������
		NodeOfTemplate(NodeOfRoot* p,const XString& str);
		//��������
		~NodeOfTemplate();
	};
	//ģ����ڵ�
	struct NodeOfTemplateClass:public NodeOfRoot
	{
		//������������Ϣ
		XTypes Info;
		//����ģ��
		NodeOfTemplate* pTemplate;
		//�����б�
		NodeOfRoot** pBaseList;
		//��������
		unsigned long baseCount;
		//ģ���βα�
		TypesCheckingObject typesChecking;
		//��һ���ڵ���ӵ������б��У���������ӵ����б��������
		NodeOfRoot* AddToList(NodeOfRoot*);
		//��һ���ڵ���ӵ��̳��б��У���������ӵ����б��������
		NodeOfRoot* AddToBase(NodeOfRoot*);
		//ʹ�ð�����ģ�����ģ��ڵ��������Ϣ������
		NodeOfTemplateClass(NodeOfTemplate* p,const TypesCheckingObject& tc,const XTypes& t):pTemplate(p),Info(t),pBaseList(NULL),baseCount(0),typesChecking(tc),NodeOfRoot(3){}
		//��������
		~NodeOfTemplateClass();
	};
	//��ͨ��ڵ�
	struct NodeOfType:public NodeOfRoot
	{
		//������������Ϣ
		XTypes Info;
		//����
		LPWSTR name;
		//���������ռ�
		NodeOfRoot* pNamespace;
		//�����б�
		NodeOfRoot** pBaseList;
		//��������
		unsigned long baseCount;
		//��һ���ڵ���ӵ������б��У���������ӵ����б��������
		NodeOfRoot*& AddToList(NodeOfRoot*);
		//��һ���ڵ���ӵ��̳��б��У���������ӵ����б��������
		NodeOfRoot*& AddToBase(NodeOfRoot*);
		//ʹ�ð�������������ռ�ڵ㡢���ƺ�������Ϣ������
		NodeOfType(NodeOfRoot* p,const XString&s,const XTypes& t);
		//��������
		~NodeOfType();
	};



#define CREATECLASSTYPE(classfullpath,baseclassfullpath) NodeOfRoot::Add(#classfullpath,XTypes(new Types<classfullpath>()),typeid(baseclassfullpath))


}