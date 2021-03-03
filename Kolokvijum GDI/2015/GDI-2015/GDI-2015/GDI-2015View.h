
// GDI-2015View.h : interface of the CGDI2015View class
//

#pragma once
#include "DImage.h"

class CGDI2015View : public CView
{
protected: // create from serialization only
	CGDI2015View() noexcept;
	DECLARE_DYNCREATE(CGDI2015View)

// Attributes
	DImage* blue;
	int pacX, pacY;
	bool open;
	int dir, lastdir;
	void Rotate(CDC* pDC, float angle);
	void Translate(CDC* pDC, double x, double y);
	void Mirror(CDC* pDC, int x, int y);
public:
	CGDI2015Doc* GetDocument() const;

// Operations
public:
	void DrawPacman(CDC* pDC, CRect rect, float angle);
	void DrawGhost(CDC* pDC, CRect rect);

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
	virtual ~CGDI2015View();
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

#ifndef _DEBUG  // debug version in GDI-2015View.cpp
inline CGDI2015Doc* CGDI2015View::GetDocument() const
   { return reinterpret_cast<CGDI2015Doc*>(m_pDocument); }
#endif

