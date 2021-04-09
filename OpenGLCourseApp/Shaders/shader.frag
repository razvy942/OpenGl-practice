#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;

out vec4 colour;

struct DirectionalLight {
	vec3 colour;
	float ambientIntensity; 
	vec3 direction;
	float diffuseIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientColour = vec4(directionalLight.colour, 1.0) * directionalLight.ambientIntensity;
																							//																		   ***vecs are normalized so |v1| * |v2| = 1***
	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);	// this gives us the cos(theta) between normal vector and direction vector *** v1 . v2 = |v1| * |v2| cos(theta)***
	vec4 diffuseColour = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;
	
	colour = texture(theTexture, TexCoord) * (ambientColour + diffuseColour);
}