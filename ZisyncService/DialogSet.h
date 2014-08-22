#pragma once
#include "MyDialog.h"
#include "MyButtonEx.h"
#include "MyTabCtrl.h"
#include "SetPage0.h"
#include "SetPage1.h"
#include "SetPage2.h"
#include "MyImage.h"
#include "afxcmn.h"

// CDialogSet dialog

class CDialogSet : public CMyDialog
{

	DECLARE_DYNAMIC(CDialogSet)
public:
	CMyImage		m_ImageBack;
	CMyButtonEx		m_btClose;
	CMyTabCtrl		m_tabSet;

	bool			m_bIsInit;

public:
	CSetPage0	m_Page0;
	CSetPage1	m_Page1;
	CSetPage2	m_Page2;

public:
	CDialogSet(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogSet();

// Dialog Data
	enum { IDD = IDD_DIALOGSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	void	SetControlPos(int cx, int cy);
	void	OnInitTabCtrl();
public:
	virtual BOOL OnInitDialog();
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeTabSet(NMHDR *pNMHDR, LRESULT *pResult);
};
