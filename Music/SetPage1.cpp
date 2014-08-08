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
}


BEGIN_MESSAGE_MAP(CSetPage1, CMyDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CSetPage1 message handlers


BOOL CSetPage1::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
//	return CMyDialog::OnEraseBkgnd(pDC);
}
