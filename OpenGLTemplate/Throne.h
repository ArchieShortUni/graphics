#pragma once
#include "Common.h"
#include "Texture.h"
// Class for generating a unit cube
class CThrone
{
public:
	CThrone();
	~CThrone();
	void Create(string filename);
	void Render();
	void Release();
private:
	GLuint m_vao;
	GLuint m_ibo;
	GLuint m_vbo;

	int m_numTriangles;

	CTexture m_texture;
}; 
