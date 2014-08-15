// AddPhone.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "AddPhone.h"
#include "afxdialogex.h"


// CAddPhone dialog

IMPLEMENT_DYNAMIC(CAddPhone, CMyDialog)

CAddPhone::CAddPhone(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddPhone::IDD, pParent)
{
	
}

CAddPhone::~CAddPhone()
{
}

void CAddPhone::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BT_SPLIT, m_slipbt);
}


BEGIN_MESSAGE_MAP(CAddPhone, CMyDialog)
END_MESSAGE_MAP()


// CAddPhone message handlers


BOOL CAddPhone::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	m_Menu.LoadMenu(IDR_MENU1);
	CMenu *PopupMenu = m_Menu.GetSubMenu(0);

	m_slipbt.SetBackImage(_T("res\\bt_split.png"), _T("res\\bt_split.png"),
		_T("res\\bt_split.png"), _T("res\\bt_split.png"));
	m_slipbt.SetButtonType(BT_SPLITBUTTON);
	m_slipbt.SetParentBack(GetBackDC());
	m_slipbt.SetMenuImage(_T("res\\bt_menu.png"));
	m_slipbt.SetIconImage(_T("res\\bt_down.png"));
	m_slipbt.SetMenu(PopupMenu->m_hMenu);
	m_slipbt.SetSize(129, 32);
	return TRUE;  
}
