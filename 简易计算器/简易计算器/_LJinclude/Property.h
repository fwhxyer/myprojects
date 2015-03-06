#pragma once//��W�Ⲩ(LuoJun)��д
#include <stddef.h>
namespace LJ
{

	//��д����
	template<class T,class ObjectT>class Property
	{
		ObjectT& This;//����ʵ��ָ��
		T (ObjectT::*getMethod)(void)const ;//����get��������ָ��
		void (ObjectT::*setMethod)(T);//����set��������ָ��
	public:
		Property(ObjectT& pCurrent,T (ObjectT::*method_get)(void)const ,void(ObjectT::*method_set)(T)):getMethod(method_get),setMethod(method_set),This(pCurrent){}
		operator T()const{return (This.*getMethod)();}//ȡ����
		Property& operator=(T t){(This.*setMethod)(t);return *this;}//дǰִ�еķ���
	};
	//ֻ������
	template<class T,class ObjectT>class PropertyReadOnly
	{
		ObjectT& This;//����ʵ��ָ��
		T (ObjectT::*getMethod)(void)const ;//����get��������ָ��
	public:
		PropertyReadOnly(ObjectT& pCurrent ,T (ObjectT::*method_get)(void)const):getMethod(method_get),This(pCurrent){}
		operator T()const{return (This.*getMethod)();}//ȡ����
	};
	//ֻд����
	template<class T,class ObjectT>class PropertyWriteOnly
	{
		ObjectT& This;//����ʵ��ָ��
		void (ObjectT::*setMethod)(T);//����set��������ָ��
	public:
		PropertyWriteOnly(ObjectT& pCurrent,void(ObjectT::*method_set)(T)):setMethod(method_set),This(pCurrent){}
		PropertyWriteOnly& operator=(T t){(This.*setMethod)(t);return *this;}//дǰִ�еķ���
	};
	//��̬�Ķ�д����
	template<class T>class StaticProperty//T�������ԣ�ָ��get������set����
	{
		T (&getMethod)(void);//����get��������
		void (&setMethod)(const T&);//����set��������
	public:
		StaticProperty(T (&method_get)(void),void(&method_set)(const T&)):getMethod(method_get),setMethod(method_set){}
		operator T()const{return (getMethod)();}//ȡ����
		StaticProperty& operator=(const T&t){(setMethod)(t);return *this;}//д����
	};
	//��̬��ֻ������
	template<class T>class StaticPropertyReadOnly
	{
		T (&getMethod)(void);//����get��������
	public:
		StaticPropertyReadOnly(T (&method_get)(void)):getMethod(method_get){}
		operator T()const{return (getMethod)();}//ȡ����
	};

	//�������Ե�ʵ�ַ�����Imperfect C++�е�������Debugģʽ�ͷ�/clr������,VS2010����ǰ�п��ܻᵼ�±������ڲ�����

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