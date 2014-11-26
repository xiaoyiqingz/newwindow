#pragma once
#include "ZiImage.h"
// CZiScrollBar

class CZiScrollBar : public CStatic
{
	DECLARE_DYNAMIC(CZiScrollBar)
public:
	CZiImage		*m_pVThumbImg, *m_pHThumbImg;
	CZiImage		*m_pVBackImg, *m_pTopImg, *m_pBottomImg;
	CZiImage		*m_pHBackImg, *m_pLeftImg, *m_pRightImg;

	CWnd			*m_pCtrl;
	UINT			m_nScrollStyle;
public:
	CZiScrollBar();
	virtual ~CZiScrollBar();

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL    SetScrollType(CWnd *pCtrl, UINT nStyle);
	void	UpdateScrollBar();

	BOOL	SetVScrollImg(UINT nBackImg, UINT nThumbImg, UINT nTopImg, UINT nBottomImg, LPCTSTR lpszFileType, LPRECT lpNinePart=NULL);
	BOOL	SetHScrollImg(UINT nBackImg, UINT nThumbImg, UINT nLeftImg, UINT nRightImg, LPCTSTR lpszFileType, LPRECT lpNinePart=NULL);
	
	void	DrawVScrollBar(CDC *pDC);
	void	DrawHScrollBar(CDC *pDC);
public:
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
};


