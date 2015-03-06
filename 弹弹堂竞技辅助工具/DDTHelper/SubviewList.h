#include "DDTHelper.h"
#pragma once


// SubviewList 对话框

class SubviewList : public CDialog
{
	DECLARE_DYNAMIC(SubviewList)
	void pressBlank(int,int);
	void pressQuick(void);
	void Visual();
	void UnVisual();
	void Behind();
	int boolBehind;
	int boolB1;
	int boolB2;
	int boolTimer;
	int boolTimer1;
	int angleOld;
	CWnd *IEWnd;
public:
	SubviewList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SubviewList();

// 对话框数据
	enum { IDD = IDD_SUBVIEWLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListTable;
	virtual BOOL OnInitDialog();
	void myinit();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CButton m_bBehind;
	afx_msg void OnBnClickedCancel3();
	afx_msg void OnBnClickedCancel2();
	CButton m_b2;
	CButton m_b3;
	CButton m_b1;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_refresh;
	CButton m_q1;
	CButton m_qf;
	CButton m_qr;
	CButton m_qq;
	CButton m_qe;
	CButton m_qz;
	CButton m_qx;
	CButton m_qc;
	CButton m_q2;
	CButton m_qb;
	CButton m_q3;
	CButton m_q4;
	CButton m_q5;
	CButton m_q6;
	CButton m_q7;
	CButton m_q8;
	CEdit m_e1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	CString m_cs1;
	afx_msg void OnEnSetfocusEdit1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	CButton m_bool;
	afx_msg void OnBnClickedButton8();
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	void changeAngle(CDC*,int);
	void checkChangeAngle(CDC*,int);
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnEnChangeEdit4();
//	CString m_cs2;
	afx_msg void OnEnSetfocusEdit4();
	CEdit m_e4;
	afx_msg void OnBnClickedButton13();
	CString m_cs2;
	afx_msg void OnBnClickedButton14();
	CButton m_q42;
	CButton m_q52;
	CButton m_q62;
	CButton m_q72;
	CButton m_q82;
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
};
