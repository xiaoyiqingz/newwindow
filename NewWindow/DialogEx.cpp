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

CONST INT	nCloseWidth=36; //closeͼ��Ŀ�� 
CONST INT	nMaxWidth=29;   //maxͼ��Ŀ��
CONST INT	nMinWidth=29;   //minͼ��Ŀ��
CONST INT   nSetWidth=16;   //set

//��ť��ʶ
#define  BST_CLOSE			0
#define  BST_MAX_SIZE		1
#define  BST_MIN_SIZE		2
#define  BST_SET			3

//��ť״̬
#define  BUT_EXIST			0x01
#define  BUT_NORMAL			0x02
#define  BUT_DISABLE		0x04

//��Ч��ֵ
#define  INVALID_BYTE		((BYTE)(0xFF))
//����ά��
#define  CountArray(Array)  (sizeof(Array)/sizeof(Array[0]))

// CDialogEx dialog

IMPLEMENT_DYNAMIC(CMyDialogEx, CDialog)

CMyDialogEx::CMyDialogEx(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	//��ť״̬
	m_cbNowButtonIndex=INVALID_BYTE;
	ZeroMemory(m_cbNowHotIndex,sizeof(m_cbNowHotIndex));
	ZeroMemory(m_cbButtonState,sizeof(m_cbButtonState));
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
	ON_WM_NCACTIVATE()
	ON_WM_SIZE()
	ON_WM_NCMOUSEMOVE()
//	ON_WM_MOUSELEAVE()
ON_WM_NCMOUSELEAVE()
ON_WM_NCLBUTTONDOWN()
ON_WM_NCLBUTTONUP()
END_MESSAGE_MAP()


// CDialogEx message handlers


void CMyDialogEx::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CDialog::OnNcPaint() for painting messages
	CWindowDC dc(this);
	DrawTitleBar(&dc);
	DrawTitleButton(&dc);
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

	HINSTANCE hInstance = AfxGetInstanceHandle();

	LoadImageFromResource(&m_ImageTitleL, IDB_TITLE_LEFT, _T("PNG"));
	LoadImageFromResource(&m_ImageTitleM, IDB_TITLE_MEDIUM, _T("PNG"));
	LoadImageFromResource(&m_ImageTitleM_Spe, IDB_TITLE_MSEP, _T("PNG"));
	LoadImageFromResource(&m_ImageTitleR, IDB_TITLE_RIGHT, _T("PNG"));

	m_ImageBt_Close.LoadFromResource(hInstance, IDB_TITLE_CLOSE);
	m_ImageBt_Max.LoadFromResource(hInstance, IDB_TITLE_MAX);
	m_ImageBt_Min.LoadFromResource(hInstance, IDB_TITLE_MIN);
	m_ImageBt_Res.LoadFromResource(hInstance, IDB_TITLE_RESTORE);
	m_ImageBt_Set.LoadFromResource(hInstance, IDB_TITLE_SET);

	m_cbNowButtonIndex = INVALID_BYTE;
	ZeroMemory(m_cbNowHotIndex, sizeof(m_cbNowHotIndex));
	ZeroMemory(m_cbButtonState,  sizeof(m_cbButtonState));

	m_cbButtonState[BST_CLOSE] = BUT_EXIST | BUT_NORMAL;
	m_cbButtonState[BST_MAX_SIZE] = BUT_EXIST | BUT_NORMAL;
	m_cbButtonState[BST_MIN_SIZE] = BUT_EXIST | BUT_NORMAL;
/*	m_cbButtonState[BST_SET] = BUT_EXIST | BUT_NORMAL;*/
	return TRUE;  

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
			(rtWnd.Width() - m_ImageTitleM_Spe.GetWidth())/2, 0);

		m_ImageTitleR.BitBlt(pDC->GetSafeHdc(), 
			rtWnd.Width() - m_ImageTitleR.GetWidth(), 0);

	}

	//��߿�
	CPoint point;
	point.x = nFrameBorerL;
	point.y = rtWnd.Height();
	pDC->FillSolidRect(0, nTitleHeight, point.x, point.y, RGB(255,0,0));

	//�±߿�
	point.x = rtWnd.Width();
	point.y = nFrameBorerB;
	pDC->FillSolidRect(0, rtWnd.Height()-point.y, point.x, point.y, RGB(0,255,0));

	//�ұ߿�
	point.x = nFrameBorerR;
	point.y = rtWnd.Height();
	pDC->FillSolidRect(rtWnd.Width()- point.x, nTitleHeight, point.x, point.y, 
		RGB(0,0,255));
}

void CMyDialogEx::DrawTitleButton(CDC * pDC)
{
	if( !m_ImageBt_Close.IsNull() )	
		m_ImageBt_Close.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_CLOSE].left,
		m_rcButton[BST_CLOSE].top,m_rcButton[BST_CLOSE].Width(),
		m_rcButton[BST_CLOSE].Height(),m_cbNowHotIndex[0]*m_rcButton[BST_CLOSE].Width(),0); // m_cbNowHotIndexȷ��������ʾͼƬ��״̬���ڼ���*�������

	if (IsZoomed())
	{
		if( !m_ImageBt_Res.IsNull() )	
			m_ImageBt_Res.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_MAX_SIZE].left,
			m_rcButton[BST_MAX_SIZE].top,m_rcButton[BST_MAX_SIZE].Width(),
			m_rcButton[BST_MAX_SIZE].Height(),m_cbNowHotIndex[1]*m_rcButton[BST_MAX_SIZE].Width(),0);
	}
	else
	{
		if( !m_ImageBt_Max.IsNull() )	
			m_ImageBt_Max.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_MAX_SIZE].left,
			m_rcButton[BST_MAX_SIZE].top,m_rcButton[BST_MAX_SIZE].Width(),
			m_rcButton[BST_MAX_SIZE].Height(),m_cbNowHotIndex[1]*m_rcButton[BST_MAX_SIZE].Width(),0);
	}

	if( !m_ImageBt_Min.IsNull() )	
		m_ImageBt_Min.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_MIN_SIZE].left,
		m_rcButton[BST_MIN_SIZE].top,m_rcButton[BST_MIN_SIZE].Width(),
		m_rcButton[BST_MIN_SIZE].Height(),m_cbNowHotIndex[2]*m_rcButton[BST_MIN_SIZE].Width(),0);

/*
	if( !m_ImageBt_Set.IsNull() )	
		m_ImageBt_Set.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_SET].left,
		m_rcButton[BST_SET].top,m_rcButton[BST_SET].Width(),
		m_rcButton[BST_SET].Height(),m_cbNowHotIndex[3]*m_rcButton[BST_SET].Width(),0);*/
}

BOOL CMyDialogEx::LoadImageFromResource(ATL::CImage *pImage, UINT nResID,LPCTSTR lpTyp)
{
	if( pImage ==NULL)return false;

	pImage->Destroy();

	// ������Դ
	HRSRC hRsrc =::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if(hRsrc ==NULL)return false;

	// ������Դ
	HGLOBAL hImgData =::LoadResource(AfxGetResourceHandle(), hRsrc);
	if(hImgData ==NULL)
	{
		::FreeResource(hImgData);
		return false;
	}

	// �����ڴ��е�ָ����Դ
	LPVOID lpVoid    =::LockResource(hImgData);

	LPSTREAM pStream =NULL;
	DWORD dwSize    =::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew    =::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte    =(LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);

	// ����ڴ��е�ָ����Դ
	::GlobalUnlock(hNew);

	// ��ָ���ڴ洴��������
	HRESULT ht =::CreateStreamOnHGlobal(hNew,TRUE,&pStream);
	if( ht != S_OK )
	{
		GlobalFree(hNew);
	}
	else
	{
		// ����ͼƬ
		pImage->Load(pStream);

		GlobalFree(hNew);
	}
	// �ͷ���Դ
	::FreeResource(hImgData);
	return true;
}

LRESULT CMyDialogEx::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT lrst = CDialog::DefWindowProc(message, wParam, lParam);

	if (!::IsWindow(m_hWnd)) 
		return lrst;

	if (message == WM_MOVE || message == WM_PAINT || message == WM_NCPAINT
		|| message == WM_NOTIFY) 
	{
		OnNcPaint();
	}

	return lrst;
//	return CDialog::DefWindowProc(message, wParam, lParam);
}


BOOL CMyDialogEx::OnNcActivate(BOOL bActive)
{
	OnNcPaint();
	return TRUE;  //�����ڱ���Ҫreturn TRUE;���˵�����CDialog��OnNcActivate
//	return CDialog::OnNcActivate(bActive);
}


void CMyDialogEx::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	INT nYPos = 1;
	INT nXpos = cx - nCloseWidth;
	
	m_rcButton[BST_CLOSE].SetRect(nXpos, nYPos, nXpos+nCloseWidth, nYPos+31);  //setrect ���þ��ε�����
	m_rcButton[BST_MAX_SIZE].SetRect(nXpos - nMaxWidth, nYPos, nXpos, nYPos+31);
	m_rcButton[BST_MIN_SIZE].SetRect(nXpos- nMaxWidth- nMaxWidth, nYPos, 
		nXpos-nMaxWidth, nYPos+31);
	/*m_rcButton[BST_SET].SetRect(nXpos- nMaxWidth- nMaxWidth - nSetWidth, nYPos + 10, 
		nXpos-nMaxWidth- nMaxWidth, nYPos + 26);*/
}


void CMyDialogEx::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	point.Offset(-rcWindow.left, -rcWindow.top);

	for (INT i = 0; i < CountArray(m_cbButtonState); i++) {
		if ((m_cbButtonState[i]&BUT_EXIST)&&(m_rcButton[i].PtInRect(point)))  //�ж�һ�����Ƿ��ھ�����
		{
			if (m_cbNowButtonIndex == i) return;

			if (m_cbNowButtonIndex != INVALID_BYTE) {
				m_cbNowHotIndex[m_cbNowButtonIndex] = en_Normal;
			}

			if ((m_cbButtonState[i]&BUT_EXIST) && (!(m_cbButtonState[i]&BUT_DISABLE)))
			{
				m_cbNowButtonIndex = i;
				m_cbNowHotIndex[i] = en_Hoven;
			}

			CDC *pDC =GetWindowDC();
			DrawTitleButton(pDC);
			ReleaseDC(pDC);
			return;
		}
	}

	if (m_cbNowButtonIndex !=INVALID_BYTE) 
	{
		m_cbNowButtonIndex = INVALID_BYTE;
		ZeroMemory(&m_cbNowHotIndex, sizeof(m_cbNowHotIndex));

		CDC *pDC = GetWindowDC();
		DrawTitleButton(pDC);
		ReleaseDC(pDC);
	}

	CDialog::OnNcMouseMove(nHitTest, point);
}

void CMyDialogEx::OnNcMouseLeave()
{
	if(m_cbNowButtonIndex != INVALID_BYTE) 
	{
		m_cbNowButtonIndex = INVALID_BYTE;
		ZeroMemory(&m_cbNowHotIndex, sizeof(m_cbNowHotIndex));
		CDC *pDC = GetWindowDC();
		DrawTitleButton(pDC);
		ReleaseDC(pDC);
	}

	CDialog::OnNcMouseLeave();
}


void CMyDialogEx::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	//��pointת��Ϊ��������
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	point.Offset(-rcWindow.left,-rcWindow.top);

	//��ť����
	for (INT i=0;i<CountArray(m_cbButtonState);i++)
	{
		if ((m_cbButtonState[i]&BUT_EXIST)&&(m_rcButton[i].PtInRect(point)))
		{
			//���״̬
			if (m_cbNowButtonIndex!=INVALID_BYTE)
			{
				m_cbNowHotIndex[m_cbNowButtonIndex]=en_Normal;
			}

			//����״̬
			if ((m_cbButtonState[i]&BUT_EXIST)&&(!(m_cbButtonState[i]&BUT_DISABLE)))
			{
				m_cbNowButtonIndex=i;
				m_cbNowHotIndex[i] = en_Press;
			}

			CDC *pDC = GetWindowDC();
			DrawTitleButton(pDC);
			ReleaseDC(pDC);

			return;
		}
	}

	//������
	if (m_cbNowButtonIndex!=INVALID_BYTE)
	{
		//���ñ���
		m_cbNowButtonIndex=INVALID_BYTE;
		ZeroMemory(&m_cbNowHotIndex,sizeof m_cbNowHotIndex);

		CDC *pDC = GetWindowDC();
		DrawTitleButton(pDC);
		ReleaseDC(pDC);
	}

	CDialog::OnNcLButtonDown(nHitTest, point);
}


void CMyDialogEx::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	point.Offset(-rcWindow.left,-rcWindow.top);

	//��ť����
	for (INT i=0;i<CountArray(m_cbButtonState);i++)
	{
		if ((m_cbButtonState[i]&BUT_EXIST)&&(m_rcButton[i].PtInRect(point)))
		{
			//����״̬
			if ((m_cbButtonState[i]&BUT_EXIST)&&(!(m_cbButtonState[i]&BUT_DISABLE)))
			{
				switch (i)
				{
				case 0:
					SendMessage(WM_CLOSE);
					break;
				case 1:
					if (IsZoomed())
						SendMessage(WM_SYSCOMMAND, SC_RESTORE,
						MAKELPARAM(point.x, point.y));
					else SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE,
						MAKELPARAM(point.x, point.y));

					break;
				case 2:
					SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 
						MAKELPARAM(point.x, point.y));
					break;
/*
				case 3:
					MessageBox(_T("����"));*/
				}
			}

			m_cbNowButtonIndex=INVALID_BYTE;
			ZeroMemory(&m_cbNowHotIndex,sizeof m_cbNowHotIndex);

			CDC *pDC = GetWindowDC();
			DrawTitleButton(pDC);
			ReleaseDC(pDC);

			return;
		}
	}

	CDialog::OnNcLButtonUp(nHitTest, point);
}
