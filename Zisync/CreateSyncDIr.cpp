// CreateSyncDIr.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "CreateSyncDIr.h"
#include "afxdialogex.h"


// CCreateSyncDIr dialog

IMPLEMENT_DYNAMIC(CCreateSyncDIr, CZiDialog)

CCreateSyncDIr::CCreateSyncDIr(CWnd* pParent /*=NULL*/)
	: CZiDialog(CCreateSyncDIr::IDD, pParent)
{

}

CCreateSyncDIr::~CCreateSyncDIr()
{
}

void CCreateSyncDIr::DoDataExchange(CDataExchange* pDX)
{
	CZiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BT_CREATE, m_btCreate);
	DDX_Control(pDX, IDC_AREA, m_gbArea);
}


BEGIN_MESSAGE_MAP(CCreateSyncDIr, CZiDialog)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CCreateSyncDIr message handlers


BOOL CCreateSyncDIr::OnInitDialog()
{
	CZiDialog::OnInitDialog();

	CRect rcControl(0, 0, 0, 0);
	HDC hParentDC = GetBackDC();
	m_btClose.Create(NULL,  WS_CHILD | WS_VISIBLE, rcControl, this, IDCANCEL);
	m_btClose.SetBackImage(IDB_CLOSE_NOR, IDB_CLOSE_HOV,IDB_CLOSE_SEL, 
		IDB_CLOSE_FOC, IMAGE_PNG);
	m_btClose.SetButtonType(BT_PUSHBUTTON);
	m_btClose.SetParentBack(hParentDC);
	m_btClose.SetSize(18 ,18);

	CRect	rcClient;
	GetClientRect(&rcClient);
	SetControlPos(rcClient.Width(), rcClient.Height());
	
	OnInitButton();
	return TRUE;
}

void CCreateSyncDIr::SetControlPos(int cx, int cy)
{
	const  UINT  uFlags = SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOCOPYBITS | SWP_NOSIZE;

	LockWindowUpdate();

	HDWP hDwp = BeginDeferWindowPos(32);
	CRect rcButton;
	m_btClose.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp, m_btClose, NULL, cx - rcButton.Width() - 2, 0, 0, 0, uFlags);
	EndDeferWindowPos(hDwp);

	Invalidate(FALSE);
	UpdateWindow();

	UnlockWindowUpdate();
}

void CCreateSyncDIr::OnInitButton()
{
	CRect rcClient, rcCenter;
	GetClientRect(&rcClient);

	CalcCenterRect(rcClient, 360, 244, rcCenter);

	m_btCreate.SetBackImage(IDB_BT_CREATE, 0, 0, 0, IMAGE_PNG, CRect(3,3,3,3));
	m_btCreate.SetButtonType(BT_PUSHBUTTON);
	m_btCreate.SetParentBack(GetBackDC());

	m_gbArea.SetItemSize(360, 244);
	m_gbArea.SetBackImage(IDB_BT_CREATEDIR, IMAGE_PNG);
	m_gbArea.SetParentBack(GetBackDC());
	m_gbArea.MoveWindow(&rcCenter);
}


void CCreateSyncDIr::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CZiDialog::OnLButtonDown(nFlags, point);
}
