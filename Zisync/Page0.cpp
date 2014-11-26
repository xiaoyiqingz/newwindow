// Page0.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "Page0.h"
#include "AddDevice.h"
#include "SyncDirSet.h"
#include "CreateSyncDIr.h"
#include "afxdialogex.h"

// for test
#define LVITEMCOUNT 4

// CPage0 dialog

IMPLEMENT_DYNAMIC(CPage0, CDialog)

CPage0::CPage0(CWnd* pParent /*=NULL*/)
	: CZiDialog(CPage0::IDD, pParent)
{

}

CPage0::~CPage0()
{
}

void CPage0::DoDataExchange(CDataExchange* pDX)
{
	CZiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_BUTTON1, m_buttonadd);
}


BEGIN_MESSAGE_MAP(CPage0, CZiDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage0::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CPage0::OnClickList1)
END_MESSAGE_MAP()


// CPage0 message handlers

BOOL CPage0::OnInitDialog()
{
	CZiDialog::OnInitDialog();

	HDC hParentDC = GetBackDC(); 
	m_buttonadd.SetBackImage(IDB_BT_ADD_NOR, IDB_BT_ADD_HOV, 
		IDB_BT_ADD_HOV, IDB_BT_ADD_NOR, IMAGE_PNG);
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

	m_list1.SetHovenImage(IDB_LIST_BACK_HOV, IMAGE_PNG, CRect(2,2,2,2));
	m_list1.SetSelectImage(IDB_LIST_BACK_SEL, IMAGE_PNG, CRect(2,2,2,2));
//	m_list1.SetScrollImage(&m_list1,IDB_SCROLL_BAR, IMAGE_PNG);

	for (int i=0; i < LVITEMCOUNT; i++) {
		m_list1.InsertItem(i,NULL);	
		m_list1.SetItemContent(i, _T("我的自同步"), _T("@3设备 1本地"), _T("历史记录"));
		m_list1.InsertImage(i, 0, IDB_LIST_FOLDER, 0, IMAGE_PNG);
		m_list1.InsertImage(i, 2, IDB_LIST_SYNC_NOR, IDB_LIST_SYNC_SEL, IMAGE_PNG);
		m_list1.InsertImage(i, 3, IDB_LIST_INVITE, 0, IMAGE_PNG);
		m_list1.InsertImage(i, 4, IDB_BT_SET, 0, IMAGE_PNG);
	}

	m_list1.InsertItem(LVITEMCOUNT, NULL);
	m_list1.SetItemContent(LVITEMCOUNT, _T("自同步"), _T("@2设备 1本地"), _T("历史记录"));
	m_list1.InsertImage(LVITEMCOUNT, 0, IDB_LIST_FOLDER, 0, IMAGE_PNG);
	m_list1.InsertImage(LVITEMCOUNT, 2, IDB_LIST_SYNC_NOR, IDB_LIST_SYNC_SEL, IMAGE_PNG);
	m_list1.InsertImage(LVITEMCOUNT, 3, IDB_LIST_INVITE, 0, IMAGE_PNG);
	m_list1.InsertImage(LVITEMCOUNT, 4, IDB_BT_SET, 0, IMAGE_PNG);

	m_list1.SetItemHeight(70);
	m_list1.SetRightTopColor(RGB(0, 124, 248), RGB(248, 24, 0));
	m_list1.MoveWindow(0,0,597,350);
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
