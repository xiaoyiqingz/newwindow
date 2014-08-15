
// MusicDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "MusicDlg.h"
#include "DialogSet.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_PREV    WM_USER+0x010
#define IDC_PLAY	WM_USER+0x011
#define IDC_PAUSE	WM_USER+0x012
#define IDC_NEXT	WM_USER+0x013
#define IDC_MIN		WM_USER+0x014
// CMusicDlg dialog


CMusicDlg::CMusicDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMusicDlg::IDD, pParent)
{
	m_bIsInit = false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SET, m_btSet);
	DDX_Control(pDX, IDC_CHECK1, m_Check);
	DDX_Control(pDX, IDC_MY_RADIO, m_Radio1);
	DDX_Control(pDX, IDC_RADIO2, m_Radio2);
	DDX_Control(pDX, IDC_RADIO3, m_Radio3);
	DDX_Control(pDX, IDC_BUTTON2, m_btIcon);
	DDX_Control(pDX, IDC_BUTTON3, m_btMenu);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_BUTTON4, m_btRight);
	DDX_Control(pDX, IDC_EDIT_MULTI, m_etMuti);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CMusicDlg, CMyDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON4, &CMusicDlg::OnClickedButton4)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMusicDlg::OnClickList1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMusicDlg::OnSelchangeTab1)
	ON_BN_CLICKED(IDC_SET, &CMusicDlg::OnBnClickedSet)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMusicDlg message handlers

BOOL CMusicDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	/*_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );*/
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
//	LoadBackSkin(_T("G:\\vstest\\NewWindow\\Music\\res\\back.jpg"));
//	LoadBackSkin(AfxGetInstanceHandle(), IDB_BACKALL, _T("IMAGE"));
//	LoadBackSkin(AfxGetInstanceHandle(), IDB_CLOSE, _T("PNG"));
	LoadBackSkin(AfxGetInstanceHandle(), IDB_BACK_NEW, _T("PNG"));
	SetWindowPos(NULL, 0, 0, 597, 527, SWP_NOMOVE);	

	CRect rcControl(0,0,0,0);
	HDC hParentDC = GetBackDC();
	m_btClose.Create(NULL, WS_VISIBLE | WS_CHILD, rcControl, this, IDCANCEL);
	m_btClose.SetBackImage(_T("res\\close1.png"), _T("res\\close2.png"), 
		_T("res\\close3.png"), _T("res\\close4.png"));
	m_btClose.SetButtonType(BT_PUSHBUTTON);
	m_btClose.SetParentBack(hParentDC);
	m_btClose.SetSize(18,18);

	m_btMin.Create(NULL, WS_VISIBLE | WS_CHILD, rcControl, this, IDC_MIN);
	m_btMin.SetBackImage(_T("res\\minimize1.png"), _T("res\\minimize2.png"), 
		_T("res\\minimize3.png"), _T("res\\minimize4.png"));
	m_btMin.SetButtonType(BT_PUSHBUTTON);
	m_btMin.SetParentBack(hParentDC);
	m_btMin.SetSize(18,18);
	m_bIsInit = true;

	InitButton();
	InitTabCtrl();


	m_page0.Create(IDD_PAGE0, &m_Tab);
	m_page1.Create(IDD_PAGE1, &m_Tab);
	m_page2.Create(IDD_PAGE2, &m_Tab);

	CRect rcItem(0, 70, 597, 500);
	m_page0.MoveWindow(&rcItem);
	m_page1.MoveWindow(&rcItem);
	m_page2.MoveWindow(&rcItem);
	m_page0.ShowWindow(SW_SHOW);
	m_page1.ShowWindow(SW_HIDE);
	m_page2.ShowWindow(SW_HIDE);

	CRect rcClient;
	GetClientRect(&rcClient);
	SetControlPos(rcClient.Width(), rcClient.Height());
/*
	DWORD dwStyle = m_list1.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	m_list1.SetExtendedStyle(dwStyle);*/

/*
	m_list1.InsertColumn( 0, _T(""), LVCFMT_LEFT, 100 );
	m_list1.InsertColumn( 1, _T(""), LVCFMT_LEFT, 300 );
	m_list1.InsertColumn( 2, _T(""), LVCFMT_LEFT, 50 );
	m_list1.InsertColumn( 3, _T(""), LVCFMT_LEFT, 50 );
	m_list1.InsertColumn( 4, _T(""), LVCFMT_LEFT, 50 );
	m_list1.m_HeaderCtrl.SetItemHeight(0);

	m_list1.m_HeaderCtrl.SetBackImage(_T("res\\folder_nav_item_bg_hover.png"),&CRect(2,2,2,2));
	m_list1.m_HeaderCtrl.SetPressImage(_T("res\\folder_nav_item_bg_pressed.png"),&CRect(2,2,2,2));
	m_list1.m_HeaderCtrl.SetGridImage(_T("res\\category_sep.png"));
	m_list1.SetHovenImage(_T("res\\item_bg_hover.png"),&CRect(2,2,2,2));
	m_list1.SetSelectImage(_T("res\\item_bg_selected.png"),&CRect(2,2,2,2));
	m_list1.SetScrollImage(&m_list1,_T("res\\SKIN_SCROLL.bmp"));

	for (int i=0; i < 12; i++) {
		m_list1.InsertItem(i,NULL);	
		m_list1.SetItemContent(i, _T("我的自同步"), _T("@3设备 1本地"), _T("历史记录"));
		m_list1.InsertImage(i, 0, _T("res\\appicns_folder_Download.png"));
		m_list1.InsertImage(i, 2, _T("res\\tab1image1.png"), _T("res\\tab1image_gray.png"));
		m_list1.InsertImage(i, 3, _T("res\\button_invite.png"));
		m_list1.InsertImage(i, 4, _T("res\\tab_set.png"));
	}
	
	m_list1.SetItemHeight(70);
	m_list1.MoveWindow(0,70,597,430);
	m_list1.m_HeaderCtrl.EnableWindow(FALSE);
	m_list1.m_HeaderCtrl.SetLockCount(1);*/

/*
	HDC hParentDC = GetBackDC();
	m_etMuti.SetBackNormalImg(_T("res\\frameBorderEffect_normalDraw.png"), CRect(3,3,3,3));
	m_etMuti.SetBackHotImg(_T("res\\frameBorderEffect_mouseDownDraw.png"), CRect(3,3,3,3));
	m_etMuti.SetScrollImage(&m_etMuti,_T("res\\SKIN_SCROLL.bmp"));
	m_etMuti.SetParentBack(hParentDC);*/

	return TRUE;  
}


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
			m_btPause.ShowWindow(SW_HIDE);
			m_btPlay.ShowWindow(SW_HIDE);
		}
		break;
	case IDC_PAUSE:
		{
			m_btPlay.ShowWindow(SW_HIDE);
			m_btPause.ShowWindow(SW_HIDE);
		}
		break;
	case IDC_MIN:
		ShowWindow(SW_MINIMIZE);
		break;
	}
	return CMyDialog::OnCommand(wParam, lParam);
}


void CMusicDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);
	if( !m_bIsInit ) return;

	SetControlPos(cx, cy);
}


void CMusicDlg::SetControlPos(int cx, int cy)
{
	//变量定义
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOSIZE;

	//锁定屏幕
	LockWindowUpdate();

	//移动控件
	HDWP hDwp=BeginDeferWindowPos(32);

	CRect rcButton;
	m_btClose.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp,m_btClose,NULL,cx-rcButton.Width()-2,0,0,0,uFlags);
	DeferWindowPos(hDwp,m_btMin,NULL,cx-rcButton.Width()-2-18,0,0,0,uFlags);

	EndDeferWindowPos(hDwp);

	//重画界面
	Invalidate(FALSE);
	UpdateWindow();

	//解除锁定
	UnlockWindowUpdate();
}


void CMusicDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CMyDialog::OnLButtonDown(nFlags, point);
}

BOOL CMusicDlg::OnEraseBkgnd(CDC* pDC)
{
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

//	CRect rc(0,0,nWidth,nHeight);
//	m_ImageBack.Draw(pDC->GetSafeHdc(),0, 0, nWidth, nHeight);
	if (&m_BackImg != NULL && !m_BackImg.IsNull()) {
		m_BackImg.Draw(pDC, rcClient);
	}
}

void CMusicDlg::InitButton()
{
	HINSTANCE hInstance = AfxGetInstanceHandle();
/*
	m_btPrev.Create(NULL, WS_CHILD|WS_VISIBLE, CRect(90,45,0,0), this,IDC_PREV);
	m_btPrev.SetButtonImage(hInstance, MAKEINTRESOURCE(IDB_PREV), _T("PNG"));
	m_btPlay.Create(NULL, WS_CHILD|WS_VISIBLE, CRect(130,45,0,0), this,IDC_PLAY);
	m_btPlay.SetButtonImage(hInstance, MAKEINTRESOURCE(IDB_PLAY), _T("PNG"));
	m_btPause.Create(NULL, WS_CHILD, CRect(130,45,0,0), this,IDC_PAUSE);
	m_btPause.SetButtonImage(hInstance, MAKEINTRESOURCE(IDB_PAUSE), _T("PNG"));
	m_btNext.Create(NULL, WS_CHILD|WS_VISIBLE, CRect(170,45,0,0), this,IDC_NEXT);
	m_btNext.SetButtonImage(hInstance, MAKEINTRESOURCE(IDB_NEXT), _T("PNG"));*/

	HDC hParentDC = GetBackDC();
	m_btRight.SetBackImage(_T("res\\button-check_basic_blue48.png"), 
		_T("res\\button-check_basic_blue48.png"),
		_T("res\\button-check_basic_blue48.png"),
		_T("res\\button-check_basic_blue48.png"));
	m_btRight.SetButtonType(BT_PUSHBUTTON);
	m_btRight.SetParentBack(hParentDC);
	m_btRight.SetSize(24,24);
	m_btRight.MoveWindow(10,502,24,24);


	m_btSet.SetBackImage(NULL,_T("res\\allbtn_highlight.png"),
		_T("res\\allbtn_down.png"), NULL, &CRect(3,3,3,3));
	m_btSet.SetIconImage(_T("res\\tab_set.png"));
	m_btSet.SetButtonType(BT_ICONBUTTON);
	m_btSet.SetParentBack(hParentDC);
	m_btSet.SetSize(60, 26);
	m_btSet.MoveWindow(530, 502, 60, 26);

	HFONT font;
	font = CreateFont(0, 0, 0, 0, FW_DONTCARE, TRUE, FALSE, FALSE, DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,_T("华文行楷"));
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

}

void CMusicDlg::InitEdit()
{

}

void CMusicDlg::InitTabCtrl() {
	m_Tab.SetParentBack(GetBackDC());
	for (int i = 0; i < 3; i++) {
		m_Tab.AddItem(i);
	}

	m_Tab.SetItemSize(CSize(64, 64), CSize(104, 74));
	m_Tab.SetItemPadding(0, 10);
	m_Tab.SetItemPadding(1, 60);
	m_Tab.SetItemPadding(2, 10);
	m_Tab.SetIconImage(0, _T("res\\tab1.png"), _T("res\\tab1.png"));
	m_Tab.SetIconImage(1, _T("res\\tab2.png"), _T("res\\tab2.png"));
	m_Tab.SetIconImage(2, _T("res\\tab3.png"), _T("res\\tab3.png"));

//	m_Tab.SetBackImage(_T("res\\back.png"), &CRect(2,2,2,2));
	m_Tab.SetItemsImage(NULL, _T("res\\Hoven.png"), _T("res\\down.png"), &CRect(2,2,2,2));
	m_Tab.SetLeftTop(10,10);
	m_Tab.SetCurSel(0);
	m_Tab.MoveWindow(0,0 ,597, 527);
}

void CMusicDlg::OnClickedButton4()
{
	// TODO: Add your control notification handler code here
	/*m_list1.InsertItem(8,NULL);	
	m_list1.SetItemText(8,1,_T("我的同步"));
	m_list1.SetItemText(8,2,_T("new"));
	m_list1.InsertImage(8,_T("res\\DocType.png"));*/
}


void CMusicDlg::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nItem = pNMItemActivate->iItem;
	int nSubItem = pNMItemActivate->iSubItem;

	if (nSubItem == 2) {
		m_list1.SetItemContent(nItem, _T("我的同步"), _T("@2设备 0本地"), _T(""));
	}
	
	*pResult = 0;
}


void CMusicDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nCurSel = m_Tab.GetCurSel();

	switch (nCurSel) {
		case 0:			

			m_page0.ShowWindow(SW_SHOW);
			m_page1.ShowWindow(SW_HIDE);
			m_page2.ShowWindow(SW_HIDE);
			break;
		case 1:
			/*m_page0.AnimateWindow(1000,  AW_HIDE | AW_SLIDE | AW_HOR_NEGATIVE);
			m_page1.AnimateWindow(500,  AW_ACTIVATE |AW_SLIDE | AW_HOR_POSITIVE);*/
			m_page0.ShowWindow(SW_HIDE);
			m_page1.ShowWindow(SW_SHOW);
			m_page2.ShowWindow(SW_HIDE);

			break;
		case 2:
			m_page0.ShowWindow(SW_HIDE);
			m_page1.ShowWindow(SW_HIDE);
			m_page2.ShowWindow(SW_SHOW);
			break;
	}

	*pResult = 0;
}


void CMusicDlg::OnBnClickedSet()
{
	CDialogSet dlg;
	dlg.DoModal();
}

