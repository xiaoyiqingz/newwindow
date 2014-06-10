#pragma once

#include "ImageEx.h"

// CDialogEx dialog

class CMyDialogEx : public CDialog
{
	DECLARE_DYNAMIC(CMyDialogEx)

protected:
	CImageEx  m_ImageTitleL;
	CImageEx  m_ImageTitleM;
	CImageEx  m_ImageTitleM_Spe;
	CImageEx  m_ImageTitleR;

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
	//ÐÞ¸Ä±êÌâÀ¸³ß´ç
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);

public:
	void DrawTitleBar(CDC *pDC);
	BOOL LoadImageFromResource(ATL::CImage *pImage, UINT nResID,LPCTSTR lpTyp);
	
};
