#pragma once
#include "ZiDialog.h"
#include "ZiImage.h"
// CSetUpPage0 dialog

class CSetUpPage0 : public CZiDialog
{
	DECLARE_DYNAMIC(CSetUpPage0)
public:
	CZiImage	m_ImageLoge;

public:
	CSetUpPage0(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetUpPage0();

// Dialog Data
	enum { IDD = IDD_SETUPPAGE0 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

public:
	virtual	BOOL OnInitDialog();
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
