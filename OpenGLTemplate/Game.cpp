/* 
OpenGL Template for INM376 / IN3005
City University London, School of Mathematics, Computer Science and Engineering
Source code drawn from a number of sources and examples, including contributions from
 - Ben Humphrey (gametutorials.com), Michal Bubner (mbsoftworks.sk), Christophe Riccio (glm.g-truc.net)
 - Christy Quinn, Sam Kellett and others

 For educational use by Department of Computer Science, City University London UK.

 This template contains a skybox, simple terrain, camera, lighting, shaders, texturing

 Potential ways to modify the code:  Add new geometry types, shaders, change the terrain, load new meshes, change the lighting, 
 different camera controls, different shaders, etc.
 
 Template version 5.0a 29/01/2017
 Dr Greg Slabaugh (gregory.slabaugh.1@city.ac.uk) 

 version 6.0a 29/01/2019
 Dr Eddie Edwards (Philip.Edwards@city.ac.uk)

 version 6.1a 13/02/2022 - Sorted out Release mode and a few small compiler warnings
 Dr Eddie Edwards (Philip.Edwards@city.ac.uk)

*/


#include "game.h"


// Constructor
Game::Game()
{
	m_pSkybox = NULL;
	m_pCamera = NULL;
	m_pShaderPrograms = NULL;
	m_pFtFont = NULL;
	m_pBarrelMesh = NULL;
	m_pHorseMesh = NULL;
	m_pSphere = NULL;
	m_pHighResolutionTimer = NULL;
	m_pAudio = NULL;
	m_testCube = NULL; 
	m_throne = NULL;
	m_pCatmullRom = NULL;
	m_stairs = NULL;
	m_player = NULL; 



	//INSTANCING TEST
	m_test = NULL;

	//Floors
	m_throne_room_floor = NULL;
	m_dinning_hall_floor = NULL;
	m_catwalk_floor = NULL;
	m_library_floor = NULL;
	m_ThroneToLibrary_floor = NULL;
	m_CatWalkToLibrary_floor = NULL;
	m_catwalk_top = NULL;

	m_bookshelf = NULL;

	m_terrain = NULL;
	m_lake = NULL;
	
	m_tPlane = NULL;
	m_FBO = NULL;

	m_dt = 0.0;
	m_framesPerSecond = 0;
	m_frameCount = 0;
	m_elapsedTime = 0.0f;

	
}

// Destructor
Game::~Game() 
{ 
	//INSTANCING TEST
	delete m_test;


	//game objects
	delete m_pCamera;
	delete m_pSkybox;
	delete m_pFtFont;

	//meshes
	delete m_player;
	delete m_npc;

	delete m_arch;
	delete m_brick_wall;
	delete m_door;
	delete m_narrow_pillar;
	delete m_pillar_top;
	delete m_skirting;
	delete m_wide_pillar;
	delete m_window;

	delete m_bookshelf;

	delete m_pBarrelMesh;
	delete m_pHorseMesh;
	delete m_stairs; 

	delete m_lake;
	delete m_terrain; 
	//Floors
	delete m_throne_room_floor;
	delete m_dinning_hall_floor;
	delete m_catwalk_floor;
	delete m_library_floor;
	delete m_ThroneToLibrary_floor;
	delete m_CatWalkToLibrary_floor;
	delete m_catwalk_top;
	delete m_garlic;

	delete m_pSphere;
	delete m_pAudio;
	delete m_testCube; 
	delete m_throne;
	delete m_pCatmullRom;

	delete m_tPlane;
	delete m_FBO;

	if (m_pShaderPrograms != NULL) {
		for (unsigned int i = 0; i < m_pShaderPrograms->size(); i++)
			delete (*m_pShaderPrograms)[i];
	}
	delete m_pShaderPrograms;

	//setup objects
	delete m_pHighResolutionTimer;
}

// Initialisation:  This method only runs once at startup
void Game::Initialise() 
{
	// Set the clear colour and depth
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f);

	//INSTANCING TEST
	m_test = new COpenAssetImportMesh;



	/// Create objects
	m_pCamera = new CCamera;
	m_pSkybox = new CSkybox;
	m_pShaderPrograms = new vector <CShaderProgram *>;
	m_pFtFont = new CFreeTypeFont;

	m_player = new CCharacter; 
	m_npc = new CCharacter;

	//Models
	m_arch = new COpenAssetImportMesh;
	m_brick_wall = new COpenAssetImportMesh;
	m_door = new COpenAssetImportMesh;
	m_narrow_pillar = new COpenAssetImportMesh;
	m_pillar_top = new COpenAssetImportMesh;
	m_skirting = new COpenAssetImportMesh;
	m_wide_pillar = new COpenAssetImportMesh;
	m_window = new COpenAssetImportMesh;
	m_pillar = new COpenAssetImportMesh;
	m_bookshelf = new COpenAssetImportMesh;

	m_pBarrelMesh = new COpenAssetImportMesh;
	m_pHorseMesh = new COpenAssetImportMesh;
	m_garlic = new COpenAssetImportMesh;
	m_lake = new CWater; 
	m_terrain = new CHeightMapTerrain;
	//Floors
	 m_throne_room_floor = new CPlane;
	 m_dinning_hall_floor = new CPlane;
	 m_catwalk_floor = new CPlane;
	 m_library_floor = new CPlane;
	 m_ThroneToLibrary_floor = new CPlane;
	 m_CatWalkToLibrary_floor = new CPlane;
	 m_catwalk_top = new CPlane; 

	m_pSphere = new CSphere;
	m_pAudio = new CAudio;
	m_testCube = new CCube; 
	m_throne = new CThrone; 
	m_stairs = new CStairs; 
	m_pCatmullRom = new CCatmullRom;

	m_tPlane = new CPlane;
	m_FBO = new CFrameBufferObject;

	RECT dimensions = m_gameWindow.GetDimensions();

	int width = dimensions.right - dimensions.left;
	int height = dimensions.bottom - dimensions.top;

	// Set the orthographic and perspective projection matrices based on the image size
	m_pCamera->SetOrthographicProjectionMatrix(width, height); 
	m_pCamera->SetPerspectiveProjectionMatrix(45.0f, (float) width / (float) height, 0.5f, 5000.0f);

	// Load shaders
	vector<CShader> shShaders;
	vector<string> sShaderFileNames;

	

	sShaderFileNames.push_back("courseworkMainShader.vert");
	sShaderFileNames.push_back("courseworkMainShader.frag");


	sShaderFileNames.push_back("courseworkInstancedShader.vert");
	sShaderFileNames.push_back("courseworkInstancedShader.frag");

	sShaderFileNames.push_back("textShader.vert");
	sShaderFileNames.push_back("textShader.frag");

	sShaderFileNames.push_back("waterShader.vert");
	sShaderFileNames.push_back("waterShader.frag");




	for (int i = 0; i < (int) sShaderFileNames.size(); i++) {
		string sExt = sShaderFileNames[i].substr((int) sShaderFileNames[i].size()-4, 4);
		int iShaderType;
		if (sExt == "vert") iShaderType = GL_VERTEX_SHADER;
		else if (sExt == "frag") iShaderType = GL_FRAGMENT_SHADER;
		else if (sExt == "geom") iShaderType = GL_GEOMETRY_SHADER;
		else if (sExt == "tcnl") iShaderType = GL_TESS_CONTROL_SHADER;
		else iShaderType = GL_TESS_EVALUATION_SHADER;
		CShader shader;
		shader.LoadShader("resources\\shaders\\"+sShaderFileNames[i], iShaderType);
		shShaders.push_back(shader);
	}


	
	//Coursework Shader
	CShaderProgram *courseworkShader = new CShaderProgram;
	courseworkShader->CreateProgram();
	courseworkShader->AddShaderToProgram(&shShaders[0]);
	courseworkShader->AddShaderToProgram(&shShaders[1]);
	courseworkShader->LinkProgram();
	m_pShaderPrograms->push_back(courseworkShader);

	//Instanced Renderer
	CShaderProgram* instancedShader = new CShaderProgram;
	instancedShader->CreateProgram();
	instancedShader->AddShaderToProgram(&shShaders[2]);
	instancedShader->AddShaderToProgram(&shShaders[3]);
	instancedShader->LinkProgram();
	m_pShaderPrograms->push_back(instancedShader);


	// Create a shader program for fonts
	CShaderProgram* pFontProgram = new CShaderProgram;
	pFontProgram->CreateProgram();
	pFontProgram->AddShaderToProgram(&shShaders[4]);
	pFontProgram->AddShaderToProgram(&shShaders[5]);
	pFontProgram->LinkProgram();
	m_pShaderPrograms->push_back(pFontProgram);

	//Water Shader 
	CShaderProgram* waterShader = new CShaderProgram;
	waterShader->CreateProgram();
	waterShader->AddShaderToProgram(&shShaders[6]);
	waterShader->AddShaderToProgram(&shShaders[7]);
	waterShader->LinkProgram();
	m_pShaderPrograms->push_back(waterShader);


	// Create the skybox
	m_pSkybox->Create(2500.0f);
	
	//m_pFtFont->LoadSystemFont("arial.ttf", 32);
	m_pFtFont->LoadFont("resources\\fonts\\ENDOR___.ttf", 32);
	m_pFtFont->SetShaderProgram(pFontProgram);

	m_garlic->Load("resources\\models\\Garlic\\garlic.obj");

	m_terrain->Create((char*)"resources\\textures\\heightmap\\heightmap.bmp", (char*)"resources\\textures\\dirtpile01.bmp", glm::vec3(0, 0, 0), 2000.0f,2000.0f, 200.5f);

	m_lake->Create("resources\\textures\\medivel stone\\", "basecolor2.jpg", 2000.f, 2000.f, 5.f);
	//Floors
	m_throne_room_floor->Create("resources\\textures\\medivel stone\\", "basecolor.jpg", 50.f, 100.f, 5.f);
	m_dinning_hall_floor->Create("resources\\textures\\medivel stone\\", "basecolor.jpg", 80.f, 30, 10.f);
	m_catwalk_floor->Create("resources\\textures\\medivel stone\\", "basecolor2.jpg", 20.f, 170.f, 10.f);
	m_library_floor->Create("resources\\textures\\medivel stone\\", "basecolor.jpg", 90.f, 90, 10.f);
	m_ThroneToLibrary_floor->Create("resources\\textures\\medivel stone\\", "basecolor.jpg", 20.f, 20, 10.f);
	m_CatWalkToLibrary_floor->Create("resources\\textures\\medivel stone\\", "basecolor2.jpg", 30.f, 20, 10.f);
	m_catwalk_top->Create("resources\\textures\\medivel stone\\", "basecolor2.jpg", 20.f, 84.1f, 10.f);

	m_testCube->Create("resources\\textures\\wood.jpg");
	m_throne->Create("resources\\textures\\wood.jpg");

	m_stairs->Create("resources\\textures\\Cobblestone.jpg", 1.f, 25.f, 1.5f, 25);

	//FBO STUFF
	m_FBO->Create(width, height);

	//Character 
	m_player->Create(glm::vec3(0, 10, -20),0);
	m_npc->Create(glm::vec3(0, 10, -20), 1);


	glEnable(GL_CULL_FACE);
	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION); 

	// Initialise audio and play background music
	m_pAudio->Initialise();
	m_pAudio->LoadEventSound("resources\\Audio\\Boing.wav");					// Royalty free sound from freesound.org
	m_pAudio->LoadMusicStream("resources\\Audio\\track.mp3");	
	m_pAudio->PlayMusicStream();


	create_instanced_level();

	
	//Spline 
	m_pCatmullRom->CreateCentreline();
	m_pCatmullRom->CreateOffsetCurves();
	m_pCatmullRom->CreateTrack();


}

void Game::Render() {

	m_FBO->Bind();
	Render_scene(0);  
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	Render_scene(1);
	// Draw the 2D graphics after the 3D graphics
	DisplayFrameRate();

	// Swap buffers to show the rendered image
	SwapBuffers(m_gameWindow.Hdc());

}
// Render method runs repeatedly in a loop
void Game::Render_scene(int pass) 
{
	
	// Clear the buffers and enable depth testing (z-buffering)
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CLIP_DISTANCE0); 
	// Set up a matrix stack
	glutil::MatrixStack modelViewMatrixStack;
	modelViewMatrixStack.SetIdentity();



	CShaderProgram* instanced = (*m_pShaderPrograms)[1];
	instanced->UseProgram();
	instanced->SetUniform("sampler0", 0);
	instanced->SetUniform("isRefraction", true);


	if (pass == 1) {
		instanced->SetUniform("isRefraction", false);
	}



	// Set the projection matrix
	modelViewMatrixStack.LookAt(m_pCamera->GetPosition(), m_pCamera->GetView(), m_pCamera->GetUpVector());
	glm::mat4 viewMatrix = modelViewMatrixStack.Top();
	glm::mat3 viewNormalMatrix = m_pCamera->ComputeNormalMatrix(viewMatrix);
	instanced->SetUniform("viewPos", m_pCamera->GetPosition());


	//Main Light
	// Set light and materials in main shader program
	glm::vec4 lightPosition = glm::vec4(60,770,-171,1); // Position of light source *in world coordinates*
	instanced->SetUniform("mainLight.Position", lightPosition);
	instanced->SetUniform("mainLight.La", glm::vec3(0.4f, 0.4f, 0.4f));
	instanced->SetUniform("mainLight.Ld", glm::vec3(0.8f, 0.8f, 0.8f));
	instanced->SetUniform("mainLight.Ls", glm::vec3(1.0f, 1.0f, 1.0f));

	//Player Pointlight
	
	instanced->SetUniform("playerLight.Position", glm::vec4(m_player->get_position(),1.0f));
	instanced->SetUniform("playerLight.La", glm::vec3(0.4f, 0.4f, 0.4f));
	instanced->SetUniform("playerLight.Ld", glm::vec3(0.8f, 0.8f, 0.8f));
	instanced->SetUniform("playerLight.Ls", glm::vec3(1.0f, 1.0f, 1.0f));
	instanced->SetUniform("playerLight.constant", .2f);
	instanced->SetUniform("playerLight.linear", .7f);
	instanced->SetUniform("playerLight.quadratic", .3f);


	instanced->SetUniform("npcLight.Position", glm::vec4(m_npc->get_position(), 1.0f));
	instanced->SetUniform("npcLight.La", glm::vec3(0.4f, 0.4f, 0.4f));
	instanced->SetUniform("npcLight.Ld", glm::vec3(0.8f, 0.8f, 0.8f));
	instanced->SetUniform("npcLight.Ls", glm::vec3(1.0f, 1.0f, 1.0f));
	instanced->SetUniform("npcLight.constant", .2f);
	instanced->SetUniform("npcLight.linear", .7f);
	instanced->SetUniform("npcLight.quadratic", .3f);


	instanced->SetUniform("material1.Ka", glm::vec3(1.0f, 1.0f, 1.0f));		// Ambient colour of light
	instanced->SetUniform("material1.Kd", glm::vec3(1.0f, 1.0f, 1.0f));		// Diffuse colour of light
	instanced->SetUniform("material1.Ks", glm::vec3(1.0f, 1.0f, 1.0f));		// Specular colour of light
	instanced->SetUniform("material1.shininess", 15.0f);		// Shininess material property
	

	//	INSTANCED RENDER CALLS
	for (int i = 0; i < level_meshes.size(); i++) {
		vector<float> temp = level_meshes.at(i).get_transforms();
		int n_transforms = level_meshes.at(i).get_number_of_transforms();

	    modelViewMatrixStack.Push();
		glUniformMatrix4fv(glGetUniformLocation(instanced->GetProgramID(), "modelMatrixes"), n_transforms, false,&temp[0]);
		instanced->SetUniform("viewMatrix", viewMatrix);
		instanced->SetUniform("projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
		instanced->SetUniform("normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		level_meshes.at(i).get_mesh().RenderInstanced();
		modelViewMatrixStack.Pop();

	}



	//Main shader 

	mainShader = (*m_pShaderPrograms)[0];
	mainShader->UseProgram();

	mainShader->SetUniform("isRefraction", true);
	mainShader->SetUniform("isNormalMapped", false);

	if (pass == 1) {
		mainShader->SetUniform("isRefraction", false);
	}
	

	glm::mat4 modelMat;

	//Terrain Shader Variables
	mainShader->SetUniform("sampler0", 0);
	mainShader->SetUniform("sampler1", 1);
	mainShader->SetUniform("sampler2", 2);
	mainShader->SetUniform("sampler3", 3);
	mainShader->SetUniform("sampler4", 4);


	mainShader->SetUniform("fMinHeight", -1000);
	mainShader->SetUniform("fMaxHeight", 1000);


	mainShader->SetUniform("cameraPos", m_pCamera->GetPosition());

	// Set light and materials in main shader program
	//glm::vec4 lightPosition2 = glm::vec4(-100, 100, -100, 2); // Position of light source *in world coordinates*
	mainShader->SetUniform("mainLight.Position", lightPosition);
	mainShader->SetUniform("mainLight.La", glm::vec3(0.4f, 0.4f, 0.4f));
	mainShader->SetUniform("mainLight.Ld", glm::vec3(0.8f, 0.8f, 0.8f));
	mainShader->SetUniform("mainLight.Ls", glm::vec3(1.0f, 1.0f, 1.0f));

	//Player Pointlight

	mainShader->SetUniform("playerLight.Position", glm::vec4(m_player->get_position(), 1.0f));
	mainShader->SetUniform("playerLight.La", glm::vec3(0.4f, 0.4f, 0.4f));
	mainShader->SetUniform("playerLight.Ld", glm::vec3(0.8f, 0.8f, 0.8f));
	mainShader->SetUniform("playerLight.Ls", glm::vec3(1.0f, 1.0f, 1.0f));
	mainShader->SetUniform("playerLight.constant", .2f);
	mainShader->SetUniform("playerLight.linear", .7f);
	mainShader->SetUniform("playerLight.quadratic", .3f);


	mainShader->SetUniform("npcLight.Position", glm::vec4(m_npc->get_position(), 1.0f));
	mainShader->SetUniform("npcLight.La", glm::vec3(0.4f, 0.4f, 0.4f));
	mainShader->SetUniform("npcLight.Ld", glm::vec3(0.8f, 0.8f, 0.8f));
	mainShader->SetUniform("npcLight.Ls", glm::vec3(1.0f, 1.0f, 1.0f));
	mainShader->SetUniform("npcLight.constant", .2f);
	mainShader->SetUniform("npcLight.linear", .7f);
	mainShader->SetUniform("npcLight.quadratic", .3f);

	mainShader->SetUniform("material1.Ka", glm::vec3(1.0f, 1.0f, 1.0f));		// Ambient colour of light
	mainShader->SetUniform("material1.Kd", glm::vec3(1.0f, 1.0f, 1.0f));		// Diffuse colour of light
	mainShader->SetUniform("material1.Ks", glm::vec3(1.0f, 1.0f, 1.0f));		// Specular colour of light
	mainShader->SetUniform("material1.shininess", 15.0f);		// Shininess material property

	mainShader->SetUniform("isCharacter", false);
	mainShader->SetUniform("isTerrain", false);
	mainShader->SetUniform("isWater", false);

	mainShader->SetUniform("renderSkybox", false);
	mainShader->SetUniform("CubeMapTex", 10);

	//SKYBOX
	modelViewMatrixStack.Push();
	mainShader->SetUniform("renderSkybox", true);
	modelMat = glm::mat4(1);
	
	// Translate the modelview matrix to the camera eye point so skybox stays centred around camera
	glm::vec3 vEye = m_pCamera->GetPosition();
	modelMat = glm::translate(modelMat, vEye); 
	modelViewMatrixStack.ApplyMatrix(modelMat);

	//modelViewMatrixStack.Translate(vEye);

	mainShader->SetUniform("modelMatrix", modelMat);
	mainShader->SetUniform("projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
	mainShader->SetUniform("modelViewMatrix", modelViewMatrixStack.Top());
	mainShader->SetUniform("normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top())); 

	m_pSkybox->Render(10);
	mainShader->SetUniform("renderSkybox", false);
	modelViewMatrixStack.Pop();




	modelViewMatrixStack.Push();
	modelMat = glm::mat4(1); 
	modelMat = glm::translate(modelMat, glm::vec3(0.f, 0.0f, 80.0f));
	modelMat = glm::scale(modelMat, glm::vec3(3.0f)); 

	//modelViewMatrixStack.Translate(glm::vec3(0.f, 0.0f, 80.0f));
	//modelViewMatrixStack.Scale(3.0f);
	modelViewMatrixStack.ApplyMatrix(modelMat);

	mainShader->SetUniform("modelMatrix", modelMat);
	mainShader->SetUniform("projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
	mainShader->SetUniform("modelViewMatrix", modelViewMatrixStack.Top());
	mainShader->SetUniform("normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
	//	pMainProgram->SetUniform("bUseTexture", false);

	m_throne->Render();
	modelViewMatrixStack.Pop();



	modelViewMatrixStack.Push();
	modelMat = glm::mat4(1);
	modelMat = glm::translate(modelMat, glm::vec3(-250.f, 0.f, 130.f));
	modelMat = glm::rotate(modelMat,  3.14f, glm::vec3(0.f, 1.f, 0.f));
	modelMat = glm::scale(modelMat, glm::vec3(2.0f));
	modelViewMatrixStack.ApplyMatrix(modelMat);




	mainShader->SetUniform("modelMatrix", modelMat);
	mainShader->SetUniform("projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
	mainShader->SetUniform("modelViewMatrix", modelViewMatrixStack.Top());
	mainShader->SetUniform("normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));

	m_stairs->Render();
	modelViewMatrixStack.Pop();
	

	modelViewMatrixStack.Push();
	modelMat = glm::mat4(1);
	modelMat = glm::translate(modelMat, glm::vec3(-250.f, 0.f, -230.f));
	modelMat = glm::scale(modelMat, glm::vec3(2.0f));
	modelViewMatrixStack.ApplyMatrix(modelMat);



	mainShader->SetUniform("modelMatrix", modelMat);
	mainShader->SetUniform("projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
	mainShader->SetUniform("modelViewMatrix", modelViewMatrixStack.Top());
	mainShader->SetUniform("normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));

	m_stairs->Render();
	modelViewMatrixStack.Pop();

	//FLOORS

	renderPlane(modelViewMatrixStack, m_pCamera, m_throne_room_floor,2.5f);
	renderPlane(modelViewMatrixStack, m_pCamera, m_dinning_hall_floor, 2.5f, glm::vec3(-175.f,0.f, 215.f));
	renderPlane(modelViewMatrixStack, m_pCamera, m_library_floor, 2.5f, glm::vec3(-100.f, 0.f, -287.5f));
	renderPlane(modelViewMatrixStack, m_pCamera, m_ThroneToLibrary_floor, 2.5f, glm::vec3(-30.f, 0.f, -150.f));
	renderPlane(modelViewMatrixStack, m_pCamera, m_CatWalkToLibrary_floor, 2.5f, glm::vec3(-250, 0.f, -272.5f));
	renderPlane(modelViewMatrixStack, m_pCamera, m_catwalk_floor, 2.5f, glm::vec3(-250.f, 0.f, -35.f));
	renderPlane(modelViewMatrixStack, m_pCamera, m_catwalk_top, 2.5f, glm::vec3(-250.f, 50.f, -50.f));

	modelViewMatrixStack.Push();
	if (use_normal_mapping) {
		mainShader->SetUniform("isNormalMapped", true);
	}
	modelMat = glm::mat4(1);
	modelMat = glm::scale(modelMat, glm::vec3(1.0f));

	modelViewMatrixStack.Scale(1.0f);
	modelViewMatrixStack.ApplyMatrix(modelMat);


	mainShader->SetUniform("modelMatrix", modelMat);
	mainShader->SetUniform("projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
	mainShader->SetUniform("modelViewMatrix", modelViewMatrixStack.Top());
	mainShader->SetUniform("normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));

	m_pCatmullRom->RenderTrack();

	mainShader->SetUniform("isNormalMapped", false);

	modelViewMatrixStack.Pop();

//	//RENDER PLAYER
	modelViewMatrixStack.Push(); 
	mainShader->SetUniform("isCharacter", true);

	modelMat = glm::mat4(1);
	modelMat = glm::translate(modelMat, m_player->get_position());

	glm::mat4 playerRotation = glm::inverse(glm::lookAt(glm::vec3(0.0, 0.0, 0.0), m_player->get_tangent(), m_player->get_up_vector()));
	modelMat *=  playerRotation;
	modelMat = glm::scale(modelMat, glm::vec3(.50f));
	modelViewMatrixStack.ApplyMatrix(modelMat);

	mainShader->SetUniform("modelMatrix", modelMat);
	mainShader->SetUniform("projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
	mainShader->SetUniform("modelViewMatrix", modelViewMatrixStack.Top());
	mainShader->SetUniform("normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));

	m_player->get_mesh().Render();
	mainShader->SetUniform("isCharacter", false);

	modelViewMatrixStack.Pop();



	//	//RENDER NPC
	modelViewMatrixStack.Push();
	mainShader->SetUniform("isCharacter", true);

	modelMat = glm::mat4(1);
	modelMat = glm::translate(modelMat, m_npc->get_position());

	glm::mat4 npcRotation = glm::inverse(glm::lookAt(glm::vec3(0.0, 0.0, 0.0), m_npc->get_tangent(), m_npc->get_up_vector()));
	modelMat *= npcRotation;
	modelMat = glm::rotate(modelMat, pi, glm::vec3(0.f, 1.f, 0.f));
	modelMat = glm::scale(modelMat, glm::vec3(.25f));
	modelViewMatrixStack.ApplyMatrix(modelMat);

	mainShader->SetUniform("modelMatrix", modelMat);
	mainShader->SetUniform("projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
	mainShader->SetUniform("modelViewMatrix", modelViewMatrixStack.Top());
	mainShader->SetUniform("normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));

	m_npc->get_mesh().Render();
	mainShader->SetUniform("isCharacter", false);

	modelViewMatrixStack.Pop();
	
	//Render Garlics
	for (int i = 0; i < level_garlics.size(); i++) {
		modelViewMatrixStack.Push();
		modelMat = glm::mat4(1);
		modelMat = glm::translate(modelMat, level_garlics.at(i).get_position()); 
		modelMat = glm::scale(modelMat, glm::vec3(1.0f));
		modelViewMatrixStack.ApplyMatrix(modelMat);

		mainShader->SetUniform("modelMatrix", modelMat);
		mainShader->SetUniform("projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
		mainShader->SetUniform("modelViewMatrix", modelViewMatrixStack.Top());
		mainShader->SetUniform("normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		m_garlic->Render();

		modelViewMatrixStack.Pop();
	}

	//TERRAIN
	 
	modelViewMatrixStack.Push();
	modelMat = glm::mat4(1);
	modelMat = glm::translate(modelMat, glm::vec3(1700.0f, 150.0f, 300));
	modelMat = glm::rotate(modelMat, 3.14f, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMat = glm::scale(modelMat, glm::vec3(3.0f));
	modelViewMatrixStack.ApplyMatrix(modelMat);

	mainShader->SetUniform("modelMatrix", modelMat);
	mainShader->SetUniform("projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
	mainShader->SetUniform("modelViewMatrix", modelViewMatrixStack.Top());
	mainShader->SetUniform("normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));

	mainShader->SetUniform("isTerrain", true);
	m_terrain->Render();  

	modelViewMatrixStack.Pop();

	mainShader->SetUniform("isTerrain", false);


	if (pass == 1) {
		glDisable(GL_CULL_FACE);


		CShaderProgram* waterShader = (*m_pShaderPrograms)[3];
		waterShader->UseProgram();

		waterShader->SetUniform("cameraPos", m_pCamera->GetPosition());
		waterShader->SetUniform("sampler0", 0);
		waterShader->SetUniform("cubeMapTex", 10);


		modelViewMatrixStack.Push();
		modelMat = glm::mat4(1);
		modelMat = glm::translate(modelMat, glm::vec3(0, -30.0f, 1000));
		modelMat = glm::scale(modelMat, glm::vec3(3.0f));
		modelViewMatrixStack.ApplyMatrix(modelMat);

		waterShader->SetUniform("modelMatrix", modelMat);
		waterShader->SetUniform("projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
		waterShader->SetUniform("modelViewMatrix", modelViewMatrixStack.Top());
		waterShader->SetUniform("normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));

		m_FBO->BindTexture(0);
		m_lake->Render();
		modelViewMatrixStack.Pop();
		glEnable(GL_CULL_FACE);

	}

}

// Update method runs repeatedly with the Render method
void Game::Update() 
{
	if (moving_up) {
		m_player->increase_height(m_dt, .0025f);
	}
	if (moving_down) {
		m_player->decrease_height(m_dt, .0025f);
	}



	// Update the camera using the amount of time that has elapsed to avoid framerate dependent motion
	m_currentDistance += m_dt * player_speed;
	player_speed += m_dt * 0.0000001;

	m_currentDistance2 += m_dt * 0.065f;


	if (m_currentDistance > m_currentDistance2) {
		has_won = true;
	}

	//

	//1687.335
	max_distance = m_pCatmullRom->get_total_length();
	glm::vec3 pos;
	glm::vec3 nextPos;
	glm::vec3 up;

	m_pCatmullRom->Sample(m_currentDistance + 1.f, nextPos);
	m_pCatmullRom->Sample(m_currentDistance, pos,up);
	//Character Movement 

	//TNB FRAME.
	glm::vec3 tangent = glm::normalize(nextPos - pos);
	glm::vec3 normal = glm::cross(tangent,up);
	glm::vec3 binormal = glm::cross(normal,tangent);

	glm::vec3 player_pos = pos + (binormal * m_player->get_height());
	m_player->set_position(player_pos);

	m_player->set_up_vector(up);
	m_player->set_tangent(tangent); 

	//NPC MOVEMENT
	glm::vec3 npcpos;
	glm::vec3 npcnextPos;
	glm::vec3 npcup;

	m_pCatmullRom->Sample(m_currentDistance2 + 1.f, npcnextPos);
	m_pCatmullRom->Sample(m_currentDistance2, npcpos, npcup);
	//Character Movement 

	//TNB FRAME.
	glm::vec3 npctangent = glm::normalize(npcnextPos - npcpos);
	glm::vec3 npctangentnormal = glm::cross(npctangent, npcup);
	glm::vec3 npctangentbinormal = glm::cross(npctangentnormal, npctangent);

	glm::vec3 npc_pos = npcpos + (npctangentbinormal * m_npc->get_height());
	m_npc->set_position(npc_pos);

	m_npc->set_up_vector(npcup);
	m_npc->set_tangent(npctangent);




	//CREATE GARLIC OBSTACLES 
	timer += m_dt * .001f;
	if (timer > 3.2f) {
		timer = 0.0f;

		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(0, 1687);
		std::uniform_int_distribution<> distr2(1, 20);

		float height = (float)distr2(gen);
		glm::vec3 g_pos = npcpos + (npctangentbinormal * height);

		//distr2(gen)

		CGarlic newGarlic;
		newGarlic.Create(g_pos, height, m_currentDistance2);
		level_garlics.emplace_back(newGarlic);

	}





	//Garlic collision tests
	for (int i = 0; i < level_garlics.size(); i++) {
		float player_garlic_distance = glm::distance(player_pos, level_garlics.at(i).get_position());
		if (player_garlic_distance < 2.f) {
			level_garlics.erase(level_garlics.begin() + i);
			player_speed -= 0.0002f;
		}
	}

	//Camera mode
	if (camera_mode == 0) {
		m_pCamera->Update(m_dt);

	}
	else if (camera_mode == 1) {
		//Third person far
		glm::vec3 camera_pos = pos + (binormal * m_player->get_height())+(binormal*glm::vec3(5)) - (tangent*glm::vec3(15.f));
		m_pCamera->Set(camera_pos, player_pos + tangent * glm::vec3(15.f), glm::vec3(0,1,0));
	}
	else if (camera_mode == 2) {
		//Third person close, zo o m y and twisty 
		glm::vec3 camera_pos = pos + (binormal * m_player->get_height()) + (binormal * glm::vec3(.7f)) - (tangent * glm::vec3(.9f));
		m_pCamera->Set(camera_pos, player_pos+ tangent * glm::vec3(4.f), up);
		//m_pCamera->Set();
	}

	else if (camera_mode == 4) {
		//Third person close, zo o m y and twisty 
		// + (npctangentbinormal * glm::vec3(.1f))
		glm::vec3 camera_pos = npc_pos + (npctangentbinormal * 2.3f) - (npctangent * glm::vec3(1.2f));
		m_pCamera->Set(camera_pos, npc_pos + npctangent * glm::vec3(5.f), npcup);
		//m_pCamera->Set();
	}

	
		//ACTION CAM
		//1687.335
		float tempDistance = m_currentDistance;
		if (tempDistance > 1687.335) {
			tempDistance = (int)tempDistance % 1687;
		}
		
		//Throne room one
	    if (tempDistance < 170) {
			if (camera_mode == 3) {
				m_pCamera->Set(glm::vec3(-59, 37, 118), player_pos + tangent * glm::vec3(4.f), glm::vec3(0, 1, 0));
			}
			current_room = "Throne Room";
		}
		//Outside
		else if (tempDistance < 310) {
			if (camera_mode == 3) {
				m_pCamera->Set(glm::vec3(-53, 33, 138), player_pos + tangent * glm::vec3(4.f), glm::vec3(0, 1, 0));
			}
			current_room = "Outside";

		}
		//Dinning Room
		else if (tempDistance < 540) {
			if (camera_mode == 3) {
				m_pCamera->Set(glm::vec3(-122, 37, 240), player_pos + tangent * glm::vec3(4.f), glm::vec3(0, 1, 0));
			}
			current_room = "Dinning Room";

		}
		//Catwalk
		else if (tempDistance < 880) {
			if (camera_mode == 3) {
				m_pCamera->Set(glm::vec3(-232, 72, 94), player_pos + tangent * glm::vec3(4.f), glm::vec3(0, 1, 0));
			}
			current_room = "Overview";

		}
		else if (tempDistance < 1030) {
			if (camera_mode == 3) {
				m_pCamera->Set(glm::vec3(-265, 36, -286), player_pos + tangent * glm::vec3(4.f), glm::vec3(0, 1, 0));
			}

		}
		//Library
		else if (tempDistance < 1510) {

			if (camera_mode == 3) {
				m_pCamera->Set(glm::vec3(-188, 45, -370), player_pos + tangent * glm::vec3(4.f), glm::vec3(0, 1, 0));
			}
			current_room = "Library";

		}
		//Throne
		else if (tempDistance < 1687.335) {

			if (camera_mode == 3) {
				m_pCamera->Set(glm::vec3(-47, 29, -101), player_pos + tangent * glm::vec3(4.f), glm::vec3(0, 1, 0));
			}
			current_room = "Throne Room";

		}

		

	
	//m_pCamera->Set(p, p + (10.f * glm::normalize(pNext - p)), glm::vec3(0, 1, 0));




	m_pAudio->Update();
}





void Game::DisplayFrameRate()
{


	CShaderProgram *fontProgram = (*m_pShaderPrograms)[2];

	RECT dimensions = m_gameWindow.GetDimensions();
	int height = dimensions.bottom - dimensions.top;
	
	int width = dimensions.right - dimensions.left;
	// Increase the elapsed time and frame counter
	m_elapsedTime += m_dt;
	m_frameCount++;

	// Now we want to subtract the current time by the last time that was stored
	// to see if the time elapsed has been over a second, which means we found our FPS.
	if (m_elapsedTime > 1000)
    {
		m_elapsedTime = 0;
		m_framesPerSecond = m_frameCount;

		// Reset the frames per second
		m_frameCount = 0;
    }

	if (m_framesPerSecond > 0) {
		// Use the font shader program and render the text
		fontProgram->UseProgram();
		glDisable(GL_DEPTH_TEST);
		fontProgram->SetUniform("matrices.modelViewMatrix", glm::mat4(1));
		fontProgram->SetUniform("matrices.projMatrix", m_pCamera->GetOrthographicProjectionMatrix());
		fontProgram->SetUniform("vColour", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		m_pFtFont->Render(20, height - 30, 20, "FPS: %d", m_framesPerSecond);
		glm::vec3 camPosVec = m_pCamera->GetPosition();
		std::string camPos = "x: " + std::to_string(camPosVec.x) + " y: " + std::to_string(camPosVec.y) + " z: " + std::to_string(camPosVec.z);
		m_pFtFont->Render(20, height - 560, 20, camPos.c_str());
		
		std::string distance = "Distance: " + std::to_string(m_currentDistance);
		m_pFtFont->Render(20, height - 60, 20, distance.c_str());

		std::string location = "Current Location: " + current_room;
		m_pFtFont->Render(20, height - 90, 20, location.c_str());


		std::string timerString = "Current Time: " + std::to_string(timer);
		m_pFtFont->Render(20, height - 140, 20, timerString.c_str());




		std::string test = "Player Speed: " + std::to_string(player_speed);
		m_pFtFont->Render(20, height - 190, 20, test.c_str());

		if (has_won) {
			std::string winScreen = "YOU WIN";
			m_pFtFont->Render(width - width/2, height - height/2, 50, winScreen.c_str());
		}




	}
}

// The game loop runs repeatedly until game over
void Game::GameLoop()
{

	// Variable timer
	m_pHighResolutionTimer->Start();
	Update();
	Render();
	m_dt = m_pHighResolutionTimer->Elapsed();
	

}


void Game::renderPlane(glutil::MatrixStack& stack, CCamera* camera, CPlane* floor, float scale,glm::vec3 position) {
	stack.Push();
	glm::mat4 modelMat = glm::mat4(1);
	modelMat = glm::translate(modelMat, position);
	modelMat = glm::scale(modelMat, glm::vec3(scale));
	stack.ApplyMatrix(modelMat);

	/*stack.Translate(position);
	stack.Scale(scale);*/
	mainShader->SetUniform("modelMatrix", modelMat);

	mainShader->SetUniform("projMatrix", camera->GetPerspectiveProjectionMatrix());
	mainShader->SetUniform("modelViewMatrix", stack.Top());
	mainShader->SetUniform("normalMatrix", camera->ComputeNormalMatrix(stack.Top()));
	floor->Render(true);
	stack.Pop();
}

void Game::create_instanced_level(){
	float scale = 10.f;

	//Initialise Building blocks
	level_mesh arch = level_mesh(*m_arch);				//0
	level_mesh brick_wall = level_mesh(*m_brick_wall);		//1
	level_mesh door = level_mesh(*m_door);				//2
	level_mesh narrow_pillar = level_mesh(*m_narrow_pillar);		//3
	level_mesh pillar_top = level_mesh(*m_pillar_top);		//4
	level_mesh skirting = level_mesh(*m_skirting);			//5
	level_mesh wide_pillar = level_mesh(*m_wide_pillar);		//6
	level_mesh window = level_mesh(*m_window);			//7

	//Props
	level_mesh bookcase = level_mesh(*m_bookshelf); //8
	level_mesh pillar = level_mesh(*m_pillar);//9

	level_meshes.push_back(arch);
	level_meshes.push_back(brick_wall);
	level_meshes.push_back(door);
	level_meshes.push_back(narrow_pillar);
	level_meshes.push_back(pillar_top);
	level_meshes.push_back(skirting);
	level_meshes.push_back(wide_pillar);
	level_meshes.push_back(window);
	level_meshes.push_back(bookcase);
	level_meshes.push_back(pillar);

	//ALL SINGLE MESHES

	//Displaying all assets underneith
	level_meshes.at(0).add_single_mesh(glm::vec3(40, -30, 80), 0, 1.f);
	level_meshes.at(1).add_single_mesh(glm::vec3(60, -30, 80), 0, 1.f);
	level_meshes.at(2).add_single_mesh(glm::vec3(90, -30, 80), 0, 1.f);
	level_meshes.at(3).add_single_mesh(glm::vec3(110, -30, 80), 0, 1.f);
	level_meshes.at(4).add_single_mesh(glm::vec3(120, -30, 80), 0, 1.f);
	level_meshes.at(5).add_single_mesh(glm::vec3(130, -30, 80), 0, 1.f);
	level_meshes.at(6).add_single_mesh(glm::vec3(160, -30, 80), 0, 1.f);
	level_meshes.at(7).add_single_mesh(glm::vec3(180, -30, 80), 0, 1.f);


	//Arches
	level_meshes.at(0).add_single_mesh(glm::vec3(-60.f, 0.f, -130.f), 0, 4.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(-280.f, 0.f, 165.f), 0, 4.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(-220, 0.f, -242.5f), pi / 2, 4.f);




	//Dinning Hall West Entrance 
	level_meshes.at(5).add_single_mesh(glm::vec3(-75.f, 0.f, 240), pi / 2, 2.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(-75.f, 0.f, 197.5f), -pi / 2, 2.5f);
	level_meshes.at(3).add_single_mesh(glm::vec3(-85.f, 0.f, 200.5f), pi / 2, 3.f);
	level_meshes.at(3).add_single_mesh(glm::vec3(-85.f, 0.f, 250.5f), pi / 2, 3.f);

	float layer2 = 60;
	level_meshes.at(5).add_single_mesh(glm::vec3(-75.f, 0.f + layer2,240), pi / 2, 2.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(-75.f, 0.f + layer2, 197.5f), -pi / 2, 2.5f);
	level_meshes.at(3).add_single_mesh(glm::vec3(-85.f, 0.f + layer2, 200.5f), pi / 2, 3.f);
	level_meshes.at(3).add_single_mesh(glm::vec3(-85.f, 0.f + layer2, 250.5f), pi / 2, 3.f);

	level_meshes.at(5).add_single_mesh(glm::vec3(-75.f, 0.f + layer2 + layer2, 240), pi / 2, 2.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(-75.f, 0.f + layer2 + layer2, 197.5f), -pi / 2, 2.5f);
	level_meshes.at(3).add_single_mesh(glm::vec3(-85.f, 0.f + layer2 + layer2, 200.5f), pi / 2, 3.f);
	level_meshes.at(3).add_single_mesh(glm::vec3(-85.f, 0.f + layer2 + layer2, 250.5f), pi / 2, 3.f);


	//NORTH THRONEROOM WALL TEST (Doesnt Need Combining Probably 

	level_meshes.at(5).add_single_mesh(glm::vec3(12.f, 0.f, 125.f), pi, 3.f);
	level_meshes.at(5).add_single_mesh(glm::vec3(62.f, 0.f, 125.f), pi, 3.f);
	level_meshes.at(0).add_single_mesh(glm::vec3 (- 15.f, 9.f, 120.f),0, 2.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(-44.2f, 9.f, 120.f),0, 2.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(14.2, 9.f, 120.f), 0, 2.f);

	level_meshes.at(3).add_single_mesh(glm::vec3(43.4f, 9.f, 120.f), 0, 3.f);
	level_meshes.at(3).add_single_mesh(glm::vec3(-63.7f, 9.f, 120.f), 0, 3.f);

	level_meshes.at(1).add_single_mesh(glm::vec3(-5.f, 0.f, -120.f), 0, 2.f);
	level_meshes.at(1).add_single_mesh(glm::vec3(43.5f, 0.f, -120.f), 0, 2.f);

	level_meshes.at(5).add_single_mesh(glm::vec3(12.f, 0.f+ layer2, 125.f), pi, 3.f);
	level_meshes.at(5).add_single_mesh(glm::vec3(62.f, 0.f + layer2, 125.f), pi, 3.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(-15.f, 9.f + layer2, 120.f), 0, 2.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(-44.2f, 9.f + layer2, 120.f), 0, 2.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(14.2, 9.f + layer2, 120.f), 0, 2.f);

	level_meshes.at(3).add_single_mesh(glm::vec3(43.4f, 9.f + layer2, 120.f), 0, 3.f);
	level_meshes.at(3).add_single_mesh(glm::vec3(-63.7f, 9.f + layer2, 120.f), 0, 3.f);

	layer2 += 60;
	level_meshes.at(5).add_single_mesh(glm::vec3(12.f, 0.f + layer2, 125.f), pi, 3.f);
	level_meshes.at(5).add_single_mesh(glm::vec3(62.f, 0.f + layer2, 125.f), pi, 3.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(-15.f, 9.f + layer2, 120.f), 0, 2.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(-44.2f, 9.f + layer2, 120.f), 0, 2.f);
	level_meshes.at(0).add_single_mesh(glm::vec3(14.2, 9.f + layer2, 120.f), 0, 2.f);

	level_meshes.at(3).add_single_mesh(glm::vec3(43.4f, 9.f + layer2, 120.f), 0, 3.f);
	level_meshes.at(3).add_single_mesh(glm::vec3(-63.7f, 9.f + layer2, 120.f), 0, 3.f);




	//THRONEROOM TO LIBRARY CONNECTION
	level_meshes.at(2).add_single_mesh(glm::vec3(-4.f, 0.f, -157.f), -pi / 2, 2.f);
	level_meshes.at(2).add_single_mesh(glm::vec3(-4.f, 0.f, -185.9f), -pi / 2, 2.f);
	level_meshes.at(3).add_single_mesh(glm::vec3(-6.f, 0.f, -195), 0.f, 3.f);

	level_meshes.at(2).add_single_mesh(glm::vec3(-56.f, 0.f, -130.f), pi / 2, 2.f);
	level_meshes.at(3).add_single_mesh(glm::vec3(-64.f, 0.f, -158.f),pi / 2, 3.f);


	//PREFABS

	mesh_group_prefab longWall = mesh_group_prefab(level_meshes);

	//Layer 1 Walls
	longWall.add_object(1,glm::vec3(0.f, 0.f, -100.f), -pi / 2, 2.f);
	longWall.add_object(1, glm::vec3(0.f, 0.f, -50.f), -pi / 2, 2.f);
	longWall.add_object(1, glm::vec3(0.f, 0.f, 0), -pi / 2, 2.f);
	longWall.add_object(1, glm::vec3(0.f, 0.f, 50.f), -pi / 2, 2.f);
	longWall.add_object(1, glm::vec3(0.f, 0.f, 100.f), -pi / 2, 2.f);

	//Layer 1 Pillars
	longWall.add_object(3, glm::vec3(0.f, 0.f, -57.5f), -pi / 2, 2.f);
	longWall.add_object(3, glm::vec3(0.f, 0.f, -7.5f), -pi / 2, 2.f);
	longWall.add_object(3, glm::vec3(0.f, 0.f, 42.5f), -pi / 2, 2.f);
	longWall.add_object(3, glm::vec3(0.f, 0.f, 92.5f), -pi / 2, 2.f);

	float height = 39;

	//Layer 2 Windows
	longWall.add_object(7, glm::vec3(0.f, height, -100.f), -pi / 2, 2.f);
	longWall.add_object(7, glm::vec3(0.f, height, -50.f), -pi / 2, 2.f);
	longWall.add_object(7, glm::vec3(0.f, height, 0), -pi / 2, 2.f);
	longWall.add_object(7, glm::vec3(0.f, height, 50.f), -pi / 2, 2.f);
	longWall.add_object(7, glm::vec3(0.f, height, 100.f), -pi / 2, 2.f);

	//Layer 2 Pillars
	longWall.add_object(3, glm::vec3(0.f, height, -57.5f), -pi / 2, 2.f);
	longWall.add_object(3, glm::vec3(0.f, height, -7.5f), -pi / 2, 2.f);
	longWall.add_object(3, glm::vec3(0.f, height, 42.5f), -pi / 2, 2.f);
	longWall.add_object(3, glm::vec3(0.f, height, 92.5f), -pi / 2, 2.f);

	height += 39;

	//Layer 3 Windows
	longWall.add_object(7, glm::vec3(0.f, height, -100.f), -pi / 2, 2.f);
	longWall.add_object(7, glm::vec3(0.f, height, -50.f), -pi / 2, 2.f);
	longWall.add_object(7, glm::vec3(0.f, height, 0), -pi / 2, 2.f);
	longWall.add_object(7, glm::vec3(0.f, height, 50.f), -pi / 2, 2.f);
	longWall.add_object(7, glm::vec3(0.f, height, 100.f), -pi / 2, 2.f);

	//Layer 3 Pillars
	longWall.add_object(3, glm::vec3(0.f, height, -57.5f), -pi / 2, 2.f);
	longWall.add_object(3, glm::vec3(0.f, height, -7.5f), -pi / 2, 2.f);
	longWall.add_object(3, glm::vec3(0.f, height, 42.5f), -pi / 2, 2.f);
	longWall.add_object(3, glm::vec3(0.f, height, 92.5f), -pi / 2, 2.f);

	height += 39;

	//Layer 4 Walls
	longWall.add_object(1, glm::vec3(0.f, height, -100.f), -pi / 2, 2.f);
	longWall.add_object(1, glm::vec3(0.f, height, -50.f), -pi / 2, 2.f);
	longWall.add_object(1, glm::vec3(0.f, height, 0), -pi / 2, 2.f);
	longWall.add_object(1, glm::vec3(0.f, height, 50.f), -pi / 2, 2.f);
	longWall.add_object(1, glm::vec3(0.f, height, 100.f), -pi / 2, 2.f);

	//Layer 4 Pillars
	longWall.add_object(3, glm::vec3(0.f, height, -57.5f), -pi / 2, 2.f);
	longWall.add_object(3, glm::vec3(0.f, height, -7.5f), -pi / 2, 2.f);
	longWall.add_object(3, glm::vec3(0.f, height, 42.5f), -pi / 2, 2.f);
	longWall.add_object(3, glm::vec3(0.f, height, 92.5f), -pi / 2, 2.f);

	//SHORT WALL
	mesh_group_prefab shortWall = mesh_group_prefab(level_meshes);
	//Layer 1 
	shortWall.add_object(1, glm::vec3(0.f, 0, -50.f), -pi / 2, 2.f);
	shortWall.add_object(1, glm::vec3(0.f, 0, 0), -pi / 2, 2.f);
	shortWall.add_object(1, glm::vec3(0.f, 0, 50.f), -pi / 2, 2.f);

	shortWall.add_object(3, glm::vec3(0.f, 0, -7.5f), -pi / 2, 2.f);
	shortWall.add_object(3, glm::vec3(0.f, 0, 42.5f), -pi / 2, 2.f);

	height = 39;
	//Layer 2 

	shortWall.add_object(7, glm::vec3(0.f, height, -50.f), -pi / 2, 2.f);
	shortWall.add_object(7, glm::vec3(0.f, height, 0), -pi / 2, 2.f);
	shortWall.add_object(7, glm::vec3(0.f, height, 50.f), -pi / 2, 2.f);

	shortWall.add_object(3, glm::vec3(0.f, height, -7.5f), -pi / 2, 2.f);
	shortWall.add_object(3, glm::vec3(0.f, height, 42.5f), -pi / 2, 2.f);

	height += 39;

	shortWall.add_object(7, glm::vec3(0.f, height, -50.f), -pi / 2, 2.f);
	shortWall.add_object(7, glm::vec3(0.f, height, 0), -pi / 2, 2.f);
	shortWall.add_object(7, glm::vec3(0.f, height, 50.f), -pi / 2, 2.f);

	shortWall.add_object(3, glm::vec3(0.f, height, -7.5f), -pi / 2, 2.f);
	shortWall.add_object(3, glm::vec3(0.f, height, 42.5f), -pi / 2, 2.f);

	height += 39;

	shortWall.add_object(1, glm::vec3(0.f, height, -50.f), -pi / 2, 2.f);
	shortWall.add_object(1, glm::vec3(0.f, height, 0), -pi / 2, 2.f);
	shortWall.add_object(1, glm::vec3(0.f, height, 50.f), -pi / 2, 2.f);

	shortWall.add_object(3, glm::vec3(0.f, height, -7.5f), -pi / 2, 2.f);
	shortWall.add_object(3, glm::vec3(0.f, height, 42.5f), -pi / 2, 2.f);

	//Set Wall Locations 
	longWall.set_prefab_location(glm::vec3(62.5, 0.f, -20.f), 0, 1.f); //Thronewall West
	longWall.submit(); 

	longWall.set_prefab_location(glm::vec3(-62.5, 0.f, 30.f),pi, 1.f); //Thronewall East
	longWall.submit();

	longWall.set_prefab_location(glm::vec3(6.5f, 0.f, -310.f), 0, 1.f); //wallLibraryWest
	longWall.submit();


	shortWall.set_prefab_location(glm::vec3(-212.5, 0.f, -350.f), pi, 1.f); //wallLibraryEast1
	shortWall.submit();

	shortWall.set_prefab_location(glm::vec3(-212.5, 0.f, -150.f), pi, 1.f); //wallLibraryEast2
	shortWall.submit();

	longWall.set_prefab_location(glm::vec3(-120.f, 0.f, -400), pi / 2, 1.f); //wallLibrarySouth
	longWall.submit();

	shortWall.set_prefab_location(glm::vec3(-105.f, 0.f, -175), -pi / 2, 1.f); //wallLibraryNorth
	shortWall.submit();


	shortWall.set_prefab_location(glm::vec3(-175, 0.f, 177), pi/2, 1.f); //wallDinningSouth
	shortWall.submit();

	longWall.set_prefab_location(glm::vec3(-175, 0.f, 252), -pi / 2, 1.f); //wallDinningNorth
	longWall.submit();

	shortWall.set_prefab_location(glm::vec3(-276.5, 0.f, 275), -pi , 1.f); //wallDinningEast
	shortWall.submit();

	//Catwalk Walls
	mesh_group_prefab plainwall = mesh_group_prefab(level_meshes);

	plainwall.add_object(1, glm::vec3(0.f, 0.f, -100.f), -pi / 2, 2.f);
	plainwall.add_object(1, glm::vec3(0.f, 0.f, -50.f), -pi / 2, 2.f);
	plainwall.add_object(1, glm::vec3(0.f, 0.f, 0), -pi / 2, 2.f);
	plainwall.add_object(1, glm::vec3(0.f, 0.f, 50.f), -pi / 2, 2.f);
	plainwall.add_object(1, glm::vec3(0.f, 0.f, 100.f), -pi / 2, 2.f);

	plainwall.add_object(1, glm::vec3(0.f, 39, -100.f), -pi / 2, 2.f);
	plainwall.add_object(1, glm::vec3(0.f, 39, -50.f), -pi / 2, 2.f);
	plainwall.add_object(1, glm::vec3(0.f, 39, 0), -pi / 2, 2.f);
	plainwall.add_object(1, glm::vec3(0.f, 39, 50.f), -pi / 2, 2.f);
	plainwall.add_object(1, glm::vec3(0.f, 39, 100.f), -pi / 2, 2.f);

	plainwall.add_object(3, glm::vec3(0.f, 39, -57.5f), -pi / 2, 2.f);
	plainwall.add_object(3, glm::vec3(0.f, 39, -7.5f), -pi / 2, 2.f);
	plainwall.add_object(3, glm::vec3(0.f, 39, 42.5f), -pi / 2, 2.f);
	plainwall.add_object(3, glm::vec3(0.f, 39, 92.5f), -pi / 2, 2.f);

	plainwall.add_object(3, glm::vec3(0.f, 0.f, -57.5f), -pi / 2, 2.f);
	plainwall.add_object(3, glm::vec3(0.f, 0.f, -7.5f), -pi / 2, 2.f);
	plainwall.add_object(3, glm::vec3(0.f, 0.f, 42.5f), -pi / 2, 2.f);
	plainwall.add_object(3, glm::vec3(0.f, 0.f, 92.5f), -pi / 2, 2.f);


	plainwall.set_prefab_location(glm::vec3(-222,0,30), 0, 1.f); //wallLibraryWest
	plainwall.submit();

	plainwall.set_prefab_location(glm::vec3(-222, 0, -148), 0, 1.f); //wallLibraryWest
	plainwall.submit();


	plainwall.set_prefab_location(glm::vec3(-222, 78, 30), 0, 1.f); //wallLibraryWest
	plainwall.submit();

	plainwall.set_prefab_location(glm::vec3(-222, 78 ,-148), 0, 1.f); //wallLibraryWest
	plainwall.submit();


	plainwall.set_prefab_location(glm::vec3(-276, -28, 65), pi, 1.f); //wallLibraryWest
	plainwall.submit();
	//ADDING PROPS 

	//level_meshes.at(8).add_single_mesh(glm::vec3(-100, 8, -300), 0, 5.f);
	mesh_group_prefab bookcaseCluster = mesh_group_prefab(level_meshes);
	bookcaseCluster.add_object(8,glm::vec3(0, 8, 0), 0, 5.f);
	bookcaseCluster.add_object(8, glm::vec3(16, 8, 0), 0, 5.f);
	bookcaseCluster.add_object(8, glm::vec3(-16, 8, 0), 0, 5.f);
	bookcaseCluster.add_object(8, glm::vec3(32, 8, 0), 0, 5.f);
	bookcaseCluster.add_object(8, glm::vec3(-32, 8, 0), 0, 5.f);
	bookcaseCluster.add_object(8, glm::vec3(0, 24, 0), 0, 5.f);
	bookcaseCluster.add_object(8, glm::vec3(16, 24, 0), 0, 5.f);
	bookcaseCluster.add_object(8, glm::vec3(-16, 24, 0), 0, 5.f);
	bookcaseCluster.add_object(8, glm::vec3(32, 24, 0), 0, 5.f);
	bookcaseCluster.add_object(8, glm::vec3(-32, 24, 0), 0, 5.f);

	bookcaseCluster.set_prefab_location(glm::vec3(-168,0,-189), 0, 1);
	bookcaseCluster.submit();

	bookcaseCluster.set_prefab_location(glm::vec3(-168, 32, -189), 0, 1);
	bookcaseCluster.submit();

	bookcaseCluster.set_prefab_location(glm::vec3(-128, 0, -259), pi/2, 1);
	bookcaseCluster.submit();

	bookcaseCluster.set_prefab_location(glm::vec3(-128, 32, -259), pi / 2, 1);
	bookcaseCluster.submit();
	
	mesh_group_prefab bigPillar = mesh_group_prefab(level_meshes);
	bigPillar.add_object(9, glm::vec3(0, 0, 0), 0, 1.f);
	bigPillar.add_object(9, glm::vec3(0, 26, 0), 0, 1.f);
	bigPillar.add_object(9, glm::vec3(0, 52, 0), 0, 1.f);
	bigPillar.add_object(9, glm::vec3(0, 78, 0), 0, 1.f);
	bigPillar.add_object(9, glm::vec3(0, 104, 0), 0, 1.f);
	bigPillar.add_object(9, glm::vec3(0, 130, 0), 0, 1.f);

	bigPillar.set_prefab_location(glm::vec3(-40, 0, -30), 0, 1.f);
	bigPillar.submit();
	bigPillar.set_prefab_location(glm::vec3(30, 0, -30), 0, 1.f);
	bigPillar.submit();

	bigPillar.set_prefab_location(glm::vec3(-40, 0, -90), 0, 1.f);
	bigPillar.submit();
	bigPillar.set_prefab_location(glm::vec3(30, 0, -90), 0, 1.f);
	bigPillar.submit();

	bigPillar.set_prefab_location(glm::vec3(-40, 0, 30), 0, 1.f);
	bigPillar.submit();
	bigPillar.set_prefab_location(glm::vec3(30, 0, 30), 0, 1.f);
	bigPillar.submit();

	bigPillar.set_prefab_location(glm::vec3(-40, 0, 90), 0, 1.f);
	bigPillar.submit();

	//Loading in the models - Must be done last
	level_meshes.at(0).load("resources\\models\\CastleObjs\\Arch.obj");
	level_meshes.at(1).load("resources\\models\\CastleObjs\\brick_wall.obj");
	level_meshes.at(2).load("resources\\models\\CastleObjs\\door.obj");
	level_meshes.at(3).load("resources\\models\\CastleObjs\\narrow_pillar.obj");
	level_meshes.at(4).load("resources\\models\\CastleObjs\\pillar_top.obj");
	level_meshes.at(5).load("resources\\models\\CastleObjs\\Skirting.obj");
	level_meshes.at(6).load("resources\\models\\CastleObjs\\wide_pillar_withdoor.obj");
	level_meshes.at(7).load("resources\\models\\CastleObjs\\window.obj");

	level_meshes.at(8).load("resources\\models\\InteriorCastle\\BookshelfLarge.obj");
	level_meshes.at(9).load("resources\\models\\CastleObjs\\Pillar_standalone.obj");

}


WPARAM Game::Execute() 
{
	m_pHighResolutionTimer = new CHighResolutionTimer;
	m_gameWindow.Init(m_hInstance);

	if(!m_gameWindow.Hdc()) {
		return 1;
	}

	Initialise();

	m_pHighResolutionTimer->Start();

	
	MSG msg;

	while(1) {													
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { 
			if(msg.message == WM_QUIT) {
				break;
			}

			TranslateMessage(&msg);	
			DispatchMessage(&msg);
		} else if (m_appActive) {
			GameLoop();
		} 
		else Sleep(200); // Do not consume processor power if application isn't active
	}

	m_gameWindow.Deinit();

	return(msg.wParam);
}

LRESULT Game::ProcessEvents(HWND window,UINT message, WPARAM w_param, LPARAM l_param) 
{
	LRESULT result = 0;

	switch (message) {


	case WM_ACTIVATE:
	{
		switch(LOWORD(w_param))
		{
			case WA_ACTIVE:
			case WA_CLICKACTIVE:
				m_appActive = true;
				m_pHighResolutionTimer->Start();
				break;
			case WA_INACTIVE:
				m_appActive = false;
				break;
		}
		break;
		}

	case WM_SIZE:
			RECT dimensions;
			GetClientRect(window, &dimensions);
			m_gameWindow.SetDimensions(dimensions);
		break;

	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(window, &ps);
		EndPaint(window, &ps);
		break;



	case WM_KEYDOWN:
		switch(w_param) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case '1':
			camera_mode = 0;
			break;
		case '2':
			camera_mode = 1;
			break;
		case '3':
			camera_mode = 2;
			break;
		case '4':
			camera_mode = 3;
			break;

		case '5':
			camera_mode = 4;
			break;

		case 'E':
			m_player->increase_height(m_dt, .05f);

			break;
		case 'Q':
			m_player->decrease_height(m_dt, .05f);
			break;
		case 'N':
			use_normal_mapping = !use_normal_mapping;
			break;
		case VK_F1:
			m_pAudio->PlayEventSound();
			break;
		}
		break;



	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		result = DefWindowProc(window, message, w_param, l_param);
		break;
	}

	return result;
}

Game& Game::GetInstance() 
{
	static Game instance;

	return instance;
}

void Game::SetHinstance(HINSTANCE hinstance) 
{
	m_hInstance = hinstance;
}

LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	return Game::GetInstance().ProcessEvents(window, message, w_param, l_param);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, PSTR, int) 
{
	Game &game = Game::GetInstance();
	game.SetHinstance(hinstance);

	return int(game.Execute());
}


