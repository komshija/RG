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
	glClearColor(0.0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	marble = LoadTextures(CString("Marble.bmp"));
	fabric = LoadTextures(CString("Fabric1.bmp"));
	metal = LoadTextures(CString("Metal1.bmp"));

	glEnable(GL_TEXTURE_2D);

	float light_position[3] = { 6,4,6 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(3, 2, 3, 0, 1, 0, 0, 1, 0);

	float uvecanje = 1.5;
	glRotated(alfa, 1, 0, 0);
	glRotated(beta, 0, 1, 0);
	
	DrawCube(uvecanje * 1.0);
	glTranslatef(0, uvecanje * 0.5, 0);
	DrawTelo(uvecanje * 0.2, uvecanje * 0.1, uvecanje * 0.05, uvecanje * 1.0, 16);
	glTranslatef(0, uvecanje * 1, 0);
	DrawAbazur(uvecanje * 0.25, uvecanje * 0.5, uvecanje * 0.2, 16);

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
	gluPerspective(45, (double)w / (double)h, 0.1, 2000);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	glDeleteTextures(1, &marble);
	glDeleteTextures(1, &metal);
	glDeleteTextures(1, &fabric);

	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

UINT CGLRenderer::LoadTextures(CString fileName)
{
	UINT id;
	DImage img;
	img.Load(fileName);

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

void CGLRenderer::DrawCube(float size)
{
	glBindTexture(GL_TEXTURE_2D, marble);
	glBegin(GL_QUADS);

	//GORE
	glTexCoord2f(0, 0);
	glNormal3f(0, 1, 0);
	glVertex3f(-size / 2, size / 2, -size / 2);

	glTexCoord2f(0, 1);
	glNormal3f(0, 1, 0);
	glVertex3f(-size / 2, size / 2, size / 2);

	glTexCoord2f(1, 1);
	glNormal3f(0, 1, 0);
	glVertex3f(size / 2, size / 2, size / 2);

	glTexCoord2f(1, 0);
	glNormal3f(0, 1, 0);
	glVertex3f(size / 2, size / 2, -size / 2);



	//DOLE
	glTexCoord2f(0, 0);
	glNormal3f(0, -1, 0);
	glVertex3f(-size / 2, -size / 2, -size / 2);

	glTexCoord2f(0, 1);
	glNormal3f(0, -1, 0);
	glVertex3f(-size / 2, -size / 2, size / 2);

	glTexCoord2f(1, 1);
	glNormal3f(0, -1, 0);
	glVertex3f(size / 2, -size / 2, size / 2);

	glTexCoord2f(1, 0);
	glNormal3f(0, -1, 0);
	glVertex3f(size / 2, -size / 2, -size / 2);




	//DESNO
	glTexCoord2f(0, 0);
	glNormal3f(1, 0, 0);
	glVertex3f(size / 2, size / 2, size / 2);

	glTexCoord2f(1, 0);
	glNormal3f(1, 0, 0);
	glVertex3f(size / 2, size / 2, -size / 2);

	glTexCoord2f(1, 1);
	glNormal3f(1, 0, 0);
	glVertex3f(size / 2, -size / 2, -size / 2);

	glTexCoord2f(0, 1);
	glNormal3f(1, 0, 0);
	glVertex3f(size / 2, -size / 2, size / 2);




	//LEVO
	glTexCoord2f(0, 0);
	glNormal3f(-1, 0, 0);
	glVertex3f(-size / 2, -size / 2, -size / 2);

	glTexCoord2f(1, 0);
	glNormal3f(-1, 0, 0);
	glVertex3f(-size / 2, -size / 2, size / 2);

	glTexCoord2f(1, 1);
	glNormal3f(-1, 0, 0);
	glVertex3f(-size / 2, size / 2, size / 2);

	glTexCoord2f(0, 1);
	glNormal3f(-1, 0, 0);
	glVertex3f(-size / 2, size / 2, -size / 2);



	//NAPRED
	glTexCoord2f(0, 0);
	glNormal3f(0, 0, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);

	glTexCoord2f(1, 0);
	glNormal3f(0, 0, 1);
	glVertex3f(size / 2, -size / 2, size / 2);

	glTexCoord2f(1, 1);
	glNormal3f(0, 0, 1);
	glVertex3f(size / 2, size / 2, size / 2);

	glTexCoord2f(0, 1);
	glNormal3f(0, 0, 1);
	glVertex3f(-size / 2, size / 2, size / 2);


	//NAZAD
	glTexCoord2f(0, 0);
	glNormal3f(0, 0, -1);
	glVertex3f(-size / 2, -size / 2, -size / 2);

	glTexCoord2f(1, 0);
	glNormal3f(0, 0, -1);
	glVertex3f(size / 2, -size / 2, -size / 2);

	glTexCoord2f(1, 1);
	glNormal3f(0, 0, -1);
	glVertex3f(size / 2, size / 2, -size / 2);

	glTexCoord2f(0, 1);
	glNormal3f(0, 0, -1);
	glVertex3f(-size / 2, size / 2, -size / 2);

	glEnd();

}

void CGLRenderer::DrawAbazur(double r1, double r2, double h, int step)
{
	float angleStep = (360. / step) * (3.14 / 180.);
	float texStep = 1. / step;

	glBindTexture(GL_TEXTURE_2D, fabric);

	glBegin(GL_QUADS);
	for (int i = 0; i < step; i++) {

		glTexCoord2f(i * texStep, 0);
		glNormal3f(cos(angleStep * i), 0, sin(angleStep * i));
		glVertex3f(r1 * cos(angleStep * i), h / 2, r1 * sin(angleStep * i));

		glTexCoord2f((i + 1) * texStep, 0);
		glNormal3f(cos(angleStep * (i + 1)), 0, sin(angleStep * (i + 1)));
		glVertex3f(r1 * cos(angleStep * (i + 1)), h / 2, r1 * sin(angleStep * (i + 1)));

		glTexCoord2f((i + 1) * texStep, 0.25);
		glNormal3f(cos(angleStep * (i + 1)), 0, sin(angleStep * (i + 1)));
		glVertex3f(r2 * cos(angleStep * (i + 1)), -h / 2, r2 * sin(angleStep * (i + 1)));


		glTexCoord2f(i * texStep, 0.25);
		glNormal3f(cos(angleStep * i), 0, sin(angleStep * i));
		glVertex3f(r2 * cos(angleStep * i), -h / 2, r2 * sin(angleStep * i));
	}
	glEnd();

}

void CGLRenderer::DrawTelo(double r1, double r2, double r3, double h, int step)
{
	float angleStep = (360. / step) * (3.14 / 180.);
	float texStep = 1. / step;
	float texStepT = 0.25;

	glBindTexture(GL_TEXTURE_2D, metal);

	for (int i = 0; i < step; i++) {

		glBegin(GL_QUAD_STRIP);

		glTexCoord2f(i * texStep, 1);
		glNormal3f(cos(angleStep * i), 0, sin(angleStep * i));
		glVertex3f(r1 * cos(angleStep * i), 0, r1 * sin(angleStep * i));

		glTexCoord2f((i + 1) * texStep, 1);
		glNormal3f(cos(angleStep * (i + 1)), 0, sin(angleStep * (i + 1)));
		glVertex3f(r1 * cos(angleStep * (i + 1)), 0, r1 * sin(angleStep * (i + 1)));




		glTexCoord2f(i * texStep, 0.75);
		glNormal3f(cos(angleStep * i), 0, sin(angleStep * i));
		glVertex3f(r2 * cos(angleStep * i), h / 4, r2 * sin(angleStep * i));

		glTexCoord2f((i + 1) * texStep, 0.75);
		glNormal3f(cos(angleStep * (i + 1)), 0, sin(angleStep * (i + 1)));
		glVertex3f(r2 * cos(angleStep * (i + 1)), h / 4, r2 * sin(angleStep * (i + 1)));



		glTexCoord2f(i * texStep, 0.5);
		glNormal3f(cos(angleStep * i), 0, sin(angleStep * i));
		glVertex3f(r3 * cos(angleStep * i), h / 2, r3 * sin(angleStep * i));

		glTexCoord2f((i + 1) * texStep, 0.5);
		glNormal3f(cos(angleStep * (i + 1)), 0, sin(angleStep * (i + 1)));
		glVertex3f(r3 * cos(angleStep * (i + 1)), h / 2, r3 * sin(angleStep * (i + 1)));




		glTexCoord2f(i * texStep, 0.25);
		glNormal3f(cos(angleStep * i), 0, sin(angleStep * i));
		glVertex3f(r3 * cos(angleStep * i), (3 * h) / 4, r3 * sin(angleStep * i));

		glTexCoord2f((i + 1) * texStep, 0.25);
		glNormal3f(cos(angleStep * (i + 1)), 0, sin(angleStep * (i + 1)));
		glVertex3f(r3 * cos(angleStep * (i + 1)), (3 * h) / 4, r3 * sin(angleStep * (i + 1)));



		glTexCoord2f(i * texStep, 0);
		glNormal3f(cos(angleStep * i), 0, sin(angleStep * i));
		glVertex3f(r2 * cos(angleStep * i), h, r2 * sin(angleStep * i));

		glTexCoord2f((i + 1) * texStep, 0);
		glNormal3f(cos(angleStep * (i + 1)), 0, sin(angleStep * (i + 1)));
		glVertex3f(r2 * cos(angleStep * (i + 1)), h, r2 * sin(angleStep * (i + 1)));

		glEnd();
	}
}

