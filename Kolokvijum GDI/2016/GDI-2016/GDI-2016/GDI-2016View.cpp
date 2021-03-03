
// GDI-2016View.cpp : implementation of the CGDI2016View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI-2016.h"
#endif

#include "GDI-2016Doc.h"
#include "GDI-2016View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDI2016View

IMPLEMENT_DYNCREATE(CGDI2016View, CView)

BEGIN_MESSAGE_MAP(CGDI2016View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGDI2016View construction/destruction

CGDI2016View::CGDI2016View() noexcept
{
	// TODO: add construction code here
	wood = new DImage();
	table = new DImage();

	wood->Load(CString("wood.jpg"));
	table->Load(CString("felt2.jpg"));
}

CGDI2016View::~CGDI2016View()
{
	delete wood;
	delete table;
}

BOOL CGDI2016View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDI2016View drawing



void CGDI2016View::OnDraw(CDC* pDC)
{
	CGDI2016Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	CRect client;
	GetClientRect(&client);

	CDC* mem = new CDC();
	mem->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, client.Width(), client.Height());
	mem->SelectObject(&bmp);
	XFORM forma;
	mem->SetGraphicsMode(GM_ADVANCED);

	int R = 30;
	int w = 900;

	mem->GetWorldTransform(&forma);
	DrawTable(mem, client);
	DrawBounds(mem, client, 30);
	DrawHoles(mem, client, 25);
	
	udareno = stap_pom > 0;

	Translate(mem, 600, 400, false);
	if (!udareno) {
			kugla_angle = stap_angle;
	}


	if (udareno) {
		Rotate(mem, kugla_angle, false);
		Translate(mem, stap_pom, 0, false);
	}
	DrawBall(mem, R);
	if (udareno) {
		Translate(mem, -stap_pom, 0, false);
		Rotate(mem, -kugla_angle, false);
	}

	Rotate(mem, stap_angle, false);
	Translate(mem, -w - R / 2, 0, false);
	if (!udareno) {
		Translate(mem, stap_pom, 0, false);
	}


	DrawStick(mem, w);
	mem->SetWorldTransform(&forma);

	pDC->BitBlt(0, 0, client.Width(), client.Height(), mem, 0, 0, SRCCOPY);



}


// CGDI2016View printing

BOOL CGDI2016View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDI2016View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDI2016View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDI2016View diagnostics

#ifdef _DEBUG
void CGDI2016View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI2016View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI2016Doc* CGDI2016View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI2016Doc)));
	return (CGDI2016Doc*)m_pDocument;
}
#endif //_DEBUG


// CGDI2016View message handlers


void CGDI2016View::DrawStick(CDC* pDC, int w)
{
	CBrush* oldbrush;
	CBrush* braonbrush = new CBrush(RGB(255, 190, 128));
	CBrush* tamnibrush = new CBrush(RGB(64, 32, 0));

	CPen* pen, * oldpen;
	pen = new CPen(PS_SOLID, 1, RGB(64, 32, 0));
	oldpen = pDC->SelectObject(pen);

	float sirina = w / 100.0;
	oldbrush = pDC->SelectObject(tamnibrush);
	CPoint* niz = new CPoint[4];



	niz[0] = CPoint(0, -sirina);
	niz[1] = CPoint(0, sirina);
	niz[2] = CPoint(0.33 * w, sirina * 0.66);
	niz[3] = CPoint(0.33 * w, -sirina * 0.66);

	pDC->Polygon(niz, 4);

	pDC->Ellipse(-sirina, -sirina, sirina, sirina);

	niz[0] = CPoint(0.33 * w, -sirina * 0.66);
	niz[1] = CPoint(0.33 * w, sirina * 0.66);
	niz[2] = CPoint(w, sirina * 0.5);
	niz[3] = CPoint(w, -sirina * 0.5);

	pDC->SelectObject(braonbrush);
	pDC->Polygon(niz, 4);

	pDC->SelectObject(oldbrush);
	pDC->SelectObject(oldpen);

	delete braonbrush;
	delete tamnibrush;
	delete pen;
	delete[] niz;

	pen = new CPen(PS_SOLID, 1, RGB(255, 255, 255));
	pDC->SelectObject(pen);

	pDC->MoveTo(2, -sirina + 4);
	pDC->LineTo(w - 2, -sirina * 0.5 + 3);

	pDC->SelectObject(oldpen);

}

void CGDI2016View::DrawBall(CDC* pDC, int w)
{
	CBrush* oldbrush, * redbrush;
	redbrush = new CBrush(RGB(255, 64, 64));
	CPen* oldpen, * pen;
	pen = new CPen(PS_SOLID, 1, RGB(128, 0, 0));

	oldpen = pDC->SelectObject(pen);
	oldbrush = pDC->SelectObject(redbrush);

	pDC->Ellipse(-w / 2, -w / 2, w / 2, w / 2);

	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	delete pen;
	delete redbrush;
	pen = new CPen(PS_SOLID, 1, RGB(255, 255, 255));
	redbrush = new CBrush(RGB(255, 255, 255));

	pDC->SelectObject(pen);
	pDC->SelectObject(redbrush);

	pDC->Ellipse(-w / 6. + w / 6., -w / 6. - w / 6., w / 6. + w / 6., w / 6. - w / 6.);


	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	delete pen;
	delete redbrush;
}

void CGDI2016View::Translate(CDC* pDC, float dx, float dy, bool rightMul)
{
	XFORM forma = {
		1,0,0,1,dx,dy
	};
	pDC->ModifyWorldTransform(&forma, rightMul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDI2016View::Rotate(CDC* pDC, float angle, bool rightMul)
{
	angle *= 3.14 / 180;
	XFORM forma = {
		cos(angle),
		sin(angle),
		-sin(angle),
		cos(angle),
		0,0
	};
	pDC->ModifyWorldTransform(&forma, rightMul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDI2016View::DrawTable(CDC* pDC, CRect rect)
{
	int sizeX = rect.Width() / table->Width() + 1;
	int sizeY = rect.Height() / table->Height() + 1;


	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {

			table->Draw(pDC, CRect(0, 0, table->Width(), table->Height()), CRect(i * table->Width(), j * table->Height(), (i + 1) * table->Width(), (j + 1) * table->Height()));
		}
	}

}

void CGDI2016View::DrawBounds(CDC* pDC, CRect rect, int w)
{
	CRgn r1, r2;
	r1.CreateRectRgn(rect.left + w, rect.top + w, rect.right - w, rect.bottom - w);
	r2.CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);

	r1.CombineRgn(&r1, &r2, RGN_XOR);
	pDC->SelectClipRgn(&r1);

	wood->Draw(pDC, CRect(0, 0, wood->Width(), wood->Height()), rect);

	pDC->SelectClipRgn(&r2);


}

void CGDI2016View::DrawHoles(CDC* pDC, CRect rect, int size)
{
	CBrush* oldbrush, * brush;
	brush = new CBrush(RGB(0, 0, 0));
	oldbrush = pDC->SelectObject(brush);

	pDC->Ellipse(rect.left + size, rect.top + size, rect.left + 2 * size, rect.top + 2 * size);
	pDC->Ellipse(rect.Width() / 2 - size / 2, rect.top + size, rect.Width() / 2 + size / 2, rect.top + 2 * size);
	pDC->Ellipse(rect.right - 2 * size, rect.top + size, rect.right - size, rect.top + 2 * size);

	pDC->Ellipse(rect.left + size, rect.bottom - size, rect.left + 2 * size, rect.bottom - 2 * size);
	pDC->Ellipse(rect.Width() / 2 - size / 2, rect.bottom - size, rect.Width() / 2 + size / 2, rect.bottom - 2 * size);
	pDC->Ellipse(rect.right - 2 * size, rect.bottom - size, rect.right - size, rect.bottom - 2 * size);

	pDC->SelectObject(oldbrush);
	delete brush;
}


BOOL CGDI2016View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}


void CGDI2016View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar) {
	case VK_DOWN:
		stap_pom -= 10;
		break;
	case VK_UP:
		stap_pom += 10;
		break;
	case VK_RIGHT:
		stap_angle += 5;
		break;
	case VK_LEFT:
		stap_angle -= 5;
		break;
	default:
		break;
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
