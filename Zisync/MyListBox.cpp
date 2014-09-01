// MyListBox.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "MyListBox.h"


// CMyListBox

IMPLEMENT_DYNAMIC(CMyListBox, CListBox)

CMyListBox::CMyListBox()
{
	m_nItemHeight = 12;
}

CMyListBox::~CMyListBox()
{
}


BEGIN_MESSAGE_MAP(CMyListBox, CListBox)
END_MESSAGE_MAP()



// CMyListBox message handlers




void CMyListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
		lpMeasureItemStruct->itemHeight = m_nItemHeight;
}


void CMyListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	bool bIsSel = lpDrawItemStruct->itemState&ODS_SELECTED;
	CRect rcItem = lpDrawItemStruct->rcItem;

	pDC->FillSolidRect(rcItem, bIsSel? RGB(255,0,0):RGB(0,255,0));
	CString	strItemText;
	GetText(lpDrawItemStruct->itemID, strItemText);

	pDC->SetTextColor(bIsSel? RGB(0, 0, 255) : RGB(0, 0, 0));

	CFont font, * oldFont;
	font.CreateFont(18,0,0,0,FW_NORMAL,0,FALSE,0,0,0,0,0,0,TEXT("Î¢ÈíÑÅºÚ"));
	oldFont = pDC->SelectObject(&font);

	pDC->DrawText(strItemText, CRect(rcItem.left+10, rcItem.top+9,
		rcItem.right-10, rcItem.bottom), DT_LEFT|DT_VCENTER);
	pDC->SelectObject(oldFont);
}


int CMyListBox::CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/)
{

	// TODO:  Add your code to determine the sorting order of the specified items
	// return -1 = item 1 sorts before item 2
	// return 0 = item 1 and item 2 sort the same
	// return 1 = item 1 sorts after item 2

	return 0;
}

void CMyListBox::SetItemHeight(int nItemHeight)
{
	m_nItemHeight = nItemHeight;
}
