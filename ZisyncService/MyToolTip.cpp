// MyToolTip.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "MyToolTip.h"
#include "MemoryDC.h"
#include "RenderManager.h"


// CMyToolTip

IMPLEMENT_DYNAMIC(CMyToolTip, CToolTipCtrl)

CMyToolTip::CMyToolTip()
{
	m_pBackImg = NULL;
	m_colorText = RGB(0, 0, 0);

	m_bResFromID = FALSE;
}

CMyToolTip::~CMyToolTip()
{
}


BEGIN_MESSAGE_MAP(CMyToolTip, CToolTipCtrl)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CMyToolTip message handlers




void CMyToolTip::OnPaint()
{
	CPaintDC dc(this); 
	CRect	rcClient;
	GetClientRect(&rcClient);
	
	CMemoryDC  MemoryDC(&dc, rcClient);
	DrawParentWndBg(GetSafeHwnd(), MemoryDC->GetSafeHdc());
	
	DrawItem(&MemoryDC, rcClient);
}


void CMyToolTip::OnDestroy()
{
	CToolTipCtrl::OnDestroy();

	if (m_bResFromID)
		RenderEngine->RemoveImage(m_pBackImg, RESOURCE_ID);
	else 
		RenderEngine->RemoveImage(m_pBackImg);
}

BOOL CMyToolTip::SetBackImg(UINT nResFromID, LPCTSTR lpszFileType/* =NULL */, CONST	LPRECT lpNinePart)
{
	m_bResFromID = TRUE;
	
	RenderEngine->RemoveImage(m_pBackImg, RESOURCE_ID);

	m_pBackImg = RenderEngine->GetImage(nResFromID, lpszFileType);

	if (m_pBackImg != NULL) {
		m_pBackImg->SetNinePart(lpNinePart);
	}

	if (m_pBackImg == NULL || m_pBackImg->IsNull()) 
		return FALSE;
	else
		return TRUE;
}

BOOL CMyToolTip::SetBackImg(LPCTSTR lpszBack, CONST LPRECT lpNinePart /*= NULL*/)
{
	RenderEngine->RemoveImage(m_pBackImg);

	m_pBackImg = RenderEngine->GetImage(lpszBack);
	
	if (m_pBackImg != NULL) {
		m_pBackImg->SetNinePart(lpNinePart);
	}

	if (m_pBackImg == NULL || m_pBackImg->IsNull()) 
		return FALSE;
	else
		return TRUE;
}

void CMyToolTip::SetTextCol(COLORREF colorText)
{
	m_colorText = colorText;
}

void CMyToolTip::DrawItem(CDC *pDc, RECT & rcClient)
{
	/*if (m_pBackImg != NULL && !m_pBackImg->IsNull()) {
		m_pBackImg->Draw(pDc, rcClient);
	}*/
	
	CBrush Brush;
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = RGB(125, 125, 125);
	CPen   Pen(PS_SOLID | PS_GEOMETRIC | PS_JOIN_ROUND, 1, &logBrush);
	Brush.CreateSolidBrush(RGB(255, 255, 204));
	CPen *pOldPen = pDc->SelectObject(&Pen);
	CBrush * pOldBrush = pDc->SelectObject(&Brush);
	pDc->Rectangle(&rcClient);
	pDc->SelectObject(pOldBrush);
	pDc->SelectObject(pOldPen);


	CString strText;
	TCHAR	szText[256];
	GetWindowText(szText, sizeof(szText)/sizeof(TCHAR));
	if (_tcslen(szText) > 0) {
		int nMode = pDc->SetBkMode(TRANSPARENT);
		CFont *pFont = GetFont();
		CFont *pOldFont = pDc->SelectObject(pFont);
		pDc->SetTextColor(m_colorText);
		int nFormat = DT_SINGLELINE | DT_END_ELLIPSIS | DT_CENTER | DT_VCENTER;

		pDc->DrawText(szText, _tcsclen(szText), &rcClient, nFormat);

		pDc->SelectObject(pOldFont);
	}
}
