#pragma once
#include "MyDialog.h"
#include "MyButtonEx.h"
#include "afxwin.h"

// CAddPhone dialog

class CAddPhone : public CMyDialog
{
	DECLARE_DYNAMIC(CAddPhone)
public:
	CMyButtonEx	m_slipbt;
	CMenu		m_Menu;
public:
	CAddPhone(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddPhone();

// Dialog Data
	enum { IDD = IDD_ADDPHONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedSplit1();
};
