#pragma once
#include "MyDialog.h"

// CSetPage1 dialog

class CSetPage1 : public CMyDialog
{
	DECLARE_DYNAMIC(CSetPage1)

public:
	CSetPage1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetPage1();

// Dialog Data
	enum { IDD = IDD_SETPAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
