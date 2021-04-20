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

	float alpha = 0;
	float beta = 0;


protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 
	void DrawAxis();

	UINT LoadTexture(CString fileName);

	UINT TSC[6];
	UINT S[6];
	UINT M[6];

	void DrawPatch(double R, int n);
	void DrawEarth(double R, int n);
	void DrawMoon(double R, int n);
	void DrawSpace(double R, int n);

	
};
