// UI\WizardSetUp.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "WizardSetUp.h"
#include "afxdialogex.h"


// CWizardSetUp dialog

IMPLEMENT_DYNAMIC(CWizardSetUp, CZiDialog)

CWizardSetUp::CWizardSetUp(CWnd* pParent /*=NULL*/)
	: CZiDialog(CWizardSetUp::IDD, pParent)
{
	m_nPage = 0;
}

CWizardSetUp::~CWizardSetUp()
{
}

void CWizardSetUp::DoDataExchange(CDataExchange* pDX)
{
	CZiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_btCancle);
	DDX_Control(pDX, IDC_SETUP_PREV, m_btPrev);
	DDX_Control(pDX, IDC_SETUP_NEXT, m_btNext);
}


BEGIN_MESSAGE_MAP(CWizardSetUp, CZiDialog)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SETUP_NEXT, OnBnClickedNext)
	ON_BN_CLICKED(IDC_SETUP_PREV, OnBnClickedPrev)
END_MESSAGE_MAP()

// CWizardSetUp message handlers
BOOL CWizardSetUp::OnInitDialog()
{
	CZiDialog::OnInitDialog();
	m_ImageBack.LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SETUP_BACK), IMAGE_PNG);
	SetWindowPos(NULL, 0, 0, 510, 380, SWP_NOMOVE );

	CRect rcControl(0, 0, 0, 0);
	m_btClose.Create(NULL,  WS_CHILD | WS_VISIBLE, rcControl, this, IDCANCEL);
	m_btClose.SetBackImage(IDB_CLOSE_NOR, IDB_CLOSE_HOV,IDB_CLOSE_SEL, 
		IDB_CLOSE_FOC, IMAGE_PNG);
	m_btClose.SetButtonType(BT_PUSHBUTTON);
	m_btClose.SetParentBack(GetBackDC());
	m_btClose.SetSize(18, 18);

	CRect rcClient;
	GetClientRect(&rcClient);
	SetControlPos(rcClient.Width(), rcClient.Height());

	OnInitButton(rcClient);

	m_Page0.Create(IDD_SETUPPAGE0, this);
	m_Page1.Create(IDD_SETUPPAGE1, this);
	m_Page2.Create(IDD_SETUPPAGE2, this);

	CRect rcPage(rcClient.left+8, rcClient.top + 32, rcClient.right-8, rcClient.bottom-56);
	m_Page0.MoveWindow(rcPage);
	m_Page1.MoveWindow(rcPage);
	m_Page2.MoveWindow(rcPage);

	m_Page0.ShowWindow(SW_SHOW);
	m_Page1.ShowWindow(SW_HIDE);
	m_Page2.ShowWindow(SW_HIDE);

	return TRUE;
}

void CWizardSetUp::SetControlPos(int cx, int cy)
{
	const UINT nFlags = SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOCOPYBITS | SWP_NOSIZE;

	LockWindowUpdate();

	HDWP  hDwp = BeginDeferWindowPos(32);
	CRect rcButton;
	m_btClose.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp, m_btClose, NULL, cx-rcButton.Width()-2, 0, 0, 0, nFlags);	
	EndDeferWindowPos(hDwp);

	Invalidate(FALSE);

	UpdateWindow();
	UnlockWindowUpdate();
}

void CWizardSetUp::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	CRect rcTitle(0, 0, rcClient.Width(), 35);
	if (PtInRect(&rcTitle, point)) {
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	}	

	CZiDialog::OnLButtonDown(nFlags, point);
}

void CWizardSetUp::DrawClientArea(CDC*pDC,int nWidth,int nHeight)
{
	m_ImageBack.Draw(pDC, 0, 0, nWidth, nHeight, 0, 0, 0, 0);
	
	CRect rcTitleCaption, rcTitle;
	rcTitle = CRect(0,0, nWidth, 35);
	pDC->DrawText(_T("自同步设置向导"), &rcTitleCaption, DT_CALCRECT);
	CalcCenterRect(rcTitle, rcTitleCaption.Width(), rcTitleCaption.Height(), rcTitleCaption);
	
	int nMode = pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(GetCtrlFont());
	pDC->SetTextColor(m_colNormalText);
	pDC->DrawText(_T("自同步设置向导"), &rcTitleCaption, DT_CENTER | DT_SINGLELINE);
	pDC->SetBkMode(nMode);
}

void CWizardSetUp::OnInitButton(CRect &rcClient)
{
	HDC hParent = GetBackDC();
	m_btCancle.SetBackImage(IDB_BT_BACK, 0, 0, 0, IMAGE_PNG);
	m_btCancle.SetButtonType(BT_PUSHBUTTON);
	m_btCancle.SetParentBack(hParent);
	m_btCancle.SetSize(74, 26);
	m_btCancle.MoveWindow(rcClient.left+20, rcClient.bottom-41, 74, 26);

	m_btPrev.SetBackImage(IDB_BT_BACK, 0, 0, 0, IMAGE_PNG);
	m_btPrev.SetButtonType(BT_PUSHBUTTON);
	m_btPrev.SetParentBack(hParent);
	m_btPrev.SetSize(74, 26);
	m_btPrev.MoveWindow(rcClient.right-188, rcClient.bottom-41, 74, 26);
	m_btPrev.ShowWindow(SW_HIDE);

	m_btNext.SetBackImage(IDB_BT_BACK, 0, 0, 0, IMAGE_PNG);
	m_btNext.SetButtonType(BT_PUSHBUTTON);
	m_btNext.SetParentBack(hParent);
	m_btNext.SetSize(74, 26);
	m_btNext.MoveWindow(rcClient.right-94, rcClient.bottom-41, 74, 26);

}

void CWizardSetUp::OnBnClickedNext()
{
	switch (m_nPage) {
		case 0:
			m_Page0.ShowWindow(SW_HIDE);
			m_Page1.ShowWindow(SW_SHOW);
			m_btPrev.ShowWindow(SW_SHOW);
			m_nPage++;
			break;
		case 1:
			if (MessageBox(_T("文件夹已存在"), _T(""),IDOK) == IDOK) {
				m_Page1.ShowWindow(SW_HIDE);
				m_Page2.ShowWindow(SW_SHOW);
				m_btNext.SetWindowText(_T("完成"));
				m_nPage++;
			}
			break;
		case 2:
			WizardSetUpOk();
			
	}
}

void CWizardSetUp::OnBnClickedPrev()
{
	CRect rcClient;
	switch (m_nPage) {
		case 1:
			m_Page0.ShowWindow(SW_SHOW);
			m_Page1.ShowWindow(SW_HIDE);
			m_btPrev.ShowWindow(SW_HIDE);
			m_nPage--;
			break;
		case 2:
			m_Page1.ShowWindow(SW_SHOW);
			m_Page2.ShowWindow(SW_HIDE);
			m_btNext.SetWindowText(_T("下一步")); 
			m_btNext.GetWindowRect(&rcClient); //refresh the NEXT button, or the CMyButtonEx OnPaint will not be called;
			ScreenToClient(rcClient);
			InvalidateRect(&rcClient, FALSE);
			m_nPage--;
			break;
		default:
			break;
	}
}

void CWizardSetUp::WizardSetUpOk()
{
	CWizardSetUp::OnOK();
}
