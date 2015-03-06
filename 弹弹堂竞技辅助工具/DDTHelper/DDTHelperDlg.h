
// DDTHelperDlg.h : 头文件
//
#include "Subview.h"
#include "XTPWnd.h"
#include "SubviewList.h"

#pragma once

// CDDTHelperDlg 对话框
class CDDTHelperDlg : public CDialogEx
{
// 构造
public:
	CDDTHelperDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DDTHELPER_DIALOG };

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
	CEdit m_e1;
	CEdit m_e2;
	CEdit m_e3;
	CString m_cs1;
	CString m_cs2;
	CString m_cs3;
	afx_msg LRESULT OnNcHitTest(CPoint point);
	CStatic m_csState;
	CStatic m_csCalc;
//	CStatic m_staticDot;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CButton m_b1;
	CButton m_bBehind;
	CButton m_b2;
	CButton m_b4;
	CButton m_b5;
	int boolColorCheck;
	int boolColorDouble;
	int boolViewMode;
	void setCAboutDlg();
	void setRESListColor(){
		setRES(aR,bR,cR,dR,eR,fR,gR,hR,iR,jR,kR);
	}
	void setFocusExforEDIT1(){
		GetDlgItem(IDC_EDIT1)->SetFocus();
	}
	CXTPWnd* pWnd;
	CXTPWnd* CreatCXTPWnd()
	{	
		CXTPWnd *pWnd = new CXTPWnd;
		pWnd->XCreate();
		//pWnd->ShowWindow(SW_SHOW);
		return pWnd;
	}
private:
	CPoint windPos,anglePos;
	int checkType;
	int boolOfCalc;
	int boolOfBigeyes;
	int boolOfOnBigeyes;
	int boolBehind;
	int boolWind;
	//int boolColorCheck;//升级为全局
	int m_Dragging;
	int first;
	double calcHuman;
	double calcScreen;
	double calc1;
	double calc2;
	CPoint m_PointOrigin,m_PointOld;
	CFont m_editFont;
	CFont m_staticFont;
	CFont m_defaultFont;
	Subview* pDlg;
	Subview* CreatSubview()
	{		
	//直接在在OnInitDialog中加入下列代码就可以了 
		Subview* pDlg = new Subview();
		pDlg->Create(Subview::IDD, pDlg);
		pDlg->ShowWindow(SW_SHOW);
		return pDlg;
	}
	SubviewList* pDlgSL;
	SubviewList* CreatSubviewList()
	{		
	//直接在在OnInitDialog中加入下列代码就可以了 
		SubviewList* pDlg = new SubviewList();
		pDlg->Create(SubviewList::IDD, pDlg);
		pDlg->ShowWindow(SW_SHOW);
		return pDlg;
	}
	struct Res{
		double angle;
		double angleHigh;
		double strength;
		double strengthHigh;
		double accuracy;
		CString angleCS;
		CString angleHighCS;
		CString strengthCS;
		CString strengthHighCS;
		CString accuracyCS;
		void Set() {angle=0;strength=0;accuracy=0;
					angleCS="0";strengthCS="0";accuracyCS="===";
					angleHighCS="";strengthHighCS="";}
		void Set(double a,double b,double c,bool reflect=TRUE) {
			angle=a;strength=b;accuracy=c;
			if (reflect)
				angleCS.Format("%1.0f  (%1.0f)",a,180-a);
			else
				angleCS.Format("%1.0f",a);
			strengthCS.Format("%1.0f",b);
			char tmp;
			if (c==77) tmp='@'; //77为Flag，表示精确度不明
			else if (c>0.167) tmp='+';
			else if (c<-0.167) tmp='-';
			else tmp='=';
			accuracyCS.Format("%c%c%c",tmp,tmp,tmp);
			angleHighCS="";strengthHighCS="";
		}
		void Set(double a,double b) {
			if (b>100||b<0) b=-1;
			angleHigh=a;strengthHigh=b;
			angleHighCS.Format("%1.0f  (%1.0f)",a,180-a);strengthHighCS.Format("%1.0f  (%1.0f)",b,this->strength);
		}
	};
	Res aR,bR,cR,dR,eR,fR,gR,hR,iR,jR;
	public:Res kR;
	private:
	void calcRES1(double);
	void calcRES2(double);
	void calcRES3(double);
	void calcRES4(double);
	void calcRES5(double);
	void calcRES6(double);
	void calcRES7(double);
	void calcRES8(double);
	void calcRES9(double);
	void calcRES10(double);
	void calcRES11(double);
	void setRES(Res,Res,Res,Res,Res,Res,Res,Res,Res,Res,Res);
	public:
	void calcRES(double wind) {calcRES1(wind);calcRES2(wind);calcRES3(wind);calcRES4(wind);
							   calcRES5(wind);calcRES6(wind);calcRES7(wind);calcRES8(wind);
							   calcRES9(wind);calcRES10(wind);calcRES11(wind);
							   setRES(aR,bR,cR,dR,eR,fR,gR,hR,iR,jR,kR);
							  }
	private:
	void myinit();
	void Visual();
	void UnVisual();
	void Behind();
	bool checkCol(CPoint point)	{
		CDC* tmpCDC=pWnd->getCDC();
		COLORREF col,coltmp;
		col=tmpCDC->GetPixel(point);
		coltmp=col;
		int	flagall=80;
		int	flag=16;
		int x=0,tf=0,tfe=0;
		point.y-=flagall/2;
		while (x<flagall){
			coltmp=tmpCDC->GetPixel(point.x,++point.y);
			++x;
			if (coltmp==col) ++tf;
			else
			{ col=coltmp;tf=0;}
			if (tf>tfe) tfe=tf;
		}
		if (tfe>=flag) return true; else return false;
		delete tmpCDC;
	}
public:
	afx_msg void OnEnSetfocusEdit1();
	afx_msg void OnEnSetfocusEdit2();
	afx_msg void OnEnSetfocusEdit3();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	virtual void OnOK();
	double getStrFromAngle(double,double);
	void setColorCheck() {if (boolColorCheck) boolColorCheck=0;else boolColorCheck=1;}
	void setColorDouble() {if (boolColorDouble) boolColorDouble=0;else boolColorDouble=1;}
	double wind;
	void getMap();
	void getMapA();
private:
	double autoGetWind(CDC* tmpCDC);

	short shape,shapeMax;
	short map[101][81];
	short mapA[101][81];
	CPoint Shape3Lpoint[400];
	CPoint Shape3Rpoint[400];
	int shapeSize[800];
	double setShape(short&);
	CString setShapetmp,setShapetmp1;
	void setShape2(short,int,int);
	void setShape2back(short,int,int);
	void setShape3(short,int,int,int check=0);
	void setShape3back(short,int,int);
	int angleOld;
	int screenDir;
	int screenPos;
	int ScreenCheck;
	int screenNLx,screenNLy,screenNRx,screenNRy;
	int screenBorder,screen1,screen2;
	int getShapeDir(short&);
	int getShapeLeft(short&);
	int getShapeRight(short&);
	void clearShape(int);
	int getScreenCheck(int);
	int getShapeNum(CPoint,CPoint,int);
	int getShapeNum1(CPoint,CPoint,int);
	int getShapeNum2(CPoint,CPoint,int);
	int lineone(int);
	int linetwo(int);
	int linethree(int);
public:
	CButton m_b6;
	afx_msg void OnBnClickedButton6();
	CButton m_b7;
	afx_msg void OnBnClickedButton7();
	int autoGetAngle(CDC* tmpCDC);
	int autoGetAngle2(CDC* tmpCDC);
	int autoGetAngle3(CDC* tmpCDC);
	int autoGetAngle4(CDC* tmpCDC);
	CString checkDJW;
	int countbit;
private:
	void setMapA(void);
	int checkShape2(void);
	int checkShape3(void);
	int checkShape4(void);
public:
	afx_msg void OnStnClickedStatic1();
};