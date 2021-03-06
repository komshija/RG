
// LabVezba1View.cpp : implementation of the CLabVezba1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LabVezba1.h"
#endif

#include "LabVezba1Doc.h"
#include "LabVezba1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <cmath>
using namespace std;

// CLabVezba1View

IMPLEMENT_DYNCREATE(CLabVezba1View, CView)

BEGIN_MESSAGE_MAP(CLabVezba1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CLabVezba1View construction/destruction

CLabVezba1View::CLabVezba1View() noexcept
{
	// TODO: add construction code here
	this->keyPressed = false;
	this->gridSize = 25;
}

double CLabVezba1View::getX(int radius, float angle)
{
	return double(radius * std::cosf(angle));
}

void CLabVezba1View::crtajTrougao(CDC* pDC, CPoint& p1, CPoint& p2, CPoint& p3, CBrush* brush)
{
	CBrush* oldBrush = pDC->SelectObject(brush);

	CPoint* trougao = new CPoint[3];
	trougao[0] = p1;
	trougao[1] = p2;
	trougao[2] = p3;
	pDC->Polygon(trougao, 3);
	delete[] trougao;

	pDC->SelectObject(oldBrush);
}

void CLabVezba1View::crtajCetvorougao(CDC* pDC, CPoint& p1, CPoint& p2, CPoint& p3, CPoint& p4, CBrush* brush)
{
	CBrush* oldBrush = pDC->SelectObject(brush);

	CPoint* cetvorougao = new CPoint[4];
	cetvorougao[0] = p1;
	cetvorougao[1] = p2;
	cetvorougao[2] = p3;
	cetvorougao[3] = p4;
	pDC->Polygon(cetvorougao, 4);
	delete[] cetvorougao;
	pDC->SelectObject(oldBrush);
}

double CLabVezba1View::getY(int radius, float angle)
{
	return double(radius * std::sinf(angle));
}

void CLabVezba1View::crtajMnogougao(CDC* pDC, double radius, int cornerCount, double x, double y, CBrush* brush)
{
	CGdiObject* oldBrush = nullptr;
	if (brush != nullptr)
		oldBrush = pDC->SelectObject(brush);
	else
		oldBrush = pDC->SelectStockObject(NULL_BRUSH);
	const double KRUG_CONST = 2 * 3.14159265358979323846;
	double deoKruga = KRUG_CONST / cornerCount;
	double mainRadius = radius * this->gridSize;
	CPoint* mnogougao = new CPoint[cornerCount];
	for (int i = 0; i < cornerCount; i++)
	{
		int xcoord = (int)getX(mainRadius, deoKruga * i) + x * this->gridSize;
		int ycoord = (int)getY(mainRadius, deoKruga * i) + y * this->gridSize;
		mnogougao[i] = CPoint(xcoord, ycoord);
	}
	pDC->Polygon(mnogougao, cornerCount);
	delete[] mnogougao;

	pDC->SelectObject(oldBrush);
}


CLabVezba1View::~CLabVezba1View()
{
}

BOOL CLabVezba1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLabVezba1View drawing

void CLabVezba1View::OnDraw(CDC* pDC)
{
	CLabVezba1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	CPen* zeleniPen = new CPen(PS_SOLID, 5, RGB(0, 255, 0));
	CPen* stariPen = pDC->SelectObject(zeleniPen);

	//================================================================
	//============================ZELENI==============================

	CBrush* zeleniBrush = new CBrush(RGB(0, 200, 0));
	crtajTrougao(pDC,
		CPoint(1.5 * this->gridSize, 11.5 * this->gridSize),
		CPoint(15.5 * this->gridSize, 11.5 * this->gridSize),
		CPoint(8.5 * this->gridSize, 18.5 * this->gridSize),
		zeleniBrush);
	delete zeleniBrush;

	//================================================================
	//=======================NARANDZASTI==============================
	
	CBrush* narandzastiBrush = new CBrush(RGB(255, 128, 0));
	crtajTrougao(pDC,
		CPoint(1.5 * this->gridSize, 11.5 * this->gridSize),
		CPoint(15.5 * this->gridSize, 11.5 * this->gridSize),
		CPoint(8.5 * this->gridSize, 4.5 * this->gridSize),
		narandzastiBrush);
	delete narandzastiBrush;

	//================================================================
	//=========================SRAFIRANI==============================

	CBrush* srafuraBrush = new CBrush(HS_DIAGCROSS, RGB(0, 0, 255));
	crtajCetvorougao(pDC,
		CPoint(5 * this->gridSize, 1 * this->gridSize),
		CPoint(12 * this->gridSize, 1 * this->gridSize),
		CPoint(15.5 * this->gridSize, 4.5 * this->gridSize),
		CPoint(8.5 * this->gridSize, 4.5 * this->gridSize),
		srafuraBrush);
	delete srafuraBrush;

	//================================================================
	//========================LJUBICASTI==============================

	CBrush* ljubicastiBrush = new CBrush(RGB(128, 0, 200));
	crtajTrougao(pDC,
		CPoint(8.5 * this->gridSize, 4.5 * this->gridSize),
		CPoint(15.5 * this->gridSize, 4.5 * this->gridSize),
		CPoint(12 * this->gridSize, 8 * this->gridSize),
		ljubicastiBrush);
	delete ljubicastiBrush;

	//================================================================
	//=============================ZUTI===============================

	CBrush* zutiBrush = new CBrush(RGB(255, 255, 0));
	crtajTrougao(pDC,
		CPoint(15.5 * this->gridSize, 11.5 * this->gridSize),
		CPoint(19 * this->gridSize, 8 * this->gridSize),
		CPoint(19 * this->gridSize, 15 * this->gridSize),
		zutiBrush);
	delete zutiBrush;

	//================================================================
	//============================CRVENI==============================

	CBrush* crveniBrush = new CBrush(RGB(255, 0, 0));
	crtajCetvorougao(pDC,
		CPoint(15.5 * this->gridSize, 4.5 * this->gridSize),
		CPoint(12 * this->gridSize, 8 * this->gridSize),
		CPoint(15.5 * this->gridSize, 11.5 * this->gridSize),
		CPoint(19 * this->gridSize, 8 * this->gridSize),
		crveniBrush);
	delete crveniBrush;

	//================================================================
	//=============================ROZE===============================

	CBrush* rozeBrush = new CBrush(RGB(255, 128, 255));
	crtajTrougao(pDC,
		CPoint(12 * this->gridSize, 1 * this->gridSize),
		CPoint(19 * this->gridSize, 1 * this->gridSize),
		CPoint(19 * this->gridSize, 8 * this->gridSize),
		rozeBrush);
	delete rozeBrush;
	
	//================================================================
	//======================PRAVILNI MNOGOUGLOVI======================
	pDC->SelectObject(stariPen);
	zeleniPen->DeleteObject();
	zeleniPen = new CPen(PS_SOLID, 3, RGB(0, 255, 0));
	pDC->SelectObject(zeleniPen);

	crtajMnogougao(pDC, 1.5, 7,8.5,14.4, nullptr);
	crtajMnogougao(pDC, 1.5, 6, 8.5, 8.4, nullptr);
	crtajMnogougao(pDC, 0.75, 5, 12, 5.8 , nullptr);
	crtajMnogougao(pDC, 0.75, 4, 17.5, 11.5, nullptr);
	crtajMnogougao(pDC, 1.1, 8, 16.9, 3.1, nullptr);


	pDC->SelectObject(stariPen);
	delete zeleniPen;

	//================================================================
	//=============================GRID===============================

	//Grid se crta pritiskom na SPACE
	//Grid se povecava pritiskom na strelicu na gore
	//Grid se smanjuje pritiskom na strelicu na dole
	if (this->keyPressed)
	{
		for (long x = 0; x < this->gridSize * 21; x = x + this->gridSize)
		{
			pDC->MoveTo(x, 0);
			pDC->LineTo(x, this->gridSize * 20);
		}
		for (long y = 0; y < this->gridSize * 21; y = y + this->gridSize)
		{
			pDC->MoveTo(0, y);
			pDC->LineTo(this->gridSize * 20, y);
		}
	}

}


// CLabVezba1View printing

BOOL CLabVezba1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLabVezba1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLabVezba1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLabVezba1View diagnostics

#ifdef _DEBUG
void CLabVezba1View::AssertValid() const
{
	CView::AssertValid();
}

void CLabVezba1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLabVezba1Doc* CLabVezba1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLabVezba1Doc)));
	return (CLabVezba1Doc*)m_pDocument;
}
#endif //_DEBUG


// CLabVezba1View message handlers


void CLabVezba1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_SPACE)
	{
		this->keyPressed = !this->keyPressed;
		Invalidate();
	}
	else if (nChar == VK_UP)
	{
		this->gridSize += 5;
		Invalidate();
	}
	else if (nChar == VK_DOWN)
	{
		if (this->gridSize != 5)
		{
			this->gridSize -= 5;
			Invalidate();
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
