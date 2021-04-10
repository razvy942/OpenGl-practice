#pragma once

#include "Light.h"

class DirectionalLight: public Light
{
public:
	DirectionalLight();

	DirectionalLight(float red, float green, float blue, 
		float aIntensity, float dIntensity, 
		float xDir, float yDir, float zDir);


	void useLight(float ambientIntensityLocation, float ambientColourLocation, float diffuseIntensityLocation, float directionLocation);

	~DirectionalLight();

private:
	glm::vec3 direction;	// Needed for diffuse lighting
};

