#pragma once
#define XTYPES_
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
#include "typeinfo.h"
namespace LJ
{
#ifdef _CLR
	//托管类型标记
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
		//查找不同,从i开始
		int FindDifferenceWith(const TypesCheckingObject&t,int i=0)const{while(i<count&&i<t.count){if(pTypes[i]!=t.pTypes[i] || pCR[i]!=t.pCR[i])break;++i;}return (i<count||i<t.count)?i:-1;}
		//查找不同,从i开始
		int AppFindDifferenceWith(const TypesCheckingObject&t,int i=0)const{while(i<count&&i<t.count){if(pTypes[i]!=t.pTypes[i])break;++i;}return (i<count||i<t.count)?i:-1;}
	};
	//如果第1个类型T与第2个类型TT同类型,则Result表示第3个类型T1，否则表示第4个类型T2
	template<class T,class TT,class T1,class T2> struct IfTypesEqual{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypesEqual<T,T,T1,T2>{typedef typename T1 Result;};
	//如果第1个类型T是指针则Result表示表示第2个类型T1，否则表示第3个类型T2
	template<class T,class T1,class T2> struct IfTypeIsPointer{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypeIsPointer<T*,T1,T2>{typedef typename T1 Result;};
	//如果第1个类型T是const则Result表示表示第2个类型T1，否则表示第3个类型T2
	template<class T,class T1,class T2> struct IfTypeIsConst{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypeIsConst<T const,T1,T2>{typedef typename T1 Result;};
	template<class T,class T1,class T2> struct IfTypeIsConst<T &,T1,T2>{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypeIsConst<T const&,T1,T2>{typedef typename T1 Result;};
	//如果第1个类型T是引用则Result表示表示第2个类型T1，否则表示第3个类型T2
	template<class T,class T1,class T2> struct IfTypeIsReference{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypeIsReference<T const,T1,T2>{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypeIsReference<T &,T1,T2>{typedef typename T1 Result;};
	template<class T,class T1,class T2> struct IfTypeIsReference<T const&,T1,T2>{typedef typename T1 Result;};
#ifdef _CLR
	template<class T,class T1,class T2> struct IfTypeIsReference<T^%,T1,T2>{typedef typename T1 Result;};
#endif
	//两个类型是否相同
	template<class T1,class T2>struct TypesEqual{static enum:signed char{isEqual=false}; inline operator bool(){return false;}};
	template<class T>struct TypesEqual<T,T>{static enum:signed char{isEqual=true}; inline operator bool(){return true;}};
	//如果第1个类型T是基本数据类型则Result表示表示第2个类型T1，否则表示第3个类型T2
	template<class T,class T1,class T2> struct IfTypeIsBaseDataType{typedef typename T2 Result;};
	template<class T,class T1,class T2> struct IfTypeIsBaseDataType<T*,T1,T2>{typedef typename T1 Result;};
	//如果第1个类型T是托管句柄则Result表示表示第2个类型T1，否则表示第3个类型T2
	template<class T,class T1,class T2> struct IfTypeIsGcHandle{typedef typename T2 Result;};
#ifdef _CLR
	template<class T,class T1,class T2> struct IfTypeIsGcHandle<T^,T1,T2>{typedef typename T1 Result;};
	template<class T,class T1,class T2> struct IfTypeIsGcHandle<T^%,T1,T2>{typedef typename T1 Result;};
	//托管句柄算到基本数据类型中
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
	//类型描述接口
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
		//默认构造
		Types():ITypes(typeid(T)){}
		//析构函数
		virtual ~Types(){}
		static enum:signed char
		{
			isReference = false,
			isConst = false,
			isPointer = false,
			isPointedConst = false,
			isGcHandle = false
		};
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//获取指针指向数据的值
		static T& PointerToReference(void *p){return *(T*)p;}
		//普通
		typedef typename T Normal;
		//指向的类型(无指向类型则用void表示)
		typedef void Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static void VoidOrPointer(void*const&p){}
		//如果不是void类型则产生错误
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
		//默认构造
		Types():ITypes(typeid(T)){}
		//析构函数
		virtual ~Types(){}
		//是否常量
		virtual bool IsConst(){return true;}
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//获取指针指向数据的值
		static T& PointerToReference(void *p){return *(T*)p;}
		//普通
		typedef typename T Normal;
		//指向的类型(无指向类型则用void表示)
		typedef void Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static void VoidOrPointer(void*const&p){}
		//如果不是void类型则产生错误
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
		//默认构造
		Types():ITypes(typeid(T)){}
		//析构函数
		virtual ~Types(){}
		//是否引用
		virtual bool IsReference(){return true;}
		
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//获取指针指向数据的值
		static T& PointerToReference(void *p){return *(T*)p;}
		//普通
		typedef typename T Normal;
		//指向的类型(无指向类型则用void表示)
		typedef void Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static void VoidOrPointer(void*const&p){}
		//如果不是void类型则产生错误
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
		//默认构造
		Types():ITypes(typeid(T)){}
		//析构函数
		virtual ~Types(){}
		//是否常量
		virtual bool IsConst(){return true;}
		//是否引用
		virtual bool IsReference(){return true;}
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//获取指针指向数据的值
		static T& PointerToReference(void *p){return *(T*)p;}
		//普通
		typedef typename T Normal;
		//指向的类型(无指向类型则用void表示)
		typedef void Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static void VoidOrPointer(void*const&p){}
		//如果不是void类型则产生错误
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
		//默认构造
		Types():ITypes(typeid(T*)){}
		//析构函数
		virtual ~Types(){}
		//是否指针
		virtual bool IsPointer(){return true;}
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//生成指向类型的指针
		virtual ITypes* NewPointedType(){return new Types<T>();;}
		//获取指针等级
		virtual long GetPointerLevel(){if(Types<T>().IsPointer()==false)return 1;return Types<T>().GetPointerLevel()+1;}	
		//获取指针指向数据的值
		static T*& PointerToReference(void *p){return *(T**)p;}
		//普通
		typedef typename T* Normal;
		//指向的类型(无指向类型则用void表示)
		typedef T Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static T* VoidOrPointer(void*const&p){return (T*)p;}
		//如果不是void类型则产生错误
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
		//默认构造
		Types():ITypes(typeid(T*&)){}
		//析构函数
		virtual ~Types(){}
		//是否指针
		virtual bool IsPointer(){return true;}
		//是否引用
		virtual bool IsReference(){return true;}
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//生成指向类型的指针
		virtual ITypes* NewPointedType(){return new Types<T>();;}
		//获取指针等级
		virtual long GetPointerLevel(){if(Types<T>().IsPointer()==false)return 1;return Types<T>().GetPointerLevel()+1;}	
		//获取指针指向数据的值
		static T*& PointerToReference(void *p){return *(T**)p;}
		//普通
		typedef typename T* Normal;
		//指向的类型(无指向类型则用void表示)
		typedef T Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static T*& VoidOrPointer(void*const&p){return (T*&)p;}
		//如果不是void类型则产生错误
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
		//默认构造
		Types():ITypes(typeid(T*const)){}
		//析构函数
		virtual ~Types(){}
		//是否指针
		virtual bool IsPointer(){return true;}
		//是否常量
		virtual bool IsConst(){return true;}
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//生成指向类型的指针
		virtual ITypes* NewPointedType(){return new Types<T>();;}
		//获取指针等级
		virtual long GetPointerLevel(){if(Types<T>().IsPointer()==false)return 1;return Types<T>().GetPointerLevel()+1;}	
		//获取指针指向数据的值
		static T*& PointerToReference(void *p){return *(T**)p;}
		//普通
		typedef typename T* Normal;
		//指向的类型(无指向类型则用void表示)
		typedef T Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static T*const VoidOrPointer(void*const&p){return (T*const)p;}
		//如果不是void类型则产生错误
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
		//默认构造
		Types():ITypes(typeid(T*const&)){}
		//析构函数
		virtual ~Types(){}
		//是否指针
		virtual bool IsPointer(){return true;}
		//是否常量
		virtual bool IsConst(){return true;}
		//是否引用
		virtual bool IsReference(){return true;}
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//生成指向类型的指针
		virtual ITypes* NewPointedType(){return new Types<T>();;}
		//获取指针等级
		virtual long GetPointerLevel(){if(Types<T>().IsPointer()==false)return 1;return Types<T>().GetPointerLevel()+1;}	
		//获取指针指向数据的值
		static T*& PointerToReference(void *p){return *(T**)p;}
		//普通
		typedef typename T* Normal;
		//指向的类型(无指向类型则用void表示)
		typedef T Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static T*const& VoidOrPointer(void*const&p){return (T*const&)p;}
		//如果不是void类型则产生错误
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
		//默认构造
		Types():ITypes(typeid(void)){}
		//析构函数
		virtual ~Types(){}
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//普通
		typedef void Normal;
		//指向的类型(无指向类型则用void表示)
		typedef void Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static void VoidOrPointer(void*const&p){}
		//如果不是void类型则产生错误
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
		//默认构造
		Types():ITypes(typeid(const void)){}
		//析构函数
		virtual ~Types(){}
		//是否常量
		virtual bool IsConst(){return true;}
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//普通
		typedef void Normal;
		//指向的类型(无指向类型则用void表示)
		typedef void Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static void VoidOrPointer(void*const&p){}
		//如果不是void类型则产生错误
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
		//默认构造
		Types():ITypes(typeid(GcType<T^>),T::typeid){}
		//析构函数
		virtual ~Types(){}
		//是否指针
		virtual bool IsPointer(){return false;}
		//数据大小
		virtual long SizeOfNormalType(){return sizeof(T^);}
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//生成指向类型的指针
		virtual ITypes* NewPointedType(){return NULL;}
		//获取指针等级
		virtual long GetPointerLevel(){return 0;}	
		//获取指针指向数据的值
		static T^% PointerToReference(void *p)
		{
			//System::Runtime::InteropServices::GCHandle g=(System::Runtime::InteropServices::GCHandle::operator System::Runtime::InteropServices::GCHandle(System::IntPtr(p)));
			//GcRefConvert<T>^o= static_cast<GcRefConvert<T>^>(g.Target);
			//g.Free();
			return *(T^*)p;
		}
		//普通
		typedef typename T^ Normal;
		//指向的类型(无指向类型则用void表示)
		typedef void Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static void VoidOrPointer(void*const&p){}
		//如果该类型不是void则抛出错误
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
		//默认构造
		Types():ITypes(typeid(GcType<T^%>),T::typeid){}
		//析构函数
		virtual ~Types(){}
		//是否指针
		virtual bool IsPointer(){return false;}
		//数据大小
		virtual long SizeOfNormalType(){return sizeof(T^%);}
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//生成指向类型的指针
		virtual ITypes* NewPointedType(){return NULL;}
		//获取指针等级
		virtual long GetPointerLevel(){return 0;}	
		//获取指针指向数据的值
		static T^% PointerToReference(void *p)
		{
			//System::Runtime::InteropServices::GCHandle g=(System::Runtime::InteropServices::GCHandle::operator System::Runtime::InteropServices::GCHandle(System::IntPtr(p)));
			//GcRefConvert<T>^o= static_cast<GcRefConvert<T>^>(g.Target);
			//g.Free();
			return *(T^*)p;
		}
		//普通
		typedef typename T^ Normal;
		//指向的类型(无指向类型则用void表示)
		typedef void Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static void VoidOrPointer(void*const&p){}
		//如果该类型不是void则抛出错误
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
		//默认构造
		Types():ITypes(typeid(GcType<T^*>),T::typeid){}
		//析构函数
		virtual ~Types(){}
		//是否指针
		virtual bool IsPointer(){return true;}
		//生成该类型的副本指针
		virtual ITypes* NewCopy(){return new Types();}
		//生成指向类型的指针
		virtual ITypes* NewPointedType(){return new Types<T^>();;}
		//获取指针等级
		virtual long GetPointerLevel(){return 1;}	
		//获取指针指向数据的值
		static T^*& PointerToReference(void *p){return *(T^**)p;}
		//普通
		typedef typename T^* Normal;
		//指向的类型(无指向类型则用void表示)
		typedef T^ Pointed;
		//如果是指针则将指针转换为当前类型，否则不做任何操作
		static T^* VoidOrPointer(void*const&p){return (T^*)p;}
		//如果该类型不是void则抛出错误
		static T^* VoidOrWrong(){throw -1;}
	};
#endif
	class XTypes:public XBase
	{
		friend NodeOfRoot;
		//与之关联的类型节点
		NodeOfRoot* pNode;
		//记录类型信息
		ITypes* pType;
	public:
		//基类通用方法
		XBaseVTypeMethods_H(XTypes);
		XTypes(const XTypes&);//复制构造
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

	//基础节点
	struct NodeOfRoot
	{
		//成员列表
		NodeOfRoot** pNodeList;
		//成员列表数量
		union {unsigned long nodeCount:24;
		struct{char _count[3];
		//当前节点类型,0为root,1为命名空间，2为模板，3为模板类，4为普通类
		unsigned char type;};};
		//获取根节点
		static NodeOfRoot& Root();
		//使用一个类型初始化
		NodeOfRoot(char type):pNodeList(NULL),nodeCount(0),type(type){}
		//析构函数
		~NodeOfRoot();
		//获取该节点名称
		XString GetName()const;
		//获取该节点全名（包括命名空间）
		XString GetFullName()const;
		//按类型id查找节点
		NodeOfRoot* FindNodeByTypeInfo(const type_info& t);
		//判断该节点是否包含于指定区域节点
		bool IsIncludeIn(NodeOfRoot* p)const;
		//判断该节点是否从另一个节点继承（类节点）
		bool IsDerivedFrom(NodeOfRoot* p)const;
		//添加命名空间节点(如果已存在同名的命名空间节点则返回其指针)
		NodeOfRoot* AddNamespace(const XString& path);
		//添加匿名临时基节点
		static NodeOfRoot*AddUnknown(const type_info& xt);
		//移除匿名临时基节点(凭借新的节点)
		static void RemoveUnknown(const type_info& xt,NodeOfRoot*p);
		//添加类节点（普通类，无继承）,比如 Add("LJ::XBase",Types<LJ::XBase>());
		static XTypes& Add(const XString& classPath,const XTypes& xt);
		//添加类节点（普通类，有继承）,比如 Add("LJ::XString",Types<LJ::XString>(),typeid(LJ::XBase));
		static XTypes& Add(const XString& classPath,const XTypes& xt,const type_info& baseid);
		//添加类节点（模板类，无继承）,比如 Add("LJ::XTypes",Types<LJ::XTypes<T>>(),TypesCheckingObject::MakeObject<T>(1));
		static XTypes& Add(const XString& classPath,const XTypes& xt,const TypesCheckingObject& tc);
		//添加类节点（模板类，有继承）,比如 Add("LJ::XArray",Types<LJ::XArray<T>>(),TypesCheckingObject::MakeObject<T>(1),typeid(LJ::XBase));
		static XTypes& Add(const XString& classPath,const XTypes& xt,const TypesCheckingObject& tc,const type_info& baseid);
	};
	//命名空间节点
	struct NodeOfNamespace:public NodeOfRoot
	{
		//名称
		LPWSTR name;
		//所在命名空间
		NodeOfRoot* pNamespace;
		//将一个类节点添加到包含列表中，并返回添加到的列表项的引用
		NodeOfType* AddClassToList(const XString& name,const XTypes& xt);
		//将一个模板节点添加到包含列表中，并返回添加到的列表项的引用
		NodeOfTemplate* AddTemplateToList(const XString& name);
		//使用包含该命名空间的命名空间节点来构造
		NodeOfNamespace(NodeOfRoot* p):pNamespace(p),name(NULL),NodeOfRoot(1){}
		//析构函数
		~NodeOfNamespace();
	};
	//模板节点
	struct NodeOfTemplate:public NodeOfRoot
	{
		//名称
		LPWSTR name;
		//所在命名空间
		NodeOfRoot* pNamespace;
		//将一个模板类节点添加到包含列表中，并返回添加到的列表项的引用
		NodeOfTemplateClass* AddTemplateClassToList(const TypesCheckingObject&tc ,const XTypes& xt);
		//使用包含该模板的命名空间节点和模板名称来构造
		NodeOfTemplate(NodeOfRoot* p,const XString& str);
		//析构函数
		~NodeOfTemplate();
	};
	//模板类节点
	struct NodeOfTemplateClass:public NodeOfRoot
	{
		//关联的类型信息
		XTypes Info;
		//所属模板
		NodeOfTemplate* pTemplate;
		//基类列表
		NodeOfRoot** pBaseList;
		//基类数量
		unsigned long baseCount;
		//模板形参表
		TypesCheckingObject typesChecking;
		//将一个节点添加到派生列表中，并返回添加到的列表项的引用
		NodeOfRoot* AddToList(NodeOfRoot*);
		//将一个节点添加到继承列表中，并返回添加到的列表项的引用
		NodeOfRoot* AddToBase(NodeOfRoot*);
		//使用包含该模板类的模板节点和类型信息来构造
		NodeOfTemplateClass(NodeOfTemplate* p,const TypesCheckingObject& tc,const XTypes& t):pTemplate(p),Info(t),pBaseList(NULL),baseCount(0),typesChecking(tc),NodeOfRoot(3){}
		//析构函数
		~NodeOfTemplateClass();
	};
	//普通类节点
	struct NodeOfType:public NodeOfRoot
	{
		//关联的类型信息
		XTypes Info;
		//名称
		LPWSTR name;
		//所在命名空间
		NodeOfRoot* pNamespace;
		//基类列表
		NodeOfRoot** pBaseList;
		//基类数量
		unsigned long baseCount;
		//将一个节点添加到派生列表中，并返回添加到的列表项的引用
		NodeOfRoot*& AddToList(NodeOfRoot*);
		//将一个节点添加到继承列表中，并返回添加到的列表项的引用
		NodeOfRoot*& AddToBase(NodeOfRoot*);
		//使用包含该类的命名空间节点、名称和类型信息来构造
		NodeOfType(NodeOfRoot* p,const XString&s,const XTypes& t);
		//析构函数
		~NodeOfType();
	};



#define CREATECLASSTYPE(classfullpath,baseclassfullpath) NodeOfRoot::Add(#classfullpath,XTypes(new Types<classfullpath>()),typeid(baseclassfullpath))


}