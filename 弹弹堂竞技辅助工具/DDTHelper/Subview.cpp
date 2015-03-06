// Subview.cpp : 实现文件
//

#include "stdafx.h"
#include "DDTHelper.h"
#include "Subview.h"
#include "afxdialogex.h"


// Subview 对话框

IMPLEMENT_DYNAMIC(Subview, CDialog)

Subview::Subview(CWnd* pParent /*=NULL*/)
	: CDialog(Subview::IDD, pParent)
{

}

Subview::~Subview()
{
}

void Subview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Subview, CDialog)
END_MESSAGE_MAP()


// Subview 消息处理程序


BOOL Subview::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	
	// TODO: Add extra initialization here
	::SetWindowPos(this->m_hWnd,HWND_BOTTOM,2,0,GetSystemMetrics(SM_CXSCREEN)-2,GetSystemMetrics(SM_CYSCREEN)-2,SWP_NOZORDER);
	
SetWindowLong(this-> GetSafeHwnd(),GWL_EXSTYLE, 
GetWindowLong(this-> GetSafeHwnd(),GWL_EXSTYLE)^0x80000); 
HINSTANCE   hInst   =   LoadLibrary( "User32.DLL ");   
if(hInst)   
{   
typedef   BOOL   (WINAPI   *MYFUNC)(HWND,COLORREF,BYTE,DWORD);   
MYFUNC   fun   =   NULL; 
//取得SetLayeredWindowAttributes函数指针   
fun=(MYFUNC)GetProcAddress(hInst,   "SetLayeredWindowAttributes "); 
if(fun)fun(this-> GetSafeHwnd(),0,128,2);   
FreeLibrary(hInst);   
}

	return TRUE;  // return TRUE  unless you set the focus to a control
}