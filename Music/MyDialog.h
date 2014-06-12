#pragma once
#include "MyImage.h"
#include "MyButton.h"
#include "MyImageEx.h"

// CMyDialog dialog

class CMyDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyDialog)
public:
	CMyImageEx		m_ImageBack;
	CMyButton		m_btClose;
	CMyButton		m_btMax;
	CMyButton		m_btMin;

	bool			m_bIsInit;
	bool			m_bIsZoomed;		//是否最大化
	bool			m_bExtrude;			//是否可以拉伸

public:
	CMyDialog(INT nIDTemplate, CWnd* pParent = NULL);   // standard constructor
	virtual ~CMyDialog();

// Dialog Data
//	enum { IDD = IDD_MYDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	virtual bool OnMaxSize() {return  false;}

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void	LoadBackSkin(LPCTSTR pszResourcePath);
	void	LoadBackSkin(HINSTANCE hInstance, UINT nIDResource, LPCTSTR pszType = NULL);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
};
