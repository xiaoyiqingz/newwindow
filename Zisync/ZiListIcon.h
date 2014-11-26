#pragma once
#include "ZiImage.h"
#include "ZiDialogBase.h"
#include "UI/ZiScrollBar.h"

// CZiListIcon

struct tagItem 
{
	int			nItem;
	bool		bIsSelected;
	bool		bIsHoveing;
	CString		strText;
	CZiImage	*m_pImgBack;
	CZiImage	*m_pImgIcon;
	CZiImage	*m_pImgIconSel;
};
typedef vector<tagItem> CItemArray;

class CZiListIcon : public CListCtrl, public ZiDialogBase
{
	DECLARE_DYNAMIC(CZiListIcon)
public:
	CItemArray		m_ItemImgArray;
	CImageList		m_ImageList1;
	CSize			m_ItemSize;
	BOOL			m_bMouseTracking;
	int				m_nHoverIndex;
	int				m_xPadding, m_yPadding;	
	BOOL			m_bResFromID;

	CZiScrollBar	m_VScroll;
public:
	CZiListIcon();
	virtual ~CZiListIcon();

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL	SetItemImage(int nItem, UINT nResBackID, UINT nResIconNorID, UINT nResIconSelID, LPCTSTR lpszFileType=NULL);
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


