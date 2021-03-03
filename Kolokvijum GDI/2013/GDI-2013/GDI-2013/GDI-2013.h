
// GDI-2013.h : main header file for the GDI-2013 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDI2013App:
// See GDI-2013.cpp for the implementation of this class
//

class CGDI2013App : public CWinApp
{
public:
	CGDI2013App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDI2013App theApp;
