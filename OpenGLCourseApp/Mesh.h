#pragma once

#include <GL\glew.h>
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Texture.h"
#include "Shader.h"

class Mesh
{
public:
	Mesh();
	Mesh(Shader* shader);
	Mesh(GLenum renderType, Shader* shader);

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void CreateMeshWithTexParams(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void CreateSphereMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	void RenderCheckerBoardMesh(int nbSquares, std::vector<Texture*>& textures);
	/// <summary>
	/// Draws the mesh on screen using a custom transformation
	/// </summary>
	/// <param name="matrix">The model matrix, representing the transformation to apply.</param>
	/// <param name="uniformModelLocation">The location of the provided model matrix.</param>
	void RenderMesh(glm::mat4& matrix, GLuint uniformModelLocation);
	void ClearMesh();

	~Mesh();


protected:
	GLenum renderType;
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
	Shader* shader;
};


