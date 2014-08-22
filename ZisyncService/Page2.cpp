// Page2.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "Page2.h"
#include "afxdialogex.h"


// CPage2 dialog

IMPLEMENT_DYNAMIC(CPage2, CMyDialog)

CPage2::CPage2(CWnd* pParent /*=NULL*/)
	: CMyDialog(CPage2::IDD, pParent)
{

}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}


BEGIN_MESSAGE_MAP(CPage2, CMyDialog)
END_MESSAGE_MAP()


// CPage2 message handlers


BOOL CPage2::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	OnInitListCtrl();
	return TRUE; 
}

void CPage2::OnInitListCtrl()
{
	m_list1.InsertColumn(0, _T(""), LVCFMT_LEFT, 100);
	m_list1.InsertColumn(1, _T(""), LVCFMT_LEFT, 447);
	m_list1.InsertColumn(2, _T(""), LVCFMT_LEFT, 50);

	m_list1.SetHovenImage(_T("res\\item_bg_hover.png"),&CRect(2,2,2,2));
	m_list1.SetSelectImage(_T("res\\item_bg_selected.png"),&CRect(2,2,2,2));
	m_list1.SetScrollImage(&m_list1, _T("res\\SKIN_SCROLL.bmp"));

	m_list1.InsertItem(0, NULL);
	m_list1.InsertImage(0, 0, _T("res\\pdf.png"));
	m_list1.SetItemContent(0, _T("自同步使用说明.pdf"), _T("1分钟前"), _T("D:\\我的自同步"));
	m_list1.InsertImage(0, 2, _T("res\\folder_nor.png"), _T("res\\folder_nor.png"));

	m_list1.InsertItem(1, NULL);
	m_list1.InsertImage(1, 0, _T("res\\doc.png"));
	m_list1.SetItemContent(1, _T("自同步使用说明.doc"), _T("2小时前"), _T("D:\\我的自同步"));
	m_list1.InsertImage(1, 2, _T("res\\folder_nor.png"), _T("res\\folder_nor.png"));

	m_list1.InsertItem(2, NULL);
	m_list1.InsertImage(2, 0, _T("res\\png.png"));
	m_list1.SetItemContent(2, _T("相册封面.pdf"), _T("2014-07-06"), _T("D:\\我的自同步"));
	m_list1.InsertImage(2, 2, _T("res\\folder_del.png"), _T("res\\folder_del.png"));

	m_list1.InsertItem(3, NULL);
	m_list1.InsertImage(3, 0, _T("res\\folder.png"));
	m_list1.SetItemContent(3, _T("aa"), _T("2014-07-05"), _T("D:\\我的自同步"));
	m_list1.InsertImage(3, 2, _T("res\\folder_nor.png"), _T("res\\folder_nor.png"));

	m_list1.SetItemHeight(70);
	m_list1.MoveWindow(0,0,597,350);
}

