// ZiStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ZisyncService.h"
#include "MemoryDC.h"
#include "RenderManager.h"
#include "ZiStatic.h"
#include <algorithm>


// CZiStatic

IMPLEMENT_DYNAMIC(CZiStatic, CStatic)

CZiStatic::CZiStatic()
{
	m_pBackImg = NULL;
}

CZiStatic::~CZiStatic()
{
}


BEGIN_MESSAGE_MAP(CZiStatic, CStatic)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()



// CZiStatic message handlers




void CZiStatic::OnDestroy()
{
	__super::OnDestroy();
	m_strPath.clear();
	RenderEngine->RemoveImage(m_pBackImg);
	m_pBackImg = NULL;
}


void CZiStatic::OnPaint()
{
	CPaintDC dc(this);

	CRect rcClient;
	GetClientRect(&rcClient);
	
	CMemoryDC MemoryDc(&dc, rcClient);

	DrawParentWndBg(GetSafeHwnd(), MemoryDc->GetSafeHdc());

	if (m_pBackImg != NULL && !m_pBackImg->IsNull()) 
		m_pBackImg->Draw(&MemoryDc, rcClient);
}

BOOL CZiStatic::SetBackImage(LPCTSTR lpszFile, const LPRECT lprcNinePart)
{
	RenderEngine->RemoveImage(m_pBackImg);

	m_pBackImg = RenderEngine->GetImage(lpszFile);

	if (m_pBackImg == NULL) 
		return FALSE;
	else 
		m_pBackImg->SetNinePart(lprcNinePart);
		return TRUE;

}

void CZiStatic::SetItemSize(int nWidth, int nHeight)
{
	SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOMOVE);
}


void CZiStatic::OnDropFiles(HDROP hDropInfo)
{
	UINT nFile;
	TCHAR szFilePath[MAX_PATH+1];
	nFile = ::DragQueryFile(hDropInfo, (UINT)(-1), NULL, 0);
	for (int i = 0; i < (int)nFile; i++) {
		szFilePath[0] = 0;
		::DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);
		if (PathIsDirectory(szFilePath)) {
			if (find(m_strPath.begin(), m_strPath.end(), szFilePath) != m_strPath.end())
				continue;
			else
				m_strPath.push_back(szFilePath);
		}
	}
	CString strText;
	vector<CString>::iterator iter = m_strPath.begin();
	for (; iter != m_strPath.end(); iter++) {
		strText += *iter + _T("\n");
	}
	MessageBox(strText);
	__super::OnDropFiles(hDropInfo);
}
