
// MusicDlg.h : header file
//

#pragma once
#include "MyDialog.h"
#include "MyButton.h"
#include "MyListBox.h"
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
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
