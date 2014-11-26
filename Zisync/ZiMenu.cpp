// ZiMenu.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "ZiMenu.h"
#include "MemoryDC.h"
#include "RenderManager.h"
// CZiMenu

IMPLEMENT_DYNAMIC(CZiMenu, CStatic)

CZiMenu::CZiMenu()
{

}

CZiMenu::~CZiMenu()
{
}

BEGIN_MESSAGE_MAP(CZiMenu, CStatic)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CZiMenu message handlers


void CZiMenu::OnPaint()
{
	CPaintDC dc(this); 
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemoryDC MemDC(&dc, rcClient);

	CBrush Brush(RGB(125, 125, 125));
	MemDC->FillRect(rcClient, &Brush);
}


void CZiMenu::OnDestroy()
{
	CStatic::OnDestroy();
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

void CZiMenu::AppendMenuItem(UINT nImageID, LPCTSTR lpszImageType, LPCTSTR lpszText, BOOL bHasChild, BOOL bIsSeparator)
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

void CZiMenu::SetItemHeight(int nHeight)
{
	m_nItemHeight = nHeight;
	SetWindowPos(NULL, 0, 0, 100, nHeight * m_MenuItem.size(), SWP_NOMOVE);
}
