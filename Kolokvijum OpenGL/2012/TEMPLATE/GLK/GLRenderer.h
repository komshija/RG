#pragma once
#include "DImage.h"

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);
		
	bool CreateGLContext(CDC* pDC);			// kreira OpenGL Rendering Context
	void PrepareScene(CDC* pDC);			// inicijalizuje scenu,
	void Reshape(CDC* pDC, int w, int h);	// kod koji treba da se izvrsi svaki put kada se promeni velicina prozora ili pogleda i
	void DrawScene(CDC* pDC);				// iscrtava scenu
	void DestroyScene(CDC* pDC);			// dealocira resurse alocirane u drugim funkcijama ove klase,

	float alfa = 0, beta = 0;

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 

	UINT LoadTextures(CString fileName);
	void DrawCube(float size);
	void DrawAbazur(double r1,double r2, double h, int step);
	void DrawTelo(double r1,double r2, double r3, double h, int step);

	UINT marble, fabric, metal;

};
