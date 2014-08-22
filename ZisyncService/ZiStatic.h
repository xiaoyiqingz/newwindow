#pragma once
#include "MyImage.h"
#include "MyDialogBase.h"

// CZiStatic

class CZiStatic : public CStatic, public MyDialogBase
{
	DECLARE_DYNAMIC(CZiStatic)
public:
	CMyImage	*m_pBackImg;
	vector<CString> m_strPath;
public:
	CZiStatic();
	virtual ~CZiStatic();

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL	SetBackImage(LPCTSTR lpszFile, const LPRECT lprcNinePart = NULL);
	void	SetItemSize(int nWidth, int nHeight);

public:
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};


