// ZiButton.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "ZiButton.h"
#include "MemoryDC.h"
#include "RenderManager.h"

// CZiButton

IMPLEMENT_DYNAMIC(CZiButton, CButton)

CZiButton::CZiButton()
{
	m_pCheckImgH = m_pCheckImgN = m_pCheckImgTichH = m_pCheckImgTickN = NULL;
	m_pBackImgN = m_pBackImgH = m_pBackImgD = m_pBackImgF = NULL;
	m_pIconImg = NULL;
	m_pMenuImg = NULL;

	m_bFocus = m_bHover = m_bPress = m_bMouseTracking = FALSE;
	m_nBtnType = BT_PUSHBUTTON;

	m_hMenu = NULL;

	m_bBackFromID = FALSE;
	m_bIconFromID = FALSE;
	m_bMenuFromID = FALSE;
	m_bCheckFromID = FALSE;
}

CZiButton::~CZiButton()
{
}


BEGIN_MESSAGE_MAP(CZiButton, CButton)
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

// CZiButton message handlers

void CZiButton::OnDestroy()
{
	CButton::OnDestroy();
//	m_pBackImg.Destroy();
	
	if (m_bBackFromID) {
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

	if (m_bIconFromID) {
		RenderEngine->RemoveImage(m_pIconImg, RESOURCE_ID);
	} else {
		RenderEngine->RemoveImage(m_pIconImg);
	}

	if (m_bCheckFromID) {
		RenderEngine->RemoveImage(m_pCheckImgH, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pCheckImgN, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pCheckImgTichH, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pCheckImgTickN, RESOURCE_ID);
	} else {
		RenderEngine->RemoveImage(m_pCheckImgH);
		RenderEngine->RemoveImage(m_pCheckImgN);
		RenderEngine->RemoveImage(m_pCheckImgTichH);
		RenderEngine->RemoveImage(m_pCheckImgTickN);
	}

	if (m_bMenuFromID) {
		RenderEngine->RemoveImage(m_pMenuImg, RESOURCE_ID);
	} else {
		RenderEngine->RemoveImage(m_pMenuImg);
	}

	m_bFocus = m_bHover = m_bPress = m_bMouseTracking = FALSE;
	m_hMenu = NULL;
}

void CZiButton::SetButtonType(BUTTON_TYPE nBtnType)
{
	m_nBtnType = nBtnType;
}


void CZiButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bMouseTracking) {
		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = GetSafeHwnd();
		_TrackMouseEvent(&tme);

		if (m_nBtnType == BT_GIFBUTTON) {
			m_pBackImgN->m_bIsPause = TRUE;
		}

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


LRESULT CZiButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	// TODO: Add your message handler code here and/or call default
	m_bMouseTracking = FALSE;
	m_bHover = FALSE;
	m_bFocus = TRUE;
	
	if (m_nBtnType == BT_GIFBUTTON) {
		m_pBackImgN->m_bIsPause = FALSE;
	} 

	RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
		| RDW_ERASE | RDW_ERASENOW);

	return 0;
}


void CZiButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bPress = TRUE;
	RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
		| RDW_ERASE | RDW_ERASENOW);

	CButton::OnLButtonDown(nFlags, point);
}


void CZiButton::OnLButtonUp(UINT nFlags, CPoint point)
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


void CZiButton::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bPress = true;
	RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
		|RDW_ERASE | RDW_ERASENOW);

	CButton::OnLButtonDown(nFlags, point);
}


void CZiButton::OnSetFocus(CWnd* pOldWnd)
{
	CButton::OnSetFocus(pOldWnd);

	m_bFocus = TRUE;
	RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
		|RDW_ERASE | RDW_ERASENOW);	
}


void CZiButton::OnKillFocus(CWnd* pNewWnd)
{
	CButton::OnKillFocus(pNewWnd);
	m_bFocus = FALSE;
	RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE 
		|RDW_ERASE | RDW_ERASENOW);
}


BOOL CZiButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}

BOOL CZiButton::SetBackImage(UINT nResNorID, 
							   UINT nResHovID, 
							   UINT nResDownID, 
							   UINT nResFocID,
							   LPCTSTR lpszFileType, 
							   CONST LPRECT lprcNinePart)
{
	m_bBackFromID = TRUE;
	RenderEngine->RemoveImage(m_pBackImgN, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pBackImgH, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pBackImgD, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pBackImgF, RESOURCE_ID);
	
	//if nResNorID != 0, other ID = 0, other Img = m_pBakcImgN;
	//if nResNorID == 0, other ID = 0, other Img = NULL  
	if (nResNorID != 0) {
		m_pBackImgN = RenderEngine->GetImage(nResNorID, lpszFileType);
	
		if (nResHovID == 0) {
			m_pBackImgH = RenderEngine->GetImage(nResNorID, lpszFileType);
		} else {
			m_pBackImgH = RenderEngine->GetImage(nResHovID, lpszFileType);
		}

		if (nResDownID == 0) {
			m_pBackImgD = RenderEngine->GetImage(nResNorID, lpszFileType);
		} else {
			m_pBackImgD = RenderEngine->GetImage(nResDownID, lpszFileType);
		}

		if (nResFocID == 0) {
			m_pBackImgF = RenderEngine->GetImage(nResNorID, lpszFileType);
		} else {
			m_pBackImgF = RenderEngine->GetImage(nResFocID, lpszFileType);
		}
	
	} else {
		if (nResHovID != 0) 
			m_pBackImgH = RenderEngine->GetImage(nResHovID, lpszFileType);

		if (nResDownID != 0) 
			m_pBackImgD = RenderEngine->GetImage(nResDownID, lpszFileType);

		if (nResFocID != 0)
			m_pBackImgF = RenderEngine->GetImage(nResFocID, lpszFileType);
	}

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

	if ((nResNorID > 0 && NULL == m_pBackImgN) || 
		(nResHovID >= 0 && NULL == m_pBackImgH) ||
		(nResDownID >= 0 && NULL == m_pBackImgD) ||
		(nResFocID >= 0 && NULL == m_pBackImgF))
		return FALSE;
	else
		return TRUE;
}

BOOL CZiButton::SetBackImage(LPCTSTR lpNormal, 
							   LPCTSTR lpHoven, 
							   LPCTSTR lpDown, 
							   LPCTSTR lpFocus, 
							   CONST LPRECT lprcNinePart /*=NULL*/)
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

	if ((lpNormal != NULL && m_pBackImgN == NULL) || 
		(lpHoven  != NULL && m_pBackImgH == NULL) ||
		(lpDown   != NULL && m_pBackImgD == NULL) ||
		(lpFocus  != NULL && m_pBackImgF == NULL))
		return FALSE;
	else
		return TRUE;
}

BOOL CZiButton::SetCheckImage(UINT nResNorID, 
								UINT nResHovID, 
								UINT nResTickNorID, 
								UINT nResTickHovID, 
								LPCTSTR lpszFileType/* =NULL */)
{
	m_bCheckFromID = TRUE;

	RenderEngine->RemoveImage(m_pCheckImgN, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pCheckImgH, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pCheckImgTickN, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pCheckImgTichH, RESOURCE_ID);

	m_pCheckImgH = RenderEngine->GetImage(nResHovID, lpszFileType);
	m_pCheckImgN = RenderEngine->GetImage(nResNorID, lpszFileType);
	m_pCheckImgTichH = RenderEngine->GetImage(nResTickHovID, lpszFileType);
	m_pCheckImgTickN = RenderEngine->GetImage(nResTickNorID, lpszFileType);

	if (m_pCheckImgH == NULL || m_pCheckImgN == NULL 
		|| m_pCheckImgTichH == NULL || m_pCheckImgTickN == NULL)
		return FALSE;
	else
		return TRUE;
}

BOOL CZiButton::SetCheckImage(LPCTSTR lpNormal, 
								LPCTSTR lpHover, 
								LPCTSTR lpTickNormal, 
								LPCTSTR lpTickHover)
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
		|| m_pCheckImgTichH == NULL || m_pCheckImgTickN == NULL)
		return FALSE;
	else
		return TRUE;
}

BOOL CZiButton::SetIconImage(UINT nResIconID, LPCTSTR lpszFileType)
{
	m_bIconFromID = TRUE;

	RenderEngine->RemoveImage(m_pIconImg, RESOURCE_ID);

	m_pIconImg = RenderEngine->GetImage(nResIconID, lpszFileType);

	if (m_pIconImg == NULL) 
		return FALSE;
	else
		return TRUE;
}

BOOL CZiButton::SetIconImage(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_pIconImg);
	
	m_pIconImg = RenderEngine->GetImage(lpszFileName);

	if (m_pIconImg == NULL) 
		return FALSE;
	else 
		return TRUE;
}

BOOL CZiButton::SetMenuImage(UINT nResFromID, LPCTSTR lpszFileType)
{
	m_bMenuFromID = TRUE;

	RenderEngine->RemoveImage(m_pMenuImg);

	m_pMenuImg = RenderEngine->GetImage(nResFromID, lpszFileType);

	if (m_pMenuImg == NULL)
		return FALSE;
	else
		return TRUE;
}

BOOL CZiButton::SetMenuImage(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_pMenuImg);

	m_pMenuImg = RenderEngine->GetImage(lpszFileName);

	if (m_pMenuImg == NULL)
		return FALSE;
	else
		return TRUE;
}

void CZiButton::SetSize(int nWidth, int nHeight)
{
	SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOMOVE);
}


void CZiButton::SetMenu(HMENU hMenu)
{
	m_hMenu = hMenu;
}

LRESULT CZiButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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



void CZiButton::OnPaint()
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
		case BT_GIFBUTTON:
			DrawGIFButton(&memoryDC, rcClient);
			break;
		ASSERT(FALSE);
	}	
}

void CZiButton::DrawPushButton(CDC* pDC,RECT &rcClient)
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

void CZiButton::DrawCheckButton(CDC* pDC,RECT &rcClient)
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

void CZiButton::DrawIconButton(CDC* pDC,RECT &rcClient)
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

void CZiButton::DrawMenuButton(CDC* pDC,RECT &rcClient)
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

void CZiButton::DrawSplitButton(CDC* pDC,RECT &rcClient)
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

void CZiButton::DrawGIFButton(CDC* pDC,RECT &rcClient) 
{
	if (m_pBackImgN != NULL && !m_pBackImgN->IsNull()) {
		if (!m_pBackImgN->IsInitGIF()) {
			m_pBackImgN->DrawFrameGIF(GetSafeHwnd(), rcClient);
			//m_pBackImgN->Draw(pDC, rcClient);
		}
	}
}

LRESULT CZiButton::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
