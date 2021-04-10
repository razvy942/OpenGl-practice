#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight();
	PointLight(float red, float green, float blue, 
		float aIntensity, float dIntensity,
		float xPos, float yPos, float zPos,
		float con, float lin, float exp);
	
	void useLight(float ambientIntensityLocation, float ambientColourLocation, 
		float diffuseIntensityLocation, float positionLocation,
		float constantLocation, float linearLocation, float exponentLocation);

	~PointLight();

protected:
	glm::vec3 position;

	float constant, linear, exponent;
};

