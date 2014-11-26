#pragma once
#include "ZiImage.h"

// CZiMenuEx

struct tagMenuItem
{
	BOOL		bHasChild;
	BOOL		bIsSeparator;
	CZiImage	*pImage;
	LPCTSTR		lpszStr;
};

typedef vector<tagMenuItem> CMenuItem;

class CZiMenuEx : public CWnd
{
	DECLARE_DYNAMIC(CZiMenuEx)
public:
	CMenuItem	m_MenuItem;
	int			m_nItemHeight;

public:
	CZiMenuEx();
	virtual ~CZiMenuEx();

protected:
	DECLARE_MESSAGE_MAP()

public:
	void AppendMenuItem(UINT nImageID, LPCTSTR lpszImageType, LPCTSTR lpszText, BOOL bHasChild=NULL, BOOL bIsSeparator=NULL);
	void SetItemHeight(int nHeight);

public:
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
};


