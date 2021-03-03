
// GDI-2017View.h : interface of the CGDI2017View class
//

#pragma once
#include "DImage.h"

class CGDI2017View : public CView
{
protected: // create from serialization only
	CGDI2017View() noexcept;
	DECLARE_DYNCREATE(CGDI2017View)

	// Attributes
	DImage* leg1, * leg2, * leg3, * body, * back2;
	void LoadIdentity(CDC* pDC);
	void Translate(CDC* pDC,float dx,float dy,bool rightmul);
	void Rotate(CDC* pDC,float angle,bool rightmul);
	void Scale(CDC* pDC,float sx,float sy,bool rightmul);
	int faza = 0;
	int pomeraj = 0;
	float povecaj = 1;

	int bgpomx = 0;
	int bgpomy = 0;
	CRect crect;

public:
	CGDI2017Doc* GetDocument() const;

	// Operations
public:
	void DrawScene(CDC* pDC, CRect rect);
	void DrawLeg(CDC* pDC, float alpha, float x, float y);

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
	virtual ~CGDI2017View();
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

#ifndef _DEBUG  // debug version in GDI-2017View.cpp
inline CGDI2017Doc* CGDI2017View::GetDocument() const
{
	return reinterpret_cast<CGDI2017Doc*>(m_pDocument);
}
#endif

