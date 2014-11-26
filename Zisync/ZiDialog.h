#pragma once
#include "ZiImage.h"
#include "MyButton.h"
#include "MyImageEx.h"
#include "ZiImage.h"
#include "ZiDialogBase.h"

// CZiDialog dialog

class CZiDialog : public CDialog, public ZiDialogBase
{
	DECLARE_DYNAMIC(CZiDialog)
public:
	CZiImage		m_BackImg;

//	bool			m_bIsInit;
	bool			m_bIsZoomed;		//是否最大化
	bool			m_bExtrude;			//是否可以拉伸

	HDC				m_hMemDC;
	HBITMAP			m_hMemBmp, m_hOldBmp;

public:
	CZiDialog(INT nIDTemplate, CWnd* pParent = NULL);   // standard constructor
	virtual ~CZiDialog();

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
//	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void	LoadBackSkin(HINSTANCE hInstance, UINT nIDResource, LPCTSTR pszType = NULL);
	HDC		GetBackDC(){ return m_hMemDC; }

	afx_msg void OnPaint();
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
};
