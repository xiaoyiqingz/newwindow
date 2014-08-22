#pragma once
#include "MyImage.h"
#include "MyDialogBase.h"

// CMyToolTip
class CMyToolTip : public CToolTipCtrl, public MyDialogBase
{
	DECLARE_DYNAMIC(CMyToolTip)
public:
	CMyImage		*m_pBackImg;
	COLORREF		m_colorText;

public:
	CMyToolTip();
	virtual ~CMyToolTip();

protected:
	DECLARE_MESSAGE_MAP()

public:
	bool	SetBackImg(LPCTSTR lpszBack,  CONST	LPRECT lpNinePart = NULL);
	void	SetTextCol(COLORREF colorText);

	void	DrawItem(CDC *pDc, RECT &rcClient);
public:
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
};


