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
	float pomeraj[3] = {0,0,0};

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 

	UINT LoadTextures(CString fileName);
	void DrawCube(float size,float s,float t,float texStep);
	void DrawRubicCube(float size,int count);
	void SetWhiteLight();
	void SetMaterial(float r,float g,float b);
	UINT opengl;

};
