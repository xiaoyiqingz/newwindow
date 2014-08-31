// CheckUpDate.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "CheckUpDate.h"
#include "afxdialogex.h"


// CCheckUpDate dialog

IMPLEMENT_DYNAMIC(CCheckUpDate, CZiDialog)

CCheckUpDate::CCheckUpDate(CWnd* pParent /*=NULL*/)
	: CZiDialog(CCheckUpDate::IDD, pParent)
{
	InitializeGIF();
	m_bCheckOk = FALSE;
}

CCheckUpDate::~CCheckUpDate()
{
	DestroyGif();
}

void CCheckUpDate::DoDataExchange(CDataExchange* pDX)
{
	CZiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_OK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancle);
	DDX_Control(pDX, IDC_UPDATE, m_btUpdate);
	DDX_Control(pDX, IDC_TEXT, m_etChecked);
	DDX_Control(pDX, IDC_OLD, m_etOldVer);
	DDX_Control(pDX, IDC_NEW, m_etNewVer);
}


BEGIN_MESSAGE_MAP(CCheckUpDate, CZiDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_OK, &CCheckUpDate::OnBnClickedCheckOk)
END_MESSAGE_MAP()

// CCheckUpDate message handlers

BOOL CCheckUpDate::OnInitDialog()
{
	CZiDialog::OnInitDialog();
	HINSTANCE hInstance = AfxGetInstanceHandle();
	m_ImageBack.LoadImage(hInstance, IDB_UPDATE_BACK, IMAGE_PNG);
	
	m_ImageWaiting.LoadImage(hInstance, IDR_LOAD, IMAGE_GIF);
	m_ImageLogo.LoadImage(hInstance, IDB_LOGO, IMAGE_PNG);
	//	m_pImage = Image::FromFile(_T("res\\hearts.gif"));

	SetWindowPos(NULL, 0, 0, 400, 220, SWP_NOMOVE);

	CRect rcControl(0, 0, 0, 0);
	HDC hParentDC = GetBackDC();
	m_btClose.Create(NULL,  WS_CHILD | WS_VISIBLE, rcControl, this, IDCANCEL);
	m_btClose.SetBackImage(IDB_CLOSE_NOR, IDB_CLOSE_HOV,IDB_CLOSE_SEL, 
		IDB_CLOSE_FOC, IMAGE_PNG);
	m_btClose.SetButtonType(BT_PUSHBUTTON);
	m_btClose.SetParentBack(hParentDC);
	m_btClose.SetSize(18 ,18);
	
	m_etChecked.ShowWindow(SW_HIDE);
	m_etNewVer.ShowWindow(SW_HIDE);
	m_etOldVer.ShowWindow(SW_HIDE);

	OnInitButton();

	CRect rcClient;
	GetClientRect(&rcClient);
	SetControlPos(rcClient.Width(), rcClient.Height());

	return TRUE;
}


void CCheckUpDate::DrawClientArea(CDC*pDC,int nWidth,int nHeight)
{
	m_ImageBack.Draw(pDC, 0, 0, nWidth, nHeight, 0, 0, 0, 0);

	if (!m_bCheckOk) {
		CRect rcClient, rcCenter, rcLogo, rcText;
		GetClientRect(&rcClient);
		CalcCenterRect(rcClient, m_ImageWaiting.GetWidth(), m_ImageWaiting.GetHeight(),
			rcCenter);
		::OffsetRect(rcCenter, 0 ,-30);
		m_ImageWaiting.DrawFrameGIF(GetSafeHwnd(), rcCenter);
		CalcCenterRect(rcCenter, 32, 32, rcLogo);
		m_ImageLogo.Draw(pDC, rcLogo);

		int nMode = pDC->SetBkMode(TRANSPARENT); 
		pDC->SelectObject(GetCtrlFont());
		pDC->DrawText(_T("当前版本0.5.0， 正在检查更新..."), &rcText, DT_CALCRECT);
		int cx = rcText.Width();
		int cy = rcText.Height();
		CalcCenterRect(rcClient, cx, cy, rcText);
		rcText.top = rcCenter.bottom + 10;
		rcText.bottom = rcText.top + cy;
		pDC->DrawText(_T("当前版本0.5.0， 正在检查更新..."), &rcText, DT_CENTER);
		pDC->SetBkMode(nMode);
	} else {
		CRect rcLogo, rcText1, rcText2;
		m_etOldVer.GetWindowRect(&rcText1);
		m_etNewVer.GetWindowRect(&rcText2);
		ScreenToClient(rcText1);
		ScreenToClient(rcText2);
		
		int nTextLeft = rcText1.left;
		int nTextTop = rcText1.top;
		int nTextHeight = rcText2.bottom - rcText1.top;

		rcLogo.top = nTextTop - (48 - nTextHeight)/2;
		rcLogo.bottom = rcLogo.top + 48;
		rcLogo.right = nTextLeft - 10;
		rcLogo.left = rcLogo.right - 48;

		m_ImageLogo.Draw(pDC, rcLogo);
	}	
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

void CCheckUpDate::OnInitButton()
{
	HDC hParentDC = GetBackDC();
	m_btCancle.SetBackImage(IDB_BT_BACK, 0, 0, 0, IMAGE_PNG);
	m_btCancle.SetButtonType(BT_PUSHBUTTON);
	m_btCancle.SetParentBack(hParentDC);
	m_btCancle.SetSize(74, 26);

	m_btUpdate.SetBackImage(IDB_BT_BACK, 0, 0, 0, IMAGE_PNG);
	m_btUpdate.SetButtonType(BT_PUSHBUTTON);
	m_btUpdate.SetParentBack(hParentDC);
	m_btUpdate.SetSize(74, 26);
	m_btUpdate.ShowWindow(FALSE);
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

	CZiDialog::OnTimer(nIDEvent);
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

void CCheckUpDate::OnBnClickedCheckOk()
{
	m_bCheckOk = TRUE;
//	m_ImageLogo.DestroyImage();
	m_ImageWaiting.DestroyImage();
	m_btCancle.ShowWindow(SW_HIDE);

	Invalidate(FALSE);
	
	m_etChecked.ShowWindow(SW_SHOW);
	m_etNewVer.ShowWindow(SW_SHOW);
	m_etOldVer.ShowWindow(SW_SHOW);
	
	CRect rcItem;
	m_btCancle.GetWindowRect(&rcItem);
	ScreenToClient(rcItem);
	m_btUpdate.ShowWindow(TRUE);
	m_btUpdate.MoveWindow(rcItem);
}

