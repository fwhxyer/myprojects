#pragma once


// Subview 对话框

class Subview : public CDialog
{
	DECLARE_DYNAMIC(Subview)
	BOOL OnInitDialog();

public:
	Subview(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Subview();
	void PostNcDestroy()  
	{ 
	    CDialog::PostNcDestroy();
		CDialog::EndDialog(0);
	    delete this; 
	} 

// 对话框数据
	enum { IDD = IDD_SUBVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
