#pragma once


// CMyListBox

class CMyListBox : public CListBox
{
	DECLARE_DYNAMIC(CMyListBox)
protected:
	INT			m_nItemHeight;
public:
	CMyListBox();
	virtual ~CMyListBox();

public:
	void	SetItemHeight(int nItemHeight);

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/);
};


