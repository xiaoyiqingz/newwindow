#pragma once
#include "MyDialog.h"
#include "MyImage.h"
#include "MyButtonEx.h"
#include "afxwin.h"
// CCheckUpDate dialog

class CCheckUpDate : public CMyDialog
{
	DECLARE_DYNAMIC(CCheckUpDate)
public:
	CMyImage		m_ImageBack;
	CMyButtonEx		m_btClose;
	CMyButtonEx		m_btCancle;
	CMyButtonEx		m_btUpdate;
	CMyImage		m_ImageWaiting;
	CMyImage		m_ImageLogo;
	
	CStatic			m_etChecked;
	CStatic			m_etOldVer;
	CStatic			m_etNewVer;
	CButton			m_btOk;
	BOOL			m_bCheckOk;
public:
	CCheckUpDate(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckUpDate();

// Dialog Data
	enum { IDD = IDD_CHECKUPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	UINT				m_nFrameCount;
	UINT				m_nFramePosition;
	PropertyItem*		m_pPropertyItem;
	HANDLE				m_hTimer;

	Image*				m_pImage;
	CDC*				m_pDC;
	CRect				m_rcGif;

	void InitializeGIF();
	void DestroyGif();
	bool TestGIF();
	bool DrawFrameGIF();

public:	
	void SetControlPos(int cx, int cy);
	void OnInitButton();

public:
	virtual	BOOL OnInitDialog();
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckOk();
};
