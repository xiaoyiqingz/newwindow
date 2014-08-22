#pragma once
#include "MyImage.h"
#include "MyDialogBase.h"

// CMyListIcon
struct tagItem 
{
	int			nItem;
	bool		bIsSelected;
	bool		bIsHoveing;
	CString		strText;
	CMyImage	*m_pImgBack;
	CMyImage	*m_pImgIcon;
	CMyImage	*m_pImgIconSel;
};
typedef vector<tagItem> CItemArray;

class CMyListIcon : public CListCtrl, public MyDialogBase
{
	DECLARE_DYNAMIC(CMyListIcon)
public:
	CItemArray		m_ItemImgArray;
	CSize			m_ItemSize;
	BOOL			m_bMouseTracking;
	int				m_nHoverIndex;
	int				m_xPadding, m_yPadding;
	CImageList		m_ImageList1;
public:
	CMyListIcon();
	virtual ~CMyListIcon();

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL	SetItemImage(int nItem, LPCTSTR lpBackImg, LPCTSTR lpIcon, LPCTSTR lpIconSel);
	BOOL	SetItemText(int nItem, CString strText);
	void	SetItemSize(CSize size);
	void	SetPadding(int cx, int cy);
	void	DrawIconItem(CDC *pDC, CRect & rcItem, int nItem);

	int		GetItemLeftPadding();
	int		GetItemCountH();
	int		GetItemCount();
	BOOL	GetChecked(int nItem);

	int		HitTest(POINT point);
public:
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void PreSubclassWindow();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
};


