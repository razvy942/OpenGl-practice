#pragma once

#include <GL\glew.h>

#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(char* fileLoc);

	void LoadTexture(GLenum texType);
	void UseTexture();
	void ClearTexture();

	~Texture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	char* fileLocation;
};

