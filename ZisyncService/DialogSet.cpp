// DialogSet.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "DialogSet.h"
#include "afxdialogex.h"


// CDialogSet dialog

IMPLEMENT_DYNAMIC(CDialogSet, CMyDialog)

CDialogSet::CDialogSet(CWnd* pParent /*=NULL*/)
	: CMyDialog(CDialogSet::IDD, pParent)
{
	m_bIsInit = false;
}

CDialogSet::~CDialogSet()
{
}

void CDialogSet::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SET, m_tabSet);
}


BEGIN_MESSAGE_MAP(CDialogSet, CMyDialog)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SET, &CDialogSet::OnSelchangeTabSet)
END_MESSAGE_MAP()


// CDialogSet message handlers


BOOL CDialogSet::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_ImageBack.LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SET_BACK), _T("PNG"));
	SetWindowPos(NULL, 0 , 0, 571, 400, SWP_NOMOVE);

	CRect rcControl(0, 0, 0, 0);
	HDC hParentDC = GetBackDC();
	m_btClose.Create(NULL,  WS_CHILD | WS_VISIBLE, rcControl, this, IDCANCEL);
	m_btClose.SetBackImage(IDB_CLOSE_NOR, IDB_CLOSE_HOV,IDB_CLOSE_SEL, 
		IDB_CLOSE_FOC, IMAGE_PNG);
	m_btClose.SetButtonType(BT_PUSHBUTTON);
	m_btClose.SetParentBack(hParentDC);
	m_btClose.SetSize(18 ,18);
	m_bIsInit = true;

	OnInitTabCtrl();
	m_Page0.Create(IDD_SETPAGE0, &m_tabSet);
	m_Page1.Create(IDD_SETPAGE1, &m_tabSet);
	m_Page2.Create(IDD_SETPAGE2, &m_tabSet);

	CRect rcPage;
	m_tabSet.GetClientRect(rcPage);
	rcPage.left = rcPage.left + 2;
	rcPage.top = rcPage.top + 24;
	rcPage.right = rcPage.right -2;
	rcPage.bottom = rcPage.bottom -2;
	
	m_Page0.MoveWindow(&rcPage);
	m_Page1.MoveWindow(&rcPage);
	m_Page2.MoveWindow(&rcPage);
	
	m_Page0.ShowWindow(SW_SHOW);
	m_Page1.ShowWindow(SW_HIDE);
	m_Page2.ShowWindow(SW_HIDE);

	CRect rcClient;
	GetClientRect(&rcClient);
	SetControlPos(rcClient.Width(), rcClient.Height());
	return TRUE; 
}


void CDialogSet::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);
	
	if (!m_bIsInit) return;
	SetControlPos(cx, cy);	
}

void CDialogSet::SetControlPos(int cx, int cy)
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

void CDialogSet::DrawClientArea(CDC*pDC,int nWidth,int nHeight)
{
	m_ImageBack.Draw(pDC, 0, 0, nWidth, nHeight, 0, 0, 0, 0);
}

void CDialogSet::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rcTitle(0, 0, 571, 30);

	if (PtInRect(&rcTitle, point)) {
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	}
	CMyDialog::OnLButtonDown(nFlags, point);
}

void CDialogSet::OnInitTabCtrl()
{
	m_tabSet.SetParentBack(GetBackDC());
	for (int i = 0 ; i < 3; i++) {
		m_tabSet.AddItem(i);
		m_tabSet.SetItemPadding(i,0);
	}

	m_tabSet.SetItemSize(CSize(100, 24), CSize(135, 24));
	m_tabSet.SetItemText(0, _T("常规"));
	m_tabSet.SetItemText(1, _T("网络"));
	m_tabSet.SetItemText(2, _T("高级"));
	m_tabSet.SetBackImage(IDB_TAB_SET_BACK, IMAGE_PNG);
	m_tabSet.SetItemsImage(IDB_TAB_SET_NOR, IDB_TAB_SET_NOR, IDB_TAB_SET_SEL, IMAGE_PNG);
	m_tabSet.SetLeftTop(100,0);
	m_tabSet.SetCurSel(0);
	m_tabSet.MoveWindow(35, 40, 495, 310);


}


void CDialogSet::OnSelchangeTabSet(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nCurSel = m_tabSet.GetCurSel();
	
	switch (nCurSel) {
		case 0:
			m_Page0.ShowWindow(SW_SHOW);
			m_Page1.ShowWindow(SW_HIDE);
			m_Page2.ShowWindow(SW_HIDE);
			break;
		case 1:
			m_Page0.ShowWindow(SW_HIDE);
			m_Page1.ShowWindow(SW_SHOW);
			m_Page2.ShowWindow(SW_HIDE);
			break;
		case 2:
			m_Page0.ShowWindow(SW_HIDE);
			m_Page1.ShowWindow(SW_HIDE);
			m_Page2.ShowWindow(SW_SHOW);
			break;
	}

	*pResult = 0;
}
