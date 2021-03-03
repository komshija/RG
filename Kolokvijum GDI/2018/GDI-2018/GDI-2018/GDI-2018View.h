
// GDI-2018View.h : interface of the CGDI2018View class
//

#pragma once
#include "DImage.h"

class CGDI2018View : public CView
{
protected: // create from serialization only
	CGDI2018View() noexcept;
	DECLARE_DYNCREATE(CGDI2018View)

// Attributes

	DImage* arm1, * arm2, * bager, * pozadina;
	HENHMETAFILE viljuska;
	ENHMETAHEADER header_viljuska;

public:
	CGDI2018Doc* GetDocument() const;

	void Translate(CDC* pDC, float dx, float dy, bool rightmul);
	void Rotate(CDC* pDC, float angle, bool rightmul);
	void Scale(CDC* pDC, float sx, float sy, bool rightmul);

	float ugaoArm1 = 0;
	float ugaoArm2 = 0;
	float ugaoFork = 0;

	int put = 0;

// Operations
public:
	void DrawBackground(CDC* pDC);
	void DrawBody(CDC* pDC);
	void DrawArm1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawFork(CDC* pDC);
	void DrawExcavator(CDC* pDC);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGDI2018View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in GDI-2018View.cpp
inline CGDI2018Doc* CGDI2018View::GetDocument() const
   { return reinterpret_cast<CGDI2018Doc*>(m_pDocument); }
#endif

