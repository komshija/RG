#include "stdafx.h"
#include "CGLTexture.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"

CGLTexture::CGLTexture()
{
}

CGLTexture::~CGLTexture()
{
}

void CGLTexture::LoadFileForm(CString fileName)
{
	DImage img;
	img.Load(fileName);
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());
}

void CGLTexture::Select()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void CGLTexture::Relase()
{
	glDeleteTextures(1, &m_ID);
}

void CGLTexture::PrepareTexture(bool lightEnabled)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	if (lightEnabled) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	else {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
}

void CGLTexture::BindDefault()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
