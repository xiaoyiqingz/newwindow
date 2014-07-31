#pragma once
#include "MyImage.h"
#include "MyDialogBase.h"
// CMyEdit

class CMyEdit : public CEdit, public MyDialogBase
{
	DECLARE_DYNAMIC(CMyEdit)
protected:
	CMyImage*		m_pBackImgN;
	CMyImage*		m_pBackImgH;
	CMyImage*		m_pIconImg;

	bool	m_bPress, m_bHover, m_bFocus, m_bMouseTracking;
	int		m_nIconWidth;
	bool	m_bHandCursor;
	CString	m_strDefText;			
	BOOL	m_bIsDefText;			
	TCHAR	m_cPwdChar;				
	CPoint	m_ptClient;		
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	BOOL SetBackNormalImg(LPCTSTR lpszFileName, CONST LPRECT lpNinePart = NULL);
	BOOL SetBackHotImg(LPCTSTR lpszFileName, CONST LPRECT lpNinePart = NULL);
	BOOL SetIconImg(LPCTSTR lpszFileName, bool bHandCursor = false);

	void SetDefaultText(LPCTSTR lpszText);
	void SetDefaultTextMode(BOOL bIsDefText);
	void GetIconRect(RECT &rcIcon);
	void SetClientPoint(CPoint pt);
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
};


