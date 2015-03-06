#if !defined(AFX_XTPWND_H__DE1DD95C_0BE3_4CEA_B437_7B413D1FC536__INCLUDED_)
#define AFX_XTPWND_H__DE1DD95C_0BE3_4CEA_B437_7B413D1FC536__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XTPWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
/*
���о�CDC
ʵ��͸�����ڻ�Ŵ󾵴���Ч��

������������·

awzzz/2002/05/27
awzzz999@163.com
*/

/////////////////////////////////////////////////////////////////////////////
int XDC2MemDC(CDC *pDC, CDC *pMemDC);
int XCWnd2MemDC(CWnd *pWnd, CDC *pMemDC);
CDC *XSaveCWnd(CWnd *pWnd);

/////////////////////////////////////////////////////////////////////////////
// CXTPWnd window

class CXTPWnd : public CWnd
{
// Construction
public:
	CXTPWnd();

// Attributes
public:
	int m_zoom;
	CDC *m_pMemDC;
	CDC* getCDC()	{	return m_pMemDC;	}
	/*CDC* refreshCDC()	{
		//DeskTopWnd
		//CDC *m_pMemDC = new CDC;
		CWnd *pDeskTopWnd = new CWnd;
		pDeskTopWnd->Attach(::GetDesktopWindow());
		CDC *pMemDC = XSaveCWnd(pDeskTopWnd);
		CDC *pMemDC=new CDC;
		return pMemDC;
		//CDC *pDC = pDeskTopWnd->GetDC();
		//	CDC *pMemDC = new CDC;
		//	XCWnd2MemDC(pDeskTopWnd, pMemDC);

		
		if (m_pMemDC && pMemDC)
		{
			m_pMemDC->DeleteDC();
			delete m_pMemDC;
		}
		
		if (pMemDC)
			m_pMemDC = pMemDC;

		pDeskTopWnd->Detach();
		delete pDeskTopWnd;
		

	}*/
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTPWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void XOwnerDraw();
	void XSaveScreen();
	void XCreate(LPCTSTR lpszWindowName = "XTPWnd");
	virtual ~CXTPWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXTPWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XTPWND_H__DE1DD95C_0BE3_4CEA_B437_7B413D1FC536__INCLUDED_)
