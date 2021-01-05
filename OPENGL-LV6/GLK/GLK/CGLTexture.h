#pragma once
class CGLTexture
{
private:
	unsigned int m_ID;
public:
	CGLTexture();
	~CGLTexture();
	void LoadFileForm(CString fileName);
	void Select();
	void Relase();
	static void PrepareTexture(bool lightEnabled);
	static void BindDefault();
};

