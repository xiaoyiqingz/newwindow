// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "Page1.h"
#include "afxdialogex.h"


// CPage1 dialog

IMPLEMENT_DYNAMIC(CPage1, CMyDialog)

CPage1::CPage1(CWnd* pParent /*=NULL*/)
	: CMyDialog(CPage1::IDD, pParent)
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


BEGIN_MESSAGE_MAP(CPage1, CMyDialog)
END_MESSAGE_MAP()


// CPage1 message handlers

BOOL CPage1::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	OnInitListCtrl();

	HDC  hParentDC = GetBackDC();
	m_btAdd.SetBackImage(_T("res\\button_add_nor.png"), _T("res\\button_add_hov.png"),
		_T("res\\button_add_hov.png"), _T("res\\button_add_nor.png"));
	m_btAdd.SetButtonType(BT_PUSHBUTTON);
	m_btAdd.SetParentBack(hParentDC);
	m_btAdd.SetSize(500, 48);
	m_btAdd.MoveWindow(50, 370, 500, 48);

	return TRUE;  	
}

void CPage1::OnInitListCtrl()
{
	m_ListPhone.InsertColumn(0, _T(""), LVCFMT_LEFT, 100);
	m_ListPhone.InsertColumn(1, _T(""), LVCFMT_LEFT, 300);
	m_ListPhone.InsertColumn(2, _T(""), LVCFMT_LEFT, 197);

	m_ListPhone.SetHovenImage(_T("res\\item_bg_hover.png"),&CRect(2,2,2,2));
	m_ListPhone.SetSelectImage(_T("res\\item_bg_selected.png"),&CRect(2,2,2,2));
	m_ListPhone.SetScrollImage(&m_ListPhone, _T("res\\SKIN_SCROLL.bmp"));

	m_ListPhone.InsertItem(0, NULL);
	m_ListPhone.InsertImage(0, 0, _T("res\\Android.png"));
	m_ListPhone.SetItemContent(0, _T("Android"), _T(""), _T("F:\\手机备份"));

	m_ListPhone.InsertItem(1, NULL);
	m_ListPhone.InsertImage(1, 0, _T("res\\Apple.png"));
	m_ListPhone.SetItemContent(1, _T("iPhone"), _T(""), _T("F:\\手机备份"));

	m_ListPhone.InsertItem(2, NULL);
	m_ListPhone.InsertImage(2, 0, _T("res\\Android.png"));
	m_ListPhone.SetItemContent(2, _T("Android"), _T(""), _T("F:\\手机备份"));

	m_ListPhone.SetItemHeight(70);
	m_ListPhone.MoveWindow(0,0,597,350);
	m_ListPhone.m_HeaderCtrl.EnableWindow(FALSE);
	m_ListPhone.m_HeaderCtrl.SetLockCount(1);
}
