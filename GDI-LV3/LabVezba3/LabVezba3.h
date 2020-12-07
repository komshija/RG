
// LabVezba3.h : main header file for the LabVezba3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLabVezba3App:
// See LabVezba3.cpp for the implementation of this class
//

class CLabVezba3App : public CWinApp
{
public:
	CLabVezba3App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLabVezba3App theApp;
