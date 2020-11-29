
// GDI-LabVezba2.h : main header file for the GDI-LabVezba2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGDILabVezba2App:
// See GDI-LabVezba2.cpp for the implementation of this class
//

class CGDILabVezba2App : public CWinApp
{
public:
	CGDILabVezba2App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGDILabVezba2App theApp;
