#pragma once


// CMyDialog dialog

class CMyDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyDialog)

public:
	CMyDialog(INT nIDTemplate, CWnd* pParent = NULL);   // standard constructor
	virtual ~CMyDialog();

// Dialog Data
//	enum { IDD = IDD_MYDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
