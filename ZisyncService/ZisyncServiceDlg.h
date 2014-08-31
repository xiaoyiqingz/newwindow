// ZisyncServiceDlg.h : header file
//

#pragma once
#include "ZiDialog.h"
#include "MyButton.h"
#include "MyListBox.h"
#include "ZiButton.h"
#include "ZiListCtrl.h"
#include "ZiTabCtrl.h"
#include "Page0.h"
#include "Page1.h"
#include "Page2.h"
#include "afxwin.h"
#include "afxcmn.h"

// CZisyncServiceDlg dialog

class CZisyncServiceDlg : public CZiDialog
{
// Construction
protected:
	CMyListBox		m_ListZisyncService;

	CZiButton		m_btSet;
	CZiButton		m_btRight;

	CZiListCtrl		m_list1;
	CZiTabCtrl		m_Tab;

	CZiButton		m_btClose;
	CZiButton		m_btMin;
	bool			m_bIsInit;
public:
	CPage0			m_page0;
	CPage1			m_page1;
	CPage2			m_page2;

public:
	CZisyncServiceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ZISYNCSERVICE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;
	TCHAR szPath[MAX_PATH];

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	/*virtual bool OnMaxSize();*/	/*子类重写父类的OnMaxSize,子类实现后最大化按子类实现进行，否则按父类最大化进行*/

	void InitButton();
	void InitTabCtrl();
	void SetControlPos(int cx, int cy);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSet();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
