#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 colour;

const int MAX_POINT_LIGHTS = 3;

struct Light 
{
	vec3 colour;
	float ambientIntensity; 
	float diffuseIntensity;
};

struct DirectionalLight 
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponant;
};

struct Material
{
	float specularIntensity;	
	float shininess;
};

uniform int pointLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform sampler2D theTexture;
uniform Material material;

uniform vec3 eyePosition;

vec4 calcLightByDirection(Light light, vec3 direction)
{
	vec4 ambientColour = vec4(light.colour, 1.0) * light.ambientIntensity;
																							//																		   ***vecs are normalized so |v1| * |v2| = 1***
	float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);	// this gives us the cos(theta) between normal vector and direction vector *** v1 . v2 = |v1| * |v2| cos(theta)***
	vec4 diffuseColour = vec4(light.colour, 1.0f) * light.diffuseIntensity * diffuseFactor;
	
	vec4 specularColour = vec4(0, 0, 0, 0);

	if(diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
		float specularFactor = dot(fragToEye, reflectedVertex);
		if (specularFactor > 0)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
		}
	}

	return (ambientColour + diffuseColour + specularColour);
}

vec4 calcDirectionalLight()
{
	return calcLightByDirection(directionalLight.base, directionalLight.direction);
}

void main()
{

	vec4 finalColour = calcDirectionalLight();
	colour = texture(theTexture, TexCoord) * finalColour;
}