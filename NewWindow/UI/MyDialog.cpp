// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "NewWindow.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// CMyDialog dialog

IMPLEMENT_DYNAMIC(CMyDialog, CDialog)

CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDialog::IDD, pParent)
{

}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
END_MESSAGE_MAP()


// CMyDialog message handlers
