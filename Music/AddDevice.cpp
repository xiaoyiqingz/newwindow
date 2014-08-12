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
	DDX_Control(pDX, IDC_TAB_ADD, m_TabAdd);
	DDX_Control(pDX, IDC_BT_REFIND, m_btReFind);
	DDX_Control(pDX, IDC_BT_SELECTED, m_btSelected);
}


BEGIN_MESSAGE_MAP(CAddDevice, CMyDialog)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BT_SELECTED, &CAddDevice::OnBnClickedBtSelected)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_ADD, &CAddDevice::OnSelchangeTabAdd)
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

	OnInitButton();
	OnInitTabCtrl();
	m_Page0.Create(IDD_ADDWIN, &m_TabAdd);
	m_Page1.Create(IDD_ADDPHONE, &m_TabAdd);
	m_Page2.Create(IDD_ADDMAIL, &m_TabAdd);

	CRect rcPage(0, 48, 480, 380);
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

void CAddDevice::OnInitTabCtrl()
{
	m_TabAdd.SetParentBack(GetBackDC());
	for (int i = 0; i < 3; i++) {
		m_TabAdd.AddItem(i);
		m_TabAdd.SetItemPadding(i, 0);
	}
	m_TabAdd.SetItemSize(CSize(80, 34), CSize(80,34));
	m_TabAdd.SetIconImage(0,_T("res\\win_nor.png"), _T("res\\win_hov.png"));
	m_TabAdd.SetIconImage(1,_T("res\\phone_nor.png"), _T("res\\phone_hov.png"));
	m_TabAdd.SetIconImage(2,_T("res\\mail_nor.png"), _T("res\\mail_hov.png"));
	
	m_TabAdd.SetItemText(0, _T("电脑"));
	m_TabAdd.SetItemText(1, _T("手机"));
	m_TabAdd.SetItemText(2, _T("其他"));

//	m_TabAdd.SetBackImage(_T("res\\device_black.png"));
	m_TabAdd.SetLeftTop(5, 5);
	m_TabAdd.SetCurSel(0);
}

void CAddDevice::OnInitButton()
{
	HDC hParentDc = GetBackDC();
	m_btReFind.SetBackImage(_T("res\\bt_back.png"),_T("res\\bt_back.png"),
		_T("res\\bt_back.png"),_T("res\\bt_back.png"));
	m_btReFind.SetButtonType(BT_PUSHBUTTON);
	m_btReFind.SetParentBack(hParentDc);
	m_btReFind.SetSize(74, 26);

	m_btSelected.SetBackImage(_T("res\\bt_back.png"),_T("res\\bt_back.png"),
		_T("res\\bt_back.png"),_T("res\\bt_back.png"));
	m_btSelected.SetButtonType(BT_PUSHBUTTON);
	m_btSelected.SetParentBack(hParentDc);
	m_btSelected.SetSize(74, 26);
}


void CAddDevice::OnBnClickedBtSelected()
{
	CString strText(_T("选择的是:"));

	for (int i =0; i < m_Page0.m_ListDevice.GetItemCount(); i++) {
		if (m_Page0.m_ListDevice.GetChecked(i)) {
			strText.AppendFormat(_T("%d "), i);
		}
	}

	MessageBox(strText);
}


void CAddDevice::OnSelchangeTabAdd(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nIndex = m_TabAdd.GetCurSel();

	switch (nIndex) {
		case 0:
			m_Page0.ShowWindow(SW_SHOW);
			m_Page1.ShowWindow(SW_HIDE);
			m_Page2.ShowWindow(SW_HIDE);
			m_btReFind.ShowWindow(SW_SHOW);
			m_btSelected.ShowWindow(SW_SHOW);
			break;
		case 1:
			m_Page0.ShowWindow(SW_HIDE);
			m_Page1.ShowWindow(SW_SHOW);
			m_Page2.ShowWindow(SW_HIDE);
			m_btReFind.ShowWindow(SW_HIDE);
			m_btSelected.ShowWindow(SW_HIDE);
			break;
		case 2:
			m_Page0.ShowWindow(SW_HIDE);
			m_Page1.ShowWindow(SW_HIDE);
			m_Page2.ShowWindow(SW_SHOW);
			m_btReFind.ShowWindow(SW_HIDE);
			m_btSelected.ShowWindow(SW_HIDE);
			break;
	}
	*pResult = 0;
}
