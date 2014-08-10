// Page2.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "Page2.h"
#include "afxdialogex.h"


// CPage2 dialog

IMPLEMENT_DYNAMIC(CPage2, CMyDialog)

CPage2::CPage2(CWnd* pParent /*=NULL*/)
	: CMyDialog(CPage2::IDD, pParent)
{

}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}


BEGIN_MESSAGE_MAP(CPage2, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPage2::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPage2 message handlers


BOOL CPage2::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_list1.SetParentBack(GetBackDC());
	m_list1.SetScrollImage(&m_list1,_T("res\\SKIN_SCROLL.bmp"));

	m_list1.SetItemImage(0, _T("res\\linux.png"), _T("res\\check_nor.png"), 
		_T("res\\check_sel.png"));
	m_list1.SetItemText(0,_T("Zhang"));
	for (int i = 1; i < 6; i++) {
		m_list1.SetItemImage(i, _T("res\\win32.png"), _T("res\\check_nor.png"), 
			_T("res\\check_sel.png"));
		m_list1.SetItemText(i,_T("DeskTop"));
	}
	m_list1.SetItemSize(CSize(78,78));
	m_list1.SetPadding(10, 10);
	
	return TRUE; 
}

void CPage2::OnBnClickedButton1()
{
	int nCount = m_list1.GetItemCount();

	CString	strText(_T("被选中的有："));
	for (int i =0; i < nCount; i++) {
		if (m_list1.GetChecked(i))
			strText.AppendFormat(_T("%d  "), i);
	}
	MessageBox(strText);
}

