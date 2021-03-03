
// GDI-2011View.h : interface of the CGDI2011View class
//

#pragma once
#include "DImage.h"

class CGDI2011View : public CView
{
protected: // create from serialization only
	CGDI2011View() noexcept;
	DECLARE_DYNCREATE(CGDI2011View)

// Attributes
	DImage* slika;
	HENHMETAFILE clio,tocak;
	ENHMETAHEADER clio_header,tocak_header;
	void PovecajRect(CRect& rect, int val);
	int pomeraj;
public:
	CGDI2011Doc* GetDocument() const;

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
	virtual ~CGDI2011View();
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

#ifndef _DEBUG  // debug version in GDI-2011View.cpp
inline CGDI2011Doc* CGDI2011View::GetDocument() const
   { return reinterpret_cast<CGDI2011Doc*>(m_pDocument); }
#endif

