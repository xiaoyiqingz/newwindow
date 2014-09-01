// SetUpPage1.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "SetUpPage1.h"
#include "afxdialogex.h"


// SetUpPage1 dialog

IMPLEMENT_DYNAMIC(CSetUpPage1, CZiDialog)

CSetUpPage1::CSetUpPage1(CWnd* pParent /*=NULL*/)
	: CZiDialog(CSetUpPage1::IDD, pParent)
{

}

CSetUpPage1::~CSetUpPage1()
{
}

void CSetUpPage1::DoDataExchange(CDataExchange* pDX)
{
	CZiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODIFY, m_btModify);
}


BEGIN_MESSAGE_MAP(CSetUpPage1, CZiDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// SetUpPage1 message handlers

BOOL CSetUpPage1::OnInitDialog()
{
	CZiDialog::OnInitDialog();

	OnInitButton();

	return TRUE;
}

HBRUSH CSetUpPage1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CZiDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	CFont font;
	if (pWnd->GetDlgCtrlID() == IDC_TITLE) {
		font.CreatePointFont(130, _T("ËÎÌו"));
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&font);
		HBRUSH hBrush =CreateSolidBrush(RGB(255, 255, 255));
		return hBrush;
	}

	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		return	hBrush;
	}

	return hbr;
}

void CSetUpPage1::OnInitButton()
{
	m_btModify.SetBackImage(IDB_BT_BACK, 0, 0, 0, _T("PNG"));
	m_btModify.SetButtonType(BT_PUSHBUTTON);
	m_btModify.SetParentBack(GetBackDC());
	m_btModify.SetSize(74, 26);
}
