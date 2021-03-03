
// GDI-2013View.h : interface of the CGDI2013View class
//

#pragma once
#include "DImage.h"

class CGDI2013View : public CView
{
protected: // create from serialization only
	CGDI2013View() noexcept;
	DECLARE_DYNCREATE(CGDI2013View)

// Attributes
	DImage* sky;
	DImage* bark;
	int x_pos = 0;
	float angle = 0;
	bool hitted = false;
public:
	CGDI2013Doc* GetDocument() const;

// Operations
public:
	void DrawBlade(CDC* pDC, int size);
	void Translate(CDC* pDC, double x, double y);
	void Rotate(CDC* pDC, float alpha);
	void DrawStar(CDC* pDC, int size);

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
	virtual ~CGDI2013View();
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

#ifndef _DEBUG  // debug version in GDI-2013View.cpp
inline CGDI2013Doc* CGDI2013View::GetDocument() const
   { return reinterpret_cast<CGDI2013Doc*>(m_pDocument); }
#endif

