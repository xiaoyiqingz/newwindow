#pragma once
#include "ZiImage.h"
#include "ZiDialogBase.h"

enum BUTTON_TYPE 
{
	BT_PUSHBUTTON,
	BT_RADIOBUTTON,
	BT_CHECKBUTTON,
	BT_ICONBUTTON,
	BT_MENUBUTTON,
	BT_SPLITBUTTON,
	BT_GIFBUTTON
};

// CZiButton

class CZiButton : public CButton,public ZiDialogBase
{
protected:
	CImage			m_pBackImg;
	CZiImage	    * m_pBackImgN, * m_pBackImgH, * m_pBackImgD, * m_pBackImgF;
	CZiImage		*m_pCheckImgH, *m_pCheckImgN, *m_pCheckImgTichH, *m_pCheckImgTickN; 
	CZiImage		*m_pIconImg;
	CZiImage		*m_pMenuImg;

	BOOL			m_bPress;
	BOOL			m_bHover;
	BOOL			m_bFocus;
	BOOL			m_bMouseTracking;
	
	HMENU			m_hMenu;
	BUTTON_TYPE		m_nBtnType;

	BOOL			m_bBackFromID;
	BOOL			m_bIconFromID;
	BOOL			m_bCheckFromID;
	BOOL			m_bMenuFromID;

	DECLARE_DYNAMIC(CZiButton)

public:
	CZiButton();
	virtual ~CZiButton();

public:
	void SetButtonType(BUTTON_TYPE nBtnType);
	
	BOOL SetBackImage(UINT nResNorID, UINT nResHovID=0, UINT nResDownID=0, UINT nResFocID=0,LPCTSTR lpszFileType=NULL, CONST LPRECT lprcNinePart=NULL);
	BOOL SetBackImage(LPCTSTR lpNormal, LPCTSTR lpHoven, LPCTSTR lpDown, LPCTSTR lpFocus, CONST LPRECT lprcNinePart=NULL);
	
	BOOL SetCheckImage(UINT nResNorID, UINT nResHovID, UINT nResTickNorID, UINT nResTickHovID, LPCTSTR lpszFileType=NULL);
	BOOL SetCheckImage(LPCTSTR lpNormal, LPCTSTR lpHover, LPCTSTR lpTickNormal, LPCTSTR lpTickHover);
	
	BOOL SetIconImage(UINT nResIconID, LPCTSTR lpszFileType);
	BOOL SetIconImage(LPCTSTR lpszFileName);
	
	BOOL SetMenuImage(UINT nResFromID, LPCTSTR lpszFileType);
	BOOL SetMenuImage(LPCTSTR lpszFileName);
	
	void SetSize(int nWidth, int nHeight);
	void SetMenu(HMENU hMenu);

	void DrawPushButton(CDC* pDC,RECT &rcClient);
	void DrawCheckButton(CDC* pDC,RECT &rcClient);
	void DrawIconButton(CDC* pDC,RECT &rcClient);
	void DrawMenuButton(CDC* pDC,RECT &rcClient);
	void DrawSplitButton(CDC* pDC,RECT &rcClient);
	void DrawGIFButton(CDC* pDC,RECT &rcClient);
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
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


