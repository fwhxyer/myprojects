
// DDTHelper.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//
#define sizeOFBigeyes 179//179is best for check 
#define timesOFBigeyes 5
#define colorCheckMiddle 60//128

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDDTHelperApp:
// �йش����ʵ�֣������ DDTHelper.cpp
//

class CDDTHelperApp : public CWinApp
{
public:
	CDDTHelperApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDDTHelperApp theApp;