
// GDI-IspitView.h : interface of the CGDIIspitView class
//

#pragma once
#include "DImage.h"

class CGDIIspitView : public CView
{
protected: // create from serialization only
	CGDIIspitView() noexcept;
	DECLARE_DYNCREATE(CGDIIspitView)

// Attributes
public:
	CGDIIspitDoc* GetDocument() const;
	int dest = 0;
	CPoint mpoint = CPoint(0,0);
// Operations
public:

	void Translate(CDC* pDC, float dx, float dy, bool rightmul);
	void Rotate(CDC* pDC, float angle,  bool rightmul);
	void Scale(CDC* pDC, float sx, float sy, bool rightmul);
	void Shear(CDC* pDC, float sx, float sy, bool rightmul);
	void Mirror(CDC* pDC, bool x, bool y, bool rightmul);


	//2019 - septembar
	void DrawConeBottom(CDC* pDC,float cx,float cy, float a, float b, float h, float n);
	void DrawConeTop(CDC* pDC,float cx,float cy, float a, float b, float h, float n);
	void DrawFigure	(CDC* pDC,float cx,float cy, float a, float b, float h, float n,float r);
	
	//2019 - oktobar
	void DrawTop(CDC* pDC, int size);
	void DrawTop2(CDC* pDC, int size);
	void DrawTail(CDC* pDC, int size, int count,float alpha);

	//2019 - jun MAX
	void DrawArrow(CDC* pDC, double r, int n, COLORREF colFill, COLORREF colLine, float angle);
	void DrawRoundedText(CDC* pDC, CRect rcRect, double perc, COLORREF colFillRect, COLORREF colLineRect, CString text, COLORREF colText, CPoint ptMouse, double r, int n, COLORREF colFillArrow, COLORREF colLineArrow);

	//2019 - jan
	void DrawCanTop(CDC* pDC, DImage* img, float cX, float cY, float a, float b, int n);
	//Ne bih znao
	void DrawCanWrapper(CDC* pDC, DImage* img, float cX, float cY, float a, float b, int n, float h);
	void DrawCan(CDC* pDC, float cX, float cY, float a, float b, int n, float h);
	
	//2019 - apr
	void DrawWheel(CDC* pDC, float r1, float r2, float w);
	void DrawWP(CDC* pDC, float r1, float r2, float w,float L,float alpha,float d);

	void DrawLake(CDC* pDC);

	void SaveRect(CDC* pDC, CRect rectView, CString name);

	void DrawPuzzle(CDC* pDC, CRect rcRect, int nRows, int nCols, float radio);
	void DrawTextRound(CDC* pDC, CString text);

	void DrawRotated(CString name, float angle);
	void GetXY(int* x, int* y, float angle);
	
	DImage *img;
	void Resample(int x, int y, DImage* img);

	CDC* DrawGradientBitmap(CDC* pDC, float w, float h, COLORREF col1, COLORREF col2);

	void DrawTriangle(CDC* pDC);
	void DrawFigureTriangles(CDC* pDC);

	void DrawCycle(CDC* pDC, int r, int n, int d);
	void DrawBicycle(CDC* pDC, int r, int n, int d, int alpha, int beta);
	void DrawText(CDC* pDC, int size, CString strTex, COLORREF clrText);

	void DrawVirusCycle(CDC* pDC, int r, int n, int d);

	void Distort(CDC* pDC,float r);

	void DrawPlate(CDC* pDC, CString text);

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
	virtual ~CGDIIspitView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnMove(int x, int y);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in GDI-IspitView.cpp
inline CGDIIspitDoc* CGDIIspitView::GetDocument() const
   { return reinterpret_cast<CGDIIspitDoc*>(m_pDocument); }
#endif

