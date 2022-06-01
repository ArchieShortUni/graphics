#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 inCoord;
layout (location = 2) in vec3 VertexNormal;
layout (location = 3) in vec3 Tangent;
layout (location = 4) in vec3 BiTangent;


out vec3 Position;
out vec3 Normal;
out vec2 vTexCoord;	
out mat3 TBN;

out vec3 worldPosition;	// used for skybox

smooth out float ioHeight;

uniform mat4 modelMatrix; 
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 projMatrix;

const vec4 plane = vec4(0,-1,0, -30.0f);
uniform bool isRefraction;
uniform bool renderSkybox;

void main()
{
    	
    vec3 T = normalize(vec3(modelMatrix)*Tangent);
    vec3 B = normalize(vec3(modelMatrix)*BiTangent);
    vec3 N = normalize(vec3(modelMatrix)*VertexNormal);
     TBN = mat3(T,B,N);
    

    worldPosition = VertexPosition;  

    if(isRefraction){
    if(!renderSkybox){
    gl_ClipDistance[0] = dot(modelMatrix*vec4(VertexPosition,1.0),plane);}}

    Normal = normalize( normalMatrix * VertexNormal);
    Position = vec3( modelMatrix *  vec4(VertexPosition,1.0) );
    gl_Position = projMatrix * modelViewMatrix * vec4(VertexPosition,1.0);
    ioHeight = VertexPosition.y;	
    vTexCoord = inCoord;

}