#pragma once
#include "ZiDialog.h"
#include "ZiButton.h"
#include "ZiImage.h"
// CAddPhoneHelp dialog

class CAddPhoneHelp : public CZiDialog
{
	DECLARE_DYNAMIC(CAddPhoneHelp)
public:
	CZiButton		m_btBack;

	CZiImage		m_ImageBack;
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
