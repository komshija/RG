
// LabVezba1.h : main header file for the LabVezba1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLabVezba1App:
// See LabVezba1.cpp for the implementation of this class
//

class CLabVezba1App : public CWinApp
{
public:
	CLabVezba1App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLabVezba1App theApp;
