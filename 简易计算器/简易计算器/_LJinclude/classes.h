#pragma once//��ֹ�ظ�����

//������Ҫ�������������������һ�£�ĳЩģ������⣩
namespace LJ
{
#if (_MANAGED == 1) || (_M_CEE == 1) //�й�֧��
#define _CLR//�Զ����һ���üǵı�ʶ����ʾ���й�����������ʱ֧�ֱ���
#include "gcroot.h"
	using namespace System;
	using System::Runtime::InteropServices::Marshal;//Marshal��
#endif

	//VS�汾����
#if _MSC_VER>=1600
#define _USE_RIGHT_VALUE_REFERENCE//��ֵ����
#else
#ifndef _CLR
#define nullptr 0
#endif
#endif
	/*
	MS VC++ 10.0 _MSC_VER = 1600��VS2010��
	MS VC++ 9.0 _MSC_VER = 1500
	MS VC++ 8.0 _MSC_VER = 1400
	MS VC++ 7.1 _MSC_VER = 1310
	MS VC++ 7.0 _MSC_VER = 1300
	MS VC++ 6.0 _MSC_VER = 1200
	MS VC++ 5.0 _MSC_VER = 1100
	*/
	//���������ʽΪclass+�ո�+����+;
	//����
	class XBase;

	//ֱ�Ӵ�XBase����

	//�쳣����
	class XException;
	//������
	class XTypes;
	//���ͽڵ�
	struct NodeOfRoot;
	struct NodeOfNamespace;
	struct NodeOfTemplate;
	struct NodeOfTemplateClass;
	struct NodeOfType;
	//��ʾʱ��
	class XTime;
	//��ʾһ�������
	class XRandom;

	//��������

	//��ʾһ�����������
	template<typename T>class XArray;
	//��ʾһ�����򼯺�����������
	template<typename T>class XCollection;
	//��ʾһ���ַ���
	class XString;
	//��ʾһ��ί��
	class XDelegates;
	//��ʾһ������
	class XActions;
	//��ʾһ������
	class XTask;

	//����������

	//��ʾһ���ַ����ı����ö����ṩ���ԵĲ�������������ֱ��ʹ�ã�
	class VString;
	//��ʾһ������
	template<typename T>class VArray;
	//��ʾһ�������
	class VBuffer;
	//��ʾһ�����򼯺�����
	template<typename T>class VCollection;
	//��ʾһ��ί�еı����ö��󣨲�Ӧֱ��ʹ�ã�
	struct IDelegate;
	//��ʾһ������ı����ö��󣨲�Ӧֱ��ʹ�ã�
	struct ITask;

	//��������

	//��ʾһ����̬����
	template<class T>class StaticProperty;
	//��ʾһ���߳�ͬ���Ŀ�����
	class ThreadControl;


}