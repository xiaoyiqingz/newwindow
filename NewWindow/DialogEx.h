#pragma once

#include "ImageEx.h"

// CDialogEx dialog

class CMyDialogEx : public CDialog
{
	DECLARE_DYNAMIC(CMyDialogEx)
	enum {
		en_Normal,
		en_Hoven,
		en_Press
	};
private:
	BYTE  m_cbNowHotIndex[3]; //第I个当前按钮是什么状态 Normal？Hoven？Press
	BYTE  m_cbNowButtonIndex; //当前索引的是哪个按钮
	BYTE  m_cbButtonState[3]; //第i个当前按钮状态 BUT_EXIST BUT_NORMAL  BUT_DISABLE
	CRect m_rcButton[3];

protected:
	CImageEx  m_ImageTitleL;
	CImageEx  m_ImageTitleM;
	CImageEx  m_ImageTitleM_Spe;
	CImageEx  m_ImageTitleR;

	CImageEx  m_ImageBt_Close;
	CImageEx  m_ImageBt_Max;
	CImageEx  m_ImageBt_Res;
	CImageEx  m_ImageBt_Min;
	CImageEx  m_ImageBt_Set;

public:
	CMyDialogEx(UINT nIDTemplate ,CWnd* pParent = NULL);   // standard constructor
	virtual ~CMyDialogEx();

// Dialog Data
//	enum { IDD = IDD_DIALOGEX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcPaint();
	//修改标题栏尺寸
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);

public:
	void DrawTitleBar(CDC *pDC);
	void DrawTitleButton(CDC * pDC);
	BOOL LoadImageFromResource(ATL::CImage *pImage, UINT nResID,LPCTSTR lpTyp);
	
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
//	afx_msg void OnMouseLeave();
	afx_msg void OnNcMouseLeave();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
};
