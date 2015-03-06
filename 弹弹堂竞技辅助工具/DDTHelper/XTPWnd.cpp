// XTPWnd.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
#include "DDTHelper.h"
#include "XTPWnd.h"
#include "DDTHelperDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//(CDC *pDC) => (CDC *pMemDC)
int XDC2MemDC(CDC *pDC, CDC *pMemDC)
{
	if (pDC && pMemDC && !pMemDC->m_hDC)
	{
		int cx, cy;
		cx = GetSystemMetrics(SM_CXSCREEN);
		cy = GetSystemMetrics(SM_CYSCREEN);

		CWnd *pWnd = pDC->GetWindow();
		if (pWnd)
		{
			CRect rect;
			pWnd->GetWindowRect(rect);
			//cx = rect.Width();//GetSystemMetrics(SM_CXSCREEN);
			//cy = rect.Height();//GetSystemMetrics(SM_CYSCREEN);
		}

		//CDC *pDC;
		pMemDC->CreateCompatibleDC(pDC);

		CBitmap bmp;
		bmp.CreateCompatibleBitmap(pDC, cx, cy);

		pMemDC->SelectObject(&bmp);
		pMemDC->BitBlt(0, 0, cx, cy, pDC, 0, 0, SRCCOPY);
		
		//ץ��ץɫʱ�Ŵ���Ϊ��ֵͼ
		CWnd *p=AfxGetApp()->GetMainWnd();
		CDDTHelperDlg *pd=(CDDTHelperDlg*)p;
		if (pd->boolColorDouble){
			int r,g,b,middle;
			COLORREF col;
			for (int x=1;x<1366;x++)
				for (int y=1;y<768;y++){
					col=pMemDC->GetPixel(x,y);
					r= col & 255;
					g= col >> 8 & 255;
					b= col >> 16 & 255;
					middle=(r+b+g)/3;
					if(middle<colorCheckMiddle){
						pMemDC->SetPixel(x,y,0);
					}else{
						pMemDC->SetPixel(x,y,0xFFFFFF);
					}
				}
		}

		::DeleteObject(bmp.m_hObject);

		return 1;
	}
	return 0;
}

//(CWnd *pWnd) => (CDC *pMemDC)
//	need: XDC2MemDC(...)
int XCWnd2MemDC(CWnd *pWnd, CDC *pMemDC)
{
	if (pWnd)
		return XDC2MemDC(pWnd->GetDC(), pMemDC);

	return 0;
}

CDC *XSaveCWnd(CWnd *pWnd)
{
	if (pWnd)
	{
		CDC *pMemDC = new CDC;
		XCWnd2MemDC(pWnd, pMemDC);

		return pMemDC;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CXTPWnd

CXTPWnd::CXTPWnd()
{
	m_zoom = 1;
	m_pMemDC = NULL;
	/*
	if (MessageBox("�Ƿ�ʹ�÷Ŵ�Ч����", NULL, MB_YESNO) == IDYES)
		m_zoom = 1;
	*/
}

CXTPWnd::~CXTPWnd()
{
	if (m_pMemDC)
	{
		m_pMemDC->DeleteDC();

		delete m_pMemDC;
		m_pMemDC = NULL;
	}
}


BEGIN_MESSAGE_MAP(CXTPWnd, CWnd)
	//{{AFX_MSG_MAP(CXTPWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_ACTIVATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CXTPWnd message handlers

void CXTPWnd::XCreate(LPCTSTR lpszWindowName)
{
	if (m_hWnd) return;
	CreateEx(
		0,//WS_EX_TOPMOST,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		lpszWindowName,
		WS_POPUP,//|WS_BORDER,//WS_OVERLAPPEDWINDOW,
		0, 0, sizeOFBigeyes, sizeOFBigeyes,
		NULL,
		NULL,
		NULL
		);
	CenterWindow();
	ShowWindow(SW_SHOW);
}

void CXTPWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	PostMessage (WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	
	CWnd::OnLButtonDown(nFlags, point);
}

//#include "TPWndDlg.h"
void CXTPWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CTPWndDlg dlg;
	//if (dlg.DoModal() == IDOK)
	/*
	if (MessageBox("ȷ����������", NULL, MB_OKCANCEL) == IDOK)
		DestroyWindow();
	*/
	CWnd::OnRButtonDown(nFlags, point);
}

void CXTPWnd::XSaveScreen()
{
	ShowWindow(SW_HIDE);

	//DeskTopWnd
	CWnd *pDeskTopWnd = new CWnd;
	pDeskTopWnd->Attach(::GetDesktopWindow());
	CDC *pMemDC = XSaveCWnd(pDeskTopWnd);

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

	ShowWindow(SW_SHOW);
}

void CXTPWnd::XOwnerDraw()
{
	CDC *pDC = GetDC();
	if (pDC && m_pMemDC)
	{
		CRect clientRect;
		CRect windowRect;
		GetClientRect(clientRect);
		GetWindowRect(windowRect);
		int rectsize=timesOFBigeyes/2+timesOFBigeyes%2;

		if (!m_zoom)//������ʾ
		{
			pDC->BitBlt(
				clientRect.left, clientRect.top, clientRect.Width(), clientRect.Height(),
				m_pMemDC,
				windowRect.left, windowRect.top, SRCCOPY
				);
		}
		else//�Ŵ�
		{
			int cx, cy, cw, ch;
			cx = clientRect.left;
			cy = clientRect.top;
			cw = clientRect.Width();
			ch = clientRect.Height();
			int wx, wy, ww, wh;
			wx = windowRect.right+15;
			wy = windowRect.top-15;
			ww = windowRect.Width();
			wh = windowRect.Height();
			if (wx < 0)
			{
				ww += wx;

				cx = wx*(-1);
				cw += wx;

				wx *= -1;
			}
			if (wy < 0)
			{
				wh += wy;

				cy = wy*(-1);
				ch += wy;

				wy *= -1;
			}
			StretchBlt(
				pDC->m_hDC, cx, cy, cw, ch,
				m_pMemDC->m_hDC, wx-ww/timesOFBigeyes/2+1, wy-wh/timesOFBigeyes/2, ww/timesOFBigeyes, wh/timesOFBigeyes,
				SRCCOPY
				);
		}

		//draw rect border
		pDC->MoveTo(clientRect.left, clientRect.top);
		pDC->LineTo(clientRect.right - 1, clientRect.top);
		pDC->LineTo(clientRect.right - 1, clientRect.bottom - 1);
		pDC->LineTo(clientRect.left, clientRect.bottom - 1);
		pDC->LineTo(clientRect.left, clientRect.top);
		pDC->Rectangle(	(clientRect.left+clientRect.right)/2-rectsize,
						(clientRect.top+clientRect.bottom)/2-rectsize,
						(clientRect.left+clientRect.right)/2+rectsize,
						(clientRect.top+clientRect.bottom)/2+rectsize	);
		//draw crossing
		/*
		pDC->LineTo((clientRect.left+clientRect.right)/2, (clientRect.top+clientRect.bottom)/2);
		pDC->LineTo((clientRect.left+clientRect.right)/2, (clientRect.top+clientRect.bottom)/2);
		*/
	}

}

void CXTPWnd::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CWnd::OnWindowPosChanged(lpwndpos);
	
	// TODO: Add your message handler code here

	XOwnerDraw();
}

void CXTPWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	XOwnerDraw();
	// Do not call CWnd::OnPaint() for painting messages
}

void CXTPWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
	if (WA_ACTIVE == nState)
		XSaveScreen();
}
