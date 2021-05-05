
// usmeniView.h : interface of the CusmeniView class
//

#pragma once


class CusmeniView : public CView
{
protected: // create from serialization only
	CusmeniView() noexcept;
	DECLARE_DYNCREATE(CusmeniView)

// Attributes
public:
	CusmeniDoc* GetDocument() const;
	float ugao = 0;
// Operations
public:
	void WritePixel4(CDC* pDC, int x, int y, COLORREF value);
	void WritePixel8(CDC* pDC, int x, int y, COLORREF value);

	void NagibniAlgoritam(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);
	void InkrementalniAlgoritam(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);
	void BresenhamovAlgoritamLinija(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);

	void TrigonometrijskiAlgoritamKrug(CDC* pDC, int r, COLORREF value);
	void PolinomniAlgoritamKrug(CDC* pDC, int r, COLORREF value);
	void BresenhamovAlgoritamKrug(CDC* pDC, int r, COLORREF value);

	void TrigonometrijskiAlgoritamElipsa(CDC* pDC, int a,int b, COLORREF value);
	void PolinomniAlgoritamElipsa(CDC* pDC, int a, int b, COLORREF value);
	void DiferencijalniPrvogRedaElipsa(CDC* pDC, int a, int b, COLORREF value);
	void DiferencijalniDrugogRedaElipsa(CDC* pDC, int a, int b, COLORREF value);

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
	virtual ~CusmeniView();
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

#ifndef _DEBUG  // debug version in usmeniView.cpp
inline CusmeniDoc* CusmeniView::GetDocument() const
   { return reinterpret_cast<CusmeniDoc*>(m_pDocument); }
#endif

