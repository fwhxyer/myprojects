
// PeopleInOutList.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPeopleInOutListApp:
// �йش����ʵ�֣������ PeopleInOutList.cpp
//

class CPeopleInOutListApp : public CWinApp
{
public:
	CPeopleInOutListApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPeopleInOutListApp theApp;