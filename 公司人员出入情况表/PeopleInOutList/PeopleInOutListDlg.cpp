
// PeopleInOutListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PeopleInOutList.h"
#include "PeopleInOutListDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CPeopleInOutListDlg �Ի���




CPeopleInOutListDlg::CPeopleInOutListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPeopleInOutListDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_cst = _T("");
	m_csc = _T("");
	m_csd = _T("");
	m_css = _T("");
	m_notecs = _T("");
}

void CPeopleInOutListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_truck);
	DDX_Control(pDX, IDC_LIST2, m_leader);
	DDX_Control(pDX, IDC_LIST3, m_vacate);
	DDX_Control(pDX, IDC_LIST4, m_subCompany);
	DDX_Control(pDX, IDC_LIST5, m_civilian);
	DDX_Control(pDX, IDC_LIST6, m_driver);
	DDX_Control(pDX, IDC_LIST7, m_stevedore);
	DDX_Control(pDX, IDC_BUTTON1, m_in);
	DDX_Control(pDX, IDC_BUTTON2, m_out);
	DDX_Control(pDX, IDC_EDIT1, m_etruck);
	DDX_Control(pDX, IDC_EDIT2, m_ecivilian);
	DDX_Control(pDX, IDC_EDIT3, m_edriver);
	DDX_Control(pDX, IDC_EDIT4, m_estevedore);
	DDX_Text(pDX, IDC_EDIT1, m_cst);
	DDX_Text(pDX, IDC_EDIT2, m_csc);
	DDX_Text(pDX, IDC_EDIT3, m_csd);
	DDX_Text(pDX, IDC_EDIT4, m_css);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_CHECK1, m_c1);
	DDX_Control(pDX, IDC_CHECK2, m_c2);
	DDX_Control(pDX, IDC_CHECK3, m_c3);
	DDX_Control(pDX, IDC_CHECK4, m_c4);
	DDX_Control(pDX, IDC_CHECK5, m_c5);
	DDX_Control(pDX, IDC_CHECK6, m_c6);
	DDX_Control(pDX, IDC_LIST8, m_subCompany2);
	DDX_Control(pDX, IDC_LIST9, m_subCompany3);
	DDX_Control(pDX, IDC_CHECK7, m_back);
	DDX_Control(pDX, IDC_EDIT5, m_note);
	DDX_Text(pDX, IDC_EDIT5, m_notecs);
}

BEGIN_MESSAGE_MAP(CPeopleInOutListDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPeopleInOutListDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPeopleInOutListDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CPeopleInOutListDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPeopleInOutListDlg::OnBnClickedCancel)
	ON_WM_NCHITTEST()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPeopleInOutListDlg::OnNMDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CPeopleInOutListDlg::OnNMDblclkList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &CPeopleInOutListDlg::OnNMDblclkList3)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST4, &CPeopleInOutListDlg::OnNMDblclkList4)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPeopleInOutListDlg::OnNMClickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CPeopleInOutListDlg::OnNMClickList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, &CPeopleInOutListDlg::OnNMClickList3)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, &CPeopleInOutListDlg::OnNMClickList4)
	ON_NOTIFY(NM_CLICK, IDC_LIST5, &CPeopleInOutListDlg::OnNMClickList5)
	ON_NOTIFY(NM_CLICK, IDC_LIST6, &CPeopleInOutListDlg::OnNMClickList6)
	ON_NOTIFY(NM_CLICK, IDC_LIST7, &CPeopleInOutListDlg::OnNMClickList7)
	ON_BN_CLICKED(IDC_BUTTON4, &CPeopleInOutListDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CPeopleInOutListDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CPeopleInOutListDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CPeopleInOutListDlg::OnBnClickedButton6)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST5, &CPeopleInOutListDlg::OnNMDblclkList5)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST6, &CPeopleInOutListDlg::OnNMDblclkList6)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST7, &CPeopleInOutListDlg::OnNMDblclkList7)
	ON_EN_CHANGE(IDC_EDIT1, &CPeopleInOutListDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CPeopleInOutListDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CPeopleInOutListDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CPeopleInOutListDlg::OnEnChangeEdit4)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CPeopleInOutListDlg::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CPeopleInOutListDlg::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CPeopleInOutListDlg::OnEnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, &CPeopleInOutListDlg::OnEnKillfocusEdit4)
	ON_BN_CLICKED(IDC_CHECK1, &CPeopleInOutListDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CPeopleInOutListDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CPeopleInOutListDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CPeopleInOutListDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CPeopleInOutListDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CPeopleInOutListDlg::OnBnClickedCheck6)
	ON_NOTIFY(NM_CLICK, IDC_LIST8, &CPeopleInOutListDlg::OnNMClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST9, &CPeopleInOutListDlg::OnNMClickList9)
	ON_BN_CLICKED(IDC_BUTTON7, &CPeopleInOutListDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CPeopleInOutListDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CPeopleInOutListDlg ��Ϣ�������

BOOL CPeopleInOutListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_NORMAL);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	boolback=0;
	for (int i=0;i<7;i++)
		for (int j=0;j<500;j++)
			listSize[i][j]=0;
	pstream.type=0;
	pstream.num=-1;
	pselect.type=0;
	pselect.num=-1;
	pselect.name=_T("");

	m_BitmapButton = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2));
	m_in.SetBitmap(m_BitmapButton);
	m_BitmapButton = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3));
	m_out.SetBitmap(m_BitmapButton);
	
	m_truck.InsertColumn(1,_T("���ƺ�"),LVCFMT_CENTER,70);
	m_truck.InsertColumn(2,_T("��ʻԱ"),LVCFMT_CENTER,70);
	m_truck.InsertColumn(3,_T("������Ա"),LVCFMT_CENTER,70);
	m_truck.InsertColumn(4,_T("������Ա"),LVCFMT_CENTER,70);
	m_truck.InsertColumn(5,_T("������Ա"),LVCFMT_CENTER,70);
	m_truck.InsertColumn(6,_T("������Ա"),LVCFMT_CENTER,70);
	m_truck.InsertColumn(7,_T("ȥ��"),LVCFMT_LEFT,255);
	
	m_leader.InsertColumn(1,_T("�����쵼"),LVCFMT_CENTER,96);
	m_vacate.InsertColumn(1,_T("�����Ա"),LVCFMT_CENTER,94);
	m_subCompany.InsertColumn(1,_T("�ֹ�˾1"),LVCFMT_CENTER,77);
	m_subCompany2.InsertColumn(1,_T("�ֹ�˾2"),LVCFMT_CENTER,77);
	m_subCompany3.InsertColumn(1,_T("�ֹ�˾3"),LVCFMT_CENTER,77);
	
	m_civilian.InsertColumn(1,_T("��ְ��Ա"),LVCFMT_CENTER,98);
	m_civilian.InsertColumn(2,_T("��"),LVCFMT_CENTER,30);
	m_driver.InsertColumn(1,_T("��ʻԱ"),LVCFMT_CENTER,98);
	m_driver.InsertColumn(2,_T("��"),LVCFMT_CENTER,30);
	m_stevedore.InsertColumn(1,_T("������Ա"),LVCFMT_CENTER,98);
	m_stevedore.InsertColumn(2,_T("��"),LVCFMT_CENTER,30);
	
	//m_note.set

	m_truck.SetExtendedStyle(LVS_EX_FULLROWSELECT); //ѡ��һ����
	m_leader.SetExtendedStyle(LVS_EX_FULLROWSELECT); //ѡ��һ����
	m_vacate.SetExtendedStyle(LVS_EX_FULLROWSELECT); //ѡ��һ����
	m_subCompany.SetExtendedStyle(LVS_EX_FULLROWSELECT); //ѡ��һ����
	m_subCompany2.SetExtendedStyle(LVS_EX_FULLROWSELECT); //ѡ��һ����
	m_subCompany3.SetExtendedStyle(LVS_EX_FULLROWSELECT); //ѡ��һ����
	m_civilian.SetExtendedStyle(LVS_EX_FULLROWSELECT); //ѡ��һ����
	m_driver.SetExtendedStyle(LVS_EX_FULLROWSELECT); //ѡ��һ����
	m_stevedore.SetExtendedStyle(LVS_EX_FULLROWSELECT); //ѡ��һ����

	loadtxt();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPeopleInOutListDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPeopleInOutListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPeopleInOutListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPeopleInOutListDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_c1.GetCheck())
		pstream.type=1;
	else if (m_c2.GetCheck())
		pstream.type=2;
	else if (m_c3.GetCheck())
		pstream.type=3;
	else if (m_c4.GetCheck())
		pstream.type=4;
	else if (m_c5.GetCheck())
		pstream.type=5;
	else if (m_c6.GetCheck())
		pstream.type=6;
	else
		pstream.type=0;
	if (m_notecs!=_T(""))
	{
		if (pstream.num==-1){
			MessageBox(_T("��עδѡ��Ŀ�공����"));
			return;
		}
		m_truck.SetItemText(pstream.num,6,m_notecs);
		m_note.SetWindowTextA(_T(""));
		return;
	}
	if (pselect.type!=0){
		CString tmpType=_T("");
		if (pstream.type>=1&&pstream.type<=6
			&&
			!(pstream.num==-1&&pstream.type==1)
			&&
			!(pstream.type==1&&listSize[1][pstream.num]>=5))
			switch (pselect.type){
			case 1:
				tmpType=_T("(��)");
				m_civilian.DeleteItem(pselect.num);
				m_civilian.UpdateWindow();
				break;
			case 2:
				tmpType=_T("(��)");
				m_driver.DeleteItem(pselect.num);;
				m_driver.UpdateWindow();
				break;
			case 3:
				tmpType=_T("(��)");
				m_stevedore.DeleteItem(pselect.num);;
				m_stevedore.UpdateWindow();
				break;
			default:
				break;
			}
		switch (pstream.type){
		case 1:
			if (pstream.num==-1)
				MessageBox(_T("δѡ����Աȥ����"));
			else if (listSize[1][pstream.num]>=5)
				MessageBox(_T("�˳���Ա������"));
			else
				m_truck.SetItemText(pstream.num,++listSize[1][pstream.num],tmpType+pselect.name);
				pselect.refresh();
			break;
		case 2:
			m_leader.InsertItem(++listSize[2][0],tmpType+pselect.name);
			pselect.refresh();
			break;
		case 3:
			m_vacate.InsertItem(++listSize[3][0],tmpType+pselect.name);
			pselect.refresh();
			break;
		case 4:
			m_subCompany.InsertItem(++listSize[4][0],tmpType+pselect.name);
			pselect.refresh();
			break;
		case 5:
			m_subCompany2.InsertItem(++listSize[5][0],tmpType+pselect.name);
			pselect.refresh();
			break;
		case 6:
			m_subCompany3.InsertItem(++listSize[6][0],tmpType+pselect.name);
			pselect.refresh();
			break;
		default:
			MessageBox(_T("δѡ����Աȥ����"));
		}
	}
	hintSort();
}


void CPeopleInOutListDlg::pushBack(CString tmp)
{
	int type=0;
	CString tmpCS=tmp.Left(3);
	tmpCS=tmpCS.Right(2);
	if (tmpCS==_T("��"))
		type=1;
	else if (tmpCS==_T("��"))
		type=2;
	else if (tmpCS==_T("��"))
		type=3;
	else{
		MessageBox(_T("���Իص�δ֪��ݵĲ�����Ա��"));
		return;
	}
	tmp=tmp.Right(tmp.GetLength()-4);
	switch (type){
	case 1:
		m_civilian.InsertItem(m_civilian.GetItemCount(),tmp);
		break;
	case 2:
		m_driver.InsertItem(m_driver.GetItemCount(),tmp);
		break;
	case 3:
		m_stevedore.InsertItem(m_stevedore.GetItemCount(),tmp);
		break;
	}
}


void CPeopleInOutListDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!boolback){
		if (m_c1.GetCheck())
			pstream.type=1;
		else if (m_c2.GetCheck())
			pstream.type=2;
		else if (m_c3.GetCheck())
			pstream.type=3;
		else if (m_c4.GetCheck())
			pstream.type=4;
		else if (m_c5.GetCheck())
			pstream.type=5;
		else if (m_c6.GetCheck())
			pstream.type=6;
		else 
			pstream.type=0;
	}else{
		boolback=0;
		m_back.SetCheck(false);
		if (pstream.type==2){
			pushBack(m_leader.GetItemText(pstream.num,0));
			--listSize[2][0];
			m_leader.DeleteItem(pstream.num);
		}else if (pstream.type==3){
			pushBack(m_vacate.GetItemText(pstream.num,0));
			--listSize[3][0];
			m_vacate.DeleteItem(pstream.num);
		}else if (pstream.type==4){
			pushBack(m_subCompany.GetItemText(pstream.num,0));
			--listSize[4][0];
			m_subCompany.DeleteItem(pstream.num);
		}else if (pstream.type==8){
			pushBack(m_subCompany2.GetItemText(pstream.num,0));
			--listSize[5][0];
			m_subCompany2.DeleteItem(pstream.num);
		}else if (pstream.type==9){
			pushBack(m_subCompany3.GetItemText(pstream.num,0));
			--listSize[6][0];
			m_subCompany3.DeleteItem(pstream.num);
		}
		return;
	}
	switch (pstream.type){
	case 1:{
		if (pstream.num==-1)
			MessageBox(_T("δѡ����Աȥ����"));
		else{
			int   nItem=-1; 
			nItem   =   m_truck.GetNextItem(nItem,   LVNI_SELECTED); 
			if(nItem==-1)   return; 
			if(MessageBox(_T("ȷʵҪ��մ�ѡ�г�����"),_T("��վ���"),MB_YESNO|MB_ICONQUESTION)==IDYES)
			{
				for (int i=1;i<=listSize[1][nItem];i++){
					pushBack(m_truck.GetItemText(nItem,i));
					m_truck.SetItemText(nItem,i,_T(""));
				}
				m_truck.SetItemText(nItem,6,_T(""));
				listSize[1][nItem]=0;
				m_truck.UpdateWindow();
			}
		}
		break;   }
	case 2:
		if(MessageBox(_T("ȷʵҪ��������쵼��"),_T("��վ���"),MB_YESNO|MB_ICONQUESTION)==IDYES)
		{
			for (int i=0;i<m_leader.GetItemCount();i++)
				pushBack(m_leader.GetItemText(i,0));
			m_leader.DeleteAllItems();
			m_leader.UpdateWindow();
		}
		break;
	case 3:
		if(MessageBox(_T("ȷʵҪ��������Ա��"),_T("��վ���"),MB_YESNO|MB_ICONQUESTION)==IDYES)
		{
			for (int i=0;i<m_vacate.GetItemCount();i++)
				pushBack(m_vacate.GetItemText(i,0));
			m_vacate.DeleteAllItems();
			m_vacate.UpdateWindow();
		}
		break;
	case 4:
		if(MessageBox(_T("ȷʵҪ��շֹ�˾1��"),_T("��վ���"),MB_YESNO|MB_ICONQUESTION)==IDYES)
		{
			for (int i=0;i<m_subCompany.GetItemCount();i++)
				pushBack(m_subCompany.GetItemText(i,0));
			m_subCompany.DeleteAllItems();
			m_subCompany.UpdateWindow();
		}
		break;
	case 5:
		if(MessageBox(_T("ȷʵҪ��շֹ�˾2��"),_T("��վ���"),MB_YESNO|MB_ICONQUESTION)==IDYES)
		{
			for (int i=0;i<m_subCompany2.GetItemCount();i++)
				pushBack(m_subCompany2.GetItemText(i,0));
			m_subCompany2.DeleteAllItems();
			m_subCompany2.UpdateWindow();
		}
		break;
	case 6:
		if(MessageBox(_T("ȷʵҪ��շֹ�˾3��"),_T("��վ���"),MB_YESNO|MB_ICONQUESTION)==IDYES)
		{
			for (int i=0;i<m_subCompany3.GetItemCount();i++)
				pushBack(m_subCompany3.GetItemText(i,0));
			m_subCompany3.DeleteAllItems();
			m_subCompany3.UpdateWindow();
		}
		break;
	default:
		MessageBox(_T("δѡ����Աȥ����"));
	}
	hintSort();
}


void CPeopleInOutListDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	m_btnOK.SetFocus();
	m_btnOK.EnableWindow(false);
}


void CPeopleInOutListDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBox(_T("ȷʵҪ�˳�������"),_T("�˳�����"),MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		if(MessageBox(_T("��Ҫ���˳�֮ǰҪ�浵�𣬴˲��������浱ǰ���ݣ�"),_T("�浵����"),MB_YESNO|MB_ICONQUESTION)==IDYES)
		{
			savetxt();
		}
		CDialogEx::OnCancel();
	}
}


LRESULT CPeopleInOutListDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	return HTCAPTION;//�����ͻ�������κεط������ر����������϶�����
}


void CPeopleInOutListDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int   nItem=-1; 
	nItem   =   m_truck.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	CString strSelectedFileName;
	strSelectedFileName=m_truck.GetItemText(nItem,   0  );
	if(strSelectedFileName!=_T("----------------"))
		if(MessageBox(_T("ȷʵҪɾ����ѡ�г�����"),_T("ɾ������"),MB_YESNO|MB_ICONQUESTION)==IDYES)
		{
			m_truck.DeleteItem(nItem);
			m_truck.DeleteItem(nItem);
			m_truck.UpdateWindow();
			UpdateData();
		}

	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMDblclkList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMDblclkList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	int   nItem=-1; 
	nItem   =   m_truck.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return;
	CString strSelectedFileName;
	strSelectedFileName=m_truck.GetItemText(nItem,   0  );
	if(strSelectedFileName==_T("----------------"))		{
		//MessageBox(_T("ѡ���˳���"+strSelectedFileName));
		m_in.SetFocus();
		return;
	}
	//pstream.type=1;
	pstream.num=nItem;
	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int   nItem=-1; 
	nItem   =   m_leader.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	clearCheck();
	m_back.SetCheck(true);
	pstream.type=2;
	boolback=true;
	pstream.num=nItem;
	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int   nItem=-1; 
	nItem   =   m_vacate.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	clearCheck();
	m_back.SetCheck(true);
	pstream.type=3;
	boolback=true;
	pstream.num=nItem;
	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int   nItem=-1; 
	nItem   =   m_subCompany.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	clearCheck();
	m_back.SetCheck(true);
	pstream.type=4;
	boolback=true;
	pstream.num=nItem;
	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMClickList5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	int   nItem=-1; 
	nItem   =   m_civilian.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	CString   strSelectedFileName; 
	strSelectedFileName=m_civilian.GetItemText(nItem,   0   )   ; 
	pselect.type=1;
	pselect.num=nItem;
	pselect.name=strSelectedFileName;

	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMClickList6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	int   nItem=-1; 
	nItem   =   m_driver.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	CString   strSelectedFileName; 
	strSelectedFileName=m_driver.GetItemText(nItem,   0   )   ; 
	pselect.type=2;
	pselect.num=nItem;
	pselect.name=strSelectedFileName;

	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMClickList7(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	int   nItem=-1; 
	nItem   =   m_stevedore.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	CString   strSelectedFileName; 
	strSelectedFileName=m_stevedore.GetItemText(nItem,   0   )   ;
	pselect.type=3; 
	pselect.num=nItem;
	pselect.name=strSelectedFileName;

	*pResult = 0;
}


void CPeopleInOutListDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_etruck.EnableWindow(true);
	m_etruck.SetFocus();
	m_btnOK.EnableWindow(true);
}


void CPeopleInOutListDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ecivilian.EnableWindow(true);
	m_ecivilian.SetFocus();
	m_btnOK.EnableWindow(true);
}


void CPeopleInOutListDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_edriver.EnableWindow(true);
	m_edriver.SetFocus();
	m_btnOK.EnableWindow(true);
}


void CPeopleInOutListDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_estevedore.EnableWindow(true);
	m_estevedore.SetFocus();
	m_btnOK.EnableWindow(true);
}


void CPeopleInOutListDlg::OnNMDblclkList5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int   nItem=-1; 
	nItem   =   m_civilian.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	if(MessageBox(_T("ȷʵҪɾ����ѡ����Ա��"),_T("ɾ������"),MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		m_civilian.DeleteItem(nItem);
		m_civilian.UpdateWindow();
		UpdateData();
	}
	hintSort();
	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMDblclkList6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int   nItem=-1; 
	nItem   =   m_driver.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	if(MessageBox(_T("ȷʵҪɾ����ѡ����Ա��"),_T("ɾ������"),MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		m_driver.DeleteItem(nItem);
		m_driver.UpdateWindow();
		UpdateData();
	}
	hintSort();
	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMDblclkList7(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int   nItem=-1; 
	nItem   =   m_stevedore.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	if(MessageBox(_T("ȷʵҪɾ����ѡ����Ա��"),_T("ɾ������"),MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		m_stevedore.DeleteItem(nItem);
		m_stevedore.UpdateWindow();
		UpdateData();
	}
	hintSort();
	*pResult = 0;
}


void CPeopleInOutListDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
}


void CPeopleInOutListDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
}


void CPeopleInOutListDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
}


void CPeopleInOutListDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
}


void CPeopleInOutListDlg::OnEnKillfocusEdit1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnEnChangeEdit1();
	if (m_cst!=(_T("")))
	{
		m_truck.InsertItem(m_truck.GetItemCount(),m_cst);
		listSize[1][m_truck.GetItemCount()]=7;
		m_truck.InsertItem(m_truck.GetItemCount(),_T("----------------"));
		m_truck.SetItemText(m_truck.GetItemCount()-1,1,_T("--------------"));
		m_truck.SetItemText(m_truck.GetItemCount()-1,2,_T("--------------"));
		m_truck.SetItemText(m_truck.GetItemCount()-1,3,_T("--------------"));
		m_truck.SetItemText(m_truck.GetItemCount()-1,4,_T("--------------"));
		m_truck.SetItemText(m_truck.GetItemCount()-1,5,_T("--------------"));
		m_truck.SetItemText(m_truck.GetItemCount()-1,6,_T("--------------------------------------------------"));
	}
	m_etruck.SetWindowText(_T(""));
	m_etruck.EnableWindow(false);
}


void CPeopleInOutListDlg::OnEnKillfocusEdit2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnEnChangeEdit2();
	if (m_csc!=(_T("")))
		m_civilian.InsertItem(m_civilian.GetItemCount(),m_csc);
	m_ecivilian.SetWindowText(_T(""));
	m_ecivilian.EnableWindow(false);
	hintSort();
}


void CPeopleInOutListDlg::OnEnKillfocusEdit3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnEnChangeEdit3();
	if (m_csd!=(_T("")))
		m_driver.InsertItem(m_driver.GetItemCount(),m_csd);
	m_edriver.SetWindowText(_T(""));
	m_edriver.EnableWindow(false);
	hintSort();
}


void CPeopleInOutListDlg::OnEnKillfocusEdit4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnEnChangeEdit4();
	if (m_css!=(_T("")))
		m_stevedore.InsertItem(m_stevedore.GetItemCount(),m_css);
	m_estevedore.SetWindowText(_T(""));
	m_estevedore.EnableWindow(false);
	hintSort();
}

void CPeopleInOutListDlg::clearCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_c1.SetCheck(false);
	m_c2.SetCheck(false);
	m_c3.SetCheck(false);
	m_c4.SetCheck(false);
	m_c5.SetCheck(false);
	m_c6.SetCheck(false);
	m_back.SetCheck(false);
	pstream.num=-1;
	pstream.type=0;
	boolback=0;
}

void CPeopleInOutListDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	clearCheck();
	m_c1.SetCheck(true);
	MessageBox(_T("���ڳ��������е���ĳһ���ƺ�ѡ�о��峵����"));
}


void CPeopleInOutListDlg::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	clearCheck();
	m_c2.SetCheck(true);
}


void CPeopleInOutListDlg::OnBnClickedCheck3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	clearCheck();
	m_c3.SetCheck(true);
}


void CPeopleInOutListDlg::OnBnClickedCheck4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	clearCheck();
	m_c4.SetCheck(true);
}


void CPeopleInOutListDlg::OnBnClickedCheck5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	clearCheck();
	m_c5.SetCheck(true);
}


void CPeopleInOutListDlg::OnBnClickedCheck6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	clearCheck();
	m_c6.SetCheck(true);
}


void CPeopleInOutListDlg::OnNMClickList8(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int   nItem=-1; 
	nItem   =   m_subCompany2.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	clearCheck();
	m_back.SetCheck(true);
	pstream.type=8;
	boolback=true;
	pstream.num=nItem;
	*pResult = 0;
}


void CPeopleInOutListDlg::OnNMClickList9(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int   nItem=-1; 
	nItem   =   m_subCompany3.GetNextItem(nItem,   LVNI_SELECTED); 
	if(nItem==-1)   return; 
	clearCheck();
	m_back.SetCheck(true);
	pstream.type=9;
	boolback=true;
	pstream.num=nItem;
	*pResult = 0;
}

void CPeopleInOutListDlg::savetxt()
{
	CString tmpCS;
	CStdioFile mFile(_T("PIOL�浵�ļ�.txt"), CFile::modeWrite|CFile::modeCreate); 
	for (int i=0;i<7;i++)
		for (int j=0;j<500;j++){
			tmpCS.Format(_T("%d\n"),listSize[i][j]);
			mFile.WriteString(tmpCS);
		}

	tmpCS.Format(_T("%d\n"),m_truck.GetItemCount());
	mFile.WriteString(tmpCS);
	for (int j=0;j<m_truck.GetItemCount();j++)
		for (int i=0;i<=listSize[1][j];i++){
			mFile.WriteString(m_truck.GetItemText(j,i));
			mFile.WriteString(_T("\n"));
			//MessageBox(m_truck.GetItemText(j,i));
		}

	tmpCS.Format(_T("%d\n"),m_leader.GetItemCount());
	mFile.WriteString(tmpCS);
	for (int i=0;i<m_leader.GetItemCount();i++){
		mFile.WriteString(m_leader.GetItemText(i,0));
		mFile.WriteString(_T("\n"));
	}
	
	tmpCS.Format(_T("%d\n"),m_vacate.GetItemCount());
	mFile.WriteString(tmpCS);
	for (int i=0;i<m_vacate.GetItemCount();i++){
		mFile.WriteString(m_vacate.GetItemText(i,0));
		mFile.WriteString(_T("\n"));
	}

	tmpCS.Format(_T("%d\n"),m_subCompany.GetItemCount());
	mFile.WriteString(tmpCS);
	for (int i=0;i<m_subCompany.GetItemCount();i++){
		mFile.WriteString(m_subCompany.GetItemText(i,0));
		mFile.WriteString(_T("\n"));
	}

	tmpCS.Format(_T("%d\n"),m_subCompany2.GetItemCount());
	mFile.WriteString(tmpCS);
	for (int i=0;i<m_subCompany2.GetItemCount();i++){
		mFile.WriteString(m_subCompany2.GetItemText(i,0));
		mFile.WriteString(_T("\n"));
	}
	
	tmpCS.Format(_T("%d\n"),m_subCompany3.GetItemCount());
	mFile.WriteString(tmpCS);
	for (int i=0;i<m_subCompany3.GetItemCount();i++){
		mFile.WriteString(m_subCompany3.GetItemText(i,0));
		mFile.WriteString(_T("\n"));
	}

	tmpCS.Format(_T("%d\n"),m_civilian.GetItemCount());
	mFile.WriteString(tmpCS);
	for (int i=0;i<m_civilian.GetItemCount();i++){
		mFile.WriteString(m_civilian.GetItemText(i,0));
		mFile.WriteString(_T("\n"));
	}

	tmpCS.Format(_T("%d\n"),m_driver.GetItemCount());
	mFile.WriteString(tmpCS);
	for (int i=0;i<m_driver.GetItemCount();i++){
		mFile.WriteString(m_driver.GetItemText(i,0));
		mFile.WriteString(_T("\n"));
	}

	tmpCS.Format(_T("%d\n"),m_stevedore.GetItemCount());
	mFile.WriteString(tmpCS);
	for (int i=0;i<m_stevedore.GetItemCount();i++){
		mFile.WriteString(m_stevedore.GetItemText(i,0));
		mFile.WriteString(_T("\n"));
	}
	
	tmpCS.Format(_T("%d\n"),m_truck.GetItemCount());
	mFile.WriteString(tmpCS);
	for (int i=1;i<m_truck.GetItemCount();i++){
		mFile.WriteString(m_truck.GetItemText(i,6));
		mFile.WriteString(_T("\n"));
	}

	mFile.Close();	
}

void CPeopleInOutListDlg::loadtxt()
{
	CString tmpCS;
	CStdioFile mFile(_T("PIOL�浵�ļ�.txt"), CFile::modeNoTruncate); 
	for (int i=0;i<7;i++)
		for (int j=0;j<500;j++){
			mFile.ReadString(tmpCS);
			listSize[i][j]=atoi(tmpCS);
			/*
			tmpCS.Format(_T("%d"),listSize[i][j]);
			if (listSize[i][j]!=0) MessageBox(tmpCS);
			*/
		}

	mFile.ReadString(tmpCS);
	int truckItemConut=atoi(tmpCS);
	m_truck.DeleteAllItems();
	for (int j=0;j<truckItemConut;j++){
		mFile.ReadString(tmpCS);
		m_truck.InsertItem(j,tmpCS);
		for (int i=1;i<=listSize[1][j];i++){
			mFile.ReadString(tmpCS);
			m_truck.SetItemText(j,i,tmpCS);
			//MessageBox(tmpCS);
		}
	}

	mFile.ReadString(tmpCS);
	int leaderCount=atoi(tmpCS);
	m_leader.DeleteAllItems();
	for (int i=0;i<leaderCount;i++){
		mFile.ReadString(tmpCS);
		m_leader.InsertItem(i,tmpCS);
	}

	mFile.ReadString(tmpCS);
	int vacateCount=atoi(tmpCS);
	m_vacate.DeleteAllItems();
	for (int i=0;i<vacateCount;i++){
		mFile.ReadString(tmpCS);
		m_vacate.InsertItem(i,tmpCS);
	}

	mFile.ReadString(tmpCS);
	int sCCount=atoi(tmpCS);
	m_subCompany.DeleteAllItems();
	for (int i=0;i<sCCount;i++){
		mFile.ReadString(tmpCS);
		m_subCompany.InsertItem(i,tmpCS);
	}

	mFile.ReadString(tmpCS);
	int sC2Count=atoi(tmpCS);
	m_subCompany2.DeleteAllItems();
	for (int i=0;i<sC2Count;i++){
		mFile.ReadString(tmpCS);
		m_subCompany2.InsertItem(i,tmpCS);
	}
	
	mFile.ReadString(tmpCS);
	int sC3Count=atoi(tmpCS);
	m_subCompany3.DeleteAllItems();
	for (int i=0;i<sC3Count;i++){
		mFile.ReadString(tmpCS);
		m_subCompany3.InsertItem(i,tmpCS);
	}
	
	mFile.ReadString(tmpCS);
	int civilianCount=atoi(tmpCS);
	m_civilian.DeleteAllItems();
	for (int i=0;i<civilianCount;i++){
		mFile.ReadString(tmpCS);
		m_civilian.InsertItem(i,tmpCS);
	}

	mFile.ReadString(tmpCS);
	int driverCount=atoi(tmpCS);
	m_driver.DeleteAllItems();
	for (int i=0;i<driverCount;i++){
		mFile.ReadString(tmpCS);
		m_driver.InsertItem(i,tmpCS);
	}

	mFile.ReadString(tmpCS);
	int stevedoreCount=atoi(tmpCS);
	m_stevedore.DeleteAllItems();
	for (int i=0;i<stevedoreCount;i++){
		mFile.ReadString(tmpCS);
		m_stevedore.InsertItem(i,tmpCS);
	}
	
	mFile.ReadString(tmpCS);
	int truckNoteCount=atoi(tmpCS);
	for (int i=1;i<truckNoteCount;i++){
		mFile.ReadString(tmpCS);
		m_truck.SetItemText(i,6,tmpCS);
	}

	mFile.Close();	

	hintSort();
}

void CPeopleInOutListDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBox(_T("ȷʵҪ�浵�𣬴˲��������浱ǰ���ݣ�"),_T("�浵����"),MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		savetxt();
	}
}


void CPeopleInOutListDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBox(_T("ȷʵҪ��ȡ�浵�𣬴˲�����Ĩ������δ�浵���ݣ�������������"),_T("��������"),MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		loadtxt();
	}
}

void CPeopleInOutListDlg::hintSort()
{
	for (int i=0;i<m_civilian.GetItemCount();i++){
		CString tmpCS;
		tmpCS.Format("%d",i+1);
		m_civilian.SetItemText(i,1,tmpCS);
	}
	for (int i=0;i<m_driver.GetItemCount();i++){
		CString tmpCS;
		tmpCS.Format("%d",i+1);
		m_driver.SetItemText(i,1,tmpCS);
	}
	for (int i=0;i<m_stevedore.GetItemCount();i++){
		CString tmpCS;
		tmpCS.Format("%d",i+1);
		m_stevedore.SetItemText(i,1,tmpCS);
	}
}