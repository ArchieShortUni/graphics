#pragma once

#include "Texture.h"
#include "VertexBufferObject.h"
#include "OpenAssetImportMesh.h"

// Class for generating a xz plane of a given size
class CCharacter
{
public:
	CCharacter();
	~CCharacter();
	void Create(glm::vec3 starting_pos,int type);

	glm::vec3  get_position() { return position; }
	glm::vec3  get_up_vector() { return up_vector; }
	glm::vec3  get_tangent() { return tangent; }
	float get_scale() { return scale; }

	void set_position(glm::vec3 new_pos) { position = new_pos; }
	void set_up_vector(glm::vec3 new_vector) {up_vector = new_vector;}
	void set_tangent(glm::vec3 new_vector) {tangent = new_vector;}

	float get_height() { return current_height; }

	void increase_height(float dt, float speed);
	void decrease_height(float dt, float speed);
	COpenAssetImportMesh& get_mesh() { return *mesh; }

private:
	COpenAssetImportMesh *mesh;

	glm::vec3 position = glm::vec3(0.f,0.f,0.f);
	glm::vec3 up_vector = glm::vec3(0.f, 1.f, 0.f);

	glm::vec3 tangent = glm::vec3(0,0,0);

	float current_height = 10.f;
	float min = 0.5f;
	float max = 20.f;

	float scale = .4f;

	float HP = 100.f;

}; 
