#pragma once
#include "MyDialog.h"
#include "MyImage.h"
#include "MyButtonEx.h"
// CCheckUpDate dialog

class CCheckUpDate : public CMyDialog
{
	DECLARE_DYNAMIC(CCheckUpDate)
public:
	CMyImage		m_ImageBack;
	CMyButtonEx		m_btClose;
	CMyImage		m_ImageWaiting;
	
	CMyButtonEx		m_btGif;

public:
	CCheckUpDate(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckUpDate();

// Dialog Data
	enum { IDD = IDD_CHECKUPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:	
	void SetControlPos(int cx, int cy);

public:
	virtual	BOOL OnInitDialog();
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

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
	void DrawLine();
};
