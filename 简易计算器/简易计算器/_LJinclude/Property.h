#pragma once//由W意波(LuoJun)编写
#include <stddef.h>
namespace LJ
{

	//读写属性
	template<class T,class ObjectT>class Property
	{
		ObjectT& This;//具体实例指针
		T (ObjectT::*getMethod)(void)const ;//保存get方法函数指针
		void (ObjectT::*setMethod)(T);//保存set方法函数指针
	public:
		Property(ObjectT& pCurrent,T (ObjectT::*method_get)(void)const ,void(ObjectT::*method_set)(T)):getMethod(method_get),setMethod(method_set),This(pCurrent){}
		operator T()const{return (This.*getMethod)();}//取方法
		Property& operator=(T t){(This.*setMethod)(t);return *this;}//写前执行的方法
	};
	//只读属性
	template<class T,class ObjectT>class PropertyReadOnly
	{
		ObjectT& This;//具体实例指针
		T (ObjectT::*getMethod)(void)const ;//保存get方法函数指针
	public:
		PropertyReadOnly(ObjectT& pCurrent ,T (ObjectT::*method_get)(void)const):getMethod(method_get),This(pCurrent){}
		operator T()const{return (This.*getMethod)();}//取方法
	};
	//只写属性
	template<class T,class ObjectT>class PropertyWriteOnly
	{
		ObjectT& This;//具体实例指针
		void (ObjectT::*setMethod)(T);//保存set方法函数指针
	public:
		PropertyWriteOnly(ObjectT& pCurrent,void(ObjectT::*method_set)(T)):setMethod(method_set),This(pCurrent){}
		PropertyWriteOnly& operator=(T t){(This.*setMethod)(t);return *this;}//写前执行的方法
	};
	//静态的读写属性
	template<class T>class StaticProperty//T类型属性，指定get方法和set方法
	{
		T (&getMethod)(void);//保存get方法函数
		void (&setMethod)(const T&);//保存set方法函数
	public:
		StaticProperty(T (&method_get)(void),void(&method_set)(const T&)):getMethod(method_get),setMethod(method_set){}
		operator T()const{return (getMethod)();}//取方法
		StaticProperty& operator=(const T&t){(setMethod)(t);return *this;}//写方法
	};
	//静态的只读属性
	template<class T>class StaticPropertyReadOnly
	{
		T (&getMethod)(void);//保存get方法函数
	public:
		StaticPropertyReadOnly(T (&method_get)(void)):getMethod(method_get){}
		operator T()const{return (getMethod)();}//取方法
	};

	//以下属性的实现方法从Imperfect C++中得来，在Debug模式和非/clr编译下,VS2010及以前有可能会导致编译器内部错误，

	typedef ptrdiff_t (*PFnOff)();

	template<typename V,typename C,void (C::*PFnSet)(V),PFnOff off>
	struct property_set
	{
		inline const property_set& operator=(V v)const
		{
			(((C*)((unsigned char*)this - (*off)()))->*PFnSet)(v);
			return *this;
		}
	};
	template<typename R,typename C,R (C::*PFnGet)(void)const,PFnOff off>

	struct property_get
	{
		operator R()const
		{
			return (((C*)((unsigned char*)this - (*off)()))->*PFnGet)();
		}
	};

	template<typename V,typename C,V (C::*PFnGet)()const,void (C::*PFnSet)(V),PFnOff off>
	struct property_getset
	{
		inline operator V()const
		{
			return (((C*)((unsigned char*)this - (*off)()))->*PFnGet)();
		}
		inline const property_getset& operator=(V v)const
		{
			(((C*)((unsigned char*)this - (*off)()))->*PFnSet)(v);
			return *this;
		}
	};

	template<typename V,typename C,V& (C::*PFnGetSet)(),PFnOff off>
	struct property_ref
	{
		inline operator V()const
		{
			return (((C*)((unsigned char*)this - (*off)()))->*PFnGetSet)();
		}
		inline const property_ref& operator=(V v)const
		{
			(((C*)((unsigned char*)this - (*off)()))->*PFnGetSet)()=v;
			return *this;
		}
	};
	#define PROPERTY_OFFSET(ClassName,PropertyName)	\
	static inline ptrdiff_t _offset()	\
	{return offsetof(ClassName,PropertyName);				}

	#define PROPERTY_GET(ValueTypeName,ClassName,GetMethod,PropertyName)	\
	property_get<ValueTypeName									\
									,	ClassName											\
									,	&ClassName::GetMethod								\
									,	&ClassName::_offset	\
									> PropertyName
	#define PROPERTY_SET(ValueTypeName,ClassName,SetMethod,PropertyName)		\
	property_set<	ValueTypeName									\
									,	ClassName											\
									,	&ClassName::SetMethod						\
									,	&ClassName::_offset	\
									> PropertyName
	#define PROPERTY_GETSET(ValueTypeName,ClassName,GetMethod,SetMethod,PropertyName)	\
	property_getset<	ValueTypeName							\
											,	ClassName									\
											,	&ClassName::GetMethod				\
											,	&ClassName::SetMethod				\
											,	&ClassName::_offset		\
											> PropertyName
	#define PROPERTY_REF(ValueTypeName,ClassName,GetSetMethod,PropertyName)	\
	property_ref<	ValueTypeName							\
						,	ClassName									\
						,	&ClassName::GetSetMethod		\
						,	&ClassName::_offset						\
						> PropertyName
	
}