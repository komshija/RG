
// GDI-2012.h : main header file for the GDI-2012 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDI2012App:
// See GDI-2012.cpp for the implementation of this class
//

class CGDI2012App : public CWinApp
{
public:
	CGDI2012App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDI2012App theApp;
