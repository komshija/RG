#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#pragma comment(lib, "GL\\glut32.lib")
#pragma comment(lib,"GL\\GLU32.lib")

CGLRenderer::CGLRenderer(void)
{
	this->angle_v = 0;
	this->angle_h = 0;
	this->angle_cx = 0;
	this->angle_cy = 0;
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
	glClearColor(0.5, 0.75, 1, 0.0);
	glEnable(GL_DEPTH_TEST);

	//---------------------------------

	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(angle_h, .0, 0, 1.0);
	glRotatef(angle_v, 0, 1.0, .0);

	DrawAxis();
	DrawGrid();

	glPushMatrix();
	//Posto je prvobitno sve nacrtano u vecoj razmeri, samo je skalirano na polovinu
	glScalef(0.5, 0.5, 0.5);
	DrawPot();
	DrawFigure();
	glPopMatrix();

	glFlush();
	//---------------------------------
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, (double)w / (double)h, 1, 100);
	gluLookAt(3.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 1.0, 0.0);
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

void CGLRenderer::DrawPrism(float radius, float height, int sides)
{

	float t_height = height / 2.0;

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	float step = (2 * C_PI) / sides;
	//Baza 1
	glBegin(GL_POLYGON);
	for (int i = 0; i < sides; i++)
		glVertex3f(get_x(radius, i * step), t_height, get_y(radius, i * step));
	glEnd();

	//Baza 2
	glBegin(GL_POLYGON);
	for (int i = 0; i < sides; i++)
		glVertex3f(get_x(radius, i * step), -t_height, get_y(radius, i * step));
	glEnd();

	//Omotac
	
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < sides; i++) {
		glVertex3f(get_x(radius, i * step), -t_height, get_y(radius, i * step));
		glVertex3f(get_x(radius, (i + 1) * step), -t_height, get_y(radius, (i + 1) * step));
		glVertex3f(get_x(radius, i * step), t_height, get_y(radius, i * step));
		glVertex3f(get_x(radius, (i + 1) * step), t_height, get_y(radius, (i + 1) * step));
	}
	glEnd();
	
	glPopMatrix();
}

void CGLRenderer::DrawCone(float radius, float height, int sides)
{
	float step = (2 * C_PI) / sides;
	float t_height = height / 2.0;

	//Baza
	glBegin(GL_POLYGON);
	for (int i = 0; i < sides; i++)
		glVertex3f(get_x(radius, i * step), -t_height, get_y(radius, i * step));
	glEnd();

	//Omotac
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < sides; i++)
	{
		glVertex3f(get_x(radius, i * step), -t_height, get_y(radius, i * step));
		glVertex3f(0, t_height, 0);
		glVertex3f(get_x(radius, (i + 1) * step), -t_height, get_y(radius, (i + 1) * step));
	}
	glEnd();

}

void CGLRenderer::DrawRoller(float radius, float height, int sides)
{
	float step = (2 * C_PI) / sides;
	float t_height = height / 2.0;

	//Baza 1
	glBegin(GL_POLYGON);
	for (int i = 0; i < sides; i++)
		glVertex3f(get_x(radius, i * step), t_height, get_y(radius, i * step));
	glEnd();

	//Baza 2
	glBegin(GL_POLYGON);
	for (int i = 0; i < sides; i++)
		glVertex3f(get_x(radius, i * step), -t_height, get_y(radius, i * step));
	glEnd();


	//Omotac
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < sides; i++) {
		glVertex3f(get_x(radius, i * step), -t_height, get_y(radius, i * step));
		glVertex3f(get_x(radius, (i + 1) * step), -t_height, get_y(radius, (i + 1) * step));
		glVertex3f(get_x(radius, i * step), t_height, get_y(radius, i * step));
		glVertex3f(get_x(radius, (i + 1) * step), t_height, get_y(radius, (i + 1) * step));
	}
	glEnd();

}

void CGLRenderer::DrawSphere(float radius, float lats, float longs)
{
	int i, j;
	for (i = 0; i <= lats; i++) {
		double alfa = C_PI * (-0.5 + (double)(i - 1)  / lats);
		double z0 = sin(alfa);
		double zr0 = cos(alfa);// radius za jedan smer

		double beta = C_PI * (-0.5 + (double)i / lats);
		double z1 = sin(beta);
		double zr1 = cos(beta); // radisu za drugi smer

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++) {//koliko redova
			double lng = 2 * C_PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(radius * x * zr0, radius * y * zr0, radius * z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(radius * x * zr1, radius * y * zr1, radius * z1);
		}
		glEnd();
	}

	
}

void CGLRenderer::DrawAxis()
{
	glLineWidth(1.0);

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(3.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 3.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 3.0);
	glEnd();
}

void CGLRenderer::DrawGrid()
{
	glLineWidth(1.0);
	glColor3f(.9, .9, .9);

	glBegin(GL_LINES);
	//0.2 step => -1 do 1 = 10
	for (float i = -1; i <= 1; i += 0.2)
	{
		glVertex3f(1.0, 0, i);
		glVertex3f(-1.0, 0, i);

		glVertex3f(i, 0, 1.0);
		glVertex3f(i, 0, -1.0);
	}
	glEnd();
}

void CGLRenderer::SetAngles(float angle_h, float angle_v)
{
	this->angle_v = angle_h;
	this->angle_h = angle_v;
}

float CGLRenderer::get_x(float radius, float angle)
{
	return radius * cosf(angle);
}

float CGLRenderer::get_y(float radius, float angle)
{
	return radius * sinf(angle);
}

void CGLRenderer::DrawPot()
{
	int sides = 8;
	float t_height = 0.4 / 2.0;

	glPushMatrix();

	glTranslatef(0, 0.2, 0);

	float step = (2 * C_PI) / sides;

	glColor3f(0.62, 0.3, 0.17);
	//Baza 1
	glBegin(GL_POLYGON);
	for (int i = 0; i < sides; i++)
		glVertex3f(get_x(0.45, i * step), t_height, get_y(0.45, i * step));
	glEnd();

	//Baza 2
	glBegin(GL_POLYGON);
	for (int i = 0; i < sides; i++)
		glVertex3f(get_x(0.4, i * step), -t_height, get_y(0.4, i * step));
	glEnd();

	//Omotac
	glBegin(GL_POLYGON);
	for (int i = 0; i < sides; i++) {
		glVertex3f(get_x(0.4, i * step), -t_height, get_y(0.4, i * step));
		glVertex3f(get_x(0.4, (i + 1) * step), -t_height, get_y(0.4, (i + 1) * step));
		glVertex3f(get_x(0.45, i * step), t_height, get_y(0.45, i * step));
		glVertex3f(get_x(0.45, (i + 1) * step), t_height, get_y(0.45, (i + 1) * step));
	}
	glEnd();

	//Translirano je vec na 0.2 , dodamo jos 0.2 da postavimo na
	//pocetak donjeg dela + 0.1 da centriramo gornji deo koji je debljine 0.2
	//+ 0.01 cisto da se lepo vidi depth

	glTranslatef(0, 0.3, 0);
	glColor4f(0.65, 0.3, 0.17, 0.5);
	this->DrawPrism(0.5, 0.2, 8);

	glPopMatrix();

}

void CGLRenderer::DrawFigure()
{
	// Bazna kupa
	glColor3f(0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0.8, 0);
	DrawCone(0.2,0.4);
	glTranslatef(0, 0.3, 0);
	DrawSphere(0.1, 15, 15);
	//sistem je na centru loptice

	MiddleBranch();
	RightBranch();
	LeftBranch();


	glPopMatrix();
}

void CGLRenderer::MiddleBranch()
{

	glPushMatrix();

	//Custom rotation
	glRotatef(angle_cx, 1, 0, 0);
	glRotatef(angle_cy, 0, 1, 0);

	glTranslatef(0, 0.1, 0);


	glColor3f(1, 1, 0);

	glTranslatef(0, 0.2, 0);
	
	DrawCone(0.1,0.4);

	glTranslatef(0, 0.2, 0);
	glTranslatef(0, 0.1, 0);
	glColor3f(0, 1, 0);

	DrawSphere(0.1, 15, 15);
	
	glPushMatrix();
	glRotatef(-45, 1, 0, 0);
	glTranslatef(0, 0.3, 0);
	DrawPrism(0.2,0.4);
	glTranslatef(0, 0.2, 0);
	glTranslatef(0, 0.1, 0);
	DrawSphere(0.1, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 1, 0, 0);
	glTranslatef(0, 0.3, 0);
	DrawCone(0.2,0.4);
	glTranslatef(0, 0.3, 0);
	DrawSphere(0.1, 15, 15);
	glPopMatrix();

	glPopMatrix();
}

void CGLRenderer::RightBranch()
{
	glPushMatrix();
	glColor3f(0, 1, 0);
	glRotatef(-45, 1, 0, 0);
	glTranslatef(0, 0.3, 0);
	DrawRoller(0.1,0.4);
	glTranslatef(0, 0.3, 0);
	DrawSphere(0.1, 15, 15);
	glPopMatrix();
}

void CGLRenderer::LeftBranch()
{
	

	glPushMatrix();
	glRotatef(45, 1, 0, 0);
	glTranslatef(0, 0.3, 0);
	DrawPrism(.1,0.4);
	glTranslatef(0, 0.3, 0);
	DrawSphere(0.1, 15, 15);


	glPushMatrix();
	glRotatef(-45, 1, 0, 0);

	glTranslatef(0, 0.3, 0);
	DrawPrism(0.1,0.4);
	glTranslatef(0, 0.3, 0);


	DrawSphere(0.1, 15, 15);

	glTranslatef(0, 0.3, 0);
	DrawPrism(0.2,0.4);
	glTranslatef(0, 0.3, 0);

	DrawSphere(0.1, 15, 15);
	glPopMatrix();

	glPushMatrix();


	glTranslatef(0, 0.3, 0);
	DrawCone(0.1, 0.4);
	glTranslatef(0, 0.3, 0);


	DrawSphere(0.1, 15, 15);

	glTranslatef(0, 0.3, 0);
	DrawCone(0.2, 0.4);
	glTranslatef(0, 0.3, 0);


	DrawSphere(0.1, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 1, 0, 0);
	glTranslatef(0, 0.3, 0);

	DrawPrism(0.1, 0.4);
	glTranslatef(0, 0.3, 0);

	DrawSphere(0.1, 15, 15);
	glPopMatrix();
	glPopMatrix();
}