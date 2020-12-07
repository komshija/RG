
// GDI-LabVezba2View.h : interface of the CGDILabVezba2View class
//

#pragma once


class CGDILabVezba2View : public CView
{
protected: // create from serialization only
	CGDILabVezba2View() noexcept;
	DECLARE_DYNCREATE(CGDILabVezba2View)
	
	HENHMETAFILE emf_cactus_light,emf_cactus;// Handleri za meta-fajlove

	CRect* _SetRegion(CDC* pDC); // Postavlja odsecanje za 500x500
	void _DrawBackground(CDC* pDC); // Boji pozadinu
	void _DrawGrid(CDC* pDC); // Crta grid
	void _DrawPot(CDC* pDC); // Crta saksiju
	void _DrawName(CDC* pDC); // Crta ime
	void _DrawCactus(CDC* pDC); // Glavna za crtanje kaktusa
	void _DrawRightArm(CDC* pDC); //Crta desni deo
	void _DrawLeftArm(CDC* pDC); //Crta levi deo
	void _DrawUpper(CDC* pDC); //Crta gornji deo koji se pomera


	void _SetTransformation1(CDC* pDC); // Postavlja prvu promenjivu transformaciju
	void _SetTransformation2(CDC* pDC); // Postavlja drugu promenjivu transformaciju

	void _SetRoation(CDC* pDC, float angle, float x, float y);

// Attributes	
	bool drawGrid;// Flag za grid
	float angle1, angle2; // Uglovi
	const double C_PI = 3.14159265358979; // Pi konstanta
	const float angleStep = 5 * ((2 * C_PI) / 360); // Korak rotiranja
public:
	CGDILabVezba2Doc* GetDocument() const;

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
	virtual ~CGDILabVezba2View();
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

#ifndef _DEBUG  // debug version in GDI-LabVezba2View.cpp
inline CGDILabVezba2Doc* CGDILabVezba2View::GetDocument() const
   { return reinterpret_cast<CGDILabVezba2Doc*>(m_pDocument); }
#endif

