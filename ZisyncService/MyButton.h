#pragma once
#include "ZiImage.h"
#include "MyImageEx.h"
// CMyButton

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)
protected:
	bool		m_bExpand; //是否拉伸
	bool		m_bHovering;
	COLORREF	m_crTextColor; //字体颜色
	CMyImageEx	m_ImageBack;

public:
	CMyButton();
	virtual ~CMyButton();

protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
	bool FixButtonSize();
	bool SetTextColor(COLORREF crTextColor);
	bool SetButtonImage(LPCTSTR pszFilePath, bool bExpandImage=false);
	bool SetButtonImage(HINSTANCE hInstance, LPCTSTR pszResourceName, LPCTSTR pszType,
		bool bExpandImage=false);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
};


