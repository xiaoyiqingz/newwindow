#pragma once
#include "MyImage.h"

// CMyDialog dialog

class CMyDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyDialog)
public:
	CMyImage   m_ImageBack;

public:
	CMyDialog(INT nIDTemplate, CWnd* pParent = NULL);   // standard constructor
	virtual ~CMyDialog();

// Dialog Data
//	enum { IDD = IDD_MYDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	bool	LoadBackSkin(LPCTSTR pszResourcePath);
	bool	LoadBackSkin(HINSTANCE hInstance, LPCTSTR pszResourcePath);
	bool	LoadBackSkin(HINSTANCE hInstance, UINT nIDResource);
	afx_msg void OnPaint();
};
