
// GDI-2015.h : main header file for the GDI-2015 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDI2015App:
// See GDI-2015.cpp for the implementation of this class
//

class CGDI2015App : public CWinApp
{
public:
	CGDI2015App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDI2015App theApp;
