#pragma once
#include "MyImage.h"
#include "MyButton.h"
#include "MyImageEx.h"
#include "ISkinControl.h"

// CMyDialog dialog

class CMyDialog : public CDialog, public ISkinControl
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

	HDC				m_hMemDC;
	HBITMAP			m_hMemBmp, m_hOldBmp;

public:
	CMyDialog(INT nIDTemplate, CWnd* pParent = NULL);   // standard constructor
	virtual ~CMyDialog();

// Dialog Data
//	enum { IDD = IDD_MYDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	virtual bool OnMaxSize() {return  false;}
	virtual void OnClientDraw(CDC*pDC, INT nWidth, INT nHeight){};
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight){}

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);void	LoadBackSkin(LPCTSTR pszResourcePath);
	void	LoadBackSkin(HINSTANCE hInstance, UINT nIDResource, LPCTSTR pszType = NULL);
	HDC		GetBackDC(){ return m_hMemDC; }

	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
};
