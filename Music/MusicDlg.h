
// MusicDlg.h : header file
//

#pragma once
#include "MyDialog.h"
#include "MyButton.h"
#include "MyListBox.h"
#include "MyButtonEx.h"
#include "afxwin.h"
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

	CMyButtonEx		m_btNewClose;
	CMyButtonEx		m_Check;
	CMyButtonEx		m_Radio1;
	CMyButtonEx		m_Radio2;
	CMyButtonEx		m_Radio3;
	CMyButtonEx		m_btIcon;
	CMyButtonEx		m_btMenu;

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

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	/*virtual bool OnMaxSize();*/	/*子类重写父类的OnMaxSize,子类实现后最大化按子类实现进行，否则按父类最大化进行*/

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	
};
