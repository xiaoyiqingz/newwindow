// CreateSyncDIr.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "CreateSyncDIr.h"
#include "afxdialogex.h"


// CCreateSyncDIr dialog

IMPLEMENT_DYNAMIC(CCreateSyncDIr, CMyDialog)

CCreateSyncDIr::CCreateSyncDIr(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCreateSyncDIr::IDD, pParent)
{

}

CCreateSyncDIr::~CCreateSyncDIr()
{
}

void CCreateSyncDIr::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BT_CREATE, m_btCreate);
	DDX_Control(pDX, IDC_AREA, m_gbArea);
}


BEGIN_MESSAGE_MAP(CCreateSyncDIr, CMyDialog)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CCreateSyncDIr message handlers


BOOL CCreateSyncDIr::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CRect rcControl(0, 0, 0, 0);
	HDC hParentDC = GetBackDC();
	m_btClose.Create(NULL,  WS_CHILD | WS_VISIBLE, rcControl, this, IDCANCEL);
	m_btClose.SetBackImage(_T("res\\close1.png"), _T("res\\close2.png"), 
		_T("res\\close3.png"), _T("res\\close4.png"));
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

	m_btCreate.SetBackImage(_T("res\\bt_create.png"),_T("res\\bt_create.png"),
		_T("res\\bt_create.png"),_T("res\\bt_create.png"), CRect(3,3,3,3));
	m_btCreate.SetButtonType(BT_PUSHBUTTON);
	m_btCreate.SetParentBack(GetBackDC());

	m_gbArea.SetItemSize(360, 244);
	m_gbArea.SetBackImage(_T("res\\bt_createdir.png"));
	m_gbArea.SetParentBack(GetBackDC());
	m_gbArea.MoveWindow(&rcCenter);
}


void CCreateSyncDIr::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CMyDialog::OnLButtonDown(nFlags, point);
}
