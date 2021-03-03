
// GDI-2018View.cpp : implementation of the CGDI2018View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI-2018.h"
#endif

#include "GDI-2018Doc.h"
#include "GDI-2018View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDI2018View

IMPLEMENT_DYNCREATE(CGDI2018View, CView)

BEGIN_MESSAGE_MAP(CGDI2018View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGDI2018View construction/destruction

CGDI2018View::CGDI2018View() noexcept
{
	// TODO: add construction code here
	arm1 = new DImage();
	arm2 = new DImage();
	bager = new DImage();
	pozadina = new DImage();

	viljuska = GetEnhMetaFile(CString("viljuska.emf"));
	GetEnhMetaFileHeader(viljuska, sizeof(ENHMETAHEADER), &header_viljuska);

	arm1->Load(CString("arm1.png"));
	arm2->Load(CString("arm2.png"));
	bager->Load(CString("bager.png"));
	pozadina->Load(CString("pozadina.png"));
}

CGDI2018View::~CGDI2018View()
{
	DeleteEnhMetaFile(viljuska);
	delete arm1;
	delete arm2;
	delete bager;
	delete pozadina;
}

BOOL CGDI2018View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDI2018View drawing

void CGDI2018View::Translate(CDC* pDC, float dx, float dy, bool rightmul)
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

void CGDI2018View::Rotate(CDC* pDC, float angle, bool rightmul)
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

void CGDI2018View::Scale(CDC* pDC, float sx, float sy, bool rightmul)
{
	XFORM forma = {
	sx,
	0,
	0,
	sy,
	0,
	0
	};

	pDC->ModifyWorldTransform(&forma, rightmul ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CGDI2018View::DrawBackground(CDC* pDC)
{
	CRect client;
	GetClientRect(&client);
	pozadina->Draw(pDC, CRect(0, 0, pozadina->Width(), pozadina->Height()), client);
}

void CGDI2018View::DrawBody(CDC* pDC)
{
	CRect bagerRect = CRect(0, 0, bager->Width(), bager->Height());
	bager->DrawTransparent(pDC, bagerRect, bagerRect,NULL);
	Translate(pDC, 0, 220, false);
	Rotate(pDC, -90, false);
}

void CGDI2018View::DrawArm1(CDC* pDC)
{


	Translate(pDC, 58, 61, false);
	Rotate(pDC, ugaoArm1, false);
	Translate(pDC, -58, -61, false);

	CRect arm1Rect = CRect(0, 0, arm1->Width(), arm1->Height());
	arm1->DrawTransparent(pDC, arm1Rect, arm1Rect, NULL);

	Translate(pDC, 309-39, 61+37, false);
	Rotate(pDC, -90, false);

}

void CGDI2018View::DrawArm2(CDC* pDC)
{

	Translate(pDC, 36, 40, false);
	Rotate(pDC, ugaoArm2, false);
	Translate(pDC, -36, -40, false);

	CRect arm2Rect = CRect(0, 0, arm2->Width(), arm2->Height());
	arm2->DrawTransparent(pDC, arm2Rect, arm2Rect, NULL);
	
	Translate(pDC, 272, 40, false);
	Rotate(pDC, -90, false);
}

void CGDI2018View::DrawFork(CDC* pDC)
{
	
	Translate(pDC, 14, -20, false);

	Translate(pDC, 14, 20, false);
	Rotate(pDC, ugaoFork, false);
	Translate(pDC, -14, -20, false);


	CRect viljuskaRect = CRect( header_viljuska.rclBounds.left,
								header_viljuska.rclBounds.top,
								header_viljuska.rclBounds.right,
								header_viljuska.rclBounds.bottom
								);
	Scale(pDC, 2.5, 2.5, false);
	pDC->PlayMetaFile(viljuska, viljuskaRect);
	Scale(pDC, -2.5, -2.5, false);

}

void CGDI2018View::DrawExcavator(CDC* pDC)
{
	CRect client;
	GetClientRect(&client);

	Translate(pDC, client.Width() - 400 + put, client.Height() - 300, false);
	DrawBody(pDC);
	DrawArm1(pDC);
	DrawArm2(pDC);
	DrawFork(pDC);
}

void CGDI2018View::OnDraw(CDC* pDC)
{
	CGDI2018Doc* pDoc = GetDocument();
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

	mem->SetGraphicsMode(GM_ADVANCED);
	
	XFORM stara;
	mem->GetWorldTransform(&stara);

	DrawBackground(mem);

	DrawExcavator(mem);

	mem->SetWorldTransform(&stara);
	pDC->BitBlt(0, 0, client.Width(), client.Height(), mem, 0, 0, SRCCOPY);

	delete mem;

}


// CGDI2018View printing

BOOL CGDI2018View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDI2018View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDI2018View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDI2018View diagnostics

#ifdef _DEBUG
void CGDI2018View::AssertValid() const
{
	CView::AssertValid();
}

void CGDI2018View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDI2018Doc* CGDI2018View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDI2018Doc)));
	return (CGDI2018Doc*)m_pDocument;
}
#endif //_DEBUG


// CGDI2018View message handlers


BOOL CGDI2018View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}


void CGDI2018View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar) {
	case '1':
		ugaoArm1 -= 10;
		break;
	case '2':
		ugaoArm1 += 10;
		break;
	case '3':
		ugaoArm2 -= 10;
		break;
	case '4':
		ugaoArm2 += 10;
		break;
	case '5':
		ugaoFork -= 10;
		break;
	case '6':
		ugaoFork += 10;
		break;
	case VK_LEFT:
		put -= 10;
		break;
	case VK_RIGHT:
		put += 10;
		break;
	}

	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
