// SetPage1.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "SetPage1.h"
#include "afxdialogex.h"


// CSetPage1 dialog

IMPLEMENT_DYNAMIC(CSetPage1, CZiDialog)

CSetPage1::CSetPage1(CWnd* pParent /*=NULL*/)
	: CZiDialog(CSetPage1::IDD, pParent)
{

}

CSetPage1::~CSetPage1()
{
}

void CSetPage1::DoDataExchange(CDataExchange* pDX)
{
	CZiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISCOVER_PORT, m_etDiscoverPort);
	DDX_Control(pDX, IDC_UPLOAD_SPEED, m_etUpSpeed);
	DDX_Control(pDX, IDC_DOWNLOAD_SPEED, m_etDownSpeed);
}


BEGIN_MESSAGE_MAP(CSetPage1, CZiDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RADIO1, &CSetPage1::OnClickedRadio1)
	ON_COMMAND(IDC_RADIO4, &CSetPage1::OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CSetPage1::OnClickedRadio5)
	ON_COMMAND(IDC_RADIO6, &CSetPage1::OnRadio6)
END_MESSAGE_MAP()


// CSetPage1 message handlers
BOOL CSetPage1::OnInitDialog()
{
	CZiDialog::OnInitDialog();
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO5))->SetCheck(TRUE);

	m_etUpSpeed.EnableWindow(FALSE);
	m_etDownSpeed.EnableWindow(FALSE);
	return TRUE;
}

BOOL CSetPage1::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
//	return CMyDialog::OnEraseBkgnd(pDC);
}


HBRUSH CSetPage1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CZiDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) {
		HBRUSH	hBrush = CreateSolidBrush(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		return hBrush;
	}
	return hbr;
}



void CSetPage1::OnClickedRadio1()
{
	m_etUpSpeed.EnableWindow(FALSE);
}


void CSetPage1::OnRadio4()
{
	m_etUpSpeed.EnableWindow(TRUE);
}


void CSetPage1::OnClickedRadio5()
{
	m_etDownSpeed.EnableWindow(FALSE);
}


void CSetPage1::OnRadio6()
{
	m_etDownSpeed.EnableWindow(TRUE);
}
