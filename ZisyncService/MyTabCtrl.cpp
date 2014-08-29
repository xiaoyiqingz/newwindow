// MyTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "MyTabCtrl.h"
#include "MemoryDC.h"
#include "RenderManager.h"


// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CTabCtrlItem::CTabCtrlItem(void) 
{
	m_nID = 0;
	m_strText = _T("");
	m_nPadding = 0;
	m_nWidth = m_nHeight = 0;
	m_nLeftWidth = m_nRightWidth = 0;
	m_bIconFromID = FALSE;

	m_lpIconImg = m_lpSelIconImg = NULL;
	m_lpBgImgN = m_lpBgImgH = m_lpBgImgD = NULL;	
}

CTabCtrlItem::~CTabCtrlItem(void) 
{
	if (m_bIconFromID) {
		RenderEngine->RemoveImage(m_lpIconImg, RESOURCE_ID);
		RenderEngine->RemoveImage(m_lpSelIconImg, RESOURCE_ID);
	} else {
		RenderEngine->RemoveImage(m_lpIconImg);
		RenderEngine->RemoveImage(m_lpSelIconImg);
	}

	RenderEngine->RemoveImage(m_lpBgImgD);
	RenderEngine->RemoveImage(m_lpBgImgH);
	RenderEngine->RemoveImage(m_lpBgImgN);
	
}

CMyTabCtrl::CMyTabCtrl()
{
	m_pImgBack = NULL;
	m_pItemImgHov = m_pItemImgNor = m_pItemImgSel = NULL;
	m_bMouseTracking = FALSE;
	m_nSelIndex = m_nHoverIndex = -1;
	m_bMouseTracking = FALSE;
	m_nLeft = m_nTop = 0;
	m_rcTabRegion = CRect(0, 0, 0, 0);
	m_textPos = TEXT_RIGHT;

	m_bBackFromID = FALSE;
	m_bItemsFromID = FALSE;
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

BOOL CMyTabCtrl::SetBackImage(UINT nResFromID, LPCTSTR lpszFileType, CONST LPRECT lpNinePart)
{
	m_bBackFromID = TRUE;

	RenderEngine->RemoveImage(m_pImgBack);

	m_pImgBack = RenderEngine->GetImage(nResFromID, lpszFileType);

	if (m_pImgBack != NULL)
		m_pImgBack->SetNinePart(lpNinePart);

	if (m_pImgBack == NULL) 
		return FALSE;
	else
		return TRUE;
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

BOOL CMyTabCtrl::SetItemsImage(UINT nResNorID, 
							   UINT nResHovID, 
							   UINT nResDownID, 
							   LPCTSTR lpszFileType/* =NULL */, 
							   CONST LPRECT lprcNinePart/* =NULL */)
{
	m_bItemsFromID = TRUE;

	RenderEngine->RemoveImage(m_pItemImgHov, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pItemImgNor, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pItemImgSel, RESOURCE_ID);

	if (nResNorID != 0) {
		m_pItemImgNor = RenderEngine->GetImage(nResNorID, lpszFileType);
	}

	if (nResHovID != 0) {
		m_pItemImgHov = RenderEngine->GetImage(nResHovID, lpszFileType);
	}
	
	if (nResDownID != 0){
		m_pItemImgSel = RenderEngine->GetImage(nResDownID, lpszFileType);
	}	

	if (m_pItemImgHov != NULL) {
		m_pItemImgHov->SetNinePart(lprcNinePart);
	}
	if (m_pItemImgNor != NULL) {
		m_pItemImgNor->SetNinePart(lprcNinePart);
	}
	if (m_pItemImgSel != NULL) {
		m_pItemImgSel->SetNinePart(lprcNinePart);
	}

	if (m_pItemImgNor == NULL || m_pItemImgHov == NULL ||  m_pItemImgSel== NULL)
		return FALSE;
	else
		return TRUE;
}

BOOL CMyTabCtrl::SetItemsImage(LPCTSTR lpNormal, 
							   LPCTSTR lpHighlight, 
							   LPCTSTR lpDown, 
							   CONST LPRECT lprcNinePart /*= NULL*/)
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

BOOL CMyTabCtrl::SetIconImage(int nIndex, UINT nResNorID, UINT nResSelID, LPCTSTR lpszFileType)
{
	CTabCtrlItem *lpItem = GetItemByIndex(nIndex);
	if (lpItem == NULL) 
		return FALSE;

	lpItem->m_bIconFromID = TRUE;
	
	RenderEngine->RemoveImage(lpItem->m_lpIconImg, RESOURCE_ID);
	RenderEngine->RemoveImage(lpItem->m_lpSelIconImg, RESOURCE_ID);

	lpItem->m_lpIconImg = RenderEngine->GetImage(nResNorID, lpszFileType);
	if (nResSelID == 0) {
		lpItem->m_lpSelIconImg = RenderEngine->GetImage(nResNorID, lpszFileType);
	} else {
		lpItem->m_lpSelIconImg = RenderEngine->GetImage(nResSelID, lpszFileType);
	}
	

	if ((nResNorID > 0 && lpItem->m_lpIconImg == NULL) ||
		(nResSelID >=0 && lpItem->m_lpSelIconImg == NULL))
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

int CMyTabCtrl::GetCurSel()
{
	return m_nSelIndex;
}

void CMyTabCtrl::SetCurSel(int nCurSel)
{
	m_nSelIndex = nCurSel;
	Invalidate(FALSE);
}

int CMyTabCtrl::AddItem(int nID)
{
	CTabCtrlItem * lpItem = new CTabCtrlItem;
	if (NULL == lpItem)
		return -1;
	lpItem->m_nID = nID;
	m_ItemArray.push_back(lpItem);

	__super::InsertItem(nID,TEXT(""));

	return m_ItemArray.size() - 1;
}

CSize CMyTabCtrl::SetItemSize(CSize size,  CSize sizeRect)
{
	for (int i = 0; i < (int)m_ItemArray.size(); i++) {
		CTabCtrlItem *lpItem = m_ItemArray.at(i);
		lpItem->m_nWidth = size.cx;
		lpItem->m_nHeight = size.cy;
		lpItem->m_nLeftWidth = 0;
		lpItem->m_nRightWidth = 0;
	
		m_rcTabRegion.right += sizeRect.cx; //横向的tabctrl 刷新矩形的横坐标根据item增长，纵坐标不变
	} 
		m_rcTabRegion.bottom += sizeRect.cy;

 	return __super::SetItemSize(sizeRect);
}

void CMyTabCtrl::SetItemPadding(int nIndex, int nPadding)
{
	CTabCtrlItem* lpItem = GetItemByIndex(nIndex);

	if (lpItem != NULL) 
		lpItem->m_nPadding = nPadding;
}

void CMyTabCtrl::SetItemText(int nIndex, LPCTSTR lpszText)
{
	CTabCtrlItem *lpItem = GetItemByIndex(nIndex);

	if (lpItem != NULL)
		lpItem->m_strText = lpszText;	
}

void CMyTabCtrl::SetTextPos(TEXT_POS textPos)
{
	m_textPos = textPos;
}

BOOL CMyTabCtrl::GetItemRectByIndex(int nIndex, CRect& rect)
{
	CTabCtrlItem *lpItem;
	int nLeft = m_nLeft, nTop = m_nTop;

	for (int i = 0; i < (int)m_ItemArray.size(); i++)
	{
		lpItem = m_ItemArray[i];
		if (lpItem != NULL)
		{
			if (i == nIndex)
			{
				rect = CRect(nLeft, nTop, nLeft+lpItem->m_nWidth, nTop+lpItem->m_nHeight);
				return TRUE;
			}
			nLeft += lpItem->m_nWidth;
			nLeft += lpItem->m_nPadding;
		}
	}

	return FALSE;
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

	CMyImage * lpIconImg = NULL;

	BOOL bSelected = FALSE;
	if (m_nSelIndex == nIndex) {
		lpIconImg = lpItem->m_lpSelIconImg;
		bSelected = TRUE;
	} else {
		lpIconImg = lpItem->m_lpIconImg;
	}

	BOOL bHasText = FALSE;
	if (lpItem->m_strText.GetLength() > 0)
		bHasText = TRUE;

	BOOL bHasIcon = FALSE;
	if (lpIconImg != NULL && !lpIconImg->IsNull())
		bHasIcon = TRUE;

	if (bHasIcon && bHasText)
	{
		int cxIcon = lpIconImg->GetWidth();
		int cyIcon = lpIconImg->GetHeight();

		int nMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(GetCtrlFont());
		pDC->SetTextColor(m_colNormalText);
		UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

		CRect rcText(0,0,0,0);	
		pDC->DrawText(lpItem->m_strText, lpItem->m_strText.GetLength(), &rcText, DT_SINGLELINE | DT_CALCRECT);
		
		CRect rcCenter;
		if (m_textPos == TEXT_RIGHT) {
			int cx = cxIcon+1+rcText.Width();
			int cy = cyIcon;
			CalcCenterRect(rcItem, cx, cy, rcCenter);

			CRect rcIcon(rcCenter.left, rcCenter.top, rcCenter.left+cxIcon, rcCenter.bottom);
			lpIconImg->Draw(pDC, rcIcon);

			rcText = CRect(rcIcon.right+1, rcItem.top, rcIcon.right+1+rcText.Width(), rcItem.bottom);

		} else if (m_textPos == TEXT_BOTTOM) {
			int cx = cxIcon ;
			int cy = cyIcon;
			CalcCenterRect(rcItem, cx, cy, rcCenter);

			CRect rcIcon(rcCenter.left, rcCenter.top, rcCenter.left+cxIcon, rcCenter.top+cyIcon);
			lpIconImg->Draw(pDC, rcIcon);
			
			CalcCenterRect(rcItem, rcText.Width(), rcText.Height(), rcCenter);
			rcText = CRect(rcCenter.left, rcItem.bottom-rcText.Height(),rcCenter.left+rcText.Width(), rcItem.bottom);
		}
 
		if (bSelected) {
			pDC->SetTextColor(RGB(255,255,255));
		}
		pDC->DrawText(lpItem->m_strText, lpItem->m_strText.GetLength(), &rcText, nFormat);

		pDC->SetBkMode(nMode);
	}
	else if (bHasIcon)	
	{
		int cxIcon = lpIconImg->GetWidth();
		int cyIcon = lpIconImg->GetHeight();

		CRect rcIcon;
		CalcCenterRect(rcItem, cxIcon, cyIcon, rcIcon);

		lpIconImg->Draw(pDC, rcIcon);
	}
	else if (bHasText)	
	{
		UINT nFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

		int nMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_colNormalText);
		pDC->SelectObject(GetCtrlFont());
		if (bSelected) {
			pDC->SetTextColor(RGB(255,255,255));
		}
		pDC->DrawText(lpItem->m_strText, lpItem->m_strText.GetLength(), &rcItem, nFormat);
		pDC->SetBkMode(nMode);
	}
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

	DrawParentWndBg(GetSafeHwnd(),MemDC.m_hDC);

	if (m_pImgBack != NULL && !m_pImgBack->IsNull())
		m_pImgBack->Draw(&MemDC, rcClient);

	for (int i = 0; i < (int)m_ItemArray.size(); i++)
	{
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
			//Invalidate(FALSE);
			InvalidateRect(m_rcTabRegion, FALSE);

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
		//Invalidate(FALSE);
		InvalidateRect(m_rcTabRegion, FALSE);
	}

	__super::OnMouseMove(nFlags, point);
}


LRESULT CMyTabCtrl::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bMouseTracking = FALSE;
	int nIndex = -1;
	if (nIndex !=m_nHoverIndex) {
		m_nHoverIndex = nIndex;
		//Invalidate(FALSE);
		InvalidateRect(m_rcTabRegion, FALSE);
	}
	return 0;
}

void CMyTabCtrl::OnDestroy()
{
	__super::OnDestroy();

	if (m_bBackFromID) 
		RenderEngine->RemoveImage(m_pImgBack, RESOURCE_ID);
	else
		RenderEngine->RemoveImage(m_pImgBack);
	
	if (m_bItemsFromID) {
		RenderEngine->RemoveImage(m_pItemImgHov, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pItemImgNor, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pItemImgSel, RESOURCE_ID);
	} else {
		RenderEngine->RemoveImage(m_pItemImgHov);
		RenderEngine->RemoveImage(m_pItemImgNor);
		RenderEngine->RemoveImage(m_pItemImgSel);
	}
	
	CTabCtrlItem *lpItem;
	for (int i = 0; i < (int)m_ItemArray.size(); i++) {
		lpItem = m_ItemArray[i];
		if (lpItem != NULL) 
			delete lpItem;
	}
	m_ItemArray.clear();

	m_nSelIndex = m_nHoverIndex = -1;
	m_bMouseTracking = FALSE;
	m_nLeft = m_nTop = 0;
}


BOOL CMyTabCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return __super::PreTranslateMessage(pMsg);
}

CTabCtrlItem * CMyTabCtrl::GetItemByIndex(int nIndex)
{
	if (nIndex >= 0 && nIndex < (int)m_ItemArray.size()) 
		return m_ItemArray[nIndex];
	else
		return NULL;
}

int CMyTabCtrl::HitTest(POINT pt)
{
	CTabCtrlItem *lpItem;
	int nLeft = m_nLeft, nTop = m_nTop;
	CRect rcItem;

	for (int i = 0; i < (int)m_ItemArray.size(); i++)
	{
		lpItem = m_ItemArray[i];
		if (lpItem != NULL)
		{
			rcItem = CRect(nLeft, nTop, nLeft+lpItem->m_nWidth, nTop+lpItem->m_nHeight);
			if (rcItem.PtInRect(pt))
				return i;
			nLeft += lpItem->m_nWidth;
			nLeft += lpItem->m_nPadding;
		}
	}

	return -1;
}
