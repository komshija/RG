
// GDI-2018.h : main header file for the GDI-2018 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDI2018App:
// See GDI-2018.cpp for the implementation of this class
//

class CGDI2018App : public CWinApp
{
public:
	CGDI2018App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDI2018App theApp;
