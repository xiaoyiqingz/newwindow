#pragma once
#include "ZiDialog.h"
#include "ZiButton.h"
#include "ZiTabCtrl.h"
#include "SetPage0.h"
#include "SetPage1.h"
#include "SetPage2.h"
#include "ZiImage.h"
#include "afxcmn.h"

// CDialogSet dialog

class CDialogSet : public CZiDialog
{

	DECLARE_DYNAMIC(CDialogSet)
public:
	CZiImage		m_ImageBack;
	CZiButton		m_btClose;
	CZiTabCtrl		m_tabSet;

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
