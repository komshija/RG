
// GDI-2017View.cpp : implementation of the CGDI2017View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI-2017.h"
#endif

#include "GDI-2017Doc.h"
#include "GDI-2017View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDI2017View

IMPLEMENT_DYNCREATE(CGDI2017View, CView)

BEGIN_MESSAGE_MAP(CGDI2017View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGDI2017View construction/destruction

CGDI2017View::CGDI2017View() noexcept
{
	// TODO: add construction code here
	leg1 = new DImage();
	leg1->Load(CString("leg1.png"));

	leg2 = new DImage();
	leg2->Load(CString("leg2.png"));

	leg3 = new DImage();
	leg3->Load(CString("leg3.png"));

	body = new DImage();
	body->Load(CString("body.png"));

	back2 = new DImage();
	back2->Load(CString("back2.jpg"));
}

void CGDI2017View::LoadIdentity(CDC* pDC)
{
	XFORM forma = {
		1,0,0,1,0,0
	};
	pDC->SetWorldTransform(&forma);
}

void CGDI2017View::Translate(CDC* pDC, float dx, float dy, bool rightmul)
{
	XFORM forma = {
	1,0,0,1,dx,dy
	};
	pDC->ModifyWorldTransform(&forma, rightmul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDI2017View::Rotate(CDC* pDC, float angle, bool rightmul)
{
	angle *= 3.14 / 180.;
	XFORM forma = {
	cos(angle),sin(angle),-sin(angle),cos(angle),0,0
	};
	pDC->ModifyWorldTransform(&forma, rightmul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDI2017View::Scale(CDC* pDC, float sx, float sy, bool rightmul)
{
	XFORM forma = {
	sx,0,0,sy,0,0
	};
	pDC->ModifyWorldTransform(&forma, rightmul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

CGDI2017View::~CGDI2017View()
{
	delete leg1;
	delete leg2;
	delete leg3;
	delete body;
	delete back2;
}

BOOL CGDI2017View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDI2017View drawing


void CGDI2017View::OnDraw(CDC* pDC)
{
	CGDI2017Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect client;
	GetClientRect(&client);

	CDC* mem = new CDC();
	mem->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, client.Width(), client.Height());
	mem->SelectObject(&bmp);

	// TODO: add draw code for native data here

	mem->SetGraphicsMode(GM_ADVANCED);

	

	DrawScene(mem, client);

	pDC->BitBlt(0, 0, client.Width(), client.Height(), mem, 0, 0, SRCCOPY);

	delete mem;

}


// CGDI2017View printing

BOOL CGDI2017View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDI2017View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDI2017View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDI2017View diagnostics

#ifdef _DEBUG
void CGDI2017View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI2017View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI2017Doc* CGDI2017View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI2017Doc)));
	return (CGDI2017Doc*)m_pDocument;
}
#endif //_DEBUG


// CGDI2017View message handlers

void CGDI2017View::DrawScene(CDC* pDC, CRect rect)
{
	XFORM stara;
	pDC->GetWorldTransform(&stara);
	
	crect = rect;

	back2->Draw(pDC, CRect(bgpomx, bgpomy, bgpomx + rect.Width(), bgpomy + rect.Height()), rect);

	Scale(pDC, povecaj, povecaj, false);
	Translate(pDC, 100 + pomeraj, 100, false);
	body->DrawTransparent(pDC, CRect(0, 0, body->Width(), body->Height()), CRect(0, 0, body->Width(), body->Height()), NULL);

	int niz[8] = { -20, -10, 0, 10, 20, 10, 0, -10 };
	int faza1 = faza;
	int faza2 = (faza + 2) % 8;
	DrawLeg(pDC, 0 + niz[faza1], 52, 168);
	DrawLeg(pDC, 0 - niz[faza1], 52, 168);
	DrawLeg(pDC, 0 + niz[faza2], 270, 168);
	DrawLeg(pDC, 0 - niz[faza2], 270, 168);

	pDC->SetWorldTransform(&stara);
}

void CGDI2017View::DrawLeg(CDC* pDC, float alpha, float x, float y)
{

	XFORM stara;
	pDC->GetWorldTransform(&stara);

	Translate(pDC, x, y, false);
	Translate(pDC, 28, 28, false);
	Rotate(pDC, alpha, false);
	Translate(pDC, -28, -28, false);

	leg1->DrawTransparent(pDC, CRect(0, 0, leg1->Width(), leg1->Height()), CRect(0, 0, leg1->Width(), leg1->Height()), NULL);

	Translate(pDC, 0, leg1->Height() - 28 - 14, false);
	Translate(pDC, 29, 29, false);
	Rotate(pDC, -alpha, false);
	Translate(pDC, -29, -29, false);

	leg2->DrawTransparent(pDC, CRect(0, 0, leg2->Width(), leg2->Height()), CRect(0, 0, leg2->Width(), leg2->Height()), NULL);

	Translate(pDC, -30, leg2->Height() - 29, false);

	leg3->DrawTransparent(pDC, CRect(0, 0, leg3->Width(), leg3->Height()), CRect(0, 0, leg3->Width(), leg3->Height()), NULL);


	pDC->SetWorldTransform(&stara);
}


BOOL CGDI2017View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}


void CGDI2017View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar)
	{
	case VK_RIGHT:
		faza++;
		pomeraj += 20;
		faza = faza % 8;
		break;
	case VK_LEFT:
		if (pomeraj > 0) {
			pomeraj -= 20;
			faza--;
			if (faza == 0) 
				faza = 7;
		}
		faza = faza % 8;
		break;
	case VK_UP:
		povecaj += 0.1;
		break;
	case VK_DOWN:
		povecaj -= 0.1;
		break;
	case 'W':
		if (bgpomy > 0)
			bgpomy -= 200;
		break;
	case 'S':
		if (bgpomy + crect.Height() + 200 < back2->Height())
			bgpomy += 200;
		break;
	case 'A':
		if (bgpomx > 0)
			bgpomx -= 200;
		break;
	case 'D':
		if (bgpomx + crect.Width() + 200 < back2->Width())
			bgpomx += 200;
		break;
	default:break;
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
