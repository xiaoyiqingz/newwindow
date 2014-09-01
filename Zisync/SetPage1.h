#pragma once
#include "ZiDialog.h"
#include "afxwin.h"

// CSetPage1 dialog

class CSetPage1 : public CZiDialog
{
	DECLARE_DYNAMIC(CSetPage1)
public:
	CEdit		m_etDiscoverPort;
	CEdit		m_etUpSpeed;
	CEdit		m_etDownSpeed;
public:
	CSetPage1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetPage1();

// Dialog Data
	enum { IDD = IDD_SETPAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg	BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickedRadio1();
	afx_msg void OnRadio4();
	afx_msg void OnClickedRadio5();
	afx_msg void OnRadio6();
};
