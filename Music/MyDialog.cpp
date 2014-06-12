// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
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
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMyDialog message handlers


BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD dwStyle = GetStyle();
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE| WS_SYSMENU |WS_MINIMIZEBOX
		|WS_MAXIMIZEBOX|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	dwNewStyle&=dwStyle;
	SetWindowLong(m_hWnd,GWL_STYLE,dwNewStyle);

	DWORD dwExStyle = GetExStyle();
	DWORD dwNewExStyle = WS_EX_LEFT |WS_EX_LTRREADING |WS_EX_RIGHTSCROLLBAR;
	dwNewExStyle&=dwExStyle;
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwNewExStyle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

bool CMyDialog::LoadBackSkin(LPCTSTR pszResourcePath)
{
	return m_ImageBack.LoadImage(pszResourcePath);
}

bool CMyDialog::LoadBackSkin(HINSTANCE hInstance, LPCTSTR pszResourcePath)
{
	return m_ImageBack.LoadImage(hInstance, pszResourcePath);
}

bool CMyDialog::LoadBackSkin(HINSTANCE hInstance, UINT nIDResource)
{
	return m_ImageBack.LoadImage(hInstance, nIDResource);
}

void CMyDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rcClient;
	GetClientRect(&rcClient);

	if (!m_ImageBack.IsNull()) {
		m_ImageBack.DrawImage(&dc, 0, 0 ,rcClient.Width(), rcClient.Height());
	}
}
