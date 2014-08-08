// SetPage0.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "SetPage0.h"
#include "afxdialogex.h"


// CSetPage0 dialog

IMPLEMENT_DYNAMIC(CSetPage0, CDialog)

CSetPage0::CSetPage0(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSetPage0::IDD, pParent)
{

}

CSetPage0::~CSetPage0()
{
}

void CSetPage0::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BT_ACCOUNT, m_btAccount);
	DDX_Control(pDX, IDC_BT_NAME, m_btName);
}


BEGIN_MESSAGE_MAP(CSetPage0, CMyDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CSetPage0 message handlers

BOOL CSetPage0::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	OnInitButton();

	return TRUE;  
}

void CSetPage0::OnInitButton()
{
	HDC hParentDC = GetBackDC();
	m_btAccount.SetBackImage(_T("res\\bt_back.png"),_T("res\\bt_back.png"),
		_T("res\\bt_back.png"),_T("res\\bt_back.png"));
	m_btAccount.SetButtonType(BT_PUSHBUTTON);
	m_btAccount.SetParentBack(hParentDC);
	m_btAccount.SetSize(74, 26);

	m_btName.SetBackImage(_T("res\\bt_back.png"),_T("res\\bt_back.png"),
		_T("res\\bt_back.png"),_T("res\\bt_back.png"));
	m_btName.SetButtonType(BT_PUSHBUTTON);
	m_btName.SetParentBack(hParentDC);
	m_btName.SetSize(74, 26);
}



BOOL CSetPage0::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
//	return CMyDialog::OnEraseBkgnd(pDC);
}
