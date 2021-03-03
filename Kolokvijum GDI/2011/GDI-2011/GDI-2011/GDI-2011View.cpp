
// GDI-2011View.cpp : implementation of the CGDI2011View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI-2011.h"
#endif

#include "GDI-2011Doc.h"
#include "GDI-2011View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDI2011View

IMPLEMENT_DYNCREATE(CGDI2011View, CView)

BEGIN_MESSAGE_MAP(CGDI2011View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CGDI2011View construction/destruction

CGDI2011View::CGDI2011View() noexcept
{
	// TODO: add construction code here
	slika = new DImage();
	slika->Load(CString("sky.jpg"));
	clio = GetEnhMetaFile(CString("clio.emf"));
	GetEnhMetaFileHeader(clio, sizeof(ENHMETAHEADER), &clio_header);
	tocak = GetEnhMetaFile(CString("tocak.emf"));
	GetEnhMetaFileHeader(tocak, sizeof(ENHMETAHEADER), &tocak_header);
	pomeraj = 0;
}

void CGDI2011View::PovecajRect(CRect& rect, int val)
{
	rect.bottom += val;
	rect.right += val;
	rect.top -= val;
	rect.left -= val;

}

CGDI2011View::~CGDI2011View()
{
	delete slika;
	DeleteEnhMetaFile(clio);
	DeleteEnhMetaFile(tocak);
}

BOOL CGDI2011View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDI2011View drawing

void CGDI2011View::OnDraw(CDC* pDC)
{
	CGDI2011Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clientRect;
	GetClientRect(&clientRect);


	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap img; 
	img.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());
	memDC->SelectObject(img);

	// TODO: add draw code for native data here
	CRect imgRect(0, 0, slika->Width(), slika->Height());

	slika->Draw(memDC, imgRect, clientRect);

	int clio_width = clio_header.rclBounds.right - clio_header.rclBounds.left;
	int clio_height = clio_header.rclBounds.bottom - clio_header.rclBounds.top;
	CRect clioRect(clientRect.Width() / 2 - clio_width / 2,
		clientRect.Height() / 2 - clio_height / 2,
		clientRect.Width() / 2 + clio_width / 2,
		clientRect.Height() / 2 + clio_height / 2);


	//bilboard
	CBrush* oldBrush;
	CBrush* greyBrush = new CBrush(RGB(128, 128, 128));
	CBrush* blackBrush = new CBrush(RGB(0, 0, 0));
	CRect bilboard_white = clioRect;

	oldBrush = memDC->SelectObject(blackBrush);
	memDC->Rectangle(clientRect.Width() / 2 - 100, clientRect.Height() / 2, clientRect.Width() / 2 + 100, clientRect.Height());

	PovecajRect(bilboard_white, 80);
	bilboard_white.right += 4;
	bilboard_white.bottom += 4;
	memDC->RoundRect(bilboard_white, CPoint(20, 20));

	bilboard_white.right -= 4;
	bilboard_white.bottom -= 4;
	memDC->SelectObject(greyBrush);
	memDC->RoundRect(bilboard_white, CPoint(20, 20));

	PovecajRect(bilboard_white, -40);

	bilboard_white.right += 4;
	bilboard_white.bottom += 4;
	memDC->SelectObject(blackBrush);
	memDC->RoundRect(bilboard_white, CPoint(20, 20));

	memDC->SelectObject(oldBrush);
	bilboard_white.right -= 4;
	bilboard_white.bottom -= 4;
	memDC->RoundRect(bilboard_white, CPoint(20, 20));

	delete greyBrush;
	delete blackBrush;


	XFORM staraForma,staraForma2, novaForma;
	memDC->SetGraphicsMode(GM_ADVANCED);
	memDC->GetWorldTransform(&staraForma);

	novaForma = {
		1,0,0,1,(FLOAT)pomeraj,0
	};

	memDC->SetWorldTransform(&novaForma);

	//clio

	memDC->PlayMetaFile(clio, clioRect);

	memDC->GetWorldTransform(&staraForma2);

	//tockovi
	int tocak_width = tocak_header.rclBounds.right - tocak_header.rclBounds.left;
	int tocak_height = tocak_header.rclBounds.bottom - tocak_header.rclBounds.top;
	float obimTocka = 2 * 3.14 * (tocak_width / 2);
	float ugao = (360 * pomeraj) / obimTocka;
	ugao *= (3.14 / 180);

	novaForma = {
		(FLOAT)cosf(ugao),
		(FLOAT)sinf(ugao),
		(FLOAT)-sinf(ugao),
		(FLOAT)cosf(ugao),
		(FLOAT)clioRect.left + 128,
		(FLOAT)clioRect.top + 230
	};
	memDC->ModifyWorldTransform(&novaForma, MWT_LEFTMULTIPLY);
	novaForma = {
	1,0,0,1,
	(FLOAT)-(clioRect.left + 128),
	(FLOAT)-(clioRect.top + 230)
	};
	memDC->ModifyWorldTransform(&novaForma, MWT_LEFTMULTIPLY);

	CRect tocakRect(
		clioRect.left + 128 - tocak_width / 2,
		clioRect.top + 230 - tocak_height / 2,
		clioRect.left + 128 + tocak_width / 2,
		clioRect.top + 230 + tocak_height / 2
	);

	memDC->PlayMetaFile(tocak, tocakRect);

	memDC->SetWorldTransform(&staraForma2);


	novaForma = {
	(FLOAT)cosf(ugao),
	(FLOAT)sinf(ugao),
	(FLOAT)-sinf(ugao),
	(FLOAT)cosf(ugao),
	(FLOAT)clioRect.left + 128 + 418,
	(FLOAT)clioRect.top + 230
	};
	memDC->ModifyWorldTransform(&novaForma, MWT_LEFTMULTIPLY);
	novaForma = {
	1,0,0,1,
	(FLOAT)-(clioRect.left + 128+418),
	(FLOAT)-(clioRect.top + 230)
	};
	memDC->ModifyWorldTransform(&novaForma, MWT_LEFTMULTIPLY);



	tocakRect.left += 418;
	tocakRect.right += 418;
	memDC->PlayMetaFile(tocak, tocakRect);

	memDC->SetWorldTransform(&staraForma);
	
	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), memDC, 0, 0, SRCCOPY);


}


// CGDI2011View printing

BOOL CGDI2011View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDI2011View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDI2011View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDI2011View diagnostics

#ifdef _DEBUG
void CGDI2011View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI2011View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI2011Doc* CGDI2011View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI2011Doc)));
	return (CGDI2011Doc*)m_pDocument;
}
#endif //_DEBUG


// CGDI2011View message handlers


void CGDI2011View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar) {
	case VK_LEFT:
		pomeraj -= 5;
		Invalidate();
		break;
	case VK_RIGHT:
		pomeraj += 5;
		Invalidate();
		break;
	default:
		break;
	}


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CGDI2011View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}
