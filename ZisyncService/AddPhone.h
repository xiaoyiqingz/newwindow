#pragma once
#include "MyDialog.h"
#include "MyImage.h"
#include "MyButtonEx.h"
#include "afxwin.h"

// CAddPhone dialog

class CAddPhone : public CMyDialog
{
	DECLARE_DYNAMIC(CAddPhone)
public:
	CMyImage		m_ImageCode;
	CMyButtonEx		m_btHelp;

public:
	CAddPhone(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddPhone();

// Dialog Data
	enum { IDD = IDD_ADDPHONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void OnInitButton();

public:
	virtual BOOL OnInitDialog();
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	afx_msg void OnBnClickedBtHelp();
};
