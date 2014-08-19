#pragma once
#include "MyDialogBase.h"
#include "MyToolTip.h"
#include "MyImage.h"

// CMyListCtrl
class CMyHeaderCtrl : public CHeaderCtrl, public MyDialogBase
{
public:
	UINT		m_uLockCount;
	UINT		m_uItemHeight;
	UINT		m_uActiveItem;
	bool		m_bPress;

	CMyImage	*m_pBackImg, *m_pPressImg, *m_pGridImg;
public:
	CMyHeaderCtrl();
	virtual ~CMyHeaderCtrl();

public:
	BOOL	SetBackImage(LPCTSTR lpNormal, CONST LPRECT lprcNinePart=NULL);
	BOOL	SetPressImage(LPCTSTR lpNormal, CONST LPRECT lprcNinePart=NULL);
	BOOL	SetGridImage(LPCTSTR lpNormal);

	void	SetItemHeight(UINT uItemHeight);
	void	SetLockCount(UINT uLockCount);
	
public:
	virtual void PreSubclassWindow();	
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);	
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);		

	LRESULT OnLayout( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()
};

struct  tagItemImage 
{
	int				nItem;
	bool			bSelect;
	CMyImage		*pImage;
	CMyImage		*pSelectImage;
};

typedef vector<tagItemImage>	CItemImgArray;

struct tagItemContent
{
	bool		bRightTopHov;
	LPCTSTR		strLeftTop;
	LPCTSTR		strRightTop;
	LPCTSTR		strLeftBottom;
	LPCTSTR		strRightBottom;
};

typedef map<int, tagItemContent> CItemContentArray;

class CMyListCtrl : public CListCtrl, public MyDialogBase
{
	DECLARE_DYNAMIC(CMyListCtrl)
public:
	CMyImage	*m_pHovenImg, *m_pSelectImg;
	CMyImage	*m_pCheckImg, *m_pUnCheckImg;

	CItemImgArray	m_ItemImgArray;
	CItemImgArray	m_ItemBtnArray;
	CItemImgArray	m_ItemInviteArray;
	CItemImgArray	m_ItemSetArray;
	CItemContentArray  m_ItemContent;
	COLORREF		m_colorBk;
	UINT			m_uActiveItem;
	int				m_nHeightItem;
	int				m_nItemHov;

	CMyHeaderCtrl	m_HeaderCtrl;
	
	CMyToolTip		m_ToolTip;
public:
	CMyListCtrl();
	virtual ~CMyListCtrl();

public:
	BOOL SetHovenImage(LPCTSTR lpszFileName, const LPRECT lprcNinePart);
	BOOL SetSelectImage(LPCTSTR lpszFileName, const LPRECT lprcNinePart);
	BOOL SetCheckImage(LPCTSTR lpszCheckName,LPCTSTR lpszUnCheckName);
	BOOL InsertImage(int nItem, int nSubitem, LPCTSTR lpszNorFileName, LPCTSTR lpszSelFileName = NULL);

	int InsertItem(const LVITEM* pItem);
	int InsertItem(int nItem, LPCTSTR lpszItem);
	int InsertItem(int nItem, LPCTSTR lpszItem, int nImage);
	int InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState,UINT nStateMask, int nImage, LPARAM lParam);	

	DWORD SetExtendedStyle(DWORD dwNewStyle);
	void DrawReportItem(CDC * pDC, INT nItem, CRect & rcSubItem, INT nColumnIndex);
	void SetItemHeight(int nHeight);
	
	void SetItemContent(int nItem,  LPCTSTR lpszLeftTop, LPCTSTR lpszRightTop, LPCTSTR lpszLeftBottom, LPCTSTR lpszRightBtoom = NULL);
	BOOL GetItemContent(int nItem,  tagItemContent& itemContent);
	
	//判断是在1列右上
	BOOL HitTestRightTop(int nItem, POINT pt);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


