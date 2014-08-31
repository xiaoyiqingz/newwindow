#pragma once
#include "ZiDialog.h"
#include "MyListCtrl.h"
#include "afxcmn.h"

// CPage2 dialog

class CPage2 : public CZiDialog
{
	DECLARE_DYNAMIC(CPage2)
public:
	CMyListCtrl		m_list1;

public:
	CPage2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPage2();

// Dialog Data
	enum { IDD = IDD_PAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void	OnInitListCtrl();

public:
	virtual BOOL OnInitDialog();
};
