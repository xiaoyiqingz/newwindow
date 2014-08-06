#pragma once
#include "MyListCtrl.h"
#include "MyButtonEx.h"
#include "MyDialog.h"
#include "afxcmn.h"
#include "afxwin.h"

// CPage0 dialog

class CPage0 : public CMyDialog
{
	DECLARE_DYNAMIC(CPage0)
public:
	CMyListCtrl		m_list1;
	CMyButtonEx		m_buttonadd;
public:
	CPage0(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPage0();

// Dialog Data
	enum { IDD = IDD_PAGE0 };
public:
	void OnInitListCtrl();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
};
