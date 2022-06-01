#include "Stairs.h"


struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 tex;

	Vertex() {}

	Vertex(const glm::vec3& pos_in, const glm::vec2& tex_coord_in, const glm::vec3& normal_in)
	{
		pos = pos_in;
		normal = normal_in;
		tex = tex_coord_in;
	}
};

CStairs::CStairs()
{}
CStairs::~CStairs()
{
	Release();
}

void CStairs::Create(string filename, float step_height, float step_width, float step_depth, int n_steps)
{
	number_of_steps = n_steps; 

	float step_texture_ratio = (step_depth / step_height) * 0.05f;

	m_texture.Load(filename);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);


	//VBO Object Data

	//Front face texture coords
	glm::vec2 t00 = glm::vec2(0.0f, 0.0f); //Bottom Left
	glm::vec2 t01 = glm::vec2(0.0f, 0.05f); //Top Left
	glm::vec2 t10 = glm::vec2(1.0f, 0.0f); //Bottom Right
	glm::vec2 t11 = glm::vec2(1.0f, 0.05f); //Top Right

	//Top face Texture Coords
	glm::vec2 tt00 = glm::vec2(0.0f, 0.0f); //Bottom Left
	glm::vec2 tt01 = glm::vec2(0.0f, step_texture_ratio); //Top Left
	glm::vec2 tt10 = glm::vec2(1.0f, 0.0f); //Bottom Right
	glm::vec2 tt11 = glm::vec2(1.0f, step_texture_ratio); //Top Right


	glm::vec3 posZ = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 negZ = glm::vec3(0.0f, 0.0f, -1.0f);

	glm::vec3 posY = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 negY = glm::vec3(0.0f, -1.0f, 0.0f);

	glm::vec3 posX = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 negX = glm::vec3(-1.0f, 0.0f, 0.0f);
	//ALL RECTANGLE FACES

	//SEAT
	//Seat front Face

	//Define Starting Points

	glm::vec3 lft = glm::vec3(-(step_width/2),step_height,0);	//Left Front Top
	glm::vec3 lfb = glm::vec3(-(step_width / 2), 0, 0);	//Left Front Bottom
	glm::vec3 rft = glm::vec3((step_width / 2), step_height, 0);  //Right Front Top
	glm::vec3 rfb = glm::vec3((step_width / 2), 0, 0);  //Right Front Bottom

	glm::vec3 ltb = glm::vec3(-(step_width / 2), step_height, step_depth); //Left Top Back
	glm::vec3 rtb = glm::vec3((step_width / 2), step_height, step_depth);	//Right Top Back


	CVertexBufferObject vbo;
	vbo.Create();
	vbo.Bind();
	
	//vbo.AddData(Data,Size) 
	/*vbo.AddData(&m_centrelinePoints.at(i), sizeof(glm::vec3));
	vbo.AddData(&texCoord, sizeof(glm::vec2));
	vbo.AddData(&normal, sizeof(glm::vec3));*/
	
	for (int i = 0; i < number_of_steps; i++) {
	// 
	//Front Face of Step 
		vbo.AddData(&lfb, sizeof(glm::vec3));
		vbo.AddData(&t00, sizeof(glm::vec2));
		vbo.AddData(&negZ, sizeof(glm::vec3));

		vbo.AddData(&lft, sizeof(glm::vec3));
		vbo.AddData(&t01, sizeof(glm::vec2));
		vbo.AddData(&negZ, sizeof(glm::vec3));

		vbo.AddData(&rfb, sizeof(glm::vec3));
		vbo.AddData(&t10, sizeof(glm::vec2));
		vbo.AddData(&negZ, sizeof(glm::vec3));

		vbo.AddData(&rft, sizeof(glm::vec3));
		vbo.AddData(&t11, sizeof(glm::vec2));
		vbo.AddData(&negZ, sizeof(glm::vec3));

		//Top Face of Step
		vbo.AddData(&lft, sizeof(glm::vec3));
		vbo.AddData(&tt00, sizeof(glm::vec2));
		vbo.AddData(&posY, sizeof(glm::vec3));

		vbo.AddData(&ltb, sizeof(glm::vec3));
		vbo.AddData(&tt01, sizeof(glm::vec2));
		vbo.AddData(&posY, sizeof(glm::vec3));

		vbo.AddData(&rft, sizeof(glm::vec3));
		vbo.AddData(&tt10, sizeof(glm::vec2));
		vbo.AddData(&posY, sizeof(glm::vec3));

		vbo.AddData(&rtb, sizeof(glm::vec3));
		vbo.AddData(&tt11, sizeof(glm::vec2));
		vbo.AddData(&posY, sizeof(glm::vec3));

		glm::vec3 increment = glm::vec3(0, step_height, step_depth);
		lft += increment;
		lfb += increment;
		rft += increment;
		rfb += increment;
		ltb += increment;
		rtb += increment;

		float increment2 = (float)rand() / RAND_MAX;
		t00 += glm::vec2(0.f, increment2);
		t01	+= glm::vec2(0.f, increment2);
		t10 += glm::vec2(0.f, increment2);
		t11	+= glm::vec2(0.f, increment2);
		float increment3 = (float)rand() / RAND_MAX;

		tt00 += glm::vec2(0.f, increment3);
		tt01 += glm::vec2(0.f, increment3);
		tt10 += glm::vec2(0.f, increment3);
		tt11 += glm::vec2(0.f, increment3);
	}

	// Upload the VBO to the GPU
	vbo.UploadDataToGPU(GL_STATIC_DRAW);
	// Set the vertex attribute locations
	GLsizei stride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);
	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride,
		(void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}

void CStairs::Render()
{
	glBindVertexArray(m_vao);
	m_texture.Bind();
	// Call glDrawArrays to render each side
	//for (int i = 0; i < 99; i += 4) {
	for (int i = 0; i < number_of_steps * 8; i += 4) {
		glDrawArrays(GL_TRIANGLE_STRIP, i, 4);

	}
		;

//	}
	



	//glDrawElements(GL_TRIANGLES, m_numTriangles * 3, GL_UNSIGNED_INT, nullptr);
}


void CStairs::Release()
{
	m_texture.Release();
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	//m_vbo.Release();
}


