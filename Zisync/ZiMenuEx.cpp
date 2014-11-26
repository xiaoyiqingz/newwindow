// ZiMenuEx.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "ZiMenuEx.h"
#include "MemoryDC.h"
#include "RenderManager.h"

// CZiMenuEx

IMPLEMENT_DYNAMIC(CZiMenuEx, CWnd)

CZiMenuEx::CZiMenuEx()
{

}

CZiMenuEx::~CZiMenuEx()
{
}


BEGIN_MESSAGE_MAP(CZiMenuEx, CWnd)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CZiMenuEx message handlers




void CZiMenuEx::OnPaint()
{
	CPaintDC dc(this); 
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemoryDC MemDC(&dc, rcClient);

	CBrush Brush(RGB(125, 125, 125));
	MemDC->FillRect(rcClient, &Brush);
}


void CZiMenuEx::OnDestroy()
{
	CWnd::OnDestroy();
	
	CMenuItem::iterator iter = m_MenuItem.begin();
	for (; iter != m_MenuItem.end(); iter++) {
		if (iter->pImage != NULL) {
			RenderEngine->RemoveImage(iter->pImage, RESOURCE_ID);
		}
		if (iter->lpszStr != NULL) {
			free(&iter->lpszStr);
			iter->lpszStr = NULL;
		}
	}
	m_MenuItem.clear();
}

void CZiMenuEx::AppendMenuItem(UINT nImageID, LPCTSTR lpszImageType, LPCTSTR lpszText, BOOL bHasChild/*=NULL*/, BOOL bIsSeparator/*=NULL*/)
{
	tagMenuItem MenuItem;
	if (bIsSeparator) {
		MenuItem.bIsSeparator = TRUE;
		MenuItem.bHasChild = FALSE;
		MenuItem.lpszStr = NULL;
		MenuItem.pImage = NULL;
	} else {
		MenuItem.bIsSeparator = FALSE;
		MenuItem.bHasChild = bHasChild;
		MenuItem.lpszStr = _tcsdup(lpszText);
		MenuItem.pImage = RenderEngine->GetImage(nImageID, lpszImageType);
	}
	m_MenuItem.push_back(MenuItem);
}

void CZiMenuEx::SetItemHeight(int nHeight)
{
	m_nItemHeight = nHeight;
	SetWindowPos(NULL, 0, 0, 100, nHeight * m_MenuItem.size(), SWP_NOMOVE);
}
