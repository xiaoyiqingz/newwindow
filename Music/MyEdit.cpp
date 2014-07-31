// MyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "MyEdit.h"
#include "MemoryDC.h"
#include "RenderManager.h"

// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{
	m_pBackImgN = NULL;
	m_pBackImgH = NULL;
	m_pIconImg = NULL;

	m_bFocus = m_bPress = m_bHover = m_bMouseTracking = FALSE;
	m_nIconWidth = 0;
	m_bHandCursor = false;

	m_bIsDefText = FALSE;
	m_cPwdChar = 0;
	m_ptClient.SetPoint(0,0);
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONUP()
END_MESSAGE_MAP()

// CMyEdit message handlers
BOOL CMyEdit::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return 	CEdit::CreateEx(
		WS_EX_LEFT|WS_EX_LTRREADING|WS_EX_RIGHTSCROLLBAR|WS_EX_NOPARENTNOTIFY|WS_EX_CLIENTEDGE,
		TEXT("EDIT"),
		NULL,
		WS_VISIBLE|WS_CHILDWINDOW|WS_TABSTOP|ES_LEFT|ES_AUTOHSCROLL|dwStyle,
		rect,pParentWnd,nID);

	return CEdit::Create(dwStyle, rect, pParentWnd, nID);
}


LRESULT CMyEdit::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class

	return CEdit::DefWindowProc(message, wParam, lParam);
}


void CMyEdit::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	if (NULL != m_pIconImg && !m_pIconImg->IsNull())
	{
		if (bCalcValidRects)
		{
			lpncsp->rgrc[0].left += m_ptClient.x;
			lpncsp->rgrc[0].top += m_ptClient.y;
			lpncsp->rgrc[0].right -= m_nIconWidth;
			lpncsp->rgrc[1] = lpncsp->rgrc[0];
		}
	}

	CEdit::OnNcCalcSize(bCalcValidRects, lpncsp);
}


void CMyEdit::OnNcPaint()
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	CRect rcClient;
	GetClientRect(&rcClient);

	ClientToScreen(&rcClient);
	rcClient.OffsetRect(-rcWindow.left, -rcWindow.top);

	rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);

	CDC *pWindowDC = GetWindowDC();
	CMemoryDC MemDC(pWindowDC,rcWindow);

	CRect rcIcon;
	if (m_pIconImg != NULL && !m_pIconImg->IsNull())
	{
		int cxIcon = m_pIconImg->GetWidth();
		int cyIcon = m_pIconImg->GetHeight();

		CalcCenterRect(rcWindow, cxIcon, cyIcon, rcIcon);
		rcIcon.right = rcWindow.right - 2;
		rcIcon.left = rcIcon.right - cxIcon;
	}

	DrawParentWndBg(GetSafeHwnd(),MemDC.GetSafeHdc());

	if (m_bHover)
	{
		if (m_pBackImgH != NULL && !m_pBackImgH->IsNull())
		{
			m_pBackImgH->Draw(&MemDC, rcWindow);
		}
		else
		{
			if (m_pBackImgN != NULL && !m_pBackImgN->IsNull())
				m_pBackImgN->Draw(&MemDC, rcWindow);
		}
	}
	else
	{
		if (m_pBackImgN != NULL && !m_pBackImgN->IsNull())
			m_pBackImgN->Draw(&MemDC, rcWindow);
	}

	if (m_pIconImg != NULL && !m_pIconImg->IsNull())
		m_pIconImg->Draw(&MemDC, rcIcon);

	pWindowDC->BitBlt(rcWindow.left,rcWindow.top,rcWindow.Width(),rcWindow.Height(),&MemDC,0,0,SRCCOPY);

	ReleaseDC(pWindowDC);
}


BOOL CMyEdit::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
//	return CEdit::OnEraseBkgnd(pDC);
}


void CMyEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rcIcon;
	CPoint pt;
	GetCursorPos(&pt);
	GetIconRect(rcIcon);

	if( PtInRect(&rcIcon,pt)) return;

	m_bPress = TRUE;
	CEdit::OnLButtonDown(nFlags, point);
}


void CMyEdit::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rcIcon;
	CPoint pt;
	GetCursorPos(&pt);
	GetIconRect(rcIcon);

	if (PtInRect(rcIcon, pt)) {
		return;
	} else {
		if (m_bPress) {
			m_bPress = FALSE;
			RedrawWindow(NULL, NULL, RDW_FRAME | RDW_VALIDATE 
				| RDW_NOERASE | RDW_ERASE);
		}
	}

	CEdit::OnLButtonUp(nFlags, point);
}


void CMyEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseTracking)
	{
		TrackMouseLeave(GetSafeHwnd());

		m_bMouseTracking = TRUE;
		m_bHover = TRUE;
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}

	CEdit::OnMouseMove(nFlags, point);
}


LRESULT CMyEdit::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bMouseTracking = FALSE;
	m_bHover = FALSE;
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	return 1;
}


void CMyEdit::OnDestroy()
{
	CEdit::OnDestroy();

	// TODO: Add your message handler code here
	RenderEngine->RemoveImage(m_pBackImgN);
	RenderEngine->RemoveImage(m_pBackImgH);
	RenderEngine->RemoveImage(m_pIconImg);

	RemoveScorll();
}


void CMyEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);

	if (m_bIsDefText)
	{
		m_bIsDefText = FALSE;
		SetPasswordChar(m_cPwdChar);
		SetWindowText(_T(""));
	}

	m_bFocus = TRUE;
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}


void CMyEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	if (GetWindowTextLength() <= 0 && !m_strDefText.IsEmpty())
	{
		m_bIsDefText = TRUE;
		m_cPwdChar = GetPasswordChar();
		SetPasswordChar(0);
		SetWindowText(m_strDefText);
	}

	m_bFocus = FALSE;
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}


BOOL CMyEdit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CRect rcIcon;
	CPoint pt;
	GetCursorPos(&pt);
	GetIconRect(rcIcon);

	if( PtInRect(&rcIcon,pt))
	{
		if( m_bHandCursor )
			SetCursor(LoadCursor(NULL,IDC_HAND));
		else
			SetCursor(LoadCursor(NULL,IDC_ARROW));

		return TRUE;
	}

	return CEdit::OnSetCursor(pWnd, nHitTest, message);
}


void CMyEdit::GetIconRect(RECT &rcIcon)
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	CalcCenterRect(rcWindow, m_nIconWidth, rcWindow.Height(), rcIcon);
	rcIcon.right = rcWindow.right - 2;
	rcIcon.left = rcIcon.right - m_nIconWidth;
}

HBRUSH CMyEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (m_bIsDefText)
		pDC->SetTextColor(m_colDefText);
	else
		pDC->SetTextColor(m_colNormalText);

	return (HBRUSH)NULL_BRUSH;
}


LRESULT CMyEdit::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rcIcon;
	GetIconRect(rcIcon);

	if (PtInRect(&rcIcon, point)) {
		return HTBORDER;
	}

	return CEdit::OnNcHitTest(point);
}


void CMyEdit::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	CWnd *pWnd = GetParent();

	if ( pWnd != NULL && pWnd->GetSafeHwnd() != NULL )
	{
		CRect rcIcon;
		CPoint pt;
		GetCursorPos(&pt);
		GetIconRect(rcIcon);

		if( PtInRect(&rcIcon,pt)) 
			pWnd->PostMessage(WM_COMMAND,GetDlgCtrlID());
	}

	CEdit::OnNcLButtonUp(nHitTest, point);
}

BOOL CMyEdit::SetBackNormalImg(LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/)
{
	RenderEngine->RemoveImage(m_pBackImgN);
	m_pBackImgN = RenderEngine->GetImage(lpszFileName);

	if (m_pBackImgN != NULL)
		m_pBackImgN->SetNinePart(lpNinePart);

	return (m_pBackImgN != NULL) ? TRUE : FALSE;
}

BOOL CMyEdit::SetBackHotImg(LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/)
{
	RenderEngine->RemoveImage(m_pBackImgH);
	m_pBackImgH = RenderEngine->GetImage(lpszFileName);

	if (m_pBackImgH != NULL)
		m_pBackImgH->SetNinePart(lpNinePart);

	return (m_pBackImgH != NULL) ? TRUE : FALSE;
}

BOOL CMyEdit::SetIconImg(LPCTSTR lpszFileName, bool bHandCursor /*= false*/)
{
	RenderEngine->RemoveImage(m_pIconImg);
	m_pIconImg = RenderEngine->GetImage(lpszFileName);

	if (m_pIconImg != NULL) {
		m_nIconWidth = m_pIconImg->GetWidth();
	}
	m_bHandCursor = bHandCursor;

	return (m_pIconImg != NULL) ? TRUE : FALSE;
}

void CMyEdit::SetDefaultText(LPCTSTR lpszText)
{
	m_strDefText = lpszText;
}

void CMyEdit::SetDefaultTextMode(BOOL bIsDefText)
{
	if (bIsDefText == m_bIsDefText)
		return;

	m_bIsDefText = bIsDefText;
	if (m_bIsDefText)
	{
		m_cPwdChar = GetPasswordChar();
		SetPasswordChar(0);
		SetWindowText(m_strDefText);
	}
	else
	{
		SetPasswordChar(m_cPwdChar);
		SetWindowText(_T(""));
	}
}
