#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

// Ambient lighting and diffuse light
class Light
{
public:
	Light();
	Light(float red, float green, float blue, float aIntensity, float xDir, float yDir, float zDir, float dIntensity);

	void useLight(float ambientIntensityLocation, float ambientColourLocation, float diffuseIntensityLocation, float directionLocation);

	~Light();

private:
	glm::vec3 colour;
	float ambientIntensity; 

	glm::vec3 direction;	// Needed for diffuse lighting
	float diffuseIntensity;
};

