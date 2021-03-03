
// GDI-2016View.h : interface of the CGDI2016View class
//

#pragma once
#include "DImage.h"

class CGDI2016View : public CView
{
protected: // create from serialization only
	CGDI2016View() noexcept;
	DECLARE_DYNCREATE(CGDI2016View)

// Attributes
	float stap_angle = 0;
	int stap_pom = 0;
	bool udareno = false;
	float kugla_angle = 0;

	DImage* wood;
	DImage* table;


public:
	CGDI2016Doc* GetDocument() const;

// Operations
public:
	void DrawStick(CDC* pDC, int w);
	void DrawBall(CDC* pDC, int w);


	void Translate(CDC* pDC, float dx, float dy, bool rightMul);
	void Rotate(CDC* pDC, float angle, bool rightMul);

	void DrawTable(CDC* pDC, CRect rect);
	void DrawBounds(CDC* pDC, CRect rect, int w);
	void DrawHoles(CDC* pDC, CRect rect, int size);

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
	virtual ~CGDI2016View();
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

#ifndef _DEBUG  // debug version in GDI-2016View.cpp
inline CGDI2016Doc* CGDI2016View::GetDocument() const
   { return reinterpret_cast<CGDI2016Doc*>(m_pDocument); }
#endif

