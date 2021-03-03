
// GDI-2015View.cpp : implementation of the CGDI2015View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI-2015.h"
#endif

#include "GDI-2015Doc.h"
#include "GDI-2015View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDI2015View

IMPLEMENT_DYNCREATE(CGDI2015View, CView)

BEGIN_MESSAGE_MAP(CGDI2015View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CGDI2015View construction/destruction

CGDI2015View::CGDI2015View() noexcept
{
	// TODO: add construction code here
	blue = new DImage();
	blue->Load(CString("blue.png"));
	pacX = 0;
	pacY = 0;
	open = true;
	dir = 0;
	lastdir = 0;
}

CGDI2015View::~CGDI2015View()
{
	delete blue;
}

BOOL CGDI2015View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDI2015View drawing

void CGDI2015View::Rotate(CDC* pDC, float angle)
{
	angle *= (3.14 / 180);
	XFORM forma = {
		cos(angle),
		sin(angle),
		-sin(angle),
		cos(angle),
		0,
		0
	};
	pDC->ModifyWorldTransform(&forma, MWT_LEFTMULTIPLY);
}

void CGDI2015View::Translate(CDC* pDC, double x, double y)
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

void CGDI2015View::Mirror(CDC* pDC, int x, int y)
{
	XFORM forma = {
	x,
	0,
	0,
	y,
	0,
	0
	};
	pDC->ModifyWorldTransform(&forma, MWT_LEFTMULTIPLY);
}

void CGDI2015View::DrawPacman(CDC* pDC, CRect rect, float angle)
{
	angle *= 3.14 / 180;
	CBrush* oldbrush;
	CBrush* yellowbrush = new CBrush(RGB(255, 255, 0));
	oldbrush = pDC->SelectObject(yellowbrush);
	CPoint start, end;
	CPoint center = rect.CenterPoint();
	//pDC->SetArcDirection(AD_CLOCKWISE);
	int radius = rect.right - center.x;

	start.x = center.x + radius * cos(angle);
	start.y = center.y + radius * sin(angle);

	end.x = center.x + radius * cos(-angle);
	end.y = center.y + radius * sin(-angle);


	pDC->Pie(rect, start, end);

	pDC->SelectObject(oldbrush);

	delete yellowbrush;
	yellowbrush = new CBrush(RGB(0, 0, 0));
	pDC->SelectObject(yellowbrush);
	CPen* pen, * oldpen;
	pen = new CPen(PS_SOLID, 5, RGB(0, 0, 0));
	oldpen = pDC->SelectObject(pen);

	CPoint oko(center.x + (radius / 2.0) * cos(-angle), center.y - (radius / 2.0) + sin(-angle));
	pDC->MoveTo(oko);
	pDC->LineTo(oko);

	delete yellowbrush;
	pDC->SelectObject(oldbrush);
	pDC->SelectObject(oldpen);

}

void CGDI2015View::DrawGhost(CDC* pDC, CRect rect)
{

	CBrush* oldbrush, * redbrush,*bluebrush;
	redbrush = new CBrush(RGB(255, 0, 0));
	bluebrush = new CBrush(RGB(0, 0, 255));

	oldbrush = pDC->SelectObject(redbrush);


	pDC->Ellipse(rect);

	pDC->SelectObject(oldbrush);
	




}

void CGDI2015View::OnDraw(CDC* pDC)
{
	CGDI2015Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	CRect crect;
	GetClientRect(&crect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, crect.Width(), crect.Height());
	memDC->SelectObject(&bmp);


	// TODO: add draw code for native data here
	memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM stara;

	blue->Draw(memDC, CRect(0, 0, blue->Width(), blue->Height()), crect);

	memDC->GetWorldTransform(&stara);
	Translate(memDC, 450 + pacX, 450 + pacY);
	switch (dir) {
	case 0:
		Rotate(memDC, -180);
		Mirror(memDC, 1, -1);
		break;
	case 1:
		Rotate(memDC, -90);
		Mirror(memDC, 1, -1);

		break;
	case 3:
		Rotate(memDC, 90);
		break;
	default:
		break;
	}
	Translate(memDC, -450 - pacX, -450 - pacY);
	DrawPacman(memDC, CRect(400 + pacX, 400 + pacY, 500 + pacX, 500 + pacY), open ? -15 : -30);
	memDC->SetWorldTransform(&stara);

	DrawGhost(memDC, CRect(100, 120, 196, 216));


	if (400+pacX < 196 && 400+pacY < 216 || 500 + pacX > 100 && 500 + pacY > 120 )
	{
		CFont *font,*oldfont;
		font = new CFont();
		font->CreateFontW(72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));
		oldfont = memDC->SelectObject(font);
		int align;
		align = pDC->SetTextAlign(TA_CENTER);
		int bkmode = pDC->SetBkMode(TRANSPARENT);
		COLORREF oldcol = pDC->SetTextColor(RGB(255, 255, 255));
		pDC->TextOutW(crect.CenterPoint().x, crect.CenterPoint().y, CString("The End"));
		pDC->SetTextColor(oldcol);
		pDC->SetTextAlign(align);
		pDC->SelectObject(oldfont);
		pDC->SetBkMode(bkmode);
		delete font;
	}


	pDC->BitBlt(0, 0, crect.Width(), crect.Height(), memDC, 0, 0, SRCCOPY);
}

// CGDI2015View printing

BOOL CGDI2015View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDI2015View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDI2015View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDI2015View diagnostics

#ifdef _DEBUG
void CGDI2015View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI2015View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI2015Doc* CGDI2015View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI2015Doc)));
	return (CGDI2015Doc*)m_pDocument;
}
#endif //_DEBUG


// CGDI2015View message handlers


void CGDI2015View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	lastdir = dir;
	switch (nChar) {

	case VK_UP:
		pacY -= 10;
		open = !open;
		dir = 1;
		Invalidate();
		break;

	case VK_DOWN:
		pacY += 10;
		open = !open;
		dir = 3;
		Invalidate();
		break;

	case VK_RIGHT:
		pacX += 10;
		open = !open;
		dir = 2;
		Invalidate();
		break;

	case VK_LEFT:
		pacX -= 10;
		open = !open;
		dir = 0;
		Invalidate();
		break;

	default:
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CGDI2015View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}
