#pragma once
#include "ZiDialog.h"
#include "ZiListCtrl.h"
#include "ZiButton.h"
#include "afxcmn.h"
#include "afxwin.h"

// CPage1 dialog

class CPage1 : public CZiDialog
{
	DECLARE_DYNAMIC(CPage1)
public:
	CZiListCtrl		m_ListPhone;
	CZiButton		m_btAdd;						

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
