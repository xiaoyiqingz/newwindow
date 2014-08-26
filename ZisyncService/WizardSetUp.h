#pragma once
#include "MyDialog.h"
#include "MyButtonEx.h"
#include "MyImage.h"
#include "SetUpPage0.h"
#include "SetUpPage1.h"
#include "SetUpPage2.h"

// CWizardSetUp dialog

class CWizardSetUp : public CMyDialog
{
	DECLARE_DYNAMIC(CWizardSetUp)
public:
	CMyImage		m_ImageBack;
	CMyButtonEx		m_btClose;	
	CMyButtonEx		m_btCancle;
	CMyButtonEx		m_btNext;
	CMyButtonEx		m_btPrev;

	CSetUpPage0		m_Page0;
	CSetUpPage1		m_Page1;
	CSetUpPage2		m_Page2;		

	int				m_nPage;
public:
	CWizardSetUp(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWizardSetUp();

// Dialog Data
	enum { IDD = IDD_WIZARDSETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void SetControlPos(int cx, int cy);
	void OnInitButton(CRect &rcClinent);
	void WizardSetUpOk();

public:
	virtual BOOL OnInitDialog();
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedPrev();
};
