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
	float L = 0;

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 
	UINT LoadTexture(CString str);
	UINT tex;

	void DrawTorus(float R,float r);
	void RotateTorus(float L);
	
	void DrawCyllinder(float r, float h, float nr, float nh=1);
	void DrawTelescope(float r, float h, float nr,float nh,float alpha,float dHolder,float angleHor,float angleVer,float dHidden,float dVisor);
	
	void DrawRoller(float r, float h, float nr, float nh);
	void DrawTwoRollers(float r, float h, float nr, float nh, float p);
	void DrawFigure(float r, float d, float hp, float h1, float p1, float h2, float p2, float h3, float p3, float alpha, float beta, float gama, CString tex);

	void DrawRing(float h, float R1, float R2, int n, CString tex);
	void DrawTwoRings();

	void DrawSphere(float R);

	void DrawSpiralPart(float R);
	void DrawSpiral(int n, float dr, float dAlpha, float ds);

	void DrawFigure2017(float h,float dx,float alpha,float beta,float dt,CString tex[]);

	void DrawColumn(float side, float height);
	void DrawPyramid(float side, float height, int n);
	void DrawPyramid2(float side, float height, int n);
	void Draw2Pyramid(float side, float height);
	void DrawFigureSept2017(float aS, float hS, float aR, float size, float height, float ratio, float angle);

	void DrawBox(float a, float b, float c);
	void DrawStub(float r,float h,int steps);
	void DrawCilindar(float r, float h, int steps);
	void DrawTample();

	void DrawSide(float x, float y, int nPartX, int nPartY, int nTexX, int nTexY);
	void DrawBox2018(float x, float y, float z, int nPartX, int nPartY, int nPartZ, int nTexX, int nTexY, int nTexZ);
	void DrawBasket(float w, float h, float d);
	void DrawFigureJan2018(float w, float h, float d, float r, float alpha, float beta, float gama);

	void DrawPaperPlane(float h);
	void DrawPaperPlaneA(float h);
	void DrawPaperPlaneB(float h);
	void DrawPaperPlaneC(float h);
	void DrawPaperPlaneD(float h);

	void DrawVase(float size);

	void DrawCone(float r,float h);
	void DrawFigure2013();

	void DrawTrapez(float a, float b, float h, float H);
	void DrawTrapezRing(float a, float b, float h, float H);
	void DrawTrapezFigure(float a, float b, float h, float H);

	void DrawPatch(float r, float LonMin, float LonMax, float LatMin, float LatMax, float dLon, float dLat);
	void DrawGlobe(float r);

	void DrawFigure2020(float r, float h, int n);

	void DrawCubeVector(float a);

	void DrawTorusVector(float R, float r);

	void DrawWheel();
};
