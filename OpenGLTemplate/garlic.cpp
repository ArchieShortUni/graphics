#include "Common.h"
#include "garlic.h"


CGarlic::CGarlic()
{}

CGarlic::~CGarlic()
{}


void CGarlic::Create(glm::vec3 starting_pos, float h, float d) {
	position = starting_pos;
	current_distance = d;
	current_height = h;
}
