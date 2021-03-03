
// GDI-2013View.cpp : implementation of the CGDI2013View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI-2013.h"
#endif

#include "GDI-2013Doc.h"
#include "GDI-2013View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDI2013View

IMPLEMENT_DYNCREATE(CGDI2013View, CView)

BEGIN_MESSAGE_MAP(CGDI2013View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CGDI2013View construction/destruction

CGDI2013View::CGDI2013View() noexcept
{
	// TODO: add construction code here
	sky = new DImage();
	bark = new DImage();
	sky->Load(CString("sky.jpg"));
	bark->Load(CString("bark.jpg"));
}

CGDI2013View::~CGDI2013View()
{
	delete sky;
	delete bark;
}

BOOL CGDI2013View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDI2013View drawing

void CGDI2013View::DrawBlade(CDC* pDC, int size)
{
	CBrush* grayBrush = new CBrush(RGB(64, 64, 64));
	CBrush* darkGrayBrush = new CBrush(RGB(128, 128, 128));
	CBrush* oldBrush;
	CPen* greyPen = new CPen(PS_SOLID, 1, RGB(64, 64, 64));
	CPen* oldPen;

	oldPen = pDC->SelectObject(greyPen);

	oldBrush = pDC->SelectObject(grayBrush);

	CPoint* trougao = new CPoint[3]();
	trougao[0] = CPoint(0, 0);
	trougao[1] = CPoint(4 * size, 0);
	trougao[2] = CPoint(size, -size);
	pDC->Polygon(trougao, 3);

	pDC->SelectObject(darkGrayBrush);

	trougao[0] = CPoint(0, 0);
	trougao[1] = CPoint(4 * size, 0);
	trougao[2] = CPoint(size, size);
	pDC->Polygon(trougao, 3);

	delete[] trougao;

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);

	CFont* font = new CFont();
	font->CreateFontW(0.7 * size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Monotype Corsiva"));
	//int oldTA = pDC->SetTextAlign(TA_CENTER);
	CFont* oldFont;
	oldFont = pDC->SelectObject(font);
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);

	COLORREF oldTextColor = pDC->SetTextColor(RGB(255, 255, 255));
	pDC->TextOutW(-1 + size, -1 - (size * 0.4), CString("Shuricane"));

	pDC->SetTextColor(RGB(192, 192, 192));
	pDC->TextOutW(size, -size * 0.4, CString("Shuricane"));

	pDC->SelectObject(oldFont);
	pDC->SetTextColor(oldTextColor);
	//pDC->SetTextAlign(oldTA);
	pDC->SetBkMode(oldBkMode);
	delete font;

}

void CGDI2013View::Translate(CDC* pDC, double x, double y)
{
	XFORM forma = {
		1,
		0,
		0,
		1,
		x,
		y
	};
	pDC->ModifyWorldTransform(&forma, MWT_LEFTMULTIPLY);
}

void CGDI2013View::Rotate(CDC* pDC, float alpha)
{
	alpha *= (3.14 / 180);
	XFORM forma = {
		cos(alpha),
		sin(alpha),
		-sin(alpha),
		cos(alpha),
		0,
		0
	};
	pDC->ModifyWorldTransform(&forma, MWT_LEFTMULTIPLY);
}

void CGDI2013View::DrawStar(CDC* pDC, int size)
{
	for (int i = 0; i < 4; i++) {
		DrawBlade(pDC, size / 2);
		Rotate(pDC, 90);
	}
}

void CGDI2013View::OnDraw(CDC* pDC)
{
	CGDI2013Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clnt;
	GetClientRect(&clnt);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,clnt.Width(),clnt.Height());
	memDC->SelectObject(bmp);



	// TODO: add draw code for native data here
	memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM old;
	memDC->GetWorldTransform(&old);

	sky->Draw(memDC, CRect(0, 0, sky->Width(), sky->Height()), clnt);
	bark->Draw(memDC, CRect(0, 0, bark->Width(), bark->Height()), CRect(clnt.Width() - bark->Width(), 0, clnt.Width(), clnt.Height()));


	int position_to_stop = clnt.Width() - bark->Width();
	int current_pos = 100 + 160 + 160/2 + x_pos;

	if ((float)current_pos / (float)position_to_stop >= 1.1) {
		hitted = true;
	}


	Translate(memDC, 100, 200);
	Translate(memDC, x_pos, 0);
	Rotate(memDC, angle);

	DrawStar(memDC, 160);
	memDC->SetWorldTransform(&old);

	pDC->BitBlt(0, 0, clnt.Width(), clnt.Height(), memDC, 0, 0, SRCCOPY);

}


// CGDI2013View printing

BOOL CGDI2013View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDI2013View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDI2013View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDI2013View diagnostics

#ifdef _DEBUG
void CGDI2013View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI2013View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI2013Doc* CGDI2013View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI2013Doc)));
	return (CGDI2013Doc*)m_pDocument;
}
#endif //_DEBUG


// CGDI2013View message handlers


void CGDI2013View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == 'W' && !hitted) {
		x_pos += 20;
		angle += 10;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CGDI2013View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}
