#version 400

in vec3 Position;
in vec3 Normal;
in vec4 clipSpace;

uniform samplerCube cubeMapTex;
uniform sampler2D sampler0;  // The texture sampler
uniform vec3 cameraPos;


out vec4 vOutputColour;	


void main() {
    
    vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
    vec2 refractCoords = vec2(ndc.x,ndc.y);

    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));


    vec4 refraction = texture(sampler0, refractCoords);	
    vec4 reflection = vec4(texture(cubeMapTex, R).rgb, 1.0);

    vOutputColour = mix(reflection,refraction,0.55);

    

    //vOutputColour = vec4(texture(cubeMapTex, vTexCoord));
}