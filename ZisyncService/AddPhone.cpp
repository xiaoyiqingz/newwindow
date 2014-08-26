// AddPhone.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "AddPhone.h"
#include "afxdialogex.h"


// CAddPhone dialog

IMPLEMENT_DYNAMIC(CAddPhone, CMyDialog)

CAddPhone::CAddPhone(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddPhone::IDD, pParent)
{
	
}

CAddPhone::~CAddPhone()
{
}

void CAddPhone::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddPhone, CMyDialog)
END_MESSAGE_MAP()


// CAddPhone message handlers


BOOL CAddPhone::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	return TRUE;  
}
