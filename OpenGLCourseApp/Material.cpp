#include "Material.h"

Material::Material()
{
	specularIntensity = 0;
	shininess = 0;
}

Material::Material(float sIntensity, float shine)
{
	specularIntensity = sIntensity;
	shininess = shine;
}


void Material::useMaterial(unsigned int specularIntensityLocation, unsigned int shininessLocation)
{
	glUniform1f(specularIntensityLocation, specularIntensity);
	glUniform1f(shininessLocation, shininess);
}

Material::~Material()
{}