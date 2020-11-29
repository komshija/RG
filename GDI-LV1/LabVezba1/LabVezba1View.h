
// LabVezba1View.h : interface of the CLabVezba1View class
//

#pragma once


class CLabVezba1View : public CView
{
protected: // create from serialization only
	CLabVezba1View() noexcept;
	DECLARE_DYNCREATE(CLabVezba1View)
	bool keyPressed;
	int gridSize;
	double getX(int radius, float angle);
	double getY(int radius, float angle);
	void crtajMnogougao(CDC* pDC, double radius, int cornerCount, double x, double y, CBrush* brush);
	void crtajTrougao(CDC* pDC, CPoint& p1, CPoint& p2, CPoint& p3, CBrush* brush);
	void crtajCetvorougao(CDC* pDC, CPoint& p1, CPoint& p2, CPoint& p3, CPoint& p4, CBrush* brush);

	// Attributes
public:
	CLabVezba1Doc* GetDocument() const;

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
	virtual ~CLabVezba1View();
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
};

#ifndef _DEBUG  // debug version in LabVezba1View.cpp
inline CLabVezba1Doc* CLabVezba1View::GetDocument() const
{
	return reinterpret_cast<CLabVezba1Doc*>(m_pDocument);
}
#endif

