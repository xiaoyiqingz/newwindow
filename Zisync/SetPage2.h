#pragma once
#include "ZiDialog.h"
#include "ZiButton.h"
#include "afxwin.h"

// CSePage2 dialog

class CSetPage2 : public CZiDialog
{
	DECLARE_DYNAMIC(CSetPage2)
public:
	CZiButton		m_btUpdate;
	CZiButton		m_btFeedback;

	CEdit			m_etSyncTime;
public:
	CSetPage2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetPage2();

// Dialog Data
	enum { IDD = IDD_SETPAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	void	OnInitButton();

public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickedRadio1();
	afx_msg void OnRadio4();
	afx_msg void OnBnClickedBtUpdate();
};
