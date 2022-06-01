#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 inCoord;
layout (location = 2) in vec3 VertexNormal;

out vec3 Position;
out vec3 Normal;
out vec2 vTexCoord;	


uniform mat4 viewMatrix;
uniform mat3 normalMatrix;
uniform mat4 projMatrix;

uniform mat4 modelMatrixes[200];


uniform bool isRefraction;

const vec4 plane = vec4(0,-1,0, -30.0f);

void main()
{


    mat4 modelMatrix = modelMatrixes[gl_InstanceID];

    if(isRefraction){
    gl_ClipDistance[0] = dot(modelMatrix*vec4(VertexPosition,1.0),plane);}

  
    Normal = normalize( normalMatrix * VertexNormal);

    Position = vec3( modelMatrix* vec4(VertexPosition,1.0) );

    gl_Position = projMatrix * viewMatrix *modelMatrix* vec4(VertexPosition,1.0); 


    vTexCoord = inCoord;

}