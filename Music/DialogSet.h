#pragma once
#include "MyDialog.h"

// CDialogSet dialog

class CDialogSet : public CMyDialog
{
	DECLARE_DYNAMIC(CDialogSet)

public:
	CDialogSet(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogSet();

// Dialog Data
	enum { IDD = IDD_DIALOGSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
