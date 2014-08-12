// SyncDirSet.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "SyncDirSet.h"
#include "afxdialogex.h"


// CSyncDirSet dialog

IMPLEMENT_DYNAMIC(CSyncDirSet, CMyDialog)

CSyncDirSet::CSyncDirSet(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSyncDirSet::IDD, pParent)
{

}

CSyncDirSet::~CSyncDirSet()
{
}

void CSyncDirSet::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BT_DELETE_DIR, m_btDeleteDir);
	DDX_Control(pDX, IDC_BT_OK, m_btOk);
	DDX_Control(pDX, IDC_BT_CANCLE, m_btCancle);
	DDX_Control(pDX, IDC_BT_CANCLE_SYNC, m_btCancleSync);
	DDX_Control(pDX, IDC_BT_SET, m_btSet);
	DDX_Control(pDX, IDC_LIST_DIR, m_ListDir);
}


BEGIN_MESSAGE_MAP(CSyncDirSet, CMyDialog)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CSyncDirSet message handlers


BOOL CSyncDirSet::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CRect  rcControl(0, 0, 0, 0);
	m_btClose.Create(NULL, WS_CHILD | WS_VISIBLE, rcControl, this, IDCANCEL);
	m_btClose.SetBackImage(_T("res\\close1.png"), _T("res\\close2.png"), 
		_T("res\\close3.png"), _T("res\\close4.png"));
	m_btClose.SetButtonType(BT_PUSHBUTTON);
	m_btClose.SetParentBack(GetBackDC());
	m_btClose.SetSize(18, 18);
	
	CRect rcCleint;
	GetClientRect(&rcCleint);
	SetControlPos(rcCleint.Width(), rcCleint.Height());

	OnInitButton();
	OnInitListCtrl();
	return TRUE;  
}


void CSyncDirSet::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CMyDialog::OnLButtonDown(nFlags, point);
}

void CSyncDirSet::SetControlPos(int cx, int cy)
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

void CSyncDirSet::OnInitButton()
{
	HDC hParentDC = GetBackDC();
	m_btDeleteDir.SetBackImage(_T("res\\bt_delete_nor.png"), _T("res\\bt_delete_hov.png"),
		_T("res\\bt_delete_hov.png"), _T("res\\bt_delete_nor.png"),CRect(2, 2, 2, 2));
	m_btDeleteDir.SetButtonType(BT_PUSHBUTTON);
	m_btDeleteDir.SetParentBack(hParentDC);
	m_btDeleteDir.SetSize(130, 30);

	m_btOk.SetBackImage(_T("res\\bt_back.png"),_T("res\\bt_back.png"),
		_T("res\\bt_back.png"),_T("res\\bt_back.png"));
	m_btOk.SetButtonType(BT_PUSHBUTTON);
	m_btOk.SetParentBack(hParentDC);
	m_btOk.SetSize(74, 26);

	m_btCancle.SetBackImage(_T("res\\bt_back.png"),_T("res\\bt_back.png"),
		_T("res\\bt_back.png"),_T("res\\bt_back.png"));
	m_btCancle.SetButtonType(BT_PUSHBUTTON);
	m_btCancle.SetParentBack(hParentDC);
	m_btCancle.SetSize(74, 26);

	m_btCancleSync.SetBackImage(_T("res\\bt_back.png"),_T("res\\bt_back.png"),
		_T("res\\bt_back.png"),_T("res\\bt_back.png"));
	m_btCancleSync.SetButtonType(BT_PUSHBUTTON);
	m_btCancleSync.SetParentBack(hParentDC);
	m_btCancleSync.SetSize(74, 26);

	m_btSet.SetBackImage(_T("res\\bt_back.png"),_T("res\\bt_back.png"),
		_T("res\\bt_back.png"),_T("res\\bt_back.png"));
	m_btSet.SetButtonType(BT_PUSHBUTTON);
	m_btSet.SetParentBack(hParentDC);
	m_btSet.SetSize(74, 26);
}

void CSyncDirSet::OnInitListCtrl()
{
	LVGROUP grp;
	memset(&grp, 0, sizeof(grp));
	grp.cbSize = sizeof(LVGROUP);
	grp.mask = LVGF_GROUPID | LVGF_HEADER | LVGF_STATE;
	grp.stateMask = LVGS_NORMAL;
	grp.state = LVGS_NORMAL;

	grp.pszHeader = _T("本机同步副本");
	grp.cchHeader = (int) wcslen(grp.pszHeader);
	grp.iGroupId = 0;
	m_ListDir.InsertGroup(0, &grp);

	grp.pszHeader = _T("远端同步副本");
	grp.cchHeader = (int) wcslen(grp.pszHeader);
	grp.iGroupId = 1;
	m_ListDir.InsertGroup(1, &grp);

	m_ListDir.EnableGroupView(TRUE);

	m_ImageList.Create(32,32,ILC_MASK|ILC_COLOR32, 0, 0);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	m_ListDir.SetImageList(&m_ImageList, LVSIL_NORMAL);
	m_ListDir.InsertColumn(0, _T(""), LVCFMT_LEFT, 350);
	m_ListDir.InsertColumn(1, _T(""), LVCFMT_RIGHT, 50);

	DWORD ExStyle=m_ListDir.GetExtendedStyle();
	ExStyle |= LVS_EX_FULLROWSELECT;
	// ExStyle |= LVS_EX_GRIDLINES;
	// ExStyle |= LVS_EX_CHECKBOXES;
	m_ListDir.SetExtendedStyle(ExStyle);

	LVITEM lvitem;
	memset(&lvitem, 0, sizeof(lvitem));
	lvitem.mask = LVIF_TEXT|LVIF_STATE|LVIF_GROUPID|LVIF_IMAGE|LVIF_COLUMNS;
	lvitem.pszText = _T("D:\\共享同步文件夹");
	lvitem.iImage = 0;
	lvitem.iItem = 0;
	lvitem.iGroupId = 0;
	m_ListDir.InsertItem(&lvitem);
	m_ListDir.SetItemText(0, 1, _T("在线"));

	lvitem.pszText = _T("F:\\共享同步文件夹");
	lvitem.iImage = 0;
	lvitem.iItem = 1;
	lvitem.iGroupId = 0;
	m_ListDir.InsertItem(&lvitem);

	lvitem.pszText = _T("F:\\共享同步文件夹");
	lvitem.iImage = 0;
	lvitem.iItem = 1;
	lvitem.iGroupId = 1;
	m_ListDir.InsertItem(&lvitem);
}
