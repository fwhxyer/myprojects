#pragma once


// Subview �Ի���

class Subview : public CDialog
{
	DECLARE_DYNAMIC(Subview)
	BOOL OnInitDialog();

public:
	Subview(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Subview();
	void PostNcDestroy()  
	{ 
	    CDialog::PostNcDestroy();
		CDialog::EndDialog(0);
	    delete this; 
	} 

// �Ի�������
	enum { IDD = IDD_SUBVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
