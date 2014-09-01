// AddWin.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "AddWin.h"
#include "afxdialogex.h"


// CAddWin dialog

IMPLEMENT_DYNAMIC(CAddWin, CZiDialog)

CAddWin::CAddWin(CWnd* pParent /*=NULL*/)
	: CZiDialog(CAddWin::IDD, pParent)
{

}

CAddWin::~CAddWin()
{
}

void CAddWin::DoDataExchange(CDataExchange* pDX)
{
	CZiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICE, m_ListDevice);
}


BEGIN_MESSAGE_MAP(CAddWin, CZiDialog)
END_MESSAGE_MAP()


// CAddWin message handlers


BOOL CAddWin::OnInitDialog()
{
	CZiDialog::OnInitDialog();

	m_ListDevice.SetParentBack(GetBackDC());
	m_ListDevice.SetScrollImage(&m_ListDevice, IDB_SCROLL_BAR, IMAGE_PNG);

	m_ListDevice.SetItemImage(0, IDB_DEVICE_LINUX, IDB_LIST_CHECK_NOR, 
		IDB_LIST_CHECK_SEL, IMAGE_PNG);
	m_ListDevice.SetItemText(0,_T("Zhang"));
	for (int i = 1; i < 5; i++) {
		m_ListDevice.SetItemImage(i, IDB_DEVICE_WIN, IDB_LIST_CHECK_NOR, 
			IDB_LIST_CHECK_SEL, IMAGE_PNG);
		m_ListDevice.SetItemText(i,_T("DeskTop"));
	}
	return TRUE; 
}
