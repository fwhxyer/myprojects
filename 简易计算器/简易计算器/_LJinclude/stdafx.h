#pragma once
//标准头文件包含（可选，这将增加程序的体积几十KB）：
//1.语言支持
#include<cstddef>//定义宏NULL和offsetof以及其他标准类型size_t 和ptrdiff_t。与对应的标准C头文件的区别是：NULL是c++空指针常量的补充定义，宏offsetof接受结构或联合类型参数，只是他们没有成员指针类型的非静态成员而已
#include<limits>//提供与基本数据类型相关的定义。例如：对于每个数值数据类型，它定义了可以出来的最大值和最小值以及二进制数字的位数。
#include<climits>//提供与基本整形数据相关的c样式定义，这些信息的c++样式在<limits>中提供
#include<cfloat>//提供与基本浮点型数据相关的c样式定义，这些信息的c++样式在<limits>中提供
#include<cstdlib>//提供支持程序启动和终止的宏和函数。这个头文件中还声明了许多其他杂项函数，例如搜索和排序函数，从字符串转换为数值等函数。他与对应的标准c头文件<stdlib.h>不同，定义了abort(void)。Abort()还有额外的功能，它不为静态或自动对象调用析构函数，也不调用传送给atexit()函数的函数。他还定义了exit()函数的额外功能，可以释放静态对象，以注册的逆序调用用atexit()注册的函数，清楚并关闭所有打开的c流，把控制权返回给主机环境
#include<new>//支持动态内存分配
#include<typeinfo>//支持变量在运行期间的类型标识
//#include<exception>//支持异常处理，这是处理程序中可能发生的错误的一种方式。
//#include<cstdarg>//支持接受数量可变的参数的函数。即在调用函数时，可以给函数传递数量不等的数据项。它定义了宏va_arg，va_end和va_start，以及va_list类型 
//#include<csetjmp>//为c样式的非本地跳跃提供函数。这些函数在c++程序中不可用
//#include<csignal>//为中断处理提供c样式支持

/*
//2.输入输出
#include<iostream>//支持标准流cin ，cout ，cerr 和clog 的输入输出，它还支持多字节字符标准流wcin， wcout ，wcerr ，wclog
#include<iomanip>//提供操纵程序，允许改变流的状态，从而改变输出的样式
#include<ios>//定义<iostream>的基类
#include<istream>//为管理输入流缓存区的输入定义模板类
#include<ostream>//为管理输出流缓存区的输出定义模板类
#include<sstream>//支持字符串的流输入输出
#include<fstream>//支持文件的流输入输出
#include<iosfwd>//为输入输出对象提供向前的声明
#include<streambuf>//支持流输入输出的缓存
#include<cstdio>//为标准流提供c样式的输入输出
#include<cwchar>//支持多字节字符的c样式输入输出
//3.诊断
#include<stdexcept>//定义标准异常。异常是处理错误的方式
#include<cassert>//定义断言宏，用于检查运行期间的情形
#include<cerrno>//支持c样式的错误信息

//4.一般工具
#include<ctime>//支持系统时钟函数
#include<utility>//定义重载的关系运算符，简化关系运算符的写入，它还定义了pair类型，该类型是一种模板类型，可以存储一对值。这些功能在库的其他地方使用
#include<functional>//定义了许多函数对象类型和支持函数对象的功能，函数对象是支持operator()()函数调用运算符的任意对象
#include<memory>//给容器，管理内存的函数和auto_ptr模板类定义标准内存分配器

//5.字符串
#include<string>//为字符串类提供支持和定义，包括多字节字符串（由char组成）的string和Unicode字符串（由wchar_t组成）
#include<cctype>//多字节字符类别
#include<cwctype>//Unicode字符类别
#include<cstring>//为处理非空字节序列和内存块提供函数。这不同于对应的标准c库头文件，几个c样式字符串的一般c库函数被返回值为const和非const的函数对替代了。
#include <cwchar>//为处理、执行I/O和转换字符序列提供函数，着不同于对应的标准c库头文件，几个Unicodec样式字符串操作的一般c库函数被返回值为const和非const的函数对替代了。
#include<cstdlib>//为把多字节字符串转换为数值，在多字节字符串和Unicode字符串之间提供转换函数

//6.容器
#include<vector>//定义vector序列模板，这是一个大小可重新设置的数组类型，比普通数组更安全更灵活
#include<list>//定义list模板序列，这是一个序列的链表，常常在任意位置插入和删除元素
#include<deque>//定义deque序列模板，支持在开始和结尾的高效插入和删除操作
#include<queue>//为队列（先进后出）数据结构定义序列适配器queue和priority_queue
#include<stack>//为堆栈（后进先出）数据结构定义序列适配器stack
#include<map>//map是一个关联容器类型，允许根据键值搜索值，其中键值是唯一的，且按照升序存储。Multimap类似于map，但键不必是唯一的
#include<set>//set是一个关联容器类型，用于以升序方式存储唯一值。multiset类似于set，但值不必是唯一的
#include<bitset>//为固定长度的位序列定义bitset模板，它可以看做固定长度的紧凑型bool数组

//7.迭代器支持
#include<iterator>//给迭代器提供定义和支持

//8.一般用途的算法
#include<algorithm>//提供一组基于算法的函数，包括置换，排序，合并和搜索
#include<cstdlib>//声明c标准库函数bsearch() 和qsort()，进行搜索和排序
#include<ciso646>//允许在代码中用and代替&&

//9.数值操作
#include<complex>//支持复数的定义和操作（？）
#include<valarray>//支持数值矢量的操作
#include<numeric>//在数值序列上定义一组一般数学操作，例如accumulate 和inner_product
#include<cmath>//这是c数学库，其中还附加了重载函数，以支持c++约定
#include<cstdlib>//提供的函数可以提取整数的绝对值，对整数进行取余数操作

//10.本地化
#include<locale>//提供的本地化包括字符类别，排列序列，以及货币和日期表示
#include<clocale>//对本地化提供c样式支持
*/
//LJ类库文件
#include "classes.h"
#include "Property.h"//属性
#include "XBase.h"//基类
#include "XTypes.h"//类型类
//#include "ThreadControl.h"//线程控制
#include "XTime.h"//时间类
#include "XRandom.h"//随机数类(其中调用了XTime::Now来初始化)
#include "Iterator.h"//迭代器
#include "XString.h"//字符串类
#include "XException.h"//异常类
#include "XArray.h"//数组类
//#include "XDelegate.h"//委托类型
#include "Equation\\stdafx.h"
//#include "sound\\stdafx.h"//（可选）
//#include "Game\\stdafx.h"//（可选）
//#include "NodeList\\stdafx.h"//（可选）
