#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#pragma comment(lib, "GL\\glut32.lib")


CGLRenderer::CGLRenderer(void)
{

}

CGLRenderer::~CGLRenderer(void)
{
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult) return false;

	m_hrc = wglCreateContext(pDC->m_hDC);

	if (!m_hrc) return false;

	return true;
}

void CGLRenderer::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	tex = LoadTexture(CString("tex.jpg"));
	//glEnable(GL_TEXTURE_2D);
	float pos[4] = { 0,0,1,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0, 0, -10);

	glRotated(beta, 1, 0, 0);
	glRotated(alfa, 0, 1, 0);

	//DrawTorus(3, 1);
	//RotateTorus(L);

	//DrawSphere(3);

	glColor3f(1, 1, 1);
	//DrawSpiralPart(3);

	//DrawSpiral(10, 1.5, 10, 1.1);

	//glColor3f(1, 0, 0);
	//DrawTelescope(1, 5, 18, 4, 10, 1, 30, 40, 0, 1);

	//DrawFigure(1, 2, 2,
	//	5, 1,
	//	5, 1,
	//	5, 1,
	//	90, 30, 60,
	//	CString("marble.bmp"));
	//glBindTexture(GL_TEXTURE_2D, tex);
	//DrawRing(2, 5, 7, 30, CString("marble.bmp"));
	//DrawTwoRings();

	//DrawFigure2017(3, 0.5, 30, 20, L, NULL);

	//DrawColumn(3, 5);

	/*
	DrawPyramid(3, 3, 4);
	glTranslatef(0, 5, 0);
	DrawPyramid2(3, 3, 4);
	*/

	//Draw2Pyramid(1, 3);
	//DrawFigureSept2017(1, 10, 2, 2, 2, 4, L);

	//DrawBox(1, 1, 0.3);
	//DrawStub(0.5, 8, 10);
	//DrawTample();

	//paper plane idea for angle


	//DrawSide(10, 10, 4, 4, 1, 1);
	//DrawBox2018(5, 5, 5, 4, 4, 4, 1, 2, 3);
	//DrawBasket(5, 5, 1);
	//DrawFigureJan2018(1, 5, 7, 3, 0, 60, 60);

	//DrawPaperPlane(10);

	//glColor3f(1, 1, 0);
	//DrawVase(10);

	//DrawCone(1, 2);
	//DrawFigure2013();

//	DrawTrapezFigure(2, 1, 1, 2);

	//DrawPatch(3, -45, 45, -45, 45, 5, 5);
	//DrawGlobe(3);

	//DrawFigure2020(1, 2, 4);
	glColor3f(0.5, 0.5, 0.5);
	//DrawCubeVector(3);

	//DrawTorusVector(3, 1);
	//DrawTorus(3, 1);
	glBindTexture(GL_TEXTURE_2D, 0);
	//DrawTample();
	//DrawRing(1,2,3,36,NULL);

	DrawWheel();
	glFlush();
	SwapBuffers(pDC->m_hDC);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)w / h, 0.1, 2000);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 

	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

UINT CGLRenderer::LoadTexture(CString str)
{
	UINT id;
	DImage img;
	img.Load(str);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());

	return id;
}

//2017 januar

void CGLRenderer::DrawTorus(float R, float r)
{
	float step = (2. * 3.14) / 36.;
	float texStep = 1. / 36.;
	glColor3f(0.5, 0.25, 0.25);

	glBegin(GL_QUADS);
	for (int i = 0; i <= 36; i++) {
		float alfa = step * i;
		for (int j = 0; j <= 36; j++) {
			float beta = step * j;

			glTexCoord2f(i * texStep, j * texStep);
			glNormal3f(cos(beta) * cos(alfa), sin(beta) * cos(alfa), sin(alfa));
			glVertex3f((R + r * cos(alfa)) * cos(beta), (R + r * cos(alfa)) * sin(beta), r * sin(alfa));

			glTexCoord2f(i * texStep, (j + 1) * texStep);
			glNormal3f(cos(beta + step) * cos(alfa), sin(beta + step) * cos(alfa), sin(alfa));
			glVertex3f((R + r * cos(alfa)) * cos(beta + step), (R + r * cos(alfa)) * sin(beta + step), r * sin(alfa));

			glTexCoord2f((i + 1) * texStep, (j + 1) * texStep);
			glNormal3f(cos(beta + step) * cos(alfa + step), sin(beta + step) * cos(alfa + step), sin(alfa + step));
			glVertex3f((R + r * cos(alfa + step)) * cos(beta + step), (R + r * cos(alfa + step)) * sin(beta + step), r * sin(alfa + step));

			glTexCoord2f((i + 1) * texStep, j * texStep);
			glNormal3f(cos(beta) * cos(alfa + step), sin(beta) * cos(alfa + step), sin(alfa + step));
			glVertex3f((R + r * cos(alfa + step)) * cos(beta), (R + r * cos(alfa + step)) * sin(beta), r * sin(alfa + step));

		}
	}
	glEnd();


}

void CGLRenderer::RotateTorus(float L)
{
	//Torus se crta u xy ravni , rotiramo ga u xz ravan
	glRotatef(90, 1, 0, 0);
	//Transliramo da ga postavimo na poziciju
	float R = 3;
	float r = 1;

	float obim = 3.14 * 2 * (R + r);
	float ugao = (360 * L) / obim;

	glTranslatef(0, R + r, 0);
	glTranslatef(L, 0, 0);
	glRotatef(ugao, 0, 0, 1);

	DrawTorus(R, r);

}

//2021 januar

void CGLRenderer::DrawCyllinder(float r, float h, float nr, float nh)
{
	float stepH = h / nh;
	float stepAngle = (360 / nr) * (3.14 / 180);
	float stepTexS = 1. / nr;
	float stepTexT = 1. / nh;

	glBegin(GL_QUADS);
	for (int i = 0; i < nr; i++)
	{
		for (int j = 0; j < nh; j++)
		{
			glTexCoord2f(i * stepTexS, j * stepTexT);
			glNormal3f(cos((i)*stepAngle), 0, sin((i)*stepAngle));
			glVertex3f(r * cos((i)*stepAngle), h - j * stepH, r * sin((i)*stepAngle));

			glTexCoord2f((i + 1) * stepTexS, j * stepTexT);
			glNormal3f(cos((i + 1) * stepAngle), 0, sin((i + 1) * stepAngle));
			glVertex3f(r * cos((i + 1) * stepAngle), h - j * stepH, r * sin((i + 1) * stepAngle));

			glTexCoord2f((i + 1) * stepTexS, (j + 1) * stepTexT);
			glNormal3f(cos((i + 1) * stepAngle), 0, sin((i + 1) * stepAngle));
			glVertex3f(r * cos((i + 1) * stepAngle), h - (j + 1) * stepH, r * sin((i + 1) * stepAngle));

			glTexCoord2f(i * stepTexS, (j + 1) * stepTexT);
			glNormal3f(cos((i)*stepAngle), 0, sin((i)*stepAngle));
			glVertex3f(r * cos((i)*stepAngle), h - (j + 1) * stepH, r * sin((i)*stepAngle));

		}
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(0, h, 0);
	for (int i = 0; i <= nr; i++)
	{
		glTexCoord2f(0.5 + 0.5 * cos(i * stepAngle), 0.5 + 0.5 * sin(i * stepAngle));
		glVertex3f(r * cos((i)*stepAngle), h, r * sin((i)*stepAngle));
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(0, 0, 0);
	for (int i = 0; i <= nr; i++)
	{
		glTexCoord2f(0.5 + 0.5 * cos(i * stepAngle), 0.5 + 0.5 * sin(i * stepAngle));
		glVertex3f(r * cos((i)*stepAngle), 0, r * sin((i)*stepAngle));
	}
	glEnd();
}

void CGLRenderer::DrawTelescope(float r, float h, float nr, float nh, float alpha, float dHolder, float angleHor, float angleVer, float dHidden, float dVisor)
{


	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
		glRotated(120 * i, 0, 1, 0);
		glRotated(alpha, 1, 0, 0);
		glTranslatef(0, -1.2 * h, 0);
		DrawCyllinder(0.1 * r, 1.2 * h, nr, nh);
		glRotatef(120, 0, 1, 0);
		glPopMatrix();
	}

	glPushMatrix();

	glRotated(angleVer, 0, 1, 0);
	glRotated(angleHor, 0, 0, 1); // Ovde se koristi Z osa za vertikalnu rotaciju

	glPushMatrix();
	glTranslatef(0, -dHolder, 0);
	DrawCyllinder(r, h, nr, nh);
	glTranslatef(0, h, 0);
	glTranslatef(0, -dHidden, 0);
	DrawCyllinder(0.8 * r, 0.8 * h, nr, nh);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -dHolder + dVisor, 0);
	glRotatef(-90, 0, 0, 1); // a ovde se ispravlja vertikalno u odnosu na nju
	glTranslatef(0, r, 0);
	DrawCyllinder(0.1 * r, 0.05 * h, nr, nh);
	glTranslatef(0, 0.05 * h + 0.1 * r, 0);
	glRotatef(90, 0, 0, 1);
	glTranslatef(0, -0.15 * h, 0);
	DrawCyllinder(0.1 * r, 0.3 * h, nr, nh);
	glPopMatrix();

	glPopMatrix();

}

//2019 septembar

void CGLRenderer::DrawRoller(float r, float h, float nr, float nh = 1)
{
	DrawCyllinder(r, h, nr, nh);
}

void CGLRenderer::DrawTwoRollers(float r, float h, float nr, float nh, float p)
{
	float h1, h2;
	h2 = h / (1 + p);
	h1 = h - h2;

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	DrawRoller(r, h2, nr, nh);
	glTranslatef(0, h2, 0);
	glColor3f(1, 1, 1);
	DrawRoller(r, h1, nr, nh);
	glPopMatrix();
}

void CGLRenderer::DrawFigure(float r, float d, float hp, float h1, float p1, float h2, float p2, float h3, float p3, float alpha, float beta, float gama, CString tex)
{
	glPushMatrix();
	DrawRoller(4 * r, hp, 20, 50);

	glTranslatef(0, hp, 0);
	glRotatef(alpha, 0, 1, 0);
	DrawTwoRollers(r, h1, 20, 50, p1);
	glTranslatef(0, h1, 0);

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glTranslatef(0, -d / 2, 0);
	DrawRoller(1.5 * r, d, 20, 50);
	glPopMatrix();

	glRotatef(beta, 1, 0, 0);
	DrawTwoRollers(r, h2, 20, 50, p2);
	glTranslatef(0, h2, 0);

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glTranslatef(0, -d / 2, 0);
	DrawRoller(1.5 * r, d, 20, 50);
	glPopMatrix();

	glRotatef(gama, 1, 0, 0);
	DrawTwoRollers(r, h3, 20, 50, p3);
	glTranslatef(0, h3, 0);

	glPopMatrix();
}

//2019 oktobar

void CGLRenderer::DrawRing(float h, float R1, float R2, int n, CString tex)
{
	const double pi = 3.14159265358979323846;
	float stepAngle = (360. / n) * (pi / 180.);
	float texS = 1. / n;

	//	glColor3f(0.5, 0.5, 0.5);
	/*glBegin(GL_QUADS);
	for (int i = 0; i < n; i++)
	{
		float a1 = i * stepAngle;
		float a2 = (i + 1) * stepAngle;
		float s1 = i * texS;
		float s2 = (i + 1) * texS;

		glNormal3f(cos(a1), 0, sin(a1));
		glTexCoord2f(s1, 0.25);
		glVertex3f(R1 * cos(a1), h / 2, R1 * sin(a1));
		glTexCoord2f(s1, 0);
		glVertex3f(R1 * cos(a1), -h / 2, R1 * sin(a1));
		glNormal3f(cos(a2), 0, sin(a2));
		glTexCoord2f(s2, 0);
		glVertex3f(R1 * cos(a2), -h / 2, R1 * sin(a2));
		glTexCoord2f(s2, 0.25);
		glVertex3f(R1 * cos(a2), h / 2, R1 * sin(a2));


		glNormal3f(0, 1, 0);
		glTexCoord2f(s1, 0.25);
		glVertex3f(R1 * cos(a1), h / 2, R1 * sin(a1));
		glTexCoord2f(s1, 0.5);
		glVertex3f(R2 * cos(a1), h / 2, R2 * sin(a1));
		glTexCoord2f(s2, 0.5);
		glVertex3f(R2 * cos(a2), h / 2, R2 * sin(a2));
		glTexCoord2f(s2, 0.25);
		glVertex3f(R1 * cos(a2), h / 2, R1 * sin(a2));


		glNormal3f(cos(a1), 0, sin(a1));
		glTexCoord2f(s1, 0.5);
		glVertex3f(R2 * cos(a1), h / 2, R2 * sin(a1));
		glTexCoord2f(s1, 0.75);
		glVertex3f(R2 * cos(a1), -h / 2, R2 * sin(a1));
		glNormal3f(cos(a2), 0, sin(a2));
		glTexCoord2f(s2, 0.75);
		glVertex3f(R2 * cos(a2), -h / 2, R2 * sin(a2));
		glTexCoord2f(s2, 0.5);
		glVertex3f(R2 * cos(a2), h / 2, R2 * sin(a2));


		glNormal3f(0, -1, 0);
		glTexCoord2f(s1, 0.75);
		glVertex3f(R1 * cos(a1), -h / 2, R1 * sin(a1));
		glTexCoord2f(s1, 1);
		glVertex3f(R2 * cos(a1), -h / 2, R2 * sin(a1));
		glTexCoord2f(s2, 1);
		glVertex3f(R2 * cos(a2), -h / 2, R2 * sin(a2));
		glTexCoord2f(s2, 0.75);
		glVertex3f(R1 * cos(a2), -h / 2, R1 * sin(a2));

	}
	glEnd();
	*/


	glBegin(GL_TRIANGLE_STRIP);
	for (float A = 0; A <= 2 * pi; A += stepAngle) {
		glVertex3f(R1 * cos(A), h / 2, R1 * sin(A));
		glVertex3f(R2 * cos(A), h / 2, R2 * sin(A));
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (float A = 0; A <= 2 * pi; A += stepAngle) {
		glVertex3f(R1 * cos(A), -h / 2, R1 * sin(A));
		glVertex3f(R2 * cos(A), -h / 2, R2 * sin(A));
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (float A = 0; A <= 2 * pi; A += stepAngle) {
		glVertex3f(R1 * cos(A), h / 2, R1 * sin(A));
		glVertex3f(R1 * cos(A), -h / 2, R1 * sin(A));
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (float A = 0; A <= 2 * pi; A += stepAngle) {
		glVertex3f(R2 * cos(A), h / 2, R2 * sin(A));
		glVertex3f(R2 * cos(A), -h / 2, R2 * sin(A));
	}
	glEnd();
}

void CGLRenderer::DrawTwoRings()
{
	DrawRing(2, 5, 7, 30, CString("marble.bmp"));
	float x = 7 - (7 - 5) / 2;
	glTranslatef(-x, 0, 0);
	glRotatef(90, 1, 0, 0);
	DrawRing(2, 5, 7, 30, CString("marble.bmp"));
}

//Vezba

void CGLRenderer::DrawSphere(float R)
{
	float step = (3.14 / 180) * 10;
	float texStepS = 1. / 18;
	float texStepT = 1. / 36;


	glBegin(GL_QUADS);
	for (int i = -9; i <= 9; i++) {
		float alfa = i * step;
		for (int j = 0; j <= 36; j++) {
			float beta = j * step;

			//glTexCoord2f(0, 0);
			glTexCoord2f(i * texStepS, j * texStepT);
			glNormal3f(cos(alfa) * cos(beta), sin(alfa), cos(alfa) * sin(beta));
			glVertex3f(R * cos(alfa) * cos(beta), R * sin(alfa), R * cos(alfa) * sin(beta));

			//glTexCoord2f(0, 1);
			glTexCoord2f(i * texStepS, (j + 1) * texStepT);
			glNormal3f(cos(alfa) * cos(beta + step), sin(alfa), cos(alfa) * sin(beta + step));
			glVertex3f(R * cos(alfa) * cos(beta + step), R * sin(alfa), R * cos(alfa) * sin(beta + step));

			//glTexCoord2f(1, 1);
			glTexCoord2f((i + 1) * texStepS, (j + 1) * texStepT);
			glNormal3f(cos(alfa + step) * cos(beta + step), sin(alfa + step), cos(alfa + step) * sin(beta + step));
			glVertex3f(R * cos(alfa + step) * cos(beta + step), R * sin(alfa + step), R * cos(alfa + step) * sin(beta + step));

			//glTexCoord2f(1, 0);
			glTexCoord2f((i + 1) * texStepS, j * texStepT);
			glNormal3f(cos(alfa + step) * cos(beta), sin(alfa + step), cos(alfa + step) * sin(beta));
			glVertex3f(R * cos(alfa + step) * cos(beta), R * sin(alfa + step), R * cos(alfa + step) * sin(beta));

		}
	}
	glEnd();

}

//2018 jun

void CGLRenderer::DrawSpiralPart(float R)
{
	/*
	float step = (3.14 / 180) * 10;

	glBegin(GL_LINE_STRIP);
	for (int i = -9; i <= 0; i++) {
		float alfa = i * step;
		for (int j = 0; j <= 36; j++) {
			float beta = j * step;


			glNormal3f(cos(alfa) * cos(beta), sin(alfa), cos(alfa) * sin(beta));
			glVertex3f(R * cos(alfa) * cos(beta), R * sin(alfa), R * cos(alfa) * sin(beta));


			glNormal3f(cos(alfa) * cos(beta + step), sin(alfa), cos(alfa) * sin(beta + step));
			glVertex3f(R * cos(alfa) * cos(beta + step), R * sin(alfa), R * cos(alfa) * sin(beta + step));

			glNormal3f(cos(alfa + step) * cos(beta + step), sin(alfa + step), cos(alfa + step) * sin(beta + step));
			glVertex3f(R * cos(alfa + step) * cos(beta + step), R * sin(alfa + step), R * cos(alfa + step) * sin(beta + step));


			glNormal3f(cos(alfa + step) * cos(beta), sin(alfa + step), cos(alfa + step) * sin(beta));
			glVertex3f(R * cos(alfa + step) * cos(beta), R * sin(alfa + step), R * cos(alfa + step) * sin(beta));

		}
	}
	glEnd();
	*/
	int n = 20;
	float stepA = (3.14 / 2.) / n;
	float stepB = (2 * 3.14) / n;
	for (float A = -(3.14 / 2.); A < 0; A += stepA) {
		glBegin(GL_LINE_STRIP);
		for (float B = 0; B <= 2 * 3.14 + stepB; B += stepB) {
			glNormal3f(cos(A) * cos(B), sin(A), cos(A) * sin(B));
			glVertex3f(R * cos(A) * cos(B), R * sin(A), R * cos(A) * sin(B));

			glNormal3f(cos(A + stepA) * cos(B), sin(A + stepA), cos(A + stepA) * sin(B));
			glVertex3f(R * cos(A + stepA) * cos(B), R * sin(A + stepA), R * cos(A + stepA) * sin(B));
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		for (float B = 0; B <= 2 * 3.14 + stepB; B += stepB) {
			glNormal3f(cos(A) * cos(B), sin(A), cos(A) * sin(B));
			glVertex3f(R * cos(A) * cos(B), R * sin(A), R * cos(A) * sin(B));
		}
		glEnd();
	}

	glBegin(GL_LINE_STRIP);
	for (float B = 0; B <= 2 * 3.14 + stepB; B += stepB) {

		glNormal3f(cos(B), 0, sin(B));
		glVertex3f(R * cos(B), 0, R * sin(B));
	}
	glEnd();

}

void CGLRenderer::DrawSpiral(int n, float dr, float dAlpha, float ds)
{
	/*
	glPushMatrix();

	for (int i = 0; i < n; i++)
	{
		glPushMatrix();
		glRotatef(-90, 0, 0, 1);
		DrawSpiralPart(1);
		glPopMatrix();
		glRotatef(dAlpha, 0, 1, 0);
		glTranslatef(dr, 0, 0);
		glScalef(ds, 1, ds);

	}

	glPopMatrix();
	*/

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);

	for (int i = 0; i < n; i++)
	{
		DrawSpiralPart(1);

		glRotatef(dAlpha, 0, 0, 1);
		glTranslatef(0, dr, 0);
		glScalef(ds, 1, ds);

	}

	glPopMatrix();
}

//2017 apr

void CGLRenderer::DrawFigure2017(float h, float dx, float alpha, float beta, float dt, CString tex[])
{
	glRotated((double)dt * alpha, 0, 1, 0);
	DrawRoller(dx, 0.2 * h, 18);
	glTranslatef(0, -0.2 * h, 0);
	DrawRoller(10 * dx, 0.2 * h, 18);
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glRotated(90.0 * i, 0, 1, 0);
		glTranslatef(3 * dx, -h, 0);
		glRotated(beta * dt, 0, 1, 0);
		DrawRoller(dx, h, 18);
		glTranslatef(0, -0.2 * h, 0);
		DrawRoller(2 * dx, 0.2 * h, 18);
		glPopMatrix();
	}
}

//2017 sept

void CGLRenderer::DrawColumn(float side, float height)
{
	glBegin(GL_QUADS);

	//Gore
	glNormal3f(0, 1, 0);
	glVertex3f(-side / 2, height / 2, -side / 2);
	glVertex3f(side / 2, height / 2, -side / 2);
	glVertex3f(side / 2, height / 2, side / 2);
	glVertex3f(-side / 2, height / 2, side / 2);

	//Dole
	glNormal3f(0, -1, 0);
	glVertex3f(-side / 2, -height / 2, -side / 2);
	glVertex3f(side / 2, -height / 2, -side / 2);
	glVertex3f(side / 2, -height / 2, side / 2);
	glVertex3f(-side / 2, -height / 2, side / 2);

	//Napred
	glNormal3f(0, 0, 1);
	glVertex3f(-side / 2, -height / 2, side / 2);
	glVertex3f(side / 2, -height / 2, side / 2);
	glVertex3f(side / 2, height / 2, side / 2);
	glVertex3f(-side / 2, height / 2, side / 2);

	//Nazad
	glNormal3f(0, 0, -1);
	glVertex3f(-side / 2, -height / 2, -side / 2);
	glVertex3f(side / 2, -height / 2, -side / 2);
	glVertex3f(side / 2, height / 2, -side / 2);
	glVertex3f(-side / 2, height / 2, -side / 2);

	//Levo
	glNormal3f(-1, 0, 0);
	glVertex3f(-side / 2, -height / 2, -side / 2);
	glVertex3f(-side / 2, -height / 2, side / 2);
	glVertex3f(-side / 2, height / 2, side / 2);
	glVertex3f(-side / 2, height / 2, -side / 2);

	//Desno
	glNormal3f(1, 0, 0);
	glVertex3f(side / 2, -height / 2, -side / 2);
	glVertex3f(side / 2, -height / 2, side / 2);
	glVertex3f(side / 2, height / 2, side / 2);
	glVertex3f(side / 2, height / 2, -side / 2);


	glEnd();

}

// Pyramid i Pyramid2 su iste funkcije, samo se normale razlicito postavljaju
// Na prvoj su normale pravilne
// Na drugoj su apriksimirane
// Pogledaj prez normale u 3d

void CGLRenderer::DrawPyramid(float side, float height, int n)
{
	float step = (360. / n) * (3.14 / 180.);
	float R = side / (2 * sin(3.14 / n));
	float L = sqrt(R * R + height * height);
	float nr = R / L;
	float ny = height / L;

	//Baza
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, -1, 0);
	glVertex3f(0, 0, 0);
	for (int i = 0; i <= n; i++)
		glVertex3f(R * cos(step * i), 0, R * sin(step * i));
	glEnd();

	//Omotac
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 1, 0);
	glVertex3f(0, height, 0);
	for (int i = 0; i <= n; i++) {
		glNormal3f(nr * cos(step * i), ny, nr * sin(step * i));
		glVertex3f(R * cos(step * i), 0, R * sin(step * i));
	}
	glEnd();

}

void CGLRenderer::DrawPyramid2(float side, float height, int n)
{
	float step = (360. / n) * (3.14 / 180.);
	float R = side / (2 * sin(3.14 / n));
	float L = sqrt(R * R + height * height);
	float nr = R / L;
	float ny = height / L;

	//Baza
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, -1, 0);
	glVertex3f(0, 0, 0);
	for (int i = 0; i <= n; i++)
		glVertex3f(R * cos(step * i), 0, R * sin(step * i));
	glEnd();

	//Omotac
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 1, 0);
	glVertex3f(0, height, 0);
	for (int i = 0; i <= n; i++) {
		glNormal3f(cos(step * i), 0, sin(step * i));
		glVertex3f(R * cos(step * i), 0, R * sin(step * i));
	}
	glEnd();
}

void CGLRenderer::Draw2Pyramid(float side, float height)
{
	DrawPyramid(side, height, 6);
	DrawPyramid(side, -height, 6);
}

void CGLRenderer::DrawFigureSept2017(float aS, float hS, float aR, float size, float height, float ratio, float angle)
{
	glPushMatrix();
	//Stub se crta od sredine, podignemo na tu visinu
	glTranslatef(0, hS / 2, 0);

	glPushMatrix();
	// Pomerimo u stranu, za pola visine, ali vratimo malo da bude ko na slici
	glTranslatef(hS / 2 - aS / 2, 0, 0);
	DrawColumn(aS, hS);
	glPopMatrix();
	//Isto i za drugi smer
	glPushMatrix();
	glTranslatef(-hS / 2 + aS / 2, 0, 0);
	DrawColumn(aS, hS);
	glPopMatrix();

	//Gornja greda
	//Dizemo gore, rotitamo po z osi
	glTranslatef(0, hS / 2, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	DrawColumn(aS, hS);
	glPopMatrix();

	glTranslatef(0, -aS / 2, 0);
	//U tekstu je offset, misli se na ratio
	//Postavimo na poziciju na kojoj se nalazi telo koje rotira
	glTranslatef(-hS / 2 + aS / 2 + ratio, 0, 0);

	//Ova osnova pretpostavimo da je prizma
	glTranslatef(0, -aS / 2, 0);
	glRotatef(angle, 0, 1, 0);
	//Crtamo je
	DrawColumn(aR, aS);
	glTranslatef(0, -aS / 2, 0);

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, -2 * height, 0);
	glEnd();

	//Spustimo se na kraj konopca
	glTranslatef(0, -2 * height, 0);
	//Pozicioniramo se za crtanje piramide
	glTranslatef(0, -height, 0);
	Draw2Pyramid(size, height);

	glPopMatrix();
}

//2018 dec

void CGLRenderer::DrawBox(float a, float b, float c)
{
	//a sirina,b duzina,c visina
	glBegin(GL_QUADS);

	//Gore
	glNormal3f(0, 1, 0);
	glVertex3f(-a / 2, c / 2, -b / 2);
	glVertex3f(a / 2, c / 2, -b / 2);
	glVertex3f(a / 2, c / 2, b / 2);
	glVertex3f(-a / 2, c / 2, b / 2);

	//Dole
	glNormal3f(0, -1, 0);
	glVertex3f(-a / 2, -c / 2, -b / 2);
	glVertex3f(a / 2, -c / 2, -b / 2);
	glVertex3f(a / 2, -c / 2, b / 2);
	glVertex3f(-a / 2, -c / 2, b / 2);

	//Napred
	glNormal3f(0, 0, 1);
	glVertex3f(-a / 2, -c / 2, b / 2);
	glVertex3f(a / 2, -c / 2, b / 2);
	glVertex3f(a / 2, c / 2, b / 2);
	glVertex3f(-a / 2, c / 2, b / 2);

	//Nazad
	glNormal3f(0, 0, -1);
	glVertex3f(-a / 2, -c / 2, -b / 2);
	glVertex3f(a / 2, -c / 2, -b / 2);
	glVertex3f(a / 2, c / 2, -b / 2);
	glVertex3f(-a / 2, c / 2, -b / 2);

	//Levo
	glNormal3f(-1, 0, 0);
	glVertex3f(-a / 2, -c / 2, -b / 2);
	glVertex3f(-a / 2, -c / 2, b / 2);
	glVertex3f(-a / 2, c / 2, b / 2);
	glVertex3f(-a / 2, c / 2, -b / 2);

	//Desno
	glNormal3f(1, 0, 0);
	glVertex3f(a / 2, -c / 2, -b / 2);
	glVertex3f(a / 2, -c / 2, b / 2);
	glVertex3f(a / 2, c / 2, b / 2);
	glVertex3f(a / 2, c / 2, -b / 2);


	glEnd();


}

void CGLRenderer::DrawStub(float r, float h, int steps)
{
	//Poziva se cilindar koji crta i baze
	//Ukupna visina h + 0.5*r + 2*0.3*r

	glPushMatrix();
	DrawCilindar(r, h, steps);
	glTranslatef(0, h / 2 + 0.25 * r, 0);
	DrawBox(2.5 * r, 2.5 * r, 0.5 * r);
	glTranslatef(0, -h - 0.25 * r, 0);

	glTranslatef(0, -0.15 * r, 0);
	DrawBox(3 * r, 3 * r, 0.3 * r);
	glTranslatef(0, -0.15 * r, 0);
	DrawBox(4 * r, 4 * r, 0.3 * r);
	glPopMatrix();

}

void CGLRenderer::DrawCilindar(float r, float h, int steps)
{
	glPushMatrix();
	glTranslatef(0, -h / 2, 0);
	DrawCyllinder(r, h, steps);
	glPopMatrix();
}

void CGLRenderer::DrawTample()
{
	/*
	float r = 0.5;
	glColor3f(0, 0, 0);

	//Stubovi
	glPushMatrix();
	//??? zasto ta pozicija? ???
	glTranslatef(-10.5, 0, 4.5);

	glTranslatef(0, 0, 3);
	for (int i = 0; i < 4; i++) {
		glTranslatef(0, 0, -3);
		DrawStub(0.5, 8, 18);
	}
	for (int i = 0; i < 7; i++) {
		glTranslatef(3, 0, 0);
		DrawStub(0.5, 8, 18);
	}
	for (int i = 0; i < 3; i++) {
		glTranslatef(0, 0, 3);
		DrawStub(0.5, 8, 18);
	}
	for (int i = 0; i < 6; i++) {
		glTranslatef(-3, 0, 0);
		DrawStub(0.5, 8, 18);
	}
	glPopMatrix();


	//Postolje
	glPushMatrix();
	//Spustimo se na dole
	glTranslatef(0, -4 - 0.6 * r, 0);
	glTranslatef(0, -0.25, 0);
	DrawBox(24, 12, 0.5);
	glTranslatef(0, -0.25, 0);
	glTranslatef(0, -0.75 * 0.5, 0);
	DrawBox(26, 14, 0.75);
	glPopMatrix();

	//Krov
	glPushMatrix();
	glTranslatef(0, 4 + 0.5 * r, 0);
	//Ploca koju drze stubovi
	glTranslatef(0, 0.15, 0);
	DrawBox(24, 12, 0.3);

	//Pomeramo 4 u visinu i +- 4 u strane rotirano za +- 60stepeni
	glTranslatef(0, 1.5, 0);
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glRotatef(30, 1, 0, 0);
	DrawBox(24, 8, 0.2);
	glPopMatrix();

	glTranslatef(0, 0, -3.5);
	glRotatef(-30, 1, 0, 0);
	DrawBox(24, 8, 0.2);

	glPopMatrix();
	*/



	glPushMatrix();
	glTranslatef(-12, 0, -6);
	glTranslatef(0.5, 0, 1);
	glPushMatrix();
	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		DrawStub(0.5, 8, 20);
		glTranslatef(0, 0, 9);
		DrawStub(0.5, 8, 20);
		glPopMatrix();
		glTranslatef(3, 0, 0);
	}
	glPopMatrix();
	glTranslatef(0, 0, 3);
	glPushMatrix();
	for (int i = 0; i < 2; i++) {
		glPushMatrix();
		DrawStub(0.5, 8, 20);
		glTranslatef(21, 0, 0);
		DrawStub(0.5, 8, 20);
		glPopMatrix();
		glTranslatef(0, 0, 3);
	}
	glPopMatrix();
	glPopMatrix();

	glColor3f(0.8, 0, 0);
	glPushMatrix();
	glTranslatef(0, -4 - 0.3 - 0.25, 0);
	DrawBox(24, 12, 0.5);
	glTranslatef(0, -0.75 / 2 - 0.25, 0);
	DrawBox(26, 14, 0.75);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(0, 4 + 0.25 * 0.5 + 0.15, 0);
	DrawBox(24, 12, 0.3);

	glColor3f(0, 0, .5);
	
	glTranslatef(0, 0, 6);
	glPushMatrix();
	glRotatef(30, 1, 0, 0);
	glTranslatef(0, 0, -4);
	DrawBox(24, 8, 0.5);
	glPopMatrix();
	glTranslatef(0, 0, -12);

	glRotatef(-30, 1, 0, 0);
	glTranslatef(0, 0, 4);
	DrawBox(24, 8, 0.5);
	
	glPopMatrix();

}

//2018 Jan

void CGLRenderer::DrawSide(float x, float y, int nPartX, int nPartY, int nTexX, int nTexY)
{
	float texStepS = (float)nTexX / (float)nPartX;
	float texStepT = (float)nTexY / (float)nPartY;
	float stepX = x / (float)nPartX;
	float stepY = y / (float)nPartY;
	glBindTexture(GL_TEXTURE_2D, tex);
	glPushMatrix();
	glTranslatef(-x / 2, -y / 2, 0);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);

	for (int i = 0; i < nPartX; i++) {
		for (int j = 0; j < nPartY; j++) {

			glTexCoord2f(texStepS * i, (float)nTexY - texStepT * j);
			glVertex3f(i * stepX, j * stepY, 0);

			glTexCoord2f(texStepS * (i + 1), (float)nTexY - texStepT * j);
			glVertex3f((i + 1) * stepX, j * stepY, 0);

			glTexCoord2f(texStepS * (i + 1), (float)nTexY - texStepT * (j + 1));
			glVertex3f((i + 1) * stepX, (j + 1) * stepY, 0);

			glTexCoord2f(texStepS * i, (float)nTexY - texStepT * (j + 1));
			glVertex3f(i * stepX, (j + 1) * stepY, 0);

		}
	}

	glEnd();

	glPopMatrix();
}

void CGLRenderer::DrawBox2018(float x, float y, float z, int nPartX, int nPartY, int nPartZ, int nTexX, int nTexY, int nTexZ)
{
	glPushMatrix();
	glTranslatef(0, 0, z / 2);
	DrawSide(x, y, nPartX, nPartY, nTexX, nTexY);
	glTranslatef(0, 0, -z);
	glRotatef(180, 0, 1, 0);
	DrawSide(x, y, nPartX, nPartY, nTexX, nTexY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0, 0, x / 2);
	DrawSide(z, y, nPartZ, nPartY, nTexZ, nTexY);
	glTranslatef(0, 0, -x);
	glRotatef(180, 0, 1, 0);
	DrawSide(z, y, nPartZ, nPartY, nTexZ, nTexY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, y / 2);
	DrawSide(x, z, nPartX, nPartZ, nTexX, nTexZ);
	glTranslatef(0, 0, -y);
	glRotatef(180, 0, 1, 0);
	DrawSide(x, z, nPartX, nPartZ, nTexX, nTexZ);
	glPopMatrix();


}

void CGLRenderer::DrawBasket(float w, float h, float d)
{
	glPushMatrix();
	glTranslatef(0, -h / 2 - d / 2, 0);
	DrawBox2018(w, d, w, 10, 1, 10, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(w / 2 - d / 2, 0, 0);
	DrawBox2018(d, h, w, 1, 1, 10, 1, 1, 1);
	glTranslatef(-w + d, 0, 0);
	DrawBox2018(d, h, w, 1, 1, 10, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -w / 2 + d / 2);
	DrawBox2018(w - 2 * d, h, d, 10, 1, 1, 1, 1, 1);
	glTranslatef(0, 0, w - d);
	DrawBox2018(w - 2 * d, h, d, 10, 1, 1, 1, 1, 1);
	glPopMatrix();

}

void CGLRenderer::DrawFigureJan2018(float w, float h, float d, float r, float alpha, float beta, float gama)
{
	glPushMatrix();
	//Cilindar se crta u 0,0,0
	DrawCilindar(r, 2 * w, 18);
	//Dizemo za pola visine cilindra i pola visine stuba
	glTranslatef(0, w + d / 2, 0);
	//Rotacija oko y
	glRotatef(alpha, 0, 1, 0);
	DrawBox2018(w, d, w, 20, 20, 20, 20, 20, 20);
	//Dizemo za pola visine stuba + pola visine kocke
	glTranslatef(0, d / 2 + 0.75 * w, 0);
	DrawBox2018(1.5 * w, 1.5 * w, 1.5 * w, 1, 1, 1, 1, 1, 1);
	//Rotacija oko z ose, posto na slici ugao raste na gore, okrenemo za 180,pa oduzmemo taj beta ugao da bi se ispravilo
	glRotatef(180 - beta, 0, 0, 1);
	// Po y osi, posto je okrenuta krecemo se za polovinu kocke koja je ostala i + pola stuba
	glTranslatef(0, d / 2 + 0.75 * w, 0);
	DrawBox2018(w, d, w, 20, 20, 20, 20, 20, 20);
	//Opet isto 
	glTranslatef(0, d / 2 + 0.75 * w, 0);
	DrawBox2018(1.5 * w, 1.5 * w, 1.5 * w, 1, 1, 1, 1, 1, 1);
	//Sad ispravljamo opet uglom gama u odnosu na predhodno
	glRotatef(-gama, 0, 0, 1);
	//Isto
	glTranslatef(0, d / 2 + 0.75 * w, 0);
	DrawBox2018(w, d, w, 20, 20, 20, 20, 20, 20);
	//pomeramo sistem na kraj 3. stuba
	glTranslatef(0, d / 2, 0);
	//Vracamo rotaciju u prvobitnu poziciju poziciju, ali samo po beta i gama
	glRotatef(gama, 0, 0, 1);
	glRotatef(-180 + beta, 0, 0, 1);
	// i pomeramo u visinu za pola korpe
	glTranslatef(0, 0.25 * h, 0);
	//Crta se korpa
	DrawBasket(6 * w, 0.5 * h, 1);
	glPopMatrix();
}

//2019 apr

void CGLRenderer::DrawPaperPlane(float h)
{
	glPushMatrix();

	glRotatef(-90, 1, 0, 0);
	glTranslatef(-h / 2, -0.75 * h, 0);

	DrawPaperPlaneA(h);
	DrawPaperPlaneD(h);

	DrawPaperPlaneB(h);
	DrawPaperPlaneC(h);

	glPopMatrix();
}

void CGLRenderer::DrawPaperPlaneA(float h)
{
	float a1 = atan2(-h, h / 2);
	float a2 = atan2(-h, -h / 2);

	float a = abs(a2 - a1);
	a /= 4;
	a *= 180. / 3.14;

	glPushMatrix();

	glTranslatef(h / 2, h, 0);
	glRotatef(a, 0, 0, 1);
	glTranslatef(-h / 2, -h, 0);

	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);

	glTexCoord2f(0.5, 0);
	glVertex3f(h / 2, h, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.25, 1);
	glVertex3f(h / 4, 0, 0);

	glEnd();


	glPopMatrix();

}

void CGLRenderer::DrawPaperPlaneB(float h)
{
	glPushMatrix();

	glTranslatef(h / 2, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(-h / 2, 0, 0);

	glTranslatef(0.25 * h, 0, 0);
	glRotatef(-2, 0, 1, 0);
	glTranslatef(-0.25 * h, 0, 0);


	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, -1);

	glTexCoord2f(0.5, 0);
	glVertex3f(h / 2, h, 0);

	glTexCoord2f(0.25, 1);
	glVertex3f(0.25 * h, 0, 0);

	glTexCoord2f(0.5, 1);
	glVertex3f(0.5 * h, 0, 0);

	glEnd();


	glPopMatrix();

}

void CGLRenderer::DrawPaperPlaneC(float h)
{
	glPushMatrix();

	glTranslatef(h / 2, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-h / 2, 0, 0);

	glTranslatef(0.75 * h, 0, 0);
	glRotatef(2, 0, 1, 0);
	glTranslatef(-0.75 * h, 0, 0);



	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, -1);

	glTexCoord2f(0.5, 0);
	glVertex3f(h / 2, h, 0);

	glTexCoord2f(0.5, 1);
	glVertex3f(0.5 * h, 0, 0);

	glTexCoord2f(0.75, 1);
	glVertex3f(0.75 * h, 0, 0);

	glEnd();


	glPopMatrix();
}

void CGLRenderer::DrawPaperPlaneD(float h)
{
	float a1 = atan2(-h, h / 2);
	float a2 = atan2(-h, -h / 2);

	float a = abs(a2 - a1);
	a /= 4;
	a *= 180. / 3.14;

	glPushMatrix();

	glTranslatef(h / 2, h, 0);
	glRotatef(-a, 0, 0, 1);
	glTranslatef(-h / 2, -h, 0);

	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);

	glTexCoord2f(0.5, 0);
	glVertex3f(h / 2, h, 0);

	glTexCoord2f(0.75, 1);
	glVertex3f(0.75 * h, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(h, 0, 0);

	glEnd();


	glPopMatrix();

}

void CGLRenderer::DrawVase(float size)
{
	//VIDI ISPIT
	//Ideja: obilazim krug, i crtam quads za svaku tacku
	//Tacke redom (na gore)
	//(x,y) 
	/*
	0.85, 0
	0.75, 0.1
	0.9,0.3
	1,0.43
	0.9,0.75
	0.75,0.8
	0.75,0.9
	0.8,1
	*/
	float stepAngle = (360 / 20) * (3.14 / 180.);
	float r = size / 5;
	float texStepS = 1. / 20;



	glBegin(GL_QUADS);
	for (int i = 0; i < 20; i++) {
		float c1 = cos(stepAngle * (float)i);
		float s1 = sin(stepAngle * (float)i);
		float c2 = cos(stepAngle * (float)(i + 1));
		float s2 = sin(stepAngle * (float)(i + 1));

		glTexCoord2f(texStepS * i, 0);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 0.85 * c1, 0, r * 0.85 * s1);

		glTexCoord2f(texStepS * (i + 1), 0);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 0.85 * c2, 0, r * 0.85 * s2);

		glTexCoord2f(texStepS * (i + 1), 1. - 0.1);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 0.75 * c2, size * 0.1, r * 0.75 * s2);

		glTexCoord2f(texStepS * i, 1. - 0.1);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 0.75 * c1, size * 0.1, r * 0.75 * s1);


		glTexCoord2f(texStepS * i, 1 - 0.1);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 0.75 * c1, size * 0.1, r * 0.75 * s1);

		glTexCoord2f(texStepS * (i + 1), 1 - 0.1);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 0.75 * c2, size * 0.1, r * 0.75 * s2);

		glTexCoord2f(texStepS * (i + 1), 1 - 0.3);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 0.9 * c2, size * 0.3, r * 0.9 * s2);

		glTexCoord2f(texStepS * i, 1 - 0.3);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 0.9 * c1, size * 0.3, r * 0.9 * s1);

		glTexCoord2f(texStepS * i, 1 - 0.3);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 0.9 * c1, size * 0.3, r * 0.9 * s1);

		glTexCoord2f(texStepS * (i + 1), 1 - 0.3);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 0.9 * c2, size * 0.3, r * 0.9 * s2);

		glTexCoord2f(texStepS * (i + 1), 1 - 0.43);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 1 * c2, size * 0.43, r * 1 * s2);

		glTexCoord2f(texStepS * i, 1 - 0.43);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 1 * c1, size * 0.43, r * 1 * s1);


		glTexCoord2f(texStepS * i, 1 - 0.43);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 1 * c1, size * 0.43, r * 1 * s1);

		glTexCoord2f(texStepS * (i + 1), 1 - 0.43);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 1 * c2, size * 0.43, r * 1 * s2);

		glTexCoord2f(texStepS * (i + 1), 1 - 0.75);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 0.9 * c2, size * 0.75, r * 0.9 * s2);

		glTexCoord2f(texStepS * i, 1 - 0.75);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 0.9 * c1, size * 0.75, r * 0.9 * s1);


		glTexCoord2f(texStepS * i, 1 - 0.75);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 0.9 * c1, size * 0.75, r * 0.9 * s1);

		glTexCoord2f(texStepS * (i + 1), 1 - 0.75);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 0.9 * c2, size * 0.75, r * 0.9 * s2);

		glTexCoord2f(texStepS * (i + 1), 1 - 0.8);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 0.75 * c2, size * 0.8, r * 0.75 * s2);

		glTexCoord2f(texStepS * i, 1 - 0.8);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 0.75 * c1, size * 0.8, r * 0.75 * s1);


		glTexCoord2f(texStepS * i, 1 - 0.8);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 0.75 * c1, size * 0.8, r * 0.75 * s1);

		glTexCoord2f(texStepS * (i + 1), 1 - 0.8);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 0.75 * c2, size * 0.8, r * 0.75 * s2);

		glTexCoord2f(texStepS * (i + 1), 1 - 0.9);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 0.8 * c2, size * 0.9, r * 0.75 * s2);

		glTexCoord2f(texStepS * i, 1 - 0.9);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 0.8 * c1, size * 0.9, r * 0.8 * s1);


		glTexCoord2f(texStepS * i, 1 - 0.9);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 0.8 * c1, size * 0.9, r * 0.8 * s1);

		glTexCoord2f(texStepS * (i + 1), 1 - 0.9);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 0.8 * c2, size * 0.9, r * 0.8 * s2);

		glTexCoord2f(texStepS * (i + 1), 1 - 1);
		glNormal3f(c2, 0, s2);
		glVertex3f(r * 1 * c2, size * 1, r * 1 * s2);

		glTexCoord2f(texStepS * i, 1 - 1);
		glNormal3f(c1, 0, s1);
		glVertex3f(r * 1 * c1, size * 1, r * 1 * s1);


	}
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (int i = 0; i <= 20; i++) {
		float c1 = cos(stepAngle * (float)i);
		float s1 = sin(stepAngle * (float)i);
		glVertex3f(r * 0.85 * c1, 0, r * 0.85 * s1);
	}

	glEnd();
}

void CGLRenderer::DrawCone(float r, float h)
{
	float step = (2 * 3.14) / 18;
	//Postavi materijal
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, -1, 0);
	glVertex3f(0, 0, 0);
	for (int i = 0; i <= 18; i++)
		glVertex3f(r * cos(step * (float)i), 0, r * sin(step * (float)i));
	glEnd();

	float L = sqrt((float)r * (float)r + (float)h * (float)h);
	float nr = h / L;
	float ny = r / L;

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 1, 0);
	glVertex3f(0, h, 0);
	for (int i = 0; i <= 18; i++)
	{
		glNormal3f(nr * cos(step * (float)i), ny, nr * sin(step * (float)i));
		glVertex3f(r * cos(step * (float)i), 0, r * sin(step * (float)i));
	}
	glEnd();
}

void CGLRenderer::DrawFigure2013()
{
	float h = 2.0, r = 1.0;
	glPushMatrix();

	glTranslatef(0, -h, 0);
	DrawCone(r, h);
	glRotatef(180, 1, 0, 0);
	DrawCone(r, h);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glPushMatrix();
	glRotatef(-60, 0, 0, 1);
	glTranslatef(0, h, 0);
	DrawCone(r, h);
	glRotatef(180, 0, 0, 1);
	DrawCone(r, h);
	glPopMatrix();
	glRotatef(60, 0, 0, 1);
	glTranslatef(0, h, 0);
	DrawCone(r, h);
	glRotatef(180, 0, 0, 1);
	DrawCone(r, h);
	glPopMatrix();
}

void CGLRenderer::DrawTrapez(float a, float b, float h, float H)
{
	float x = (a - b) / 2;
	float L = sqrt(x * x + h * h);
	float nx = h / L;
	float ny = x / L;

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-b / 2, h / 2, -H / 2);
	glVertex3f(b / 2, h / 2, -H / 2);
	glVertex3f(b / 2, h / 2, H / 2);
	glVertex3f(-b / 2, h / 2, H / 2);

	glNormal3f(0, -1, 0);
	glVertex3f(-a / 2, -h / 2, -H / 2);
	glVertex3f(a / 2, -h / 2, -H / 2);
	glVertex3f(a / 2, -h / 2, H / 2);
	glVertex3f(-a / 2, -h / 2, H / 2);

	glNormal3f(0, 0, -1);
	glVertex3f(-b / 2, h / 2, -H / 2);
	glVertex3f(b / 2, h / 2, -H / 2);
	glVertex3f(a / 2, -h / 2, -H / 2);
	glVertex3f(-a / 2, -h / 2, -H / 2);

	glNormal3f(0, 0, 1);
	glVertex3f(-b / 2, h / 2, H / 2);
	glVertex3f(b / 2, h / 2, H / 2);
	glVertex3f(a / 2, -h / 2, H / 2);
	glVertex3f(-a / 2, -h / 2, H / 2);

	glNormal3f(nx, ny, 0);
	glVertex3f(b / 2, h / 2, -H / 2);
	glVertex3f(b / 2, h / 2, H / 2);
	glVertex3f(a / 2, -h / 2, H / 2);
	glVertex3f(a / 2, -h / 2, -H / 2);

	glNormal3f(-nx, ny, 0);
	glVertex3f(-b / 2, h / 2, -H / 2);
	glVertex3f(-b / 2, h / 2, H / 2);
	glVertex3f(-a / 2, -h / 2, H / 2);
	glVertex3f(-a / 2, -h / 2, -H / 2);

	glEnd();
}

void CGLRenderer::DrawTrapezRing(float a, float b, float h, float H)
{
	float x = (a - b) / 2.;
	float d = sqrt((a - x) * (a - x) + h * h);


	glPushMatrix();

	for (int i = 0; i < 6; i++) {
		glPushMatrix();
		glTranslatef(0, -d + h / 2, 0);
		DrawTrapez(a, b, h, H);
		glPopMatrix();
		glRotatef(60, 0, 0, 1);
	}

	glPopMatrix();

}

void CGLRenderer::DrawTrapezFigure(float a, float b, float h, float H)
{
	float x = (a - b) / 2.;
	float d = sqrt((a - x) * (a - x) + h * h);
	glPushMatrix();
	float nizMaterial1[4] = { 0.75, 0.75, 0.75,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, nizMaterial1);
	DrawTrapezRing(a, b, h, H);

	float nizR[6] = { 1,1,0,0,0,1 };
	float nizG[6] = { 0,0,0,1,1,1 };
	float nizB[6] = { 0,1,1,1,0,0 };

	for (int i = 0; i < 6; i++) {
		glPushMatrix();
		glTranslatef(0, 2 * d, 0);
		float nizMaterial[4] = { nizR[i], nizG[i], nizB[i],1 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, nizMaterial);
		DrawTrapezRing(a, b, h, H);
		glPopMatrix();
		glRotatef(-60, 0, 0, 1);
	}
	glPopMatrix();
}

void CGLRenderer::DrawPatch(float r, float LonMin, float LonMax, float LatMin, float LatMax, float dLon, float dLat)
{

	const float toRad = 3.14 / 180.0;
	LonMin *= toRad;
	LonMax *= toRad;
	LatMin *= toRad;
	LatMax *= toRad;

	float LatStep = (LatMax - LatMin) / dLat;
	float LonStep = (LonMax - LonMin) / dLon;
	glColor3f(1, 0, 0);


	for (double a = LatMin; a <= LatMax; a += LatStep) {
		glBegin(GL_TRIANGLE_STRIP);
		for (double b = LonMin; b <= LonMax; b += LonStep) {
			glNormal3f(cos(a) * cos(b), sin(a), cos(a) * sin(b));
			glVertex3f(r * cos(a) * cos(b), r * sin(a), r * cos(a) * sin(b));

			glNormal3f(cos(a + LatStep) * cos(b), sin(a + LatStep), cos(a + LatStep) * sin(b));
			glVertex3f(r * cos(a + LatStep) * cos(b), r * sin(a + LatStep), r * cos(a + LatStep) * sin(b));
		}
		glEnd();
	}

}

void CGLRenderer::DrawGlobe(float r)
{
	glPushMatrix();
	for (int i = 0; i < 8; i++) {
		DrawPatch(r, -45, 45, -45, 45, 5, 5);
		glRotatef(45, 0, 1, 0);
	}
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	DrawPatch(r, -45, 45, -45, 45, 5, 5);
	glRotatef(-45, 0, 1, 0);
	DrawPatch(r, -45, 45, -45, 45, 5, 5);
	glRotatef(45, 0, 1, 0);
	glRotatef(180, 0, 0, 1);
	DrawPatch(r, -45, 45, -45, 45, 5, 5);
	glRotatef(-45, 0, 1, 0);
	DrawPatch(r, -45, 45, -45, 45, 5, 5);

	glPopMatrix();

}

void CGLRenderer::DrawFigure2020(float r, float h, int n)
{
	glPushMatrix();
	float step = 360 / (2 * n);
	DrawCone(2 * r, 2 * h);
	glTranslatef(0, 2 * h, 0);
	glRotatef(90 + step / 2, 0, 0, 1);

	for (int i = 0; i < 2 * n; i++) {
		glRotatef(-step, 0, 0, 1);
		DrawCone(r, h);
		glTranslatef(0, h, 0);
	}
	glPopMatrix();
}

void CGLRenderer::DrawCubeVector(float a)
{

	float v[24];
	float i[24];
	float n[24];

	v[0] = -a / 2; v[1] = -a / 2; v[2] = -a / 2;	//0
	v[3] = a / 2; v[4] = -a / 2; v[5] = -a / 2;		//1
	v[6] = a / 2; v[7] = a / 2; v[8] = -a / 2;		//2
	v[9] = -a / 2; v[10] = a / 2; v[11] = -a / 2;	//3
	v[12] = -a / 2; v[13] = a / 2; v[14] = a / 2;	//4
	v[15] = -a / 2; v[16] = -a / 2; v[17] = a / 2;	//5
	v[18] = a / 2; v[19] = -a / 2; v[20] = a / 2;	//6
	v[21] = a / 2; v[22] = a / 2; v[23] = a / 2;	//7


	i[0] = 5; i[1] = 4; i[2] = 7; i[3] = 6;			//q0
	i[4] = 6; i[5] = 7; i[6] = 2; i[7] = 1;			//q1
	i[8] = 0; i[9] = 3; i[10] = 2; i[11] = 1;		//q2
	i[12] = 5; i[13] = 4; i[14] = 3; i[15] = 0;		//q3
	i[16] = 4; i[17] = 3; i[18] = 2; i[19] = 7;		//q4
	i[20] = 5; i[21] = 6; i[22] = 1; i[23] = 0;		//q5


	glVertexPointer(3, GL_FLOAT, 0, v);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, i);

	glDisableClientState(GL_VERTEX_ARRAY);

}

void CGLRenderer::DrawTorusVector(float R, float r)
{
	float* vertex = new float[36 * 36 * 3];
	float* normal = new float[36 * 36 * 3];
	float* tex = new float[36 * 36 * 2];
	int* index = new int[36 * 36 * 4];

	float step = (2. * 3.14) / 36.;
	float texStep = 1. / 36.;

	for (int i = 0; i < 36; i++) {
		float alfa = step * i;
		for (int j = 0; j < 36; j++) {
			float beta = step * j;

			tex[i * 36 + j] = i * texStep;
			tex[i * 36 + j * 2 + 1] = j * texStep;

			normal[i * 36 + j * 3] = cos(beta) * cos(alfa);
			normal[i * 36 + j * 3 + 1] = sin(beta) * cos(alfa);
			normal[i * 36 + j * 3 + 2] = sin(alfa);

			vertex[i * 36 + j * 3] = (R + r * cos(alfa)) * cos(beta);
			vertex[i * 36 + j * 3 + 1] = (R + r * cos(alfa)) * sin(beta);
			vertex[i * 36 + j * 3 + 2] = r * sin(alfa);
		}
	}


	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 36; j++) {
			index[i * 36 + j * 4] = (i * 36 + j * 36) % ((i + 1) * 36);
			index[i * 36 + j * 4 + 1] = (i * 36 + j * 36 + 1) % ((i + 1) * 36);
			index[i * 36 + j * 4 + 2] = ((i + 1) * 36 + j * 36 + 1) % ((i + 2) * 36);
			index[i * 36 + j * 4 + 3] = ((i + 1) * 36 + j * 36) % ((i + 2) * 36);
		}
	}

	glVertexPointer(3, GL_FLOAT, 0, vertex);
	//	glNormalPointer(GL_FLOAT, 0, normal);
	//	glTexCoordPointer(2, GL_FLOAT, 0, tex);

	glEnableClientState(GL_VERTEX_ARRAY);
	//	glEnableClientState(GL_NORMAL_ARRAY);
	//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDrawElements(GL_QUADS, 36 * 36 * 4, GL_UNSIGNED_BYTE, index);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	delete[] vertex;
	delete[] tex;
	delete[] normal;
	delete[] index;


}

void CGLRenderer::DrawWheel()
{
	float R1 = 4;
	float R2 = 3;
	float d = 1;
	int bb = 10;

	glPushMatrix();
	glRotatef(90,1,0,0);
	DrawRing(d, R1, R2, 360, NULL);
	glPopMatrix();
	float step = 360. / bb;
	const float toRad = 3.14 / 180.0;

	for (int i = 0; i < bb; i++) {
		glPushMatrix();

		glTranslatef(cos(i * step * toRad) * R2 * 0.5, sin(i * step * toRad) * R2 * 0.5, 0);
		glRotatef(i * step, 0, 0, 1);
		DrawBox(R2, d * 0.66, d * 0.66);

		glPopMatrix();
	}

}

