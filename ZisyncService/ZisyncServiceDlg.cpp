
// ZisyncServiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "ZisyncServiceDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "DialogSet.h"
#include "MemoryDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_MIN		WM_USER+0x014
// CZisyncServiceDlg dialog


CZisyncServiceDlg::CZisyncServiceDlg(CWnd* pParent /*=NULL*/)
	: CZiDialog(CZisyncServiceDlg::IDD, pParent)
{
	m_bIsInit = false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZisyncServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CZiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SET, m_btSet);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_BUTTON4, m_btRight);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CZisyncServiceDlg, CZiDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CZisyncServiceDlg::OnClickList1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CZisyncServiceDlg::OnSelchangeTab1)
	ON_BN_CLICKED(IDC_SET, &CZisyncServiceDlg::OnBnClickedSet)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CZisyncServiceDlg message handlers

BOOL CZisyncServiceDlg::OnInitDialog()
{
	CZiDialog::OnInitDialog();

	/*_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );*/

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	LoadBackSkin(AfxGetInstanceHandle(), IDB_BACK_NEW, IMAGE_PNG);
	SetWindowPos(NULL, 0, 0, 597, 527, SWP_NOMOVE);	

	CRect rcControl(0,0,0,0);
	HDC hParentDC = GetBackDC();
	m_btClose.Create(NULL, WS_VISIBLE | WS_CHILD, rcControl, this, IDCANCEL);
	m_btClose.SetBackImage(IDB_CLOSE_NOR, IDB_CLOSE_HOV, IDB_CLOSE_SEL, 
		IDB_CLOSE_FOC, IMAGE_PNG);
	m_btClose.SetButtonType(BT_PUSHBUTTON);
	m_btClose.SetParentBack(hParentDC);
	m_btClose.SetSize(18,18);

	m_btMin.Create(NULL, WS_VISIBLE | WS_CHILD, rcControl, this, IDC_MIN);
	m_btMin.SetBackImage(IDB_MIN_NOR, IDB_MIN_HOV, IDB_MIN_SEL,
		IDB_MIN_FOC,IMAGE_PNG);
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

	return TRUE;  
}


void CZisyncServiceDlg::OnPaint()
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
		CZiDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CZisyncServiceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CZisyncServiceDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	switch (LOWORD(wParam)) {
	case IDC_MIN:
		ShowWindow(SW_MINIMIZE);
		break;
	}
	return CZiDialog::OnCommand(wParam, lParam);
}


void CZisyncServiceDlg::OnSize(UINT nType, int cx, int cy)
{
	CZiDialog::OnSize(nType, cx, cy);
	if( !m_bIsInit ) return;

	SetControlPos(cx, cy);
}


void CZisyncServiceDlg::SetControlPos(int cx, int cy)
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


void CZisyncServiceDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CZiDialog::OnLButtonDown(nFlags, point);
}

BOOL CZisyncServiceDlg::OnEraseBkgnd(CDC* pDC)
{
/*
	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC BufferDC(pDC,&rcClient);

	BufferDC.FillSolidRect(&rcClient,m_colBack);*/

	return TRUE;
//	return CMyDialog::OnEraseBkgnd(pDC);
}

/*
bool CZisyncServiceDlg::OnMaxSize()
{
	CRect rcClient;
	GetClientRect(&rcClient);

	static bool bMini = false;

	bMini = !bMini;

	SetWindowPos(NULL, 0, 0, rcClient.Width(), (bMini? 76:510), SWP_NOMOVE);
	
	return true;
}*/


void CZisyncServiceDlg::DrawClientArea(CDC*pDC,int nWidth,int nHeight)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	if (&m_BackImg != NULL && !m_BackImg.IsNull()) {
		m_BackImg.Draw(pDC, rcClient);
	}
}

void CZisyncServiceDlg::InitButton()
{
	HINSTANCE hInstance = AfxGetInstanceHandle();

	HDC hParentDC = GetBackDC();
	m_btRight.SetBackImage(IDB_BT_STATUS_OK, 0, 0, 0, IMAGE_PNG);
	m_btRight.SetButtonType(BT_PUSHBUTTON);
	m_btRight.SetParentBack(hParentDC);
	m_btRight.SetSize(24,24);
	m_btRight.MoveWindow(10,502,24,24);


	m_btSet.SetBackImage(0, IDB_BT_BACK_HOV, IDB_BT_BACK_DOWN, 0, IMAGE_PNG, 
		&CRect(3,3,3,3));
	m_btSet.SetIconImage(IDB_BT_SET, IMAGE_PNG);
	m_btSet.SetButtonType(BT_ICONBUTTON);
	m_btSet.SetParentBack(hParentDC);
	m_btSet.SetSize(60, 26);
	m_btSet.MoveWindow(530, 502, 60, 26);
}

void CZisyncServiceDlg::InitTabCtrl() {
	m_Tab.SetParentBack(GetBackDC());
	for (int i = 0; i < 3; i++) {
		m_Tab.AddItem(i);
	}

	m_Tab.SetItemSize(CSize(64, 64), CSize(104, 74));
	m_Tab.SetItemPadding(0, 10);
	m_Tab.SetItemPadding(1, 60);
	m_Tab.SetItemPadding(2, 10);
	m_Tab.SetIconImage(0, IDB_TAB_DEVICE, 0, IMAGE_PNG);
	m_Tab.SetIconImage(1, IDB_TAB_PHONE, 0, IMAGE_PNG);
	m_Tab.SetIconImage(2, IDB_TAB_HISTROY, 0, IMAGE_PNG);

	m_Tab.SetItemsImage(0, IDB_TAB_BACK_HOVEN, IDB_TAB_BACK_DOWN, 
		IMAGE_PNG, &CRect(2,2,2,2));
	m_Tab.SetLeftTop(10,10);
	m_Tab.SetCurSel(0);
	m_Tab.MoveWindow(0,0 ,597, 527);
}

void CZisyncServiceDlg::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nItem = pNMItemActivate->iItem;
	int nSubItem = pNMItemActivate->iSubItem;

	if (nSubItem == 2) {
		m_list1.SetItemContent(nItem, _T("我的同步"), _T("@2设备 0本地"), _T(""));
	}
	
	*pResult = 0;
}


void CZisyncServiceDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nCurSel = m_Tab.GetCurSel();

	switch (nCurSel) {
		case 0:			

			m_page0.ShowWindow(SW_SHOW);
			m_page1.ShowWindow(SW_HIDE);
			m_page2.ShowWindow(SW_HIDE);
			break;
		case 1:
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


void CZisyncServiceDlg::OnBnClickedSet()
{
	CDialogSet dlg;
	dlg.DoModal();
}

