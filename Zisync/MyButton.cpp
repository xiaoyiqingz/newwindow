// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{
	m_bExpand = true;
	m_bHovering = false;
	m_crTextColor = RGB(0, 0, 0); 
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()



// CMyButton message handlers




void CMyButton::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	CButton::PreSubclassWindow();
	SetButtonStyle(GetButtonStyle()|BS_OWNERDRAW);

}


int CMyButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetButtonStyle(GetButtonStyle() | BS_OWNERDRAW);
	// TODO:  Add your specialized creation code here

	return 0;
}


bool CMyButton::SetButtonImage(LPCTSTR pszFilePath, bool bExpandImage/*=false*/)
{
	ASSERT(pszFilePath);
	if (pszFilePath==NULL) return false;

	m_bExpand=bExpandImage;
	m_ImageBack.Load(pszFilePath);

	if (m_bExpand==false) FixButtonSize();
	if (GetSafeHwnd()) Invalidate(FALSE);

	return true;
}

bool CMyButton::SetButtonImage(HINSTANCE hInstance, LPCTSTR pszResourceName, LPCTSTR pszType, bool bExpandImage/*=false*/)
{
	ASSERT(pszResourceName!=0);
	if (pszResourceName==NULL) return false;

	m_bExpand=bExpandImage;
	m_ImageBack.LoadImage(hInstance,pszResourceName,pszType);

	//调整位置
	if (m_bExpand==false) FixButtonSize();
	if (GetSafeHwnd()) Invalidate(FALSE);

	return true;
}

bool CMyButton::FixButtonSize()
{
	if (!m_ImageBack.IsNull() && GetSafeHwnd()) 
	{
		SetWindowPos(NULL, 0, 0, m_ImageBack.GetWidth()/4, 
			m_ImageBack.GetHeight(), SWP_NOMOVE);  //SWP_NOMOVE 保留当前位置(忽略x和y)
		return true;
	}
	return false;
}

void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bHovering == false) 
	{
		m_bHovering = true;
		Invalidate(FALSE);
		TRACKMOUSEEVENT TrackMouseEvent;
		TrackMouseEvent.cbSize=sizeof(TrackMouseEvent);
		TrackMouseEvent.dwFlags=TME_LEAVE;
		TrackMouseEvent.hwndTrack=GetSafeHwnd();
		TrackMouseEvent.dwHoverTime=HOVER_DEFAULT;
		_TrackMouseEvent(&TrackMouseEvent);  //TrackMouseEvent *
	}
	CButton::OnMouseMove(nFlags, point);
}


LRESULT CMyButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	// TODO: Add your message handler code here and/or call default
	m_bHovering = false;
	Invalidate(FALSE);
	
	return 0;
}

bool CMyButton::SetTextColor(COLORREF crTextColor)
{
	m_crTextColor = crTextColor;
	if (GetSafeHwnd()) Invalidate(FALSE);
	
	return true;
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//定义变量
	CRect rcClient;
	GetClientRect(&rcClient);
	bool bDisable=((lpDrawItemStruct->itemState&ODS_DISABLED)!=0);
	bool bButtonDown=((lpDrawItemStruct->itemState&ODS_SELECTED)!=0);

	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	//获取文字
	CString strText;
	GetWindowText(strText);

	//绘制父窗口背景
	CRect rcWindow;
	CClientDC clDC(GetParent());

	GetWindowRect(rcWindow);
	GetParent()->ScreenToClient(rcWindow);

	CDC dcParent;
	CBitmap bmp,*pOldBitmap;
	dcParent.CreateCompatibleDC(&clDC);
	bmp.CreateCompatibleBitmap(&clDC,rcClient.Width(),rcClient.Height());
	pOldBitmap = dcParent.SelectObject(&bmp);
	dcParent.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&clDC,rcWindow.left,rcWindow.top,SRCCOPY);
	bmp.DeleteObject();

	//加载背景图
	if ( !m_ImageBack.IsNull() )
	{
		//计算位图位置
		int nWidth=m_ImageBack.GetWidth()/4,nDrawPos=0;
		if (bDisable) nDrawPos=nWidth*3;
		else if (bButtonDown) nDrawPos=nWidth*2;
		else if (m_bHovering) nDrawPos=nWidth*1;

		//绘画背景图
		if (m_bExpand==false) m_ImageBack.TransDrawImage(pDC,0,0,rcClient.Width(),rcClient.Height(),nDrawPos,0, RGB(255, 255,255));
		else m_ImageBack.Draw(pDC->GetSafeHdc(), 0, 0, rcClient.Width(), rcWindow.Height(), nDrawPos, 0, nWidth, m_ImageBack.GetHeight());
	}
	else
	{
		//绘画默认界面
		pDC->FillSolidRect(&rcClient,GetSysColor(COLOR_BTNFACE));
		if (bButtonDown) pDC->Draw3dRect(&rcClient,GetSysColor(COLOR_WINDOWFRAME),GetSysColor(COLOR_3DHILIGHT));
		else pDC->Draw3dRect(&rcClient,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_WINDOWFRAME));
	}

	//绘画字体
	rcClient.top+=1;
	pDC->SetBkMode(TRANSPARENT);
	if (bDisable) pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
	else pDC->SetTextColor(m_crTextColor);
	pDC->DrawText(strText,strText.GetLength(),rcClient,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

	return;
}

BOOL CMyButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}
