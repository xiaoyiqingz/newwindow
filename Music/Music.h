
// Music.h : main header file for the PROJECT_NAME application
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
// CMusicApp:
// See Music.cpp for the implementation of this class
//

class CMusicApp : public CWinApp
{
protected:
	ULONG_PTR				m_GdiplusToken;

public:
	CMusicApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CMusicApp theApp;