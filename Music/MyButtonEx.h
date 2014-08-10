#pragma once
#include "MyImage.h"
#include "MyDialogBase.h"

enum BUTTON_TYPE 
{
	BT_PUSHBUTTON,
	BT_RADIOBUTTON,
	BT_CHECKBUTTON,
	BT_ICONBUTTON,
	BT_MENUBUTTON
};

// CMyButtonEx

class CMyButtonEx : public CButton,public MyDialogBase
{
protected:
	CImage			m_pBackImg;
	CMyImage	    * m_pBackImgN, * m_pBackImgH, * m_pBackImgD, * m_pBackImgF;
	CMyImage		*m_pCheckImgH, *m_pCheckImgN, *m_pCheckImgTichH, *m_pCheckImgTickN; 
	CMyImage		*m_pIconImg;
	CMyImage		*m_pMenuImg;

	BOOL			m_bPress;
	BOOL			m_bHover;
	BOOL			m_bFocus;
	BOOL			m_bMouseTracking;
	
	HMENU			m_hMenu;
	BUTTON_TYPE		m_nBtnType;

	DECLARE_DYNAMIC(CMyButtonEx)

public:
	CMyButtonEx();
	virtual ~CMyButtonEx();

public:
	void SetButtonType(BUTTON_TYPE nBtnType);
	bool SetBackImage(HINSTANCE hInstance, UINT nResourceID);
	BOOL SetBackImage(LPCTSTR lpNormal, LPCTSTR lpHoven, LPCTSTR lpDown, LPCTSTR lpFocus, CONST LPRECT lprcNinePart=NULL);
	bool SetCheckImage(LPCTSTR lpNormal, LPCTSTR lpHover, LPCTSTR lpTickNormal, LPCTSTR lpTickHover);
	bool SetIconImage(LPCTSTR lpszFileName);
	BOOL SetMenuImage(LPCTSTR lpszFileName);
	void SetSize(int nWidth, int nHeight);
	void SetMenu(HMENU hMenu);

	void DrawPushButton(CDC* pDC,RECT &rcClient);
	void DrawCheckButton(CDC* pDC,RECT &rcClient);
	void DrawIconButton(CDC* pDC,RECT &rcClient);
	void DrawMenuButton(CDC* pDC,RECT &rcClient);
//	void SetParentBack(HDC hDC){ m_bTransparent = true; m_hParentDC = hDC;}

public:
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();

protected:
	DECLARE_MESSAGE_MAP()
};


