
// GDI-Ispit.h : main header file for the GDI-Ispit application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDIIspitApp:
// See GDI-Ispit.cpp for the implementation of this class
//

class CGDIIspitApp : public CWinApp
{
public:
	CGDIIspitApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDIIspitApp theApp;
