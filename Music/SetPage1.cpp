// SetPage1.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "SetPage1.h"
#include "afxdialogex.h"


// CSetPage1 dialog

IMPLEMENT_DYNAMIC(CSetPage1, CMyDialog)

CSetPage1::CSetPage1(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSetPage1::IDD, pParent)
{

}

CSetPage1::~CSetPage1()
{
}

void CSetPage1::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISCOVER_PORT, m_etDiscoverPort);
}


BEGIN_MESSAGE_MAP(CSetPage1, CMyDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSetPage1 message handlers


BOOL CSetPage1::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
//	return CMyDialog::OnEraseBkgnd(pDC);
}


HBRUSH CSetPage1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) {
		HBRUSH	hBrush = CreateSolidBrush(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		return hBrush;
	}
	return hbr;
}
