#pragma once

#include "Shader.h"
#include "IndependentMesh.h"
#include "ComplexObject.h"

class Utils
{
public:
	Utils();

	float toRadians(float deg);

	ComplexObject* CreateLetterP(GLuint uniformModel);
	ComplexObject* CreateLetterR(GLuint uniformModel);
	ComplexObject* CreateNumber2(GLuint uniformModel);
	ComplexObject* CreateNumber4(GLuint uniformModel);

	void createSphere(IndependentMesh* mesh);
	void createCylinder(IndependentMesh* mesh);

	void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, float* vertices,
		unsigned int vertexCount, unsigned int vLength, unsigned int normalOffset);

	
	/// <summary>
	/// Creates characters representing the first and last letter of each team member's name, and the first and last digit of their student ID.
	/// This then adds those created objects to the object list.
	/// </summary>
	/// <param name="shader">The shader that will be used to render the objects</param>
	void CreateLetters(unsigned int modelLocation, std::vector<ComplexObject*>* objectList);

private:
	// Cube vertices
	float vertices[196] = {
		-0.5, -0.5,  0.5, 0.0, 0.0,		0.0f, 0.0f, 0.0f,
		 0.5, -0.5,  0.5, 1.0, 0.0,		0.0f, 0.0f, 0.0f,
		 0.5,  0.5,  0.5, 1.0, 1.0,		0.0f, 0.0f, 0.0f,
		-0.5,  0.5,  0.5, 0.0, 1.0,		0.0f, 0.0f, 0.0f,
		// top							
		-0.5,  0.5,  0.5, 0.0, 0.0,		0.0f, 0.0f, 0.0f,
		 0.5,  0.5,  0.5, 1.0, 0.0,		0.0f, 0.0f, 0.0f,
		 0.5,  0.5, -0.5, 1.0, 1.0,		0.0f, 0.0f, 0.0f,
		-0.5,  0.5, -0.5, 0.0, 1.0,		0.0f, 0.0f, 0.0f,
		// back							
		 0.5, -0.5, -0.5, 0.0, 0.0,		0.0f, 0.0f, 0.0f,
		-0.5, -0.5, -0.5, 1.0, 0.0,		0.0f, 0.0f, 0.0f,
		-0.5,  0.5, -0.5, 1.0, 1.0,		0.0f, 0.0f, 0.0f,
		 0.5,  0.5, -0.5, 0.0, 1.0,		0.0f, 0.0f, 0.0f,
		 // bottom						
		 -0.5, -0.5, -0.5, 0.0, 0.0,	0.0f, 0.0f, 0.0f,
		  0.5, -0.5, -0.5, 1.0, 0.0,	0.0f, 0.0f, 0.0f,
		  0.5, -0.5,  0.5, 1.0, 1.0,	0.0f, 0.0f, 0.0f,
		 -0.5, -0.5,  0.5, 0.0, 1.0,	0.0f, 0.0f, 0.0f,
		 // left						
		 -0.5, -0.5, -0.5, 0.0, 0.0,	0.0f, 0.0f, 0.0f,
		 -0.5, -0.5,  0.5, 1.0, 0.0,	0.0f, 0.0f, 0.0f,
		 -0.5,  0.5,  0.5, 1.0, 1.0,	0.0f, 0.0f, 0.0f,
		 -0.5,  0.5, -0.5, 0.0, 1.0,	0.0f, 0.0f, 0.0f,
		 // right						
		  0.5, -0.5,  0.5, 0.0, 0.0,	0.0f, 0.0f, 0.0f,
		  0.5, -0.5, -0.5, 1.0, 0.0,	0.0f, 0.0f, 0.0f,
		  0.5,  0.5, -0.5, 1.0, 1.0,	0.0f, 0.0f, 0.0f,
		  0.5,  0.5,  0.5, 0.0, 1.0,	0.0f, 0.0f, 0.0f
	};
	// Cube Indices
	unsigned int indices[36] = {
		// front
		0,  1,  2,
		2,  3,  0,
		// top
		4,  5,  6,
		6,  7,  4,
		// back
		 8,  9, 10,
		10, 11,  8,
		// bottom
		12, 13, 14,
		14, 15, 12,
		// left
		16, 17, 18,
		18, 19, 16,
		// right
		20, 21, 22,
		22, 23, 20,
	};
};
