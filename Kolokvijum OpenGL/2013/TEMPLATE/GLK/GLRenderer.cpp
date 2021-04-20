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
	glClearColor(1, 1, 1, 0);
	glEnable(GL_DEPTH_TEST);

	tex[0] = LoadTexture(CString("Eiffel-1a.bmp"));
	tex[1] = LoadTexture(CString("Eiffel-2a.bmp"));
	tex[2] = LoadTexture(CString("Eiffel-3a.bmp"));
	tex[3] = LoadTexture(CString("Eiffel-4a.bmp"));

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

	float toRad = 3.14 / 180;
	
	gluLookAt(15 * cos(beta * toRad), 5, 15 * sin(beta * toRad), 0, 4, 0, 0, 1, 0);

	glPushMatrix();
	glTranslatef(10 * cos(alfa * toRad), 0, 10 * sin(alfa * toRad));
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();

	float light_position[4] = { 10*cos(alfa * toRad),0,10*sin(alfa*toRad),0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	float light_direction[3] = { 1,0,0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30);
	glEnable(GL_LIGHT0);


	//glRotatef(alfa, 1, 0, 0);
	//glRotatef(beta, 0, 1, 0);

	//ZADATAK SE NE RADI BAS KAO NA KOLOKVIJUMU SA VEKTORIMA
	DrawAiffelTower();

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

	glDeleteTextures(4, tex);

	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
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

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());

	return id;
}

void CGLRenderer::DrawPiramida(float a, float b, float h, float x1, float x2)
{

	float r = (a - b) / 2;
	float L = sqrt(h * h + r * r);
	float ny = r / L;
	float nr = h / L;


	
	glBegin(GL_QUADS);


	//Desna
	glTexCoord2f(1-x2, 1);
	glNormal3f(nr, ny, 0);
	glVertex3f(a / 2, -h / 2, -a / 2);
	glTexCoord2f(1-x1, 0);
	glNormal3f(nr, ny, 0);
	glVertex3f(b / 2, h / 2, -b / 2);
	glTexCoord2f(x1, 0);
	glNormal3f(nr, ny, 0);
	glVertex3f(b / 2, h / 2, b / 2);
	glTexCoord2f(x2, 1);
	glNormal3f(nr, ny, 0);
	glVertex3f(a / 2, -h / 2, a / 2);


	//Zadnja

	glTexCoord2f(1 - x2, 1);
	glNormal3f(0, ny, -nr);
	glVertex3f(-a / 2, -h / 2, -a / 2);
	glTexCoord2f(1 - x1, 0);
	glNormal3f(0, ny, -nr);
	glVertex3f(-b / 2, h / 2, -b / 2);
	glTexCoord2f(x1, 0);
	glNormal3f(0, ny, -nr);
	glVertex3f(b / 2, h / 2, -b / 2);
	glTexCoord2f(x2, 1);
	glNormal3f(0, ny, -nr);
	glVertex3f(a / 2, -h / 2, -a / 2);
	
	//Prednja
	glTexCoord2f(1 - x2, 1);
	glNormal3f(0, ny, nr);
	glVertex3f(-a / 2, -h / 2, a / 2);
	glTexCoord2f(1 - x1, 0);
	glNormal3f(0, ny, nr);
	glVertex3f(-b / 2, h / 2, b / 2);
	glTexCoord2f(x1, 0);
	glNormal3f(0, ny, nr);
	glVertex3f(b / 2, h / 2, b / 2);
	glTexCoord2f(x2, 1);
	glNormal3f(0, ny, nr);
	glVertex3f(a / 2, -h / 2, a / 2);


	//Leva
	glTexCoord2f(1 - x2, 1);
	glNormal3f(-nr, ny, 0);
	glVertex3f(-a / 2, -h / 2, -a / 2);
	glTexCoord2f(1 - x1, 0);
	glNormal3f(-nr, ny, 0);
	glVertex3f(-b / 2, h / 2, -b / 2);
	glTexCoord2f(x1, 0);
	glNormal3f(-nr, ny, 0);
	glVertex3f(-b / 2, h / 2, b / 2);
	glTexCoord2f(x2, 1);
	glNormal3f(-nr, ny, 0);
	glVertex3f(-a / 2, -h / 2, a / 2);

	glEnd();

}

void CGLRenderer::DrawAiffelTower()
{

	glPushMatrix();
	glTranslatef(0, 1.5 / 2, 0);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	DrawPiramida(4, 2.4, 1.5, 0.215, 0);
	glTranslatef(0, 1.5 / 2, 0);

	glBindTexture(GL_TEXTURE_2D, tex[3]);
	DrawPiramida(2.4, 2.64, 0.25, 0, 0);

	glTranslatef(0, 1.5 / 2, 0);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	DrawPiramida(2.4, 1.2, 1.5, 0.215, 0);
	glTranslatef(0, 1.5 / 2, 0);

	glPushMatrix();
	glScalef(0.5, 1, 0.5);
	glBindTexture(GL_TEXTURE_2D, tex[3]);
	DrawPiramida(2.4, 2.64, 0.25, 0, 0);
	glPopMatrix();

	glTranslatef(0, 4, 0);
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	DrawPiramida(1.08, 0, 8, 0.45, 0.05);
	glTranslatef(0, 4, 0);
	glPopMatrix();

}
