// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// CMyDialog dialog

#define		IDC_WND_MAX			WM_USER+0x01
#define		IDC_WND_MIN			WM_USER+0x02

IMPLEMENT_DYNAMIC(CMyDialog, CDialog)

CMyDialog::CMyDialog(INT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	m_bIsInit = false;
	m_bIsZoomed = false;
	m_bExtrude = true;
}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMyDialog message handlers


BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD dwStyle = GetStyle();
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE| WS_SYSMENU |WS_MINIMIZEBOX
		|WS_MAXIMIZEBOX|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	dwNewStyle&=dwStyle;
	SetWindowLong(m_hWnd,GWL_STYLE,dwNewStyle);

	DWORD dwExStyle = GetExStyle();
	DWORD dwNewExStyle = WS_EX_LEFT |WS_EX_LTRREADING |WS_EX_RIGHTSCROLLBAR;
	dwNewExStyle&=dwExStyle;
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwNewExStyle);

	CRect rcControl(0,0,0,0);  //在WM_SIZE中改变大小

	m_btClose.Create(NULL,WS_CHILD|WS_VISIBLE,rcControl,this,IDCANCEL);
	m_btClose.SetButtonImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_CLOSE), _T("PNG"));

	m_btMax.Create(NULL,WS_CHILD|WS_VISIBLE,rcControl,this,IDC_WND_MAX);
	m_btMax.SetButtonImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_MAX), _T("PNG"));

	m_btMin.Create(NULL,WS_CHILD|WS_VISIBLE,rcControl,this,IDC_WND_MIN);
	m_btMin.SetButtonImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_MIN), _T("PNG"));

	m_bIsInit = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDialog::LoadBackSkin(LPCTSTR pszResourcePath)
{
	m_ImageBack.Load(pszResourcePath);
}

void CMyDialog::LoadBackSkin(HINSTANCE hInstance, UINT nIDResource, LPCTSTR pszType)
{
	if (pszType == NULL) 
		m_ImageBack.LoadFromResource(hInstance, nIDResource);
	else 
		m_ImageBack.LoadImage(hInstance, MAKEINTRESOURCE(nIDResource), pszType);
}

void CMyDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rcClient;
	GetClientRect(&rcClient);

	if (!m_ImageBack.IsNull()) {
		m_ImageBack.Draw(dc.GetSafeHdc(), 0, 0,rcClient.Width(), rcClient.Height());
//		m_ImageBack.DrawImageTile(&dc, 0, 0, rcClient.Width(), rcClient.Height());
//		m_ImageBack.BitBlt(dc.GetSafeHdc(), 0, 0, rcClient.Width(), rcClient.Height(), 0, 0);
	}
}


void CMyDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if( !m_bIsInit ) return;

	//变量定义
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOSIZE;

	//锁定屏幕
	LockWindowUpdate();

	//移动控件
	HDWP hDwp=BeginDeferWindowPos(32);

	CRect rcButton;
	m_btClose.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp,m_btClose,NULL,cx-rcButton.Width()-2,2,0,0,uFlags);
	DeferWindowPos(hDwp,m_btMax,NULL,cx-rcButton.Width()*2-2,2,0,0,uFlags);
	DeferWindowPos(hDwp,m_btMin,NULL,cx-rcButton.Width()*3-2,2,0,0,uFlags);

	EndDeferWindowPos(hDwp);

	//重画界面
	Invalidate(FALSE);
	UpdateWindow();

	//解除锁定
	UnlockWindowUpdate();
}


BOOL CMyDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam)) {
	case IDC_WND_MAX:
		if (!OnMaxSize()) {
			static CRect rcClient(0, 0, 0, 0);
			if (m_bIsZoomed) {
				MoveWindow(&rcClient);

				m_bIsZoomed = false;
			} else {
				GetWindowRect(&rcClient);

				CRect rc;
				SystemParametersInfo(SPI_GETWORKAREA, 0,&rc, 0);
				MoveWindow(&rc);

				m_bIsZoomed = true;
			}
		}
		break;

	case IDC_WND_MIN:
		{
			ShowWindow(SW_MINIMIZE);
			break;
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}


void CMyDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_bIsZoomed) {
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
		return;
	} 

	CDialog::OnLButtonDown(nFlags, point);
}
