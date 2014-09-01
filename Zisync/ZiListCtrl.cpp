// ZiListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "ZiListCtrl.h"
#include "MemoryDC.h"
#include "RenderManager.h"

// CZiListCtrl

IMPLEMENT_DYNAMIC(CZiListCtrl, CListCtrl)

CZiListCtrl::CZiListCtrl()
{
	m_nHeightItem = 0;
	m_uActiveItem = -1;
	m_nItemHov = 0;
	m_pHovenImg = m_pSelectImg = NULL;
	m_pCheckImg = m_pUnCheckImg = NULL;
	m_colorBk = RGB(255, 255, 255);
	m_colorRightTopNor = m_colorRightTopHov = RGB(0, 0, 0);
	
	m_bBackHovFromID = FALSE;
	m_bBackSelFromID = FALSE;
	m_bIconFromID = FALSE;

	m_ToolTip.Create(this);
}

CZiListCtrl::~CZiListCtrl()
{
}


BEGIN_MESSAGE_MAP(CZiListCtrl, CListCtrl)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()

// CZiListCtrl message handlers

int CZiListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

//	m_HeaderCtrl.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd());

	return 0;
}


void CZiListCtrl::OnDestroy()
{
	__super::OnDestroy();

	if (m_ToolTip.GetSafeHwnd())
		m_ToolTip.DestroyWindow();
	m_ToolTip.m_hWnd = NULL;

	if (m_bBackHovFromID) {
		RenderEngine->RemoveImage(m_pHovenImg, RESOURCE_ID);
	} else {
		RenderEngine->RemoveImage(m_pHovenImg);
	}
	
	if (m_bBackSelFromID) {
		RenderEngine->RemoveImage(m_pSelectImg, RESOURCE_ID);
	} else {
		RenderEngine->RemoveImage(m_pSelectImg);
	}

	CItemImgArray::iterator iterImg = m_ItemImgArray.begin();
	for (; iterImg != m_ItemImgArray.end(); ++iterImg) {
		if (m_bIconFromID) {
			RenderEngine->RemoveImage(iterImg->pImage, RESOURCE_ID);
		} else {
			RenderEngine->RemoveImage(iterImg->pImage);
		}		
	}
	m_ItemImgArray.clear();

	CItemImgArray::iterator iterBtn = m_ItemBtnArray.begin();
	for (; iterBtn != m_ItemBtnArray.end(); ++iterBtn) {
		if (m_bIconFromID) {
			RenderEngine->RemoveImage(iterBtn->pImage, RESOURCE_ID);
			RenderEngine->RemoveImage(iterBtn->pSelectImage, RESOURCE_ID);
		} else {
			RenderEngine->RemoveImage(iterBtn->pImage);
			RenderEngine->RemoveImage(iterBtn->pSelectImage);
		}		
	}
	m_ItemBtnArray.clear();

	CItemImgArray::iterator iterInvite = m_ItemInviteArray.begin();
	for (; iterInvite != m_ItemInviteArray.end(); ++iterInvite) {
		if (m_bIconFromID) {
			RenderEngine->RemoveImage(iterInvite->pImage, RESOURCE_ID);
		} else {
			RenderEngine->RemoveImage(iterInvite->pImage);
		}		
	}
	m_ItemInviteArray.clear();

	CItemImgArray::iterator iterSet = m_ItemSetArray.begin();
	for (; iterSet != m_ItemSetArray.end(); ++iterSet) {
		if (m_bIconFromID) {
			RenderEngine->RemoveImage(iterSet->pImage, RESOURCE_ID);
		} else {
			RenderEngine->RemoveImage(iterSet->pImage);
		}
	}
	m_ItemSetArray.clear();

	RenderEngine->RemoveImage(m_pCheckImg);
	RenderEngine->RemoveImage(m_pUnCheckImg);

	m_ItemContent.clear();
	RemoveScorll();
}


void CZiListCtrl::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	__super::PreSubclassWindow();
//	m_HeaderCtrl.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd());
	return;
}


void CZiListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CRect rcItem = lpDrawItemStruct->rcItem;
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CMemoryDC BufferDc(pDC, rcItem);

	INT nItemID = lpDrawItemStruct->itemID;
//	INT nColumnCount=m_HeaderCtrl.GetItemCount();
	INT nColumnCount = GetHeaderCtrl()->GetItemCount();

	CRect rcClipBox;
	BufferDc.GetClipBox(&rcClipBox);

	BufferDc.SetBkMode(TRANSPARENT);
	BufferDc.SetTextColor(m_colNormalText);
	BufferDc.SelectObject(GetCtrlFont());
	BufferDc->FillSolidRect(&rcItem, m_colorBk);

	if (lpDrawItemStruct->itemState & ODS_SELECTED) {
		if (m_pSelectImg != NULL && !m_pSelectImg->IsNull()) {
			m_pSelectImg->Draw(&BufferDc, rcItem);
		}
	} else if ( m_uActiveItem == nItemID ) {
		if (m_pHovenImg != NULL && !m_pSelectImg->IsNull()) {
			m_pHovenImg->Draw(&BufferDc, rcItem);
		}
	}

	for (INT i = 0; i < nColumnCount; i++) {
		CRect rcSubRect;
		GetSubItemRect(nItemID, i, LVIR_BOUNDS, rcSubRect);

		if (rcSubRect.left > rcSubRect.right) break;
		if (rcSubRect.right < rcSubRect.left) continue;

		DrawReportItem(&BufferDc, nItemID, rcSubRect, i);
	}

	return;
}

void CZiListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rcItem;

	static UINT uOldActionItem = -1;
	for (INT i = 0; i < GetItemCount(); i++) {
		GetItemRect(i, rcItem, LVIR_BOUNDS);
		if (PtInRect(&rcItem, point)) {
			m_uActiveItem = i;

			if (uOldActionItem != m_uActiveItem) {
				uOldActionItem = m_uActiveItem;
				Invalidate(FALSE);
			}

			break;
		}
	}

	CRect rcSubItem, rcLeftTop;
	for ( INT i = 0 ; i < GetItemCount(); i++) {
		GetSubItemRect(i, 1, LVIR_BOUNDS, rcSubItem);
		rcLeftTop.top = rcSubItem.top;
		rcLeftTop.bottom = rcSubItem.top + (rcSubItem.bottom - rcSubItem.top)/2 ;
		rcLeftTop.right = rcSubItem.right;
		rcLeftTop.left =  rcSubItem.right - 80;

		if (PtInRect(&rcLeftTop, point)) {
			CItemContentArray::iterator it = m_ItemContent.find(i);

			if (it == m_ItemContent.end()) {
			} else {
				it->second.bRightTopHov = true;
				Invalidate(FALSE);
			}
			break;
		} else {
			CItemContentArray::iterator it = m_ItemContent.find(i);

			if (it == m_ItemContent.end()) {
			} else {
				it->second.bRightTopHov = false;
				Invalidate(FALSE);
			}
		}
	}

	CRect rcSubItemTip;
	for (INT i = 0; i < GetItemCount(); i++) {
		GetSubItemRect(i, 2, LVIR_BOUNDS, rcSubItemTip);
		if (PtInRect(&rcSubItemTip, point)) {
			CString strText = _T("立即同步");
			if (!m_ToolTip.GetSafeHwnd()) {
				m_ToolTip.Create(this);				
				m_ToolTip.SetMaxTipWidth(200);
			}

			if (m_ToolTip.GetSafeHwnd()) {
				m_ToolTip.Activate(TRUE);
				m_ToolTip.AddTool(this, _T("立即同步"),&rcSubItemTip, 1);
			}
		}
	}

	__super::OnMouseMove(nFlags, point);
}

BOOL CZiListCtrl::PreTranslateMessage(MSG* pMsg)
{
	if(m_ToolTip.GetSafeHwnd())
	{
		m_ToolTip.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

BOOL CZiListCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC BufferDc(pDC, &rcClient);
	BufferDc.FillSolidRect(&rcClient, m_colorBk);

	return TRUE;
}

void CZiListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pCheckImg != NULL && !m_pCheckImg->IsNull()) {
		CRect rcSubItem, rcIcon;

		for (INT i = 0; i < GetItemCount(); i++) {
			GetItemRect(i,rcSubItem, LVIR_BOUNDS);

			rcIcon.left = rcSubItem.left+7;
			rcIcon.top = rcSubItem.top+(rcSubItem.Height()-m_pCheckImg->GetHeight())/2;
			rcIcon.right = rcIcon.left + m_pCheckImg->GetWidth();
			rcIcon.bottom = rcIcon.top + m_pCheckImg->GetHeight();
			
			if (PtInRect(&rcIcon, point)) {
				SetCheck(i, !GetCheck(i));

				SetItemState(i, LVIS_FOCUSED | LVIS_SELECTED,LVIS_FOCUSED | LVIS_SELECTED);
				SetSelectionMark(i);

				Invalidate(FALSE);
				break;
			}
		}
	}
	
	for (INT i = 0; i < GetItemCount(); i++) {
		CRect rcSubItem;
		GetSubItemRect(i, 2, LVIR_BOUNDS, rcSubItem);
		if (PtInRect(&rcSubItem, point)) {
			CItemImgArray::iterator iter = m_ItemBtnArray.begin();
			for (; iter != m_ItemBtnArray.end(); ++iter) {
				if (iter->nItem == i){					
					iter->bSelect = !iter->bSelect;
				}
			}
		}
	} 

	__super::OnLButtonDown(nFlags, point);
}

BOOL CZiListCtrl::SetHovenImage(UINT nResFromID, LPCTSTR lpszFileType, const LPRECT lprcNinePart)
{
	m_bBackHovFromID = TRUE;

	RenderEngine->RemoveImage(m_pHovenImg, RESOURCE_ID);

	m_pHovenImg = RenderEngine->GetImage(nResFromID, lpszFileType);

	if (m_pHovenImg == NULL) {
		return FALSE;
	} else {
		m_pHovenImg->SetNinePart(lprcNinePart);
		return TRUE;
	}
}

BOOL CZiListCtrl::SetHovenImage(LPCTSTR lpszFileName, const LPRECT lprcNinePart)
{
	RenderEngine->RemoveImage(m_pHovenImg);

	m_pHovenImg = RenderEngine->GetImage(lpszFileName);

	if (m_pHovenImg == NULL) { 
		return FALSE;
	}else {
		m_pHovenImg->SetNinePart(lprcNinePart);
		return TRUE;
	}
}

BOOL CZiListCtrl::SetSelectImage(UINT nResFromID, LPCTSTR lpszFileType, const LPRECT lprcNinePart) 
{
	m_bBackSelFromID = TRUE;

	RenderEngine->RemoveImage(m_pSelectImg);

	m_pSelectImg = RenderEngine->GetImage(nResFromID, lpszFileType);

	if (m_pSelectImg == NULL) {
		return FALSE;
	} else {
		m_pSelectImg->SetNinePart(lprcNinePart);
		return TRUE;
	}
}

BOOL CZiListCtrl::SetSelectImage(LPCTSTR lpszFileName, const LPRECT lprcNinePart)
{
	RenderEngine->RemoveImage(m_pSelectImg);

	m_pSelectImg = RenderEngine->GetImage(lpszFileName);

	if (m_pSelectImg == NULL) {
		return FALSE;
	} else {
		m_pSelectImg->SetNinePart(lprcNinePart);
		return TRUE;
	}
}

BOOL CZiListCtrl::SetCheckImage(LPCTSTR lpszCheckName,LPCTSTR lpszUnCheckName)
{
	RenderEngine->RemoveImage(m_pCheckImg);
	RenderEngine->RemoveImage(m_pUnCheckImg);

	m_pCheckImg = RenderEngine->GetImage(lpszCheckName);
	m_pUnCheckImg = RenderEngine->GetImage(lpszUnCheckName);
	
	if (m_pCheckImg == NULL || m_pUnCheckImg == NULL)
		return FALSE;
	else
		return TRUE;
}

BOOL CZiListCtrl::InsertImage(int nItem, int nSubItem, UINT nResNorID, UINT nResSelID, LPCTSTR lpszFileType)
{
	m_bIconFromID = TRUE;
	
	CItemImgArray::iterator iter, iterEnd;
	CItemImgArray* pItemArray;
	switch (nSubItem)
	{
	case 0:
		iter = m_ItemImgArray.begin();
		iterEnd = m_ItemImgArray.end();
		pItemArray = &m_ItemImgArray;
		break;
	case 2:
		iter = m_ItemBtnArray.begin();
		iterEnd = m_ItemBtnArray.end();
		pItemArray = &m_ItemBtnArray;
		break;
	case 3:
		iter = m_ItemInviteArray.begin();
		iterEnd = m_ItemInviteArray.end();
		pItemArray = &m_ItemInviteArray;
		break;
	case 4:
		iter = m_ItemSetArray.begin();
		iterEnd = m_ItemSetArray.end();
		pItemArray = &m_ItemSetArray;
		break;
	}

	for (; iter != iterEnd; ++iter) {
		if (iter->nItem == nItem) {
			if (iter->pImage != NULL) {
				RenderEngine->RemoveImage(iter->pImage, RESOURCE_ID);
				iter->pImage = RenderEngine->GetImage(nResNorID, lpszFileType);
				
				if (iter->pSelectImage != NULL) {
					iter->bSelect = false;
					RenderEngine->RemoveImage(iter->pSelectImage);
					if (nResSelID != 0)
						iter->pSelectImage = RenderEngine->GetImage(nResSelID, lpszFileType);					
				}
				return TRUE;
			}
		}		
	}

	tagItemImage ItemImage;
	ItemImage.nItem = nItem;
	ItemImage.bSelect = false;
	ItemImage.pImage = RenderEngine->GetImage(nResNorID, lpszFileType);
	if (nResSelID != 0)
		ItemImage.pSelectImage = RenderEngine->GetImage(nResSelID, lpszFileType);

	if (NULL == ItemImage.pImage)
		return FALSE;
	else if (nResSelID > 0 && ItemImage.pSelectImage ==NULL) 
		return FALSE;
	else {
		pItemArray->push_back(ItemImage);
		return TRUE;
	} 

	ASSERT(FALSE);		
	return FALSE;
}

BOOL CZiListCtrl::InsertImage(int nItem, int nSubItem, LPCTSTR lpszFileName, LPCTSTR lpszSelFileName)
{
	CItemImgArray::iterator iter, iterEnd;
	CItemImgArray* pItemArray;
	switch (nSubItem)
	{
		case 0:
			iter = m_ItemImgArray.begin();
			iterEnd = m_ItemImgArray.end();
			pItemArray = &m_ItemImgArray;
		break;
		case 2:
			iter = m_ItemBtnArray.begin();
			iterEnd = m_ItemBtnArray.end();
			pItemArray = &m_ItemBtnArray;
		break;
		case 3:
			iter = m_ItemInviteArray.begin();
			iterEnd = m_ItemInviteArray.end();
			pItemArray = &m_ItemInviteArray;
		break;
		case 4:
			iter = m_ItemSetArray.begin();
			iterEnd = m_ItemSetArray.end();
			pItemArray = &m_ItemSetArray;
		break;
	}
	
	for (; iter != iterEnd; ++ iter) {
		if (iter->nItem == nItem) {
			if (iter->pImage != NULL) {
				RenderEngine->RemoveImage(iter->pImage);
				iter->pImage = RenderEngine->GetImage(lpszFileName);

				if (lpszSelFileName != NULL &&(iter->pSelectImage != NULL))
				{
					iter->bSelect = false;
					RenderEngine->RemoveImage(iter->pSelectImage);
					iter->pSelectImage = RenderEngine->GetImage(lpszSelFileName);
				}
				return TRUE;
			}
		}		
	}

	tagItemImage ItemImage;
	ItemImage.nItem = nItem;
	ItemImage.bSelect = false;
	ItemImage.pImage = RenderEngine->GetImage(lpszFileName);
	if (lpszSelFileName != NULL) {
		ItemImage.pSelectImage = RenderEngine->GetImage(lpszSelFileName);
	}

	if (ItemImage.pImage == NULL)
		return FALSE;
	else if (lpszSelFileName != NULL && ItemImage.pSelectImage ==NULL) 
		return FALSE;
	else {
		pItemArray->push_back(ItemImage);
		return TRUE;
	} 
		
	ASSERT(FALSE);		
	return FALSE;	
}

void CZiListCtrl::DrawReportItem(CDC * pDC, INT nItem, CRect & rcSubItem, INT nColumnIndex)
{
//	TCHAR szString[256] = _T("");
//	GetItemText(nItem, nColumnIndex, szString, sizeof(szString)/sizeof(TCHAR));
	
	rcSubItem.left += 5;

	if (nColumnIndex == 0) {
		if ((m_pCheckImg != NULL && !m_pCheckImg->IsNull()) 
			&&(m_pUnCheckImg != NULL && !m_pUnCheckImg->IsNull()))
		{
			if (GetCheck(nItem)) 
				m_pCheckImg->DrawImage(pDC, rcSubItem.left+2, 
				rcSubItem.top+(rcSubItem.Height() - m_pCheckImg->GetHeight())/2);
			
			else 
				m_pUnCheckImg->DrawImage(pDC, rcSubItem.left+2, 
				rcSubItem.top+(rcSubItem.Height() - m_pUnCheckImg->GetHeight())/2);
			rcSubItem.left += (8+m_pCheckImg->GetWidth());
		}
	

		CItemImgArray::iterator iter = m_ItemImgArray.begin();
		for (;iter != m_ItemImgArray.end(); ++iter) {
			if (iter->nItem == nItem) {
				CZiImage *pImage = iter->pImage;
				
				if (pImage != NULL && !pImage->IsNull()) {
					pImage->DrawImage(pDC, rcSubItem.left+2,
						rcSubItem.top+(rcSubItem.Height()-pImage->GetHeight())/2);
					rcSubItem.left += (8+pImage->GetWidth());
				}
				break;
			}
		}
	} else if (nColumnIndex == 2) {
		CItemImgArray::iterator iter = m_ItemBtnArray.begin();
		for (;iter != m_ItemBtnArray.end(); ++iter) {
			if (iter->nItem == nItem) {
				CZiImage *pImage;
				if (iter->bSelect) {
					pImage = iter->pSelectImage;;
				} else {
					pImage = iter->pImage;
				}					

				if (pImage != NULL && !pImage->IsNull()) {
					pImage->DrawImage(pDC, rcSubItem.left+2,
						rcSubItem.top+(rcSubItem.Height()-pImage->GetHeight())/2);
					rcSubItem.left += (8+pImage->GetWidth());
				}
				break;
			}
		}
	} 
	else if (nColumnIndex == 1) {
		tagItemContent ItemContent;
		CItemContentArray::iterator it = m_ItemContent.find(nItem);

		if (it == m_ItemContent.end()) {
			return;
		} else {
			ItemContent.strLeftBottom = it->second.strLeftBottom;
			ItemContent.strLeftTop = it->second.strLeftTop;
			ItemContent.strRightTop = it->second.strRightTop;
			ItemContent.strRightBottom = it->second.strRightBottom;
			ItemContent.bRightTopHov = it->second.bRightTopHov;
		}

		CRect rcLeftTop, rcLeftBottom, rcRightTop, rcRightBottom;
		rcRightTop.left = rcSubItem.right - 80;
		rcRightTop.right = rcSubItem.right;
		rcRightTop.top = rcSubItem.top;
		rcRightTop.bottom = rcSubItem.top + (rcSubItem.bottom - rcSubItem.top)/2 - 5;

		rcLeftTop.top = rcRightTop.top;
		rcLeftTop.bottom = rcRightTop.bottom;
		rcLeftTop.right = rcRightTop.left - 30;
		rcLeftTop.left = rcSubItem.left;

		if (ItemContent.strRightBottom != NULL) {
			rcLeftBottom.top = rcRightTop.bottom + 5;
			rcLeftBottom.bottom = rcSubItem.bottom;
			rcLeftBottom.left = rcSubItem.left;
			rcLeftBottom.right = rcSubItem.left + rcSubItem.Width()/2;

			rcRightBottom.top = rcLeftBottom.top;
			rcRightBottom.bottom = rcLeftBottom.bottom;
			rcRightBottom.left = rcLeftBottom.right + 5;
			rcRightBottom.right = rcRightTop.right;
		} else {
			rcLeftBottom.top = rcRightTop.bottom + 5;
			rcLeftBottom.bottom = rcSubItem.bottom;
			rcLeftBottom.left = rcSubItem.left;
			rcLeftBottom.right = rcSubItem.right;
		}

		if (ItemContent.strLeftTop != NULL) {
			CFont font, *pOldFont;
			font.CreateFont(15, 8, 0, 0, FW_MEDIUM, FALSE, FALSE, 0, DEFAULT_CHARSET,             
				OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
				DEFAULT_PITCH | FF_SWISS, _T("宋体"));
			pOldFont = pDC->SelectObject(&font);
			pDC->DrawText(ItemContent.strLeftTop,lstrlen(ItemContent.strLeftTop),
				&rcLeftTop, DT_BOTTOM | DT_SINGLELINE |DT_END_ELLIPSIS);
			pDC->SelectObject(pOldFont);
		} 
		if (ItemContent.strLeftBottom != NULL) {
			COLORREF oldColor;
			oldColor = pDC->SetTextColor(RGB(125, 125, 125));
			pDC->DrawText(ItemContent.strLeftBottom,lstrlen(ItemContent.strLeftBottom), 
				&rcLeftBottom, DT_TOP | DT_SINGLELINE |DT_END_ELLIPSIS);
			pDC->SetTextColor(oldColor);
		}	
		if (ItemContent.strRightTop !=NULL) {
			COLORREF oldColor;
			if (ItemContent.bRightTopHov) {
				oldColor = pDC->SetTextColor(m_colorRightTopHov);
			} else {
				oldColor = pDC->SetTextColor(m_colorRightTopNor);
			}			
			pDC->DrawText(ItemContent.strRightTop,lstrlen(ItemContent.strRightTop), 
				&rcRightTop, DT_BOTTOM | DT_SINGLELINE |DT_END_ELLIPSIS);
			pDC->SetTextColor(oldColor);
		}
		if (ItemContent.strRightBottom != NULL) {
			pDC->DrawText(ItemContent.strRightBottom,lstrlen(ItemContent.strRightBottom), 
				&rcRightBottom, DT_TOP | DT_SINGLELINE |DT_END_ELLIPSIS | DT_LEFT);
		}
	} 
	else if (nColumnIndex == 3) {
		CItemImgArray::iterator iter = m_ItemInviteArray.begin();
		for (;iter != m_ItemInviteArray.end(); ++iter) {
			if (iter->nItem == nItem) {
				CZiImage *pImage;
				if (iter->bSelect) {
					pImage = iter->pSelectImage;;
				} else {
					pImage = iter->pImage;
				}					

				if (pImage != NULL && !pImage->IsNull()) {
					pImage->DrawImage(pDC, rcSubItem.left+2,
						rcSubItem.top+(rcSubItem.Height()-pImage->GetHeight())/2);
					rcSubItem.left += (8+pImage->GetWidth());
				}
				break;
			}
		}
	} else if (nColumnIndex == 4) {
		CItemImgArray::iterator iter = m_ItemSetArray.begin();
		for (;iter != m_ItemSetArray.end(); ++iter) {
			if (iter->nItem == nItem) {
				CZiImage *pImage;
				if (iter->bSelect) {
					pImage = iter->pSelectImage;;
				} else {
					pImage = iter->pImage;
				}					

				if (pImage != NULL && !pImage->IsNull()) {
					pImage->DrawImage(pDC, rcSubItem.left+2,
						rcSubItem.top+(rcSubItem.Height()-pImage->GetHeight())/2);
					rcSubItem.left += (8+pImage->GetWidth());
				}
				break;
			}
		}
	}
	return;
}

void CZiListCtrl::SetItemHeight(int nHeight)
{
	m_nHeightItem = nHeight;

	CRect rcWin;
	GetWindowRect(&rcWin);

	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	
	SendMessage(WM_WINDOWPOSCHANGED, 0, LPARAM(&wp));
}

void CZiListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (m_nHeightItem > 0) {
		lpMeasureItemStruct->itemHeight  = m_nHeightItem;
	}
}

int CZiListCtrl::InsertItem(const LVITEM* pItem)
{
	int nResult = CListCtrl::InsertItem(pItem);

	SetCheck(pItem->iItem, FALSE);

	return nResult;
}

int CZiListCtrl::InsertItem(int nItem, LPCTSTR lpszItem)
{
	int nResult = CListCtrl::InsertItem(nItem, lpszItem);

	SetCheck(nItem, FALSE);

	return nResult;
}

int CZiListCtrl::InsertItem(int nItem, LPCTSTR lpszItem, int nImage)
{
	int nResult = CListCtrl::InsertItem(nItem, lpszItem, nImage);

	SetCheck(nItem, FALSE);

	return nResult;
}

int CZiListCtrl::InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState,UINT nStateMask, int nImage, LPARAM lParam)
{
	int nResult = CListCtrl::InsertItem(nMask, nItem, lpszItem, nState, nStateMask, nImage, lParam);

	SetCheck(nItem, FALSE);

	return nResult;
}

DWORD CZiListCtrl::SetExtendedStyle(DWORD dwNewStyle)
{
	if ( dwNewStyle & LVS_EX_CHECKBOXES )
	{
		dwNewStyle &=~LVS_EX_CHECKBOXES;
		dwNewStyle &=~LVS_EX_GRIDLINES;
	}

	return CListCtrl::SetExtendedStyle(dwNewStyle);
}

void CZiListCtrl::SetItemContent(int nItem, LPCTSTR lpszLeftTop, LPCTSTR lpszRightTop, LPCTSTR lpszLeftBottom, LPCTSTR lpszRightBtoom)
{
	CItemContentArray::iterator it = m_ItemContent.find(nItem);
	tagItemContent ItemContent;
	ItemContent.strLeftTop = lpszLeftTop;
	ItemContent.strRightTop = lpszRightTop;
	ItemContent.strLeftBottom = lpszLeftBottom;
	ItemContent.strRightBottom = lpszRightBtoom;
	ItemContent.bRightTopHov = false;

	if (it == m_ItemContent.end()) {
		m_ItemContent.insert(map<int, tagItemContent>::value_type(nItem, ItemContent));	
	} else {
		it->second = ItemContent;
		Invalidate(FALSE);
	}
}

BOOL CZiListCtrl::GetItemContent(int nItem, tagItemContent& itemContent)
{
	CItemContentArray::iterator it = m_ItemContent.find(nItem);

	if (it == m_ItemContent.end()) {
		return FALSE;
	} else {
		itemContent.strLeftBottom = it->second.strLeftBottom;
		itemContent.strLeftTop = it->second.strLeftTop;
		itemContent.strRightTop = it->second.strRightTop;
		return TRUE;
	}
}

BOOL CZiListCtrl::HitTestRightTop(int nItem, POINT pt)
{
	CRect rcSubItem, rcRightTop;
	GetSubItemRect(nItem, 1, LVIR_BOUNDS, rcSubItem);
	rcRightTop.top = rcSubItem.top;
	rcRightTop.bottom = rcSubItem.top + (rcSubItem.bottom - rcSubItem.top)/2 ;
	rcRightTop.right = rcSubItem.right;
	rcRightTop.left =  rcSubItem.right - 80;

	if (PtInRect(&rcRightTop, pt)) 
		return TRUE;
	else
		return FALSE;
}

void CZiListCtrl::SetRightTopColor(COLORREF colorNor,COLORREF colorHov)
{
	m_colorRightTopHov = colorHov;
	m_colorRightTopNor = colorNor;
}



BEGIN_MESSAGE_MAP(CZiHeaderCtrl, CHeaderCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
END_MESSAGE_MAP()


CZiHeaderCtrl::CZiHeaderCtrl()
{
	m_uLockCount = 0;
	m_uItemHeight = 0;

	m_pBackImg = m_pPressImg = m_pGridImg = NULL;
	m_bPress = false;
}

CZiHeaderCtrl::~CZiHeaderCtrl()
{

}

void CZiHeaderCtrl::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CHeaderCtrl::PreSubclassWindow();
}


BOOL CZiHeaderCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	NMHEADER * pNMHearder=(NMHEADER*)lParam;

	if ((pNMHearder->hdr.code==HDN_BEGINTRACKA)||(pNMHearder->hdr.code==HDN_BEGINTRACKW))
	{
		if (pNMHearder->iItem<(INT)m_uLockCount)
		{
			*pLResult=TRUE;
			return TRUE;
		}
	}

	return CHeaderCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}
void CZiHeaderCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rcRect;

	GetClientRect(&rcRect);

	CMemoryDC BufferDC(&dc, rcRect);

	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SetTextColor(m_colNormalText);
	BufferDC.SelectObject(GetCtrlFont());

	if (m_pBackImg != NULL && !m_pBackImg->IsNull()) {
		m_pBackImg->Draw(&BufferDC, rcRect);
	}

	if (m_pPressImg != NULL && !m_pPressImg->IsNull() && m_pPressImg) {
		CRect rcItemRect;
		GetItemRect(m_uActiveItem, &rcItemRect);

		m_pPressImg->Draw(&BufferDC, rcItemRect);
	}

	CRect rcItem;
	HDITEM HDItem;
	TCHAR szBuffer[64];
	for (INT i=0;i<GetItemCount();i++)
	{
		HDItem.mask=HDI_TEXT;
		HDItem.pszText=szBuffer;
		HDItem.cchTextMax=sizeof(szBuffer)/sizeof(TCHAR);

		GetItem(i,&HDItem);
		GetItemRect(i,&rcItem);

		if (m_pGridImg != NULL && !m_pGridImg->IsNull())
			m_pGridImg->DrawImage(&BufferDC,(rcItem.right-m_pGridImg->GetWidth()),(rcItem.Height()-m_pGridImg->GetHeight())/2);

		rcItem.DeflateRect(3,1,3,1);
		BufferDC.DrawText(szBuffer,lstrlen(szBuffer),&rcItem,DT_END_ELLIPSIS|DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	}

}

void CZiHeaderCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rcItem;

	for (INT i=0;i<GetItemCount();i++)
	{
		GetItemRect(i,&rcItem);

		if ( PtInRect(&rcItem,point) )
		{
			m_bPress = true;
			m_uActiveItem = i;
			break;
		}
	}

	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	CHeaderCtrl::OnLButtonDown(nFlags, point);
}


void CZiHeaderCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bPress = false;

	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	CHeaderCtrl::OnLButtonUp(nFlags, point);
}


BOOL CZiHeaderCtrl::OnEraseBkgnd(CDC* pDC)
{
	return	TRUE;
}

BOOL CZiHeaderCtrl::SetBackImage(LPCTSTR lpNormal, CONST LPRECT lprcNinePart/*=NULL*/)
{
	RenderEngine->RemoveImage(m_pBackImg);

	m_pBackImg = RenderEngine->GetImage(lpNormal);

	if (NULL == m_pBackImg)
		return FALSE;
	else
	{
		m_pBackImg->SetNinePart(lprcNinePart);
		return TRUE;
	}
}

BOOL CZiHeaderCtrl::SetPressImage(LPCTSTR lpNormal, CONST LPRECT lprcNinePart/*=NULL*/)
{
	RenderEngine->RemoveImage(m_pPressImg);

	m_pPressImg = RenderEngine->GetImage(lpNormal);

	if (NULL == m_pPressImg)
		return FALSE;
	else
	{
		m_pPressImg->SetNinePart(lprcNinePart);
		return TRUE;
	}
}

BOOL CZiHeaderCtrl::SetGridImage(LPCTSTR lpNormal)
{
	RenderEngine->RemoveImage(m_pGridImg);

	m_pGridImg = RenderEngine->GetImage(lpNormal);

	if (NULL == m_pGridImg)
		return FALSE;
	else
	{
		return TRUE;
	}
}

void CZiHeaderCtrl::SetLockCount(UINT uLockCount) {
	m_uLockCount = uLockCount;
}

void CZiHeaderCtrl::SetItemHeight(UINT uItemHeight)
{
	m_uItemHeight = uItemHeight;
}



void CZiHeaderCtrl::OnDestroy()
{
	__super::OnDestroy();

	RenderEngine->RemoveImage(m_pBackImg);
	RenderEngine->RemoveImage(m_pPressImg);
	RenderEngine->RemoveImage(m_pGridImg);
}

LRESULT CZiHeaderCtrl::OnLayout( WPARAM wParam, LPARAM lParam )
{
	LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam); 
	HD_LAYOUT &hdl = *( HD_LAYOUT * ) lParam; 
	RECT *prc = hdl.prc; 
	WINDOWPOS *pwpos = hdl.pwpos; 

	int nHeight = 0;
	pwpos->cy = nHeight; 
	prc->top = nHeight; 

	return lResult; 
}
