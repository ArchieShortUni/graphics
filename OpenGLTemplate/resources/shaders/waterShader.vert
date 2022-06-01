#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 inCoord;
layout (location = 2) in vec3 VertexNormal;

out vec3 Position;
out vec3 Normal;
out vec4 clipSpace;

out vec3 worldPosition;	// used for skybox


uniform mat4 modelMatrix; 
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 projMatrix;


void main()
{
    	

    worldPosition = VertexPosition;  
    Normal = normalize( normalMatrix * VertexNormal);
    Position = vec3( modelMatrix *  vec4(VertexPosition,1.0) );

    clipSpace = projMatrix * modelViewMatrix  * vec4(VertexPosition,1.0);
    gl_Position = clipSpace;

}