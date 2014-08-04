#pragma once
#include "MyDialogBase.h"
#include "MyImage.h"

// CMyTabCtrl

class  CTabCtrlItem
{
public:
	CTabCtrlItem(void);
	~CTabCtrlItem(void);

public:
	int		m_nID;
	CString	m_strText;
	int		m_nWidth, m_nHeight;
	int		m_nLeftWidth, m_nRightWidth;
	int		m_nPadding;
	CMyImage * m_lpBgImgN, * m_lpBgImgH, * m_lpBgImgD;
	CMyImage * m_lpIconImg, * m_lpSelIconImg;
};

typedef vector<CTabCtrlItem *>			CTabCtrlItemArray;


class CMyTabCtrl : public CTabCtrl, public MyDialogBase
{
	DECLARE_DYNAMIC(CMyTabCtrl)
public:
	CTabCtrlItemArray	m_ItemArray;
	CMyImage	*m_pImgBack;
	CMyImage	*m_pItemImgNor, *m_pItemImgHov, * m_pItemImgSel;
	BOOL		m_bMouseTracking;
	int			m_nSelIndex, m_nHoverIndex;
	int			m_nLeft, m_nTop;

public:
	CMyTabCtrl();
	virtual ~CMyTabCtrl();

public:
	BOOL	SetBackImage(LPCTSTR lpszFileName, CONST LPRECT lpNinePart=NULL);
	BOOL	SetItemsImage(LPCTSTR lpNormal, LPCTSTR lpHighlight, LPCTSTR lpDown, CONST LPRECT lprcNinePart = NULL);
	BOOL	SetIconImage(int nIndex, LPCTSTR lpIcon, LPCTSTR lpSelIcon);

	void	SetLeftTop(int nLeft, int nTop);
	CSize	SetItemSize(CSize size);
	void	SetItemPadding(int nIndex, int nPadding);
	int		HitTest(POINT pt);
	void	DrawItem(CDC *pDC, int nIndex);

	int		GetCurSel();
	void	SetCurSel(int nCurSel);
	int		AddItem(int nID);
	void	SetItemText(int nIndex, LPCTSTR lpszText);

	BOOL	GetItemRectByIndex(int nIndex, CRect& rect);
	CTabCtrlItem * GetItemByIndex(int nIndex);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


