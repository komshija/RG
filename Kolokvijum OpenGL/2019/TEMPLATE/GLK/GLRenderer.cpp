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
	glEnable(GL_TEXTURE_2D);
	texture = Loadtexture("excavator.png");

	cube[0] = Loadtexture("bot.jpg");
	/*cube[1] = Loadtexture("top.jpg");
	cube[2] = Loadtexture("left.jpg");
	cube[3] = Loadtexture("right.jpg");
	cube[4] = Loadtexture("front.jpg");
	cube[5] = Loadtexture("back.jpg");
	*/
	

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(alfa, 0, 0, 1);
	glRotatef(beta, 0, 1, 0);

	DrawCubeEnv(100);
	DrawExcavator();

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
	gluPerspective(55, (double)w / (double)h, 0.1, 2000);
	gluLookAt(0, 5, 0, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	glDeleteTextures(1, &texture);
	glDeleteTextures(6, cube);
	
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

UINT CGLRenderer::Loadtexture(char* fileName)
{
	UINT id;
	DImage img;
	img.Load(CString(fileName));

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

void CGLRenderer::DrawPolygon(POINTF* points, POINTF* texCoords, int n)
{
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < n; i++) {
		glTexCoord2f(texCoords[i].x, texCoords[i].y);
		glVertex3f(points[i].x, points[i].y, 0);
	}
	glEnd();
}

void CGLRenderer::DrawExtrudedPolygon(POINTF* points, POINTF* texCoords, int n, float zh, float r, float g, float b)
{
	glColor3f(1, 1, 1);
	glNormal3f(0, 0, -1);
	DrawPolygon(points, texCoords, n);
	glTranslatef(0, 0, zh);
	glNormal3f(0, 0, 1);
	DrawPolygon(points, texCoords, n);
	glTranslatef(0, 0, -zh);

	
	glColor3f(r, g, b);
	glBegin(GL_QUAD_STRIP);
	for (int i = 1; i < n; i++) {
		glVertex3f(points[i].x, points[i].y, 0);
		glVertex3f(points[i].x, points[i].y, zh);
	}
	glVertex3f(points[1].x, points[1].y, 0);
	glVertex3f(points[1].x, points[1].y, zh);
	glEnd();

	
}

void CGLRenderer::DrawBase()
{
	float texStep = 1. / 16.;
	int n = 11;
	POINTF* points = new POINTF[n];
	POINTF* texCoord = new POINTF[n];

	points[0].x = 8 * 0.5;
	points[0].y = 2 * 0.5;
	texCoord[0].x = texStep * 8;
	texCoord[0].y = texStep * 14;

	points[1].x = 1 * 0.5;
	points[1].y = 0 * 0.5;
	texCoord[1].x = texStep * 1;
	texCoord[1].y = texStep * 16;

	points[2].x = 0 * 0.5;
	points[2].y = 1 * 0.5;
	texCoord[2].x = texStep * 0;
	texCoord[2].y = texStep * 15;

	points[3].x = 0 * 0.5;
	points[3].y = 3 * 0.5;
	texCoord[3].x = texStep * 0;
	texCoord[3].y = texStep * 13;

	points[4].x = 1 * 0.5;
	points[4].y = 4 * 0.5;
	texCoord[4].x = texStep * 1;
	texCoord[4].y = texStep * 12;

	points[5].x = 15 * 0.5;
	points[5].y = 4 * 0.5;
	texCoord[5].x = texStep * 15;
	texCoord[5].y = texStep * 12;

	points[6].x = 16 * 0.5;
	points[6].y = 3 * 0.5;
	texCoord[6].x = texStep * 16;
	texCoord[6].y = texStep * 13;

	points[7].x = 16 * 0.5;
	points[7].y = 1 * 0.5;
	texCoord[7].x = texStep * 16;
	texCoord[7].y = texStep * 15;

	points[8].x = 16 * 0.5;
	points[8].y = 1 * 0.5;
	texCoord[8].x = texStep * 16;
	texCoord[8].y = texStep * 15;

	points[9].x = 15 * 0.5;
	points[9].y = 0 * 0.5;
	texCoord[9].x = texStep * 15;
	texCoord[9].y = texStep * 16;

	points[10].x = 1 * 0.5;
	points[10].y = 0 * 0.5;
	texCoord[10].x = texStep * 1;
	texCoord[10].y = texStep * 16;

	DrawExtrudedPolygon(points, texCoord, 11, 5, 0, 0, 0);


	delete []points;
	delete []texCoord;
}

void CGLRenderer::DrawBody()
{
	float texStep = 1. / 16.;
	int n = 7;
	POINTF* points = new POINTF[n];
	POINTF* texCoord = new POINTF[n];

	points[0].x = 4 * 0.5;
	points[0].y = 4 * 0.5;
	texCoord[0].x = texStep * 12;
	texCoord[0].y = texStep * 4;

	points[1].x = 0 * 0.5;
	points[1].y = 0 * 0.5;
	texCoord[1].x = texStep * 8;
	texCoord[1].y = texStep * 8;

	points[2].x = 0 * 0.5;
	points[2].y = 8 * 0.5;
	texCoord[2].x = texStep * 8;
	texCoord[2].y = texStep * 0;

	points[3].x = 4 * 0.5;
	points[3].y = 8 * 0.5;
	texCoord[3].x = texStep * 12;
	texCoord[3].y = texStep * 0;

	points[4].x = 8 * 0.5;
	points[4].y = 4 * 0.5;
	texCoord[4].x = texStep * 16;
	texCoord[4].y = texStep * 4;

	points[5].x = 8 * 0.5;
	points[5].y = 0 * 0.5;
	texCoord[5].x = texStep * 16;
	texCoord[5].y = texStep * 8;

	points[6].x = 0 * 0.5;
	points[6].y = 0 * 0.5;
	texCoord[6].x = texStep * 8;
	texCoord[6].y = texStep * 8;

	DrawExtrudedPolygon(points, texCoord, 7, 4, 0.96, 0.5, 0.12);


	delete[]points;
	delete[]texCoord;
}

void CGLRenderer::DrawArm(float zh)
{
	float texStep = 1. / 16.;
	int n = 8;
	POINTF* points = new POINTF[n];
	POINTF* texCoord = new POINTF[n];

	points[0].x = 8 * 0.5;
	points[0].y = 2 * 0.5;
	texCoord[0].x = texStep * 8;
	texCoord[0].y = texStep * 10;

	points[1].x = 1 * 0.5;
	points[1].y = 0 * 0.5;
	texCoord[1].x = texStep * 1;
	texCoord[1].y = texStep * 12;

	points[2].x = 0 * 0.5;
	points[2].y = 1 * 0.5;
	texCoord[2].x = texStep * 0;
	texCoord[2].y = texStep * 11;

	points[3].x = 0 * 0.5;
	points[3].y = 3 * 0.5;
	texCoord[3].x = texStep * 0;
	texCoord[3].y = texStep * 9;

	points[4].x = 1 * 0.5;
	points[4].y = 4 * 0.5;
	texCoord[4].x = texStep * 1;
	texCoord[4].y = texStep * 8;

	points[5].x = 16 * 0.5;
	points[5].y = 3 * 0.5;
	texCoord[5].x = texStep * 16;
	texCoord[5].y = texStep * 9;

	points[6].x = 16 * 0.5;
	points[6].y = 1 * 0.5;
	texCoord[6].x = texStep * 16;
	texCoord[6].y = texStep * 11;

	points[7].x = 1 * 0.5;
	points[7].y = 0 * 0.5;
	texCoord[7].x = texStep * 8;
	texCoord[7].y = texStep * 10;

	DrawExtrudedPolygon(points, texCoord, n, zh, 0.96, 0.5, 0.12);


	delete[]points;
	delete[]texCoord;
}

void CGLRenderer::DrawFork()
{
	float texStep = 1. / 16.;
	int n = 8;
	POINTF* points = new POINTF[n];
	POINTF* texCoord = new POINTF[n];

	points[0].x = 4 * 0.5;
	points[0].y = 4 * 0.5;
	texCoord[0].x = texStep * 4;
	texCoord[0].y = texStep * 2;

	points[1].x = 0 * 0.5;
	points[1].y = 0 * 0.5;
	texCoord[1].x = texStep * 0;
	texCoord[1].y = texStep * 6;

	points[2].x = 0 * 0.5;
	points[2].y = 5 * 0.5;
	texCoord[2].x = texStep * 0;
	texCoord[2].y = texStep * 1;

	points[3].x = 1 * 0.5;
	points[3].y = 6 * 0.5;
	texCoord[3].x = texStep * 1;
	texCoord[3].y = texStep * 0;

	points[4].x = 7 * 0.5;
	points[4].y = 6 * 0.5;
	texCoord[4].x = texStep * 7;
	texCoord[4].y = texStep * 0;

	points[5].x = 8 * 0.5;
	points[5].y = 5 * 0.5;
	texCoord[5].x = texStep * 8;
	texCoord[5].y = texStep * 1;

	points[6].x = 8 * 0.5;
	points[6].y = 0 * 0.5;
	texCoord[6].x = texStep * 8;
	texCoord[6].y = texStep * 6;

	points[7].x = 0 * 0.5;
	points[7].y = 0 * 0.5;
	texCoord[7].x = texStep * 0;
	texCoord[7].y = texStep * 6;

	DrawExtrudedPolygon(points, texCoord, n, 1, 0.7, 0.7, 0.7);


	delete[]points;
	delete[]texCoord;
}

void CGLRenderer::DrawExcavator()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	glTranslatef(-4, 0, -2.5);
	DrawBase();
	glTranslatef(4*.5, 0.5*4, 0.5);
	DrawBody();
	glTranslatef(4,0,2);
	glTranslatef(1, 1, 0);
	glRotatef(90 + ugao1, 0, 0, 1);
	glTranslatef(-1, -1, 0);
	DrawArm(1);
	glTranslatef(7.5, 1, -0.25);
	glRotatef(-90 + ugao2, 0, 0, 1);
	glTranslatef(-1, -1, 0);
	DrawArm(1.5);
	glTranslatef(7.5, 1, 0.25);
	glRotatef(-90 + ugao3, 0, 0, 1);
	glTranslatef(-1, -1, 0);
	DrawFork();
	glPopMatrix();
}

void CGLRenderer::DrawCubeEnv(float a)
{
	glPushMatrix();
	glTranslatef(0, a / 2, 0);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	a /= 2;

	//bot
	glBindTexture(GL_TEXTURE_2D, cube[0]);
	glTexCoord2f(0, 0);
	glVertex3f(-a,-a,-a);
	glTexCoord2f(0, 1);
	glVertex3f(-a,-a,a);
	glTexCoord2f(1, 1);
	glVertex3f(a,-a,a);
	glTexCoord2f(1, 0);
	glVertex3f(a,-a,-a);

	//top
	glBindTexture(GL_TEXTURE_2D, cube[1]);
	glTexCoord2f(0, 0);
	glVertex3f(-a, a, -a);
	glTexCoord2f(0, 1);
	glVertex3f(-a, a, a);
	glTexCoord2f(1, 1);
	glVertex3f(a, a, a);
	glTexCoord2f(1, 0);
	glVertex3f(a, a, -a);

	//left
	glBindTexture(GL_TEXTURE_2D, cube[2]);
	glTexCoord2f(1, 1);
	glVertex3f(-a, -a, -a);
	glTexCoord2f(1, 0);
	glVertex3f(-a, a, -a);
	glTexCoord2f(0, 0);
	glVertex3f(-a, a, a);
	glTexCoord2f(0, 1);
	glVertex3f(-a, -a, a);

	//right
	glBindTexture(GL_TEXTURE_2D, cube[3]);
	glTexCoord2f(1, 1);
	glVertex3f(a, -a, -a);
	glTexCoord2f(1, 0);
	glVertex3f(a, a, -a);
	glTexCoord2f(0, 0);
	glVertex3f(a, a, a);
	glTexCoord2f(0, 1);
	glVertex3f(a, -a, a);

	//front
	glBindTexture(GL_TEXTURE_2D, cube[4]);
	glTexCoord2f(1, 1);
	glVertex3f(-a, -a, -a);
	glTexCoord2f(1, 0);
	glVertex3f(-a, a, -a);
	glTexCoord2f(0, 0);
	glVertex3f(a, a, -a);
	glTexCoord2f(0, 1);
	glVertex3f(a, -a, -a);


	//front
	glBindTexture(GL_TEXTURE_2D, cube[5]);
	glTexCoord2f(1, 1);
	glVertex3f(-a, -a, a);
	glTexCoord2f(1, 0);
	glVertex3f(-a, a, a);
	glTexCoord2f(0, 0);
	glVertex3f(a, a, a);
	glTexCoord2f(0, 1);
	glVertex3f(a, -a, a);

	glEnd();
	glPopMatrix();
}

