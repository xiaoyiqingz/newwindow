// SePage2.cpp : implementation file
//

#include "stdafx.h"
#include "Zisync.h"
#include "SetPage2.h"
#include "afxdialogex.h"
#include "CheckUpDate.h"

// CSePage2 dialog

IMPLEMENT_DYNAMIC(CSetPage2, CZiDialog)

CSetPage2::CSetPage2(CWnd* pParent /*=NULL*/)
	: CZiDialog(CSetPage2::IDD, pParent)
{

}

CSetPage2::~CSetPage2()
{
}

void CSetPage2::DoDataExchange(CDataExchange* pDX)
{
	CZiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UPDATE, m_btUpdate);
	DDX_Control(pDX, IDC_FEEDBACK, m_btFeedback);
	DDX_Control(pDX, IDC_SYNC_TIME, m_etSyncTime);
}


BEGIN_MESSAGE_MAP(CSetPage2, CZiDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RADIO1, &CSetPage2::OnClickedRadio1)
	ON_COMMAND(IDC_RADIO4, &CSetPage2::OnRadio4)
	ON_BN_CLICKED(IDC_UPDATE, OnBnClickedBtUpdate)
END_MESSAGE_MAP()


// CSePage2 message handlers


BOOL CSetPage2::OnInitDialog()
{
	CZiDialog::OnInitDialog();
	
	OnInitButton();
	
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	m_etSyncTime.EnableWindow(FALSE);
	
	return TRUE;  
}

void CSetPage2::OnInitButton()
{
	HDC hParentDc = GetBackDC();
	m_btFeedback.SetBackImage(IDB_BT_BACK, 0, 0, 0, _T("png"));
	m_btFeedback.SetButtonType(BT_PUSHBUTTON);
	m_btFeedback.SetParentBack(hParentDc);
	m_btFeedback.SetSize(74, 26);

	m_btUpdate.SetBackImage(IDB_BT_BACK, 0, 0, 0, _T("png"));
	m_btUpdate.SetButtonType(BT_PUSHBUTTON);
	m_btUpdate.SetParentBack(hParentDc);
	m_btUpdate.SetSize(74, 26);
}


HBRUSH CSetPage2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CZiDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) {
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		return hBrush;
	}
	return hbr;
}


void CSetPage2::OnClickedRadio1()
{
	m_etSyncTime.EnableWindow(FALSE);
}


void CSetPage2::OnRadio4()
{
	m_etSyncTime.EnableWindow(TRUE);
}

void CSetPage2::OnBnClickedBtUpdate()
{
	CCheckUpDate CheckUpDate;
	CheckUpDate.DoModal();
}
