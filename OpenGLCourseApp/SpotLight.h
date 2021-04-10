#pragma once

#include "PointLight.h"


class SpotLight :
    public PointLight
{
public:
	SpotLight();
	SpotLight(float red, float green, float blue,
		float aIntensity, float dIntensity,
		float xPos, float yPos, float zPos,
		float xDir, float yDir, float zDir,
		float con, float lin, float exp,
		float edge);

	void useLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
		unsigned int diffuseIntensityLocation, unsigned int positionLocation, unsigned int directionLocation,
		unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation, unsigned int edgeLocation);

    
    ~SpotLight();

private:
    glm::vec3 direction;

    float edge, procEdge;
};

