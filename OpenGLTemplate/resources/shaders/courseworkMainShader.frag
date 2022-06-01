#version 400

in vec3 Position;
in vec3 Normal;
in vec2 vTexCoord;
in vec3 worldPosition;
in mat3 TBN;
smooth in float ioHeight;


struct LightInfo
{
	vec4 Position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};

struct PointLight
{
	vec4 Position;
	//vec3 Colour;
	vec3 La;
	vec3 Ld;
	vec3 Ls;

	float constant;
    float linear;
    float quadratic;
};



struct MaterialInfo
{
	vec3 Ma;
	vec3 Md;
	vec3 Ms;
	float shininess;
};

uniform LightInfo mainLight; 
uniform PointLight playerLight;
uniform PointLight npcLight;

uniform MaterialInfo material1;



uniform sampler2D sampler0;  // The texture sampler
uniform sampler2D sampler1; 
uniform sampler2D sampler2; 
uniform sampler2D sampler3; 
uniform sampler2D sampler4;  



//Skybox Texture
uniform samplerCube CubeMapTex;


uniform float fMinHeight, fMaxHeight;
uniform bool isTerrain;
uniform bool renderSkybox;
uniform bool isCharacter;
uniform bool isWater;
uniform bool isNormalMapped;


vec3 lightingNormal;

uniform vec3 cameraPos;

out vec4 vOutputColour;	

float getBlend(float height, float max,float min){
   return clamp((height - min) / (max - min), 0,1);
}


vec3 phong()
{
  vec3 n = normalize( lightingNormal );
  vec3 s = normalize( vec3(mainLight.Position) - Position );
  vec3 v = normalize(vec3(-Position));
  vec3 r = reflect( -s, n );
  return  vec3(.3f) *( mainLight.La + mainLight.Ld * max( dot(s, n), 0.0 ) + mainLight.Ls * pow( max( dot(r,v), 0.0 ), material1.shininess ) );
}

vec3 pointLightPhong(){
  vec3 n = normalize( lightingNormal );
  vec3 s = normalize( vec3(playerLight.Position) - Position );
  vec3 v = normalize(vec3(-Position));
  vec3 r = reflect( -s, n );

 float distance    = length(vec3(playerLight.Position) - Position);
 float attenuation = 1.0 / (playerLight.constant + playerLight.linear * distance + 
  			     playerLight.quadratic * (distance * distance));    

 vec3 color = vec3(0.52157,  0.06275 , 0.03137);

  return  color*vec3(.9f) *( playerLight.La + playerLight.Ld * max( dot(s, n), 0.0 ) + playerLight.Ls * pow( max( dot(r,v), 0.0 ), material1.shininess ) )*(attenuation*300);
}

//Temp for the demo submission
vec3 pointLightPhongNPC(){
  vec3 n = normalize( lightingNormal );
  vec3 s = normalize( vec3(npcLight.Position) - Position );
  vec3 v = normalize(vec3(-Position));
  vec3 r = reflect( -s, n );

 float distance    = length(vec3(npcLight.Position) - Position);
 float attenuation = 1.0 / (npcLight.constant + npcLight.linear * distance + 
  			     npcLight.quadratic * (distance * distance));    

 vec3 color = vec3(0.74118,  0.61569 , 0.00000);

  return  color*vec3(.9f) *( npcLight.La + npcLight.Ld * max( dot(s, n), 0.0 ) + npcLight.Ls * pow( max( dot(r,v), 0.0 ), material1.shininess ) )*(attenuation*300);
}

void main() {

    if(isNormalMapped){
    lightingNormal = texture(sampler1,vTexCoord).rgb;
    lightingNormal = lightingNormal * 2.0 - 1.0;
    lightingNormal = normalize(TBN * lightingNormal);
    }
    else{
    lightingNormal = Normal;
    }
    


    if (isTerrain) {
    vec4 vTexColour0 = texture(sampler0, vTexCoord);
    vec4 vTexColour1 = texture(sampler1, vTexCoord);
    vec4 vTexColour2 = texture(sampler2, vTexCoord);
    vec4 vTexColour3 = texture(sampler3, vTexCoord);
    vec4 vTexColour4 = texture(sampler4, vTexCoord);


    float f = clamp(4*(ioHeight - (-90)) / (95 - (-90)), 0, 4);
    vec4 vTexColour;
    if (f < 1)
    vTexColour = mix(vTexColour4, vTexColour3, f);
    else if (f < 2)
    vTexColour = mix(vTexColour3, vTexColour2, f - 1.0);
    else if(f<3)
    vTexColour = mix(vTexColour2, vTexColour1, f - 2.0);
    else
    vTexColour = mix(vTexColour1, vTexColour0, f - 3.0);

    vOutputColour = vTexColour* vec4(phong()+pointLightPhong()+pointLightPhongNPC(), 1.0f);

    }
    
    else if(renderSkybox){
    	vOutputColour = texture(CubeMapTex, worldPosition);

}


    else if(isCharacter){
    vec4 vTexColour = texture(sampler0, vTexCoord);	
    vOutputColour = vTexColour * vec4(phong()*4, 1.0f);

    }
    
    else if(isWater){

    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    vOutputColour = vec4(texture(CubeMapTex, R).rgb, 1.0);

}
    
    else{

    vec4 vTexColour = texture(sampler0, vTexCoord);	
    vOutputColour = vTexColour * vec4(phong()+pointLightPhong()+pointLightPhongNPC(), 1.0f);

    }
}