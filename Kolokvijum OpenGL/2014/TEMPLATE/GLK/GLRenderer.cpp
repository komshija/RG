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
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	opengl = LoadTextures(CString("opengl.bmp"));

	glEnable(GL_TEXTURE_2D);
	

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);
	SetWhiteLight();

	glRotated(alfa, 1, 0, 0);
	glRotated(beta, 0, 1, 0);

	DrawRubicCube(5.0, 3);

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
	glDeleteTextures(1, &opengl);

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

void CGLRenderer::DrawCube(float size, float s, float t, float texStep)
{
	glBindTexture(GL_TEXTURE_2D, opengl);
	glBegin(GL_QUADS);

	//GORE
	SetMaterial(1, 1, 1);
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



	SetMaterial(1, 1, 0);
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




	SetMaterial(0, 0, 1);
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




	SetMaterial(0, 1, 0);
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



	SetMaterial(1, 0, 0);
	//NAPRED
	//glTexCoord2f(0, 0);

	glTexCoord2f(s, t + texStep);
	glNormal3f(0, 0, 1);
	glVertex3f(-size / 2, -size / 2, size / 2);

	//glTexCoord2f(1, 0);
	glTexCoord2f(s + texStep, t + texStep);
	glNormal3f(0, 0, 1);
	glVertex3f(size / 2, -size / 2, size / 2);

	//glTexCoord2f(1, 1);
	glTexCoord2f(s + texStep, t);
	glNormal3f(0, 0, 1);
	glVertex3f(size / 2, size / 2, size / 2);

	//glTexCoord2f(0, 1);
	glTexCoord2f(s, t);
	glNormal3f(0, 0, 1);
	glVertex3f(-size / 2, size / 2, size / 2);


	SetMaterial(1, 0.5, 0);
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

void CGLRenderer::DrawRubicCube(float size, int count)
{

	float texStep = 1.0 / count;

	float razmak = size + 0.05 * size;
	glTranslatef(-razmak * (count / 2), razmak * (count / 2), razmak * (count / 2));

	for (int k = 0; k < count; k++) {
		glPushMatrix();
		glTranslatef(0, -razmak * (count / 2), -razmak * (count / 2));
		glRotated(pomeraj[k], 1, 0, 0);
		glTranslatef(0, razmak * (count / 2), razmak * (count / 2));
		for (int i = 0; i < count; i++) {
			glPushMatrix();
			for (int j = 0; j < count; j++) {
				DrawCube(size, k * texStep, i * texStep, texStep);
				glTranslatef(0, 0, -size - 0.05 * size);
			}
			glPopMatrix();
			glTranslatef(0, -size - 0.05 * size, 0);
		}
		glPopMatrix();
		glTranslatef(size + 0.05 * size, 0, 0);
	}

}

void CGLRenderer::SetWhiteLight()
{
	//LIGHT0 na poziciciju 5,20,0 , 0 znaci da je tackasto
	float light_position0[4] = { 5,20,0,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	//LIGHT1 na poziciciju 6,4,6, 1 znaci da je direkciono

	float light_position1[4] = { 20,20,20,1 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	float light_direction0[3] = { -1,-1,-0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction0);
	// Da bude usmereno ka 0,0,0
	float light_direction[3] = { -1,-1,-1 };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction);

	//Postavimo sta se jos trazi u zadatku
	float val = 13;
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, val);
	val = 2;
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, val);

	//Povecamo ambijentalno
	float ambient[4] = { 0.5,0.5,0.5,1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	//Postavimo lokalnog posmatraca
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	

	//ukljucimo
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
}

void CGLRenderer::SetMaterial(float r, float g, float b)
{
	float amb[4] = {0.2*r,0.2*g,0.2*b,1};
	float dif[4] = { r,g,b,1 };
	float spec[4] = { r,g,b,1 };
	float emmi[4] = { 0,0,0,0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emmi);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 64);
}
