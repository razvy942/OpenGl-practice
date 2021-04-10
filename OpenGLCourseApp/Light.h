#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

// Ambient lighting and diffuse light
class Light
{
public:
	Light();
	Light(float red, float green, float blue, float aIntensity, float dIntensity);

	~Light();

protected:
	glm::vec3 colour;
	float ambientIntensity; 

	// glm::vec3 direction;	// Needed for diffuse lighting
	float diffuseIntensity;
};

