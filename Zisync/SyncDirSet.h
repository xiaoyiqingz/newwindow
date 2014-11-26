#pragma once
#include "ZiDialog.h"
#include "ZiImage.h"
#include "ZiButton.h"
#include "afxwin.h"
#include "afxcmn.h"
// CSyncDirSet dialog

class CSyncDirSet : public CZiDialog
{
	DECLARE_DYNAMIC(CSyncDirSet)
public:
	CZiImage		*m_pBackImg;
	CZiButton		m_btClose;
	CZiButton		m_btDeleteDir;
	CZiButton		m_btOk;
	CZiButton		m_btCancle;
	CZiButton		m_btCancleSync;
	CZiButton		m_btSet;

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
