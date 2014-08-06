// DialogSet.cpp : implementation file
//

#include "stdafx.h"
#include "Music.h"
#include "DialogSet.h"
#include "afxdialogex.h"


// CDialogSet dialog

IMPLEMENT_DYNAMIC(CDialogSet, CMyDialog)

CDialogSet::CDialogSet(CWnd* pParent /*=NULL*/)
	: CMyDialog(CDialogSet::IDD, pParent)
{

}

CDialogSet::~CDialogSet()
{
}

void CDialogSet::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogSet, CMyDialog)
END_MESSAGE_MAP()


// CDialogSet message handlers


BOOL CDialogSet::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE; 
}
