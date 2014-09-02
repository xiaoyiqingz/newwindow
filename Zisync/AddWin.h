#pragma once
#include "ZiDialog.h"
#include "ZiListIcon.h"
#include "afxcmn.h"

// CAddWin dialog

class CAddWin : public CZiDialog
{
	DECLARE_DYNAMIC(CAddWin)
public:
	CZiListIcon		m_ListDevice;
public:
	CAddWin(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddWin();

// Dialog Data
	enum { IDD = IDD_ADDWIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
