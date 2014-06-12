
// MusicDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "MusicDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMusicDlg dialog




CMusicDlg::CMusicDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMusicDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMusicDlg, CMyDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMusicDlg message handlers

BOOL CMusicDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
//	LoadBackSkin(_T("G:\\vstest\\NewWindow\\Music\\res\\back.jpg"));
//	LoadBackSkin(AfxGetInstanceHandle(), IDB_BACKALL, _T("IMAGE"));
//	LoadBackSkin(AfxGetInstanceHandle(), IDB_CLOSE, _T("PNG"));
	LoadBackSkin(AfxGetInstanceHandle(), IDB_GROUND);

	SetWindowPos(NULL, 0, 0, 816, 510, SWP_NOMOVE);
	return TRUE;  
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMusicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CMyDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMusicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

