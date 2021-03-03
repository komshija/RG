
// GDI-2014.h : main header file for the GDI-2014 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDI2014App:
// See GDI-2014.cpp for the implementation of this class
//

class CGDI2014App : public CWinApp
{
public:
	CGDI2014App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDI2014App theApp;
