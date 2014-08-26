#pragma once
#include "MyDialog.h"
#include "MyButtonEx.h"
#include "MyImage.h"
// CAddPhoneHelp dialog

class CAddPhoneHelp : public CMyDialog
{
	DECLARE_DYNAMIC(CAddPhoneHelp)
public:
	CMyButtonEx		m_btBack;

	CMyImage		m_ImageBack;
public:
	CAddPhoneHelp(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddPhoneHelp();

// Dialog Data
	enum { IDD = IDD_ADDPHONEHELP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual	BOOL OnInitDialog();
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	afx_msg void OnBnClickBtBack();
};
