// SetUpPage2.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "SetUpPage2.h"
#include "afxdialogex.h"


// CSetUpPage2 dialog

IMPLEMENT_DYNAMIC(CSetUpPage2, CZiDialog)

CSetUpPage2::CSetUpPage2(CWnd* pParent /*=NULL*/)
	: CZiDialog(CSetUpPage2::IDD, pParent)
{
	m_Radio = 0;
}

CSetUpPage2::~CSetUpPage2()
{
}

void CSetUpPage2::DoDataExchange(CDataExchange* pDX)
{
	CZiDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio);
	DDX_Control(pDX, IDC_ROUTER_PORT, m_etDisPort);
	DDX_Control(pDX, IDC_PUB_PORT, m_etPubPort);
}


BEGIN_MESSAGE_MAP(CSetUpPage2, CZiDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RADIO1, &CSetUpPage2::OnClickedRadio1)
	ON_COMMAND(IDC_RADIO4, &CSetUpPage2::OnRadio4)
END_MESSAGE_MAP()

// CSetUpPage2 message handlers

BOOL CSetUpPage2::OnInitDialog()
{
	CZiDialog::OnInitDialog();
	m_etDisPort.EnableWindow(FALSE);
	m_etPubPort.EnableWindow(FALSE);
	return TRUE;
}

HBRUSH CSetUpPage2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CZiDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	CFont font;
	if (pWnd->GetDlgCtrlID() == IDC_TITLE) {
		font.CreatePointFont(150, _T("ËÎÌו"));
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&font);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		return hBrush;
	}

	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		return hBrush;
	}

	return hbr;
}


void CSetUpPage2::OnClickedRadio1()
{
	m_Radio = 0;

	m_etDisPort.EnableWindow(FALSE);
	m_etPubPort.EnableWindow(FALSE);
}


void CSetUpPage2::OnRadio4()
{
	m_Radio = 1;

	m_etDisPort.EnableWindow(TRUE);
	m_etPubPort.EnableWindow(TRUE);
}

