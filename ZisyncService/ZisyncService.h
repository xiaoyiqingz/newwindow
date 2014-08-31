// ZisyncService.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <Shlwapi.h>
#include <map>
#include <vector>

using namespace std;

// CZisyncServiceApp:
// See ZisyncService.cpp for the implementation of this class
//

#define	  IMAGE_JPG	    _T("IMAGE");
#define   IMAGE_PNG		_T("PNG")
#define	  IMAGE_GIF		_T("GIF")
#define	  IMAGE_BMP		_T("BMP")

class CZisyncServiceApp : public CWinApp
{
protected:
	ULONG_PTR				m_GdiplusToken;

	CShellManager			*m_pShellManager;
public:
	CZisyncServiceApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CZisyncServiceApp theApp;