#pragma once
#include "ZiImage.h"
#include "ZiDialogBase.h"

// CZiToolTip

class CZiToolTip : public CToolTipCtrl, public ZiDialogBase
{
	DECLARE_DYNAMIC(CZiToolTip)
public:
	CZiImage		*m_pBackImg;
	COLORREF		m_colorText;

	BOOL			m_bResFromID;
public:
	CZiToolTip();
	virtual ~CZiToolTip();

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL	SetBackImg(UINT nResFromID, LPCTSTR lpszFileType=NULL, CONST LPRECT lpNinePart = NULL);
	BOOL	SetBackImg(LPCTSTR lpszBack,  CONST	LPRECT lpNinePart=NULL);
	
	void	SetTextCol(COLORREF colorText);

	void	DrawItem(CDC *pDc, RECT &rcClient);
public:
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
};


