// UI\ZiScrollBar.cpp : implementation file
//
#include "stdafx.h"
#include "Zisync.h"
#include "RenderManager.h"
#include "Ui/ZiScrollBar.h"

// CZiScrollBar
#define SCROLLBAR_NORMAL_MINIMUM 45

IMPLEMENT_DYNAMIC(CZiScrollBar, CStatic)

CZiScrollBar::CZiScrollBar()
{
	m_pHThumbImg = m_pVThumbImg = NULL;
	m_pHBackImg = m_pVBackImg = NULL;
	m_pTopImg = m_pBottomImg = NULL;
	m_pLeftImg = m_pRightImg = NULL;
}

CZiScrollBar::~CZiScrollBar()
{
}


BEGIN_MESSAGE_MAP(CZiScrollBar, CStatic)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CZiScrollBar message handlers

void CZiScrollBar::OnPaint()
{
	CPaintDC dc(this); 

	if (m_nScrollStyle == SB_VERT) {
		DrawVScrollBar(&dc);
	} else if (m_nScrollStyle == SB_HORZ){
		DrawHScrollBar(&dc);
	}
}

void CZiScrollBar::OnDestroy()
{
	CStatic::OnDestroy();

	if (m_nScrollStyle == SB_VERT) {
		RenderEngine->RemoveImage(m_pVBackImg, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pVThumbImg, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pTopImg, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pBottomImg, RESOURCE_ID);
	} else if (m_nScrollStyle == SB_HORZ){
		RenderEngine->RemoveImage(m_pHBackImg, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pHThumbImg, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pLeftImg, RESOURCE_ID);
		RenderEngine->RemoveImage(m_pRightImg, RESOURCE_ID);
	}
}

BOOL CZiScrollBar::SetVScrollImg(UINT nBackImg, 
								 UINT nThumbImg, 
								 UINT nTopImg, 
								 UINT nBottomImg, 
								 LPCTSTR lpszFileType, 
								 LPRECT lpNinePart/*=NULL*/)
{
	RenderEngine->RemoveImage(m_pVBackImg, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pVThumbImg, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pTopImg, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pBottomImg, RESOURCE_ID);

	m_pVBackImg = RenderEngine->GetImage(nBackImg, lpszFileType);
	m_pVThumbImg = RenderEngine->GetImage(nThumbImg, lpszFileType);
	m_pTopImg = RenderEngine->GetImage(nTopImg, lpszFileType);
	m_pBottomImg = RenderEngine->GetImage(nBottomImg, lpszFileType);

	if (m_pVBackImg != NULL)
		m_pVBackImg->SetNinePart(lpNinePart);
	if (m_pVThumbImg != NULL)
		m_pVThumbImg->SetNinePart(lpNinePart);

	if ((nBackImg > 0 && m_pVBackImg != NULL) ||
		(nThumbImg > 0 && m_pVThumbImg != NULL) ||
		(nTopImg > 0 && m_pTopImg != NULL) ||
		(nBottomImg > 0 && m_pBottomImg != NULL)) 
		return FALSE;
	else 
		return TRUE;
}

BOOL CZiScrollBar::SetHScrollImg(UINT nBackImg, 
								 UINT nThumbImg, 
								 UINT nLeftImg, 
								 UINT nRightImg, 
								 LPCTSTR lpszFileType, 
								 LPRECT lpNinePart/*=NULL*/)
{
	RenderEngine->RemoveImage(m_pHBackImg, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pHThumbImg, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pLeftImg, RESOURCE_ID);
	RenderEngine->RemoveImage(m_pRightImg, RESOURCE_ID);

	m_pVBackImg = RenderEngine->GetImage(nBackImg, lpszFileType);
	m_pVThumbImg = RenderEngine->GetImage(nThumbImg, lpszFileType);
	m_pLeftImg = RenderEngine->GetImage(nLeftImg, lpszFileType);
	m_pRightImg = RenderEngine->GetImage(nRightImg, lpszFileType);

	if (m_pVBackImg != NULL)
		m_pVBackImg->SetNinePart(lpNinePart);
	if (m_pVThumbImg != NULL)
		m_pVThumbImg->SetNinePart(lpNinePart);

	if ((nBackImg > 0 && m_pVBackImg != NULL) ||
		(nThumbImg > 0 && m_pVThumbImg != NULL) ||
		(nLeftImg > 0 && m_pLeftImg != NULL) ||
		(nRightImg > 0 && m_pRightImg != NULL)) 
		return FALSE;
	else 
		return TRUE;
}

BOOL CZiScrollBar::SetScrollType(CWnd *pCtrl, UINT nStyle)
{
	if (pCtrl == NULL) 
		return FALSE;
//pCtrl: ListCtrl or ListIcon 	
	m_pCtrl = pCtrl;

	int cx, cy;
	if (nStyle == SB_VERT) {
		cx = ::GetSystemMetrics(SM_CXVSCROLL);
		cy = ::GetSystemMetrics(SM_CYVSCROLL);
	} else if (nStyle == SB_HORZ) {
		cx = ::GetSystemMetrics(SM_CXHSCROLL);
		cy = ::GetSystemMetrics(SM_CYHSCROLL);
	} else {
		return FALSE;
	}

	m_nScrollStyle = nStyle;

	CRect rcClient;
//Get the Rect of ListCtrl (relative to Desktop)
	pCtrl->GetWindowRect(&rcClient);
	pCtrl->ModifyStyle(0, WS_CLIPSIBLINGS);

//Get the Rect relative to Dialog 
	CWnd * pParent = pCtrl->GetParent();
	pParent->ScreenToClient(rcClient);

//Get the rect of ScrollBar	
	if (nStyle == SB_VERT) {
		rcClient.left = rcClient.right - cx;
	} else if (nStyle == SB_HORZ) {
		rcClient.top = rcClient.bottom - cy;
	}

	BOOL bRes = Create(NULL, WS_CHILD|SS_LEFT|WS_VISIBLE|WS_EX_TOPMOST, rcClient, pParent);

	if (!bRes) 
		return FALSE;

	UpdateScrollBar();
	return TRUE;
}


void CZiScrollBar::UpdateScrollBar()
{
	if (!IsWindow(m_hWnd) || m_pCtrl == NULL) 
		return;

	m_pCtrl->SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	SCROLLINFO sf;
	memset(&sf, 0, sizeof(SCROLLINFO));
	sf.cbSize = sizeof(SCROLLINFO);
	m_pCtrl->GetScrollInfo(m_nScrollStyle, &sf, SIF_ALL);
	if (sf.nPage < 0) {
		ShowWindow(SW_HIDE);
		return;
	}

	SCROLLBARINFO hscr;
	memset(&hscr, 0, sizeof(SCROLLBARINFO));
	hscr.cbSize = sizeof(SCROLLBARINFO);
	CRect rcScrollBar;

	if (m_nScrollStyle == SB_VERT) {
		::GetScrollBarInfo(m_pCtrl->m_hWnd, OBJID_VSCROLL, &hscr);
		rcScrollBar = CRect(hscr.rcScrollBar);
	} else if (m_nScrollStyle == SB_HORZ) {
		::GetScrollBarInfo(m_pCtrl->m_hWnd, OBJID_HSCROLL, &hscr);
		rcScrollBar = CRect(hscr.rcScrollBar);
	}

	GetParent()->ScreenToClient(&rcScrollBar);

	SetWindowPos(NULL, rcScrollBar.left, rcScrollBar.top, rcScrollBar.Width(), 
		rcScrollBar.Height(), SWP_SHOWWINDOW|SWP_NOZORDER);
	Invalidate(FALSE);
}

void CZiScrollBar::DrawVScrollBar(CDC *pDC)
{
	if(m_pCtrl == NULL)
	{
		return;
	}

	int cxButton     = ::GetSystemMetrics(SM_CXVSCROLL);
	int cyButton     = ::GetSystemMetrics(SM_CYVSCROLL);

	if(IsWindow(m_hWnd))
	{		
		SCROLLBARINFO vscr;
		memset(&vscr, 0, sizeof(SCROLLBARINFO));
		vscr.cbSize = sizeof(SCROLLBARINFO);
		if( ::GetScrollBarInfo(m_pCtrl->m_hWnd, OBJID_VSCROLL, &vscr) )
		{ 
			CRect rcVScrollBar(vscr.rcScrollBar);	

			int iWidth = vscr.dxyLineButton;
			int iThumbTop = vscr.xyThumbTop;
			int iThumbBottom = vscr.xyThumbBottom;

			if(rcVScrollBar.Height() < ::GetSystemMetrics(SM_CYVSCROLL)*2+1)
			{
				cyButton = (rcVScrollBar.Height() - 1)/2; 
			}

			CDC cMemDC;
			cMemDC.CreateCompatibleDC(pDC);

			CBitmap bmp;
			BITMAP bitmap;

			//The top arrow button
			bmp.LoadBitmap(IDB_VERTICLE_SCROLLBAR_UPARROW);
			bmp.GetBitmap(&bitmap);
			cMemDC.SelectObject(&bmp);
			pDC->StretchBlt(0, 0, cxButton, cyButton, &cMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

			//The bottom arrow button
			bmp.DeleteObject();
			bmp.LoadBitmap(IDB_VERTICLE_SCROLLBAR_DOWNARROW);
			bmp.GetBitmap(&bitmap);
			cMemDC.SelectObject(&bmp);
			pDC->StretchBlt(0, rcVScrollBar.Height() - cyButton, cxButton, cyButton, &cMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

			//The scroll bar itself
			bmp.DeleteObject();
			bmp.LoadBitmap(IDB_VERTICLE_SCROLLBAR_SPAN);
			cMemDC.SelectObject(&bmp);
			bmp.GetBitmap(&bitmap);
			pDC->StretchBlt(0, cyButton, rcVScrollBar.Width(), rcVScrollBar.Height() - 2*cyButton, &cMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

			if(rcVScrollBar.Height() <= SCROLLBAR_NORMAL_MINIMUM)
			{
				return;
			}

			//The thumb
			bmp.DeleteObject();
			bmp.LoadBitmap(IDB_VERTICLE_SCROLLBAR_SLIDER_TOP);
			bmp.GetBitmap(&bitmap);
			cMemDC.SelectObject(&bmp);
			pDC->StretchBlt(0, iThumbTop, iWidth, bitmap.bmHeight, &cMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight,SRCCOPY);

			bmp.DeleteObject();
			bmp.LoadBitmap(IDB_VERTICLE_SCROLLBAR_SLIDER_CENTER);
			bmp.GetBitmap(&bitmap);
			cMemDC.SelectObject(&bmp);
			pDC->StretchBlt(0 , iThumbTop + bitmap.bmHeight, iWidth, iThumbBottom - iThumbTop - 2*bitmap.bmHeight, &cMemDC, 0, 0,bitmap.bmWidth, bitmap.bmHeight,SRCCOPY);

			bmp.DeleteObject();
			bmp.LoadBitmap(IDB_VERTICLE_SCROLLBAR_SLIDER_BOTTOM);
			bmp.GetBitmap(&bitmap);
			cMemDC.SelectObject(&bmp);
			pDC->StretchBlt(0 , iThumbBottom - bitmap.bmHeight, iWidth, bitmap.bmHeight, &cMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight,SRCCOPY);


			bmp.DeleteObject();
			bmp.LoadBitmap(IDB_VERTICLE_SCROLLBAR_THUMB);
			bmp.GetBitmap(&bitmap);
			cMemDC.SelectObject(&bmp);
			pDC->StretchBlt(0, (iThumbTop + iThumbBottom)/2 - bitmap.bmHeight /2 , iWidth, bitmap.bmHeight, &cMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		}
	}

}

void CZiScrollBar::DrawHScrollBar(CDC *pDC)
{
	if(m_pCtrl == NULL)
	{
		return;
	}

	int cxButton     = ::GetSystemMetrics(SM_CXHSCROLL);
	int cyButton     = ::GetSystemMetrics(SM_CYHSCROLL);

	if(IsWindow(m_hWnd))
	{		
		SCROLLBARINFO hscr;
		memset(&hscr, 0, sizeof(SCROLLBARINFO));
		hscr.cbSize = sizeof(SCROLLBARINFO);
		if( ::GetScrollBarInfo(m_pCtrl->m_hWnd, OBJID_HSCROLL, &hscr) )
		{ 
			CRect rcHScrollBar(hscr.rcScrollBar);			

			int iHeigth = hscr.dxyLineButton;
			int iThumbLeft = hscr.xyThumbTop;
			int iThumbRight = hscr.xyThumbBottom;

			if(rcHScrollBar.Width() < ::GetSystemMetrics(SM_CXHSCROLL)*2+1)
			{
				cxButton = (rcHScrollBar.Width() - 1)/2; 
			}

			CDC cMemDC;
			cMemDC.CreateCompatibleDC(pDC);

			CBitmap bmp;
			BITMAP bitmap;

			//The left arrow button
			bmp.LoadBitmap(IDB_HORIZONTAL_SCROLLBAR_LEFTARROW);
			bmp.GetBitmap(&bitmap);
			cMemDC.SelectObject(&bmp);
			pDC->StretchBlt(0, 0, cxButton, cyButton, &cMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

			//The right arrow button
			bmp.DeleteObject();
			bmp.LoadBitmap(IDB_HORIZONTAL_SCROLLBAR_RIGHTARROW);
			bmp.GetBitmap(&bitmap);
			cMemDC.SelectObject(&bmp);
			pDC->StretchBlt(rcHScrollBar.Width() - cxButton, 0, cxButton, cyButton, &cMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

			//The scroll bar itself
			bmp.DeleteObject();
			bmp.LoadBitmap(IDB_HORIZONTAL_SCROLLBAR_SPAN);
			cMemDC.SelectObject(&bmp);
			bmp.GetBitmap(&bitmap);
			pDC->StretchBlt(cxButton, 0, rcHScrollBar.Width() - 2*cxButton, rcHScrollBar.Height(), &cMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

			if(rcHScrollBar.Width() <= SCROLLBAR_NORMAL_MINIMUM)
			{
				return;
			}

			//The thumb
			bmp.DeleteObject();
			bmp.LoadBitmap(IDB_HORIZONTAL_SCROLLBAR_SLIDER_LEFT);
			bmp.GetBitmap(&bitmap);
			cMemDC.SelectObject(&bmp);
			pDC->StretchBlt(iThumbLeft, 0, bitmap.bmWidth, iHeigth, &cMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight,SRCCOPY);

			bmp.DeleteObject();
			bmp.LoadBitmap(IDB_HORIZONTAL_SCROLLBAR_SLIDER_CENTER);
			bmp.GetBitmap(&bitmap);
			cMemDC.SelectObject(&bmp);
			pDC->StretchBlt(iThumbLeft + bitmap.bmWidth , 0, iThumbRight - iThumbLeft - 2*bitmap.bmWidth,iHeigth, &cMemDC, 0, 0,bitmap.bmWidth, bitmap.bmHeight,SRCCOPY);

			bmp.DeleteObject();
			bmp.LoadBitmap(IDB_HORIZONTAL_SCROLLBAR_SLIDER_RIGHT);
			bmp.GetBitmap(&bitmap);
			cMemDC.SelectObject(&bmp);
			pDC->StretchBlt(iThumbRight - bitmap.bmWidth , 0, bitmap.bmWidth, iHeigth, &cMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight,SRCCOPY);


			bmp.DeleteObject();
			bmp.LoadBitmap(IDB_HORIZONTAL_SCROLLBAR_THUMB);
			bmp.GetBitmap(&bitmap);
			cMemDC.SelectObject(&bmp);
			pDC->StretchBlt((iThumbLeft + iThumbRight)/2 - bitmap.bmWidth/2, 0, bitmap.bmWidth, iHeigth, &cMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		}
	}
}
