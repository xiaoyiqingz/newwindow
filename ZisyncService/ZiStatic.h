#pragma once
#include "ZiImage.h"
#include "ZiDialogBase.h"

// CZiStatic

class CZiStatic : public CStatic, public ZiDialogBase
{
	DECLARE_DYNAMIC(CZiStatic)
public:
	CZiImage	*m_pBackImg;
	BOOL		m_bResFromID;

	vector<CString> m_strPath;
public:
	CZiStatic();
	virtual ~CZiStatic();

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL	SetBackImage(LPCTSTR lpszFile, const LPRECT lprcNinePart = NULL);
	BOOL	SetBackImage(UINT nResBackID, LPCTSTR lpszFileType = NULL);
	void	SetItemSize(int nWidth, int nHeight);

public:
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};


