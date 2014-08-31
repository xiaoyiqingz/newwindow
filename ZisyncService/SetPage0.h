#pragma once
#include "ZiDialog.h"
#include "ZiButton.h"
#include "afxwin.h"

// CSetPage0 dialog

class CSetPage0 : public CZiDialog
{
	DECLARE_DYNAMIC(CSetPage0)
public:
	CZiButton		m_btAccount;
	CZiButton		m_btName;
public:
	CSetPage0(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetPage0();

// Dialog Data
	enum { IDD = IDD_SETPAGE0 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	void	OnInitButton();

public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
