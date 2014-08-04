// MyTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "MyTabCtrl.h"
#include "MemoryDC.h"
#include "RenderManager.h"


// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CTabCtrlItem::CTabCtrlItem(void) 
{
	m_nID = 0;
	m_strText = _T("");
	m_nWidth = m_nHeight = 0;
	m_nLeftWidth = m_nRightWidth = 0;
	m_nPadding = 0;
	m_lpBgImgN = m_lpBgImgH = m_lpBgImgD = NULL;
	m_lpIconImg = m_lpSelIconImg = NULL;
}

CTabCtrlItem::~CTabCtrlItem(void) 
{
	RenderEngine->RemoveImage(m_lpBgImgD);
	RenderEngine->RemoveImage(m_lpBgImgH);
	RenderEngine->RemoveImage(m_lpBgImgN);
	RenderEngine->RemoveImage(m_lpIconImg);
	RenderEngine->RemoveImage(m_lpSelIconImg);
}

CMyTabCtrl::CMyTabCtrl()
{
	m_pImgBack = NULL;
	m_pItemImgHov = m_pItemImgNor = m_pItemImgSel = NULL;
	m_bMouseTracking = FALSE;
	m_nSelIndex = m_nHoverIndex = -1;
}

CMyTabCtrl::~CMyTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CMyTabCtrl message handlers




void CMyTabCtrl::SetLeftTop(int nLeft, int nTop)
{
	m_nLeft = nLeft;
	m_nTop = nTop;
}

void CMyTabCtrl::SetItemPadding(int nIndex, int nPadding)
{
	CTabCtrlItem* lpItem = GetItemByIndex(nIndex);

	if (lpItem != NULL) 
		lpItem->m_nPadding = nPadding;
}

CSize CMyTabCtrl::SetItemSize(CSize size)
{
	for (int i = 0; i < (int)m_ItemArray.size(); i++) {
		CTabCtrlItem *lpItem = m_ItemArray[i];
		lpItem->m_nWidth = size.cx;
		lpItem->m_nHeight = size.cy;

		lpItem->m_nLeftWidth = 0;
		lpItem->m_nRightWidth = 0;
	} 

	return __super::SetItemSize(size);
}

BOOL CMyTabCtrl::SetBackImage(LPCTSTR lpszFileName, CONST LPRECT lpNinePart/*=NULL*/)
{
	RenderEngine->RemoveImage(m_pImgBack);

	m_pImgBack = RenderEngine->GetImage(lpszFileName);

	if (m_pImgBack != NULL)
		m_pImgBack->SetNinePart(lpNinePart);

	if (m_pImgBack == NULL) 
		return FALSE;
	else
		return TRUE;
}

BOOL CMyTabCtrl::SetItemsImage(LPCTSTR lpNormal, LPCTSTR lpHighlight, LPCTSTR lpDown, CONST LPRECT lprcNinePart /*= NULL*/)
{
	RenderEngine->RemoveImage(m_pItemImgHov);
	RenderEngine->RemoveImage(m_pItemImgNor);
	RenderEngine->RemoveImage(m_pItemImgSel);

	m_pItemImgNor = RenderEngine->GetImage(lpNormal);
	m_pItemImgHov = RenderEngine->GetImage(lpHighlight);
	m_pItemImgSel = RenderEngine->GetImage(lpDown);

	if (m_pItemImgHov != NULL) {
		m_pItemImgHov->SetNinePart(lprcNinePart);
	}
	if (m_pItemImgNor != NULL) {
		m_pItemImgNor->SetNinePart(lprcNinePart);
	}
	if (m_pItemImgSel != NULL) {
		m_pItemImgSel->SetNinePart(lprcNinePart);
	}

	if ((lpNormal != NULL && m_pItemImgNor == NULL) ||
		(lpHighlight != NULL && m_pItemImgHov == NULL) ||
		(lpDown != NULL && m_pItemImgSel== NULL))
		return FALSE;
	else
		return TRUE;
}

BOOL CMyTabCtrl::SetIconImage(int nIndex, LPCTSTR lpIcon, LPCTSTR lpSelIcon)
{
	CTabCtrlItem *lpItem = GetItemByIndex(nIndex);
	if (lpItem == NULL) 
		return FALSE;

	RenderEngine->RemoveImage(lpItem->m_lpIconImg);
	RenderEngine->RemoveImage(lpItem->m_lpSelIconImg);

	lpItem->m_lpIconImg = RenderEngine->GetImage(lpIcon);
	lpItem->m_lpSelIconImg = RenderEngine->GetImage(lpSelIcon);

	if ((lpIcon != NULL && lpItem->m_lpIconImg == NULL) ||
		(lpSelIcon != NULL && lpItem->m_lpSelIconImg == NULL))
			return FALSE;
	else 
		return TRUE;	
}

void CMyTabCtrl::SetCurSel(int nCurSel)
{
	m_nSelIndex = nCurSel;
	Invalidate(FALSE);
}

int CMyTabCtrl::GetCurSel()
{
	return m_nSelIndex;
}

void CMyTabCtrl::SetItemText(int nIndex, LPCTSTR lpszText)
{
	CTabCtrlItem *lpItem = GetItemByIndex(nIndex);

	if (lpItem != NULL)
		lpItem->m_strText = lpszText;	
}

int CMyTabCtrl::AddItem(int nID)
{
	CTabCtrlItem * lpItem = new CTabCtrlItem;
	if (NULL == lpItem)
		return -1;
	lpItem->m_nID = nID;
	m_ItemArray.push_back(lpItem);

	__super::InsertItem(nID,TEXT(""));

	SetItemPadding(nID,10);

	return m_ItemArray.size() - 1;
}

BOOL CMyTabCtrl::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CMyTabCtrl::OnPaint()
{
	CPaintDC dc(this); 

	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC MemDC(&dc, rcClient);

	DrawParentWndBg(GetSafeHwnd(), MemDC.m_hDC);

	if (m_pImgBack != NULL && !m_pImgBack->IsNull()) {
		m_pImgBack->Draw(&MemDC, rcClient);
	}

	for (int i =0; i < (int)m_ItemArray.size(); i++) {
		DrawItem(&MemDC, i);
	}
}


void CMyTabCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	
	int nIndex = HitTest(point);
	if (nIndex != -1) {
		if (nIndex != m_nSelIndex) {
			m_nSelIndex = nIndex;
			Invalidate(FALSE);

			NMHDR nmhdr = {m_hWnd, GetDlgCtrlID(), TCN_SELCHANGE};
			::SendMessage(::GetParent(m_hWnd), WM_NOTIFY, GetDlgCtrlID(), (LPARAM)&nmhdr);
		}
	}
	__super::OnLButtonDown(nFlags, point);
}


void CMyTabCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseTracking) {
		TrackMouseLeave(GetSafeHwnd());
		m_bMouseTracking = TRUE;
	}

	int  nIndex;
	nIndex = HitTest(point);
	if (nIndex != m_nHoverIndex)
	{
		m_nHoverIndex = nIndex;
		Invalidate();
	}

	__super::OnMouseMove(nFlags, point);
}


LRESULT CMyTabCtrl::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bMouseTracking = FALSE;
	int nIndex = -1;
	if (nIndex !=m_nHoverIndex) {
		m_nHoverIndex = nIndex;
		Invalidate(FALSE);
	}
	return 0;
}

void CMyTabCtrl::OnDestroy()
{
	__super::OnDestroy();

	RenderEngine->RemoveImage(m_pImgBack);
	RenderEngine->RemoveImage(m_pItemImgHov);
	RenderEngine->RemoveImage(m_pItemImgNor);
	RenderEngine->RemoveImage(m_pItemImgSel);

	CTabCtrlItem *lpItem;
	for (int i = 0; i < (int)m_ItemArray.size(); i++) {
		lpItem = m_ItemArray[i];
		if (lpItem != NULL) 
			delete lpItem;
	}
	m_ItemArray.clear();

	m_nSelIndex = m_nHoverIndex = -1;
}


BOOL CMyTabCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return __super::PreTranslateMessage(pMsg);
}

void CMyTabCtrl::DrawItem(CDC *pDC, int nIndex)
{
	CTabCtrlItem * lpItem = GetItemByIndex(nIndex);
	if (lpItem == NULL) return;

	CRect rcItem;
	GetItemRectByIndex(nIndex, rcItem);

	if (m_nSelIndex == nIndex) {
		if (lpItem->m_lpBgImgD != NULL && !lpItem->m_lpBgImgD->IsNull())
			lpItem->m_lpBgImgD->Draw(pDC, rcItem);
		else if (m_pItemImgSel != NULL && !m_pItemImgSel->IsNull()) 
			m_pItemImgSel->Draw(pDC, rcItem);
	} else if (m_nHoverIndex == nIndex) {
		if (lpItem->m_lpBgImgH != NULL && !lpItem->m_lpBgImgH->IsNull())
			lpItem->m_lpBgImgH->Draw(pDC, rcItem);
		else if (m_pItemImgHov != NULL && !m_pItemImgHov->IsNull())
			m_pItemImgHov->Draw(pDC, rcItem);
	} else {
		if (lpItem->m_lpBgImgN != NULL && !lpItem->m_lpBgImgN->IsNull())
			lpItem->m_lpBgImgN->Draw(pDC, rcItem);
		else if (m_pItemImgNor != NULL && !m_pItemImgNor->IsNull())
			m_pItemImgNor->Draw(pDC, rcItem);
	}

	CMyImage * lpIconImage = NULL;

	if (m_nSelIndex == nIndex) 
		lpIconImage = lpItem->m_lpSelIconImg;
	else
		lpIconImage = lpItem->m_lpIconImg;

	BOOL bHasText = FALSE;
	if (lpItem->m_strText.GetLength() > 0) 
		bHasText = TRUE;

	BOOL bHasIcon = FALSE;
	if (lpIconImage !=NULL && !lpIconImage->IsNull())
		bHasIcon = TRUE;

	if (bHasText && bHasIcon) {
		int cxIcon = lpIconImage->GetWidth();
		int cyIcon = lpIconImage->GetHeight();

		int nMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(GetCtrlFont());
		pDC->SetTextColor(m_colNormalText);

		CRect rcText(0,0,0,0);
		pDC->DrawText(lpItem->m_strText, lpItem->m_strText.GetLength(), &rcText, DT_SINGLELINE | DT_CALCRECT);

		int cx = cxIcon+1+rcText.Width();
		int cy = cyIcon;

		CRect rcCenter;
		CalcCenterRect(rcItem, cx, cy, rcCenter);

		CRect rcIcon(rcCenter.left, rcCenter.top, rcCenter.left + cxIcon, rcCenter.bottom);
		lpIconImage->Draw(pDC, rcIcon);
		rcText = CRect(rcIcon.right+1, rcItem.top, rcIcon.right+1+rcText.Width(), rcItem.bottom);
		pDC->DrawText(lpItem->m_strText,lpItem->m_strText.GetLength(), &rcText, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_LEFT);

		pDC->SetBkMode(nMode);
	} else if (bHasIcon) {
		int cxIcon = lpIconImage->GetWidth();
		int cyIcon = lpIconImage->GetHeight();

		CRect rcIcon;
		CalcCenterRect(rcItem, cxIcon, cyIcon, rcIcon);
		lpIconImage->Draw(pDC, rcIcon);
	} else if (bHasText) {
		int nMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_colNormalText);
		pDC->SelectObject(GetCtrlFont());

		pDC->DrawText(lpItem->m_strText, lpItem->m_strText.GetLength() ,&rcItem, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_END_ELLIPSIS);
		pDC->SetBkMode(nMode);
	}

}

CTabCtrlItem * CMyTabCtrl::GetItemByIndex(int nIndex)
{
	if (nIndex >= 0 && nIndex < (int)m_ItemArray.size()) 
		return m_ItemArray[nIndex];
	else
		return NULL;
}

BOOL CMyTabCtrl::GetItemRectByIndex(int nIndex, CRect& rect)
{
	CTabCtrlItem *pItem;
	int nLeft = m_nLeft;
	int nTop = m_nTop;

	for (int i = 0; i < (int)m_ItemArray.size(); i++) {
		pItem = m_ItemArray[i];
		if (pItem != NULL) {
			if (nIndex == i) {
				rect = CRect(nLeft, nTop, nLeft + pItem->m_nWidth, nTop + pItem->m_nHeight);
				return TRUE;
			}
			nLeft += pItem->m_nWidth;
			nLeft += pItem->m_nPadding;
		}
	}

	return FALSE;
}

int CMyTabCtrl::HitTest(POINT pt)
{
	CTabCtrlItem *lpItem;
	int nLeft = m_nLeft, nTop = m_nTop;

	CRect rcItem;
	for (int i = 0 ; i < (int)m_ItemArray.size(); i++) {
		lpItem = m_ItemArray[i];
		if (lpItem != NULL) {
			rcItem = CRect(nLeft, nTop, nLeft + lpItem->m_nWidth, nTop + lpItem->m_nHeight);
			if (rcItem.PtInRect(pt)) 
				return i;
			nLeft += lpItem->m_nWidth;
			nLeft += lpItem->m_nPadding;
		}
	}

	return -1;
}
