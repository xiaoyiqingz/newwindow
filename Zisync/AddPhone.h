#pragma once
#include "ZiDialog.h"
#include "ZiImage.h"
#include "ZiButton.h"
#include "afxwin.h"

// CAddPhone dialog

class CAddPhone : public CZiDialog
{
	DECLARE_DYNAMIC(CAddPhone)
public:
	CZiImage		m_ImageCode;
	CZiButton		m_btHelp;

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
