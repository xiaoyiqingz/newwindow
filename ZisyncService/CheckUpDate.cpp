// CheckUpDate.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "CheckUpDate.h"
#include "afxdialogex.h"


// CCheckUpDate dialog

IMPLEMENT_DYNAMIC(CCheckUpDate, CMyDialog)

CCheckUpDate::CCheckUpDate(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCheckUpDate::IDD, pParent)
{
	InitializeGIF();
}

CCheckUpDate::~CCheckUpDate()
{
	DestroyGif();
}

void CCheckUpDate::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GIF, m_btGif);
}


BEGIN_MESSAGE_MAP(CCheckUpDate, CMyDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CCheckUpDate message handlers

BOOL CCheckUpDate::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	m_ImageBack.LoadImage(AfxGetInstanceHandle(), IDB_UPDATE_BACK, _T("PNG"));
	m_ImageWaiting.LoadImage(_T("res\\hearts.gif"));
	
	m_pImage = Image::FromFile(_T("res\\hearts.gif"));

	SetWindowPos(NULL, 0, 0, 400, 220, SWP_NOMOVE);

	CRect rcControl(0, 0, 0, 0);
	HDC hParentDC = GetBackDC();
	m_btClose.Create(NULL,  WS_CHILD | WS_VISIBLE, rcControl, this, IDCANCEL);
	m_btClose.SetBackImage(_T("res\\close1.png"), _T("res\\close2.png"), 
		_T("res\\close3.png"), _T("res\\close4.png"));
	m_btClose.SetButtonType(BT_PUSHBUTTON);
	m_btClose.SetParentBack(hParentDC);
	m_btClose.SetSize(18 ,18);
	CRect rcClient;
	GetClientRect(&rcClient);
	SetControlPos(rcClient.Width(), rcClient.Height());
	

	m_btGif.SetBackImage(IDR_GIF, 0, 0, 0, _T("GIF"));
	m_btGif.SetButtonType(BT_GIFBUTTON);
	m_btGif.SetParentBack(hParentDC);
	m_btGif.SetSize(m_pImage->GetWidth(), m_pImage->GetHeight());

	return TRUE;
}


void CCheckUpDate::DrawClientArea(CDC*pDC,int nWidth,int nHeight)
{
	m_ImageBack.Draw(pDC, 0, 0, nWidth, nHeight, 0, 0, 0, 0);
	
	CRect rcImage, rcClient(0, 0, nWidth, nHeight);
	int cx = m_ImageWaiting.GetWidth();
	int cy = m_ImageWaiting.GetHeight();
	CalcCenterRect(rcClient, cx, cy, rcImage);
	m_pDC = pDC;

//	m_ImageWaiting.Draw(pDc, rcImage);
//	m_ImageWaiting.DrawFrameGIF(&dc, rcImage);
}

void CCheckUpDate::SetControlPos(int cx, int cy)
{
	const  UINT  uFlags = SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOCOPYBITS | SWP_NOSIZE;

	LockWindowUpdate();

	HDWP hDwp = BeginDeferWindowPos(32);
	CRect rcButton;
	m_btClose.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp, m_btClose, NULL, cx - rcButton.Width() - 8, 4, 0, 0, uFlags);
	EndDeferWindowPos(hDwp);

	Invalidate(FALSE);
	UpdateWindow();

	UnlockWindowUpdate();
}

void CCheckUpDate::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}

void CCheckUpDate::OnTimer(UINT_PTR nIDEvent)
{
	GUID   pageGuid = FrameDimensionTime;

	RectF rcDrawRect;
	rcDrawRect.X = (REAL)m_rcGif.left;
	rcDrawRect.Y = (REAL)m_rcGif.top;
	rcDrawRect.Width = (REAL)m_rcGif.Width();
	rcDrawRect.Height = (REAL)m_rcGif.Height();

	CClientDC dc(this);
	Graphics graphics(dc.GetSafeHdc());
	graphics.DrawImage(m_pImage, rcDrawRect);
	m_pImage->SelectActiveFrame(&pageGuid, m_nFramePosition++);		

	if (m_nFramePosition == m_nFrameCount)
		m_nFramePosition = 0;

	CMyDialog::OnTimer(nIDEvent);
}

bool CCheckUpDate::TestGIF()
{
	UINT count = 0;
	count = m_pImage->GetFrameDimensionsCount();
	GUID* pDimensionIDs = new GUID[count];

	// 得到子帧的对象列表
	m_pImage->GetFrameDimensionsList(pDimensionIDs, count);

	//获取总帧数
	m_nFrameCount =  m_pImage->GetFrameCount(&pDimensionIDs[0]);

	// 假设图像具有属性条目 PropertyItemEquipMake.
	// 获取此条目的大小.
	int nSize =  m_pImage->GetPropertyItemSize(PropertyTagFrameDelay);

	// 为属性条目分配空间.
	m_pPropertyItem = (PropertyItem*) malloc(nSize);
	m_pImage->GetPropertyItem(PropertyTagFrameDelay, nSize, m_pPropertyItem);
	delete pDimensionIDs;

	return m_nFrameCount > 1;
}

bool CCheckUpDate::DrawFrameGIF()
{
	if (!TestGIF()) 
		return false;

	CRect rcClient;
	GetClientRect(&rcClient);
	CalcCenterRect(rcClient, m_pImage->GetWidth(), m_pImage->GetHeight(), m_rcGif);

	m_nFramePosition = 0;

	long lPause = ((long*) m_pPropertyItem->value)[m_nFramePosition] * 10;

	SetTimer(0, lPause, NULL);

	return true;
}


void CCheckUpDate::InitializeGIF()
{
	m_nFrameCount = 0;
	m_nFramePosition = 0;
	m_pPropertyItem = NULL;

	m_pImage = NULL;
	m_pDC = NULL;
}

void CCheckUpDate::DestroyGif()
{
	if (m_pPropertyItem != NULL) {
		free(m_pPropertyItem);
		m_pPropertyItem;
	}
	if (m_pImage != NULL) {
		delete(m_pImage);
		m_pImage = NULL;
	}
}

void CCheckUpDate::DrawLine()
{
	static int x1 =50, y1 =50, x2 = 100, y2 = 50; 
	CClientDC dc(this);
	Graphics graphics(dc.GetSafeHdc());
	Pen pen(Color(255, 255, 0, 0));
	graphics.DrawLine(&pen, x1, y1, x2, y2);
	x1 += 5;
	x2 += 5;
}
