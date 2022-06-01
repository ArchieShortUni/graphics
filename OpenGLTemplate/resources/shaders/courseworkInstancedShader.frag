#version 400

in vec3 Position;
in vec3 viewPos;
in vec3 Normal;
in vec2 vTexCoord;



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




out vec4 vOutputColour;	

vec3 phong()
{
  vec3 n = normalize( Normal );
  vec3 s = normalize( vec3(mainLight.Position) - Position );
  vec3 v = normalize(vec3(-Position));
  vec3 r = reflect( -s, n );
  return  vec3(.3f) *( mainLight.La + mainLight.Ld * max( dot(s, n), 0.0 ) + mainLight.Ls * pow( max( dot(r,v), 0.0 ), material1.shininess ) );
}

vec3 pointLightPhong(){
  vec3 n = normalize( Normal );
  vec3 s = normalize( vec3(playerLight.Position) - Position );
  vec3 v = normalize(vec3(-Position));
  vec3 r = reflect( -s, n );

 float distance    = length(vec3(playerLight.Position) - Position);
 float attenuation = 1.0 / (playerLight.constant + playerLight.linear * distance + 
  			     playerLight.quadratic * (distance * distance));    

 vec3 color = vec3(0.52157 , 0.06275,  0.03137);

  return  color*vec3(.9f) *( playerLight.La + playerLight.Ld * max( dot(s, n), 0.0 ) + playerLight.Ls * pow( max( dot(r,v), 0.0 ), material1.shininess ) )*(attenuation*300);
}

//Temp for the demo submission
vec3 pointLightPhongNPC(){
  vec3 n = normalize( Normal );
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

    vec4 vTexColour = texture(sampler0, vTexCoord);	

     vOutputColour = vTexColour * vec4(phong()+pointLightPhong()+pointLightPhongNPC(), 1.0f);
 
}