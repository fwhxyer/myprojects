#pragma once//防止重复定义

//所有需要定义的类先在这里声明一下（某些模板类除外）
namespace LJ
{
#if (_MANAGED == 1) || (_M_CEE == 1) //托管支持
#define _CLR//自定义的一个好记的标识，表示以有公共语言运行时支持编译
#include "gcroot.h"
	using namespace System;
	using System::Runtime::InteropServices::Marshal;//Marshal类
#endif

	//VS版本特性
#if _MSC_VER>=1600
#define _USE_RIGHT_VALUE_REFERENCE//右值引用
#else
#ifndef _CLR
#define nullptr 0
#endif
#endif
	/*
	MS VC++ 10.0 _MSC_VER = 1600（VS2010）
	MS VC++ 9.0 _MSC_VER = 1500
	MS VC++ 8.0 _MSC_VER = 1400
	MS VC++ 7.1 _MSC_VER = 1310
	MS VC++ 7.0 _MSC_VER = 1300
	MS VC++ 6.0 _MSC_VER = 1200
	MS VC++ 5.0 _MSC_VER = 1100
	*/
	//类的声明格式为class+空格+类名+;
	//基类
	class XBase;

	//直接从XBase派生

	//异常类型
	class XException;
	//类型类
	class XTypes;
	//类型节点
	struct NodeOfRoot;
	struct NodeOfNamespace;
	struct NodeOfTemplate;
	struct NodeOfTemplateClass;
	struct NodeOfType;
	//表示时间
	class XTime;
	//表示一个随机数
	class XRandom;

	//引用类型

	//表示一个数组的引用
	template<typename T>class XArray;
	//表示一个无序集合容器的引用
	template<typename T>class XCollection;
	//表示一个字符串
	class XString;
	//表示一个委托
	class XDelegates;
	//表示一个动作
	class XActions;
	//表示一个任务
	class XTask;

	//被引用类型

	//表示一个字符串的被引用对象（提供独自的操作方法，可以直接使用）
	class VString;
	//表示一个数组
	template<typename T>class VArray;
	//表示一个缓存块
	class VBuffer;
	//表示一个无序集合容器
	template<typename T>class VCollection;
	//表示一个委托的被引用对象（不应直接使用）
	struct IDelegate;
	//表示一个任务的被引用对象（不应直接使用）
	struct ITask;

	//特殊类型

	//表示一个静态属性
	template<class T>class StaticProperty;
	//表示一个线程同步的控制器
	class ThreadControl;


}