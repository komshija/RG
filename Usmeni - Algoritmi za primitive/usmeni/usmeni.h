
// usmeni.h : main header file for the usmeni application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CusmeniApp:
// See usmeni.cpp for the implementation of this class
//

class CusmeniApp : public CWinApp
{
public:
	CusmeniApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CusmeniApp theApp;
