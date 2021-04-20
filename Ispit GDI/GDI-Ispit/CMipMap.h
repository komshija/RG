#pragma once
#include "DImage.h"

class CMipMap
{
private:
	CDC* memDC;
	int width;
	int height;
	

public:
	CMipMap(CDC* pDC, CString name);
	~CMipMap();
	void DrawMipMap(CDC* pDC, int x, int y, int size);
};

