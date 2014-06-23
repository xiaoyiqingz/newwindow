
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

#define IDC_PREV    WM_USER+0x010
#define IDC_PLAY	WM_USER+0x011
#define IDC_PAUSE	WM_USER+0x012
#define IDC_NEXT	WM_USER+0x013
// CMusicDlg dialog




CMusicDlg::CMusicDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMusicDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NEW_CLOSE, m_btNewClose);
	DDX_Control(pDX, IDC_CHECK1, m_Check);
	DDX_Control(pDX, IDC_MY_RADIO, m_Radio1);
	DDX_Control(pDX, IDC_RADIO2, m_Radio2);
	DDX_Control(pDX, IDC_RADIO3, m_Radio3);
	DDX_Control(pDX, IDC_BUTTON2, m_btIcon);
	DDX_Control(pDX, IDC_BUTTON3, m_btMenu);
}

BEGIN_MESSAGE_MAP(CMusicDlg, CMyDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
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

	HINSTANCE hInstance = AfxGetInstanceHandle();
	m_btPrev.Create(NULL, WS_CHILD|WS_VISIBLE, CRect(90,45,0,0), this,IDC_PREV);
	m_btPrev.SetButtonImage(hInstance, MAKEINTRESOURCE(IDB_PREV), _T("PNG"));
	m_btPlay.Create(NULL, WS_CHILD|WS_VISIBLE, CRect(130,45,0,0), this,IDC_PLAY);
	m_btPlay.SetButtonImage(hInstance, MAKEINTRESOURCE(IDB_PLAY), _T("PNG"));
	m_btPause.Create(NULL, WS_CHILD, CRect(130,45,0,0), this,IDC_PAUSE);
	m_btPause.SetButtonImage(hInstance, MAKEINTRESOURCE(IDB_PAUSE), _T("PNG"));
	m_btNext.Create(NULL, WS_CHILD|WS_VISIBLE, CRect(170,45,0,0), this,IDC_NEXT);
	m_btNext.SetButtonImage(hInstance, MAKEINTRESOURCE(IDB_NEXT), _T("PNG"));

	HDC hParentDC = GetBackDC();
	m_btNewClose.SetBackImage(hInstance, IDB_NEW_CLOSE);
	m_btNewClose.SetButtonType(BT_PUSHBUTTON);
	m_btNewClose.SetSize(36, 31);

	HFONT font;
	font = CreateFont(0, 0, 0, 0, FW_DONTCARE, TRUE, FALSE, FALSE, DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,_T("�����п�"));
	m_Check.SetCheckImage(_T("res\\checkbox_normal.png"),
		_T("res\\checkbox_hightlight.png"),
		_T("res\\checkbox_tick_normal.png"),
		_T("res\\checkbox_tick_highlight.png"));
	m_Check.SetButtonType(BT_CHECKBUTTON);
	m_Check.SetParentBack(hParentDC);
	m_Check.SetSize(68, 15);
	m_Check.SetCtrlFont(font);
//	DeleteObject(font);   //*

	m_Radio1.SetCheckImage(_T("res\\radiobtn_normal.png"), 
		_T("res\\radiobtn_highlight.png"), 
		_T("res\\radiobtn_tick_normal.png"), 
		_T("res\\radiobtn_tick_highlight.png"));
	m_Radio1.SetButtonType(BT_RADIOBUTTON);
	m_Radio1.SetParentBack(hParentDC);
	m_Radio1.SetSize(68,15);
	m_Radio1.SetCheck(BST_CHECKED);

	m_Radio2.SetCheckImage(_T("res\\radiobtn_normal.png"), 
		_T("res\\radiobtn_highlight.png"), 
		_T("res\\radiobtn_tick_normal.png"), 
		_T("res\\radiobtn_tick_highlight.png"));
	m_Radio2.SetButtonType(BT_RADIOBUTTON);
	m_Radio2.SetParentBack(hParentDC);
	m_Radio2.SetSize(68,15);

	m_Radio3.SetCheckImage(_T("res\\radiobtn_normal.png"), 
		_T("res\\radiobtn_highlight.png"), 
		_T("res\\radiobtn_tick_normal.png"), 
		_T("res\\radiobtn_tick_highlight.png"));
	m_Radio3.SetButtonType(BT_RADIOBUTTON);
	m_Radio3.SetParentBack(hParentDC);
	m_Radio3.SetSize(68,15);

	m_btIcon.SetBackImage(NULL,_T("res\\allbtn_highlight.png"),
		_T("res\\allbtn_down.png"),NULL);
	m_btIcon.SetIconImage(_T("res\\message.png"));
	m_btIcon.SetButtonType(BT_ICONBUTTON);
	m_btIcon.SetParentBack(hParentDC);
	m_btIcon.SetSize(22, 22);

	static CMenu menu;
	menu.LoadMenu(IDR_MENU1);

	CMenu *PopupMenu = menu.GetSubMenu(0);

	m_btMenu.SetBackImage(NULL,_T("res\\menubtn_highlight.png"), _T("res\\menubtn_highlight.png"),NULL);
	m_btMenu.SetIconImage(_T("res\\imonline.png"));
	m_btMenu.SetMenuImage(_T("res\\MainPanel_FolderNode_expandTexture.png"));
	m_btMenu.SetButtonType(BT_MENUBUTTON);
	m_btMenu.SetParentBack(hParentDC);
	m_btMenu.SetMenu(PopupMenu->m_hMenu);
	m_btMenu.SetSize(35,22);

	CRect rcClient;
	GetClientRect(&rcClient);

	m_ListMusic.Create(WS_CHILD|WS_VISIBLE|LBS_OWNERDRAWVARIABLE|LBS_HASSTRINGS,
		CRect(1,120,309,rcClient.bottom),this,NULL);
	m_ListMusic.SetItemHeight(48);

	m_ListMusic.AddString(TEXT("���� - ����"));
	m_ListMusic.AddString(TEXT("�����ս�� - �й�������"));
	m_ListMusic.AddString(TEXT("�����ڣ����й�����������"));
	m_ListMusic.AddString(TEXT("�Ұ����й� - ����"));
	m_ListMusic.AddString(TEXT("��һ�ΰ����� - ������"));
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



BOOL CMusicDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	switch (LOWORD(wParam)) {
	case IDC_PLAY:
		{
			m_btPause.ShowWindow(SW_SHOW);
			m_btPlay.ShowWindow(SW_HIDE);
		}
		break;
	case IDC_PAUSE:
		{
			m_btPlay.ShowWindow(SW_SHOW);
			m_btPause.ShowWindow(SW_HIDE);
		}
		break;
	}
	return CMyDialog::OnCommand(wParam, lParam);
}


BOOL CMusicDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
//	return CMyDialog::OnEraseBkgnd(pDC);
}

/*
bool CMusicDlg::OnMaxSize()
{
	CRect rcClient;
	GetClientRect(&rcClient);

	static bool bMini = false;

	bMini = !bMini;

	SetWindowPos(NULL, 0, 0, rcClient.Width(), (bMini? 76:510), SWP_NOMOVE);
	
	return true;
}*/


void CMusicDlg::DrawClientArea(CDC*pDC,int nWidth,int nHeight)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	m_ImageBack.Draw(pDC->GetSafeHdc(),0, 0, nWidth, nHeight);
}
