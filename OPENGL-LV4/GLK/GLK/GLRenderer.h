#pragma once

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

	void DrawPrism(float radius, float height = 0.3, int sides = 4);
	void DrawSphere(float radius, float lats, float longs);
	void DrawCone(float radius, float height = 0.3, int sides = 6);
	void DrawRoller(float radius, float height = 0.3, int sides = 18);

	void DrawAxis();
	void DrawGrid();

	CPoint GetAngle() {
		return CPoint(angle_v, angle_h);
	}
	void SetAngles(float angle_h, float angle_v);

	inline void AngleCX(int angle) {
		angle_cx += angle;
	}

	inline void AngleCY(int angle) {
		angle_cy += angle;
	}

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 

	void DrawPot();
	void DrawFigure();

	float get_x(float radius, float angle);
	float get_y(float radius, float angle);

	float angle_v;
	float angle_h;

	float angle_cx;
	float angle_cy;

	const double C_PI = 3.14159265358979323846;
	const double C_PI_RAD = 3.14159265358979323846 / 180.0;

	void MiddleBranch();
	void RightBranch();
	void LeftBranch();
};
