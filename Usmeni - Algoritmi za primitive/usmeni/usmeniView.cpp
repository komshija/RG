
// usmeniView.cpp : implementation of the CusmeniView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "usmeni.h"
#endif

#include "usmeniDoc.h"
#include "usmeniView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CusmeniView

IMPLEMENT_DYNCREATE(CusmeniView, CView)

BEGIN_MESSAGE_MAP(CusmeniView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CusmeniView construction/destruction

CusmeniView::CusmeniView() noexcept
{
	// TODO: add construction code here

}

CusmeniView::~CusmeniView()
{
}

BOOL CusmeniView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CusmeniView drawing




void CusmeniView::OnDraw(CDC* pDC)
{
	CusmeniDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	// Postavljen koord pocetak u centar prozora radi preglednosti algoritma
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), -rect.Height());
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(-rect.Width() / 2, rect.Height() / 2);

	int radius = 300;
	// Strelice gore i dole sluze za promenu ugla za crtanje linije, da bi se menjao nagib

	// ------- LINIJE -------
	NagibniAlgoritam(pDC,0, 0, radius * cos(ugao), radius *sin(ugao), RGB(0, 0, 0)); // ne radi
	//InkrementalniAlgoritam(pDC,0, 0,50 * cos(ugao), 50*sin(ugao), RGB(0, 0, 0)); // radi
	//BresenhamovAlgoritamLinija(pDC, 0, 0, radius * cos(ugao), radius * sin(ugao), RGB(0, 0, 0)); // radi

	// ------- KRUGOVI -------
//	TrigonometrijskiAlgoritamKrug(pDC, 100, RGB(0, 0, 0)); // radi
//	PolinomniAlgoritamKrug(pDC, 100, RGB(0, 0, 0)); // radi
//	BresenhamovAlgoritamKrug(pDC, radius, RGB(0, 0, 0)); // radi

	// ------- ELIPSE -------
	//TrigonometrijskiAlgoritamElipsa(pDC, 200, 100, RGB(0, 0, 0)); // radi
	PolinomniAlgoritamElipsa(pDC, 100, 200, RGB(0, 0, 0)); // da se vidi dal treba se doradi 
	//DiferencijalniPrvogRedaElipsa(pDC, 200, 100, RGB(0, 0, 0)); // radi
	//DiferencijalniDrugogRedaElipsa(pDC, 200, 100, RGB(0, 0, 0)); // radi

}


// CusmeniView printing

BOOL CusmeniView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CusmeniView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CusmeniView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CusmeniView diagnostics

#ifdef _DEBUG
void CusmeniView::AssertValid() const
{
	CView::AssertValid();
}

void CusmeniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CusmeniDoc* CusmeniView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CusmeniDoc)));
	return (CusmeniDoc*)m_pDocument;
}
#endif //_DEBUG


// CusmeniView message handlers
void CusmeniView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const float rad = 3.14 / 180.;
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_UP) ugao += 5 * rad;
	if (nChar == VK_DOWN) ugao -= 5 * rad;
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CusmeniView::WritePixel4(CDC* pDC, int x, int y, COLORREF value)
{
	pDC->SetPixel(x, y, value);
	pDC->SetPixel(-x, y, value);
	pDC->SetPixel(-x, -y, value);
	pDC->SetPixel(x, -y, value);
}

void CusmeniView::WritePixel8(CDC* pDC, int x, int y, COLORREF value)
{
	pDC->SetPixel(x, y, value);
	pDC->SetPixel(-x, y, value);
	pDC->SetPixel(-x, -y, value);
	pDC->SetPixel(x, -y, value);

	pDC->SetPixel(y, x, value);
	pDC->SetPixel(-y, x, value);
	pDC->SetPixel(-y, -x, value);
	pDC->SetPixel(y, -x, value);
	
}

void CusmeniView::NagibniAlgoritam(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value)
{
	float dx, dy, m, y, b, x, xend, yend;
	dx = x1 - x0;
	dy = y1 - y0;
	m = dy / dx;
	b = y1 - m * x1;

	if (abs(m) < 1) {
		if (x0 > x1) {
			x = x1;
			xend = x0;
		}
		else {
			x = x0;
			xend = x1;
		}

		while(x<=xend)
		{
			y = x * m + b;
			pDC->SetPixel(x, int(y + 0.5), value);
			x++;
		}
	}
	else {
		if (y0 > y1) {
			y = y1;
			yend = y0;
		}
		else {
			y = y0;
			yend = y1;
		}

		while( y <= yend)
		{
			x = (y - b) / m;
			pDC->SetPixel(int(x + 0.5), int(y + 0.5), value);
			y++;
		}
	}

}

void CusmeniView::InkrementalniAlgoritam(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value)
{
	float dx, dy, m, y, b, x, xend, yend;
	dx = x1 - x0;
	dy = y1 - y0;
	m = dy / dx;

	if (abs(m) < 1) {

		if (x0 > x1) {
			x = x1;
			y = y1;
			xend = x0;
		}
		else {
			x = x0;
			y = y0;
			xend = x1;
		}

		for (; x <= xend; x++)
		{
			pDC->SetPixel(x, int(y + 0.5), value);
			y += m;
		}
	}
	else {
		m = dx / dy;

		if (y0 > y1) {
			y = y1;
			x = x1;

			yend = y0;
		}
		else {
			y = y0;
			x = x0;
			yend = y1;
		}

		for (; y <= yend; y++)
		{
			pDC->SetPixel(int(x + 0.5), int(y + 0.5), value);
			x += m;
		}
	}

}

void CusmeniView::BresenhamovAlgoritamLinija(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value)
{

	int dx, dy, x, y, incr1, incr2, xend,yend, d;
	int incx, incy;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);

	

	if (dx != 0 && (float)dy / (float)dx < 1.) {
		d = 2 * dy - dx;
		incr1 = 2 * dy;
		incr2 = 2 * (dy - dx);

		x = x0 > x1 ? x1 : x0;
		y = x0 > x1 ? y1 : y0;
		xend = x0 > x1 ? x0 : x1;
		yend = x0 > x1 ? y0 : y1;

		incy = y - yend > 0 ? -1 : 1;

		while (x <= xend) {
			pDC->SetPixel(x, y, value);
			x = x + 1;
			if (d < 0) 
				d += incr1;
			else {
				y = y + incy;
				d += incr2;
			}
		}
	}
	else {
		d = 2 * dx - dy;
		incr1 = 2 * dx;
		incr2 = 2 * (dx - dy);


		y = y0 > y1 ? y1 : y0;
		yend = y0 > y1 ? y0 : y1;
		x = y0 > y1 ? x1 : x0;
		xend = y0 > y1 ? x0 : x1;

		incx = x - xend > 0 ? -1 : 1;


		while (y <= yend) {
			pDC->SetPixel(x, y, value);
			y = y + 1;
			if (d < 0)
				d += incr1;
			else {
				x = x + incx;
				d += incr2;
			}
		}
	}

}

void CusmeniView::TrigonometrijskiAlgoritamKrug(CDC* pDC, int r, COLORREF value)
{
	float alfa, dvapi = 6.283185, pi4 = 0.785398;
	float step = dvapi / (7 * r);
	int x, y;
	for (alfa = 0; alfa < pi4; alfa += step)
	{
		x = int(r * cos(alfa) + 0.5);
		y = int(r * sin(alfa) + 0.5);
		WritePixel8(pDC, x, y, value);
	}
}

void CusmeniView::PolinomniAlgoritamKrug(CDC* pDC, int r, COLORREF value)
{
	int x, y, xend;
	xend = (int)(r / sqrt(2) + 0.5);
	for (x = 0; x <= xend; x++)
	{
		y = (int)(sqrt(r * r - x * x) + 0.5);
		WritePixel8(pDC, x, y, value);
	}
}

void CusmeniView::BresenhamovAlgoritamKrug(CDC* pDC, int r, COLORREF value)
{
	int x, y, d;
	x = r; y = 0;
	d = 3 - 2 * r;
	while (x > y) {
		WritePixel8(pDC, x, y, value);
		if (d < 0) 
			d += 4 * y + 6;
		else {
			d += 4 * (y - x) + 10;
			x--;
		}
		y++;
	}
	if (x == y)
		WritePixel8(pDC, x, y, value);
}

void CusmeniView::TrigonometrijskiAlgoritamElipsa(CDC* pDC, int a, int b, COLORREF value)
{
	float alfa, dvapi = 6.283185, pi2 = 1.570796;
	float step = dvapi / (7 * max(a,b));
	int x, y;
	for (alfa = 0; alfa < pi2; alfa += step)
	{
		x = int(a * cos(alfa) + 0.5);
		y = int(b * sin(alfa) + 0.5);
		WritePixel4(pDC, x, y, value);
	}
}

void CusmeniView::PolinomniAlgoritamElipsa(CDC* pDC, int a, int b, COLORREF value)
{
	int x, y, a2,b2;
	a2 = a * a;
	b2 = b * b;
	for (x = 0; x <= a/2; x++) {
		y = (int)(b * sqrt(1 - x * x / a2) + 0.5);
		WritePixel4(pDC, x, y,value);
	}
	for (; y >= 0; y--) {
		x = (int)(a * sqrt(1 - y * y / b2) + 0.5);
		WritePixel4(pDC, x, y, value);
	}

}

void CusmeniView::DiferencijalniPrvogRedaElipsa(CDC* pDC, int a, int b, COLORREF value)
{
	float ba, ab, x0, x1, y0, y1, Dphi;
	Dphi = 3.1416 / 180.0;
	ba = Dphi * b / a; ab = Dphi * a / b;
	x0 = a; y0 = 0;
	for (int j = 0; j < 90; j++) {
		x1 = x0 - ab * y0;
		y1 = y0 + ba * x0;
		BresenhamovAlgoritamLinija(pDC, x0, y0, x1, y1, value);
		BresenhamovAlgoritamLinija(pDC, -x0, y0, -x1, y1, value);
		BresenhamovAlgoritamLinija(pDC, x0, -y0, x1, -y1, value);
		BresenhamovAlgoritamLinija(pDC, -x0, -y0, -x1, -y1, value);
		x0 = x1;
		y0 = y1;
	}
}

void CusmeniView::DiferencijalniDrugogRedaElipsa(CDC* pDC, int a, int b, COLORREF value)
{
	float x0, x1, y0, y1, x2, y2, k;
	k = 3.1416 / 180.0;
	x0 = a; y0 = 0;
	x1 = a * cos(k);
	y1 = b * sin(k);
	k = 2 - k * k;
	for (int j = 0; j < 90; j++) {
		BresenhamovAlgoritamLinija(pDC, x0, y0, x1, y1, value);
		BresenhamovAlgoritamLinija(pDC, -x0, y0, -x1, y1, value);
		BresenhamovAlgoritamLinija(pDC, x0, -y0, x1, -y1, value);
		BresenhamovAlgoritamLinija(pDC, -x0, -y0, -x1, -y1, value);
		x2 = k * x1 - x0;
		y2 = k * y1 - y0;
		x0 = x1;
		y0 = y1;
		x1 = x2;
		y1 = y2;
	}
}

