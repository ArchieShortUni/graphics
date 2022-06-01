#include "Throne.h"


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

CThrone::CThrone()
{}
CThrone::~CThrone()
{
	Release();
}

void CThrone::Create(string filename)
{

	m_texture.Load(filename);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);


	//VBO Object Data

	Vertex vertices[150];

	glm::vec2 t00 = glm::vec2(0.0f, 0.0f); //Bottom Left
	glm::vec2 t01 = glm::vec2(0.0f, 1.0f); //Top Left
	glm::vec2 t10 = glm::vec2(1.0f, 0.0f); //Bottom Right
	glm::vec2 t11 = glm::vec2(1.0f, 1.0f); //Top Right
	glm::vec2 placeholder = glm::vec2(.5f, .5f);


	glm::vec3 posZ = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 negZ = glm::vec3(0.0f, 0.0f, -1.0f);

	glm::vec3 posY = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 negY = glm::vec3(0.0f, -1.0f, 0.0f);

	glm::vec3 posX = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 negX = glm::vec3(-1.0f, 0.0f, 0.0f);
	//ALL RECTANGLE FACES

	//SEAT
	//Seat front Face
	vertices[0] = Vertex(glm::vec3(-2.0f, 0.f, 0.f), glm::vec2(.0f, 0.0f), negZ); //bottom left front
	vertices[2] = Vertex(glm::vec3(2.0f, 0.f, 0.f), glm::vec2(1.f, 0.0f), negZ);  //bottom right front
	vertices[1] = Vertex(glm::vec3(-2.0f, 1.f, 0.f), glm::vec2(.0f, 0.3f), negZ); //top left front
	vertices[3] = Vertex(glm::vec3(2.0f, 1.f, 0.f), glm::vec2(1.0f, 0.3f), negZ);  //top right front

	//left armrest inwards face
	vertices[4] = Vertex(glm::vec3(-2.0f, 0.f, 0.f), glm::vec2(0.f, 0.f), posX); //bottom left front //0
	vertices[5] = Vertex(glm::vec3(-2.0f, 0.f, -.5f), glm::vec2(0.18f, 0.f), posX);  //bottom			//4
	vertices[6] = Vertex(glm::vec3(-2.0f, 1.f, 0.f), glm::vec2(0.f, 0.3f), posX); //top left front    //1
	vertices[7] = Vertex(glm::vec3(-2.0f, 1.f, -.5f), glm::vec2(0.18f, 0.3f), posX);  //top          //5

	// right armrest inwards face
	vertices[8] = Vertex(glm::vec3(2.0f, 0.f, -.5f), glm::vec2(0.18f, 0.f), negX);  //bottom			//6
	vertices[9] = Vertex(glm::vec3(2.0f, 0.f, 0.f), glm::vec2(0.f, 0.f), negX);  //bottom right front //3
	vertices[10] = Vertex(glm::vec3(2.0f, 1.f, -.5f), glm::vec2(0.18f, 0.3f), negX);  //top				//7
	vertices[11] = Vertex(glm::vec3(2.0f, 1.f, 0.f), glm::vec2(0.f, 0.3f), negX);  //top right front	//2


	//seat top
	vertices[12] = Vertex(glm::vec3(-2.0f, 1.f, 0.f), glm::vec2(0.0f, 1.0f), posY); //top left front //1
	vertices[13] = Vertex(glm::vec3(-2.0f, 1.f, 3.5f), glm::vec2(0.0f, .0f), posY);  //left back	//8
	vertices[14] = Vertex(glm::vec3(2.0f, 1.f, 0.f), glm::vec2(1.0f, 1.0f), posY);  //top right front	//2
	vertices[15] = Vertex(glm::vec3(2.0f, 1.f, 3.5f), glm::vec2(1.0f, 0.0f), posY);  //right back	//9

	//CHAIR BACK
	vertices[16] = Vertex(glm::vec3(-2.0f, 1.f, 3.5f), glm::vec2(0.0f, .0f), negZ);  //left back //8
	vertices[17] = Vertex(glm::vec3(-2.0f, 8.f, 3.5f), glm::vec2(0.0f, .74f), negZ);  //left p1 //10
	vertices[18] = Vertex(glm::vec3(2.0f, 1.f, 3.5f), glm::vec2(1.0f, 0.0f), negZ);  //right back  9
	vertices[19] = Vertex(glm::vec3(2.0f, 8.f, 3.5f), glm::vec2(1.0f, 0.74f), negZ);  //right p4  11


	//ARMRESTS
	//left armrest frontwards face
	vertices[20] = Vertex(glm::vec3(-2.0f, 0.f, -.5f), glm::vec2(.4f, 0.0f), negZ);  //bottom	4
	vertices[21] = Vertex(glm::vec3(-3.0f, 0.f, -.5f), glm::vec2(.0f, 0.0f), negZ);  //bottom outside		17
	vertices[22] = Vertex(glm::vec3(-2.0f, 3.f, -.5f), glm::vec2(.4f, 1.0f), negZ);  //top inside		19
	vertices[23] = Vertex(glm::vec3(-3.0f, 3.f, -.5f), glm::vec2(0.0f, 1.0f), negZ);  //top outside 18

	//right armrest frontwards face
	vertices[24] = Vertex(glm::vec3(3.0f, 0.f, -.5f), glm::vec2(.0f, 0.0f), negZ);  //bottom outside 20
	vertices[25] = Vertex(glm::vec3(2.0f, 0.f, -.5f), glm::vec2(.4f, 0.0f), negZ);  //bottom  6
	vertices[26] = Vertex(glm::vec3(3.0f, 3.f, -.5f), glm::vec2(0.0f, 1.0f), negZ);  //top outside  21 
	vertices[27] = Vertex(glm::vec3(2.0f, 3.f, -.5f), glm::vec2(.4f, 1.0f), negZ);  //top inside 22

	//left armrest outside face
	vertices[28] = Vertex(glm::vec3(-3.0f, 0.f, -.5f), glm::vec2(.0f, 0.0f), negX);  //bottom outside 17
	vertices[29] = Vertex(glm::vec3(-3.0f, 0.f, 3.5f), glm::vec2(1.4f, 0.0f), negX);  //bottom  23
	vertices[30] = Vertex(glm::vec3(-3.0f, 3.f, -.5f), glm::vec2(0.0f, 1.0f), negX);  //top outside 18
	vertices[31] = Vertex(glm::vec3(-3.0f, 3.f, 3.5f), glm::vec2(1.4f, 1.0f), negX);  //top 24

	//right armrest outside face
	vertices[32] = Vertex(glm::vec3(3.0f, 0.f, 3.5f), glm::vec2(1.4f, 0.0f), posX);  //bottom		25
	vertices[33] = Vertex(glm::vec3(3.0f, 0.f, -.5f), glm::vec2(.0f, 0.0f), posX);  //bottom outside 20
	vertices[34] = Vertex(glm::vec3(3.0f, 3.f, 3.5f), glm::vec2(1.4f, 1.0f), posX);  //top 26
	vertices[35] = Vertex(glm::vec3(3.0f, 3.f, -.5f), glm::vec2(0.0f, 1.0f), posX);  //top outside  21

	//left armrest inwards face top
	vertices[36] = Vertex(glm::vec3(-2.0f, 1.f, -.5f), glm::vec2(1.4f, 1.0f), posX);  //top		5
	vertices[37] = Vertex(glm::vec3(-2.0f, 3.f, -.5f), glm::vec2(1.4f, 0.0f), posX);  //top inside		19
	vertices[38] = Vertex(glm::vec3(-2.0f, 1.f, 3.5f), glm::vec2(0.0f, 1.0f), posX);  //left back	8
	vertices[39] = Vertex(glm::vec3(-2.0f, 3.f, 3.5f), glm::vec2(.0f, 0.0f), posX);  //top inside back	27

	//right armrest inwards face top
	vertices[40] = Vertex(glm::vec3(2.0f, 3.f, -.5f), glm::vec2(1.4f, 1.0f), negX);  //top inside 22
	vertices[41] = Vertex(glm::vec3(2.0f, 1.f, -.5f), glm::vec2(1.4f, 0.0f), negX);  //top 7
	vertices[42] = Vertex(glm::vec3(2.0f, 3.f, 3.5f), glm::vec2(0.0f, 1.0f), negX);  //top inside back	28
	vertices[43] = Vertex(glm::vec3(2.0f, 1.f, 3.5f), glm::vec2(.0f, 0.0f), negX);  //right back	9

	//left armrest top face
	vertices[44] = Vertex(glm::vec3(-3.0f, 3.f, -.5f), glm::vec2(.0f, .0f), posY);  //top outside		18
	vertices[45] = Vertex(glm::vec3(-3.0f, 3.f, 3.5f), glm::vec2(1.4f, .3f), posY);  //top	24 
	vertices[46] = Vertex(glm::vec3(-2.0f, 3.f, -.5f), glm::vec2(.0f, .3f), posY);  //top inside	19
	vertices[47] = Vertex(glm::vec3(-2.0f, 3.f, 3.5f), glm::vec2(1.4f, .0f), posY);  //top inside back	27

	//right armrest top face
	vertices[48] = Vertex(glm::vec3(2.0f, 3.f, 3.5f), glm::vec2(.0f, .0f), posY);  //top inside back	28
	vertices[49] = Vertex(glm::vec3(3.0f, 3.f, 3.5f), glm::vec2(.0f, .3f), posY);  //top	26
	vertices[50] = Vertex(glm::vec3(2.0f, 3.f, -.5f), glm::vec2(1.4f, .3f), posY);  //top inside	22 
	vertices[51] = Vertex(glm::vec3(3.0f, 3.f, -.5f), glm::vec2(1.4f, .0f), posY);  //top outside	21

	//bottom back of chair
	vertices[52] = Vertex(glm::vec3(2.0f, 0.f, 4.5f), glm::vec2(1.0f, 0.0f), posZ);  //bottom right back  37
	vertices[53] = Vertex(glm::vec3(2.0f, 8.f, 4.5f), glm::vec2(1.0f, 0.74f), posZ);  //right p4 back	30
	vertices[54] = Vertex(glm::vec3(-2.0f, 0.f, 4.5f), glm::vec2(0.0f, .0f), posZ);  //bottom left back	36
	vertices[55] = Vertex(glm::vec3(-2.0f, 8.f, 4.5f), glm::vec2(0.0f, .74f), posZ);  //left p1 back		29

	//SIDES OF CHAIRS


	//p1 p2 front back link

	glm::vec3 p1p2Normal = glm::cross(glm::vec3(-2.0f, 8.f, 3.5f) - glm::vec3(-2.0f, 8.f, 4.5f), glm::vec3(-2.0f, 8.f, 3.5f) - glm::vec3(-1.0f, 9.f, 3.5f));
	vertices[56] = Vertex(glm::vec3(-2.0f, 8.f, 3.5f), glm::vec2(0.0f, 0.0f), p1p2Normal);  //left p1	10
	vertices[57] = Vertex(glm::vec3(-2.0f, 8.f, 4.5f), glm::vec2(0.4f, 0.0f), p1p2Normal);  //left p1 back	29
	vertices[58] = Vertex(glm::vec3(-1.0f, 9.f, 3.5f), glm::vec2(0.0f, 1.0f), p1p2Normal);  //p2	12
	vertices[59] = Vertex(glm::vec3(-1.0f, 9.f, 4.5f), glm::vec2(0.4f, 1.0f), p1p2Normal);  //p2 back	31

	//p2 p3 front back link 
	glm::vec3 p2p3Normal = glm::cross(glm::vec3(-.8f, 8.f, 3.5f) - glm::vec3(-.8f, 8.f, 4.5f), glm::vec3(-.8f, 8.f, 3.5f) - glm::vec3(-1.0f, 9.f, 3.5f));
	vertices[60] = Vertex(glm::vec3(-.8f, 8.f, 3.5f), glm::vec2(0.0f, 0.0f), -p2p3Normal);  //p3	13
	vertices[61] = Vertex(glm::vec3(-1.0f, 9.f, 3.5f), glm::vec2(0.0f, 1.0f), -p2p3Normal);  //p2	12
	vertices[62] = Vertex(glm::vec3(-.8f, 8.f, 4.5f), glm::vec2(0.4f, 0.0f), -p2p3Normal);  //p3 back	32
	vertices[63] = Vertex(glm::vec3(-1.0f, 9.f, 4.5f), glm::vec2(0.4f, 1.0f), -p2p3Normal);  //p2 back	31

	//p5 p3 front back link
	glm::vec3 p5p3Normal = glm::cross(glm::vec3(.0f, 10.f, 3.5f) - glm::vec3(-.8f, 8.f, 3.5f), glm::vec3(.0f, 10.f, 3.5f) - glm::vec3(.0f, 10.f, 4.5f));
	vertices[64] = Vertex(glm::vec3(.0f, 10.f, 3.5f), glm::vec2(0.0f, 0.0f), p5p3Normal);  //p5	14
	vertices[65] = Vertex(glm::vec3(-.8f, 8.f, 3.5f), glm::vec2(0.0f, 1.0f), p5p3Normal);  //p3 13
	vertices[66] = Vertex(glm::vec3(.0f, 10.f, 4.5f), glm::vec2(0.4f, 0.0f), p5p3Normal);  //p5 back 33
	vertices[67] = Vertex(glm::vec3(-.8f, 8.f, 4.5f), glm::vec2(0.4f, 1.0f), p5p3Normal);  //p3 back	32


	//p6 p5 front back link
	glm::vec3 p6p5Normal = glm::cross(glm::vec3(-1.0f, 11.f, 3.5f) - glm::vec3(.0f, 10.f, 3.5f), glm::vec3(-1.0f, 11.f, 3.5f) - glm::vec3(-1.0f, 11.f, 4.5f));
	vertices[68] = Vertex(glm::vec3(-1.0f, 11.f, 3.5f), glm::vec2(0.0f, 0.0f), p6p5Normal);  //p6	15
	vertices[69] = Vertex(glm::vec3(.0f, 10.f, 3.5f), glm::vec2(0.0f, 1.0f), p6p5Normal);  //p5	14
	vertices[70] = Vertex(glm::vec3(-1.0f, 11.f, 4.5f), glm::vec2(0.4f, 0.0f), p6p5Normal);  //p6 back	34
	vertices[71] = Vertex(glm::vec3(.0f, 10.f, 4.5f), glm::vec2(0.4f, 1.0f), p6p5Normal);  //p5 back	33

	//p7 p6 front back link	
	glm::vec3 p7p6Normal = glm::cross(glm::vec3(.0f, 12.5f, 3.5f) - glm::vec3(-1.0f, 11.f, 3.5f), glm::vec3(.0f, 12.5f, 3.5f) - glm::vec3(.0f, 12.5f, 4.5f));
	vertices[72] = Vertex(glm::vec3(.0f, 12.5f, 3.5f), glm::vec2(0.0f, 0.0f), p7p6Normal);  //p7	16
	vertices[73] = Vertex(glm::vec3(-1.0f, 11.f, 3.5f), glm::vec2(0.0f, 1.0f), p7p6Normal);  //p6		15
	vertices[74] = Vertex(glm::vec3(.0f, 12.5f, 4.5f), glm::vec2(0.4f, 0.0f), p7p6Normal);  //p7 back	35
	vertices[75] = Vertex(glm::vec3(-1.0f, 11.f, 4.5f), glm::vec2(0.4f, 1.0f), p7p6Normal);  //p6 back	34

	//p7 p4 front back link 
	glm::vec3 p7p4Normal = glm::cross(glm::vec3(.0f, 12.5f, 3.5f) - glm::vec3(.0f, 12.5f, 4.5f), glm::vec3(.0f, 12.5f, 3.5f) - glm::vec3(2.0f, 8.f, 3.5f));
	vertices[76] = Vertex(glm::vec3(.0f, 12.5f, 3.5f), glm::vec2(0.0f, 1.0f), p7p4Normal);  //p7	16
	vertices[77] = Vertex(glm::vec3(.0f, 12.5f, 4.5f), glm::vec2(0.4f, 1.0f), p7p4Normal);  //p7 back	35
	vertices[78] = Vertex(glm::vec3(2.0f, 8.f, 3.5f), glm::vec2(0.0f, 0.0f), p7p4Normal);  //right p4	11
	vertices[79] = Vertex(glm::vec3(2.0f, 8.f, 4.5f), glm::vec2(0.4f, 0.0f), p7p4Normal);  //right p4 back	30



	//left side of chair back
	vertices[80] = Vertex(glm::vec3(-2.0f, 8.f, 3.5f), glm::vec2(.4f, 0.74f), negX);  //left p1	10
	vertices[81] = Vertex(glm::vec3(-2.0f, 1.f, 3.5f), glm::vec2(.4f, 0.0f), negX);  //left back	8
	vertices[82] = Vertex(glm::vec3(-2.0f, 8.f, 4.5f), glm::vec2(.0f, 0.74f), negX);  //left p1 back	29
	vertices[83] = Vertex(glm::vec3(-2.0f, 0.f, 4.5f), glm::vec2(.0f, 0.0f), negX);  //bottom left back	36

	//right side of chair back
	vertices[84] = Vertex(glm::vec3(2.0f, 8.f, 3.5f), glm::vec2(.4f, 0.74f), posX);  //right p4	11
	vertices[85] = Vertex(glm::vec3(2.0f, 8.f, 4.5f), glm::vec2(.0f, 0.74f), posX);  //right p4 back	30
	vertices[86] = Vertex(glm::vec3(2.0f, 1.f, 3.5f), glm::vec2(.4f, 0.0f), posX);  //right back	9
	vertices[87] = Vertex(glm::vec3(2.0f, 0.f, 4.5f), glm::vec2(.0f, 0.0f), posX);  //bottom right back	37

	//BACK OF ARMREST
	//left
	vertices[89] = Vertex(glm::vec3(-2.0f, 1.f, 3.5f), glm::vec2(.0f, 0.0f), posZ);  //left back	8
	vertices[88] = Vertex(glm::vec3(-3.0f, 0.f, 3.5f), glm::vec2(.4f, 0.0f), posZ);  //bottom 23
	vertices[90] = Vertex(glm::vec3(-3.0f, 3.f, 3.5f), glm::vec2(.4f, 1.0f), posZ);  //top	24
	vertices[91] = Vertex(glm::vec3(-2.0f, 3.f, 3.5f), glm::vec2(.0f, 1.0f), posZ);  //top inside back	27

	//right
	vertices[92] = Vertex(glm::vec3(2.0f, 1.f, 3.5f), glm::vec2(.0f, 0.0f), posZ);  //right back	9
	vertices[93] = Vertex(glm::vec3(3.0f, 0.f, 3.5f), glm::vec2(.4f, 0.0f), posZ);  //bottom	25
	vertices[94] = Vertex(glm::vec3(2.0f, 3.f, 3.5f), glm::vec2(.0f, 1.0f), posZ);  //top inside back	28
	vertices[95] = Vertex(glm::vec3(3.0f, 3.f, 3.5f), glm::vec2(.4f, 1.0f), posZ);  //top		26

	//BOTTOM
	//middle bottom
	vertices[96] = Vertex(glm::vec3(-3.0f, 0.f, -.5f), t00, negY);  //bottom outside		17
	vertices[97] = Vertex(glm::vec3(3.0f, 0.f, -.5f), t01, negY);  //bottom outside		20
	vertices[98] = Vertex(glm::vec3(-2.0f, 0.f, 4.5f), t10, negY);  //bottom left back	36
	vertices[99] = Vertex(glm::vec3(2.0f, 0.f, 4.5f), t11, negY);  //bottom right back	37

	//ALL TRIANGLE FACES
	//p1,p2,p3 triangle
	vertices[100] = Vertex(glm::vec3(-2.0f, 8.f, 3.5f), glm::vec2(0.0f, .74f), negZ);  //left p1 10
	vertices[101] = Vertex(glm::vec3(-1.0f, 9.f, 3.5f), glm::vec2(0.25f, .83f), negZ);  //p2	12
	vertices[102] = Vertex(glm::vec3(-.8f, 8.f, 3.5f), glm::vec2(0.3f, .74f), negZ);  //p3	13

	//p3,p5,p4 triangle
	vertices[103] = Vertex(glm::vec3(-.8f, 8.f, 3.5f), glm::vec2(0.3f, .74f), negZ);  //p3	13
	vertices[104] = Vertex(glm::vec3(.0f, 10.f, 3.5f), glm::vec2(0.5f, .87f), negZ);  //p5	14
	vertices[105] = Vertex(glm::vec3(2.0f, 8.f, 3.5f), glm::vec2(1.0f, .74f), negZ);  //right p4	11

	//p4,p6,p7 triangle
	vertices[106] = Vertex(glm::vec3(2.0f, 8.f, 3.5f), glm::vec2(1.0f, .74f), negZ);  //right p4	11
	vertices[107] = Vertex(glm::vec3(-1.0f, 11.f, 3.5f), glm::vec2(0.25f, .94f), negZ);  //p6	15
	vertices[108] = Vertex(glm::vec3(.0f, 12.5f, 3.5f), glm::vec2(0.5f, .99f), negZ);  //p7 16

	//BACK OF CHAIRS 
	//p1,p2,p3 triangle   
	vertices[109] = Vertex(glm::vec3(-2.0f, 8.f, 4.5f), glm::vec2(0.0f, .74f), posZ);  //left p1 back	29
	vertices[110] = Vertex(glm::vec3(-.8f, 8.f, 4.5f), glm::vec2(0.3f, .74f), posZ);  //p3 back	32
	vertices[111] = Vertex(glm::vec3(-1.0f, 9.f, 4.5f), glm::vec2(0.25f, .83f), posZ);  //p2 back	31

	//p3,p5,p4 triangle 
	vertices[112] = Vertex(glm::vec3(-.8f, 8.f, 4.5f), glm::vec2(0.3f, .74f), posZ);  //p3 back	32
	vertices[113] = Vertex(glm::vec3(2.0f, 8.f, 4.5f), glm::vec2(1.0f, .74f), posZ);  //right p4 back	30
	vertices[114] = Vertex(glm::vec3(.0f, 10.f, 4.5f), glm::vec2(0.5f, .87f), posZ);  //p5 back	33

	//p4,p6,p7 triangle
	vertices[115] = Vertex(glm::vec3(2.0f, 8.f, 4.5f), glm::vec2(1.0f, .74f), posZ);  //right p4 back	30
	vertices[116] = Vertex(glm::vec3(.0f, 12.5f, 4.5f), glm::vec2(0.5f, .99f), posZ);  //p7 back	35
	vertices[117] = Vertex(glm::vec3(-1.0f, 11.f, 4.5f), glm::vec2(0.25f, .94f), posZ);  //p6 back	34

	//SIDES OF CHAIRS
	//left chair corner		
	glm::vec3 leftCornerNormal = glm::cross(glm::vec3(-2.0f, 1.f, 3.5f) - glm::vec3(-3.0f, 0.f, 3.5f), glm::vec3(-2.0f, 1.f, 3.5f) - glm::vec3(-2.0f, 0.f, 4.5f));
	vertices[118] = Vertex(glm::vec3(-2.0f, 1.f, 3.5f), glm::vec2(0.1f, 0.4f), leftCornerNormal);  //left back	8
	vertices[119] = Vertex(glm::vec3(-3.0f, 0.f, 3.5f), glm::vec2(0.2f, 0.0f), leftCornerNormal);  //bottom		23
	vertices[120] = Vertex(glm::vec3(-2.0f, 0.f, 4.5f), glm::vec2(0.0f, 0.0f), leftCornerNormal);  //bottom left back	36

	//right chair corner
	glm::vec3 rightCornerNormal = glm::cross(glm::vec3(2.0f, 1.f, 3.5f) - glm::vec3(2.0f, 0.f, 4.5f), glm::vec3(2.0f, 1.f, 3.5f) - glm::vec3(3.0f, 0.f, 3.5f));
	vertices[121] = Vertex(glm::vec3(2.0f, 1.f, 3.5f), glm::vec2(0.1f, 0.4f), rightCornerNormal);  //right back	9
	vertices[122] = Vertex(glm::vec3(2.0f, 0.f, 4.5f), glm::vec2(0.0f, 0.0f), rightCornerNormal);  //bottom right back	37
	vertices[123] = Vertex(glm::vec3(3.0f, 0.f, 3.5f), glm::vec2(0.2f, 0.0f), rightCornerNormal);  //bottom	25

	//CHAIR UNDERSIDE
	//left
	vertices[124] = Vertex(glm::vec3(-3.0f, 0.f, -.5f), t00, negY);  //bottom outside		17
	vertices[125] = Vertex(glm::vec3(-2.0f, 0.f, 4.5f), t01, negY);  //bottom left back	36
	vertices[126] = Vertex(glm::vec3(-3.0f, 0.f, 3.5f), t10, negY);  //bottom		23

	//right
	vertices[127] = Vertex(glm::vec3(3.0f, 0.f, -.5f), t00, negY);  //bottom outside 
	vertices[128] = Vertex(glm::vec3(3.0f, 0.f, 3.5f), glm::vec2(0.0f, .2f), negY);  //bottom 
	vertices[129] = Vertex(glm::vec3(2.0f, 0.f, 4.5f), glm::vec2(.2f, 0.0f), negY);  //bottom right back

	m_numTriangles = size(vertices);
	// t00, glm::vec3(0.0f, 0.0f, 1.0f)

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//textures
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	//normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}

void CThrone::Render()
{
	glBindVertexArray(m_vao);
	m_texture.Bind();
	// Call glDrawArrays to render each side
	for (int i = 0; i < 99; i += 4) {
		glDrawArrays(GL_TRIANGLE_STRIP, i, 4);
	}
	for (int i = 100; i < m_numTriangles; i += 3) {
		glDrawArrays(GL_TRIANGLE_STRIP, i, 3);

	}



	//glDrawElements(GL_TRIANGLES, m_numTriangles * 3, GL_UNSIGNED_INT, nullptr);
}


void CThrone::Release()
{
	m_texture.Release();
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	//m_vbo.Release();
}




//struct Vertex {
//	glm::vec3 pos;
//	glm::vec2 tex;
//
//	Vertex() {}
//
//	Vertex(const glm::vec3& pos_, const glm::vec2& tex_)
//	{
//		pos = pos_;
//		tex = tex_;
//	}
//};
//
//CThrone::CThrone()
//{}
//CThrone::~CThrone()
//{
//	Release();
//}
//
//void CThrone::Create(string filename)
//{
//
//	//	m_texture.Load(filename);
//	//	m_texture.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER,
//	//		GL_LINEAR_MIPMAP_LINEAR);
//	//	m_texture.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		//m_texture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
//	///	m_texture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glGenVertexArrays(1, &m_vao);
//	glBindVertexArray(m_vao);
//
//	//VBO Object Data
//
//	Vertex vertices[100];
//
//	glm::vec2 t00 = glm::vec2(0.0f, 0.0f); //Bottom Left
//	glm::vec2 t01 = glm::vec2(0.0f, 1.0f); //Top Left
//	glm::vec2 t10 = glm::vec2(1.0f, 0.0f); //Bottom Right
//	glm::vec2 t11 = glm::vec2(1.0f, 1.0f); //Top Right
//	glm::vec2 placeholder = glm::vec2(.5f, .5f);
//
//	//Seat front Face
//	vertices[0] = Vertex(glm::vec3(-2.0f, 0.f, 0.f), placeholder); //bottom left front
//	vertices[1] = Vertex(glm::vec3(-2.0f, 1.f, 0.f), placeholder); //top left front
//	vertices[2] = Vertex(glm::vec3(2.0f, 1.f, 0.f), placeholder);  //top right front
//	vertices[3] = Vertex(glm::vec3(2.0f, 0.f, 0.f), placeholder);  //bottom right front
//
//	//left armrest inwards face
//	vertices[4] = Vertex(glm::vec3(-2.0f, 0.f, -.5f), placeholder);  //bottom 
//	vertices[5] = Vertex(glm::vec3(-2.0f, 1.f, -.5f), placeholder);  //top
//
//	//right armrest inwards face
//	vertices[6] = Vertex(glm::vec3(2.0f, 0.f, -.5f), placeholder);  //bottom 
//	vertices[7] = Vertex(glm::vec3(2.0f, 1.f, -.5f), placeholder);  //top
//
//	//Seat top
//	vertices[8] = Vertex(glm::vec3(-2.0f, 1.f, 3.5f), placeholder);  //left back
//	vertices[9] = Vertex(glm::vec3(2.0f, 1.f, 3.5f), placeholder);  //right back
//
//	//seat backing first section
//	vertices[10] = Vertex(glm::vec3(-2.0f, 8.f, 3.5f), placeholder);  //left p1
//	vertices[11] = Vertex(glm::vec3(2.0f, 8.f, 3.5f), placeholder);  //right p4
//
//	//top of chair complex bit
//
//	vertices[12] = Vertex(glm::vec3(-1.0f, 9.f, 3.5f), placeholder);  //p2
//	vertices[13] = Vertex(glm::vec3(-.8f, 8.f, 3.5f), placeholder);  //p3
//	vertices[14] = Vertex(glm::vec3(.0f, 10.f, 3.5f), placeholder);  //p5
//	vertices[15] = Vertex(glm::vec3(-1.0f, 11.f, 3.5f), placeholder);  //p6
//	vertices[16] = Vertex(glm::vec3(.0f, 12.5f, 3.5f), placeholder);  //p7
//
//	//left arm front 
//	vertices[17] = Vertex(glm::vec3(-3.0f, 0.f, -.5f), placeholder);  //bottom outside 
//	vertices[18] = Vertex(glm::vec3(-3.0f, 3.f, -.5f), placeholder);  //top outside 
//	vertices[19] = Vertex(glm::vec3(-2.0f, 3.f, -.5f), placeholder);  //top inside 
//
//	//right arm front 
//	vertices[20] = Vertex(glm::vec3(3.0f, 0.f, -.5f), placeholder);  //bottom outside 
//	vertices[21] = Vertex(glm::vec3(3.0f, 3.f, -.5f), placeholder);  //top outside 
//	vertices[22] = Vertex(glm::vec3(2.0f, 3.f, -.5f), placeholder);  //top inside 
//
//	//left arm outside face
//	vertices[23] = Vertex(glm::vec3(-3.0f, 0.f, 3.5f), placeholder);  //bottom 
//	vertices[24] = Vertex(glm::vec3(-3.0f, 3.f, 3.5f), placeholder);  //top 
//
//	//right arm outside face
//	vertices[25] = Vertex(glm::vec3(3.0f, 0.f, 3.5f), placeholder);  //bottom 
//	vertices[26] = Vertex(glm::vec3(3.0f, 3.f, 3.5f), placeholder);  //top 
//
//	//left arm inside face top 
//	vertices[27] = Vertex(glm::vec3(-2.0f, 3.f, 3.5f), placeholder);  //top inside back
//
//	//right arm inside face top 
//	vertices[28] = Vertex(glm::vec3(2.0f, 3.f, 3.5f), placeholder);  //top inside back
//
//	//behind chair vertices 
//	vertices[29] = Vertex(glm::vec3(-2.0f, 8.f, 4.5f), placeholder);  //left p1 back
//	vertices[30] = Vertex(glm::vec3(2.0f, 8.f, 4.5f), placeholder);  //right p4 back
//	vertices[31] = Vertex(glm::vec3(-1.0f, 9.f, 4.5f), placeholder);  //p2 back
//	vertices[32] = Vertex(glm::vec3(-.8f, 8.f, 4.5f), placeholder);  //p3 back
//	vertices[33] = Vertex(glm::vec3(.0f, 10.f, 4.5f), placeholder);  //p5 back
//	vertices[34] = Vertex(glm::vec3(-1.0f, 11.f, 4.5f), placeholder);  //p6 back
//	vertices[35] = Vertex(glm::vec3(.0f, 12.5f, 4.5f), placeholder);  //p7 back
//
//	//Bottom of back of chair 
//	vertices[36] = Vertex(glm::vec3(-2.0f, 0.f, 4.5f), placeholder);  //bottom left back
//	vertices[37] = Vertex(glm::vec3(2.0f, 0.f, 4.5f), placeholder);  //bottom right back
//
//
//	//indicies 
//
//	unsigned int indicies[] = {
//		//SEAT
//		0,1,2,		2,3,0,		//Seat front Face
//		0,4,5,		5,1,0,		//left armrest inwards face
//		3,7,6,		7,3,2,		//right armrest inwards face
//		1,8,9,		9,2,1,		//seat top
//
//		//CHAIR BACK
//		8,10,11,	11,9,8,		//set backing first section
//		10,12,13,				//p1,p2,p3 triangle
//		13,14,11,				//p3,p5,p4 triangle
//		11,15,16,				//p4,p6,p7 triangle
//
//		//ARMRESTS
//		4,17,18,	4,18,19,	//left armrest frontwards face
//		6,21,20,	6,22,21,	//right armrest frontwards face
//		17,23,24,   17,24,18,	//left armrest outside face
//		20,26,25,	20,21,26,	//right armrest outside face
//		5,19,27,	5,27,8,		//left armrest inwards face top
//		7,28,22,	7,9,28,		//right armrest inwards face top
//		24,27,18,	18,27,19,	//left armrest top face
//		26,21,28,	21,22,28,	//right armrest top face
//
//		//BACK OF CHAIRS 
//		29,32,31,				//p1,p2,p3 triangle   
//		32,30,33,				//p3,p5,p4 triangle 
//		30,35,34,				//p4,p6,p7 triangle
//		29,36,37,	29,37,30,	//bottom back of chair
//
//		//SIDES OF CHAIRS
//		10,31,12,   31,10,29,	//p1 p2 front back link 
//		12,32,13,  	12,31,32,	//p2 p3 front back link 
//		14,13,33,   33,13,32,	//p5 p3 front back link
//		15,14,34,   34,14,33,	//p6 p5 front back link
//		16,15,35,  	35,15,34,	//p7 p6 front back link
//		16,35,11,   35,30,11,	//p7 p4 front back link 
//
//		10,36,29,   10,8,36,	//left side of chair back
//		11,30,37,	11,37,9,	//right side of chair back
//
//		8,23,36,				//left chair corner	
//		9,37,25,				//right chair corner
//
//		//BACK OF ARMREST
//		8,24,23, 8,27,24,		//left
//		9,25,26, 9,26,28,		//right
//
//		//CHAIR UNDERSIDE
//		17,37,36, 17,20,37,		//middle bottom
//		17,36,23,				//left
//		20,25,37				//right
//	};
//	m_numTriangles = size(indicies) / 3;
//
//
//	//Normals 
//
//	//Texture Coords (later)
//
//
//	//Load into VAO
//	glGenBuffers(1, &m_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	//positions
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
//
//	//textures
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
//
//	//
//
//	//Create and load indicie buffer data 
//	glGenBuffers(1, &m_ibo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
//
//	//	glGenBuffers(1, &m_ibo);
//		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
//	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indicies), indicies, GL_STATIC_DRAW);
//
//	glBindVertexArray(0);
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//
//
//}
//
//
//
//void CThrone::Render()
//{
//	glBindVertexArray(m_vao);
//	m_texture.Bind();
//	// Call glDrawArrays to render each side
//	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//
//	glDrawElements(GL_TRIANGLES, m_numTriangles * 3, GL_UNSIGNED_INT, nullptr);
//
//}
//
//
//void CThrone::Release()
//{
//	m_texture.Release();
//	glDeleteVertexArrays(1, &m_vao);
//	//m_vbo.Release();
//}
//
