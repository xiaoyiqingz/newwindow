#pragma once
#include "MyDialog.h"
#include "afxwin.h"

// CSetUpPage2 dialog

class CSetUpPage2 : public CMyDialog
{
	DECLARE_DYNAMIC(CSetUpPage2)
public:
	int		m_Radio;

	CEdit m_etDisPort;
	CEdit m_etPubPort;

public:
	CSetUpPage2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetUpPage2();

// Dialog Data
	enum { IDD = IDD_SETUPPAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickedRadio1();
	afx_msg void OnRadio4();
};
