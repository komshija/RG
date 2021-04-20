
// GDI-IspitView.cpp : implementation of the CGDIIspitView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI-Ispit.h"
#endif

#include "GDI-IspitDoc.h"
#include "GDI-IspitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDIIspitView

IMPLEMENT_DYNCREATE(CGDIIspitView, CView)

BEGIN_MESSAGE_MAP(CGDIIspitView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	//	ON_WM_MOVE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CGDIIspitView construction/destruction

CGDIIspitView::CGDIIspitView() noexcept
{
	// TODO: add construction code here
	img = new DImage();
	img->Load(CString("sand.jpg"));
}

CGDIIspitView::~CGDIIspitView()
{
}

BOOL CGDIIspitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDIIspitView drawing

void CGDIIspitView::Translate(CDC* pDC, float dx, float dy, bool rightmul)
{
	XFORM forma = {
	1,
	0,
	0,
	1,
	dx,
	dy
	};

	pDC->ModifyWorldTransform(&forma, rightmul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDIIspitView::Rotate(CDC* pDC, float angle, bool rightmul)
{
	angle *= 3.14 / 180.;
	XFORM forma = {
	cos(angle),
	sin(angle),
	-sin(angle),
	cos(angle),
	0,
	0
	};

	pDC->ModifyWorldTransform(&forma, rightmul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDIIspitView::Scale(CDC* pDC, float sx, float sy, bool rightmul)
{
	XFORM forma = {
	1,
	sx,
	sy,
	1,
	0,
	0
	};

	pDC->ModifyWorldTransform(&forma, rightmul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDIIspitView::Shear(CDC* pDC, float sx, float sy, bool rightmul)
{
	XFORM forma = {
	1,
	sx,
	sy,
	1,
	0,
	0
	};

	pDC->ModifyWorldTransform(&forma, rightmul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDIIspitView::Mirror(CDC* pDC, bool x, bool y, bool rightmul)
{
	XFORM forma = {
	x ? 1 : -1,
	0,
	0,
	y ? 1 : -1,
	0,
	0
	};

	pDC->ModifyWorldTransform(&forma, rightmul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}


void CGDIIspitView::OnDraw(CDC* pDC)
{
	CGDIIspitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	pDC->SetGraphicsMode(GM_ADVANCED);
	//Translate(pDC, 200, 200, false);


	//DrawFigure(pDC, 300, 300, 25, 10, 100, 6, 10);


	//DrawTop(pDC, 100);
	//DrawTop2(pDC, 100);
	//DrawTail(pDC, 20, 5, 45);

	//DrawArrow(pDC, 25, 4, NULL, RGB(255, 0, 0), RGB(0, 0, 0), 90);
	//DrawRoundedText(pDC, CRect(500, 300, 500 + 300, 300 + 200), 0, RGB(0, 255, 0), RGB(255, 0, 0), CString("Text"), RGB(255, 255, 255), mpoint, 12, 4, RGB(255, 0, 0), RGB(0, 0, 0));

	//DrawCanTop(pDC, NULL, 100, 100, 30, 60, 6, 100);
	//DrawCanWrapper(pDC, NULL, 100, 100, 30, 60, 6, 100);
	//DrawCan

	//Translate(pDC, 200, 200, false);
	//DrawWheel(pDC, 100, 80, 20);
	//DrawWP(pDC, 30, 20, 5, 200, 5, dest);


	//Testiraj Cmipmap

	//SaveRect(pDC, CRect(100, 100, 100 + 300, 100 + 200), CString("test.jpg"));

	DrawPuzzle(pDC, CRect(100, 100, 100 + 600, 100 + 350), 6, 7, 1.7);

	//DrawTextRound(pDC, CString("Your score: 9pts"));

	//DrawLake(pDC);

	//DrawRotated(CString("test.jpg"), 60);
	/*img->Width();
	Resample(100, 100, img);
	img->Draw(pDC, CRect(0, 0, 100, 100), CRect(0, 0, 100, 100));*/

	//DrawGradientBitmap(pDC, 100, 200, NULL, NULL);

	//DrawFigureTriangles(pDC);


	//DrawCycle(pDC, 50, 10, 2);
	//DrawBicycle(pDC, 50, 10, 2, 30, 45);

	//DrawVirusCycle(pDC, 50, 6, 2);

	//Distort(pDC, 1.4);
	//DrawPlate(pDC, CString("Text"));

	//DrawGhost(pDC, CRect(100, 120, 196, 216));


}


// CGDIIspitView printing

BOOL CGDIIspitView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDIIspitView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDIIspitView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDIIspitView diagnostics

#ifdef _DEBUG
void CGDIIspitView::AssertValid() const
{
	CView::AssertValid();
}

void CGDIIspitView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDIIspitDoc* CGDIIspitView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIIspitDoc)));
	return (CGDIIspitDoc*)m_pDocument;
}
#endif //_DEBUG


// CGDIIspitView message handlers

void CGDIIspitView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//dest += 10;
	//Invalidate();
	CView::OnLButtonDown(nFlags, point);
}

//void CGDIIspitView::OnMove(int x, int y)
//{
//	CView::OnMove(x, y);
//	mpoint = CPoint(x, y);
//	Invalidate();
//	// TODO: Add your message handler code here
//}

void CGDIIspitView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//mpoint = point;
	//Invalidate();
	CView::OnMouseMove(nFlags, point);
}

void CGDIIspitView::DrawConeBottom(CDC* pDC, float cx, float cy, float a, float b, float h, float n)
{
	XFORM stara;
	pDC->GetWorldTransform(&stara);
	Translate(pDC, cx, cy, false);
	float toRad = 3.14 / 180.;
	float stepAngleKrug = (2 * 3.14) / (3 * n);

	CBrush* oldbrush, * brush;
	brush = new CBrush(RGB(255, 255, 255));
	int boja = 255 / n;

	oldbrush = pDC->SelectObject(brush);
	float stepA = a / (n / 2);
	float stepB = b / (n / 2);

	CPoint* nizKupa = new CPoint[3];

	nizKupa[0] = CPoint(0, 0);
	int bpos = h;

	for (int i = 1; i <= n; i++) {
		if (i == (n / 2) + 1)
			stepB = -stepB;

		nizKupa[1] = CPoint(-a + (i - 1) * stepA, bpos);
		nizKupa[2] = CPoint(-a + i * stepA, bpos + stepB);

		bpos += stepB;

		pDC->Polygon(nizKupa, 3);
		pDC->SelectObject(oldbrush);
		delete brush;
		brush = new CBrush(RGB(255 - (i + 1) * boja, 255 - (i + 1) * boja, 255 - (i + 1) * boja));
		pDC->SelectObject(brush);
	}


	delete[] nizKupa;

	pDC->SelectObject(oldbrush);
	delete brush;
	Translate(pDC, 0, h, false);

	//beli brush
	brush = new CBrush(RGB(255, 255, 255));
	pDC->SelectObject(brush);


	CPoint* niz = new CPoint[3 * n];

	for (int i = 0; i < 3 * n; i++) {
		niz[i] = CPoint(a * cos(i * stepAngleKrug), b * sin(i * stepAngleKrug));
	}

	pDC->Polygon(niz, 3 * n);
	Translate(pDC, 0, -h, false);
	delete[] niz;

	pDC->SelectObject(oldbrush);
	Translate(pDC, -cx, -cy, false);

	pDC->SetWorldTransform(&stara);
}

void CGDIIspitView::DrawConeTop(CDC* pDC, float cx, float cy, float a, float b, float h, float n)
{
	XFORM stara;
	pDC->GetWorldTransform(&stara);
	Translate(pDC, cx, cy, false);
	float toRad = 3.14 / 180.;
	float stepAngleKrug = (2 * 3.14) / (3 * n);

	CBrush* oldbrush, * brush;
	brush = new CBrush(RGB(255, 255, 255));
	int boja = 255 / n;

	oldbrush = pDC->SelectObject(brush);
	float stepA = a / (n / 2);
	float stepB = b / (n / 2);

	CPoint* nizKupa = new CPoint[3];

	nizKupa[0] = CPoint(0, 0);
	int bpos = h;

	for (int i = 1; i <= n; i++) {
		if (i == (n / 2) + 1)
			stepB = -stepB;

		nizKupa[1] = CPoint(-a + (i - 1) * stepA, bpos);
		nizKupa[2] = CPoint(-a + i * stepA, bpos + stepB);

		bpos += stepB;

		pDC->Polygon(nizKupa, 3);
		pDC->SelectObject(oldbrush);
		delete brush;
		brush = new CBrush(RGB(255 - (i + 1) * boja, 255 - (i + 1) * boja, 255 - (i + 1) * boja));
		pDC->SelectObject(brush);
	}


	delete[] nizKupa;

	pDC->SelectObject(oldbrush);
	delete brush;
	Translate(pDC, -cx, -cy, false);
	pDC->SetWorldTransform(&stara);
}

// RESI OVO
void CGDIIspitView::DrawFigure(CDC* pDC, float cx, float cy, float a, float b, float h, float n, float r)
{

	XFORM stara;
	pDC->GetWorldTransform(&stara);

	Rotate(pDC, 45, false);
	for (int i = 0; i < 4; i++) {
		Translate(pDC, -cx, -cy, false);
		Translate(pDC, r, r, false);
		if (i < 2)
			DrawConeBottom(pDC, cx, cy, a, b, h, n);
		else
			DrawConeTop(pDC, cx, cy, a, b, h, n);
		Translate(pDC, -r, -r, false);
		Translate(pDC, cx, cy, false);
		Rotate(pDC, 90, false);
	}

	pDC->SetWorldTransform(&stara);
}

void CGDIIspitView::DrawTop(CDC* pDC, int size)
{
	pDC->BeginPath();

	float r = size / 2;

	float r1 = r * 0.75;
	float r2 = r1 / 2;

	int old = pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->MoveTo(r1, 0);
	pDC->ArcTo(-r1, -r1, r1, r1, r1, 0, 0, r1);
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(-r2, r1, r2, r1 + 2 * r2, 0, r1, 0, r1 + 2 * r2);
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(-r1, -r1 - 2 * r2, r1, r1 + 2 * r2, 0, r1 + 2 * r2, r1, 0);

	pDC->EndPath();

	pDC->StrokeAndFillPath();

}

void CGDIIspitView::DrawTop2(CDC* pDC, int size)
{
	XFORM stara;
	pDC->GetWorldTransform(&stara);

	Rotate(pDC, -90, false);
	Mirror(pDC, false, true, false);
	DrawTop(pDC, size);


	pDC->SetWorldTransform(&stara);

}

void CGDIIspitView::DrawTail(CDC* pDC, int size, int count, float alpha)
{
	XFORM stara;
	pDC->GetWorldTransform(&stara);

	for (int i = 0; i < count; i++)
	{
		Rotate(pDC, -alpha, false);
		pDC->Ellipse(0, -size / 2., 2 * size, size / 2.);
		Translate(pDC, 2 * size, 0, false);
	}

	Translate(pDC, (size / 2.) * 0.75, 0, false);
	DrawTop2(pDC, size);

	pDC->SetWorldTransform(&stara);
}

void CGDIIspitView::DrawArrow(CDC* pDC, double r, int n, COLORREF colFill, COLORREF colLine, float angle)
{
	XFORM stara;
	pDC->GetWorldTransform(&stara);
	Rotate(pDC, angle, false);

	int x_init = 0;
	CBrush* oldb, * brush;
	brush = new CBrush(colFill);
	oldb = pDC->SelectObject(brush);

	CPen* oldp, * pen;
	pen = new CPen(PS_SOLID, 1, colLine);
	oldp = pDC->SelectObject(pen);

	for (int i = 0; i < n; i++) {
		int br_kruzica = n - i;
		int y_init = -(br_kruzica * 2 * r + r * (br_kruzica - 1)) / 2.;

		for (int j = 0; j < br_kruzica; j++) {
			pDC->Ellipse(x_init, y_init, x_init + 2 * r, y_init + 2 * r);
			y_init += 3 * r;
		}
		x_init += 3 * r;
	}

	pDC->SelectObject(oldp);
	pDC->SelectObject(oldb);
	delete brush;
	delete pen;


	pDC->SetWorldTransform(&stara);
}

void CGDIIspitView::DrawRoundedText(CDC* pDC, CRect rcRect, double perc, COLORREF colFillRect, COLORREF colLineRect, CString text, COLORREF colText, CPoint ptMouse, double r, int n, COLORREF colFillArrow, COLORREF colLineArrow)
{
	XFORM stara;
	pDC->GetWorldTransform(&stara);


	CBrush* oldb, * brush;
	brush = new CBrush(colFillRect);
	oldb = pDC->SelectObject(brush);

	CPen* oldp, * pen;
	pen = new CPen(PS_SOLID, 1, colLineRect);
	oldp = pDC->SelectObject(pen);

	pDC->RoundRect(rcRect, CPoint(4 * r, 4 * r));

	pDC->SelectObject(oldp);
	pDC->SelectObject(oldb);
	delete brush;
	delete pen;

	//text

	CFont font;
	font.CreateFontW(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));
	COLORREF oldTextCol = pDC->SetTextColor(colText);
	CFont* oldFont;
	oldFont = pDC->SelectObject(&font);
	int bkmode = pDC->SetBkMode(TRANSPARENT);
	int ta = pDC->SetTextAlign(TA_CENTER);

	CPoint center = rcRect.CenterPoint();
	pDC->TextOutW(center.x, center.y, text);

	pDC->SetTextAlign(ta);
	pDC->SetBkMode(bkmode);
	pDC->SelectObject(oldFont);
	pDC->SetTextColor(oldTextCol);

	CRgn glavni, pom;
	glavni.CreateRectRgn(rcRect.left + 4 * r, rcRect.top + 4 * r, rcRect.right - 4 * r, rcRect.bottom - 4 * r);

	pom.CreateEllipticRgn(rcRect.left, rcRect.top, rcRect.left + 4 * r, rcRect.top + 4 * r);
	glavni.CombineRgn(&glavni, &pom, RGN_OR);
	pom.DeleteObject();

	pom.CreateEllipticRgn(rcRect.left, rcRect.bottom - 4 * r, rcRect.left + 4 * r, rcRect.bottom);
	glavni.CombineRgn(&glavni, &pom, RGN_OR);
	pom.DeleteObject();

	pom.CreateEllipticRgn(rcRect.right - 4 * r, rcRect.bottom - 4 * r, rcRect.right, rcRect.bottom);
	glavni.CombineRgn(&glavni, &pom, RGN_OR);
	pom.DeleteObject();

	pom.CreateEllipticRgn(rcRect.right - 4 * r, rcRect.top, rcRect.right, rcRect.top + 4 * r);
	glavni.CombineRgn(&glavni, &pom, RGN_OR);
	pom.DeleteObject();

	pom.CreateRectRgn(rcRect.left + 4 * r, rcRect.top, rcRect.right - 4 * r, rcRect.bottom);
	glavni.CombineRgn(&glavni, &pom, RGN_OR);
	pom.DeleteObject();

	pom.CreateRectRgn(rcRect.left, rcRect.top + 4 * r, rcRect.right, rcRect.bottom - 4 * r);
	glavni.CombineRgn(&glavni, &pom, RGN_OR);
	pom.DeleteObject();

	bool drawArrows = glavni.PtInRegion(ptMouse);

	if (drawArrows) {
		Translate(pDC, rcRect.right + r, rcRect.top + rcRect.Height() / 2, false);
		DrawArrow(pDC, r, n, colFillArrow, colLineArrow, 0);
		Translate(pDC, -rcRect.Width() - 2 * r, 0, false);
		DrawArrow(pDC, r, n, colFillArrow, colLineArrow, 180);
		Translate(pDC, rcRect.Width() / 2 + r, rcRect.Height() / 2 + r, false);
		DrawArrow(pDC, r, n, colFillArrow, colLineArrow, 90);
		Translate(pDC, 0, -rcRect.Height() - 2 * r, false);
		DrawArrow(pDC, r, n, colFillArrow, colLineArrow, -90);
	}


	pDC->SetWorldTransform(&stara);
}

void CGDIIspitView::DrawCanTop(CDC* pDC, DImage* img, float cX, float cY, float a, float b, int n)
{
	float step = (360. / n) * (3.14 / 180.);
	CPoint* poly = new CPoint[n];
	for (int i = 0; i < n; i++)
		poly[i] = CPoint(cX + a * cos(i * step), cY + b * sin(i * step));

	CRgn rgn;
	rgn.CreatePolygonRgn(poly, 4, ALTERNATE);
	pDC->SelectClipRgn(&rgn);

	//sacuvas stari
	delete[] poly;

	int w = img->Width();
	int h = img->Height();

	img->Draw(pDC, CRect(w / 2 - h / 4, 0, w / 2 + h / 4, h / 2), CRect(cX - a, cY - b, cX + a, cY + b));

	CRect client;
	GetClientRect(&client);
	CRgn old;
	old.CreateRectRgn(client.left, client.top, client.right, client.bottom);
	pDC->SelectClipRgn(&old);

}


//Sa Shear ne bih znao da uradim, ali da se iscrta kao poligon znao bih
void CGDIIspitView::DrawCanWrapper(CDC* pDC, DImage* img, float cX, float cY, float a, float b, int n, float h)
{

}

void CGDIIspitView::DrawCan(CDC* pDC, float cX, float cY, float a, float b, int n, float h)
{
	DImage* img = new DImage();
	img->Load(CString("limenka.jpg"));

	DrawCanTop(pDC, img, cX, cY, a, b, n);
	DrawCanWrapper(pDC, img, cX, cY, a, b, n, h);
	delete img;
}

void CGDIIspitView::DrawWheel(CDC* pDC, float r1, float r2, float w)
{
	float p = r1 - r2;
	for (int i = 0; i < 3; i++) {
		pDC->Rectangle(-w / 2, -r2 - p, w / 2, r2 + p);
		Rotate(pDC, 120, false);
	}
	pDC->BeginPath();
	pDC->Ellipse(-r1, -r1, r1, r1);
	pDC->Ellipse(-r2, -r2, r2, r2);
	pDC->EndPath();

	pDC->StrokeAndFillPath();

}

void CGDIIspitView::DrawWP(CDC* pDC, float r1, float r2, float w, float L, float alpha, float d)
{
	CPoint* niz = new CPoint[3];

	niz[0] = CPoint(0, 0);
	niz[1] = CPoint(0, (float)L * abs(tan(alpha * (3.14 / 180.))));
	niz[2] = CPoint(L, (float)L * abs(tan(alpha * (3.14 / 180.))));

	pDC->Polygon(niz, 3);

	delete[]niz;

	Translate(pDC, 0, -r1, false);
	Rotate(pDC, alpha, false);
	Translate(pDC, d, 0, false);
	Rotate(pDC, (360 * d) / (2 * 3.14 * r1), false);
	DrawWheel(pDC, r1, r2, w);

}

void CGDIIspitView::DrawLake(CDC* pDC)
{


	CPoint p(0, 0);
	int r = 25;
	pDC->SetArcDirection(AD_CLOCKWISE);
	CString text("213425516452453136");
	for (int i = 0; i < text.GetLength(); i++) {
		int ad = pDC->GetArcDirection();

		switch (text[i]) {

		case '1':
			//1
			if (ad == AD_CLOCKWISE) {
				pDC->Arc(p.x - r, p.y, p.x + r, p.y + 2 * r, p.x, p.y, p.x + r, p.y + r);
				p.x += r;
				p.y += r;
			}
			else {
				pDC->Arc(p.x - 2 * r, p.y - r, p.x, p.y + r, p.x, p.y, p.x - r, p.y - r);
				p.x -= r;
				p.y -= r;
			}
			if (i + 1 < text.GetLength() && text[i + 1] != '6')
				pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
			break;

		case '2':
			//2
			if (ad == AD_CLOCKWISE) {
				pDC->Arc(p.x, p.y - r, p.x + r * 2, p.y + r, p.x, p.y, p.x + r, p.y - r);
				p.x += r;
				p.y -= r;
			}
			else {
				pDC->Arc(p.x - r, p.y, p.x + r, p.y + 2 * r, p.x, p.y, p.x - r, p.y + r);
				p.x -= r;
				p.y += r;
			}

			pDC->SetArcDirection(AD_CLOCKWISE);
			break;

		case '3':
			//3
			if (ad == AD_CLOCKWISE) {
				pDC->Arc(p.x - r, p.y - 2 * r, p.x + r, p.y, p.x, p.y, p.x - r, p.y - r);
				p.x -= r;
				p.y -= r;
			}
			else {
				pDC->Arc(p.x, p.y - r, p.x + r * 2, p.y + r, p.x, p.y, p.x + r, p.y + r);
				p.x += r;
				p.y += r;
			}


			pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
			break;
		case '4':
			//4
			if (ad == AD_CLOCKWISE) {
				pDC->Arc(p.x - 2 * r, p.y - r, p.x, p.y + r, p.x, p.y, p.x - r, p.y + r);
				p.x -= r;
				p.y += r;
			}
			else {
				pDC->Arc(p.x - r, p.y - 2 * r, p.x + r, p.y, p.x, p.y, p.x + r, p.y - r);
				p.x += r;
				p.y -= r;
			}
			if (i + 1 < text.GetLength() && text[i + 1] == '5')
				pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
			else
				pDC->SetArcDirection(AD_CLOCKWISE);

			break;

		case '5':
			//5


			pDC->MoveTo(p);
			if (ad == AD_CLOCKWISE)
			{
				pDC->LineTo(p.x + r, p.y);
				p.x += r;
			}
			else
			{
				pDC->LineTo(p.x - r, p.y);
				p.x -= r;
			}
			break;

		case '6':
			//6


			pDC->MoveTo(p);
			if (ad == AD_CLOCKWISE)
			{
				pDC->LineTo(p.x, p.y + r);
				p.y += r;
			}
			else
			{
				pDC->LineTo(p.x, p.y - r);
				p.y -= r;
			}
			break;
		}
	}
}

void CGDIIspitView::SaveRect(CDC* pDC, CRect rectView, CString name)
{

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rectView.Width(), rectView.Height());
	memDC->SelectObject(&bmp);

	memDC->BitBlt(0, 0, rectView.Width(), rectView.Height(), pDC, rectView.left, rectView.top, SRCCOPY);

	DImage* img = new DImage(bmp);
	img->Save(name);
	delete img;
	delete memDC;


}

void CGDIIspitView::DrawPuzzle(CDC* pDC, CRect rcRect, int nRows, int nCols, float radio)
{
	int rowHeight = rcRect.Height() / nRows;
	int colWidth = rcRect.Width() / nCols;

	int duzacount = nCols / 2 + 1;
	int kracacount = nCols - duzacount;

	float duza = colWidth * radio;
	float kraca = colWidth / radio;

	float razlika = (duza - kraca) / 2.;

	for (int i = 0; i < nRows; i++) {
		int x1 = rcRect.left;
		int x2 = rcRect.left;
		for (int j = 0; j < nCols; j++) {
			int inc1, inc2;

			if (i % 2 == 0) {
				inc1 = colWidth;
				inc2 = j % 2 == 0 ? colWidth - razlika : colWidth + razlika;
			}
			else {
				inc1 = j % 2 == 0 ? - razlika : colWidth + razlika;
				inc2 = colWidth;
			}

			CPoint trap[4];
		

			trap[0] = CPoint(x1, rcRect.top + i * rowHeight);
			trap[1] = CPoint(x2, rcRect.top + (i + 1) * rowHeight);
			trap[2] = CPoint(x2 + inc2, rcRect.top + (i + 1) * rowHeight);
			trap[3] = CPoint(x1 + inc1, rcRect.top + i * rowHeight);
			

			pDC->Polygon(trap, 4);

			x1 += inc1;
			x2 += inc2;
		}
	}
}

void CGDIIspitView::DrawTextRound(CDC* pDC, CString text)
{
	XFORM stara;
	pDC->GetWorldTransform(&stara);
	CFont* font = new CFont();
	font->CreateFontW(18, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));
	CFont* old = pDC->SelectObject(font);
	int radius = 100;
	Rotate(pDC, -180, false);
	float angleStep = 180.0 / text.GetLength();

	pDC->SetTextAlign(TA_CENTER);

	for (int i = 0; i < text.GetLength(); i++) {

		Translate(pDC, radius, 0, false);
		Rotate(pDC, 90 + angleStep, false);
		pDC->TextOutW(0, 0, CString(text[i]));
		Rotate(pDC, -90 - angleStep, false);
		Translate(pDC, -radius, 0, false);
		Rotate(pDC, angleStep, false);

	}

	pDC->SelectObject(old);
	delete font;
	pDC->SetWorldTransform(&stara);
}

void CGDIIspitView::DrawRotated(CString name, float angle)
{
	const float toRad = 3.14 / 180.0;

	DImage* img = new DImage();
	img->Load(name);

	int cx = img->Width() / 2;
	int cy = img->Height() / 2;

	int x[4] = { -cx,-cx,cx,cx }, y[4] = { -cy,cy,cy,-cy };

	//Odredimo tacke temena nakon rotacije iz ugla lokalnog koordinatnog sistema koji se nalazi u centru slike
	for (int i = 0; i < 4; i++)
		GetXY(&x[i], &y[i], angle * toRad);
	// Nadjemo maksimum i minimum po obe koordinate
	int max_x = 0, max_y = 0, min_x = x[0], min_y = y[0];
	for (int i = 0; i < 4; i++) {
		max_x = max(max_x, x[i]);
		max_y = max(max_y, y[i]);
		min_x = min(min_x, x[i]);
		min_y = min(min_y, y[i]);
	}

	//Razlika je nova sirina i visina slike bez odsecanja
	int nova_sirina = max_x - min_x;
	int nova_visina = max_y - min_y;

	//Klasicno kreiranje memDC-a
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(GetDC());
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(GetDC(), nova_sirina, nova_visina);
	memDC->SelectObject(bmp);

	memDC->SetGraphicsMode(GM_ADVANCED);

	//Cuvamo stanje za transformacije
	XFORM stara;
	memDC->GetWorldTransform(&stara);

	//Transliramo u centar novokreirane bitmape pa zarotiramo za ugao
	Translate(memDC, nova_sirina / 2, nova_visina / 2, false);
	Rotate(memDC, angle, false);

	//CRTAMO CELU SLIKU, ALI CRTAMO IZ UGLA LOKALNOG KOORDINATNOG SISTEMA
	img->Draw(memDC, CRect(0, 0, img->Width(), img->Height()), CRect(-img->Width() / 2, -img->Height() / 2, img->Width() / 2, img->Height() / 2));

	//Ponistavamo transformacije
	memDC->SetWorldTransform(&stara);

	//Sacuvamo bitmapu
	DImage nova(bmp);
	nova.Save(CString("rotirana.jpg"));

	delete img;
	delete memDC;
}

void CGDIIspitView::GetXY(int* x, int* y, float angle)
{
	int xt = *x * cos(angle) - *y * sin(angle);
	int yt = *x * sin(angle) + *y * cos(angle);
	*x = xt;
	*y = yt;
}

void CGDIIspitView::Resample(int x, int y, DImage* img)
{
	int w = img->Width();
	int h = img->Height();
	int bpp = img->BPP();
	unsigned char* resampled = new unsigned char[x * y * bpp];
	unsigned char* buffer = img->GetDIBBits();

	for (int i = 0; i < y; i++) {
		float ny = (float)i / (float)y;
		int r = h * ny;
		for (int j = 0; j < x; j++) {
			float nx = (float)j / (float)x;
			int c = w * nx;

			for (int k = 0; k < bpp - 1; k++)
				resampled[i * x + j + k] = (unsigned char)((buffer[r * w + c + k] + buffer[r * w + c + bpp + k] + buffer[(r + 1) * w + c + k] + buffer[(r + 1) * w + c + bpp + k]) / 4);
			resampled[i * x + j + bpp - 1] = buffer[r * w + c + bpp - 1];
		}
	}

	CBitmap bmp;
	bmp.CreateBitmap(x, y, bpp, 8, resampled);
	DImage resampledImg(bmp);
	*img = resampledImg;
}

CDC* CGDIIspitView::DrawGradientBitmap(CDC* pDC, float w, float h, COLORREF col1, COLORREF col2)
{
	CBitmap* bmp = new CBitmap();
	bmp->CreateCompatibleBitmap(pDC, (int)w, (int)h);
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	memDC->SelectObject(bmp);

	int top = 10;
	int left = 10;
	int right = 200;
	int bottom = 200;
	int radius = 20;


	pDC->BeginPath();
	pDC->RoundRect(left, top, right, bottom, radius, radius);
	pDC->EndPath();
	pDC->SelectClipPath(RGN_COPY);

	TRIVERTEX vertices[2];

	vertices[0].x = left;
	vertices[0].y = top;
	vertices[0].Red = 0xffff;
	vertices[0].Green = 0;
	vertices[0].Blue = 0;
	vertices[0].Alpha = 0xffff;

	vertices[1].x = right;
	vertices[1].y = bottom;
	vertices[1].Red = 0;
	vertices[1].Green = 0;
	vertices[1].Blue = 0xffff;
	vertices[1].Alpha = 0xffff;

	GRADIENT_RECT r;
	r.UpperLeft = 0;
	r.LowerRight = 1;

	pDC->GradientFill(vertices, 2, &r, 1, GRADIENT_FILL_RECT_V);

	return memDC;
}

void CGDIIspitView::DrawTriangle(CDC* pDC)
{
	CPoint niz[3];
	niz[0] = CPoint(0, 0);
	niz[1] = CPoint(0, 200);
	niz[2] = CPoint(100, 0);
	pDC->Polygon(niz, 3);
}

void CGDIIspitView::DrawFigureTriangles(CDC* pDC)
{
	Translate(pDC, 300, 300, false);
	Rotate(pDC, -180, false);
	DrawTriangle(pDC);
	Mirror(pDC, false, true, false);
	DrawTriangle(pDC);
	Rotate(pDC, -90, false);
	DrawTriangle(pDC);
	Mirror(pDC, true, false, false);
	DrawTriangle(pDC);

}

void CGDIIspitView::DrawCycle(CDC* pDC, int r, int n, int d)
{
	CPen* oldp, * pen;
	pen = new CPen(PS_SOLID, d, RGB(0, 0, 128));
	CBrush* oldb, * brush;
	brush = new CBrush(RGB(0, 0, 128));
	oldp = pDC->SelectObject(pen);
	oldb = pDC->SelectObject(brush);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Ellipse(-r, -r, r, r);

	float step = (360 / n);
	pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM stara;
	pDC->GetWorldTransform(&stara);


	for (int i = 0; i < n; i++) {
		pDC->MoveTo(0, 0);
		pDC->LineTo(r, 0);
		Rotate(pDC, step, false);
	}

	pDC->SetWorldTransform(&stara);

	pDC->SelectObject(brush);
	pDC->Ellipse(-d * 2, -d * 2, d * 2, d * 2);
	pDC->SelectObject(oldp);
	pDC->SelectObject(oldb);
	delete pen;
	delete brush;
}

void CGDIIspitView::DrawBicycle(CDC* pDC, int r, int n, int d, int alpha, int beta)
{
	//pDC->SetGraphicMode(GM_ADVANCED);

	//Tockovi
	XFORM stara, stara1;
	pDC->GetWorldTransform(&stara1);
	pDC->GetWorldTransform(&stara);

	DrawCycle(pDC, r, n, d);
	Translate(pDC, (1.4 + 0.75) * r, 0.75 * r, false);
	DrawCycle(pDC, 0.25 * r, n, d);
	//Translate(pDC,-(1.4+0.75)*r,-0.75*r,false);
	pDC->SetWorldTransform(&stara);

	//Rucice i pedale
	CPen* oldp, * pen;
	pen = new CPen(PS_SOLID, d, RGB(0, 0, 128));
	oldp = pDC->SelectObject(pen);

	pDC->MoveTo(0, 0);
	pDC->LineTo(0, -r * 1.6);
	pDC->LineTo(0.2 * r, -r * 1.6);
	pDC->MoveTo(0, 0);

	pDC->GetWorldTransform(&stara);
	Rotate(pDC, alpha, false);
	pDC->MoveTo(-0.4 * r, 0);
	pDC->LineTo(0.4 * r, 0);
	Translate(pDC, 0.4 * r, 0, false);
	Rotate(pDC, -alpha, false);
	pDC->MoveTo(-0.1 * r, 0);
	pDC->LineTo(0.1 * r, 0);
	Rotate(pDC, alpha, false);
	Translate(pDC, -2 * 0.4 * r, 0, false);
	Rotate(pDC, -alpha, false);
	pDC->MoveTo(-0.1 * r, 0);
	pDC->LineTo(0.1 * r, 0);
	pDC->SetWorldTransform(&stara);

	//Lukovi
	int ad = pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->MoveTo(0, -r * 1.4);
	pDC->ArcTo(-r * 1.4, -r * 1.4, r * 1.4, r * 1.4, 0, -r * 1.4, r * 1.4, 0);
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(r * 1.4, -r * 0.75, r * (1.4 + 2 * 0.75), r * 0.75, r * 1.4, 0, (1.4 + 0.75) * r, r * 0.75);
	pDC->MoveTo(r * 1.4, 0);
	pDC->LineTo(r * 1.6, 0);
	pDC->SetArcDirection(ad);

	//Sediste
	pDC->GetWorldTransform(&stara);
	Rotate(pDC, -beta, false);
	pDC->MoveTo(r * 1.4, 0);
	pDC->LineTo(r * 1.6, 0);
	Translate(pDC, r * 1.6, 0, false);
	Rotate(pDC, beta, false);
	pDC->MoveTo(-r * 0.15, 0);
	pDC->LineTo(r * 0.15, 0);

	pDC->SetWorldTransform(&stara1);

	pDC->SelectObject(oldp);
	delete pen;
}

void CGDIIspitView::DrawText(CDC* pDC, int size, CString strTex, COLORREF clrText)
{
	XFORM stara1;
	pDC->GetWorldTransform(&stara1);
	//	Translate(pDC, r * (1.4 + 1), r, false);
	Rotate(pDC, -90, false);
	CFont* oldf, * font = new CFont();
	font->CreateFont(size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));
	COLORREF oldColor = pDC->SetTextColor(clrText);
	oldf = pDC->SelectObject(font);
	pDC->TextOut(0, 0, strTex);

	pDC->SetTextColor(oldColor);
	pDC->SelectObject(oldf);
	delete font;

	pDC->SetWorldTransform(&stara1);
}

void CGDIIspitView::DrawVirusCycle(CDC* pDC, int r, int n, int d)
{
	float step = (360 / n) * (3.14 / 180.);
	CPoint* niz = new CPoint[n];
	for (int i = 0; i < n; i++) {
		niz[i] = CPoint(r * cos(step * i), r * sin(step * i));
		pDC->MoveTo(r * cos(step * i), r * sin(step * i));
		pDC->LineTo(3 * r * cos(step * i), 3 * r * sin(step * i));
	}
	pDC->Polygon(niz, n);

	delete[]niz;
	float s = 2 * r * sin(3.14 / n);
	float a = r * cos(3.14 / n);

	pDC->Rectangle(-s / 2, a, s / 2, a + 8 * r);

}

void CGDIIspitView::Distort(CDC* pDC, float r)
{
	DImage img;
	img.Load(CString("test.jpg"));


	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, img.Width() * r, img.Height());
	CDC* mem1 = new CDC();
	mem1->CreateCompatibleDC(pDC);
	mem1->SelectObject(&bmp);

	CDC* mem2 = new CDC();
	mem2->CreateCompatibleDC(pDC);
	CBitmap bmp2;
	bmp2.CreateBitmap(img.Width(), img.Height(), 4, 8, img.GetDIBBits());
	mem2->SelectObject(&bmp2);

	mem1->SetGraphicsMode(GM_ADVANCED);
	Translate(mem1, img.Width() / 2, img.Height() / 2, false);

	CPoint niz[3] = { CPoint(-r * img.Width() / 2,0),CPoint(r * img.Width() / 2,0), CPoint(0,img.Width()) };

	mem1->PlgBlt(niz, mem2, 0, 0, img.Width(), img.Height(), CBitmap(), 0, 0);

	pDC->BitBlt(0, 0, img.Width() * r, img.Height(), mem1, 0, 0, SRCCOPY);
	delete mem1;
	delete mem2;

}

void CGDIIspitView::DrawPlate(CDC* pDC, CString text)
{
	CRect client;
	GetClientRect(&client);
	CRgn oldRgn;
	oldRgn.CreateRectRgn(0, 0, client.Width(), client.Height());

	CRgn region;
	region.CreateRectRgn(0, 0, 200, 100);
	CRgn krugovi[4];
	krugovi[0].CreateEllipticRgn(-20, -20, 20, 20);
	krugovi[1].CreateEllipticRgn(200 - 20, -20, 200 + 20, 20);
	krugovi[2].CreateEllipticRgn(200 - 20, 100 - 20, 200 + 20, 100 + 20);
	krugovi[3].CreateEllipticRgn(-20, 100 - 20, 20, 100 + 20);
	region.CombineRgn(&region, &krugovi[0], RGN_XOR);
	region.CombineRgn(&region, &krugovi[1], RGN_XOR);
	region.CombineRgn(&region, &krugovi[2], RGN_XOR);
	region.CombineRgn(&region, &krugovi[3], RGN_XOR);

	pDC->SelectClipRgn(&region);

	DImage* img = new DImage();
	img->Load(CString("sand.jpg"));
	img->Draw(pDC, CRect(0, 0, img->Width(), img->Height()), CRect(0, 0, 200, 100));
	delete img;


	int arcdirold = pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->BeginPath();
	pDC->MoveTo(0, 20);
	pDC->ArcTo(-20, -20, 20, 20, 0, 20, 20, 0);
	pDC->LineTo(180, 0);
	pDC->ArcTo(180, -20, 220, 20, 180, 0, 200, 20);
	pDC->LineTo(200, 80);
	pDC->ArcTo(180, 80, 220, 120, 200, 80, 180, 100);
	pDC->LineTo(20, 100);
	pDC->ArcTo(-20, 80, 20, 120, 20, 100, 0, 80);
	pDC->LineTo(0, 20);
	pDC->EndPath();

	CPen* oldp, * pen = new CPen(PS_SOLID, 3, RGB(200, 50, 0));
	oldp = pDC->SelectObject(pen);
	pDC->SelectClipRgn(&oldRgn);
	pDC->StrokePath();
	pDC->SelectObject(oldp);
	delete pen;
	pDC->SetArcDirection(arcdirold);

	CFont* oldf, * font = new CFont();
	font->CreateFont(48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Verdana"));
	oldf = pDC->SelectObject(font);

	int bkold = pDC->SetBkMode(TRANSPARENT);
	CSize sz = pDC->GetTextExtent(text);
	COLORREF oldcol = pDC->SetTextColor(RGB(0, 0, 0));
	pDC->TextOut(100 - (sz.cx / 2) + 2, 50 - sz.cy / 2 + 2, text);
	pDC->SetTextColor(RGB(255, 255, 0));
	pDC->TextOut(100 - (sz.cx / 2), 50 - sz.cy / 2, text);
	pDC->SelectObject(oldf);
	delete font;
	pDC->SetBkMode(bkold);

	CBitmap* bmp = new CBitmap();
	bmp->CreateCompatibleBitmap(pDC, 200, 100);
	CDC* mem = new CDC();
	mem->CreateCompatibleDC(pDC);
	mem->SelectObject(bmp);
	mem->BitBlt(0, 0, 200, 100, pDC, 0, 0, SRCCOPY);
	DImage* saveImg = new DImage(*bmp);
	saveImg->Save(CString("Zad1.bmp"));
	delete saveImg;
	delete mem;
	delete bmp;


}

void CGDIIspitView::DrawGhost(CDC* pDC, CRect rect)
{
	//pDC->Rectangle(rect);
	CPen* oldp, * pen = new CPen(PS_SOLID, 1, RGB(0, 0, 0));
	CBrush* oldb, * brush = new CBrush(RGB(255, 0, 0));
	oldp = pDC->SelectObject(pen);
	oldb = pDC->SelectObject(brush);
	int width = rect.BottomRight().x;
	int height = rect.BottomRight().y;
	int nula = rect.left;
	int rw = rect.Width() / 12;
	int rh = rect.Height() / 12;
	pDC->BeginPath();
	pDC->MoveTo(rect.BottomRight());
	pDC->LineTo(width, height - rect.Height() * 0.5);
	int ad = pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(nula, nula, width, height, width, height - rect.Height() * 0.5, nula, height - rect.Height() * 0.5);
	pDC->LineTo(nula, height);
	pDC->ArcTo(nula - rw, height - 2 * rh, nula + rw, height, nula, height, nula + rw, height - rh);
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(nula + rw, height - 2 * rh, nula + 3 * rw, height, nula + rw, height - rh, nula + 3 * rw, height - rh);
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(nula + 3 * rw, height - 2 * rh, nula + 5 * rw, height, nula + 3 * rw, height - rh, nula + 5 * rw, height - rh);
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(nula + 5 * rw, height - 2 * rh, nula + 7 * rw, height, nula + 5 * rw, height - rh, nula + 7 * rw, height - rh);
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(nula + 7 * rw, height - 2 * rh, nula + 9 * rw, height, nula + 7 * rw, height - rh, nula + 9 * rw, height - rh);
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(nula + 9 * rw, height - 2 * rh, nula + 11 * rw, height, nula + 9 * rw, height - rh, nula + 11 * rw, height - rh);
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(nula + 11 * rw, height - 2 * rh, nula + 13 * rw, height, nula + 11 * rw, height - rh, width, height);
	pDC->EndPath();
	pDC->StrokeAndFillPath();
	pDC->SelectObject(oldb);
	delete brush;
	brush = new CBrush(RGB(255, 255, 255));
	pDC->SelectObject(brush);
	int posx1 = rect.left + rect.Width() * 0.8;
	int posx2 = rect.left + rect.Width() * 0.5;
	int posy = rect.top + rect.Height() * 0.3;
	rw *= 1.3;
	pDC->Ellipse(posx1 - rw, posy - rw, posx1 + rw, posy + rw);
	pDC->Ellipse(posx2 - rw, posy - rw, posx2 + rw, posy + rw);
	pDC->SelectObject(oldb);
	delete brush;
	brush = new CBrush(RGB(0, 0, 255));
	pDC->SelectObject(brush);
	posx1 *= 1.02;
	posx2 *= 1.02;
	rw *= 0.4;
	pDC->Ellipse(posx1 - rw, posy - rw, posx1 + rw, posy + rw);
	pDC->Ellipse(posx2 - rw, posy - rw, posx2 + rw, posy + rw);
	pDC->SelectObject(oldp);
	delete pen;
	pDC->SelectObject(oldb);
	delete brush;
}






