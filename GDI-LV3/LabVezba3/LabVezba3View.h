
// LabVezba3View.h : interface of the CLabVezba3View class
//

#pragma once
#include "DImage.h"


class CLabVezba3View : public CView
{
protected: // create from serialization only
	CLabVezba3View() noexcept;
	DECLARE_DYNCREATE(CLabVezba3View)
	
//Methods
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Scale(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Mirror(CDC* pDC, bool mx, bool my, bool rightMultiply);
	void DrawTransparent(CDC* pDC, DImage* img,int x,int y);
	void MemDCTopDC(CDC* memDC, CDC* pDC);
	void DrawGrid(CDC* memDC);
//Attributes

	DImage** part;
	const float C_PI = 3.141592653589793;
	// Jedan stepen
	const float stepAngle = (C_PI) / 180;
public:
	CLabVezba3Doc* GetDocument() const;
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
	virtual ~CLabVezba3View();
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

};

#ifndef _DEBUG  // debug version in LabVezba3View.cpp
inline CLabVezba3Doc* CLabVezba3View::GetDocument() const
   { return reinterpret_cast<CLabVezba3Doc*>(m_pDocument); }
#endif

