
// GDI-2014View.h : interface of the CGDI2014View class
//

#pragma once
#include "DImage.h"

class CGDI2014View : public CView
{
protected: // create from serialization only
	CGDI2014View() noexcept;
	DECLARE_DYNCREATE(CGDI2014View)

// Attributes
	HENHMETAFILE clio;
	DImage *wheel;

	int put;
	float angle;

public:
	CGDI2014Doc* GetDocument() const;
	void DrawGround(CDC* pDC, float angle);
	void Translate(CDC* pDC, float dX, float dY, bool rightMul);
	void Rotate(CDC* pDC, float angle, bool rightMul);
	void Scale(CDC* pDC, float sX, float sY, bool rightMul);
	void DrawCar(CDC* pDC, int x, int y, int w, int h);
	void DrawWheel(CDC* pDC, int x, int y, int r, float angle);
// Operations
public:

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
	virtual ~CGDI2014View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in GDI-2014View.cpp
inline CGDI2014Doc* CGDI2014View::GetDocument() const
   { return reinterpret_cast<CGDI2014Doc*>(m_pDocument); }
#endif

