#pragma once
#include "MyDialog.h"
#include "MyButtonEx.h"
#include "afxwin.h"

// CAddMail dialog

class CAddMail : public CMyDialog
{
	DECLARE_DYNAMIC(CAddMail)
public:
	CMyButtonEx		m_btFile;
	CMyButtonEx		m_btMail;

public:
	CAddMail(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddMail();

// Dialog Data
	enum { IDD = IDD_ADDMAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void OnInitButton();
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
