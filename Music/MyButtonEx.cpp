// MyButtonEx.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "MyButtonEx.h"
#include "MemoryDC.h"
#include "RenderManager.h"

// CMyButtonEx

IMPLEMENT_DYNAMIC(CMyButtonEx, CButton)

CMyButtonEx::CMyButtonEx()
{
	m_pCheckImgH = m_pCheckImgN = m_pCheckImgTichH = m_pCheckImgTickN = NULL;
	m_pIconImg = NULL;
	m_pMenuImg = NULL;

	m_bFocus = m_bHover = m_bPress = m_bMouseTracking = FALSE;
	m_nBtnType = BT_PUSHBUTTON;
}

CMyButtonEx::~CMyButtonEx()
{
}


BEGIN_MESSAGE_MAP(CMyButtonEx, CButton)
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CMyButtonEx message handlers
void CMyButtonEx::OnDestroy()
{
	CButton::OnDestroy();
	m_pBackImg.Destroy();
	RenderEngine->RemoveImage(m_pCheckImgH);
	RenderEngine->RemoveImage(m_pCheckImgN);
	RenderEngine->RemoveImage(m_pCheckImgTichH);
	RenderEngine->RemoveImage(m_pCheckImgTickN);

	m_pIconImg = NULL;
	m_pMenuImg = NULL;

	m_bFocus = m_bHover = m_bPress = m_bMouseTracking = FALSE;
}

void CMyButtonEx::SetButtonType(BUTTON_TYPE nBtnType)
{
	m_nBtnType = nBtnType;
}


void CMyButtonEx::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bMouseTracking) {
		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = GetSafeHwnd();
		_TrackMouseEvent(&tme);

		m_bMouseTracking = TRUE;
		m_bHover = TRUE;
		m_bFocus = FALSE;
		BOOL bResult;
		bResult = RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
			| RDW_ERASE | RDW_ERASENOW);
		ASSERT(bResult != FALSE);
	}

	CButton::OnMouseMove(nFlags, point);
}


LRESULT CMyButtonEx::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	// TODO: Add your message handler code here and/or call default
	m_bMouseTracking = FALSE;
	m_bHover = FALSE;
	m_bFocus = TRUE;
	RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
		| RDW_ERASE | RDW_ERASENOW);

	return 0;
}


void CMyButtonEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bPress = TRUE;
	RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
		| RDW_ERASE | RDW_ERASENOW);

	CButton::OnLButtonDown(nFlags, point);
}


void CMyButtonEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bPress) {
		m_bPress = FALSE;
		RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
			| RDW_ERASE | RDW_ERASENOW);
		
/*
		if(m_nBtnType == BT_MENUBUTTON) {

		}*/
	}
	CButton::OnLButtonUp(nFlags, point);
}


void CMyButtonEx::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bPress = true;
	RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
		|RDW_ERASE | RDW_ERASENOW);

	CButton::OnLButtonDown(nFlags, point);
}


void CMyButtonEx::OnSetFocus(CWnd* pOldWnd)
{
	CButton::OnSetFocus(pOldWnd);

	m_bFocus = TRUE;
	RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
		|RDW_ERASE | RDW_ERASENOW);	
}


void CMyButtonEx::OnKillFocus(CWnd* pNewWnd)
{
	CButton::OnKillFocus(pNewWnd);
	m_bFocus = FALSE;
	RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
		|RDW_ERASE | RDW_ERASENOW);
}


BOOL CMyButtonEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}

bool CMyButtonEx::SetBackImage(HINSTANCE hInstance, UINT nResourceID)
{
	m_pBackImg.LoadFromResource(hInstance, nResourceID);
	ASSERT(m_pBackImg != NULL);

	return true;
}

bool CMyButtonEx::SetCheckImage(LPCTSTR lpNormal, LPCTSTR lpHover, LPCTSTR lpTickNormal, LPCTSTR lpTickHover)
{
	RenderEngine->RemoveImage(m_pCheckImgH);
	RenderEngine->RemoveImage(m_pCheckImgN);
	RenderEngine->RemoveImage(m_pCheckImgTichH);
	RenderEngine->RemoveImage(m_pCheckImgTickN);

	m_pCheckImgH = RenderEngine->GetImage(lpHover);
	m_pCheckImgN = RenderEngine->GetImage(lpNormal);
	m_pCheckImgTichH = RenderEngine->GetImage(lpTickHover);
	m_pCheckImgTickN = RenderEngine->GetImage(lpTickNormal);

	if (m_pCheckImgH == NULL || m_pCheckImgN == NULL 
		|| m_pCheckImgTichH == NULL || m_pCheckImgTickN == NULL) {
			return false;
	} else {
		return true;
	}

}

void CMyButtonEx::SetSize(int nWidth, int nHeight)
{
	SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOMOVE);
}


LRESULT CMyButtonEx::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == BM_SETSTATE) {
		RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
			| RDW_ERASE | RDW_ERASENOW);
	}

	return CButton::DefWindowProc(message, wParam, lParam);
}



void CMyButtonEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC memoryDC(&dc, rcClient);
	DrawParentWndBg(GetSafeHwnd(), memoryDC->GetSafeHdc());

	if (m_nBtnType == BT_PUSHBUTTON) {
		DrawPushButton(&memoryDC, rcClient);
	} else if (m_nBtnType == BT_CHECKBUTTON) {
		DrawCheckButton(&memoryDC, rcClient);
	}
}

void CMyButtonEx::DrawPushButton(CDC* pDC,RECT &rcClient)
{
	if (m_bPress) {
		m_pBackImg.Draw(pDC->GetSafeHdc(), rcClient, CRect(108, 0, 144, 31));   //3
	} else if (m_bFocus) {
		m_pBackImg.Draw(pDC->GetSafeHdc(), rcClient, CRect(36, 0, 72, 31));   //2
	} else if (m_bHover) {
		m_pBackImg.Draw(pDC->GetSafeHdc(), rcClient, CRect(72, 0, 108, 31));  //4
	} else {
		m_pBackImg.Draw(pDC->GetSafeHdc(), rcClient, CRect(0, 0, 36, 31));	//1
	}
}

void CMyButtonEx::DrawCheckButton(CDC* pDC,RECT &rcClient)
{
	int nWidth = 15, nHeight = 15;
	if (m_pCheckImgN != NULL && !m_pCheckImgN->IsNull()) {
		nWidth = m_pCheckImgN->GetWidth();
		nHeight = m_pCheckImgN->GetHeight();
	}

	CRect rcCheck, rcText;
	rcCheck.left = rcClient.left;
	rcCheck.right = rcClient.left + nWidth;
	rcCheck.top = (rcClient.bottom - rcClient.top - nHeight) / 2 ;
	rcCheck.bottom = rcCheck.top + nHeight;

	rcText = rcClient;
	rcText.left = rcCheck.right + 5;

	BOOL bCheck = ((GetCheck() == BST_CHECKED) ? TRUE : FALSE);

	if (m_bHover) {
		if (bCheck) {
			if (m_pCheckImgTichH != NULL && !m_pCheckImgTichH->IsNull())
				m_pCheckImgTichH->DrawImage(pDC, rcCheck);
		} else {
			if (m_pCheckImgH != NULL && !m_pCheckImgH->IsNull())
				m_pCheckImgH->DrawImage(pDC, rcCheck);	
		}
	} else {
		if (bCheck) {
			if (m_pCheckImgTickN != NULL && !m_pCheckImgTickN->IsNull()) 
				m_pCheckImgTickN->DrawImage(pDC, rcCheck);
		} else {
			if (m_pCheckImgN != NULL && !m_pCheckImgN->IsNull())
				m_pCheckImgN->DrawImage(pDC, rcCheck);
		}
	}

	CString strText;
	GetWindowText(strText);

	if (strText.GetLength() > 0) {
		UINT nFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;

		int Mode = pDC->SetBkMode(TRANSPARENT);
//		CFont* pFont = GetFont();
		CFont* pFont = CFont::FromHandle(GetCtrlFont());
		CFont* pOldFont = pDC->SelectObject(pFont);
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->DrawText(strText, rcText, nFormat);
		pDC->SelectObject(pOldFont);
		pDC->SetBkMode(Mode);
	}
}
