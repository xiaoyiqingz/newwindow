// MyListIcon.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "MemoryDC.h"
#include "MyListIcon.h"
#include "RenderManager.h"

// CMyListIcon

IMPLEMENT_DYNAMIC(CMyListIcon, CListCtrl)

CMyListIcon::CMyListIcon()
{
	m_xPadding = 5;
	m_yPadding = 5;
}

CMyListIcon::~CMyListIcon()
{
}


BEGIN_MESSAGE_MAP(CMyListIcon, CListCtrl)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CMyListIcon message handlers




void CMyListIcon::OnDestroy()
{
	__super::OnDestroy();

	CItemArray::iterator iter = m_ItemImgArray.begin();
	for (; iter != m_ItemImgArray.end(); ++iter) {
		RenderEngine->RemoveImage(iter->m_pImgBack);
		RenderEngine->RemoveImage(iter->m_pImgIcon);
		RenderEngine->RemoveImage(iter->m_pImgIconSel);
	}
	m_ItemImgArray.clear();

	RemoveScorll();
}

BOOL CMyListIcon::SetItemImage(int nItem, LPCTSTR lpBackImg, LPCTSTR lpIcon, LPCTSTR lpIconSel)
{
	CItemArray::iterator iter = m_ItemImgArray.begin();
	for (; iter != m_ItemImgArray.end(); iter++) {
		if (iter->nItem == nItem) {
			if (iter->m_pImgBack != NULL) {
				RenderEngine->RemoveImage(iter->m_pImgBack);
				RenderEngine->GetImage(lpBackImg);
			}

			if (iter->m_pImgIcon != NULL) {
				RenderEngine->RemoveImage(iter->m_pImgIcon);
				RenderEngine->GetImage(lpIcon);
			}

			if (iter->m_pImgIconSel!= NULL) {
				RenderEngine->RemoveImage(iter->m_pImgIconSel);
				RenderEngine->GetImage(lpIconSel);
			}
			return TRUE;
		}
	}

	tagItem ItemNode;
	ItemNode.nItem = nItem;
	ItemNode.bIsSelected = false;
	ItemNode.m_pImgBack = RenderEngine->GetImage(lpBackImg);
	ItemNode.m_pImgIcon = RenderEngine->GetImage(lpIcon);
	ItemNode.m_pImgIconSel = RenderEngine->GetImage(lpIconSel);

	if (NULL == ItemNode.m_pImgBack || NULL == ItemNode.m_pImgIcon || 
		NULL == ItemNode.m_pImgIconSel) 
		return FALSE;
	else {
		m_ItemImgArray.push_back(ItemNode);
		return TRUE;
	}
}


void CMyListIcon::OnPaint()
{
	CPaintDC dc(this); 
	
	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC memoryDC(&dc, rcClient);
	DrawParentWndBg(GetSafeHwnd(), memoryDC->GetSafeHdc());

	for (int i = 0; i < (int)m_ItemImgArray.size(); i++) {
		int xOrder = i % GetItemCountH();
		int yOrder = i / GetItemCountH();
		CRect rcItem;
		rcItem.left = GetItemLeftPadding() + (m_ItemSize.cx + m_xPadding) * xOrder;
		rcItem.right = rcItem.left + m_ItemSize.cy;
		rcItem.top = (m_ItemSize.cy + m_yPadding) * yOrder;
		rcItem.bottom = rcItem.top + m_ItemSize.cy;

		DrawIconItem(&memoryDC, rcItem, i);
	}
}

void CMyListIcon::DrawIconItem(CDC *pDC, CRect & rcItem, int nItem)
{
	CItemArray::iterator iter = m_ItemImgArray.begin();
	for(; iter != m_ItemImgArray.end(); iter++) {
		if (iter->nItem == nItem) {
			BOOL  bIsSelected = FALSE;
			if (iter->bIsSelected == true) 
				bIsSelected = TRUE;

			int cx = iter->m_pImgBack->GetWidth();
			int cy = iter->m_pImgBack->GetWidth();
			int cxIcon = iter->m_pImgIcon->GetWidth();
			int cyIcon = iter->m_pImgIcon->GetHeight();

			CRect rcBack, rcIcon, rcText;
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

			rcText.top = rcIcon.bottom + 2;
			rcText.left = rcItem.left + 2;
			rcText.bottom = rcItem.bottom - 2;
			rcText.right = rcItem.right - 2;

			int nMode = pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(GetCtrlFont());
			pDC->SetTextColor(m_colNormalText);
			UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;
			pDC->DrawText(iter->strText, iter->strText.GetLength(), &rcText, nFormat);
			pDC->SetBkMode(nMode);
			break;
		}
						
	}	
}

void CMyListIcon::SetItemSize(CSize size)
{
	m_ItemSize = size;
}

int CMyListIcon::GetItemCountH()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	return ((rcClient.Width() - m_ItemSize.cx) / (m_ItemSize.cx + m_xPadding)) + 1;
}

int CMyListIcon::GetItemLeftPadding()
{	
	int itemWidth = GetItemCountH() * (m_xPadding + m_ItemSize.cx) -m_xPadding;
	CRect rcClient;
	GetClientRect(&rcClient);
	return (rcClient.Width() - itemWidth)/2;
}

void CMyListIcon::SetPadding(int cx, int cy)
{
	m_xPadding = cx;
	m_yPadding = cy;
}


BOOL CMyListIcon::SetItemText(int nItem, CString strText)
{
	CItemArray::iterator iter = m_ItemImgArray.begin();
	for (; iter != m_ItemImgArray.end(); iter++) {
		if (iter->nItem == nItem) {
			iter->strText = strText;
			return TRUE;
		}
	}
	return FALSE;
}


BOOL CMyListIcon::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
//	return __super::OnEraseBkgnd(pDC);
}


void CMyListIcon::OnLButtonDown(UINT nFlags, CPoint point)
{
	int nIndex = HitTest(point);
	if (nIndex != -1) {
		m_ItemImgArray[nIndex].bIsSelected = !m_ItemImgArray[nIndex].bIsSelected;
		Invalidate(FALSE);
	}
	__super::OnLButtonDown(nFlags, point);
}

int CMyListIcon::HitTest(POINT point)
{
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
	}
	return -1;
}

int CMyListIcon::GetItemCount()
{
	return (int)m_ItemImgArray.size();
}

BOOL CMyListIcon::GetChecked(int nItem)
{
	if (m_ItemImgArray[nItem].bIsSelected == true) 
		return TRUE;
	else 
		return FALSE;
}
