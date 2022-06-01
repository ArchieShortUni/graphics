#pragma once
#include "Common.h"
#include "Texture.h"
#include "VertexBufferObjectIndexed.h"
// Class for generating a unit cube
class CCube
{
public:
	CCube();
	~CCube();
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