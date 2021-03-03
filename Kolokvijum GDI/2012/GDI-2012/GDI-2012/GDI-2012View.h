
// GDI-2012View.h : interface of the CGDI2012View class
//

#pragma once


class CGDI2012View : public CView
{
protected: // create from serialization only
	CGDI2012View() noexcept;
	DECLARE_DYNCREATE(CGDI2012View)

	int EffR(int a, int b);
	int angle = 0;
// Attributes
public:
	CGDI2012Doc* GetDocument() const;

// Operations
public:
	void Trapez(CDC* pDC, int a, int b, int h);
	void Translate(CDC* pDC, float x, float y);
	void Rotate(CDC* pDC, float a);
	void DrawGear(CDC* pDC, int spokeCount, int spokeWidth);
	void DrawScene(CDC* pDC);
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
	virtual ~CGDI2012View();
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

#ifndef _DEBUG  // debug version in GDI-2012View.cpp
inline CGDI2012Doc* CGDI2012View::GetDocument() const
   { return reinterpret_cast<CGDI2012Doc*>(m_pDocument); }
#endif

