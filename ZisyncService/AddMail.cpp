// AddMail.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "AddMail.h"
#include "afxdialogex.h"


// CAddMail dialog

IMPLEMENT_DYNAMIC(CAddMail, CMyDialog)

CAddMail::CAddMail(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddMail::IDD, pParent)
{

}

CAddMail::~CAddMail()
{
}

void CAddMail::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddMail, CMyDialog)
END_MESSAGE_MAP()


// CAddMail message handlers
