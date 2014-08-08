#pragma once
#include "MyDialog.h"
#include "MyButtonEx.h"
#include "afxwin.h"

// CSetPage0 dialog

class CSetPage0 : public CMyDialog
{
	DECLARE_DYNAMIC(CSetPage0)
public:
	CMyButtonEx		m_btAccount;
	CMyButtonEx		m_btName;

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
};
