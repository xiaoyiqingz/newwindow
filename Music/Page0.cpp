// Page0.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "Page0.h"
#include "AddDevice.h"
#include "SyncDirSet.h"
#include "CreateSyncDIr.h"
#include "afxdialogex.h"


// CPage0 dialog

IMPLEMENT_DYNAMIC(CPage0, CDialog)

CPage0::CPage0(CWnd* pParent /*=NULL*/)
	: CMyDialog(CPage0::IDD, pParent)
{

}

CPage0::~CPage0()
{
}

void CPage0::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_BUTTON1, m_buttonadd);
}


BEGIN_MESSAGE_MAP(CPage0, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage0::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPage0::OnClickList1)
END_MESSAGE_MAP()


// CPage0 message handlers

BOOL CPage0::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	HDC hParentDC = GetBackDC(); 
	m_buttonadd.SetBackImage(_T("res\\button_add_nor.png"), 
		_T("res\\button_add_hov.png"),
		_T("res\\button_add_hov.png"),
		_T("res\\button_add_nor.png"));
	m_buttonadd.SetButtonType(BT_PUSHBUTTON);
	m_buttonadd.SetParentBack(hParentDC);
	m_buttonadd.SetSize(500,48);
	m_buttonadd.MoveWindow(50,370,500,48);	

	OnInitListCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPage0::OnInitListCtrl()
{
	m_list1.InsertColumn( 0, _T(""), LVCFMT_LEFT, 100 );
	m_list1.InsertColumn( 1, _T(""), LVCFMT_LEFT, 327 );
	m_list1.InsertColumn( 2, _T(""), LVCFMT_LEFT, 50 );
	m_list1.InsertColumn( 3, _T(""), LVCFMT_LEFT, 50 );
	m_list1.InsertColumn( 4, _T(""), LVCFMT_LEFT, 50 );
//	m_list1.m_HeaderCtrl.SetItemHeight(0);
/*
	m_list1.m_HeaderCtrl.SetBackImage(_T("res\\folder_nav_item_bg_hover.png"),&CRect(2,2,2,2));
	m_list1.m_HeaderCtrl.SetPressImage(_T("res\\folder_nav_item_bg_pressed.png"),&CRect(2,2,2,2));
	m_list1.m_HeaderCtrl.SetGridImage(_T("res\\category_sep.png"));*/
	m_list1.SetHovenImage(_T("res\\item_bg_hover.png"),&CRect(2,2,2,2));
	m_list1.SetSelectImage(_T("res\\item_bg_selected.png"),&CRect(2,2,2,2));
	m_list1.SetScrollImage(&m_list1,_T("res\\SKIN_SCROLL.bmp"));

	for (int i=0; i < 3; i++) {
		m_list1.InsertItem(i,NULL);	
		m_list1.SetItemContent(i, _T("我的自同步"), _T("@3设备 1本地"), _T("历史记录"));
		m_list1.InsertImage(i, 0, _T("res\\appicns_folder_Download.png"));
		m_list1.InsertImage(i, 2, _T("res\\tab1image1.png"), _T("res\\tab1image_gray.png"));
		m_list1.InsertImage(i, 3, _T("res\\button_invite.png"));
		m_list1.InsertImage(i, 4, _T("res\\tab_set.png"));
	}

	m_list1.InsertItem(3, NULL);
	m_list1.SetItemContent(3, _T("自同步"), _T("@2设备 1本地"), _T("历史记录"));
	m_list1.InsertImage(3, 0,_T("res\\appicns_folder_Download.png"));
	m_list1.InsertImage(3, 2, _T("res\\tab1image1.png"), _T("res\\tab1image_gray.png"));
	m_list1.InsertImage(3, 3, _T("res\\button_invite.png"));
	m_list1.InsertImage(3, 4, _T("res\\tab_set.png"));

	m_list1.SetItemHeight(70);
	m_list1.MoveWindow(0,0,597,350);
//	m_list1.m_HeaderCtrl.EnableWindow(FALSE);
//	m_list1.m_HeaderCtrl.SetLockCount(1);
}

void CPage0::OnBnClickedButton1()
{
	CCreateSyncDIr dlg;
	dlg.DoModal();
}

void CPage0::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CAddDevice dlgAddDevice;
	CSyncDirSet dlgSyncDirSet;
	switch (pNMListView->iSubItem)
	{
		case 3:
			dlgAddDevice.DoModal();
			break;
		case 1:
			{
				POINT point;
				GetCursorPos(&point);
				::ScreenToClient(GetSafeHwnd(),&point);
				if (m_list1.HitTestRightTop(pNMListView->iItem, point)) {
					dlgSyncDirSet.DoModal();
				}
			}	
			break;
		case 4:
			dlgSyncDirSet.DoModal();
			break;
	}
	*pResult = 0;
}
