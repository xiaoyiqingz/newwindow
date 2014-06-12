// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "NewWindow.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// CMyDialog dialog

IMPLEMENT_DYNAMIC(CMyDialog, CDialog)

CMyDialog::CMyDialog(INT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{

}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
END_MESSAGE_MAP()


// CMyDialog message handlers


BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD dwStyle = GetStyle();
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU 
		|WS_MAXIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	dwNewStyle &= dwStyle;

	SetWindowLong(m_hWnd, GWL_STYLE, dwNewStyle);

	DWORD dwExStyle = GetExStyle();
	DWORD dwNewExStyle = WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR;
	dwNewExStyle&=dwExStyle;
	SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewExStyle);

	return TRUE;  

}
