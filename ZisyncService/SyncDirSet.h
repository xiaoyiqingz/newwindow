#pragma once
#include "MyDialog.h"
#include "MyImage.h"
#include "MyButtonEx.h"
#include "afxwin.h"
#include "afxcmn.h"
// CSyncDirSet dialog

class CSyncDirSet : public CMyDialog
{
	DECLARE_DYNAMIC(CSyncDirSet)
public:
	CMyImage		*m_pBackImg;
	CMyButtonEx		m_btClose;
	CMyButtonEx		m_btDeleteDir;
	CMyButtonEx		m_btOk;
	CMyButtonEx		m_btCancle;
	CMyButtonEx		m_btCancleSync;
	CMyButtonEx		m_btSet;

	CListCtrl		m_ListDir;
	CImageList		m_ImageList;
public:
	CSyncDirSet(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSyncDirSet();

// Dialog Data
	enum { IDD = IDD_SYNCDIRSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	void	OnInitButton();
	void	OnInitListCtrl();
	void	SetControlPos(int cx, int cy);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
