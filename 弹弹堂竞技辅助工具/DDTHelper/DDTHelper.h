
// DDTHelper.h : PROJECT_NAME 应用程序的主头文件
//
#define sizeOFBigeyes 179//179is best for check 
#define timesOFBigeyes 5
#define colorCheckMiddle 60//128

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CDDTHelperApp:
// 有关此类的实现，请参阅 DDTHelper.cpp
//

class CDDTHelperApp : public CWinApp
{
public:
	CDDTHelperApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CDDTHelperApp theApp;