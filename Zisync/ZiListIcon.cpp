// ZiListIcon.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "MemoryDC.h"
#include "ZiListIcon.h"
#include "RenderManager.h"

// CZiListIcon

IMPLEMENT_DYNAMIC(CZiListIcon, CListCtrl)

CZiListIcon::CZiListIcon()
{
	m_xPadding = 5;
	m_yPadding = 5;
	m_nHoverIndex = -1;
	m_bMouseTracking = FALSE;
	
	m_bResFromID = FALSE;
}

CZiListIcon::~CZiListIcon()
{
}


BEGIN_MESSAGE_MAP(CZiListIcon, CListCtrl)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

// CZiListIcon message handlers

void CZiListIcon::PreSubclassWindow()
{
	m_ImageList1.Create(55, 55,ILC_MASK|ILC_COLOR32, 0, 0);
	m_ImageList1.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	SetImageList(&m_ImageList1, LVSIL_NORMAL);

	__super::PreSubclassWindow();
}

void CZiListIcon::OnDestroy()
{
	__super::OnDestroy();

	CItemArray::iterator iter = m_ItemImgArray.begin();
	for (; iter != m_ItemImgArray.end(); ++iter) {
		if (m_bResFromID) {
			RenderEngine->RemoveImage(iter->m_pImgBack, RESOURCE_ID);
			RenderEngine->RemoveImage(iter->m_pImgIcon, RESOURCE_ID);
			RenderEngine->RemoveImage(iter->m_pImgIconSel, RESOURCE_ID);
		} else {
			RenderEngine->RemoveImage(iter->m_pImgBack);
			RenderEngine->RemoveImage(iter->m_pImgIcon);
			RenderEngine->RemoveImage(iter->m_pImgIconSel);
		}		
	}
	m_ItemImgArray.clear();
	
	m_bMouseTracking = FALSE;
	m_nHoverIndex = -1;

	RemoveScorll();
}

BOOL CZiListIcon::SetItemImage(int nItem, 
							   UINT nResBackID, 
							   UINT nResIconNorID, 
							   UINT nResIconSelID, 
							   LPCTSTR lpszFileType)
{
	m_bResFromID = TRUE;

	CItemArray::iterator iter = m_ItemImgArray.begin();
	for (; iter != m_ItemImgArray.end(); iter++) {
		if (iter->nItem == nItem) {
			if (iter->m_pImgBack != NULL) {
				RenderEngine->RemoveImage(iter->m_pImgBack, RESOURCE_ID);
				iter->m_pImgBack = RenderEngine->GetImage(nResBackID, lpszFileType);
			}

			if (iter->m_pImgIcon != NULL) {
				RenderEngine->RemoveImage(iter->m_pImgIcon, RESOURCE_ID);
				iter->m_pImgIcon = RenderEngine->GetImage(nResIconNorID, lpszFileType);
			}

			if (iter->m_pImgIconSel!= NULL) {
				RenderEngine->RemoveImage(iter->m_pImgIconSel, RESOURCE_ID);
				if (nResIconSelID == 0) {
					iter->m_pImgIconSel = RenderEngine->GetImage(nResIconNorID, lpszFileType);
				} else {
					iter->m_pImgIconSel = RenderEngine->GetImage(nResIconSelID, lpszFileType);
				}
				
			}
			return TRUE;
		}
	}

	tagItem ItemNode;
	ItemNode.nItem = nItem;
	ItemNode.bIsSelected = false;
	ItemNode.bIsHoveing = false;
	ItemNode.m_pImgBack = RenderEngine->GetImage(nResBackID, lpszFileType);
	ItemNode.m_pImgIcon = RenderEngine->GetImage(nResIconNorID, lpszFileType);
	if (nResIconSelID == 0) {
		ItemNode.m_pImgIconSel = RenderEngine->GetImage(nResIconNorID, lpszFileType);
	} else {
		ItemNode.m_pImgIconSel = RenderEngine->GetImage(nResIconSelID, lpszFileType);
	}
	

	if (ItemNode.m_pImgBack == NULL ||ItemNode.m_pImgIcon == NULL || 
		ItemNode.m_pImgIconSel == NULL) 
		return FALSE;
	else {
		m_ItemImgArray.push_back(ItemNode);
		__super::InsertItem(nItem, _T(""), 0);
		return TRUE;
	}
}

BOOL CZiListIcon::SetItemImage(int nItem, LPCTSTR lpBackImg, LPCTSTR lpIcon, LPCTSTR lpIconSel)
{
	CItemArray::iterator iter = m_ItemImgArray.begin();
	for (; iter != m_ItemImgArray.end(); iter++) {
		if (iter->nItem == nItem) {
			if (iter->m_pImgBack != NULL) {
				RenderEngine->RemoveImage(iter->m_pImgBack);
				iter->m_pImgBack = RenderEngine->GetImage(lpBackImg);
			}

			if (iter->m_pImgIcon != NULL) {
				RenderEngine->RemoveImage(iter->m_pImgIcon);
				iter->m_pImgIcon = RenderEngine->GetImage(lpIcon);
			}

			if (iter->m_pImgIconSel!= NULL) {
				RenderEngine->RemoveImage(iter->m_pImgIconSel);
				iter->m_pImgIconSel = RenderEngine->GetImage(lpIconSel);
			}
			return TRUE;
		}
	}

	tagItem ItemNode;
	ItemNode.nItem = nItem;
	ItemNode.bIsSelected = false;
	ItemNode.bIsHoveing = false;
	ItemNode.m_pImgBack = RenderEngine->GetImage(lpBackImg);
	ItemNode.m_pImgIcon = RenderEngine->GetImage(lpIcon);
	ItemNode.m_pImgIconSel = RenderEngine->GetImage(lpIconSel);

	if (NULL == ItemNode.m_pImgBack || NULL == ItemNode.m_pImgIcon || 
		NULL == ItemNode.m_pImgIconSel) 
		return FALSE;
	else {
		m_ItemImgArray.push_back(ItemNode);
		__super::InsertItem(nItem, _T(""), 0);
		return TRUE;
	}
}


void CZiListIcon::OnPaint()
{
	CPaintDC dc(this); 
	
	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC memoryDC(&dc, rcClient);
	DrawParentWndBg(GetSafeHwnd(), memoryDC->GetSafeHdc());
	CRect	rcItem;
	
	for (int i = 0; i < (int)m_ItemImgArray.size(); i++) {
		GetSubItemRect(i, 0, LVIR_BOUNDS, rcItem);
		DrawIconItem(&memoryDC, rcItem, i);
	}
}

void CZiListIcon::DrawIconItem(CDC *pDC, CRect & rcItem, int nItem)
{
	CItemArray::iterator iter = m_ItemImgArray.begin();
	for(; iter != m_ItemImgArray.end(); iter++) {
		if (iter->nItem == nItem) {
			BOOL  bIsSelected = FALSE;
			if (iter->bIsSelected == true) 
				bIsSelected = TRUE;
			BOOL bIsHovering = FALSE;
			if (iter->bIsHoveing == true)
				bIsHovering = TRUE;

			int cx = iter->m_pImgBack->GetWidth();
			int cy = iter->m_pImgBack->GetWidth();
			int cxIcon = iter->m_pImgIcon->GetWidth();
			int cyIcon = iter->m_pImgIcon->GetHeight();

			CRect rcBack, rcIcon;
			rcBack.left = (rcItem.Width() - cx + 1) /2 + rcItem.left;
			rcBack.top = rcItem.top + 3;
			rcBack.right = rcBack.left + cx;
			rcBack.bottom = rcBack.top + cy;
			iter->m_pImgBack->Draw(pDC, rcBack);

			rcIcon.left = rcBack.right - cxIcon/2;
			rcIcon.right = rcIcon.left + cxIcon;
			rcIcon.top = rcBack.bottom - cyIcon/2;
			rcIcon.bottom = rcIcon.top + cyIcon;
			if (bIsSelected) 
				iter->m_pImgIconSel->Draw(pDC, rcIcon);
			else 
				iter->m_pImgIcon->Draw(pDC, rcIcon);

			CRect rcText(0,0,0,0);
			int nMode = pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(GetCtrlFont());
			pDC->SetTextColor(m_colNormalText);	
			pDC->DrawText(iter->strText, iter->strText.GetLength(), &rcText, DT_SINGLELINE | DT_CALCRECT);
			
			UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;
			if (bIsHovering) {
				pDC->SetTextColor(RGB(0, 127, 248));
			} else {
				pDC->SetTextColor(RGB(0, 0, 0));
			}
			if (rcText.Width() > rcItem.Width()) {
				rcText.top = rcIcon.bottom + 2;
				rcText.left = rcItem.left;
				rcText.bottom = rcItem.bottom;
				rcText.right = rcItem.right;
				pDC->DrawText(iter->strText, iter->strText.GetLength(), &rcText, nFormat);
			} else {
				rcText.top = rcIcon.bottom + 2;
				rcText.left = rcItem.left + (rcItem.Width() - rcText.Width() + 1) / 2;
				rcText.bottom = rcItem.bottom;
				rcText.right = rcItem.right;
				pDC->DrawText(iter->strText, iter->strText.GetLength(), &rcText, nFormat);
			}
			pDC->SetBkMode(nMode);
			break;
		}
						
	}	
}

int CZiListIcon::GetItemLeftPadding()
{	
	int itemWidth = GetItemCountH() * (m_xPadding + m_ItemSize.cx) -m_xPadding;
	CRect rcClient;
	GetClientRect(&rcClient);
	return (rcClient.Width() - itemWidth)/2;
}

BOOL CZiListIcon::SetItemText(int nItem, CString strText)
{
	CItemArray::iterator iter = m_ItemImgArray.begin();
	for (; iter != m_ItemImgArray.end(); iter++) {
		if (iter->nItem == nItem) {
			iter->strText = strText;
			__super::SetItemText(nItem, 0, strText);
			return TRUE;
		}
	}
	return FALSE;
}


BOOL CZiListIcon::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
//	return __super::OnEraseBkgnd(pDC);
}


void CZiListIcon::OnLButtonDown(UINT nFlags, CPoint point)
{
	int nIndex = HitTest(point);
	if (nIndex != -1) {
		m_ItemImgArray[nIndex].bIsSelected = !m_ItemImgArray[nIndex].bIsSelected;
		Invalidate(FALSE);
	}
	__super::OnLButtonDown(nFlags, point);
}

void CZiListIcon::SetItemSize(CSize size)
{
	m_ItemSize = size;
	CRect rcWorkAreas, rcClient;
	GetClientRect(&rcClient);
	
	rcWorkAreas.left = 0;
	rcWorkAreas.top = 0;
	rcWorkAreas.right = rcClient.right;
	rcWorkAreas.bottom = rcWorkAreas.top + ((int)m_ItemImgArray.size()/GetItemCountH() * (m_ItemSize.cy + m_yPadding) + m_ItemSize.cy);
}

int CZiListIcon::HitTest(POINT point)
{
	for (int i = 0; i < (int)m_ItemImgArray.size(); i++) {
		CRect rcItem;
		GetSubItemRect(i, 0, LVIR_BOUNDS, rcItem);
		if (PtInRect(&rcItem, point)) {
			return i;
		}
	}
	return -1;
/*
	CRect rcArea, rcClient;
	GetClientRect(&rcClient);
	rcArea.left = rcClient.left + GetItemLeftPadding();
	rcArea.right = rcClient.right - GetItemLeftPadding();
	rcArea.top = 0;
	rcArea.bottom = rcArea.top + ((int)m_ItemImgArray.size()/GetItemCountH() * (m_ItemSize.cy + m_yPadding) + m_ItemSize.cy); 

	if (rcClient.PtInRect(point)) {
		int cx = point.x / (m_ItemSize.cx + m_xPadding);
		int cy = point.y / (m_ItemSize.cy + m_yPadding);
		if ((point.x - cx * (m_ItemSize.cx + m_xPadding) <= m_ItemSize.cx) &&
			(point.y - cy * (m_ItemSize.cy + m_yPadding) <= m_ItemSize.cy)) 
		{
			return cx  + cy * GetItemCountH();
		} 
	}*/
}

BOOL CZiListIcon::GetChecked(int nItem)
{
	if (m_ItemImgArray[nItem].bIsSelected == true) 
		return TRUE;
	else 
		return FALSE;
}


void CZiListIcon::SetPadding(int cx, int cy)
{
	m_xPadding = cx;
	m_yPadding = cy;
}


int CZiListIcon::GetItemCountH()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	return ((rcClient.Width() - m_ItemSize.cx) / (m_ItemSize.cx + m_xPadding)) + 1;
}

int CZiListIcon::GetItemCount()
{
	return (int)m_ItemImgArray.size();
}


void CZiListIcon::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseTracking) {
		TrackMouseLeave(GetSafeHwnd());
		m_bMouseTracking = TRUE;
	}
	
	int nIndex = HitTest(point);
	if ( nIndex != -1 || m_nHoverIndex != -1) {
		if (m_nHoverIndex == -1) {
			m_nHoverIndex = nIndex;
		} else if (m_nHoverIndex != nIndex) {
			m_ItemImgArray[m_nHoverIndex].bIsHoveing = false;
			m_nHoverIndex = nIndex;
		}

		if (m_nHoverIndex != -1) {
			m_ItemImgArray[m_nHoverIndex].bIsHoveing = true;
		}
		Invalidate(FALSE);
	} 

	__super::OnMouseMove(nFlags, point);
}

LRESULT CZiListIcon::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bMouseTracking = FALSE;
	int nIndex = -1;
	if (nIndex != m_nHoverIndex) {
		m_ItemImgArray[m_nHoverIndex].bIsHoveing = false;
		m_nHoverIndex = nIndex;
		Invalidate(FALSE);
	}
	return 0;
}
