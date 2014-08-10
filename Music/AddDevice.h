#pragma once
#include "MyDialog.h"
#include "MyImage.h"
#include "MyButtonEx.h"

// CAddDevice dialog

class CAddDevice : public CMyDialog
{
	DECLARE_DYNAMIC(CAddDevice)
public:
	CMyImage		m_ImageBack;
	CMyButtonEx		m_btClose;

	bool			m_bIsInit;
public:
	CAddDevice(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddDevice();

// Dialog Data
	enum { IDD = IDD_ADDDEVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void	SetControlPos(int cx, int cy);

public:
	virtual BOOL OnInitDialog();
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
