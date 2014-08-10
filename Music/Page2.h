#pragma once
#include "MyDialog.h"
#include "MyListCtrl.h"
#include "MyListIcon.h"
#include "afxcmn.h"

// CPage2 dialog

class CPage2 : public CMyDialog
{
	DECLARE_DYNAMIC(CPage2)
public:
	CMyListIcon		m_list1;

public:
	CPage2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPage2();

// Dialog Data
	enum { IDD = IDD_PAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
