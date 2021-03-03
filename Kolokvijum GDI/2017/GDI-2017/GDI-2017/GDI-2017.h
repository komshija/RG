
// GDI-2017.h : main header file for the GDI-2017 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDI2017App:
// See GDI-2017.cpp for the implementation of this class
//

class CGDI2017App : public CWinApp
{
public:
	CGDI2017App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDI2017App theApp;
