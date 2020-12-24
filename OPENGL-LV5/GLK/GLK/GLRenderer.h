#pragma once
#include "CGLMaterial.h"

struct Vertex {
	float x, y, z;
};

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

	void DrawAxis();

	CPoint GetAngle() {
		return CPoint(angle_v, angle_h);
	}
	void SetAngles(float angle_h, float angle_v);
	
	void SwitchLight0();
	void SwitchLight1();
	void SwitchLight2();
	void SwitchNormals();

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 
	float angle_v;
	float angle_h;
	float get_x(float radius, float angle);
	float get_y(float radius, float angle);
	bool light0;
	bool light1;
	bool light2;
	bool normals;

	float radius1;
	float radius2;

	void DrawRoom();
	void DrawStand();
	void DrawVase();
	void DrawRing(float radius1, float radius2, float height);

	void IncRing(float step);
	void DecRing(float step);

	void DrawPrism(float radius, float height = 0.3, int sides = 4);
	void DrawSphere(float radius);
	void DrawRoller(float radius, float height = 0.3, int sides = 18);

	const double C_PI = 3.14159265358979323846;
	const double C_PI_RAD = 3.14159265358979323846 / 180.0;

	Vertex CalculateNormal(Vertex A, Vertex B, Vertex C);
	Vertex SubstractVectors(Vertex A, Vertex B);
	Vertex CrossProductVectors(Vertex A, Vertex B);
	Vertex Normalise(Vertex A);
	float Scalar(Vertex A);

	void AmbientLight();
	void ViewPointLight();

	void RedLight();
	void GreenLight();
	void BlueLight();

	CGLMaterial light_blue, dark_blue;
	CGLMaterial matBase;
	CGLMaterial roomBase;
	CGLMaterial greenSphere;
	CGLMaterial blueSphere;
	CGLMaterial redSphere;
};
