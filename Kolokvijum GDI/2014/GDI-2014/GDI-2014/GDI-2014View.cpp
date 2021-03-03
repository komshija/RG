
// GDI-2014View.cpp : implementation of the CGDI2014View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI-2014.h"
#endif

#include "GDI-2014Doc.h"
#include "GDI-2014View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDI2014View

IMPLEMENT_DYNCREATE(CGDI2014View, CView)

BEGIN_MESSAGE_MAP(CGDI2014View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CGDI2014View construction/destruction

CGDI2014View::CGDI2014View() noexcept
{
	// TODO: add construction code here
	wheel = new DImage();
	wheel->Load(CString("wheel.png"));
	clio = GetEnhMetaFile(CString("clio.emf"));
	put = 0;
	angle = 20;
}


CGDI2014View::~CGDI2014View()
{
	delete wheel;
	DeleteEnhMetaFile(clio);
}

BOOL CGDI2014View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDI2014View drawing

void CGDI2014View::OnDraw(CDC* pDC)
{
	CGDI2014Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect crect;
	GetClientRect(&crect);

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,crect.Width(),crect.Height());
	memDC->SelectObject(bmp);
	XFORM stara;
	memDC->GetWorldTransform(&stara);

	memDC->SetGraphicsMode(GM_ADVANCED);
	// TODO: add draw code for native data here
	DrawGround(memDC, angle);
	int r = 38;
	Translate(memDC, 0, crect.Height(), false);
	Rotate(memDC, -angle, false);
	Translate(memDC, 450 / 2, -(450 / 2.5) - r / 2.0  + 90, false);

	Translate(memDC, put, 0, false);
	DrawCar(memDC, 0, 0, 450, 450 / 2.5);

	float ugaotocka = (360 * (float)put) / (2 * 3.14 * r);

	DrawWheel(memDC, -155, +70, r, angle + ugaotocka);
	DrawWheel(memDC, +135, +70, r, angle + ugaotocka);

	memDC->SetWorldTransform(&stara);

	pDC->BitBlt(0, 0, crect.Width(), crect.Height(), memDC, 0, 0, SRCCOPY);

}


// CGDI2014View printing

BOOL CGDI2014View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDI2014View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDI2014View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDI2014View diagnostics

#ifdef _DEBUG
void CGDI2014View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI2014View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI2014Doc* CGDI2014View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI2014Doc)));
	return (CGDI2014Doc*)m_pDocument;
}
#endif //_DEBUG


// CGDI2014View message handlers



void CGDI2014View::DrawGround(CDC* pDC, float angle)
{
	CRect client;
	GetClientRect(&client);

	CPen* oldpen, * pen;
	pen = new CPen(PS_SOLID, 3, RGB(128, 64, 0));

	CBrush* oldbrush, * bluebrush, * greenbrush;
	bluebrush = new CBrush(RGB(192, 192, 255));
	greenbrush = new CBrush(HS_FDIAGONAL, RGB(128, 32, 32));
	COLORREF bkold = pDC->SetBkColor(RGB(220, 255, 192));

	oldbrush = pDC->SelectObject(bluebrush);
	pDC->Rectangle(client);

	oldpen = pDC->SelectObject(pen);
	pDC->SelectObject(greenbrush);

	CPoint* niz = new CPoint[3];

	niz[0] = CPoint(client.left, client.bottom);
	niz[1] = client.BottomRight();
	niz[2] = CPoint(client.right, client.bottom - client.Width() * tan(angle * (3.14 / 180.0)));

	pDC->Polygon(niz, 3);
	delete[] niz;

	pDC->SelectObject(oldbrush);
	pDC->SelectObject(oldpen);
	delete pen;
	delete bluebrush;
	delete greenbrush;


}

void CGDI2014View::Translate(CDC* pDC, float dX, float dY, bool rightMul)
{
	XFORM forma = {
		1,
		0,
		0,
		1,
		dX,
		dY
	};
	pDC->ModifyWorldTransform(&forma, rightMul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDI2014View::Rotate(CDC* pDC, float angle, bool rightMul)
{
	angle *= 3.14 / 180.0;
	XFORM forma = {
		cos(angle),
		sin(angle),
		-sin(angle),
		cos(angle),
		0,
		0
	};
	pDC->ModifyWorldTransform(&forma, rightMul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDI2014View::Scale(CDC* pDC, float sX, float sY, bool rightMul)
{
	XFORM forma = {
		1,
		sX,
		sY,
		1,
		0,
		0
	};
	pDC->ModifyWorldTransform(&forma, rightMul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDI2014View::DrawCar(CDC* pDC, int x, int y, int w, int h)
{
	ENHMETAHEADER header;
	GetEnhMetaFileHeader(clio, sizeof(ENHMETAHEADER), &header);
	CRect cliorect(
		x + w / 2,
		y - h / 2,
		x - w / 2,
		y + h / 2
	);

	pDC->PlayMetaFile(clio, cliorect);
}

void CGDI2014View::DrawWheel(CDC* pDC, int x, int y, int r, float angle)
{
	XFORM oldform;
	pDC->GetWorldTransform(&oldform);

	CRect wheelrect(-r, -r, r, r);
	Translate(pDC, x, y, false);
	Rotate(pDC, angle, false);
	wheel->DrawTransparent(pDC, CRect(52, 12, 52 + 376, 12 + 376), wheelrect,RGB(255,255,255));


	pDC->SetWorldTransform(&oldform);
}

void CGDI2014View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar) {
	case VK_UP:
		if (angle < 80) {
			put = 0;
			angle += 10;
		}
		break;
	case VK_DOWN:
		if (angle > -10) {
			put = 0;
			angle -= 10;
		}
		break;
	case VK_RIGHT:
		put += 10;
		break;
	case VK_LEFT:
		put -= 10;
		break;
	default:
		break;
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CGDI2014View::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}
