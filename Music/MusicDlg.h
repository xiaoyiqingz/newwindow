
// MusicDlg.h : header file
//

#pragma once
#include "MyDialog.h"
#include "MyButton.h"
#include "MyListBox.h"
#include "MyButtonEx.h"
#include "MyListCtrl.h"
#include "MyEdit.h"
#include "MyTabCtrl.h"
#include "Page0.h"
#include "Page1.h"
#include "Page2.h"
#include "afxwin.h"
#include "afxcmn.h"
// CMusicDlg dialog
class CMusicDlg : public CMyDialog
{
// Construction
protected:
	CMyButton		m_btPrev;
	CMyButton		m_btPlay;
	CMyButton		m_btPause;
	CMyButton		m_btNext;
	CMyListBox		m_ListMusic;

	CMyButtonEx		m_btSet;
	CMyButtonEx		m_Check;
	CMyButtonEx		m_Radio1;
	CMyButtonEx		m_Radio2;
	CMyButtonEx		m_Radio3;
	CMyButtonEx		m_btIcon;
	CMyButtonEx		m_btMenu;
	CMyButtonEx		m_btRight;

	CMyListCtrl		m_list1;
	CMyEdit			m_etMuti;
	CMyTabCtrl		m_Tab;

	CMyButtonEx		m_btClose;
	CMyButtonEx		m_btMin;
	bool			m_bIsInit;
public:
	CPage0			m_page0;
	CPage1			m_page1;
	CPage2			m_page2;

public:
	CMusicDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MUSIC_DIALOG };

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
	void InitEdit();
	void InitTabCtrl();
	void SetControlPos(int cx, int cy);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	afx_msg void OnClickedButton4();
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSet();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
