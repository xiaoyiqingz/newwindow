// SetPage0.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "SetPage0.h"
#include "afxdialogex.h"


// CSetPage0 dialog

IMPLEMENT_DYNAMIC(CSetPage0, CDialog)

CSetPage0::CSetPage0(CWnd* pParent /*=NULL*/)
	: CZiDialog(CSetPage0::IDD, pParent)
{

}

CSetPage0::~CSetPage0()
{
}

void CSetPage0::DoDataExchange(CDataExchange* pDX)
{
	CZiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BT_ACCOUNT, m_btAccount);
	DDX_Control(pDX, IDC_BT_NAME, m_btName);
}


BEGIN_MESSAGE_MAP(CSetPage0, CZiDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSetPage0 message handlers

BOOL CSetPage0::OnInitDialog()
{
	CZiDialog::OnInitDialog();
	
	OnInitButton();

	return TRUE;  
}

void CSetPage0::OnInitButton()
{
	HDC hParentDC = GetBackDC();
	m_btAccount.SetBackImage(IDB_BT_BACK, 0, 0, 0, _T("PNG"));
	m_btAccount.SetButtonType(BT_PUSHBUTTON);
	m_btAccount.SetParentBack(hParentDC);
	m_btAccount.SetSize(74, 26);

	m_btName.SetBackImage(IDB_BT_BACK, 0, 0, 0, _T("PNG"));
	m_btName.SetButtonType(BT_PUSHBUTTON);
	m_btName.SetParentBack(hParentDC);
	m_btName.SetSize(74, 26);
}



BOOL CSetPage0::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
//	return CMyDialog::OnEraseBkgnd(pDC);
}


HBRUSH CSetPage0::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CZiDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		return	hBrush;
	}
	return hbr;
}
