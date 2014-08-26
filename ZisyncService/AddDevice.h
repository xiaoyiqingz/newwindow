#pragma once
#include "MyDialog.h"
#include "MyImage.h"
#include "MyTabCtrl.h"
#include "MyButtonEx.h"
#include "AddWin.h"
#include "AddPhone.h"
#include "AddMail.h"
#include "AddPhoneHelp.h"
#include "afxcmn.h"
#include "afxwin.h"

// CAddDevice dialog

class CAddDevice : public CMyDialog
{
	DECLARE_DYNAMIC(CAddDevice)
public:
	CMyImage		m_ImageBack;
	CMyButtonEx		m_btClose;
	CMyTabCtrl		m_TabAdd;
	CMyButtonEx		m_btReFind;
	CMyButtonEx		m_btSelected;

	bool			m_bIsInit;

	CAddWin			m_Page0;
	CAddPhone		m_Page1;
	CAddMail		m_Page2;
	CAddPhoneHelp	m_Page3;
public:
	CAddDevice(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddDevice();

// Dialog Data
	enum { IDD = IDD_ADDDEVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void	SetControlPos(int cx, int cy);
	void	OnInitTabCtrl();
	void	OnInitButton();

public:
	virtual BOOL OnInitDialog();
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtSelected();
	afx_msg void OnSelchangeTabAdd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
