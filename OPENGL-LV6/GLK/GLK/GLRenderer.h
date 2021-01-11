#pragma once
#include "CGLTexture.h"
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

	void SetAngles(float angle_h, float angle_v);
	CPoint GetAngle() {
		return CPoint(angle_v, angle_h);
	}

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 

	float angle_v;
	float angle_h;
	void DrawGround();
	void DrawAxis();
	void DrawSide();
	void DrawWheelSide();
	void DrawWheel();

	void DrawTruck();
	void DrawSphere(float radius);

	CGLTexture groundTex, truckTex;
};
