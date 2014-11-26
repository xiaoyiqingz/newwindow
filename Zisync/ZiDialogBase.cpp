#include "StdAfx.h"
#include "ZiDialogBase.h"
#include "RenderManager.h"
#include "UI/SkinUI_ScrollBar.h"

ZiDialogBase::ZiDialogBase(void)
{
	m_hParentDC = NULL;
	m_bTransparent = FALSE;
	m_colDefText = RGB(128,128,128);
	m_colNormalText = RGB(0,0,0);
	m_colDisableText = RGB(128,128,128);
	m_colReadOnlyText = RGB(0,0,0);
	m_colSelectText = RGB(255,255,255);
	m_colFrameNormal = RGB(0,0,0);
	m_colBack=RGB(255,255,255);
	m_Font = RenderEngine->GetDeaultFont();
}

ZiDialogBase::~ZiDialogBase(void)
{
	m_bTransparent = FALSE;
}

void ZiDialogBase::CalcCenterRect( RECT& rcDest, int cx, int cy, RECT& rcCenter )
{
	int x = ((rcDest.right-rcDest.left) - cx + 1) / 2;
	int y = ((rcDest.bottom-rcDest.top) - cy + 1) / 2;

	rcCenter.left = rcDest.left+x;
	rcCenter.top = rcDest.top+y;
	rcCenter.right = rcCenter.left+cx;
	rcCenter.bottom = rcCenter.top+cy;
}

void ZiDialogBase::DrawParentWndBg(HWND hWnd, HDC hDC )
{
	if( hWnd == NULL ) return;
	if ( !m_bTransparent ) return;

	HWND hParentWnd = ::GetParent(hWnd);

	CRect rcWindow;
	::GetWindowRect(hWnd,&rcWindow);
	::ScreenToClient(hParentWnd, (LPPOINT)&rcWindow); 
	::ScreenToClient(hParentWnd, ((LPPOINT)&rcWindow)+1);

	::BitBlt(hDC, 0, 0, rcWindow.Width(), rcWindow.Height(), m_hParentDC, rcWindow.left, rcWindow.top, SRCCOPY);
}

void ZiDialogBase::SetDefText( COLORREF colText )
{
	m_colDefText = colText;
}

void ZiDialogBase::SetNormalText( COLORREF colText )
{
	m_colNormalText = colText;
}

void ZiDialogBase::SetDisableText( COLORREF colText )
{
	m_colDisableText = colText;
}

void ZiDialogBase::SetSelectText( COLORREF colText )
{
	m_colSelectText = colText;
}

void ZiDialogBase::SetFrameColor( COLORREF colFrame )
{
	m_colFrameNormal = colFrame;
}


BOOL ZiDialogBase::SetScrollImage( CWnd * pOwn,UINT nResID, LPCTSTR lpszFileType/*LPCTSTR pszFileName*/ )
{
/*	RenderEngine->RemoveImage(m_pImageScroll);
	m_pImageScroll = RenderEngine->GetImage(pszFileName);*/

	RenderEngine->RemoveImage(m_pImageScroll, RESOURCE_ID);
	m_pImageScroll = RenderEngine->GetImage(nResID, lpszFileType);

	if ( (m_pImageScroll != NULL) && (pOwn != NULL) && (pOwn->GetSafeHwnd() != NULL) )
	{
		ASSERT(m_pImageScroll != NULL);
		if( m_pImageScroll == NULL) return FALSE;

		//ÉèÖÃ¹ö¶¯
//		SkinUI_Init(pOwn->GetSafeHwnd(),m_pImageScroll->ImageToBitmap());
	}

	return TRUE;
}

void ZiDialogBase::RemoveScorll()
{
//	RenderEngine->RemoveImage(m_pImageScroll);
	RenderEngine->RemoveImage(m_pImageScroll, RESOURCE_ID);
}

BOOL ZiDialogBase::TrackMouseLeave( HWND hWnd )
{
	TRACKMOUSEEVENT tme = { 0 };
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = hWnd;

	return _TrackMouseEvent(&tme);
}

void ZiDialogBase::SetCtrlFont( HFONT hFont )
{
	m_Font = hFont;
}

HFONT ZiDialogBase::GetCtrlFont()
{
	return m_Font;
}

void ZiDialogBase::SetBackColor( COLORREF colBack )
{
	m_colBack = colBack;
}

void ZiDialogBase::SetUnTransparent()
{
	m_bTransparent  = false;
}
