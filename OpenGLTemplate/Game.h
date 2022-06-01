#pragma once

#include "Common.h"
#include <string> 

// Setup includes
#include "HighResolutionTimer.h"
#include "GameWindow.h"

// Game includes
#include "Camera.h"
#include "Water.h" 
#include "Skybox.h"
#include "Plane.h"
#include "Shaders.h"
#include "FreeTypeFont.h"
#include "Sphere.h"
#include "MatrixStack.h"
#include "OpenAssetImportMesh.h"
#include "Audio.h"
#include "testCube.h"
#include "Throne.h"
#include "Stairs.h"
#include "CatmullRom.h"
#include "HeightMapTerrain.h"
#include "FrameBufferObject.h"
#include "character.h"
#include <random> 
#include "garlic.h"



// Classes used in game.  For a new class, declare it here and provide a pointer to an object of this class below.  Then, in Game.cpp, 
// include the header.  In the Game constructor, set the pointer to NULL and in Game::Initialise, create a new object.  Don't forget to 
// delete the object in the destructor.   
class CCamera;
class CSkybox;
class CShader;
class CShaderProgram;
class CPlane;
class CFreeTypeFont;
class CHighResolutionTimer;
class CSphere;
class COpenAssetImportMesh;
class CAudio;
class CCube;
class CThrone; 
class CCatmullRom;
class CHeightMapTerrain; 
class CStairs;
class CWater; 
class CFrameBufferObject; 
class CCharacter;
class CGarlic; 

struct level_mesh {
	COpenAssetImportMesh mesh;
	vector<glm::mat4> transform_matrixes;
	int number_of_transforms = 0;
	vector<float> transFloatsVec;

	level_mesh(COpenAssetImportMesh m) :mesh(m) {}

	vector<float> flatten_mat(glm::mat4 mat) {
		vector<float> newMatrix;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				newMatrix.push_back(mat[i][j]);
			}
		}
		return newMatrix;
	}

	void load(std::string path) {
		mesh.Load(path, number_of_transforms);
		//Turn mat4 to vec float 

		for (int i = 0; i < transform_matrixes.size(); i++) {
			vector<float> temp = flatten_mat(transform_matrixes.at(i));
			transFloatsVec.insert(transFloatsVec.end(), temp.begin(), temp.end());
		}
	}

	int get_number_of_transforms() { return number_of_transforms; }

	void add_transform(glm::mat4 transform) {
		transform_matrixes.push_back(transform);
		number_of_transforms++;
	}

	void add_single_mesh(glm::vec3 position, float rotation, float scale) {
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::rotate(transform, rotation, glm::vec3(0, 1, 0));
		transform = glm::scale(transform, glm::vec3(scale)); 
		transform_matrixes.push_back(transform);
		number_of_transforms++;
	}

	std::vector<float> get_transforms() {
		return 	 transFloatsVec;
		
	}

	COpenAssetImportMesh& get_mesh() { return mesh; }
};

struct mesh_group_prefab {
	vector<level_mesh>& level_mesh_vector;
	vector<float> level_mesh_positions;
	vector<glm::mat4> prefab_transforms;

	vector<glm::vec3> positions;
	vector<float> rotations;
	vector<float> scales;


	mesh_group_prefab(vector<level_mesh>& lmv) :level_mesh_vector(lmv) {}

	void add_object(int mesh_number, glm::vec3 position, float rotation, float scale) {
		level_mesh_positions.push_back(mesh_number);
		positions.push_back(position);
		rotations.push_back(rotation);
		scales.push_back(scale);
	}

	void set_prefab_location(glm::vec3 position, float rotation, float scale) {
		prefab_transforms.clear(); 
		for (int i = 0; i < level_mesh_positions.size(); i++) {
			glm::mat4 transform = glm::mat4(1.0f);

			transform = glm::translate(transform, position);
			transform = glm::rotate(transform, rotation, glm::vec3(0, 1, 0));
			transform = glm::scale(transform, glm::vec3(scale));

			transform = glm::translate(transform, positions.at(i));
			transform = glm::rotate(transform, rotations.at(i), glm::vec3(0, 1, 0));
			transform = glm::scale(transform, glm::vec3(scales.at(i)));

			prefab_transforms.push_back(transform);
		}
	}

	void submit() {
		for (int i = 0; i < level_mesh_positions.size(); i++) {
			level_mesh_vector.at(level_mesh_positions.at(i)).add_transform(prefab_transforms.at(i));
		}
	}
};




class Game {
private:
	// Three main methods used in the game.  Initialise runs once, while Update and Render run repeatedly in the game loop.
	void Initialise();
	void Update();
	void Render();
	void Render_scene(int pass = 0);


	// Pointers to game objects.  They will get allocated in Game::Initialise()
	CSkybox *m_pSkybox;
	CCamera *m_pCamera;
	vector <CShaderProgram *> *m_pShaderPrograms;
	CFreeTypeFont *m_pFtFont;

	CHeightMapTerrain *m_terrain;  
	CWater *m_lake;

	//Rooms
	CPlane* m_throne_room_floor;
	CPlane* m_dinning_hall_floor;
	CPlane* m_catwalk_floor;
	CPlane* m_library_floor;
	CPlane* m_catwalk_top; 

	//Corridoor Floors
	CPlane* m_ThroneToLibrary_floor;
	CPlane* m_CatWalkToLibrary_floor;
	
	//INSTANCING TEST
	COpenAssetImportMesh* m_test;

	//Meshes
	COpenAssetImportMesh* m_arch;
	COpenAssetImportMesh* m_brick_wall;
	COpenAssetImportMesh* m_door;
	COpenAssetImportMesh* m_narrow_pillar;
	COpenAssetImportMesh* m_pillar_top;
	COpenAssetImportMesh* m_skirting;
	COpenAssetImportMesh* m_wide_pillar;
	COpenAssetImportMesh* m_window;
	COpenAssetImportMesh* m_pillar;




	//Props
	COpenAssetImportMesh* m_bookshelf;
	COpenAssetImportMesh* m_garlic;


	COpenAssetImportMesh *m_pBarrelMesh;
	COpenAssetImportMesh *m_pHorseMesh;
 
	CSphere *m_pSphere;
	CHighResolutionTimer *m_pHighResolutionTimer;
	CAudio* m_pAudio; 
	CCube* m_testCube; 
	CThrone* m_throne;
	CStairs* m_stairs;
	CCatmullRom* m_pCatmullRom;

	CPlane* m_tPlane;
	CFrameBufferObject* m_FBO;

	CCharacter* m_player; 
	CCharacter* m_npc;

	// Some other member variables
	double m_dt;
	int m_framesPerSecond;
	bool m_appActive;


public:
	Game();
	~Game();
	static Game& GetInstance();

	LRESULT ProcessEvents(HWND window,UINT message, WPARAM w_param, LPARAM l_param);
	void SetHinstance(HINSTANCE hinstance);
	WPARAM Execute();

private:
	float m_currentDistance = 0.0f; 
	float player_speed = 0.06f;
	float m_currentDistance2 = 30.0f;

	float timer = 0.0f; 

	float pi = 3.14159265359; 
	static const int FPS = 60;
	void DisplayFrameRate();
	void GameLoop();
	GameWindow m_gameWindow;
	HINSTANCE m_hInstance;
	int m_frameCount;
	double m_elapsedTime;

	float rotationAngle;


	//Player Variables
	float camera_mode = 0; 
	float max_distance = 0;

	bool moving_up = false;
	bool moving_down = false;

	std::string current_room = "";

	//Level Variables
	vector<CGarlic> level_garlics; 
	vector<level_mesh> level_meshes;

	bool has_won = false;
	bool use_normal_mapping = true;

	void renderPlane(glutil::MatrixStack& stack, CCamera* camera, CPlane* floor, float scale = 1.f, glm::vec3 position = glm::vec3(0, 0, 0));
	void create_instanced_level();




	//Variables to compartmentilise object rendering
	CShaderProgram* mainShader;



};
