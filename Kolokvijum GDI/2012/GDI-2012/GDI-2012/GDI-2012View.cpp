
// GDI-2012View.cpp : implementation of the CGDI2012View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI-2012.h"
#endif

#include "GDI-2012Doc.h"
#include "GDI-2012View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDI2012View

IMPLEMENT_DYNCREATE(CGDI2012View, CView)

BEGIN_MESSAGE_MAP(CGDI2012View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CGDI2012View construction/destruction

CGDI2012View::CGDI2012View() noexcept
{
	// TODO: add construction code here

}

int CGDI2012View::EffR(int a, int b)
{
	float eff_o = a * b * 1.4 * 2;
	float eff_r = eff_o / (2 * 3.14);
	return eff_r;
}

CGDI2012View::~CGDI2012View()
{
}

BOOL CGDI2012View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDI2012View drawing



void CGDI2012View::OnDraw(CDC* pDC)
{
	CGDI2012Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CRect cr;
	GetClientRect(&cr);
	// TODO: add draw code for native data here
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, cr.Width(), cr.Height());
	memDC->SelectObject(bm);

	memDC->Rectangle(cr);

	memDC->SetGraphicsMode(GM_ADVANCED);
	DrawScene(memDC);



	pDC->BitBlt(0, 0, cr.Width(), cr.Height(), memDC, 0, 0, SRCCOPY);
}


// CGDI2012View printing

BOOL CGDI2012View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDI2012View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDI2012View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDI2012View diagnostics

#ifdef _DEBUG
void CGDI2012View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI2012View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI2012Doc* CGDI2012View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI2012Doc)));
	return (CGDI2012Doc*)m_pDocument;
}
#endif //_DEBUG


// CGDI2012View message handlers



// User methods

void CGDI2012View::Trapez(CDC* pDC, int a, int b, int h)
{
	CPoint* niz = new CPoint[4];
	niz[0] = CPoint(-a / 2, -h / 2);
	niz[1] = CPoint(a / 2, -h / 2);
	niz[2] = CPoint(b / 2, h / 2);
	niz[3] = CPoint(-b / 2, h / 2);
	pDC->Polygon(niz, 4);
	delete []niz;
}

void CGDI2012View::Translate(CDC* pDC, float x, float y)
{
	XFORM forma = {
		1,0,0,1,x,y
	};
	pDC->ModifyWorldTransform(&forma, MWT_LEFTMULTIPLY);
}

void CGDI2012View::Rotate(CDC* pDC, float a)
{
	a *= 3.14 / 180;
	XFORM forma = {
		cosf(a),
		sinf(a),
		-sinf(a),
		cosf(a),
		0,
		0
	};
	pDC->ModifyWorldTransform(&forma, MWT_LEFTMULTIPLY);
}

void CGDI2012View::DrawGear(CDC* pDC, int spokeCount, int spokeWidth)
{
	//Efektivni obim
	CPen* oldpen, *pen;
	pen = new CPen(PS_DASH, 1, RGB(0, 0, 0));
	oldpen = pDC->SelectObject(pen);

	float eff_r = EffR(spokeCount, spokeWidth);
	CBrush* oldbrush;
	oldbrush = (CBrush * )pDC->SelectStockObject(NULL_BRUSH);
	pDC->Ellipse(-eff_r, -eff_r, eff_r, eff_r);


	pDC->SelectObject(oldpen);
	delete pen;
	pen = new CPen(PS_SOLID, 2, RGB(0, 0, 255));
	CBrush * brush;
	brush = new CBrush(RGB(128, 128, 255));
	pDC->SelectObject(pen);
	oldbrush = pDC->SelectObject(brush);

	pDC->Ellipse(-eff_r + spokeWidth / 2, -eff_r + spokeWidth / 2, eff_r - spokeWidth / 2, eff_r - spokeWidth / 2);

	XFORM staraForma; 
	pDC->GetWorldTransform(&staraForma);

	float angle = 360 / spokeCount;
	float rad_angle = angle * (3.14 / 180);

	for (int i = 0; i < spokeCount; i++) {
		Translate(pDC, eff_r * cosf(rad_angle * i), eff_r * sinf(rad_angle * i));
		Rotate(pDC, 90 + angle*i);
		Trapez(pDC, 0.6 * spokeWidth, 1.4 * spokeWidth, spokeWidth);
		Rotate(pDC, -(90 + angle*i));
		Translate(pDC, -eff_r * cosf(rad_angle * i), -eff_r * sinf(rad_angle * i));
		
	}

	pDC->SetWorldTransform(&staraForma);
	
	pDC->Rectangle(-spokeWidth, -spokeWidth, spokeWidth, spokeWidth);
	CFont arial;
	arial.CreateFontW(18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));
	CFont* oldfont = (CFont*)pDC->SelectObject(arial);
	int oldTA = pDC->SetTextAlign(TA_CENTER);
	CString tekst;
	pDC->SetBkMode(TRANSPARENT);
	tekst.Format(CString("%d zubaca"), spokeCount);
	pDC->TextOutW(0, spokeWidth / 2 + 9, tekst);

	pDC->SelectObject(oldbrush);
	pDC->SelectObject(oldpen);

	delete brush;
	delete pen;


}

void CGDI2012View::DrawScene(CDC* pDC)
{
	XFORM old;
	pDC->GetWorldTransform(&old);
	Translate(pDC, 300, 300);

	Rotate(pDC, angle);
	DrawGear(pDC, 20, 20);
	Rotate(pDC, -angle);
	
	Translate(pDC,EffR(20,20),0);
	Translate(pDC,EffR(10,20),0);

	Rotate(pDC, -angle);
	Rotate(pDC, 16);
	DrawGear(pDC, 10, 20);
	Rotate(pDC, -16);
	Rotate(pDC, angle);

	Translate(pDC, -EffR(10, 20), 0);
	Translate(pDC, -EffR(20, 20), 0);
	
	Translate(pDC, -EffR(20, 20),0);
	Translate(pDC, 0, -EffR(20, 20));
	Translate(pDC, -EffR(10, 20)/4, 0);

	Rotate(pDC, -angle);
	DrawGear(pDC, 10, 20);
	Rotate(pDC, angle);
	pDC->SetWorldTransform(&old);
}


void CGDI2012View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_UP) {
		angle++;
		Invalidate();
	}
	if (nChar == VK_DOWN) {
		angle--;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CGDI2012View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}
