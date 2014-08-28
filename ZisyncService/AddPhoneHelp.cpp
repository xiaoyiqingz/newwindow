// AddPhoneHelp.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "AddDevice.h"
#include "AddPhoneHelp.h"
#include "afxdialogex.h"


// CAddPhoneHelp dialog

IMPLEMENT_DYNAMIC(CAddPhoneHelp, CMyDialog)

CAddPhoneHelp::CAddPhoneHelp(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddPhoneHelp::IDD, pParent)
{

}

CAddPhoneHelp::~CAddPhoneHelp()
{
}

void CAddPhoneHelp::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BACK, m_btBack);
}


BEGIN_MESSAGE_MAP(CAddPhoneHelp, CMyDialog)
	ON_BN_CLICKED(IDC_BACK, OnBnClickBtBack)
END_MESSAGE_MAP()

// CAddPhoneHelp message handlers

BOOL CAddPhoneHelp::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	m_ImageBack.LoadImage(AfxGetInstanceHandle() ,IDB_PHONE_HELP, _T("PNG"));

	m_btBack.SetBackImage(IDB_HELP_NOR, IDB_HELP_SEL, IDB_HELP_SEL, 0, _T("PNG"));
	m_btBack.SetButtonType(BT_PUSHBUTTON);
	m_btBack.SetParentBack(GetBackDC());
	m_btBack.SetSize(70, 26);

	return TRUE;
}

void CAddPhoneHelp::DrawClientArea(CDC*pDC,int nWidth,int nHeight)
{
	int cx = m_ImageBack.GetWidth();
	int cy = m_ImageBack.GetHeight();
	m_ImageBack.Draw(pDC, 0, 0, nWidth, nHeight, 0, 0, 0, 0);
}

void CAddPhoneHelp::OnBnClickBtBack()
{
	this->ShowWindow(SW_HIDE);
	((CAddDevice *)(GetParent()->GetParent()))->m_Page1.ShowWindow(SW_SHOW);
}

