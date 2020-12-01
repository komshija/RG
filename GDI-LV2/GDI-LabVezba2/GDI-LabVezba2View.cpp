
// GDI-LabVezba2View.cpp : implementation of the CGDILabVezba2View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI-LabVezba2.h"
#endif

#include "GDI-LabVezba2Doc.h"
#include "GDI-LabVezba2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDILabVezba2View

IMPLEMENT_DYNCREATE(CGDILabVezba2View, CView)

BEGIN_MESSAGE_MAP(CGDILabVezba2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGDILabVezba2View construction/destruction

CGDILabVezba2View::CGDILabVezba2View() noexcept
{
	// TODO: add construction code here
	drawGrid = false;
	emf_cactus = GetEnhMetaFile(CString("cactus_part.emf"));
	emf_cactus_light = GetEnhMetaFile(CString("cactus_part_light.emf"));
	angle1 = 0;
	angle2 = 0;
}

CGDILabVezba2View::~CGDILabVezba2View()
{
	DeleteEnhMetaFile(emf_cactus);
	DeleteEnhMetaFile(emf_cactus_light);
}

BOOL CGDILabVezba2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDILabVezba2View drawing

void CGDILabVezba2View::OnDraw(CDC* pDC)
{
	CGDILabVezba2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRgn region;
	region.CreateRectRgnIndirect(_SetRegion(pDC));
	_DrawBackground(pDC);
	_DrawCactus(pDC);
	_DrawPot(pDC);
	_DrawName(pDC);

	if (drawGrid)
		_DrawGrid(pDC);
	
	pDC->SelectClipRgn(&region);
}



// CGDILabVezba2View printing

BOOL CGDILabVezba2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDILabVezba2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDILabVezba2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDILabVezba2View diagnostics

#ifdef _DEBUG
void CGDILabVezba2View::AssertValid() const
{
	CView::AssertValid();
}

void CGDILabVezba2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDILabVezba2Doc* CGDILabVezba2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDILabVezba2Doc)));
	return (CGDILabVezba2Doc*)m_pDocument;
}
#endif //_DEBUG


// CGDILabVezba2View message handlers

void CGDILabVezba2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar)
	{
	case VK_SPACE:
		drawGrid = !drawGrid;
		Invalidate();
		break;

	case VK_LEFT:
		angle1 -= angleStep;
		Invalidate();
		break;

	case VK_RIGHT:
		angle1 += angleStep;
		Invalidate();
		break;

	case VK_UP:
		angle2 += angleStep;
		Invalidate();
		break;

	case VK_DOWN:
		angle2 -= angleStep;
		Invalidate();
		break;

	default:
		break;
	}


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//User methods

CRect* CGDILabVezba2View::_SetRegion(CDC* pDC)
{
	CRect result;
	pDC->GetClipBox(result);
	CRgn region;
	region.CreateRectRgn(0, 0, 500, 500);
	pDC->SelectClipRgn(&region);
	return &result;
}

void CGDILabVezba2View::_DrawGrid(CDC* pDC)
{
	for (int p = 25; p <= 500; p = p + 25)
	{
		pDC->MoveTo(p, 0);
		pDC->LineTo(p, 500);
		pDC->MoveTo(0, p);
		pDC->LineTo(500, p);
	}
}

void CGDILabVezba2View::_DrawPot(CDC* pDC)
{
	CBrush* brush = new CBrush(RGB(222, 148, 0));
	CBrush* oldBrush = pDC->SelectObject(brush);
	CPoint* trapez = new CPoint[4]();
	trapez[0] = CPoint(200, 450);
	trapez[1] = CPoint(300, 450);
	trapez[2] = CPoint(290, 500);
	trapez[3] = CPoint(210, 500);
	pDC->Polygon(trapez, 4);
	pDC->Rectangle(190, 430, 310, 450);
	pDC->SelectObject(oldBrush);
	delete[]trapez;
	delete brush;
}

void CGDILabVezba2View::_DrawName(CDC* pDC)
{
	XFORM oldForm, form1;
	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	pDC->GetWorldTransform(&oldForm);
	//Postavljamo rotaciju za Pi/2
	_SetRoation(pDC, C_PI / 2.0, 475, 25);

	CString* ime = new CString("16835 Milan Radosavljevic");
	CFont* font = new CFont();
	font->CreateFontW(25, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));
	CFont* oldFont = pDC->SelectObject(font);
	CPoint textPosition(475, 25);
	pDC->SetBkMode(TRANSPARENT);

	COLORREF oldColor = pDC->SetTextColor(RGB(0, 0, 0));
	pDC->TextOutW(textPosition.x + 1, textPosition.y + 1, *ime);
	pDC->SetTextColor(RGB(255, 255, 0));
	pDC->TextOutW(textPosition.x, textPosition.y, *ime);

	pDC->SelectObject(oldFont);
	pDC->SetTextColor(oldColor);
	pDC->SetBkMode(OPAQUE);
	delete font;
	delete ime;
	pDC->SetWorldTransform(&oldForm);
	pDC->SetGraphicsMode(oldMode);
}

void CGDILabVezba2View::_DrawBackground(CDC* pDC)
{
	CBrush* brush = new CBrush(RGB(135, 206, 235));
	CBrush* oldBrush = pDC->SelectObject(brush);
	CPen* pen = new CPen(PS_NULL, 0, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(pen);
	CRect* rect = new CRect(0, 0, 501, 501);
	pDC->Rectangle(rect);
	delete rect;
	pDC->SelectObject(oldBrush);
	delete brush;
	pDC->SelectObject(oldPen);
	delete pen;

}

void CGDILabVezba2View::_DrawCactus(CDC* pDC)
{	
	//Postavljamo brush
	CBrush* brush = new CBrush(RGB(51, 204, 51));
	CBrush* oldBrush = pDC->SelectObject(brush);
	XFORM oldForm;


	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	pDC->GetWorldTransform(&oldForm);

	//Postavimo vecu promenjivu rotaciju 1
	_SetTransformation1(pDC);
	//Crtamo prvi kaktus
	PlayEnhMetaFile(pDC->m_hDC, emf_cactus_light, CRect(250 - (30 / 1), 350 , 250 + (30 / 1), 425 ));

	_DrawRightArm(pDC);
	_DrawUpper(pDC);
	_DrawLeftArm(pDC);

	//Crtamo donje spojeve (krugove) jer su oni ispred kaktusa
	pDC->Ellipse(250 - 10, 350 - 10, 250 + 10, 350 + 10);
	pDC->Ellipse(250 - 10, 425 - 10, 250 + 10, 425 + 10);

	pDC->SetWorldTransform(&oldForm);
	pDC->SelectObject(oldBrush);
	delete brush;
	pDC->SetGraphicsMode(oldMode);

}

void CGDILabVezba2View::_DrawRightArm(CDC* pDC)
{
	XFORM form,saveForm,oldForm;
	pDC->GetWorldTransform(&oldForm);
	//Ovde smo pod uticajem samo prve promenjive transformacije
	const double angleStep4 = C_PI / 4;

	//Rotiramo prvo za Pi/4
	_SetRoation(pDC, angleStep4, 250, 350);
	PlayEnhMetaFile(pDC->m_hDC, emf_cactus, CRect(250 - (30 / 3), 275 , 250 + (30 / 3), 350));
	
	pDC->GetWorldTransform(&saveForm);

	//Na vec rotirano za Pi/4 zarotiramo jos za Pi/4

	_SetRoation(pDC, angleStep4, 250, 275);


	PlayEnhMetaFile(pDC->m_hDC, emf_cactus, CRect(250 - (30 / 2) - 5, 200 , 250 + (30 / 2) + 5, 275 ));
	//Resetujemo na prvu rotaciju za Pi/4
	pDC->SetWorldTransform(&saveForm);

	//Na vec rotirano za Pi/4 rotiramo za -Pi/4
	_SetRoation(pDC, -angleStep4, 250, 275);


	PlayEnhMetaFile(pDC->m_hDC, emf_cactus, CRect(250 - (30 / 2) - 5, 200 , 250 + (30 / 2) + 5, 275 ));

	pDC->SetWorldTransform(&saveForm);
	pDC->Ellipse(250 - 10, 275 - 10, 250 + 10, 275 + 10);

	pDC->SetWorldTransform(&oldForm);

}

void CGDILabVezba2View::_DrawLeftArm(CDC* pDC)
{
	XFORM oldForm, form;
	pDC->GetWorldTransform(&oldForm);
	
	//Postavlja se na rotaciju -Pi/4 koja je pod uticajem samo vece promenjive rotacije
	const double angleStep4 = C_PI / 4;
	_SetRoation(pDC, -angleStep4, 250, 350);

	PlayEnhMetaFile(pDC->m_hDC, emf_cactus, CRect(250 - (30 / 3), 275 , 250 + (30 / 3), 350 ));

	pDC->SetWorldTransform(&oldForm);
}

void CGDILabVezba2View::_DrawUpper(CDC* pDC)
{
	XFORM saveForm, form,oldForm;
	pDC->GetWorldTransform(&oldForm);
	//Postavljamo manju promenjivu rotaciju 
	_SetTransformation2(pDC);


	PlayEnhMetaFile(pDC->m_hDC, emf_cactus_light, CRect(250 - (30 / 3), 275 , 250 + (30 / 3), 350 ));
	pDC->GetWorldTransform(&saveForm);
	//Ovde smo pod uticajem obe promenjive transformacije
	
	//Prvo rotiramo za Pi/4
	const double angleStep4 = C_PI / 4;

	_SetRoation(pDC, angleStep4, 250, 275);

	//Gornji desni deo
	PlayEnhMetaFile(pDC->m_hDC, emf_cactus, CRect(250 - (30 / 3), 200 , 250 + (30 / 3), 275 ));
	PlayEnhMetaFile(pDC->m_hDC, emf_cactus, CRect(250 - (30 / 1), 125 , 250 + (30 / 1), 200 ));
	pDC->Ellipse(250 - 10, 200 - 10, 250 + 10, 200 + 10);
	
	//Vracamo uticaj na samo promenjive transformacije
	pDC->SetWorldTransform(&saveForm);
	//Crtamo gornji deo
	PlayEnhMetaFile(pDC->m_hDC, emf_cactus, CRect(250 - (30 / 3), 200 , 250 + (30 / 3), 275 ));
	PlayEnhMetaFile(pDC->m_hDC, emf_cactus, CRect(250 - (30 / 1), 125 , 250 + (30 / 1), 200 ));
	pDC->Ellipse(250 - 10, 200 - 10, 250 + 10, 200 + 10);

	//Rotiramo za -Pi/4, a pod uticajem smo obe promenjive transformacije
	
	_SetRoation(pDC, -angleStep4, 250, 275);

	PlayEnhMetaFile(pDC->m_hDC, emf_cactus, CRect(250 - (30 / 3), 200 , 250 + (30 / 3), 275 ));

	//Vracamo uticaj na samo promenjive transformacije
	pDC->SetWorldTransform(&saveForm);
	//Crtamo krugove koji su ispred kaktusa i koji su pod uticajem obe promenjive transformacije
	pDC->Ellipse(250 - 10, 275 - 10, 250 + 10, 275 + 10);
	pDC->Ellipse(250 - 10, 200 - 10, 250 + 10, 200 + 10);

	pDC->SetWorldTransform(&oldForm);
}

void CGDILabVezba2View::_SetTransformation1(CDC* pDC)
{
	XFORM  form1;

	form1 = {
		cosf(angle1),
		sinf(angle1),
		-sinf(angle1),
		cosf(angle1),
		250,
		425
	};
	pDC->SetWorldTransform(&form1);

	form1 = {
		1,
		0,
		0,
		1,
		-250,
		-425
	};
	pDC->ModifyWorldTransform(&form1, MWT_LEFTMULTIPLY);

}

void CGDILabVezba2View::_SetTransformation2(CDC* pDC)
{
	XFORM form2;
	form2 = {
		cosf(angle2),
		sinf(angle2),
		-sinf(angle2),
		cosf(angle2),
		250,
		350
	};
	pDC->ModifyWorldTransform(&form2, MWT_LEFTMULTIPLY);
	form2 = {
		1,
		0,
		0,
		1,
		-250,
		-350
	};
	pDC->ModifyWorldTransform(&form2, MWT_LEFTMULTIPLY);
}

void CGDILabVezba2View::_SetRoation(CDC* pDC, float angle, float x, float y)
{
	XFORM form;
	form = {
		cosf(angle),
		sinf(angle),
		-sinf(angle),
		cosf(angle),
		x,
		y
	};
	pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
	form = {
		1,
		0,
		0,
		1,
		-x,
		-y
	};
	pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}