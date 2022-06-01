#pragma once

#include "Texture.h"
#include "VertexBufferObject.h"
#include "OpenAssetImportMesh.h"

// Class for generating a xz plane of a given size
class CGarlic
{
public:
	CGarlic();
	~CGarlic();
	void Create(glm::vec3 starting_pos, float h, float d);

	glm::vec3  get_position() { return position; }
	float  get_distance() { return current_distance; }
	float get_height() { return current_height; }


private:

	glm::vec3 position;

	float current_height = 0.f;

	float current_distance = 0.f;

};
#pragma once
