
// PeopleInOutListDlg.h : 头文件
//

#pragma once


// CPeopleInOutListDlg 对话框
class CPeopleInOutListDlg : public CDialogEx
{
// 构造
public:
	CPeopleInOutListDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PEOPLEINOUTLIST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int listSize[7][500];
	bool boolback;
	CListCtrl m_truck;
	CListCtrl m_leader;
	CListCtrl m_vacate;
	CListCtrl m_subCompany;
	CListCtrl m_civilian;
	CListCtrl m_driver;
	CListCtrl m_stevedore;
	CButton m_in;
	CButton m_out;
	afx_msg void OnBnClickedButton1();
	HBITMAP m_BitmapButton;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	struct Pstream{
		int type;
		int num;
	};
	Pstream pstream;
	struct Pselect{
		void refresh(){type=0;num=-1;name=_T("");}
		int type;
		int num;
		CString name;
	};
	Pselect pselect;
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnNMDblclkList5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList7(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_etruck;
	CEdit m_ecivilian;
	CEdit m_edriver;
	CEdit m_estevedore;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	CString m_cst;
	CString m_csc;
	CString m_csd;
	CString m_css;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnEnKillfocusEdit3();
	afx_msg void OnEnKillfocusEdit4();
	CButton m_btnOK;
	CButton m_c1;
	CButton m_c2;
	CButton m_c3;
	CButton m_c4;
	CButton m_c5;
	CButton m_c6;
	afx_msg void OnBnClickedCheck1();
	void clearCheck();
	void savetxt();
	void loadtxt();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	CListCtrl m_subCompany2;
	CListCtrl m_subCompany3;
	CButton m_back;
	afx_msg void OnNMClickList8(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList9(NMHDR *pNMHDR, LRESULT *pResult);
	void pushBack(CString);
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	void hintSort();
	CEdit m_note;
	CString m_notecs;
};
