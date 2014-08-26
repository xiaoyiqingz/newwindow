#pragma once
#include "MyDialog.h"
#include "MyButtonEx.h"
// SetUpPage1 dialog

class CSetUpPage1 : public CMyDialog
{
	DECLARE_DYNAMIC(CSetUpPage1)
public:
	CMyButtonEx		m_btModify;

public:
	CSetUpPage1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetUpPage1();

// Dialog Data
	enum { IDD = IDD_SETUPPAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void	OnInitButton();

public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
