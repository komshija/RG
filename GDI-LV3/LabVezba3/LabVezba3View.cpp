
// LabVezba3View.cpp : implementation of the CLabVezba3View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LabVezba3.h"
#endif

#include "LabVezba3Doc.h"
#include "LabVezba3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CLabVezba3View
IMPLEMENT_DYNCREATE(CLabVezba3View, CView)
BEGIN_MESSAGE_MAP(CLabVezba3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CLabVezba3View construction/destruction

CLabVezba3View::CLabVezba3View() noexcept
{
	// TODO: add construction code here
	part = new DImage * [3];
	for (int i = 0; i < 3; i++)
	{
		part[i] = new DImage[3];
		for (int j = 0; j < 3; j++)
		{
			CString fileName;
			fileName.Format(CString("Bitmaps/index%d%d.bmp"), i, j);
			part[i][j].Load(fileName);
			part[i][j].MakeItGrey();
		}
	}
}

CLabVezba3View::~CLabVezba3View()
{
	for (int i = 0; i < 3; i++)
		delete[] part[i];
	delete[] part;
}

BOOL CLabVezba3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLabVezba3View drawing

void CLabVezba3View::OnDraw(CDC* pDC)
{
	CLabVezba3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;



	
	CRect clientWindow;
	GetClientRect(&clientWindow);
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, clientWindow.Width(), clientWindow.Height());

	memDC->SelectObject(bmp);
	DrawGrid(memDC);
	//====================
	int oldGMode = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM oldForm;
	memDC->GetWorldTransform(&oldForm);

	//0,0 - Done
	
	Translate(memDC, 128, 128, false);
	Mirror(memDC, false, true, false);
	Rotate(memDC, 5.78, false);
	Translate(memDC, -(128), -(128), false);
	DrawTransparent(memDC, &part[0][0], -22, 22);
	memDC->SetWorldTransform(&oldForm);
	
	//0,1 - Done
	
	Translate(memDC, 128, 134, false);
	Mirror(memDC, true, false, false);
	Rotate(memDC, 81.9, false);
	Translate(memDC, -(128), -(134), false);
	DrawTransparent(memDC, &part[0][1], -49, 115);
	memDC->SetWorldTransform(&oldForm);
	
	//0,2 - Done

	Translate(memDC, 128, 134, false);
	Mirror(memDC, false, true,false);
	Rotate(memDC, -97.3, false);
	Translate(memDC, -(128), -(134), false);
	DrawTransparent(memDC, &part[0][2], -66, 265);
	memDC->SetWorldTransform(&oldForm);

	//1,0 - Done

	Translate(memDC, 121, 133, false);
	Mirror(memDC, true, false, false);
	Rotate(memDC, -14, false);
	Translate(memDC, -(121), -(133), false);
	DrawTransparent(memDC, &part[1][0], -13, 117);
	memDC->SetWorldTransform(&oldForm);

	//1,1 - Done

	Translate(memDC, 121, 133, false);
	Mirror(memDC, false, true, false);
	Rotate(memDC, 99, false);
	Translate(memDC, -(121), -(133), false);
	DrawTransparent(memDC, &part[1][1], -139, -112);
	memDC->SetWorldTransform(&oldForm);

	//1,2 - Done

	Translate(memDC, 122, 134, false);
	Mirror(memDC, true, false, false);
	Rotate(memDC, 33.3, false);
	Translate(memDC, -(122), -(134), false);
	DrawTransparent(memDC, &part[1][2], -172, 247);
	memDC->SetWorldTransform(&oldForm);

	//2,0 - Done

	Translate(memDC, 125, 140, false);
	Mirror(memDC, true, false, false);
	Rotate(memDC, 25, false);
	Translate(memDC, -(125), -(140), false);
	DrawTransparent(memDC, &part[2][0],  133, 229);
	memDC->SetWorldTransform(&oldForm);

	//2,1 - Done

	Translate(memDC, 125, 140, false);
	Mirror(memDC, false, true, false);
	Rotate(memDC, 91, false);
	Translate(memDC, -(125), -(140), false);
	DrawTransparent(memDC, &part[2][1], -262, -117);
	memDC->SetWorldTransform(&oldForm);

	//2,1 - Done

	Translate(memDC, 125, 140, false);
	Mirror(memDC, false, true, false);
	Rotate(memDC, -30, false);
	Translate(memDC, -(125), -(140), false);
	DrawTransparent(memDC, &part[2][2], 369, -83);
	memDC->SetWorldTransform(&oldForm);




	memDC->SetWorldTransform(&oldForm);
	memDC->SetGraphicsMode(oldGMode);
	//====================
	MemDCTopDC(memDC, pDC);
	//pDC->BitBlt(0, 0, clientWindow.Width(), clientWindow.Height(), memDC, 0, 0, SRCCOPY);
	delete memDC;
	
}

// CLabVezba3View printing

BOOL CLabVezba3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}
void CLabVezba3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}
void CLabVezba3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}
// CLabVezba3View diagnostics

#ifdef _DEBUG
void CLabVezba3View::AssertValid() const
{
	CView::AssertValid();
}

void CLabVezba3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLabVezba3Doc* CLabVezba3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLabVezba3Doc)));
	return (CLabVezba3Doc*)m_pDocument;
}
#endif //_DEBUG


// CLabVezba3View message handlers
BOOL CLabVezba3View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


// User methods


void CLabVezba3View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM form =
	{
		1,
		0,
		0,
		1,
		dX,
		dY
	};
	pDC->ModifyWorldTransform(&form, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CLabVezba3View::Scale(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM form =
	{
		dX,
		0,
		0,
		dY,
		0,
		0
	};
	pDC->ModifyWorldTransform(&form, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CLabVezba3View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM form =
	{
		cosf(angle * stepAngle),
		sinf(angle * stepAngle),
		-sinf(angle * stepAngle),
		cosf(angle * stepAngle),
		0,
		0
	};
	pDC->ModifyWorldTransform(&form, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CLabVezba3View::Mirror(CDC* pDC, bool mx, bool my, bool rightMultiply)
{
	XFORM form =
	{
		mx ? -1 : 1,
		0,
		0,
		my ? -1 : 1,
		0,
		0
	};
	pDC->ModifyWorldTransform(&form, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CLabVezba3View::DrawTransparent(CDC* pDC, DImage* img, int x, int y)
{
	CBitmap mask;
	mask.CreateBitmap(img->Width(), img->Height(), 1, 1, NULL);
	CBitmap image;
	image.CreateBitmap(img->Width(), img->Height(), 4, 8, NULL);
	image.SetBitmapBits(img->Width() * img->Height() * img->BPP(), img->GetDIBBits());

	CDC* srcDC = new CDC();
	CDC* dstDC = new CDC();
	srcDC->CreateCompatibleDC(pDC);
	dstDC->CreateCompatibleDC(pDC);

	CBitmap* srcOldBitmap = srcDC->SelectObject(&image);
	CBitmap* dstOldBitmap = dstDC->SelectObject(&mask);

	COLORREF removeColor = srcDC->GetPixel(0, 0);
	COLORREF srcOldBckColor = srcDC->SetBkColor(removeColor);
	dstDC->BitBlt(0, 0, img->Width(), img->Height(), srcDC, 0, 0, SRCCOPY);

	COLORREF srcOldTextColor = srcDC->SetTextColor(RGB(255, 255, 255));
	srcDC->SetBkColor(RGB(0, 0, 0));
	srcDC->BitBlt(0, 0, img->Width(), img->Height(), dstDC, 0, 0, SRCAND);

	dstDC->SelectObject(dstOldBitmap);
	delete dstDC;

	srcDC->SelectObject(&mask);
	pDC->BitBlt(x, y, img->Width(), img->Height(), srcDC, 0, 0, SRCAND);
	srcDC->SelectObject(&image);
	pDC->BitBlt(x, y, img->Width(), img->Height(), srcDC, 0, 0, SRCPAINT);
	srcDC->SelectObject(srcOldBitmap);
	delete srcDC;
}

void CLabVezba3View::MemDCTopDC(CDC* memDC, CDC* pDC)
{
	CRect clientWindow;
	GetClientRect(&clientWindow);
	CBitmap mask;
	mask.CreateBitmap(clientWindow.Width(), clientWindow.Height(), 1, 1, NULL);
	CDC* dstDC = new CDC();
	dstDC->CreateCompatibleDC(memDC);
	dstDC->SelectObject(&mask);
	memDC->SetBkColor(RGB(0, 0, 0));
	memDC->SetTextColor(RGB(255, 255, 255));
	dstDC->BitBlt(0, 0, clientWindow.Width(), clientWindow.Height(), memDC, 0, 0, SRCPAINT);
	pDC->BitBlt(0, 0, clientWindow.Width(), clientWindow.Height(), dstDC, 0, 0, SRCAND);
	delete dstDC;
	pDC->BitBlt(0, 0, clientWindow.Width(), clientWindow.Height(), memDC, 0, 0, SRCPAINT);

}

void CLabVezba3View::DrawGrid(CDC* memDC)
{
	CPen* pen = new CPen(PS_SOLID, 1, RGB(1, 1, 1));
	CPen* oldPen = memDC->SelectObject(pen);
	for (int p = 25; p <= 500; p = p + 25)
	{
		memDC->MoveTo(p, 0);
		memDC->LineTo(p, 500);
		memDC->MoveTo(0, p);
		memDC->LineTo(500, p);
	}
	memDC->SelectObject(oldPen);
	delete pen;
}
