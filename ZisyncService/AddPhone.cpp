// AddPhone.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "AddDevice.h"
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
	DDX_Control(pDX, IDC_BT_HELP, m_btHelp);
}


BEGIN_MESSAGE_MAP(CAddPhone, CMyDialog)
	ON_BN_CLICKED(IDC_BT_HELP, OnBnClickedBtHelp)
END_MESSAGE_MAP()


// CAddPhone message handlers


BOOL CAddPhone::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	m_ImageCode.LoadImage(AfxGetInstanceHandle(), IDB_CODE_PNG, _T("PNG"));

	m_btHelp.SetBackImage(IDB_HELP, 0, _T("PNG"));
	m_btHelp.SetButtonType(BT_PUSHBUTTON);
	m_btHelp.SetParentBack(GetBackDC());
	m_btHelp.SetSize(24, 24);

	return TRUE;	
}

void CAddPhone::DrawClientArea(CDC*pDC,int nWidth,int nHeight)
{
	CRect rcClient, rcCode;
	GetClientRect(&rcClient);
	
	int cx = m_ImageCode.GetWidth();
	int cy = m_ImageCode.GetHeight();

	CalcCenterRect(rcClient, cx, cy, rcCode);

	m_ImageCode.Draw(pDC, rcCode.left, rcCode.top+10, rcCode.Width(), rcCode.Height(), 0, 0, 0, 0);
}

void CAddPhone::OnBnClickedBtHelp()
{
	this->ShowWindow(SW_HIDE);
	((CAddDevice *)(GetParent()->GetParent()))->m_Page3.ShowWindow(SW_SHOW);
}
