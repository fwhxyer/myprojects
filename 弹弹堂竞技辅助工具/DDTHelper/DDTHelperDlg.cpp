
// DDTHelperDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DDTHelper.h"
#include "DDTHelperDlg.h"
#include "afxdialogex.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEWF
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

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
public:
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CDDTHelperDlg 对话框



CDDTHelperDlg::CDDTHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDDTHelperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_cs1 = _T("");
	m_cs2 = _T("");
	m_cs3 = _T("");
	boolOfCalc = 0;
	boolOfBigeyes = 0;
	boolOfOnBigeyes = 0;
	//  boolOfBehind = 0;
	//  boolOfWind = 0;
	boolBehind = 0;
	boolWind = 0;
	boolColorCheck =0;
	boolColorDouble =0;
	boolViewMode =1;
	m_Dragging = 0;
	anglePos=CPoint(186,680);
}

void CDDTHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_EDIT3, m_e3);
	DDX_Text(pDX, IDC_EDIT1, m_cs1);
	DDV_MaxChars(pDX, m_cs1, 1);
	DDX_Text(pDX, IDC_EDIT2, m_cs2);
	DDV_MaxChars(pDX, m_cs2, 1);
	DDX_Text(pDX, IDC_EDIT3, m_cs3);
	DDV_MaxChars(pDX, m_cs3, 4);
	DDX_Control(pDX, IDC_STATIC1, m_csState);
	DDX_Control(pDX, IDC_STATIC2, m_csCalc);
	//  DDX_Control(pDX, IDC_STATICd, m_staticDot);
	DDX_Control(pDX, IDC_BUTTON5, m_b1);
	DDX_Control(pDX, IDC_BUTTON2, m_bBehind);
	DDX_Control(pDX, IDC_BUTTON1, m_b2);
	DDX_Control(pDX, IDC_BUTTON4, m_b4);
	DDX_Control(pDX, IDC_BUTTON3, m_b5);
	DDX_Control(pDX, IDC_BUTTON6, m_b6);
	DDX_Control(pDX, IDC_BUTTON7, m_b7);
}

BEGIN_MESSAGE_MAP(CDDTHelperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BUTTON1, &CDDTHelperDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDDTHelperDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDDTHelperDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDDTHelperDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDDTHelperDlg::OnBnClickedButton5)
	ON_EN_SETFOCUS(IDC_EDIT1, &CDDTHelperDlg::OnEnSetfocusEdit1)
	ON_EN_SETFOCUS(IDC_EDIT2, &CDDTHelperDlg::OnEnSetfocusEdit2)
	ON_EN_SETFOCUS(IDC_EDIT3, &CDDTHelperDlg::OnEnSetfocusEdit3)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_EN_CHANGE(IDC_EDIT1, &CDDTHelperDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CDDTHelperDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CDDTHelperDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON6, &CDDTHelperDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDDTHelperDlg::OnBnClickedButton7)
	ON_STN_CLICKED(IDC_STATIC1, &CDDTHelperDlg::OnStnClickedStatic1)
END_MESSAGE_MAP()


// CDDTHelperDlg 消息处理程序

BOOL CDDTHelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	if (boolViewMode==1){
		::SetWindowPos(m_hWnd,HWND_NOTOPMOST,GetSystemMetrics(SM_CXSCREEN)-130,240,0,0,SWP_NOSIZE);
	}else
		::SetWindowPos(m_hWnd,HWND_NOTOPMOST,26,1,0,0,SWP_NOSIZE);

	
	if (boolViewMode==1){
		m_editFont.CreatePointFont(300, "宋体"); 
	}else{
		m_editFont.CreatePointFont(350, "宋体"); 
	}
	m_b1.SetFont(&m_editFont); // 设置新字体
	//m_staticDot.SetFont(&m_editFont);// 设置风力中间点的字体 //已于VS2010版舍弃
	
	m_defaultFont.CreatePointFont(500, "宋体"); 
	if (boolViewMode==1){
	m_e1.SetFont(&m_defaultFont); // 设置新字体
	}else
	m_e1.SetFont(&m_defaultFont); // 设置新字体
	if (boolViewMode==1){
	m_e2.SetFont(&m_defaultFont); // 设置新字体
	}else
	m_e2.SetFont(&m_defaultFont); // 设置新字体
	
	if (boolViewMode==1){
		m_staticFont.CreatePointFont(115, "宋体"); 
	}else{
		m_staticFont.CreatePointFont(150, "宋体");
	}
	m_b4.SetFont(&m_staticFont); // 设置新字体
	//m_b6.SetFont(&m_staticFont); // 设置新字体
	m_csState.SetFont(&m_staticFont); // 设置新字体

	pDlgSL=CreatSubviewList();

	myinit();

	//pDlg=CreatSubview();
	//pDlg->PostNcDestroy();

	GetDlgItem(IDC_EDIT1)->SetFocus();
	return FALSE;
	// 除非将焦点设置到控件，否则返回 TRUE
}
void CDDTHelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		/*
		//关于 窗口的响应函数
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
		*/
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CDDTHelperDlg::setCAboutDlg()	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}

void CDDTHelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDDTHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



LRESULT CDDTHelperDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return HTCAPTION;//单击客户区域的任何地方都返回标题栏用以拖动程序
	//return CDialog::OnNcHitTest(point);
}

void CDDTHelperDlg::Visual()
{
		SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|0x80000);
		typedef BOOL (WINAPI* FSetLayeredWindowAttributes)(HWND,COLORREF,BYTE,DWORD);
		FSetLayeredWindowAttributes setLayeredWindowAttributes;
		HINSTANCE hInst=LoadLibrary(_T("User32.dll"));
		setLayeredWindowAttributes=(FSetLayeredWindowAttributes)GetProcAddress(hInst,"SetLayeredWindowAttributes");
		if (setLayeredWindowAttributes)
		   setLayeredWindowAttributes(GetSafeHwnd(),RGB(0,1,0),255,2);
		FreeLibrary(hInst);
		pDlgSL->m_ListTable.SetTextColor(RGB(0,0,0));
		setRES(aR,bR,cR,dR,eR,fR,gR,hR,iR,jR,kR);
}

void CDDTHelperDlg::UnVisual()
{
		SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|0x80000);
		typedef BOOL (WINAPI* FSetLayeredWindowAttributes)(HWND,COLORREF,BYTE,DWORD);
		FSetLayeredWindowAttributes setLayeredWindowAttributes;
		HINSTANCE hInst=LoadLibrary(_T("User32.dll"));
		setLayeredWindowAttributes=(FSetLayeredWindowAttributes)GetProcAddress(hInst,"SetLayeredWindowAttributes");
		if (setLayeredWindowAttributes)
		   setLayeredWindowAttributes(GetSafeHwnd(),RGB(0,0,255),255,2);
		FreeLibrary(hInst);
		pDlgSL->m_ListTable.SetTextColor(RGB(255,0,0));
		setRES(aR,bR,cR,dR,eR,fR,gR,hR,iR,jR,kR);
}

void CDDTHelperDlg::Behind() 
{
	// TODO: Add your control notification handler code here
	//ChangeFocus(4);           这句话打断了Subview的进程，查错一天	
	GetDlgItem(IDC_EDIT1)->SetFocus();
	if (!boolBehind){
		SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		boolBehind=1;
		CString tmp="取消最前";
		m_bBehind.SetWindowText(tmp);
	}else{
		::SetWindowPos(m_hWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		boolBehind=0;
		CString tmp="总在最前";
		m_bBehind.SetWindowText(tmp);
	}
}

void CDDTHelperDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	myinit();
	GetDlgItem(IDC_EDIT1)->SetFocus();
}


void CDDTHelperDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	//ChangeFocus(4);           这句话打断了Subview的进程，查错一天	
	if (!boolBehind){
		UnVisual();
	}else{
		Visual();
	}
	Behind();
	pDlgSL->OnBnClickedOk();
}


void CDDTHelperDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!boolOfBigeyes){
		boolOfBigeyes=1;
		CString tmp="裸眼";
		m_b5.SetWindowText(tmp);
	}else{
		boolOfBigeyes=0;
		CString tmp="放大镜";
		m_b5.SetWindowText(tmp);
	}
	GetDlgItem(IDC_EDIT1)->SetFocus();
}


void CDDTHelperDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	this->SetCapture();
	Behind();
	CString tmp="";
	tmp.Format("开始测屏距");
	if (boolViewMode==1){
	}else
	m_csState.SetFont(&m_editFont); // 设置新字体
	m_csState.SetWindowText(tmp);
	pDlg=CreatSubview();
	if(boolOfBigeyes) pWnd=CreatCXTPWnd();
	boolOfCalc=1;
	boolOfOnBigeyes=1;
	//dcDesktop.MoveTo(m_p1.x,m_p1.y);
	//dcDesktop.LineTo(m_p2.x,m_p2.y);

	calcScreen=0;

}


void CDDTHelperDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	this->SetCapture();
	Behind();
	CString tmp="";
	tmp.Format("开始测距");
	if (boolViewMode==1){
	}else
	m_csState.SetFont(&m_editFont); // 设置新字体
	m_csState.SetWindowText(tmp);
	pDlg=CreatSubview();
	if(boolOfBigeyes) pWnd=CreatCXTPWnd();
	boolOfCalc=2;
	boolOfOnBigeyes=1;
}

void CDDTHelperDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	this->SetCapture();
	Behind();
	CString tmp="";
	tmp.Format("开始测风力");
	if (boolViewMode==1){
	}else
	m_csState.SetFont(&m_editFont); // 设置新字体
	m_csState.SetWindowText(tmp);
	pDlg=CreatSubview();
	if(boolOfBigeyes) pWnd=CreatCXTPWnd();
	boolOfCalc=5;
	boolOfOnBigeyes=1;
	//dcDesktop.MoveTo(m_p1.x,m_p1.y);
	//dcDesktop.LineTo(m_p2.x,m_p2.y);

}

void CDDTHelperDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	this->SetCapture();
	Behind();
	CString tmp="";
	tmp.Format("开始测角度");
	if (boolViewMode==1){
	}else
	m_csState.SetFont(&m_editFont); // 设置新字体
	m_csState.SetWindowText(tmp);
	pDlg=CreatSubview();
	if(boolOfBigeyes) pWnd=CreatCXTPWnd();
	boolOfCalc=6;
	boolOfOnBigeyes=1;
	//dcDesktop.MoveTo(m_p1.x,m_p1.y);
	//dcDesktop.LineTo(m_p2.x,m_p2.y);
}

void CDDTHelperDlg::myinit()
{
	CString tmp="";
	m_e1.SetWindowText(tmp);
	m_e2.SetWindowText(tmp);
	pDlgSL->myinit();
	/*
	aR.Set(80,94,0,0);
	bR.Set(65,56,0);
	cR.Set(50,48,0.2);
	dR.Set(30,48,-0.2);
	eR.Set(6,100,0);
	fR.Set(100,96,-0.2,0);
	gR.Set(70,60,77);
	hR.Set(20,54,0);
	iR.Set(50,41,77);
	jR.Set(23,41,77);
	*/
	
	checkType=1;
	screenDir=0;
	boolBehind=0;
	boolWind=0;
	boolOfCalc=0;
	boolOfBigeyes=1;//默认打开放大镜
	boolOfOnBigeyes=0;
	calcHuman=100;//设置距离
	calcScreen=100;//设置距离
	calc1=1;
	calc2=0;
	wind=0;
	tmp.Format("屏距:%1.1f\n高差:%1.0f\n人物:%1.0f\n屏距:%1.0f",calc1*10,calc2*10,calcHuman,calcScreen);
	m_csCalc.SetWindowText(tmp);
	//pDlg->PostNcDestroy();
	tmp="风力:0.0 ";
	kR.angle=0;
	m_csState.SetWindowText(tmp);

	calcRES(0);
}

void CDDTHelperDlg::setRES(Res a,Res b,Res c,Res d,Res e,Res f,Res g,Res h,Res iR,Res jR,Res kR)
{
	pDlgSL->m_ListTable.DeleteAllItems();
	//添加数据
	int iItem;	
	//iItem = pDlgSL->m_ListTable.InsertItem(0," ");
	iItem = pDlgSL->m_ListTable.InsertItem(1,"94力高抛");
	pDlgSL->m_ListTable.SetItemText(iItem,1,a.angleCS);
	pDlgSL->m_ListTable.SetItemText(iItem,2,a.strengthCS);	
	pDlgSL->m_ListTable.SetItemText(iItem,3,a.accuracyCS);	
	//pDlgSL->m_ListTable.SetItemText(iItem,1,a.angleHighCS);
	//pDlgSL->m_ListTable.SetItemText(iItem,2,a.strengthHighCS);	
	iItem = pDlgSL->m_ListTable.InsertItem(2," ");
	iItem = pDlgSL->m_ListTable.InsertItem(3,"94力背抛");
	pDlgSL->m_ListTable.SetItemText(iItem,1,f.angleCS);
	pDlgSL->m_ListTable.SetItemText(iItem,2,f.strengthCS);	
	pDlgSL->m_ListTable.SetItemText(iItem,3,f.accuracyCS);	
	//pDlgSL->m_ListTable.SetItemText(iItem,1,f.angleHighCS);
	//pDlgSL->m_ListTable.SetItemText(iItem,2,f.strengthHighCS);	
	iItem = pDlgSL->m_ListTable.InsertItem(4," ");
	iItem = pDlgSL->m_ListTable.InsertItem(5,"62力半抛");
	//pDlgSL->m_ListTable.SetItemText(iItem,1,g.angleCS);
	//pDlgSL->m_ListTable.SetItemText(iItem,2,g.strengthCS);	
	//pDlgSL->m_ListTable.SetItemText(iItem,3,g.accuracyCS);
	pDlgSL->m_ListTable.SetItemText(iItem,1,g.angleHighCS);
	pDlgSL->m_ListTable.SetItemText(iItem,2,g.strengthHighCS);	
	iItem = pDlgSL->m_ListTable.InsertItem(6," ");
	iItem = pDlgSL->m_ListTable.InsertItem(7,"41力小抛");
	//pDlgSL->m_ListTable.SetItemText(iItem,1,iR.angleCS);
	//pDlgSL->m_ListTable.SetItemText(iItem,2,iR.strengthCS);	
	//pDlgSL->m_ListTable.SetItemText(iItem,3,iR.accuracyCS);	
	pDlgSL->m_ListTable.SetItemText(iItem,1,iR.angleHighCS);
	pDlgSL->m_ListTable.SetItemText(iItem,2,iR.strengthHighCS);		
	iItem = pDlgSL->m_ListTable.InsertItem(8," ");
	iItem = pDlgSL->m_ListTable.InsertItem(9,"63度埋人");
	//pDlgSL->m_ListTable.SetItemText(iItem,1,b.angleCS);
	//pDlgSL->m_ListTable.SetItemText(iItem,2,b.strengthCS);	
	//pDlgSL->m_ListTable.SetItemText(iItem,3,b.accuracyCS);	
	pDlgSL->m_ListTable.SetItemText(iItem,1,b.angleHighCS);
	pDlgSL->m_ListTable.SetItemText(iItem,2,b.strengthHighCS);	
	iItem = pDlgSL->m_ListTable.InsertItem(10," ");
	iItem = pDlgSL->m_ListTable.InsertItem(11,"50度定角");
	//pDlgSL->m_ListTable.SetItemText(iItem,1,c.angleCS);
	//pDlgSL->m_ListTable.SetItemText(iItem,2,c.strengthCS);	
	//pDlgSL->m_ListTable.SetItemText(iItem,3,c.accuracyCS);	
	pDlgSL->m_ListTable.SetItemText(iItem,1,c.angleHighCS);
	pDlgSL->m_ListTable.SetItemText(iItem,2,c.strengthHighCS);	
	iItem = pDlgSL->m_ListTable.InsertItem(12," ");
	iItem = pDlgSL->m_ListTable.InsertItem(13,"30度定角");
	//pDlgSL->m_ListTable.SetItemText(iItem,1,d.angleCS);
	//pDlgSL->m_ListTable.SetItemText(iItem,2,d.strengthCS);	
	//pDlgSL->m_ListTable.SetItemText(iItem,3,d.accuracyCS);	
	pDlgSL->m_ListTable.SetItemText(iItem,1,d.angleHighCS);
	pDlgSL->m_ListTable.SetItemText(iItem,2,d.strengthHighCS);	
	iItem = pDlgSL->m_ListTable.InsertItem(14," ");
	iItem = pDlgSL->m_ListTable.InsertItem(15,"23度火炬");
	pDlgSL->m_ListTable.SetItemText(iItem,1,jR.angleHighCS);
	pDlgSL->m_ListTable.SetItemText(iItem,2,jR.strengthHighCS);	
	iItem = pDlgSL->m_ListTable.InsertItem(16," ");
	iItem = pDlgSL->m_ListTable.InsertItem(17,"20度定角");
	//pDlgSL->m_ListTable.SetItemText(iItem,1,h.angleCS);
	//pDlgSL->m_ListTable.SetItemText(iItem,2,h.strengthCS);	
	//pDlgSL->m_ListTable.SetItemText(iItem,3,h.accuracyCS);	
	pDlgSL->m_ListTable.SetItemText(iItem,1,h.angleHighCS);
	pDlgSL->m_ListTable.SetItemText(iItem,2,h.strengthHighCS);	
	iItem = pDlgSL->m_ListTable.InsertItem(18," ");
	iItem = pDlgSL->m_ListTable.InsertItem(19,"满力直射");
	//pDlgSL->m_ListTable.SetItemText(iItem,1,e.angleCS);
	//pDlgSL->m_ListTable.SetItemText(iItem,2,e.strengthCS);	
	//pDlgSL->m_ListTable.SetItemText(iItem,3,e.accuracyCS);	
	pDlgSL->m_ListTable.SetItemText(iItem,1,e.angleHighCS);
	pDlgSL->m_ListTable.SetItemText(iItem,2,e.strengthHighCS);	
	iItem = pDlgSL->m_ListTable.InsertItem(20," ");
	iItem = pDlgSL->m_ListTable.InsertItem(21,"自定义");
	pDlgSL->m_ListTable.SetItemText(iItem,1,kR.angleHighCS);
	pDlgSL->m_ListTable.SetItemText(iItem,2,kR.strengthHighCS);	
	pDlgSL->m_ListTable.SetExtendedStyle(LVS_EX_FULLROWSELECT); //选中一整行
}

void CDDTHelperDlg::calcRES1(double wind)
{
	aR.angle=90-calc1*10+2*wind;
	if (calc1>2.08) aR.angle-=1.9;
	else if (calc1>1.93) aR.angle-=1.35;
	else if (calc1>1.68) aR.angle-=0.85;
	else if (calc1>1.43) aR.angle-=0.5;
	else if (calc1>1.23) aR.angle-=0.2;
	else if (calc1>1.13) aR.angle-=0.1;
	double tmp=aR.angle-(int)aR.angle;
	if (tmp>=0.5) tmp-=1;
	tmp*=-1;//力度与高抛角小数位成正相关
	aR.strength=94+tmp*3.6;
	tmp=aR.strength-int(aR.strength);
	if (tmp>=0.5) tmp-=1;//精确度与力度小数位负相关
	aR.accuracy=tmp;
	aR.Set(aR.angle,aR.strength,aR.accuracy,0);
	if (getStrFromAngle(aR.angle,wind)<=100)
		aR.Set(aR.angle,getStrFromAngle(aR.angle,wind));
	else
		aR.Set(aR.angle-2,getStrFromAngle(aR.angle-2,wind));
}

void CDDTHelperDlg::calcRES2(double wind)
{
	bR.angle=65+2*wind;
	double tmp=bR.angle-int(bR.angle);
	if (tmp>=0.5) tmp-=1;
	tmp*=-1;//力度与65变角小数位成正相关
	/*
	bR.strength=94+tmp*4;
	tmp=bR.strength-int(bR.strength);
	if (tmp>=0.5) tmp-=1;//精确度与力度小数位负相关
	bR.accuracy=tmp;
	*/
	double strengths[]={0,13,21,26,32,37,41,44,49,53,56,59,62,65,68,71,74,77,80,83,86
		,87.5,89,91,93,94.5,96,97.5,98.5,99,99.5,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
	bR.strength=(1-calc1*10+int(calc1*10))*strengths[int(calc1*10)]+(calc1*10-int(calc1*10))*strengths[int(calc1*10)+1];
	bR.strength+=tmp*3;//此处系数是否为3暂不可知
	if (calc1>2.2) bR.strength+=2;
	else if (calc1>1.93) bR.strength+=1.5;
	else if (calc1>1.63) bR.strength+=1;
	else if (calc1>1.53) bR.strength+=0.5;
	if (int(calc1*10)>19) 
		bR.accuracy=77;//大于20屏距精确度不明
	else
		bR.accuracy=0;
	//bR.Set(bR.angle,bR.strength,bR.accuracy);
	//这句用作65度变角力度
	bR.Set(63,getStrFromAngle(63,wind),0);

	double correct=0;
	if (calc1>2.2) correct+=6;
	else if (calc1>1.93) correct+=4.5;
	else if (calc1>1.63) correct+=3;
	else if (calc1>1.53) correct+=1.5;
	else if (calc1>1.28) correct+=0.5;
	else if (calc1>0.98) correct+=0;

	bR.Set(63,getStrFromAngle(63,wind)+correct);
	/*
	if (bR.angle<68)
		bR.Set(bR.angle,getStrFromAngle(bR.angle,wind));
	else
		bR.Set(68,getStrFromAngle(68,wind));
	*/
}

void CDDTHelperDlg::calcRES3(double wind)
{
	cR.angle=50;
	double strengths[]={0,14.1,20.1,24.8,28.8,32.5,35.9,39,42,44.9,48.3,50.5,53,55.5,58,60.5,63.0,65.5,68,70,72.5
		,75,77.5,79,81,83,86,88.5,91,93,95,97,98.5,99.4,100,100,100,100,100,100,100,100,100,100,100,100,100};
	cR.strength=(1-calc1*10+int(calc1*10))*strengths[int(calc1*10)]+(calc1*10-int(calc1*10))*strengths[int(calc1*10)+1];
	if (calc1<0.5)		cR.strength-=wind*0.75;
	else if	(calc1<1)	cR.strength-=wind*1;
	else if	(calc1<1.5)	cR.strength-=wind*1.25;
	else if	(calc1<2)	cR.strength-=wind*1.9;
	else	cR.strength-=wind*2.0;
	double tmp=cR.strength-int(cR.strength);
	if (tmp>=0.5) tmp-=1;//精确度与力度小数位负相关
	cR.accuracy=tmp;//精确度未验证
	if (calc1>1.9) cR.accuracy=77;
	cR.Set(cR.angle,cR.strength,cR.accuracy);
	cR.Set(50,getStrFromAngle(50,wind));
}

void CDDTHelperDlg::calcRES4(double wind)
{
	dR.angle=30;
	double strengths[]={0,14,20,24.7,28.7,32.3,35.7,38.8,41.8,44.7,47.5,50.2,52.8,55.3,57.9,60.3,62.7,65.7,67.5,69.8,72.1
		,74.8,77.5,79,81,83,86,88.5,91,93,95,97,98.5,99.4,100,100,100,100,100,100,100,100,100,100,100,100,100};
	dR.strength=(1-calc1*10+int(calc1*10))*strengths[int(calc1*10)]+(calc1*10-int(calc1*10))*strengths[int(calc1*10)+1];
	if (calc1<0.5)	{}
	else if	(calc1<1)	dR.strength-=wind*0.5;
	else if	(calc1<1.5)	dR.strength-=wind*0.75;
	else if	(calc1<2)	dR.strength-=wind*1.0;
	else	dR.strength-=wind*1.3;
	double tmp=dR.strength-int(dR.strength);
	if (tmp>=0.5) tmp-=1;//精确度与力度小数位负相关
	dR.accuracy=tmp;//精确度未验证
	if (calc1>1.9) cR.accuracy=77;
	dR.Set(dR.angle,dR.strength,dR.accuracy);
	dR.Set(30,getStrFromAngle(30,wind));
}

void CDDTHelperDlg::calcRES5(double wind)
{
	eR.angle=calc1*6;
	double tmp=eR.angle-int(eR.angle);
	if (tmp<-0.25||tmp>0.25) 
		//eR.accuracy=77;
		eR.accuracy=0;
	else eR.accuracy=0;//平射能准确射到整数屏距  //本行在VS2010版本中被忽略
	eR.strength=100;
	eR.Set(eR.angle,eR.strength,eR.accuracy);
	eR.angleHigh=calc1*6+calc2*3+atan(calc2/calc1)*sizeOFBigeyes/3.141592653;
	if (eR.angleHigh>90||eR.angleHigh<-90)
		eR.Set(0,0);
	else
		eR.Set(eR.angleHigh,eR.strength);
}

void CDDTHelperDlg::calcRES6(double wind)
{
	fR.angle=90+(calc1+0.0483)*10-2*wind;
	if (calc1>2.08) aR.angle+=1.9;
	else if (calc1>1.93) aR.angle+=1.35;
	else if (calc1>1.68) aR.angle+=0.85;
	else if (calc1>1.43) aR.angle+=0.5;
	else if (calc1>1.23) aR.angle+=0.2;
	else if (calc1>1.13) aR.angle+=0.1;
	double tmp=fR.angle-int(fR.angle);
	if (tmp>=0.5) tmp-=1;//力度与背抛角小数位成负相关
	fR.strength=94+tmp*3.6;
	tmp=fR.strength-int(fR.strength);
	if (tmp>=0.5) tmp-=1;//精确度与力度小数位负相关
	fR.accuracy=tmp;
	fR.Set(fR.angle,fR.strength,fR.accuracy,0);
	fR.angle-=2*0.483;
	if (getStrFromAngle(180-fR.angle,wind)<=100)
		fR.Set(fR.angle,getStrFromAngle(180-fR.angle,wind));
	else
		fR.Set(fR.angle-2,getStrFromAngle(180-fR.angle-2,wind));
}

void CDDTHelperDlg::calcRES7(double wind)
{
	gR.angle=90-calc1*20+2*wind;
	double tmp=gR.angle-int(gR.angle);
	if (tmp>=0.5) tmp-=1;
	tmp*=-1;//力度与半抛角小数位成正相关
	gR.strength=60+tmp*4;//此处系数是否为4暂不可知
	tmp=gR.strength-int(gR.strength);
	if (tmp>=0.5) tmp-=1;//精确度与力度小数位负相关
	if (calc1<1)
		gR.accuracy=tmp;
	else
		gR.accuracy=77;//大于一屏不靠谱
	gR.Set(gR.angle,gR.strength,gR.accuracy);
	gR.Set(gR.angle,getStrFromAngle(gR.angle,wind));
}

void CDDTHelperDlg::calcRES8(double wind)
{
	hR.angle=20;
	double strengths[]={0,10,19,25,30,36,40,44,48,51,54,57,60,63,66,69,72,74,76,78,80
		,82,84,86,88,90,92,94,96,98,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
	hR.strength=(1-calc1*10+int(calc1*10))*strengths[int(calc1*10)]+(calc1*10-int(calc1*10))*strengths[int(calc1*10)+1];
	if (calc1<0.5)	{}
	else if	(calc1<1)	hR.strength-=wind*0.25;
	else if	(calc1<1.5)	hR.strength-=wind*0.50;
	else if	(calc1<2)	hR.strength-=wind*0.75;
	else	hR.strength-=wind*1;
	double tmp=hR.strength-int(hR.strength);
	if (tmp>=0.5) tmp-=1;//精确度与力度小数位负相关
	hR.accuracy=tmp;//精确度未验证
	if (calc1>1.9) cR.accuracy=77;
	hR.Set(hR.angle,hR.strength,hR.accuracy);
	hR.Set(20,getStrFromAngle(20,wind));
}

void CDDTHelperDlg::calcRES9(double wind)
{
	iR.angle=90-calc1*40+2*wind;
	if (calc1>2.2) iR.angle-=1;
	else if (calc1>1.93) iR.angle-=0.75;
	else if (calc1>1.63) iR.angle-=0.5;
	else if (calc1>1.53) iR.angle-=0.2;
	double tmp=iR.angle-int(iR.angle);
	if (tmp>=0.5) tmp-=1;
	tmp*=-1;//力度与小抛角小数位成正相关
	iR.strength=41+tmp*4;
	tmp=iR.strength-int(iR.strength);
	if (tmp>=0.5) tmp-=1;//精确度与力度小数位负相关
	if (calc1>0.5)
		iR.accuracy=77;//大于半屏不靠谱
	else
		iR.accuracy=tmp;
	iR.Set(iR.angle,iR.strength,iR.accuracy);
	iR.Set(iR.angle,getStrFromAngle(iR.angle,wind));
}

void CDDTHelperDlg::calcRES10(double wind)
{
	jR.angle=23;
	jR.strength=getStrFromAngle(jR.angle,wind);
	jR.accuracy=77;
	jR.Set(jR.angle,jR.strength,jR.accuracy);
	jR.Set(jR.angle,getStrFromAngle(jR.angle,wind));
}

void CDDTHelperDlg::calcRES11(double wind)
{
	kR.strength=getStrFromAngle(kR.angle,wind);
	kR.accuracy=77;
	kR.Set(kR.angle,kR.strength,kR.accuracy);
	kR.Set(kR.angle,getStrFromAngle(kR.angle,wind));
}

void CDDTHelperDlg::OnEnSetfocusEdit1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_e1.SetWindowText("");
}


void CDDTHelperDlg::OnEnSetfocusEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_e2.SetWindowText("");
}


void CDDTHelperDlg::OnEnSetfocusEdit3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_e3.SetWindowText("");
}


void CDDTHelperDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (boolOfBigeyes && boolOfOnBigeyes)
	{	
		ClientToScreen(&point);
		pWnd->MoveWindow(point.x-195,point.y+15,sizeOFBigeyes,sizeOFBigeyes,1);
		  if (boolColorCheck)  {//手动设置 调试工具 显示鼠标点及RGB颜色的十进制表示
			CString tmp;
			CDC* tmpCDC=pWnd->getCDC();
			COLORREF col;
			col=tmpCDC->GetPixel(point);
			int r= col & 255;
			int g= col >> 8 & 255;
			int b= col >> 16 & 255;
			tmp.Format("r%d\ng%d\nb%d\n位置%d,%d",r,g,b,point.x,point.y);
			if (boolViewMode==1){
			}else
			m_csCalc.SetFont(&m_staticFont); // 设置新字体
			m_csCalc.SetWindowText(tmp);

		  }
	}
	if (boolOfCalc==3)
	{
	  if (!(boolOfBigeyes && boolOfOnBigeyes)) ClientToScreen(&point);
	  CClientDC   ClientDC(GetDesktopWindow());
	  //CScrollView::OnPrepareDC(&ClientDC); 
   
	  if(m_Dragging){  
	  CClientDC   ClientDC(GetDesktopWindow());
   
	//  OnPrepareDC(&ClientDC);  
	  //------------------设置画笔===============================
CPen pn;
    pn.CreatePen( PS_SOLID, 3, RGB( 0, 0, 255 ) );  //创建画笔 线宽12

    ClientDC.SelectObject( pn );                        //DC设置创建的画笔为当前画笔

    CPen* myp = ClientDC.SelectObject( &pn );          //设置当前画笔时，会返回一个指针存储先前画笔（注意这里&pn实际上可以为任何画笔，这一步执行的是SelectObject，会影响DC当前使用的画笔，因此后面一定要将DC的画笔恢复）

    ClientDC.SelectObject( myp );//注意将画笔恢复
	  //------------------=======================================
   
	  ClientDC.SetROP2(R2_NOT);//生成逆转当前屏幕颜色来画线的绘图方式以擦去之前画的线 
 
	  ClientDC.MoveTo(m_PointOrigin);//画线  
	  ClientDC.LineTo(m_PointOld);  
	  ClientDC.MoveTo(m_PointOrigin);  
	  ClientDC.LineTo(point);  
	  m_PointOld=point;  

	  calcScreen=point.x-m_PointOrigin.x;
	  if (calcScreen<0) calcScreen*=-1;

  	  CString tmp="";
	  tmp.Format("屏距:%1.1f\n高差:%1.0f\n人物:%1.0f\n屏距:%1.0f",calc1*10,calc2*10,calcHuman,calcScreen);
	  m_csCalc.SetWindowText(tmp);
		//测试屏距校准
		/*因为此情况下boolOfBigeyes==0，无法执行该段程序，错误未知
		  if (boolOfBigeyes)  {
			CString tmp;
			CDC* tmpCDC=pWnd->getCDC();
			COLORREF col;
			col=tmpCDC->GetPixel(point);
			tmp.Format("颜色%d，位置%d,%d",col,point.x,point.y);
			if (boolViewMode==1){
			}else
			m_csState.SetFont(&m_staticFont); // 设置新字体
			m_csState.SetWindowText(tmp);
		  }
		*/
	  }  
   
	}else if (boolOfCalc==4)
	{
	  if (!(boolOfBigeyes && boolOfOnBigeyes)) ClientToScreen(&point);
	  CClientDC   ClientDC(GetDesktopWindow());
	  //CScrollView::OnPrepareDC(&ClientDC);  
   
	  if(m_Dragging){  
	  CClientDC   ClientDC(GetDesktopWindow());
   
	//  OnPrepareDC(&ClientDC);  
	  //------------------设置画笔===============================
CPen pn;
    pn.CreatePen( PS_SOLID, 1, RGB( 0, 0, 255 ) );  //创建画笔 线宽12

    ClientDC.SelectObject( pn );                        //DC设置创建的画笔为当前画笔

    CPen* myp = ClientDC.SelectObject( &pn );          //设置当前画笔时，会返回一个指针存储先前画笔（注意这里&pn实际上可以为任何画笔，这一步执行的是SelectObject，会影响DC当前使用的画笔，因此后面一定要将DC的画笔恢复）

    ClientDC.SelectObject( myp );//注意将画笔恢复
	  //------------------=======================================
   
	  ClientDC.SetROP2(R2_NOT);//生成逆转当前屏幕颜色来画线的绘图方式以擦去之前画的线 
 
	  ClientDC.MoveTo(m_PointOrigin);//画线  
	  ClientDC.LineTo(m_PointOld);  
	  ClientDC.MoveTo(m_PointOrigin);  
	  ClientDC.LineTo(point);  
	  m_PointOld=point;  

	  calcHuman=point.x-m_PointOrigin.x;
	  if (calcHuman<0) calcHuman*=-1;
	  calc1=calcHuman/calcScreen;
	  double tmpDy=point.y-m_PointOrigin.y;
	  calc2=tmpDy/calcScreen;

  	  CString tmp="";
	  tmp.Format("屏距:%1.1f\n高差:%1.0f\n人物:%1.0f\n屏距:%1.0f",calc1*10,calc2*10,calcHuman,calcScreen);
	  m_csCalc.SetWindowText(tmp);
	  }  
   
	}
	CDialogEx::OnMouseMove(nFlags,   point);  
}


void CDDTHelperDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    UpdateData();
    switch(nIDEvent)
    {
    case 1:
        {
			CString tmp="";
			m_csState.SetWindowText(tmp);
            KillTimer(1);//弹出一次提示框后杀掉timer，否则会重复弹框
        }
        break;    
    default:
        break;
    }
	if (boolViewMode==1){
	}else
	m_csState.SetFont(&m_editFont); // 设置新字体

	CDialogEx::OnTimer(nIDEvent);
}


void CDDTHelperDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (boolOfCalc==2 && boolOfBigeyes==0)
	{
	  boolOfCalc=4;
	  CClientDC   ClientDC(GetDesktopWindow());
	  ClientToScreen(&point); 
	  //OnPrepareDC(&ClientDC);  
   
	  m_PointOrigin=point;  
	  m_PointOld=point;  
	  m_Dragging=1;  
   
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDDTHelperDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (boolOfCalc==1 && boolOfBigeyes==0)
	{
	  boolOfCalc=3;
	  CClientDC   ClientDC(GetDesktopWindow());
	  ClientToScreen(&point); 
	  //OnPrepareDC(&ClientDC);  
   
	  m_PointOrigin=point;  
	  m_PointOld=point;  
	  m_Dragging=1;  
	  /*
	  //通过0x999999校准屏距
	  if (boolOfBigeyes)  {
		CDC* tmpCDC=pWnd->getCDC();
		COLORREF col;
		col=tmpCDC->GetPixel(point);
		{
		  //测试屏距校准
		  CString tmp="";
		  tmp.Format("%i,%i",col,point.x);
		  m_csState.SetFont(&m_staticFont); // 设置新字体
		  m_csState.SetWindowText(tmp);
		}
		while(col!=0x999999 && point.x<1366)
			col=tmpCDC->GetPixel(++point.x,point.y);
		if (point.x<1366){
		  m_PointOrigin=point;  
		  m_PointOld=point;
		}
	  }
	  */
	}  else if (boolOfCalc==1 && boolOfBigeyes==1)
	{
	  CClientDC   ClientDC(GetDesktopWindow());
	  ClientToScreen(&point); 
	  //OnPrepareDC(&ClientDC); 

	  m_PointOrigin=point;  
	  m_PointOld=point; 

	  //通过类0x999999的竖线左右逼近计算屏距

		while(!checkCol(m_PointOrigin))
			++m_PointOrigin.x;
		while(!checkCol(m_PointOld))
			--m_PointOld.x;

	  boolOfCalc=0;
	  calcScreen=m_PointOld.x-m_PointOrigin.x;
	  if (calcScreen<0) calcScreen*=-1;

	  CString tmp="";
	  m_csState.SetWindowText(tmp);
	  tmp.Format("屏距:%1.1f\n高差:%1.0f\n人物:%1.0f\n屏距:%1.0f",calc1*10,calc2*10,calcHuman,calcScreen);
	  m_csCalc.SetWindowText(tmp);
	  Behind();
	  
	  CDialog::OnLButtonUp(nFlags,   point);  

	  pDlg->PostNcDestroy();
	  if(boolOfBigeyes) pWnd->DestroyWindow();
	  boolOfOnBigeyes=0;
	  //OnBnClickedButton5();//新版本中舍弃测屏距时链接测距 使竞赛逻辑更清晰
	  ::ReleaseCapture();//新版本中提前释放Capture提前到测屏距第一次点击中

	}  else if (boolOfCalc==2 && boolOfBigeyes==1)
	{
	  CClientDC   ClientDC(GetDesktopWindow());
	  ClientToScreen(&point); 
	  //OnPrepareDC(&ClientDC);  

	  /*已被证明存在致命Bug 操作时敌人位置不一定处在小屏幕中
	  //==============测距时自动导入屏距===========================================
	  m_PointOrigin=point;  
	  m_PointOld=point; 

	  //通过类0x999999的竖线左右逼近计算屏距

		while(!checkCol(m_PointOrigin))
			++m_PointOrigin.x;
		while(!checkCol(m_PointOld))
			--m_PointOld.x;

	  boolOfCalc=0;
	  calcScreen=m_PointOld.x-m_PointOrigin.x;
	  if (calcScreen<0) calcScreen*=-1;

	  CString tmp="";
	  m_csState.SetWindowText(tmp);
	  tmp.Format("屏距:%1.1f\n高差:%1.0f\n人物:%1.0f\n屏距:%1.0f",calc1*10,calc2*10,calcHuman,calcScreen);
	  m_csCalc.SetWindowText(tmp);
	  //==================================================================
	  */

	  boolOfCalc=4;
   
	  m_PointOrigin=point;  
	  m_PointOld=point;  
	  m_Dragging=1;  
   
	} else if (boolOfCalc==3)
	{
	  ::ReleaseCapture();
	  if(m_Dragging){ 
		  m_Dragging=0;  }
	  CClientDC   ClientDC(GetDesktopWindow());
	  ClientToScreen(&point);
	  //CEditView::OnPrepareDC(&ClientDC,NULL);  
	  ClientDC.DPtoLP(&point); 
	  //------------------设置画笔===============================
CPen pn;
    pn.CreatePen( PS_SOLID, 3, RGB( 0, 0, 255 ) );  //创建画笔 线宽12

    ClientDC.SelectObject( pn );                        //DC设置创建的画笔为当前画笔

    CPen* myp = ClientDC.SelectObject( &pn );          //设置当前画笔时，会返回一个指针存储先前画笔（注意这里&pn实际上可以为任何画笔，这一步执行的是SelectObject，会影响DC当前使用的画笔，因此后面一定要将DC的画笔恢复）

    ClientDC.SelectObject( myp );//注意将画笔恢复
	  //------------------=======================================
   
	  ClientDC.SetROP2(R2_NOT);//生成逆转当前屏幕颜色来画线的绘图方式以擦去之前画的线 
 
	  ClientDC.MoveTo(m_PointOrigin);//画线  
	  ClientDC.LineTo(m_PointOld);  
		  

	  boolOfCalc=0;
	  calcScreen=point.x-m_PointOrigin.x;
	  if (calcScreen<0) calcScreen*=-1;
	  /*
	  //通过0x999999校准屏距
	  if (boolOfBigeyes)  {
		CDC* tmpCDC=pWnd->getCDC();
		COLORREF col;
		col=tmpCDC->GetPixel(point);
		while(col!=0x999999 && point.x<1366)
			col=tmpCDC->GetPixel(++point.x,point.y);
		if (point.x<1366){
		  	calcScreen=point.x-m_PointOrigin.x;
		}
	  }
	  */
	  CString tmp="";
	  m_csState.SetWindowText(tmp);
	  tmp.Format("屏距:%1.1f\n高差:%1.0f\n人物:%1.0f\n屏距:%1.0f",calc1*10,calc2*10,calcHuman,calcScreen);
	  m_csCalc.SetWindowText(tmp);
	  Behind();
	  
	  CDialog::OnLButtonUp(nFlags,   point);  
		/*
		//原版不删除最后一根线
	  ClientDC.SetROP2(R2_NOT);  
	  ClientDC.MoveTo(m_PointOrigin);  
	  ClientDC.LineTo(m_PointOld);  
	  ClientDC.SetROP2(R2_COPYPEN);  
	  ClientDC.MoveTo(m_PointOrigin);  
	  ClientDC.LineTo(point);  
	  }  
	  */

	  pDlg->PostNcDestroy();
	  if(boolOfBigeyes) pWnd->DestroyWindow();
	  boolOfOnBigeyes=0;
	  OnBnClickedButton5();

	} else if (boolOfCalc==4)
	{
	  pDlg->PostNcDestroy();
	  if(boolOfBigeyes) pWnd->DestroyWindow();
	  boolOfOnBigeyes=0;
	  //pDlg->PostNcDestroy();
	  ::ReleaseCapture(); 
	  if(m_Dragging){  
		  m_Dragging=0;  }
	  CClientDC   ClientDC(GetDesktopWindow());
	  ClientToScreen(&point);
	  //CEditView::OnPrepareDC(&ClientDC,NULL);  
	  ClientDC.DPtoLP(&point);  
	  //------------------设置画笔===============================
		CPen pn;
		pn.CreatePen( PS_SOLID, 1, RGB( 0, 0, 255 ) );  //创建画笔 线宽12

		ClientDC.SelectObject( pn );                        //DC设置创建的画笔为当前画笔

		CPen* myp = ClientDC.SelectObject( &pn );          //设置当前画笔时，会返回一个指针存储先前画笔（注意这里&pn实际上可以为任何画笔，这一步执行的是SelectObject，会影响DC当前使用的画笔，因此后面一定要将DC的画笔恢复）

		ClientDC.SelectObject( myp );//注意将画笔恢复
	  //------------------=======================================
   
	  ClientDC.SetROP2(R2_NOT);//生成逆转当前屏幕颜色来画线的绘图方式以擦去之前画的线 
 
	  ClientDC.MoveTo(m_PointOrigin);//画线  
	  ClientDC.LineTo(m_PointOld);  
		  
	  boolOfCalc=0;
	  calcHuman=point.x-m_PointOrigin.x;
	  if (calcHuman<0) {calcHuman*=-1;screenDir=1;} else screenDir=0;
	  calc1=calcHuman/calcScreen;
	  double tmpDy=point.y-m_PointOrigin.y;
	  calc2=tmpDy/calcScreen;

  	  CString tmp="";
	  m_csState.SetWindowText(tmp);
	  tmp.Format("屏距:%1.1f\n高差:%1.0f\n人物:%1.0f\n屏距:%1.0f",calc1*10,calc2*10,calcHuman,calcScreen);
	  m_csCalc.SetWindowText(tmp);
	  Behind();
	  //得到屏距后自动计算当前屏距0风时数据
		if (boolViewMode==1){
		}else
		  m_csState.SetFont(&m_staticFont); // 设置新字体

		if (boolOfBigeyes) {
			  CDC* tmpCDC=pWnd->getCDC();
			  double tmpDou=autoGetWind(	tmpCDC	);
			  //double tmpDou=0;
			  tmp.Format("风力:%1.1f ",tmpDou);
			  calcRES(	tmpDou	);
		} else	{
			  tmp="风力:0.0 ";
			  calcRES(0);
		}
		  m_csState.SetWindowText(tmp);
		  setRES(aR,bR,cR,dR,eR,fR,gR,hR,iR,jR,kR);
		  CDDTHelperDlg::GetDlgItem(IDC_EDIT1)->SetFocus();
			/*
			//原版不删除最后一根线
		  ClientDC.SetROP2(R2_NOT);  
		  ClientDC.MoveTo(m_PointOrigin);  
		  ClientDC.LineTo(m_PointOld);  
		  ClientDC.SetROP2(R2_COPYPEN);  
		  ClientDC.MoveTo(m_PointOrigin);  
		  ClientDC.LineTo(point);  
		  }  
		  */ 
	}    else if (boolOfCalc==5)
	{
	  CClientDC   ClientDC(GetDesktopWindow());
	  ClientToScreen(&point); 
	  //OnPrepareDC(&ClientDC); 
	  boolOfCalc=0;

	  Behind();

	  windPos=point;
	  //刷新状态信息并自动测风计算结果
			  CDC* tmpCDC=pWnd->getCDC();
			  double tmpDou=autoGetWind(	tmpCDC	);
			  //double tmpDou=0;
			  CString tmp="";
			  tmp.Format("风力:%1.1f ",tmpDou);
			  m_csState.SetWindowText(tmp);
			  calcRES(	tmpDou	);
	  
	  CDialog::OnLButtonUp(nFlags,   point);  

	  pDlg->PostNcDestroy();
	  if(boolOfBigeyes) pWnd->DestroyWindow();
	  boolOfOnBigeyes=0;
	  ::ReleaseCapture();
	}    else if (boolOfCalc==6)
	{
	  CClientDC   ClientDC(GetDesktopWindow());
	  ClientToScreen(&point); 
	  //OnPrepareDC(&ClientDC); 
	  boolOfCalc=0;

	  Behind();

	  anglePos=point;

			  CString tmp="";
			  tmp.Format("x %1.0d\ny %1.0d\ndefaultX 186\ndefaultY 680",anglePos.x,anglePos.y);
			  m_csCalc.SetWindowText(tmp);
	  CDC* tmpCDC=pWnd->getCDC();
	  angleOld=autoGetAngle(tmpCDC);
		if(angleOld==0)
			  tmp.Format("角度:0");
		else
			  tmp.Format("角度:%1.0d ",angleOld);
			  m_csState.SetWindowText(tmp);
	  m_csState.SetWindowTextA(tmp);

	  CDialog::OnLButtonUp(nFlags,   point);  

	  pDlg->PostNcDestroy();
	  if(boolOfBigeyes) pWnd->DestroyWindow();
	  boolOfOnBigeyes=0;
	  ::ReleaseCapture();
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CDDTHelperDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
    int tmplength=m_e1.GetWindowTextLength();
    if(tmplength==1)
    {
        //GetDlgItem(m_e2).SetFocus();
		if (m_cs1[0]=='`')
		{
			boolWind=1;
			CString tmp="";
			m_e1.SetWindowText(tmp);
			tmp.Format("负数风力");
			if (boolViewMode==1){
			}else
			m_csState.SetFont(&m_editFont); // 设置新字体
			m_csState.SetWindowText(tmp);
			//SetTimer(1, 3000, NULL);
		}else if(m_cs1[0]<'0'||m_cs1[0]>'6')
		{
			CString tmp="";
			m_e1.SetWindowText(tmp);
		}else
		{
			GetDlgItem(IDC_EDIT2)->SetFocus();
		}
    }else if(tmplength>1)
	{	
		CString tmp=m_cs1;
		tmp=tmp.Left(1);
		m_e1.SetWindowText(tmp);
	}
}


void CDDTHelperDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	//  m_e2 范围越界
    int tmplength=m_e2.GetWindowTextLength();
    if(tmplength==1)
    {
		// part 2   calculator
		//=============读取两个文本框的风力
		CString tmpCS=m_cs1+"."+m_cs2;
		double tmpD;
		tmpD=atof(tmpCS);
		if (boolWind) {tmpD*=-1;boolWind=0;} else {tmpD*=1;}
		wind=tmpD;
		if (boolViewMode==1){
		}else
		m_csState.SetFont(&m_staticFont); // 设置新字体
		CString tmp="";
		tmp.Format("风力:%1.1f ",tmpD);
		m_csState.SetWindowText(tmp);
		//SetTimer(1, 3000, NULL);
		//计算完成后不再抹除数据
		//=============读取两个文本框的风力

		calcRES(tmpD);

		GetDlgItem(IDC_EDIT1)->SetFocus();
    }else if(tmplength>1)
	{
		CString tmp=m_cs2;
		tmp=tmp.Left(1);
		m_e2.SetWindowText(tmp);
	}
}


void CDDTHelperDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if(m_e3.GetWindowTextLengthA()<=4)
	{
		double m_tmpCalc1ReadIn=atof(m_cs3);
		if (m_tmpCalc1ReadIn<100&&m_tmpCalc1ReadIn>=0)
		{
			calc1=m_tmpCalc1ReadIn/10;
			calcHuman=calc1*calcScreen;
			calcRES(0);
		}else
		{
			m_tmpCalc1ReadIn=int(m_tmpCalc1ReadIn)%100+m_tmpCalc1ReadIn-int(m_tmpCalc1ReadIn);
			CString tmp="";
			tmp.Format("%1.1f",m_tmpCalc1ReadIn);
			m_e3.SetWindowTextA(tmp);
		}
	}else{
		CString tmp=m_cs3.Left(4);
		m_e3.SetWindowTextA(tmp);
	}
  	CString tmp="";
	tmp.Format("屏距:%1.1f\n高差:%1.0f\n人物:%1.0f\n屏距:%1.0f",calc1*10,calc2*10,calcHuman,calcScreen);
	m_csCalc.SetWindowText(tmp);
}


void CDDTHelperDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

			//计算0.0风时数据
			if (boolViewMode==1){
			}else
			  m_csState.SetFont(&m_staticFont); // 设置新字体
			  CString tmp="风力:0.0 ";
			  m_csState.SetWindowText(tmp);
			  calcRES(0);

	//CDialogEx::OnOK();//结束对话框
}


double CDDTHelperDlg::getStrFromAngle(double A,double wind)
{
	double kv=0.257,kw=0.8,kc=0.00012,nc=0.48,g=10;
	double c=kc*(40-A)*abs(40-A)+nc,c1=calc1*10,c2=calc2*10;
	double W=wind*kw;
	A=(A/180)*3.1415926;
	double insqrt=c*c+8*(c*W*sin(A)+g*cos(A))/(c1*sin(A)-c2*cos(A));
	double ans=(c2*c*W+c1*g)*(c+sqrt(insqrt))/(4*(c*W*sin(A)+g*cos(A)));
	return ans/kv;
}

void CDDTHelperDlg::clearShape(int n)
{
	//清除箭头外侧冗余图像，由于边框判定，已取消
}

int CDDTHelperDlg::getShapeDir(short &n)
{
		int itmp=0,jtmp=0,ktmp=0;
		//for (int i=0;i<101;i++)
		for (int j=40;j>0;j--)
			if (map[50][j]==0)
			{
				shapeMax=0;
				setShape2(++n,50,j);
				if (shapeMax<100)
					setShape2back(n--,50,j);
				else
				{
					shapeSize[n]=shapeMax;
					jtmp=j;
					setShapetmp1.Format("%d,%d\n",n,shapeSize[n]);
					setShapetmp+=setShapetmp1;
					break;
				}
			}

		/*
		CString tmpCS1;
		CFile mFile("map2.txt", CFile::modeWrite|CFile::modeCreate); 
		mFile.Write(setShapetmp,255); 
		for (int j=0;j<81;j++){
			for (int i=0;i<101;i++)
			{
				tmpCS1.Format("%d",map[i][j]);
				mFile.Write(tmpCS1,1); 
			}
				tmpCS1.Format("  %d",j);
				mFile.Write(tmpCS1,4); 
			mFile.Write("\n",8); 
		}
		mFile.Close();	
		*/

		for (int i=50;i<100;i++)
			if (map[i][jtmp]==1) { itmp=i-1;break;}
		if (itmp==0) return 88;
		for (int j=jtmp+1;j<81;j++)
			if (map[50][j]==n) { screenPos=j;break;}
		if (screenPos!=jtmp) screenPos=(screenPos+jtmp)/2;
		ktmp=0;
		for (int k=jtmp-1;k>=jtmp-6;k--)
			if (map[itmp][k]!=map[itmp][k+1]) {ktmp=1;break;}
		if (ktmp==0) {	clearShape(n);return 1;}
		for (int i=50;i>0;i--)
			if (map[i][jtmp]==1) { itmp=i+1;break;}
		if (itmp>50) return 88;
		ktmp=0;
		for (int k=jtmp-1;k>=jtmp-6;k--)
			if (map[itmp][k]!=map[itmp][k+1]) {ktmp=1;break;}
		if (ktmp==0) {	clearShape(n);return 0;}
		return 88;
}

int CDDTHelperDlg::getShapeLeft(short &n)
{
	screenNLx=100;
	screenNLy=80;
	screenNRx=0;
	screenNRy=0;
		int itmp=0,jtmp=0,ktmp=0;
		for (int i=50;i>0;i--)
		//for (int j=40;j>0;j--)
			if (map[i][screenPos]==0)
			{
				shapeMax=0;
				setShape2(++n,i,screenPos);
				if (shapeMax<45){
					if (n==3) {	
						screenNLx=100;
						screenNLy=80;
						screenNRx=0;
						screenNRy=0;
					}
					setShape2back(n--,i,screenPos);
				}else{
					shapeSize[n]=shapeMax;
					itmp=i;
					int ScreenCheck;
					if (n==3){
						ScreenCheck=getScreenCheck(3);
						/*setShapetmp1.Format("n%d,Size%d,SC%d,Lx%d,Ly%d,Rx%d,Ry%d,W%d,H%d,screenPos%d  ,\n",
							n,shapeSize[n],ScreenCheck,screenNLx,screenNLy,screenNRx,screenNRy,
							screenNLx-screenNRx,screenNLy-screenNRy,screenPos);
							*/
						setShapetmp1.Format("%d,%d,SC%d\n",n,shapeSize[n],ScreenCheck);
						setShapetmp+=setShapetmp1;
					}else
					{
						setShapetmp1.Format("%d,%d\n",n,shapeSize[n]);
						setShapetmp+=setShapetmp1;
					}
				}
			}
			else if (map[i][screenPos]==screenBorder)	{break;}
	return 0;
}

int CDDTHelperDlg::getShapeRight(short &n)
{
	screenNLx=100;
	screenNLy=80;
	screenNRx=0;
	screenNRy=0;
		int itmp=0,jtmp=0,ktmp=0;
		for (int i=50;i<101;i++)
		//for (int j=40;j>0;j--)
			if (map[i][screenPos]==0)
			{
				shapeMax=0;
				setShape2(++n,i,screenPos);
				if (shapeMax<45){
					if (n==4) {	
						screenNLx=100;
						screenNLy=80;	
						screenNRx=0;
						screenNRy=0;
					}
					setShape2back(n--,i,screenPos);
				}else{
					shapeSize[n]=shapeMax;
					itmp=i;
					int ScreenCheck;
					if (n==4){
						ScreenCheck=getScreenCheck(4);
						setShapetmp1.Format("%d,%d,SC%d\n",n,shapeSize[n],ScreenCheck);
						setShapetmp+=setShapetmp1;
					}else
					{
						setShapetmp1.Format("%d,%d\n",n,shapeSize[n]);
						setShapetmp+=setShapetmp1;
					}
				}
			}
			else if (map[i][screenPos]==screenBorder)	{break;}

	return 0;
}

int CDDTHelperDlg::getScreenCheck(int n)
{
	double ans=0;
	int x,y;
	if (screenNRx==0||screenNRy==0||screenNLx==100||screenNLx==80)
		return 0;
	x=(screenNRx+screenNLx)/2;x=screenNRx;
	y=(screenNRy+screenNLy)/2;y=screenNRy;
	for (int i=screenNLx;i<=screenNRx;i++)
		for (int j=screenNLy;j<=screenNRy;j++)
		{
			if (map[i][j]==n)
				ans+=(i-x)*(i-x)+(j-y)*(j-y);
		}
	return int(ans);
}	

double CDDTHelperDlg::setShape(short &n)
{
	double ans=0;
	setShapetmp=setShapetmp1="";  
	screenPos=40;
	screenBorder=2;

	int direction=getShapeDir(n);	
	if (direction==88) return 0;
	if (direction!=screenDir) {
		direction=-1;
		boolWind=1;
	} else direction=1;

	int leftNum=getShapeLeft(n); 
	int rightNum=getShapeRight(n);
	ans=leftNum+rightNum/10.0;
	//ans=1.5;
	
	setShapetmp1.Format("%d\n",n);
	setShapetmp=setShapetmp1+setShapetmp;

	//m_csCalc.SetWindowText(setShapetmp);
	/*
	CString tmpCS1;
	CFile mFile("map1.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",map[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	*/
	return ans*direction;
}

void CDDTHelperDlg::setShape2(short n,int x,int y)
{
	++shapeMax;
	if (shapeMax<2000)
	{
		map[x][y]=n;
		if (n==3) {	
			if (screenNLx>x) screenNLx=x;
			if (screenNLy>y) screenNLy=y;
			if (screenNRx<x) screenNRx=x;
			if (screenNRy<y) screenNRy=y;
		}
		if (n==4) {	
			if (screenNLx>x) screenNLx=x;
			if (screenNLy>y) screenNLy=y;
			if (screenNRx<x) screenNRx=x;
			if (screenNRy<y) screenNRy=y;
		}

		if (x+1<101 && map[x+1][y]==0)
			setShape2(n,x+1,y);
		if (x-1>0 && map[x-1][y]==0)
			setShape2(n,x-1,y);
		if (y+1<81 && map[x][y+1]==0)
			setShape2(n,x,y+1);
		if (y-1>0 && map[x][y-1]==0)
			setShape2(n,x,y-1);
	}
}
void CDDTHelperDlg::setShape2back(short n,int x,int y)
{
	map[x][y]=1;
	if (x+1<101 && map[x+1][y]==n)
		setShape2back(n,x+1,y);
	if (x-1>0 && map[x-1][y]==n)
		setShape2back(n,x-1,y);
	if (y+1<81 && map[x][y+1]==n)
		setShape2back(n,x,y+1);
	if (y-1>0 && map[x][y-1]==n)
		setShape2back(n,x,y-1);
}

double CDDTHelperDlg::autoGetWind(CDC* tmpCDC)
{
	return 0;
	//ClientToScreen(&windPos); 
	int r,g,b,middle;
	COLORREF col;
	for (int x=windPos.x-50;x<windPos.x+50;x++)
		for (int y=windPos.y-40;y<windPos.y+40;y++){
			col=tmpCDC->GetPixel(x,y);
			r= col & 255;
			g= col >> 8 & 255;
			b= col >> 16 & 255;
			middle=(r+b+g)/3;
			if(middle<colorCheckMiddle){
				//tmpCDC->SetPixel(x,y,0);无需浪费时间效率为当前位置无法重绘的可视图片赋值
				map[x-windPos.x+51][y-windPos.y+41]=0;
			}else{
				//tmpCDC->SetPixel(x,y,0xFFFFFF);
				map[x-windPos.x+51][y-windPos.y+41]=1;
			}
		}
	/*
	CString tmpCS1;
	CFile mFile("map.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",map[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	*/
	shape=1;
	return setShape(shape);
	//调试：显示统计图形总数
	/*
  	CString tmp="";
	tmp.Format("%d",shape);
	m_csCalc.SetWindowText(tmp);
	*/
}


int CDDTHelperDlg::autoGetAngle(CDC* tmpCDC)
{ 
	/*getMapA();
	int angle;
	*/
	int r,g,b,middle,angle;
	COLORREF col;
	for (int x=anglePos.x-50;x<anglePos.x+50;x++)
		for (int y=anglePos.y-40;y<anglePos.y+40;y++){
			col=tmpCDC->GetPixel(x,y);
			r= col & 255;
			g= col >> 8 & 255;
			b= col >> 16 & 255;
			middle=(r+b+g)/3;
			if(middle<colorCheckMiddle){
				mapA[x-anglePos.x+51][y-anglePos.y+41]=1;
			}else{
				mapA[x-anglePos.x+51][y-anglePos.y+41]=0;
			}
		}
	//图形中间竖线置为空白防止两数字粘连
	int num=0;
	for (int x=30;x<51;x++)
		if (mapA[50][x]==0) ++num;
	countbit=1;
	if (num<4) {
		countbit=2;
		for (int y=0;y<81;y++)
			mapA[50][y]=1;
	}

	CString tmpCS1;
	CFile mFile("mapAbegin.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	

	setMapA();
	if (checkShape2()==-255)
		angle=-255;
	else if (checkShape3()==-255)
		angle=checkShape2();
	else if (checkShape4()==-255)
		angle=10*checkShape2()+checkShape3();
	else 
		angle=100*checkShape2()+10*checkShape3()+checkShape4();

			
	/*
	if (countbit==2)
		angle=10*checkShape2()+checkShape3();
	else if (countbit==1)
		angle=checkShape2();
		*/


	/*
	mFile.Open("mapAans.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	//*/

	return angle;
}

int CDDTHelperDlg::autoGetAngle2(CDC* tmpCDC)
{ 
	int r,g,b,middle,angle;
	COLORREF col;
	for (int x=anglePos.x-50;x<anglePos.x+50;x++)
		for (int y=anglePos.y-40;y<anglePos.y+40;y++){
			col=tmpCDC->GetPixel(x,y);
			r= col & 255;
			g= col >> 8 & 255;
			b= col >> 16 & 255;
			middle=(r+b+g)/3;
			if(middle<colorCheckMiddle+15){
				mapA[x-anglePos.x+51][y-anglePos.y+41]=1;
			}else{
				mapA[x-anglePos.x+51][y-anglePos.y+41]=0;
			}
		}
	//图形中间竖线置为空白防止两数字粘连
	int num=0;
	for (int x=30;x<51;x++)
		if (mapA[50][x]==0) ++num;
	if (num<4) 
		for (int y=0;y<81;y++)
			mapA[50][y]=1;
	/*
	CString tmpCS1;
	CFile mFile("mapAbegin2.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	*/

	setMapA();
	if (checkShape2()==-255)
		angle=-255;
	else if (checkShape3()==-255)
		angle=checkShape2();
	else if (checkShape4()==-255)
		angle=10*checkShape2()+checkShape3();
	else 
		angle=100*checkShape2()+10*checkShape3()+checkShape4();

	/*
	mFile.Open("mapAans2.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	//*/

	return angle;
}

int CDDTHelperDlg::autoGetAngle3(CDC* tmpCDC)
{ 
	int r,g,b,middle,angle;
	COLORREF col;
	for (int x=anglePos.x-50;x<anglePos.x+50;x++)
		for (int y=anglePos.y-40;y<anglePos.y+40;y++){
			col=tmpCDC->GetPixel(x,y);
			r= col & 255;
			g= col >> 8 & 255;
			b= col >> 16 & 255;
			middle=(r+b+g)/3;
			if(middle<colorCheckMiddle+30){
				mapA[x-anglePos.x+51][y-anglePos.y+41]=1;
			}else{
				mapA[x-anglePos.x+51][y-anglePos.y+41]=0;
			}
		}
	//图形中间竖线置为空白防止两数字粘连
	int num=0;
	for (int x=30;x<51;x++)
		if (mapA[50][x]==0) ++num;
	if (num<4) 
		for (int y=0;y<81;y++)
			mapA[50][y]=1;
	/*
	CString tmpCS1;
	CFile mFile("mapAbegin3.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	*/

	setMapA();
	if (checkShape2()==-255)
		angle=-255;
	else if (checkShape3()==-255)
		angle=checkShape2();
	else if (checkShape4()==-255)
		angle=10*checkShape2()+checkShape3();
	else 
		angle=100*checkShape2()+10*checkShape3()+checkShape4();

	/*
	mFile.Open("mapAans3.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	//*/

	return angle;
}

int CDDTHelperDlg::autoGetAngle4(CDC* tmpCDC)
{ 
	int r,g,b,middle,angle;
	COLORREF col;
	for (int x=anglePos.x-50;x<anglePos.x+50;x++)
		for (int y=anglePos.y-40;y<anglePos.y+40;y++){
			col=tmpCDC->GetPixel(x,y);
			r= col & 255;
			g= col >> 8 & 255;
			b= col >> 16 & 255;
			middle=(r+b+g)/3;
			if(middle<colorCheckMiddle+68){
				mapA[x-anglePos.x+51][y-anglePos.y+41]=1;
			}else{
				mapA[x-anglePos.x+51][y-anglePos.y+41]=0;
			}
		}
	//图形中间竖线置为空白防止两数字粘连
	int num=0;
	for (int x=30;x<51;x++)
		if (mapA[50][x]==0) ++num;
	if (num<4) 
		for (int y=0;y<81;y++)
			mapA[50][y]=1;
	/*
	CString tmpCS1;
	CFile mFile("mapAbegin4.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	*/

	setMapA();
	if (checkShape2()==-255)
		angle=-255;
	else if (checkShape3()==-255)
		angle=checkShape2();
	else if (checkShape4()==-255)
		angle=10*checkShape2()+checkShape3();
	else 
		angle=100*checkShape2()+10*checkShape3()+checkShape4();

	/*
	mFile.Open("mapAans4.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	//*/

	return angle;
}

void CDDTHelperDlg::setMapA(void)
{
	short n=1;
	for (int i=0;i<400;i++)
	{
		Shape3Lpoint[i].x=100;
		Shape3Lpoint[i].y=80;
		Shape3Rpoint[i].x=0;
		Shape3Rpoint[i].y=0;
	}
	
	for (int i=50;i>30;i--)
		if (mapA[i][41]==0)
		{
			shapeMax=0;
			setShape3(++n,i,41);
			if (shapeMax>150 || shapeMax<20 || (Shape3Rpoint[n].x-Shape3Lpoint[n].x>15) ){
				setShape3back(n--,i,41);
				continue;
			}
			break;
		}
	for (int i=50;i<71;i++)
		if (mapA[i][41]==0)
		{
			shapeMax=0;
			setShape3(++n,i,41);
			if (shapeMax>150 || shapeMax<20 || (Shape3Rpoint[n].x-Shape3Lpoint[n].x>15) ){
				setShape3back(n--,i,41);
				continue;
			}
			break;
		}
		
	/*
	CString tmpCS1;
	CFile mFile("mapA1.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	*/

	for (int j=1;j<81;j++)
	for (int i=100;i>0;i--)
		if (mapA[i][j]==0||mapA[i][j]>4)
		{
			setShape3back(mapA[i][j],i,j);
		}
		
	/*
	mFile.Open("mapA2.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	*/
		
	for (int i=0;i<400;i++)
	{
		Shape3Lpoint[i].x=100;
		Shape3Lpoint[i].y=80;
		Shape3Rpoint[i].x=0;
		Shape3Rpoint[i].y=0;
	}
	n=5;
	for (int i=1;i<101;i++)
		if ( mapA[i][41]!=1 && mapA[i][41]!=n )
		{
			shapeMax=0;
			setShape3(++n,i,41,mapA[i][41]);
		}
	for (int j=1;j<81;j++)
		for (int i=100;i>0;i--)
			if (mapA[i][j]>5)
			{
				Shape3Lpoint[mapA[i][j]-4]=Shape3Lpoint[mapA[i][j]];
				Shape3Rpoint[mapA[i][j]-4]=Shape3Rpoint[mapA[i][j]];
				mapA[i][j]-=4;
			}
}

void CDDTHelperDlg::setShape3(short n,int x,int y,int check)
{
	/*
	CString tmpCS1;
	CFile mFile("mapAtmp.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=0;j<81;j++){
		for (int i=0;i<101;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	mFile.Close();	
	*/
	++shapeMax;
	if (shapeMax<2000)
	{
		mapA[x][y]=n;
		
		if (Shape3Lpoint[n].x>x) Shape3Lpoint[n].x=x;
		if (Shape3Lpoint[n].y>y) Shape3Lpoint[n].y=y;
		if (Shape3Rpoint[n].x<x) Shape3Rpoint[n].x=x;
		if (Shape3Rpoint[n].y<y) Shape3Rpoint[n].y=y;

		if (x+1<101 && mapA[x+1][y]==check)
			setShape3(n,x+1,y,check);
		if (x-1>0 && mapA[x-1][y]==check)
			setShape3(n,x-1,y,check);
		if (y+1<81 && mapA[x][y+1]==check)
			setShape3(n,x,y+1,check);
		if (y-1>0 && mapA[x][y-1]==check)
			setShape3(n,x,y-1,check);
	}
}
void CDDTHelperDlg::setShape3back(short n,int x,int y)
{
	mapA[x][y]=1;
	Shape3Lpoint[n].x=100;
	Shape3Lpoint[n].y=80;
	Shape3Rpoint[n].x=0;
	Shape3Rpoint[n].y=0;
	if (x+1<101 && mapA[x+1][y]==n)
		setShape3back(n,x+1,y);
	if (x-1>0 && mapA[x-1][y]==n)
		setShape3back(n,x-1,y);
	if (y+1<81 && mapA[x][y+1]==n)
		setShape3back(n,x,y+1);
	if (y-1>0 && mapA[x][y-1]==n)
		setShape3back(n,x,y-1);
}

int CDDTHelperDlg::getShapeNum2(CPoint L,CPoint R,int n)
{
	int x1=L.x,x2=R.x,y1=L.y,y2=R.y;
	int k=1;
	int sum1=0;
	int sum2=0;
	int sum3=0;
	int sum4=0;
	for(int i=y1;i<=y2;i++,k++)
		for(int j=x1;j<=x2;j++)
		{
			if(mapA[j][i]==n)
				sum1+=k;
		}
	k=1;
	for(int i=y2;i>=y1;i--,k++)
		for(int j=x1;j<=x2;j++)
		{
			if(mapA[j][i]==n)
				sum2+=k;
		}
		k=1;
		for(int i=x1;i<=x2;i++,k++)
			for(int j=y1;j<=y2;j++)
			{
				if(mapA[i][j]==n)
					sum3+=k;	
			}
		k=1;
		for(int i=x2;i>=x1;i--,k++)
			for(int j=y1;j<=y2;j++)
			{
				if(mapA[i][j]==n)
					sum4+=k;	
			}
	
	  checkDJW.Format("%d,%d,%d,%d(%d,%d)(%d,%d) %d ",sum1,sum2,sum3,sum4,x1,y1,x2,y2,n-1);
	  //MessageBox(checkDJW);
	
	if(sum2<=20&&sum1<=20&&sum3<=20)
		{checkDJW+="-255\n";return -255;}
	if(sum1<450)
		{checkDJW+="7";return 7;}
	if(sum2<450)
		{checkDJW+="1";return 1;}
	if(sum1>=715||sum2>=715||sum4>600)
		{checkDJW+="8";return 8;}
	if(500<sum1&&sum1<600&&450<sum2&&sum2<525&&375<sum3&&sum3<525&&375<sum4&&sum4<450)
		{checkDJW+="2";return 2;}
	if(550<sum1&&sum1<625&&550<sum2&&sum2<625&&520<sum3&&sum3<568&&425<sum4&&sum4<475)
		{checkDJW+="3";return 3;}
	if(550<sum1&&sum1<650&&550<sum2&&sum2<650&&550<sum3&&sum3<725&&400<sum4&&sum4<575)
		{checkDJW+="4";return 4;}
	if(550<sum1&&sum1<600&&550<sum2&&sum2<625&&500<sum3&&sum3<550&&450<sum4&&sum4<500)
		{checkDJW+="5";return 5;}
	if(675<sum1&&sum1<725&&600<sum2&&sum2<650&&550<sum3&&sum3<600&&550<sum4&&sum4<600)
		{checkDJW+="6";return 6;}
	if(550<sum1&&sum1<650&&600<sum2&&sum2<725&&475<sum3&&sum3<600&&500<sum4&&sum4<575)
		{checkDJW+="9";return 9;}
	if(625<sum1&&sum1<725&&650<sum2&&sum2<725&&550<sum3&&sum3<625&&550<sum4&&sum4<625)
		{checkDJW+="0";return 0;}
	else 
		{checkDJW+="-255";return -255;}
}

int CDDTHelperDlg::getShapeNum1(CPoint L,CPoint R,int n)
{
int X_Len=R.x-L.x;
	int Y_Len=R.y-L.y;

	if(lineone(n)==9)
		return 5;
    if(lineone(n)==7)
		 if(linetwo(n)==10)
			return 3;
		 else if(linetwo(n)==9)
			 return  8;
	if(lineone(n)==11 )
			return    7;
	if(lineone(n)==3)
			return    1;
	if(lineone(n)==4)
	{
		if(linetwo(n)==5)
			return   4;
		else
			return    1;
	}
	if(lineone(n)==5)
	{
		if(linetwo(n)==5)
			return   4;
		if(linetwo(n)==8)
			return   9;
		else if (linetwo(n)==9)
			return   0;
	}
	if(lineone(n)==6)
		if(linetwo(n)==8)
			return 6;
		else if (linetwo(n)==9)
			if(linethree(n)==6)
				return 2;
			else if(linethree(n)==8)
				return 9;
	return -255;
}

int  CDDTHelperDlg::lineone(int n)
 {
	 CPoint L=Shape3Lpoint[n],R=Shape3Rpoint[n];
	int tar=0;
	for(int  i=L.x; i<=R.x ; i++)
		if((mapA[i][L.y])==n)
			tar++;
	return tar;
}

int  CDDTHelperDlg::linetwo(int n)
{
	CPoint L=Shape3Lpoint[n],R=Shape3Rpoint[n];
	int tar=0;
	for(int i=L.x; i<=R.x ;i++)
		if(mapA[i][L.y+1]==n)
			tar++;
	return  tar;
}

int  CDDTHelperDlg::linethree(int n)
{
	CPoint L=Shape3Lpoint[n],R=Shape3Rpoint[n];
	int tar=0;
	for(int i=L.x; i<=R.x ;i++)
		if(mapA[i][L.y+2]==n)
			tar++;
	return  tar;
}

int CDDTHelperDlg::getShapeNum(CPoint L,CPoint R,int n)
{
	if (L.x>=R.x||L.y>=R.y)
		return -255;

	int b1=0,b2=0,b3=0;
	int x=(L.x+R.x)/2;
	for (int i=L.y+1;i<=R.y-1;i++)
		if (mapA[x-1][i]==1) b1=1;
	for (int i=L.y+1;i<=R.y-1;i++)
		if (mapA[x+0][i]==1) b2=1;
	for (int i=L.y+1;i<=R.y-1;i++)
		if (mapA[x+1][i]==1) b3=1;
	if (b1==0&&b2==0&&b3==0) return 1;

	b1=b2=b3=0;
	int y=R.y;
	for (int i=L.x+1;i<=R.x-1;i++)
		if (mapA[i][y]==1) b1=1;
	for (int i=L.x+1;i<=R.x-1;i++)
		if (mapA[i][y-1]==1) b2=1;
	if (b1==0&&b2==0&&b3==0) return 2;

	b1=b2=b3=0;
	y=L.y;
	for (int i=L.x+1;i<=R.x-1;i++)
		if (mapA[i][y]==1) b1=1;
	for (int i=L.x+1;i<=R.x-1;i++)
		if (mapA[i][y+1]==1) b2=1;
	if (b1==0&&b2==0&&b3==0) {
		if (mapA[L.x+1][y+3]==1)
			return 7;
		else if (mapA[L.x+1][y+3]==n)
			return 5;
	}
	
	b1=b2=b3=0;
	x=(L.x+R.x*3)/4;
	for (int i=L.y+1;i<=R.y-1;i++)
		if (mapA[x-1][i]==1) b1=1;
	for (int i=L.y+1;i<=R.y-1;i++)
		if (mapA[x+0][i]==1) b2=1;
	for (int i=L.y+1;i<=R.y-1;i++)
		if (mapA[x+1][i]==1) b3=1;
	if (b1==0&&b2==0&&b3==0) return 4;
	
	b1=b2=b3=0;
	x=L.x+1;
	for (int i=L.y+1;i<=R.y;i++)
		if (mapA[x][i]!=mapA[x][i-1]) b1++;
	x=(L.x+R.x)/2;
	for (int i=L.y+1;i<=R.y;i++)
		if (mapA[x][i]!=mapA[x][i-1]) b2++;
	x=R.x-1;
	for (int i=L.y+1;i<=R.y;i++)
		if (mapA[x][i]!=mapA[x][i-1]) b3++;
	if (b1==2&&b2==4&&b3==1) return 3;
	if (b1==3&&b2==4&&b3==4) return 3;
	if (b1==2&&b2==4&&b3==3) return 6;
	if (b1==4&&b2==4&&b3==4) return 8;
	if (b1==3&&b2==4&&b3==2) return 9;
	if (b2==2) return 0;
	CString tmp;tmp.Format("%d,%d,%d",b1,b2,b3);
	MessageBox(tmp);
	return -255;
}

int CDDTHelperDlg::checkShape2(void)
{
	CPoint L=Shape3Lpoint[2],R=Shape3Rpoint[2];
	
	CString tmpCS1;
	CFile mFile("mapAN2.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=L.y;j<=R.y;j++){
		for (int i=L.x;i<=R.x;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	

	int ans1=getShapeNum(L,R,2);
	int ans2=getShapeNum1(L,R,2);
	
	mFile.Write(checkDJW,255); 
	mFile.Close();
	//if (ans1==3||ans1==5&&ans2!=-255) checkType=2;

	if (checkType==1)
		return ans1;
	else if (checkType==2)
		return ans2;
	return -255;
}

int CDDTHelperDlg::checkShape3(void)
{
	CPoint L=Shape3Lpoint[3],R=Shape3Rpoint[3];
	
	CString tmpCS1;
	CFile mFile("mapAN3.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=L.y;j<=R.y;j++){
		for (int i=L.x;i<=R.x;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}	
	

	int ans1=getShapeNum(L,R,3);
	int ans2=getShapeNum1(L,R,3);
	
	mFile.Write(checkDJW,255); 
	mFile.Close();
	//if (ans1==3||ans1==5&&ans2!=-255) checkType=2;

	if (checkType==1)
		return ans1;
	else if (checkType==2)
		return ans2;
	return -255;
}

int CDDTHelperDlg::checkShape4(void)
{
	CPoint L=Shape3Lpoint[4],R=Shape3Rpoint[4];
	/*
	CString tmpCS1;
	CFile mFile("mapAN4.txt", CFile::modeWrite|CFile::modeCreate); 
	mFile.Write(setShapetmp,255); 
	for (int j=L.y;j<=R.y;j++){
		for (int i=L.x;i<=R.x;i++)
		{
			tmpCS1.Format("%d",mapA[i][j]);
			mFile.Write(tmpCS1,1); 
		}
			tmpCS1.Format("  %d",j);
			mFile.Write(tmpCS1,4); 
		mFile.Write("\n",8); 
	}
	*/

	int ans1=getShapeNum(L,R,4);
	int ans2=getShapeNum1(L,R,4);
	
	//mFile.Write(checkDJW,255); 
	//mFile.Close();	
	//if (ans1==3||ans1==5&&ans2!=-255) checkType=2;

	if (checkType==1)
		return ans1;
	else if (checkType==2)
		return ans2;
	return -255;
}

void CDDTHelperDlg::OnStnClickedStatic1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDDTHelperDlg::getMap()
{
	HDC hDC = ::GetDC(NULL);
	CPoint pt; 
	GetCursorPos(&pt);
	COLORREF clr = ::GetPixel(hDC, pt.x, pt.y);
	CString s;
	s.Format("%ul",clr);
	m_csCalc.SetWindowText(s);
	m_csState.SetWindowText(s);
}


void CDDTHelperDlg::getMapA()
{
	int r,g,b,middle,angle;
	COLORREF col;
	HDC hDC = ::GetDC(NULL);
	for (int x=anglePos.x-50;x<anglePos.x+50;x++)
		for (int y=anglePos.y-40;y<anglePos.y+40;y++){
			col=::GetPixel(hDC, x, y);
			r= col & 255;
			g= col >> 8 & 255;
			b= col >> 16 & 255;
			middle=(r+b+g)/3;
			if(middle<colorCheckMiddle){
				mapA[x-anglePos.x+51][y-anglePos.y+41]=1;
			}else{
				mapA[x-anglePos.x+51][y-anglePos.y+41]=0;
			}
		}
	::ReleaseDC(NULL,hDC);
}