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
	glClearColor(1.0, 1.0, 1.0, 1.0); // Postavi na belu pozadinu
	glEnable(GL_DEPTH_TEST); // Omoguci dubinu
	/*glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);*/


	TSC[0] = LoadTexture(CString("TSC0.jpg"));
	TSC[1] = LoadTexture(CString("TSC1.jpg"));
	TSC[2] = LoadTexture(CString("TSC2.jpg"));
	TSC[3] = LoadTexture(CString("TSC3.jpg"));
	TSC[4] = LoadTexture(CString("TSC4.jpg"));
	TSC[5] = LoadTexture(CString("TSC5.jpg"));

	M[0] = LoadTexture(CString("M0.jpg"));
	M[1] = LoadTexture(CString("M1.jpg"));
	M[2] = LoadTexture(CString("M2.jpg"));
	M[3] = LoadTexture(CString("M3.jpg"));
	M[4] = LoadTexture(CString("M4.jpg"));
	M[5] = LoadTexture(CString("M5.jpg"));

	S[0] = LoadTexture(CString("S0.jpg"));
	S[1] = LoadTexture(CString("S1.jpg"));
	S[2] = LoadTexture(CString("S2.jpg"));
	S[3] = LoadTexture(CString("S3.jpg"));
	S[4] = LoadTexture(CString("S4.jpg"));
	S[5] = LoadTexture(CString("S5.jpg"));


	glEnable(GL_TEXTURE_2D);
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


	glDisable(GL_DEPTH_TEST);
	//glDisable(GL_LIGHTING);

	glPushMatrix();
	glRotatef(alpha, 1, 0, 0);
	glRotatef(beta, 0, 1, 0);

	DrawSpace(1.0, 20);
	glPopMatrix();


	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);


	glTranslatef(0, 0, -10);
	glRotatef(alpha, 1, 0, 0);
	glRotatef(beta, 0, 1, 0);

	DrawAxis();
	//glColor3f(1.0, 0.0, 0.0);
	
	//DrawPatch(3, 20);
	
	DrawEarth(3, 20);
	glTranslatef(-50, 0, 0);
	glRotated(30, 0, 1, 0);
	DrawMoon(1, 20);

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
	gluPerspective(40, (double)w / (double)h, 0.1, 2000);
	//gluLookAt(0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	glDeleteTextures(6, TSC);
	glDeleteTextures(6, M);
	glDeleteTextures(6, S);
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
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

UINT CGLRenderer::LoadTexture(CString fileName)
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

	/*if (lightEnabled) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	else {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}*/

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());

	return id;
}

void CGLRenderer::DrawPatch(double R, int n)
{
	double podeoci = 2.0 / n;

	double x, y;
	y = 1.0;

	for (int i = 0; i < n; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		x = -1.0;
		for (int j = 0; j < n; j++) {

			double ro = atan(x);
			double teta = atan(y * cos(ro));

			double xd = R * cos(teta) * sin(ro);
			double yd = R * cos(teta) * cos(ro);
			double zd = R * sin(teta);

			glNormal3f(xd / R, yd / R, zd / R);
			glTexCoord2f((x + 1.0) / 2.0, (-y + 1.0) / 2.0);
			glVertex3f(xd, yd, zd);

			ro = atan(x);
			teta = atan((y-podeoci) * cos(ro));
		
			xd = R * cos(teta) * sin(ro);
			yd = R * cos(teta) * cos(ro);
			zd = R * sin(teta);

			glNormal3f(xd / R, yd / R, zd / R);
			glTexCoord2f((x + 1.0) / 2.0, (-y + podeoci + 1.0) / 2.0);
			glVertex3f(xd, yd, zd);
			
			x += podeoci;
		}
		glEnd();
		y -= podeoci;
	}

}

void CGLRenderer::DrawEarth(double R, int n)
{
	
	glPushMatrix();
	for (int i = 0; i < 4; i++)
	{
		glBindTexture(GL_TEXTURE_2D, TSC[i]);
		DrawPatch(R, n);
		glRotated(90, 1, 0, 0);
	}
	glPopMatrix();


	glPushMatrix();
	glRotated(-90, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, TSC[4]);
	DrawPatch(R, n);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, TSC[5]);
	DrawPatch(R, n);
	glPopMatrix();

}

void CGLRenderer::DrawMoon(double R, int n)
{
	glPushMatrix();
	for (int i = 0; i < 4; i++)
	{
		glBindTexture(GL_TEXTURE_2D, M[i]);
		DrawPatch(R, n);
		glRotated(90, 1, 0, 0);
	}
	glPopMatrix();


	glPushMatrix();
	glRotated(-90, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, M[4]);
	DrawPatch(R, n);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, M[5]);
	DrawPatch(R, n);
	glPopMatrix();
}

void CGLRenderer::DrawSpace(double R, int n)
{
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	for (int i = 0; i < 4; i++)
	{
		glBindTexture(GL_TEXTURE_2D, S[i]);
		DrawPatch(R, n);
		glRotated(90, 1, 0, 0);
	}
	glPopMatrix();


	glPushMatrix();
	glRotated(-90, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, S[4]);
	DrawPatch(R, n);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, S[5]);
	DrawPatch(R, n);
	glPopMatrix();
	glEnable(GL_CULL_FACE);
}
