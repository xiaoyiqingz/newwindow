#pragma once
#include "MyDialog.h"
#include "ZiStatic.h"
#include "MyButtonEx.h"
#include "afxwin.h"

// CCreateSyncDIr dialog

class CCreateSyncDIr : public CMyDialog
{
	DECLARE_DYNAMIC(CCreateSyncDIr)
public:
	CMyButtonEx		m_btClose;
	CMyButtonEx		m_btCreate;

	CZiStatic		m_gbArea;
public:
	CCreateSyncDIr(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCreateSyncDIr();

// Dialog Data
	enum { IDD = IDD_CREATESYNCDIR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	void	SetControlPos(int cx, int cy);
	void	OnInitButton();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
