
// GDI-2011.h : main header file for the GDI-2011 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDI2011App:
// See GDI-2011.cpp for the implementation of this class
//

class CGDI2011App : public CWinApp
{
public:
	CGDI2011App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDI2011App theApp;
