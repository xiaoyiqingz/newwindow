// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "Page1.h"
#include "afxdialogex.h"


// CPage1 dialog

IMPLEMENT_DYNAMIC(CPage1, CZiDialog)

CPage1::CPage1(CWnd* pParent /*=NULL*/)
	: CZiDialog(CPage1::IDD, pParent)
{

}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PHONE, m_ListPhone);
	DDX_Control(pDX, IDC_BUTTON1, m_btAdd);
}


BEGIN_MESSAGE_MAP(CPage1, CZiDialog)
END_MESSAGE_MAP()


// CPage1 message handlers

BOOL CPage1::OnInitDialog()
{
	CZiDialog::OnInitDialog();

	OnInitListCtrl();

	HDC  hParentDC = GetBackDC();
	m_btAdd.SetBackImage(IDB_BT_ADD_NOR, IDB_BT_ADD_HOV, 
		IDB_BT_ADD_HOV, IDB_BT_ADD_NOR, _T("PNG"));
	m_btAdd.SetButtonType(BT_PUSHBUTTON);
	m_btAdd.SetParentBack(hParentDC);
	m_btAdd.SetSize(500, 48);
	m_btAdd.MoveWindow(50, 370, 500, 48);

	return TRUE;  	
}

void CPage1::OnInitListCtrl()
{
	m_ListPhone.InsertColumn(0, _T(""), LVCFMT_LEFT, 100);
	m_ListPhone.InsertColumn(1, _T(""), LVCFMT_LEFT, 350);
	m_ListPhone.InsertColumn(2, _T(""), LVCFMT_LEFT, 147);

	m_ListPhone.SetHovenImage(IDB_LIST_BACK_HOV, IMAGE_PNG, CRect(2,2,2,2));
	m_ListPhone.SetSelectImage(IDB_LIST_BACK_SEL, IMAGE_PNG, CRect(2,2,2,2));
	m_ListPhone.SetScrollImage(&m_ListPhone, _T("res\\SKIN_SCROLL.bmp"));

	m_ListPhone.InsertItem(0, NULL);
	m_ListPhone.InsertImage(0, 0, IDB_PHONE_ANDROID, 0, IMAGE_PNG);
	m_ListPhone.SetItemContent(0, _T("Android"), _T(""), _T("F:\\手机备份"),
		_T("上次备份完成于1分钟前"));

	m_ListPhone.InsertItem(1, NULL);
	m_ListPhone.InsertImage(1, 0, IDB_PHONE_IOS, 0, IMAGE_PNG);
	m_ListPhone.SetItemContent(1, _T("iPhone"), _T(""), _T("F:\\手机备份"),
		_T("上次备份完成于 2014-07-16"));

	m_ListPhone.InsertItem(2, NULL);
	m_ListPhone.InsertImage(2, 0, IDB_PHONE_ANDROID, 0, IMAGE_PNG);
	m_ListPhone.SetItemContent(2, _T("Android"), _T(""), _T("F:\\手机备份"),
		_T("上次备份完成于 2014-07-16"));

	m_ListPhone.SetItemHeight(70);
	m_ListPhone.MoveWindow(0,0,597,350);
}
