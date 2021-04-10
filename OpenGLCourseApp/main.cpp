#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "CommonValues.h"

#include "Window.h"
#include "Mesh.h"
#include "IndependentMesh.h"
#include "ComplexObject.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Utils.h"
#include "Material.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<IndependentMesh*> independentMeshes;
std::vector<ComplexObject*> objectList;
std::vector<Shader> shaderList;
std::vector<Texture*> gridTextures;

Camera camera;
Camera camera2;
Camera camera3;
Camera camera4;
Utils utils;

Texture brickTexture;
Texture dirtTexture;
Texture blackMarbleTexture;
Texture whiteMarbleTexture;
Texture whiteMarbleTexture2;

Material shinyMaterial;
Material dullMaterial;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";


void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, float* vertices,
	unsigned int vertexCount, unsigned int vLength, unsigned int normalOffset);
void CreateObjects();
void CreateShaders();
void changeCamera(float* currentAngle);
void createGrid(int squareCount);


int main() 
{
	mainWindow = Window(1366, 768);
	mainWindow.Initialise();

	
	CreateObjects();
	CreateShaders();

	objectList = std::vector<ComplexObject*>();
	utils = Utils(&shaderList[0]);

	camera = Camera(glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.0f, 0.2f);
	camera2 = Camera(glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.0f, 0.2f);
	camera3 = Camera(glm::vec3(0.0f, 0.0f, 5.5f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.0f, 0.2f);
	camera4 = Camera(glm::vec3(0.0f, 4.0f, 5.5f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.0f, 0.2f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTexture(GL_RGBA);
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTexture(GL_RGBA);
	blackMarbleTexture = Texture("Textures/FLoor/Marble_Black.jpg");
	blackMarbleTexture.LoadTexture(GL_RGB);
	gridTextures.push_back(&blackMarbleTexture);
	whiteMarbleTexture = Texture("Textures/Floor/Marble_SlabWhite.jpg");
	whiteMarbleTexture.LoadTexture(GL_RGB);
	gridTextures.push_back(&whiteMarbleTexture);
	whiteMarbleTexture2 = Texture("Textures/Floor/Marble_SlabWhite2.jpg");
	whiteMarbleTexture2.LoadTexture(GL_RGB);
	gridTextures.push_back(&whiteMarbleTexture2);

	shinyMaterial = Material(1.0f, 16.0f);
	dullMaterial = Material(0.3f, 4.0f);
	
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 
		0.2f, 0.3f, 
		2.0f, -1.0f, -2.0f);

	unsigned int pointLightCount = 0;
	pointLights[0] = PointLight(0.0f, 1.0f, 0.0f,
		0.1f, 1.0f,
		-4.0f, 0.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;
	pointLights[1] = PointLight(0.0f, 0.0f, 0.5f,
		0.1f, 1.0f,
		4.0f, 0.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	shaderList[0].UseShader();
	uniformModel = shaderList[0].GetModelLocation();
	createGrid(GRID_SQUARES);
	
	utils.CreateLetters(uniformModel, &objectList);
	
	IndependentMesh sphere = IndependentMesh(&shaderList[0]);
	utils.createSphere(&sphere);
	meshList.push_back(&sphere);
	
	IndependentMesh cylinder = IndependentMesh(&shaderList[0]);
	utils.createCylinder(&cylinder, 20, 0.1, 1);
	meshList.push_back(&cylinder);
	glEnable(GL_NORMALIZE);
	float currentAngle = 0.0f;
	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;

		// Get + Handle User Input
		glfwPollEvents();
		changeCamera(&currentAngle);
		

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLight(pointLights, pointLightCount);
		
		//mainLight.useLight(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection);

		// renderObjects(uniformModel, uniformProjection, uniformView, projection);
		glm::mat4 view = camera.calculateViewMatrix();
		view = glm::rotate(view, toRadians * currentAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::mat4 model(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		dirtTexture.UseTexture();
		// dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();

		// Grid
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, -0.5f, -2.5f));
		model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		blackMarbleTexture.UseTexture();
		meshList[2]->RenderCheckerBoardMesh(GRID_SQUARES, gridTextures);

		dirtTexture.UseTexture();
		// LETTERS
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.4f, 0.0f, -.5f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));

		objectList[0]->SetModelMatrix(model, 4);
		objectList[0]->RenderObject();
		//objectList[0]->RenderLetters(&blackMarbleTexture, &blackMarbleTexture, false);

		model = glm::mat4(1.0f);
		brickTexture.UseTexture();
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, -.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		sphere.SetModelMatrix(model, uniformModel);
		sphere.RenderMesh();
		// test

		model = glm::mat4(1.0f);
		brickTexture.UseTexture();
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, toRadians * 90, glm::vec3(1.0f, 0.0f, 0.0f));
		cylinder.SetModelMatrix(model, uniformModel);
		cylinder.RenderMesh();
		
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}


// ******************************************************************************************** //
//										HELPER METHODS                                         //
// ****************************************************************************************** //
void createGrid(int squareCount)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	// Loops through each row, then for each column it creates a point clamped between 0 to 1
	for (int i = 0; i <= squareCount; i++) {
		for (int j = 0; j <= squareCount; j++) {
			float x = (float)j / (float)squareCount;
			float y = 0;
			float z = (float)i / (float)squareCount;
			float u = j;
			float t = i;

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			vertices.push_back(u);
			vertices.push_back(t);

			vertices.push_back(0.0f);
			vertices.push_back(-1.0f);
			vertices.push_back(0.0f);
		}
	}

	// A double loop to connect all the vertices with the appropriate indices.
	// First it top left to top right vertex, then top right with bottom right, then bottom right with bottom left and finally bottom left with top right. 
	for (int i = 0; i < squareCount; i++) {
		for (int j = 0; j < squareCount; j++) {
			int top = i * (1 + squareCount);
			int bottom = (i + 1) * (1 + squareCount);

			// NOTE: Switched to drawing squares using 2 triangles instead of 4 lines.
			indices.push_back(top + j);			// TOP LEFT
			indices.push_back(top + j + 1);		// TOP RIGHT
			indices.push_back(bottom + j);		// BOTTOM LEFT

			indices.push_back(top + j + 1);		// TOP RIGHT
			indices.push_back(bottom + j + 1);	// BOTTOM RIGHT
			indices.push_back(bottom + j);		// BOTTOM LEFT
		}
	}

	//calcAverageNormals(&indices[0], indices.size(), &vertices[0], vertices.size(), 8, 5);

	IndependentMesh* gridObj = new IndependentMesh(&shaderList[0]);
	gridObj->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	meshList.push_back(gridObj);
}

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, float* vertices,
	unsigned int vertexCount, unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)			// += 3 because each triangle consists of 3 vertices
	{
		unsigned int in0 = indices[i] * vLength;		// to pull the correct vertex value from the array, we need to multiply by the vLength (in our case 8, because each vertex had 8 values: x y z u v nx ny nz)
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;

		glm::vec3 v1 = glm::vec3(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2 = glm::vec3(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;

		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < vertexCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec = glm::vec3(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y, vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	float vertices[] = {
		//	x      y      z			u	  v			normals (need to be averaged out before being sent to shaders): 0.0f because they're just placeholders for now
			-1.0f, -1.0f, -0.6f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f,
	};

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void changeCamera(float* currentAngle)
{
	if (mainWindow.getsKeys()[GLFW_KEY_1])
	{
		camera = camera2;
	}
	if (mainWindow.getsKeys()[GLFW_KEY_2])
	{
		camera = camera3;
	}
	if (mainWindow.getsKeys()[GLFW_KEY_3])
	{
		camera = camera4;
	}
	if (mainWindow.getsKeys()[GLFW_KEY_LEFT])
	{
		(*currentAngle)--;
	}
	if (mainWindow.getsKeys()[GLFW_KEY_RIGHT])
	{
		(*currentAngle)++;
	}
}