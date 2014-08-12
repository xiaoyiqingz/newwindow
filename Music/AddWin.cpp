// AddWin.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "AddWin.h"
#include "afxdialogex.h"


// CAddWin dialog

IMPLEMENT_DYNAMIC(CAddWin, CMyDialog)

CAddWin::CAddWin(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddWin::IDD, pParent)
{

}

CAddWin::~CAddWin()
{
}

void CAddWin::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICE, m_ListDevice);
}


BEGIN_MESSAGE_MAP(CAddWin, CMyDialog)
END_MESSAGE_MAP()


// CAddWin message handlers


BOOL CAddWin::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_ListDevice.SetParentBack(GetBackDC());
	m_ListDevice.SetScrollImage(&m_ListDevice,_T("res\\SKIN_SCROLL.bmp"));

	m_ListDevice.SetItemImage(0, _T("res\\linux.png"), _T("res\\check_nor.png"), 
		_T("res\\check_sel.png"));
	m_ListDevice.SetItemText(0,_T("Zhang"));
	for (int i = 1; i < 5; i++) {
		m_ListDevice.SetItemImage(i, _T("res\\win32.png"), _T("res\\check_nor.png"), 
			_T("res\\check_sel.png"));
		m_ListDevice.SetItemText(i,_T("DeskTop"));
	}
	return TRUE; 
}
