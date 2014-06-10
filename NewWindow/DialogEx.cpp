// DialogEx.cpp : implementation file
//

#include "stdafx.h"
#include "NewWindow.h"
#include "DialogEx.h"
#include "afxdialogex.h"

const INT  nTitleHeight = 33;
const INT  nFrameBorerL = 2;  //Left;
const INT  nFrameBorerR = 2;  //Right;
const INT  nFrameBorerB = 2;  //Bottom;

// CDialogEx dialog

IMPLEMENT_DYNAMIC(CMyDialogEx, CDialog)

CMyDialogEx::CMyDialogEx(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{

}

CMyDialogEx::~CMyDialogEx()
{
}

void CMyDialogEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialogEx, CDialog)
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
END_MESSAGE_MAP()


// CDialogEx message handlers


void CMyDialogEx::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CDialog::OnNcPaint() for painting messages
	CWindowDC dc(this);
	DrawTitleBar(&dc);
}


void CMyDialogEx::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	lpncsp->rgrc[0].top += nTitleHeight-GetSystemMetrics(SM_CYCAPTION) -
		GetSystemMetrics(SM_CYSIZEFRAME);

	lpncsp->rgrc[0].left += nFrameBorerL- GetSystemMetrics(SM_CXFRAME);
	lpncsp->rgrc[0].right -= nFrameBorerR - GetSystemMetrics(SM_CXSIZEFRAME);
	 lpncsp->rgrc[0].bottom -=nFrameBorerB-GetSystemMetrics(SM_CYSIZEFRAME);

	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}


BOOL CMyDialogEx::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadImageFromResource(&m_ImageTitleL, IDB_TITLE_LEFT, _T("PNG"));
	LoadImageFromResource(&m_ImageTitleM, IDB_TITLE_MEDIUM, _T("PNG"));
	LoadImageFromResource(&m_ImageTitleM_Spe, IDB_TITLE_MSEP, _T("PNG"));
	LoadImageFromResource(&m_ImageTitleR, IDB_TITLE_RIGHT, _T("PNG"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDialogEx::DrawTitleBar(CDC *pDC)
{
	if (GetSafeHwnd() == NULL) return;   //1

	CRect rtWnd ,rtTile, rtButtons;
	GetWindowRect(&rtWnd);

	rtTile.SetRect(0, 0, rtWnd.right, nTitleHeight);

	if (!m_ImageTitleL.IsNull()) {
		m_ImageTitleL.BitBlt(pDC->GetSafeHdc(), 0, 0);  //2

		for (INT nXPos = m_ImageTitleL.GetWidth(); nXPos < rtWnd.Width(); 
			nXPos += m_ImageTitleM.GetWidth()) 
		{
			m_ImageTitleM.BitBlt(pDC->GetSafeHdc(), nXPos, 0);
		}

		m_ImageTitleM_Spe.BitBlt(pDC->GetSafeHdc(), 
			(rtWnd.Width() - m_ImageTitleM_Spe.GetWidth()/2), 0);

		m_ImageTitleR.BitBlt(pDC->GetSafeHdc(), 
			rtWnd.Width() - m_ImageTitleR.GetWidth(), 0);

	}

	//左边框
	CPoint point;
	point.x = nFrameBorerL;
	point.y = rtWnd.Height();
	pDC->FillSolidRect(0, nTitleHeight, point.x, point.y, RGB(10,10,10));

	//下边框
	point.x = rtWnd.Width();
	point.y = nFrameBorerB;
	pDC->FillSolidRect(0, rtWnd.Height()-point.y, point.x, point.y, RGB(20,20,20));

	//右边框
	point.x = nFrameBorerR;
	point.y = rtWnd.Height();
	pDC->FillSolidRect(rtWnd.Width()- point.x, nTitleHeight, point.x, point.y, 
		RGB(30,30,30));
}


BOOL CMyDialogEx::LoadImageFromResource(ATL::CImage *pImage, UINT nResID,LPCTSTR lpTyp)
{
	if( pImage ==NULL)return false;

	pImage->Destroy();

	// 查找资源
	HRSRC hRsrc =::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if(hRsrc ==NULL)return false;

	// 加载资源
	HGLOBAL hImgData =::LoadResource(AfxGetResourceHandle(), hRsrc);
	if(hImgData ==NULL)
	{
		::FreeResource(hImgData);
		return false;
	}

	// 锁定内存中的指定资源
	LPVOID lpVoid    =::LockResource(hImgData);

	LPSTREAM pStream =NULL;
	DWORD dwSize    =::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew    =::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte    =(LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);

	// 解除内存中的指定资源
	::GlobalUnlock(hNew);

	// 从指定内存创建流对象
	HRESULT ht =::CreateStreamOnHGlobal(hNew,TRUE,&pStream);
	if( ht != S_OK )
	{
		GlobalFree(hNew);
	}
	else
	{
		// 加载图片
		pImage->Load(pStream);

		GlobalFree(hNew);
	}
	// 释放资源
	::FreeResource(hImgData);
	return true;
}