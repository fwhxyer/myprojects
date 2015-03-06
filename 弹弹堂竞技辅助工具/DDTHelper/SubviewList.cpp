// SubviewList.cpp : 实现文件
//

#include "stdafx.h"
#include "DDTHelper.h"
#include "SubviewList.h"
#include "afxdialogex.h"
#include "DDTHelperDlg.h"
/*
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

*/
// SubviewList 对话框

IMPLEMENT_DYNAMIC(SubviewList, CDialog)

SubviewList::SubviewList(CWnd* pParent /*=NULL*/)
	: CDialog(SubviewList::IDD, pParent)
{

	m_cs1 = _T("");
	//  m_cs2 = _T("");
	m_cs2 = _T("");
}

SubviewList::~SubviewList()
{
}

void SubviewList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListTable);
	DDX_Control(pDX, IDOK, m_bBehind);
	DDX_Control(pDX, IDCANCEL2, m_b2);
	DDX_Control(pDX, IDCANCEL3, m_b3);
	DDX_Control(pDX, IDCANCEL, m_b1);
	DDX_Control(pDX, IDC_BUTTON1, m_refresh);
	DDX_Control(pDX, IDC_CHECK1, m_q1);
	DDX_Control(pDX, IDC_CHECK10, m_qf);
	DDX_Control(pDX, IDC_CHECK11, m_qr);
	DDX_Control(pDX, IDC_CHECK12, m_qq);
	DDX_Control(pDX, IDC_CHECK13, m_qe);
	DDX_Control(pDX, IDC_CHECK14, m_qz);
	DDX_Control(pDX, IDC_CHECK15, m_qx);
	DDX_Control(pDX, IDC_CHECK16, m_qc);
	DDX_Control(pDX, IDC_CHECK2, m_q2);
	DDX_Control(pDX, IDC_CHECK9, m_qb);
	DDX_Control(pDX, IDC_CHECK3, m_q3);
	DDX_Control(pDX, IDC_CHECK4, m_q4);
	DDX_Control(pDX, IDC_CHECK5, m_q5);
	DDX_Control(pDX, IDC_CHECK6, m_q6);
	DDX_Control(pDX, IDC_CHECK7, m_q7);
	DDX_Control(pDX, IDC_CHECK8, m_q8);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Text(pDX, IDC_EDIT1, m_cs1);
	DDV_MaxChars(pDX, m_cs1, 3);
	DDX_Control(pDX, IDC_CHECK17, m_bool);
	//  DDX_Text(pDX, IDC_EDIT4, m_cs2);
	//  D//  DV_MaxChars(p//  DX, m_cs2, 2);
	DDX_Control(pDX, IDC_EDIT4, m_e4);
	DDX_Text(pDX, IDC_EDIT4, m_cs2);
	DDV_MaxChars(pDX, m_cs2, 3);
	DDX_Control(pDX, IDC_CHECK42, m_q42);
	DDX_Control(pDX, IDC_CHECK52, m_q52);
	DDX_Control(pDX, IDC_CHECK62, m_q62);
	DDX_Control(pDX, IDC_CHECK72, m_q72);
	DDX_Control(pDX, IDC_CHECK82, m_q82);
}


BEGIN_MESSAGE_MAP(SubviewList, CDialog)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDOK, &SubviewList::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &SubviewList::OnBnClickedCancel)
	ON_BN_CLICKED(IDCANCEL3, &SubviewList::OnBnClickedCancel3)
	ON_BN_CLICKED(IDCANCEL2, &SubviewList::OnBnClickedCancel2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &SubviewList::OnNMDblclkList1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &SubviewList::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &SubviewList::OnNMClickList1)
	ON_EN_CHANGE(IDC_EDIT1, &SubviewList::OnEnChangeEdit1)
	ON_EN_SETFOCUS(IDC_EDIT1, &SubviewList::OnEnSetfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &SubviewList::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &SubviewList::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &SubviewList::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &SubviewList::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &SubviewList::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &SubviewList::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &SubviewList::OnBnClickedButton8)
//	ON_WM_MOUSEACTIVATE()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCLBUTTONUP()
	ON_WM_MOUSEACTIVATE()
//	ON_WM_ACTIVATE()
ON_BN_CLICKED(IDC_BUTTON10, &SubviewList::OnBnClickedButton10)
ON_BN_CLICKED(IDC_BUTTON11, &SubviewList::OnBnClickedButton11)
ON_BN_CLICKED(IDC_BUTTON12, &SubviewList::OnBnClickedButton12)
ON_EN_CHANGE(IDC_EDIT4, &SubviewList::OnEnChangeEdit4)
ON_EN_SETFOCUS(IDC_EDIT4, &SubviewList::OnEnSetfocusEdit4)
ON_BN_CLICKED(IDC_BUTTON13, &SubviewList::OnBnClickedButton13)
ON_BN_CLICKED(IDC_BUTTON14, &SubviewList::OnBnClickedButton14)
ON_BN_CLICKED(IDC_BUTTON15, &SubviewList::OnBnClickedButton15)
ON_BN_CLICKED(IDC_BUTTON16, &SubviewList::OnBnClickedButton16)
END_MESSAGE_MAP()


// SubviewList 消息处理程序


BOOL SubviewList::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	::SetWindowPos(m_hWnd,HWND_NOTOPMOST,2,0,0,0,SWP_NOSIZE);

	//设置列数
	m_ListTable.InsertColumn(0,_T(("打击方式")),LVCFMT_LEFT,80);
	//m_ListTable.InsertColumn(1,_T(("角度")),LVCFMT_LEFT,74);
	//m_ListTable.InsertColumn(2,_T(("力度")),LVCFMT_LEFT,73);
	//m_ListTable.InsertColumn(3,_T(("误差")),LVCFMT_LEFT,75);
	m_ListTable.InsertColumn(4,_T(("角度(高差)")),LVCFMT_LEFT,74);
	m_ListTable.InsertColumn(5,_T(("力度(高差)")),LVCFMT_LEFT,73);
	
	myinit();

	boolBehind=0;

	m_bool.SetCheck(TRUE);
	OnBnClickedButton2();
	
	boolB1=0;
	boolB2=0;

	IEWnd = FindWindow("IEFrame", NULL);//Internet Explorer_Server
	if (!(IEWnd->GetSafeHwnd())) MessageBox("如需使用自动力功能请使用IE浏览器打开游戏后运行本程序！");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void SubviewList::myinit()
{
	//重置列数宽度
	m_ListTable.SetColumnWidth(0,80);
	m_ListTable.SetColumnWidth(1,74);
	m_ListTable.SetColumnWidth(2,73);
	m_ListTable.SetColumnWidth(3,75);
	m_ListTable.SetColumnWidth(4,74);
	m_ListTable.SetColumnWidth(5,73);
	m_ListTable.DeleteAllItems();
}

LRESULT SubviewList::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return HTCAPTION;//单击客户区域的任何地方都返回标题栏用以拖动程序
	//return CDialog::OnNcHitTest(point);
}


void SubviewList::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnOK();
	if (!boolBehind){
		UnVisual();
	}else{
		Visual();
	}
	Behind();
}

void SubviewList::Visual()
{
		SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|0x80000);
		typedef BOOL (WINAPI* FSetLayeredWindowAttributes)(HWND,COLORREF,BYTE,DWORD);
		FSetLayeredWindowAttributes setLayeredWindowAttributes;
		HINSTANCE hInst=LoadLibrary(_T("User32.dll"));
		setLayeredWindowAttributes=(FSetLayeredWindowAttributes)GetProcAddress(hInst,"SetLayeredWindowAttributes");
		if (setLayeredWindowAttributes)
		   setLayeredWindowAttributes(GetSafeHwnd(),RGB(0,0,0),255,2);
		FreeLibrary(hInst);
		m_ListTable.SetTextColor(RGB(0,0,0));
}

void SubviewList::UnVisual()
{
		SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|0x80000);
		typedef BOOL (WINAPI* FSetLayeredWindowAttributes)(HWND,COLORREF,BYTE,DWORD);
		FSetLayeredWindowAttributes setLayeredWindowAttributes;
		HINSTANCE hInst=LoadLibrary(_T("User32.dll"));
		setLayeredWindowAttributes=(FSetLayeredWindowAttributes)GetProcAddress(hInst,"SetLayeredWindowAttributes");
		if (setLayeredWindowAttributes)
		   setLayeredWindowAttributes(GetSafeHwnd(),RGB(0,0,0),200,2);
		FreeLibrary(hInst);
		m_ListTable.SetTextColor(RGB(255,0,0));
}

void SubviewList::Behind() 
{
	// TODO: Add your control notification handler code here
	//ChangeFocus(4);           这句话打断了Subview的进程，查错一天	
	CWnd *p=AfxGetApp()->GetMainWnd();
	CDDTHelperDlg *pd=(CDDTHelperDlg*)p;
	if (!boolBehind){
		SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		boolBehind=1;
		CString tmp="取消最前";
		m_bBehind.SetWindowText(tmp);
		m_ListTable.SetTextColor(RGB(255,0,0));
		pd->setRESListColor();
	}else{
		::SetWindowPos(m_hWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		boolBehind=0;
		CString tmp="总在最前";
		m_bBehind.SetWindowText(tmp);
		m_ListTable.SetTextColor(RGB(0,0,0));
		pd->setRESListColor();
	}
}

void SubviewList::OnBnClickedCancel3()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *p=AfxGetApp()->GetMainWnd();
	CDDTHelperDlg *pd=(CDDTHelperDlg*)p;
	pd->setCAboutDlg();
}


void SubviewList::OnBnClickedCancel2()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *p=AfxGetApp()->GetMainWnd();
	CDDTHelperDlg *pd=(CDDTHelperDlg*)p;
	pd->setColorDouble();
	
	if (!boolB2){
		boolB2=1;
		CString tmp="取消";
		m_b2.SetWindowText(tmp);
	}else{
		boolB2=0;
		CString tmp="二值化";
		m_b2.SetWindowText(tmp);
	}
}

void SubviewList::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnCancel();
	CWnd *p=AfxGetApp()->GetMainWnd();
	CDDTHelperDlg *pd=(CDDTHelperDlg*)p;
	pd->setColorCheck();
	
	if (!boolB1){
		boolB1=1;
		CString tmp="取消";
		m_b1.SetWindowText(tmp);
	}else{
		boolB1=0;
		CString tmp="抓点抓色";
		m_b1.SetWindowText(tmp);
	}
}

void SubviewList::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData();
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int   nItem=-1; 
	nItem   =   m_ListTable.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	CString   strSelectedFileName,strAngle; 
	if (nItem==0||nItem==2)
		strSelectedFileName=m_ListTable.GetItemText(nItem,   2   )   ; 
	else
		strSelectedFileName=m_ListTable.GetItemText(nItem,   2   )   ; 
	strAngle=m_ListTable.GetItemText(nItem,   1   )   ;
	int strength=atoi(strSelectedFileName);
	int angleNow=atoi(strAngle);
	*pResult   =   0;

	if (strength>0 && strength<=100)
		pressBlank(strength,angleNow);

	*pResult = 0;
}

void SubviewList::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{	//same as OnNMClickList1();
}

void SubviewList::pressBlank(int str,int angleNow)
{
	if (m_bool.GetCheck())
	{
		//CString tmp;
		//tmp.Format("%d",str);
		//MessageBox(tmp);

		/*HWND hwnd=::FindWindow(0, "文档1.txt - 记事本"); //假设你要找的窗口标题为“文档1” 
		CWnd::FromHandle(hwnd)->SetForegroundWindow(); 
		::PostMessage(hwnd, WM_KEYDOWN, VK_SPACE, 0L); //发送ESC按下的键盘消息
		*/
		//HWND GetForegroundWindow(VOID)
		//CWnd *pWnd=GetForegroundWindow();
		if (IEWnd->GetSafeHwnd()) 
		{ 
			  IEWnd->ShowWindow(SW_SHOWMAXIMIZED); 
			  IEWnd->SetForegroundWindow();
			  boolTimer1=str;boolTimer=1;

			  pressQuick();
			  
			  Sleep(100);

		  	  CWnd *p=AfxGetApp()->GetMainWnd();
		   	  CDDTHelperDlg *pd=(CDDTHelperDlg*)p;
			  CXTPWnd* tmpCDC=(pd->CreatCXTPWnd());

			  changeAngle(tmpCDC->getCDC(),angleNow);

			  tmpCDC->DestroyWindow();
			  
			  /*
			  Sleep(100);

			  tmpCDC=(pd->CreatCXTPWnd());

			  checkChangeAngle(tmpCDC->getCDC(),angleNow);

			  tmpCDC->DestroyWindow();
			  */
			  Sleep(200);

			  keybd_event(VK_SPACE, 0, 0, 0);
			  SetTimer(1,   40		,    NULL); 
			  //KEYEVENTF_KEYUP is in Timer

			  //MessageBox("开始了！");
		}
	}
}

void SubviewList::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//UpdateData();
	
	/*
	if (boolTimer){
		boolTimer=0;
		keybd_event(VK_SPACE, 0, 0, 0); 
		SetTimer(1,   boolTimer1*2000/50,   NULL); 
	}else{
		keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);  
		KillTimer(1);
	}
	*/
	Sleep(boolTimer1*2000/50);
	keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);  
	KillTimer(1);
	if	(	!( m_q1.GetCheck()&&m_q2.GetCheck() )	) OnBnClickedButton2();
	CDialog::OnTimer(nIDEvent);
}


void SubviewList::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_q1.GetCheck()) m_q1.SetCheck(FALSE);
	if (m_q2.GetCheck()) m_q2.SetCheck(FALSE);
	if (m_q3.GetCheck()) m_q3.SetCheck(FALSE);
	if (m_q4.GetCheck()) m_q4.SetCheck(FALSE);
	if (m_q5.GetCheck()) m_q5.SetCheck(FALSE);
	if (m_q6.GetCheck()) m_q6.SetCheck(FALSE);
	if (m_q7.GetCheck()) m_q7.SetCheck(FALSE);
	if (m_q8.GetCheck()) m_q8.SetCheck(FALSE);
	if (m_q42.GetCheck()) m_q42.SetCheck(FALSE);
	if (m_q52.GetCheck()) m_q52.SetCheck(FALSE);
	if (m_q62.GetCheck()) m_q62.SetCheck(FALSE);
	if (m_q72.GetCheck()) m_q72.SetCheck(FALSE);
	if (m_q82.GetCheck()) m_q82.SetCheck(FALSE);
	if (m_qb.GetCheck()) m_qb.SetCheck(FALSE);
	if (m_qf.GetCheck()) m_qf.SetCheck(FALSE);
	if (m_qr.GetCheck()) m_qr.SetCheck(FALSE);
	if (m_qq.GetCheck()) m_qq.SetCheck(FALSE);
	if (m_qe.GetCheck()) m_qe.SetCheck(FALSE);
	if (m_qz.GetCheck()) m_qz.SetCheck(FALSE);
	if (m_qx.GetCheck()) m_qx.SetCheck(FALSE);
	if (m_qc.GetCheck()) m_qc.SetCheck(FALSE);
}

void SubviewList::pressQuick(void)
{
	UpdateData(TRUE);
	if (m_qq.GetCheck()){keybd_event('Q', 0, 0, 0); keybd_event('Q', 0, KEYEVENTF_KEYUP, 0);  }
	if (m_qe.GetCheck()){keybd_event('E', 0, 0, 0); keybd_event('E', 0, KEYEVENTF_KEYUP, 0);  }
	if (m_qz.GetCheck()){keybd_event('Z', 0, 0, 0); keybd_event('Z', 0, KEYEVENTF_KEYUP, 0);  }
	if (m_qx.GetCheck()){keybd_event('X', 0, 0, 0); keybd_event('X', 0, KEYEVENTF_KEYUP, 0);  }
	if (m_qc.GetCheck()){keybd_event('C', 0, 0, 0); keybd_event('C', 0, KEYEVENTF_KEYUP, 0);  }
	if (m_qf.GetCheck()){keybd_event('F', 0, 0, 0); keybd_event('F', 0, KEYEVENTF_KEYUP, 0);  Sleep(100);}
	else if (m_qr.GetCheck()){keybd_event('R', 0, 0, 0); keybd_event('R', 0, KEYEVENTF_KEYUP, 0);  Sleep(100);}
	else if (!m_qq.GetCheck() || !m_qe.GetCheck())
	{
		if (m_qb.GetCheck()){keybd_event('B', 0, 0, 0); keybd_event('B', 0, KEYEVENTF_KEYUP, 0);  Sleep(100);}
		if (m_q1.GetCheck()){keybd_event('1', 0, 0, 0); keybd_event('1', 0, KEYEVENTF_KEYUP, 0);  }
		if (m_q2.GetCheck()){keybd_event('2', 0, 0, 0); keybd_event('2', 0, KEYEVENTF_KEYUP, 0);  }
		if (m_q3.GetCheck() && 
			!m_q1.GetCheck() ){keybd_event('3', 0, 0, 0); keybd_event('3', 0, KEYEVENTF_KEYUP, 0);  }
		if (m_q42.GetCheck()){keybd_event('4', 0, 0, 0); keybd_event('4', 0, KEYEVENTF_KEYUP, 0); 
							  keybd_event('4', 0, 0, 0); keybd_event('4', 0, KEYEVENTF_KEYUP, 0);  }
		if (m_q4.GetCheck()){keybd_event('4', 0, 0, 0); keybd_event('4', 0, KEYEVENTF_KEYUP, 0);  }
		if (m_q52.GetCheck()){keybd_event('5', 0, 0, 0); keybd_event('5', 0, KEYEVENTF_KEYUP, 0);  
							  keybd_event('5', 0, 0, 0); keybd_event('5', 0, KEYEVENTF_KEYUP, 0);  }
		if (m_q5.GetCheck()){keybd_event('5', 0, 0, 0); keybd_event('5', 0, KEYEVENTF_KEYUP, 0);  }
		if (m_q62.GetCheck()){keybd_event('6', 0, 0, 0); keybd_event('6', 0, KEYEVENTF_KEYUP, 0);  
							  keybd_event('6', 0, 0, 0); keybd_event('6', 0, KEYEVENTF_KEYUP, 0);  }
		if (m_q6.GetCheck()){keybd_event('6', 0, 0, 0); keybd_event('6', 0, KEYEVENTF_KEYUP, 0);  }
		if (m_q72.GetCheck()){keybd_event('7', 0, 0, 0); keybd_event('7', 0, KEYEVENTF_KEYUP, 0);  
							  keybd_event('7', 0, 0, 0); keybd_event('7', 0, KEYEVENTF_KEYUP, 0);  }
		if (m_q7.GetCheck()){keybd_event('7', 0, 0, 0); keybd_event('7', 0, KEYEVENTF_KEYUP, 0);  }
		if (m_q82.GetCheck()){keybd_event('8', 0, 0, 0); keybd_event('8', 0, KEYEVENTF_KEYUP, 0);  
							  keybd_event('8', 0, 0, 0); keybd_event('8', 0, KEYEVENTF_KEYUP, 0);  }
		if (m_q8.GetCheck()){keybd_event('8', 0, 0, 0); keybd_event('8', 0, KEYEVENTF_KEYUP, 0);  }
	}
}

void SubviewList::OnEnSetfocusEdit1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_e1.SetWindowText("");
}

void SubviewList::OnEnSetfocusEdit4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_e4.SetWindowText("");
}

void SubviewList::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	//  m_e2 范围越界
	double tmpD;
	tmpD=atof(m_cs1);
	if (tmpD>100)
	{
		CString tmp=m_cs1;
		tmp=tmp.Left(2);
		m_e1.SetWindowText(tmp);
	}else if (tmpD>0)
	{
		m_ListTable.SetItemText(20,2,m_cs1);
	}
}

void SubviewList::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	//  m_e2 范围越界
	double tmpD;
	tmpD=atof(m_cs2);
	if (tmpD>100)
	{
		CString tmp=m_cs2;
		tmp=tmp.Left(2);
		m_e4.SetWindowText(tmp);
	}else if (tmpD>0)
	{
		CWnd *p=AfxGetApp()->GetMainWnd();
		CDDTHelperDlg *pd=(CDDTHelperDlg*)p;
		/*
		Ctring tmp=m_cs2;
		tmp.Format("%1.0f",pd->getStrFromAngle(atof(m_cs2),pd->wind));
		*/
		pd->kR.angle=atof(m_cs2);
		pd->kR.Set(atof(m_cs2),pd->getStrFromAngle(atof(m_cs2),pd->wind));
		pd->calcRES(pd->wind);
		/*
		m_ListTable.SetItemText(20,1,m_cs2);
		if (atof(tmp)>100 || atof(tmp)<0)
			m_ListTable.SetItemText(20,2,"-1");
		else
			m_ListTable.SetItemText(20,2,tmp);
		*/
	}
}

void SubviewList::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码 
	OnBnClickedButton1();
	m_q3.SetCheck(TRUE);
	m_q42.SetCheck(TRUE);
	m_q5.SetCheck(TRUE);
	m_q6.SetCheck(TRUE);
	m_q7.SetCheck(TRUE);
	//m_q8.SetCheck(TRUE);
}


void SubviewList::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
	m_q1.SetCheck(TRUE);
	m_q42.SetCheck(TRUE);
	m_q5.SetCheck(TRUE);
	m_q6.SetCheck(TRUE);
	m_q7.SetCheck(TRUE);
	//m_q8.SetCheck(TRUE);
}


void SubviewList::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
	m_q1.SetCheck(TRUE);
	m_q2.SetCheck(TRUE);
	m_q7.SetCheck(TRUE);
	m_q8.SetCheck(TRUE);
}


void SubviewList::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
	m_q1.SetCheck(TRUE);
	m_qc.SetCheck(TRUE);
}


void SubviewList::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
	m_qf.SetCheck(TRUE);
	m_qz.SetCheck(TRUE);
}


void SubviewList::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
	m_qq.SetCheck(TRUE);
}


void SubviewList::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
	m_qx.SetCheck(TRUE);
}

void SubviewList::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
	m_q3.SetCheck(TRUE);
	m_q7.SetCheck(TRUE);
}

void SubviewList::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
	m_q3.SetCheck(TRUE);
	m_q6.SetCheck(TRUE);
}

void SubviewList::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
	m_q3.SetCheck(TRUE);
	m_q4.SetCheck(TRUE);
}

void SubviewList::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
	m_qr.SetCheck(TRUE);
}

void SubviewList::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_qb.GetCheck()) m_qb.SetCheck(FALSE);
	else m_qb.SetCheck(TRUE);
}

void SubviewList::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButton1();
	m_q42.SetCheck(TRUE);
	m_q4.SetCheck(TRUE);
	m_q52.SetCheck(TRUE);
	m_q5.SetCheck(TRUE);
	m_q62.SetCheck(TRUE);
	m_q6.SetCheck(TRUE);
	m_q72.SetCheck(TRUE);
	m_q7.SetCheck(TRUE);
	m_q82.SetCheck(TRUE);
	m_q8.SetCheck(TRUE);
}

void SubviewList::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_qe.GetCheck()) m_qe.SetCheck(FALSE);
	else m_qe.SetCheck(TRUE);
}

void SubviewList::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CWnd *p=AfxGetApp()->GetMainWnd();
	CDDTHelperDlg *pd=(CDDTHelperDlg*)p;
	pd->setFocusExforEDIT1();
	CDialog::OnNcLButtonUp(nHitTest, point);
}


void SubviewList::changeAngle(CDC* tmpCDC,int angleNow)
{
	CWnd *p=AfxGetApp()->GetMainWnd();
	CDDTHelperDlg *pd=(CDDTHelperDlg*)p;
	angleOld=pd->autoGetAngle(tmpCDC);
	if (angleOld==-255)
		angleOld=pd->autoGetAngle2(tmpCDC);
	if (angleOld==-255)
		angleOld=pd->autoGetAngle3(tmpCDC);
	if (angleOld==-255)
		angleOld=pd->autoGetAngle4(tmpCDC);
	if (angleOld!=-255){
		int correct=angleNow-angleOld;
		if (correct>0)
		{
			for (int i=0;i<correct;i++)
			{
				keybd_event(VK_UP, 0, 0, 0); keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
			}
		}else if (correct<0){
			for (int i=0;i>correct;i--)
			{
				keybd_event(VK_DOWN, 0, 0, 0); keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
			}
		}
	}
	CString tmp;tmp.Format("角度:%d",angleOld);
	pd->m_csState.SetWindowTextA(tmp);
}


void SubviewList::checkChangeAngle(CDC* tmpCDC,int angleNow)
{
	CWnd *p=AfxGetApp()->GetMainWnd();
	CDDTHelperDlg *pd=(CDDTHelperDlg*)p;
	angleOld=pd->autoGetAngle(tmpCDC);
	if (angleOld==-255)
		angleOld=pd->autoGetAngle2(tmpCDC);
	if (angleOld==-255)
		angleOld=pd->autoGetAngle3(tmpCDC);
	if (angleOld==-255)
		angleOld=pd->autoGetAngle4(tmpCDC);
	if (angleOld!=-255){
		if (angleOld!=angleNow){
			boolTimer1=int(pd->getStrFromAngle(angleOld,pd->wind));
			CString tmp;
			if (100>=boolTimer1&&boolTimer1>0){
				tmp.Format("%d",angleOld);
				m_ListTable.SetItemText(20,1,tmp);
				tmp.Format("%d",boolTimer1);
				m_ListTable.SetItemText(20,2,tmp);
				tmp.Format("极限:%d",angleOld);
				pd->kR.Set(angleOld,boolTimer1,77);
				pd->kR.Set(angleOld,boolTimer1);
				//pd->calcRES(0);
			}else
			{
				tmp.Format("极限不可达");
				keybd_event('P', 0, 0, 0); keybd_event('P', 0, KEYEVENTF_KEYUP, 0);
			}
			pd->m_csState.SetWindowTextA(tmp);
		}
	}
}

