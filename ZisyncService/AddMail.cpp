// AddMail.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "AddMail.h"
#include "afxdialogex.h"

// CAddMail dialog

IMPLEMENT_DYNAMIC(CAddMail, CMyDialog)

CAddMail::CAddMail(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddMail::IDD, pParent)
{

}

CAddMail::~CAddMail()
{
}

void CAddMail::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BT_FILE, m_btFile);
	DDX_Control(pDX, IDC_BT_MAIL, m_btMail);
}


BEGIN_MESSAGE_MAP(CAddMail, CMyDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAddMail message handlers


BOOL CAddMail::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	OnInitButton();

	return TRUE; 
}

void CAddMail::OnInitButton()
{
	m_btFile.SetBackImage(IDB_HELP_NOR, IDB_HELP_SEL, _T("PNG"), CRect(2, 2, 2, 2));
	m_btFile.SetButtonType(BT_PUSHBUTTON);
	m_btFile.SetParentBack(GetBackDC());
	m_btFile.SetSize(80, 30);

	m_btMail.SetBackImage(IDB_HELP_NOR, IDB_HELP_SEL, _T("PNG"), CRect(2, 2, 2, 2));
	m_btMail.SetButtonType(BT_PUSHBUTTON);
	m_btMail.SetParentBack(GetBackDC());
	m_btMail.SetSize(80, 30);
}

HBRUSH CAddMail::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		return hBrush;
	}

	return hbr;
}
