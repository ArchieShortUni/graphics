#pragma once
#include "Common.h"
#include "Texture.h"
#include "vertexBufferObject.h"

// Class for generating a unit cube
class CStairs
{
public:
	CStairs();
	~CStairs();
	void Create(string filename,float step_height,float step_width,float step_depth,int n_steps);
	void Render();
	void Release();
private:
	GLuint m_vao;
	GLuint m_vbo;

	int number_of_steps;
	int m_numTriangles;

	CTexture m_texture;
};
