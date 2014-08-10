// AddDevice.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "AddDevice.h"
#include "afxdialogex.h"


// CAddDevice dialog

IMPLEMENT_DYNAMIC(CAddDevice, CMyDialog)

CAddDevice::CAddDevice(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddDevice::IDD, pParent)
{
	m_bIsInit = false;
}

CAddDevice::~CAddDevice()
{
}

void CAddDevice::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddDevice, CMyDialog)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CAddDevice message handlers


BOOL CAddDevice::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	m_ImageBack.LoadImage(AfxGetInstanceHandle(), IDB_DEVICE_BACK, _T("PNG"));
	
	CRect rcControl(0, 0, 0, 0);
	HDC hParentDC = GetBackDC();
	m_btClose.Create(NULL,  WS_CHILD | WS_VISIBLE, rcControl, this, IDCANCEL);
	m_btClose.SetBackImage(_T("res\\close1.png"), _T("res\\close2.png"), 
		_T("res\\close3.png"), _T("res\\close4.png"));
	m_btClose.SetButtonType(BT_PUSHBUTTON);
	m_btClose.SetParentBack(hParentDC);
	m_btClose.SetSize(18 ,18);
	m_bIsInit = true;

	CRect rcClient;
	GetClientRect(&rcClient);
	SetControlPos(rcClient.Width(), rcClient.Height());
	return TRUE; 
}

void CAddDevice::DrawClientArea(CDC*pDC,int nWidth,int nHeight)
{
	m_ImageBack.Draw(pDC, 0, 0, nWidth, nHeight, 0, 0, 0, 0);
}


void CAddDevice::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if (!m_bIsInit) return;
	SetControlPos(cx, cy);
}

void CAddDevice::SetControlPos(int cx, int cy)
{
	const  UINT  uFlags = SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOCOPYBITS | SWP_NOSIZE;

	LockWindowUpdate();

	HDWP hDwp = BeginDeferWindowPos(32);
	CRect rcButton;
	m_btClose.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp, m_btClose, NULL, cx - rcButton.Width() - 8, 4, 0, 0, uFlags);
	EndDeferWindowPos(hDwp);

	Invalidate(FALSE);
	UpdateWindow();

	UnlockWindowUpdate();
}


void CAddDevice::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rcTitle(0, 0, 465,30);
	if (PtInRect(&rcTitle, point)) {
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	}

	CMyDialog::OnLButtonDown(nFlags, point);
}
