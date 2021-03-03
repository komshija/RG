
// GDI-2016.h : main header file for the GDI-2016 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDI2016App:
// See GDI-2016.cpp for the implementation of this class
//

class CGDI2016App : public CWinApp
{
public:
	CGDI2016App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDI2016App theApp;
