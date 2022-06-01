#pragma once

#include "Texture.h"
#include "VertexBufferObject.h"
#include "Cubemap.h"
// Class for generating a xz plane of a given size
class CWater
{
public:
	CWater();
	~CWater();
	void Create(string sDirectory, string sFilename, float fWidth, float fHeight, float fTextureRepeat);
	void Render();
	void Release();
private:
	UINT m_vao;
	CVertexBufferObject m_vbo;
	CTexture m_texture;
	string m_directory;
	string m_filename;
	CCubemap m_cubemapTexture;

	float m_width;
	float m_height;
};