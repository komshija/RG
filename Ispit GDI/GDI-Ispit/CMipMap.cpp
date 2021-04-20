#include "pch.h"
#include "CMipMap.h"

CMipMap::CMipMap(CDC *pDC,CString name)
{
	memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	DImage* img = new DImage();
	img->Load(name);


	width = img->Width();
	height = img->Height();

	int maxW = img->Width();
	int tempw = img->Width()/2;

	while (tempw > 0) {
		maxW += tempw;
		tempw = tempw / 2;
	}

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, maxW , img->Height());
	memDC->SelectObject(&bmp);



	int w = img->Width();
	int h = img->Height();

	CRect drawRect(0, 0,img->Width(),img->Height());
	CRect imgRect(0,0,img->Width(), img->Height());

	while (w > 0) {
		img->Draw(memDC, imgRect, drawRect);
		drawRect.left += w;
		w = w / 2;
		drawRect.right += w;
		h = h / 2;
		drawRect.bottom = h;

	}

	delete img;

}

CMipMap::~CMipMap()
{
	delete memDC;
}

void CMipMap::DrawMipMap(CDC* pDC, int x, int y, int size)
{
	int temp = this->width;
	int pom = 0;
	while (temp > size) {
		pom = pom + temp;
		temp = temp / 2;
	}
	pDC->BitBlt(x, y, temp, temp, memDC, pom, 0, SRCCOPY);
}
