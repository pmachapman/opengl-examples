
// Ogl.h : main header file for the Ogl application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COglApp:
// See Ogl.cpp for the implementation of this class
//

class COglApp : public CWinApp
{
public:
	COglApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COglApp theApp;
