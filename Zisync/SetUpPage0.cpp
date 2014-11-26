// SetUpPage0.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "SetUpPage0.h"
#include "afxdialogex.h"


// CSetUpPage0 dialog

IMPLEMENT_DYNAMIC(CSetUpPage0, CZiDialog)

CSetUpPage0::CSetUpPage0(CWnd* pParent /*=NULL*/)
	: CZiDialog(CSetUpPage0::IDD, pParent)
{

}

CSetUpPage0::~CSetUpPage0()
{
}

void CSetUpPage0::DoDataExchange(CDataExchange* pDX)
{
	CZiDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetUpPage0, CZiDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CSetUpPage0 message handlers


BOOL CSetUpPage0::OnInitDialog()
{
	CZiDialog::OnInitDialog();

	m_ImageLoge.LoadImage(AfxGetInstanceHandle(), IDB_LOGO, _T("PNG"));

	return TRUE;
}

void CSetUpPage0::DrawClientArea(CDC*pDC,int nWidth,int nHeight)
{
	int cx = m_ImageLoge.GetWidth();
	int cy = m_ImageLoge.GetHeight();
	m_ImageLoge.Draw(pDC, 50, 50, cx, cy, 0, 0, 0, 0);

	CFont Font;
	Font.CreatePointFont(130, _T("方正舒体"));
	int nMode = pDC->SetBkMode(TRANSPARENT);
	CFont *pOldFont = pDC->SelectObject(&Font);

	CRect rcLogo;
	pDC->DrawText(_T("自由同步  自在同步"), &rcLogo, DT_CALCRECT);

	int cxLogo = rcLogo.Width();
	int cyLogo = rcLogo.Height();
	rcLogo.left = 50 - (cxLogo - cx + 1)/2;
	rcLogo.right = rcLogo.left + cxLogo;
	rcLogo.top = 70 + cy + 10;
	rcLogo.bottom = rcLogo.top + cyLogo;
	pDC->DrawText(_T("自由同步  自在同步"), &rcLogo, DT_CENTER | DT_SINGLELINE);

	pDC->SetBkMode(nMode);
	pDC->SelectObject(pOldFont);
	Font.DeleteObject();

	Font.CreatePointFont(150, _T("宋体"));
	CRect rcTitle, rcClient(0, 0, nWidth, 40);
	nMode = pDC->SetBkMode(TRANSPARENT);
	pOldFont = pDC->SelectObject(&Font);
	pDC->DrawText(_T("登录自同步"), &rcTitle, DT_CALCRECT);
	CalcCenterRect(rcClient, rcTitle.Width(), rcTitle.Height(), rcTitle);
	pDC->DrawText(_T("登录自同步"), &rcTitle, DT_CENTER | DT_SINGLELINE);

	pDC->SetBkMode(nMode);
	pDC->SelectObject(pOldFont);
}


HBRUSH CSetUpPage0::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CZiDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		return	hBrush;
	}
	return hbr;
}
