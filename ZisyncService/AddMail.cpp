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
	DDX_Control(pDX, IDC_BUTTON1, m_btGif);
}


BEGIN_MESSAGE_MAP(CAddMail, CMyDialog)
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
	m_btGif.SetBackImage(_T("res\\gif.gif"), _T("res\\gif.gif"), _T("res\\gif.gif"),_T("res\\gif.gif"));
	m_btGif.SetButtonType(BT_PUSHBUTTON);
	m_btGif.SetParentBack(GetBackDC());
	m_btGif.SetSize(80,80);
}
