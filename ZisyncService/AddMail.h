#pragma once
#include "ZiDialog.h"
#include "ZiButton.h"
#include "afxwin.h"

// CAddMail dialog

class CAddMail : public CZiDialog
{
	DECLARE_DYNAMIC(CAddMail)
public:
	CZiButton		m_btFile;
	CZiButton		m_btMail;

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
