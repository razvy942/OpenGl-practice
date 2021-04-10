#include "Mesh.h"

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
	renderType = GL_TRIANGLES;
}


Mesh::Mesh(Shader* shader)
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
	renderType = GL_TRIANGLES;
	this->shader = shader;
}

void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::CreateSphereMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 6));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 8));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::CreateMeshWithTexParams(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, // Position
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertices[0]) * 8, // Skip 8 values as the Stride, because each of our value has 8 values in the array..
		0);
	glEnableVertexAttribArray(0);

	// Now we tell it how to handle the UV coords.
	glVertexAttribPointer(1, // Tex coordinates
		2, // 2 values in our UV coords.
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertices[0]) * 8, // Skip 8 values as the Stride before we reach next uv coord
		(void*)(sizeof(vertices[0]) * 3) // Offset. Where to start for uv coords.
	);
	glEnableVertexAttribArray(1);

	// Now we tell it how to handle the normal coords.
	glVertexAttribPointer(2, // Normal coordinates
		3, // our coordinates have x,y,z
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertices[0]) * 8, // Skip 8 values as the Stride before we reach next normal coord
		(void*)(sizeof(vertices[0]) * 5) // Offset. Where to start for normal coords.
	);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


void Mesh::RenderMesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(renderType, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::RenderCheckerBoardMesh(int nbSquares, std::vector<Texture*>& textures)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	srand(1);

	int currentOffset = 0;
	for (int i = 0; i < indexCount / 6; i++)
	{
		/*if (i % nbSquares)
		{
			currentOffset ++;
		}
		textures[(currentOffset) % textures.size()]->UseTexture();*/

		textures[rand() % textures.size()]->UseTexture();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * i * sizeof(unsigned int)));
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::RenderMesh(glm::mat4& matrix, GLuint uniformModelLocation)
{
	// We want to work with our created VAO.
	glBindVertexArray(VAO);
	// We indent to show we are working with this VAO from here on.  

	// Binding IBO.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Applying the provided matrix
	// Reassigning the uniform variable. So now we want to assign a matrix, 4x4, with float values.
	glUniformMatrix4fv(uniformModelLocation, // Value to change
		1, // How many matrices to pass
		GL_FALSE, // Transpose?
		glm::value_ptr(matrix)); // Our value. Can't pass our value directly. We need to use a pointer.

								 // Drawing our triangles.
	glDrawElements(renderType, // What to draw
		indexCount, // Count of indices
		GL_UNSIGNED_INT, // Format of indices
		0 // Point to the indices, but we dont need it because we have IBO already.
	);

	// Removing the model matrix from gpu
	//glUniform1f(uniformModelLocation, 0.0f);

	// We unbind the VAO.
	glBindVertexArray(0);
	// Unbinding the IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::ClearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}


Mesh::~Mesh()
{
	ClearMesh();
}

