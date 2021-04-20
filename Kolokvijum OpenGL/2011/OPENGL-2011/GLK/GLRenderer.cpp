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
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	LoadTexture();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	glEnable(GL_LIGHT0);

	glTranslatef(0, 0, -10);

	glRotatef(alfa, 1, 0, 0);
	glRotatef(beta, 0, 1, 0);

	DrawCompoundBody();
	DrawWings();

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
	glDeleteTextures(1, &id);
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::DrawBody(double r, double h1, double h2, int n)
{
	float step = (360 / n) * (3.14 / 180.0);
	float texStep = 0.5 / n;

	glBegin(GL_QUADS);
	for (int i = 0; i < n; i++) {
		glNormal3f(cos(step * i), 0, sin(step * i));
		glTexCoord2f(0.25, 0.5 + i * texStep);
		glVertex3f(r * cos(step * i), -h2 / 2, r * sin(step * i));

		glNormal3f(cos(step * i), 0, sin(step * i));
		glTexCoord2f(0.5, 0.5 + i * texStep);
		glVertex3f(r * cos(step * i), h2 / 2, r * sin(step * i));

		glNormal3f(cos(step * (i + 1)), 0, sin(step * (i + 1)));
		glTexCoord2f(0.5, 0.5 + (i+1) * texStep);
		glVertex3f(r * cos(step * (i+1)), h2 / 2, r * sin(step * (i + 1)));

		glNormal3f(cos(step * (i + 1)), 0, sin(step * (i + 1)));
		glTexCoord2f(0.25, 0.5 + (i+1) * texStep);
		glVertex3f(r * cos(step * (i + 1)), -h2 / 2, r * sin(step * (i + 1)));
	}
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.125,0.75);
	glVertex3f(0, h1 / 2, 0);
	for (int i = 0; i <= n; i++) {
		glNormal3f(cos(step * i), 0, sin(step * i));
		glTexCoord2f(0.125 + 0.125 * cos(step * i),0.75 + 0.25*sin(step * i));
		glVertex3f(r * cos(step * i), h2/2, r * sin(step * i));
	}
	glEnd();



	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0.125, 0.75);
	glVertex3f(0, -h1 / 2, 0);
	for (int i = 0; i <= n; i++) {
		glNormal3f(cos(step * i), 0, sin(step * i));
		glTexCoord2f(0.125 + 0.125 * cos(step * i),0.75 + 0.25*sin(step * i));
		glVertex3f(r * cos(step * i), -h2 / 2, r * sin(step * i));
	}
	glEnd();


}

void CGLRenderer::DrawCompoundBody()
{
	glPushMatrix();

	glRotated(90, 1, 0, 0);
	DrawBody(1.0, 2.5, 2.0, 8);
	glRotated(90, 0, 0, 1);
	glColor3f(0.75, 0.75,0.75);
	glDisable(GL_TEXTURE_2D);
	DrawBody(0.5, 3.5, 3.0, 8);
	DrawBody(0.25, 5.0, 5.0, 8);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CGLRenderer::DrawWing()
{
	glPushMatrix();

	glTranslatef(0, 0.75, 0);
	glRotated(-20, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.5, 0);
	glVertex3f(0, 2.75, 0);

	glTexCoord2f(0, 0.5);
	glVertex3f(-4, 0.75, 0);
	
	glTexCoord2f(0.75, 0.5);
	glVertex3f(2, 0.75, 0);

	glTexCoord2f(0.75, 0);
	glVertex3f(2, 2.75, 0);

	glEnd();

	glTranslatef(0, 0.75, 0);
	glRotated(20, 1, 0, 0);
	glTranslatef(0, -0.75, 0);

	
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.5,0.5);
	glVertex3f(0, 0.75, 0);

	glTexCoord2f(0.75,0.5);
	glVertex3f(2, 0.75, 0);
	
	glTexCoord2f(0.75,1);
	glVertex3f(2, -0.75, 0);

	glTexCoord2f(0.5,1);
	glVertex3f(0, -0.75, 0);
	glEnd();

	glTranslatef(0, -0.75, 0);
	glRotated(20, 1, 0, 0);
	glTranslatef(0, 0.75, 0);

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	
	glTexCoord2f(0.5, 0);
	glVertex3f(0, -2.75, 0);
	
	glTexCoord2f(0, 0.5);
	glVertex3f(-4, -0.75, 0);

	glTexCoord2f(0.75, 0.5);
	glVertex3f(2, -0.75, 0);

	glTexCoord2f(0.75, 0);
	glVertex3f(2, -2.75, 0);
	glEnd();

	
	glPopMatrix();
}

void CGLRenderer::DrawWings()
{
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslatef(0, 0, 2.5);
	DrawWing();
	glTranslatef(0, 0, -5);
	glRotated(180, 1, 0, 0);
	DrawWing();
	glPopMatrix();
}

void CGLRenderer::LoadTexture()
{
	DImage img;
	img.Load(CString("Kol2011.bmp"));
	

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());

}

