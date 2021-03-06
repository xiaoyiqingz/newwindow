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
	m_pBackImgN = m_pBackImgH = m_pBackImgD = m_pBackImgF = NULL;
	m_pIconImg = NULL;
	m_pMenuImg = NULL;

	m_bFocus = m_bHover = m_bPress = m_bMouseTracking = FALSE;
	m_nBtnType = BT_PUSHBUTTON;

	m_hMenu = NULL;
	m_bResFromID = FALSE;
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
	RenderEngine->RemoveImage(m_pIconImg);
	RenderEngine->RemoveImage(m_pMenuImg);
	if (m_bResFromID) {
		RenderEngine->RemoveImage(m_pBackImgN, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pBackImgH, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pBackImgD, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pBackImgF, RESOURCE_ID);
	} else {
		RenderEngine->RemoveImage(m_pBackImgN);
		RenderEngine->RemoveImage(m_pBackImgH);
		RenderEngine->RemoveImage(m_pBackImgD);
		RenderEngine->RemoveImage(m_pBackImgF);
	}

	m_bFocus = m_bHover = m_bPress = m_bMouseTracking = FALSE;
	m_hMenu = NULL;
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
		

		if (m_nBtnType == BT_MENUBUTTON)
		{
			if (::IsMenu(m_hMenu))
			{
				CRect rc;
				GetClientRect(&rc);
				ClientToScreen(&rc);
				::TrackPopupMenuEx(m_hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,
					rc.left, rc.bottom, ::GetParent(GetSafeHwnd()), NULL);
			}
		}

		if (m_nBtnType == BT_SPLITBUTTON)
		{
			CRect rcClient, rcMenu;
			GetClientRect(&rcClient);
			rcMenu.left = rcClient.right - 16;
			rcMenu.top = rcClient.top;
			rcMenu.right = rcClient.right;
			rcMenu.bottom = rcClient.bottom;
			if (PtInRect(rcMenu, point)){
				if (::IsMenu(m_hMenu))
				{
					CRect rc;
					GetClientRect(&rc);
					ClientToScreen(&rc);
					::TrackPopupMenuEx(m_hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,
						rc.left, rc.bottom, ::GetParent(GetSafeHwnd()), NULL);
				}
			}
		}
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

BOOL CMyButtonEx::SetBackImage( UINT nResourceID, LPCTSTR lpszFileType)
{
	/*m_pBackImg.LoadFromResource(hInstance, nResourceID);
	ASSERT(m_pBackImg != NULL);*/
	m_bResFromID = TRUE;
	RenderEngine->RemoveImage(m_pBackImgN, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pBackImgH, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pBackImgD, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pBackImgF, RESOURCE_ID);

	m_pBackImgN = RenderEngine->GetImage(nResourceID, lpszFileType);
	m_pBackImgH = RenderEngine->GetImage(nResourceID, lpszFileType);
	m_pBackImgD = RenderEngine->GetImage(nResourceID, lpszFileType);
	m_pBackImgF = RenderEngine->GetImage(nResourceID, lpszFileType);

	if ((nResourceID > 0 && NULL == m_pBackImgN) || 
		(nResourceID > 0 && NULL == m_pBackImgH) ||
		(nResourceID > 0 && NULL == m_pBackImgD) ||
		(nResourceID > 0 && NULL == m_pBackImgF))
		return FALSE;
	else
		return TRUE;
}

BOOL CMyButtonEx::SetBackImage(LPCTSTR lpNormal, LPCTSTR lpHoven, LPCTSTR lpDown, LPCTSTR lpFocus, CONST LPRECT lprcNinePart /*=NULL*/)
{
	RenderEngine->RemoveImage(m_pBackImgN);
	RenderEngine->RemoveImage(m_pBackImgH);
	RenderEngine->RemoveImage(m_pBackImgD);
	RenderEngine->RemoveImage(m_pBackImgF);

	m_pBackImgN = RenderEngine->GetImage(lpNormal);
	m_pBackImgH = RenderEngine->GetImage(lpHoven);
	m_pBackImgD = RenderEngine->GetImage(lpDown);
	m_pBackImgF = RenderEngine->GetImage(lpFocus);

	if( lprcNinePart != NULL )
	{
		if (m_pBackImgN != NULL)
			m_pBackImgN->SetNinePart(lprcNinePart);

		if (m_pBackImgH != NULL)
			m_pBackImgH->SetNinePart(lprcNinePart);

		if (m_pBackImgD != NULL)
			m_pBackImgD->SetNinePart(lprcNinePart);

		if (m_pBackImgF != NULL)
			m_pBackImgF->SetNinePart(lprcNinePart);
	}

	if ((lpNormal != NULL && NULL == m_pBackImgN) || 
		(lpHoven  != NULL && NULL == m_pBackImgH) ||
		(lpDown   != NULL && NULL == m_pBackImgD) ||
		(lpFocus  != NULL && NULL == m_pBackImgF))
		return FALSE;
	else
		return TRUE;
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

bool CMyButtonEx::SetIconImage(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_pIconImg);
	
	m_pIconImg = RenderEngine->GetImage(lpszFileName);

	if (m_pIconImg == NULL) 
		return false;
	else 
		return true;

}

BOOL CMyButtonEx::SetMenuImage(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_pMenuImg);

	m_pMenuImg = RenderEngine->GetImage(lpszFileName);

	if (NULL == m_pMenuImg)
		return FALSE;
	else
		return TRUE;
}

void CMyButtonEx::SetSize(int nWidth, int nHeight)
{
	SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOMOVE);
}


void CMyButtonEx::SetMenu(HMENU hMenu)
{
	m_hMenu = hMenu;
}

LRESULT CMyButtonEx::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == BM_SETSTATE) {
		RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
			| RDW_ERASE | RDW_ERASENOW);
	}

	if ( message == BM_SETCHECK )
	{
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

	switch (m_nBtnType) {
		case BT_PUSHBUTTON:
			DrawPushButton(&memoryDC, rcClient);
			break;
		case BT_RADIOBUTTON:
		case BT_CHECKBUTTON:
			DrawCheckButton(&memoryDC, rcClient);
			break;
		case BT_ICONBUTTON:
			DrawIconButton(&memoryDC, rcClient);
			break;
		case BT_MENUBUTTON:
			DrawMenuButton(&memoryDC, rcClient);
			break;
		case BT_SPLITBUTTON:
			DrawSplitButton(&memoryDC, rcClient);
			break;
		ASSERT(FALSE);
	}	
}

void CMyButtonEx::DrawPushButton(CDC* pDC,RECT &rcClient)
{
	if (m_bPress)		// 鼠标左键按下状态
	{
		if (m_pBackImgD != NULL && !m_pBackImgD->IsNull())
			m_pBackImgD->DrawImage(pDC, rcClient);
	}
	else if (m_bHover)	// 鼠标悬停状态
	{
		if (m_pBackImgH != NULL && !m_pBackImgH->IsNull())
			m_pBackImgH->DrawImage(pDC, rcClient);
	}
	else if (m_bFocus)	// 焦点状态
	{
		if (m_pBackImgF != NULL && !m_pBackImgF->IsNull())
			m_pBackImgF->DrawImage(pDC, rcClient);
	}
	else				// 普通状态
	{
		if (m_pBackImgN != NULL && !m_pBackImgN->IsNull())
			m_pBackImgN->DrawImage(pDC, rcClient);
	}

	if (m_bPress)
		::OffsetRect(&rcClient,1, 1);

	CString strText;
	GetWindowText(strText);

	BOOL bHasText = FALSE;
	if (strText.GetLength() > 0)
		bHasText = TRUE;

	BOOL bHasIcon = FALSE;
	if (m_pIconImg != NULL && !m_pIconImg->IsNull())
		bHasIcon = TRUE;

	if (bHasIcon && bHasText)	// 带图标和文字
	{
		int cxIcon = m_pIconImg->GetWidth();
		int cyIcon = m_pIconImg->GetHeight();

		int nMode = pDC->SetBkMode(TRANSPARENT);

		CFont *pFont = GetFont();
		CFont *pOldFont = pDC->SelectObject(pFont);

		CRect rcText(0,0,0,0);	// 计算文字宽高
		pDC->DrawText(strText, &rcText, DT_SINGLELINE | DT_CALCRECT);

		int cx = cxIcon+3+rcText.Width();
		int cy = cyIcon;

		CRect rcCenter;
		CalcCenterRect(rcClient, cx, cy, rcCenter);

		CRect rcIcon(rcCenter.left, rcCenter.top, rcCenter.left+cxIcon, rcCenter.bottom);
		m_pIconImg->DrawImage(pDC, rcIcon);

		UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;
		rcText = CRect(rcIcon.right+3, rcClient.top, rcIcon.right+3+rcText.Width(), rcClient.bottom);
		pDC->DrawText(strText, &rcText, nFormat);

		pDC->SelectObject(pOldFont);
		pDC->SetBkMode(nMode);
	}
	else if (bHasIcon)	// 仅图标
	{
		int cxIcon = m_pIconImg->GetWidth();
		int cyIcon = m_pIconImg->GetHeight();

		CRect rcIcon;
		CalcCenterRect(rcClient, cxIcon, cyIcon, rcIcon);

		m_pIconImg->DrawImage(pDC, rcIcon);
	}
	else if (bHasText)	// 仅文字
	{
		UINT nFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

		int nMode = pDC->SetBkMode(TRANSPARENT);
		CFont *pFont = GetFont();
		CFont *pOldFont = pDC->SelectObject(pFont);
		pDC->DrawText(strText, &rcClient, nFormat);
		pDC->SelectObject(pOldFont);
		pDC->SetBkMode(nMode);
	}
	/*if (m_bPress) {
		m_pBackImg.Draw(pDC->GetSafeHdc(), rcClient, CRect(108, 0, 144, 31));  //3
	} else if (m_bFocus) {
		m_pBackImg.Draw(pDC->GetSafeHdc(), rcClient, CRect(36, 0, 72, 31));   //2
	} else if (m_bHover) {
		m_pBackImg.Draw(pDC->GetSafeHdc(), rcClient, CRect(72, 0, 108, 31));  //4
	} else {
		m_pBackImg.Draw(pDC->GetSafeHdc(), rcClient, CRect(36, 0, 72, 31));	  //2
	}*/
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

void CMyButtonEx::DrawIconButton(CDC* pDC,RECT &rcClient)
{
	if (m_bPress)
	{
		if (m_pBackImgD != NULL && !m_pBackImgD->IsNull())
			m_pBackImgD->Draw(pDC, rcClient);
	} else if (m_bHover) {
		if (m_pBackImgH != NULL && !m_pBackImgH->IsNull())
			m_pBackImgH->Draw(pDC, rcClient);
	}

	if (m_bPress)
		::OffsetRect(&rcClient,1, 1);

	CString strText;
	GetWindowText(strText);

	BOOL bHasText = FALSE;
	if (strText.GetLength() > 0)
		bHasText = TRUE;

	BOOL bHasIcon = FALSE;
	if (m_pIconImg != NULL && !m_pIconImg->IsNull())
		bHasIcon = TRUE;

	if (bHasIcon && bHasText)	// 带图标和文字
	{
		int cxIcon = m_pIconImg->GetWidth();
		int cyIcon = m_pIconImg->GetHeight();

		int nMode = pDC->SetBkMode(TRANSPARENT);
		CFont *pFont = GetFont();
		CFont *pOldFont = pDC->SelectObject(pFont);

		CRect rcText(0,0,0,0);	// 计算文字宽高
		pDC->DrawText(strText, &rcText, DT_SINGLELINE | DT_CALCRECT);

		int cx = cxIcon+3+rcText.Width();
		int cy = cyIcon;

		CRect rcCenter;
		CalcCenterRect(rcClient, cx, cy, rcCenter);

		CRect rcIcon(rcCenter.left, rcCenter.top, rcCenter.left+cxIcon, rcCenter.bottom);
		m_pIconImg->DrawImage(pDC, rcIcon);

		UINT nFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;
		rcText = CRect(rcIcon.right+3, rcClient.top, rcIcon.right+3+rcText.Width(), rcClient.bottom);
		pDC->DrawText(strText, &rcText, nFormat);

		pDC->SelectObject(pOldFont);
		pDC->SetBkMode(nMode);	
	}
	else if (bHasIcon)
	{
		int cxIcon = m_pIconImg->GetWidth();
		int cyIcon = m_pIconImg->GetHeight();

		CRect rcIcon;
		CalcCenterRect(rcClient, cxIcon, cyIcon, rcIcon);

		m_pIconImg->DrawImage(pDC, rcIcon);
	}
	else if (bHasText)
	{
		CRect rcText(rcClient);
		rcText.left += 2;
		rcText.right -= 2;

		UINT nFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

		int nMode = pDC->SetBkMode(TRANSPARENT);
		CFont *pFont = GetFont();
		CFont *pOldFont = pDC->SelectObject(pFont);
		pDC->DrawText(strText, &rcText, nFormat);
		pDC->SelectObject(pOldFont);
		pDC->SetBkMode(nMode);	
	}
}

void CMyButtonEx::DrawMenuButton(CDC* pDC,RECT &rcClient)
{
	if (m_bPress)
	{
		if (m_pBackImgD != NULL && !m_pBackImgD->IsNull())
			m_pBackImgD->DrawImage(pDC, rcClient);
	}
	else if (m_bHover)
	{
		if (m_pBackImgH != NULL && !m_pBackImgH->IsNull())
			m_pBackImgH->DrawImage(pDC, rcClient);
	}

	CRect rcMenu(0, 0, 0, 0);

	if (m_pMenuImg != NULL && !m_pMenuImg->IsNull())
	{
		int cx = m_pMenuImg->GetWidth();
		int cy = m_pMenuImg->GetHeight();
		int x = rcClient.right - 3 - cx;
		int y = (rcClient.bottom-rcClient.top - cy + 1) / 2;
		rcMenu = CRect(x, y, x+cx, y+cy);
		m_pMenuImg->DrawImage(pDC, rcMenu);
	}

	if (m_pIconImg != NULL && !m_pIconImg->IsNull())
	{
		int cx = m_pIconImg->GetWidth();
		int cy = m_pIconImg->GetHeight();

		int nRight;
		if (rcMenu.left > 0)
			nRight = rcMenu.left;
		else
			nRight = rcClient.right;

		CRect rcIcon(rcClient.left, rcClient.top, nRight, rcClient.bottom);
		CalcCenterRect(rcIcon, cx, cy, rcIcon);

		if (m_bPress)
			rcIcon.OffsetRect(1, 1);
		m_pIconImg->DrawImage(pDC, rcIcon);
	}
}

void CMyButtonEx::DrawSplitButton(CDC* pDC,RECT &rcClient)
{
	if (m_pBackImgN != NULL && !m_pBackImgN->IsNull()) {
		m_pBackImgN->DrawImage(pDC, rcClient);
	}

	CRect  rcMenu, rcIcon;
	if (m_pMenuImg != NULL && !m_pMenuImg->IsNull()) {
		int cx = m_pMenuImg->GetWidth();
		int cy = m_pMenuImg->GetHeight();

		int x = rcClient.right - 3 - cx;
		int y = (rcClient.bottom - rcClient.top - cy + 1) /2;
		rcMenu = CRect(x, y, x+cx, y+cy);
		m_pMenuImg->DrawImage(pDC, rcMenu);
	}

	if (m_pIconImg != NULL && !m_pIconImg->IsNull()) {
		int cx = m_pIconImg->GetWidth();
		int cy = m_pIconImg->GetHeight();

		int x = rcClient.left + 3;
		int y = (rcClient.bottom - rcClient.top - cy + 1)/2;
		if (m_bPress) {
			rcIcon = CRect(x+1, y+1, x+cx, y+cy);
		} else {
			rcIcon = CRect(x, y, x+cx, y+cy);
		}		
		m_pIconImg->DrawImage(pDC, rcIcon);
	}

	CString strText;
	GetWindowText(strText);
	
	BOOL  bHasText;
	if (strText.GetLength() > 0) 
		bHasText = TRUE;

	if (bHasText) {
		int  nMode = pDC->SetBkMode(TRANSPARENT);
		CFont *Font = GetFont();
		CFont *oldFont = pDC->SelectObject(Font);
		CRect rcText;
		if (m_bPress) {
			rcText = CRect(rcIcon.right + 3, rcClient.top + 3, rcMenu.left - 2, rcClient.bottom );
		} else {
			rcText = CRect(rcIcon.right + 2, rcClient.top + 2, rcMenu.left - 2, rcClient.bottom);
		}
		
//		pDC->DrawText(strText, rcText, DT_SINGLELINE | DT_CALCRECT);

		UINT nFormat = DT_LEFT | DT_END_ELLIPSIS | DT_VCENTER | DT_SINGLELINE;
		pDC->DrawText(strText, rcText, nFormat);
		pDC->SelectObject(oldFont);
		pDC->SetBkMode(nMode);
	}
}


LRESULT CMyButtonEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_PRINT || message == WM_PRINTCLIENT) {
/*

		CRect rcClient;
		GetClientRect(&rcClient);
		CDC dc;
		dc.Attach((HDC)wParam);
		CMemoryDC MemoryDc(&dc, rcClient);
		DrawParentWndBg(GetSafeHwnd(), MemoryDc->GetSafeHdc());

		DrawPushButton(&MemoryDc, rcClient);

		dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(),&MemoryDc, 0, 0, SRCCOPY);
		
		ReleaseDC(&dc);*/
	}

	return __super::WindowProc(message, wParam, lParam);
}
