#include "Common.h"
#include "character.h"


CCharacter::CCharacter()
{}

CCharacter::~CCharacter()
{}


void CCharacter::Create(glm::vec3 starting_pos,int type) {
	mesh = new COpenAssetImportMesh;
	if (type == 0) {
		mesh->Load("resources\\models\\Bat\\bat.obj", 0);
	}
	else {
		mesh->Load("resources\\models\\squirrel\\squirrel.obj", 0);
	}
	position = starting_pos;
}

void CCharacter::increase_height(float dt, float speed) {
	if (current_height > max) {
		current_height = max;
	}

	current_height += dt * speed;


}
void CCharacter::decrease_height(float dt, float speed) {
	if (current_height < min) {
		current_height = min;
	}
	current_height -= dt * speed;
}
