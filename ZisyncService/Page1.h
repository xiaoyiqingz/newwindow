#pragma once
#include "MyDialog.h"
#include "MyListCtrl.h"
#include "MyButtonEx.h"
#include "afxcmn.h"
#include "afxwin.h"

// CPage1 dialog

class CPage1 : public CMyDialog
{
	DECLARE_DYNAMIC(CPage1)
public:
	CMyListCtrl		m_ListPhone;
	CMyButtonEx		m_btAdd;						

public:
	CPage1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPage1();

// Dialog Data
	enum { IDD = IDD_PAGE1 };
public:
	void	OnInitListCtrl();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
