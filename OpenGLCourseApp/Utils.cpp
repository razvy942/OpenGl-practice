#include "Utils.h"


Utils::Utils()
{
	calcAverageNormals(indices, 36, vertices, 192, 8, 5);
}

float Utils::toRadians(float deg)
{
	return deg * (3.14159265f / 180.0f);
}

ComplexObject* Utils::CreateLetterP(GLuint uniformModel)
{
	// LETTER P

	// Creating the base of the letter P
	IndependentMesh* pBase = new IndependentMesh();
	pBase->CreateMeshWithTexParams(vertices, indices, 192, 36);
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 6.0f, 1.0f));

	pBase->SetModelMatrix(model, uniformModel);


	// Creating top part of p
	IndependentMesh* pTop = new IndependentMesh();
	pTop->CreateMeshWithTexParams(vertices, indices, 192, 36);
	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(2.0f, 4.5f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));

	pTop->SetModelMatrix(model, uniformModel);

	// Creating right side of top
	IndependentMesh* pTopRight = new IndependentMesh();
	pTopRight->CreateMeshWithTexParams(vertices, indices, 192, 36);
	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(3.0f, 3.15f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.7f, 1.0f));

	pTopRight->SetModelMatrix(model, uniformModel);

	// Creating bottom of top
	IndependentMesh* pTopBottom = new IndependentMesh();
	pTopBottom->CreateMeshWithTexParams(vertices, indices, 192, 36);
	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(2.0f, 1.8f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));

	pTopBottom->SetModelMatrix(model, uniformModel);


	ComplexObject* pLetter = new ComplexObject();
	pLetter->meshList.push_back(pBase);
	pLetter->meshList.push_back(pTop);
	pLetter->meshList.push_back(pTopRight);
	pLetter->meshList.push_back(pTopBottom);

	return pLetter;
}


ComplexObject* Utils::CreateLetterR(GLuint uniformModel)
{
	// LETTER R

	// Creating the base of the letter R
	IndependentMesh* rBase = new IndependentMesh();
	rBase->CreateMeshWithTexParams(vertices, indices, 192, 36);
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 6.0f, 1.0f));

	rBase->SetModelMatrix(model, uniformModel);


	// Creating top part of R
	IndependentMesh* rTop = new IndependentMesh();
	rTop->CreateMeshWithTexParams(vertices, indices, 192, 36);
	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(2.0f, 4.5f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));

	rTop->SetModelMatrix(model, uniformModel);

	// Creating right side of top
	IndependentMesh* rTopRight = new IndependentMesh();
	rTopRight->CreateMeshWithTexParams(vertices, indices, 192, 36);
	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(3.0f, 3.15f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.7f, 1.0f));

	rTopRight->SetModelMatrix(model, uniformModel);

	// Creating bottom of top
	IndependentMesh* rTopBottom = new IndependentMesh();
	rTopBottom->CreateMeshWithTexParams(vertices, indices, 192, 36);
	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(2.0f, 1.8f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));

	rTopBottom->SetModelMatrix(model, uniformModel);


	// Creating bottom 
	IndependentMesh* rBottom = new IndependentMesh();
	rBottom->CreateMeshWithTexParams(vertices, indices, 192, 36);
	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(2.0f, 0.5f, 0.0f));
	model = glm::rotate(model, toRadians(45), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 3.5f, 1.0f));

	rBottom->SetModelMatrix(model, uniformModel);

	ComplexObject* rLetter = new ComplexObject();
	rLetter->meshList.push_back(rBase);
	rLetter->meshList.push_back(rTop);
	rLetter->meshList.push_back(rTopRight);
	rLetter->meshList.push_back(rTopBottom);
	rLetter->meshList.push_back(rBottom);


	return rLetter;
}



void Utils::CreateLetters(unsigned int modelLocation, std::vector<ComplexObject*>* objectList) {	
	//////////////////////////////////////////
	// Creating Razvan's name and ID object //
	//////////////////////////////////////////
	glm::mat4 model = glm::mat4(1.0f);

	ComplexObject* letterR = CreateLetterR(modelLocation);
	ComplexObject* letterP = CreateLetterP(modelLocation);
	// R translate
	model = glm::mat4(1.0f);
	//model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.2f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	letterR->SetModelMatrix(model, modelLocation);
	//// P translate
	model = glm::mat4(1.0f);
	//model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.2f));
	model = glm::translate(model, glm::vec3(5.0f, 0.0f, -2.0f));
	model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	letterP->SetModelMatrix(model, modelLocation);


	ComplexObject* razvanNameAndID = new ComplexObject();
	razvanNameAndID->objectList.push_back(letterR);
	razvanNameAndID->objectList.push_back(letterP);


	objectList->push_back(razvanNameAndID);
}

void Utils::createSphere(IndependentMesh* mesh)
{
	int verticalDiv;
	int horizontalDiv;
	verticalDiv = horizontalDiv = 50;

	std::vector<float>vertices;
	std::vector<unsigned int> indices;


	float horizontalAng = 0;
	float horizontalDiff = (2 * glm::pi<double>()) / horizontalDiv;

	float verticalAng = glm::pi<double>() / 2;
	float verticalDiff = -(glm::pi<double>() / verticalDiv);


	for (int i = 0; i <= verticalDiv; i++) {

		float cosVert = glm::cos(verticalAng);
		float sinVert = glm::sin(verticalAng);

		for (int j = 0; j <= horizontalDiv; j++) {

			float cosHor = glm::cos(horizontalAng);
			float sinHor = glm::sin(horizontalAng);


			float x = cosVert * sinHor;
			float y = sinVert;
			float z = cosVert * cosHor;

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
			
			vertices.push_back((float)j / horizontalDiv);
			vertices.push_back((float)i / verticalDiv);
			

			vertices.push_back(x); 
			vertices.push_back(y); 
			vertices.push_back(z); 


			horizontalAng += horizontalDiff;
		}

		verticalAng += verticalDiff;
	}


	for (int i = 0; i < verticalDiv; i++) {
		float k1 = i * (horizontalDiv + 1);
		float k2 = k1 + horizontalDiv + 1;

		for (int j = 0; j < horizontalDiv; j++) {

			if (i != 0) {
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			if (i != (verticalDiv - 1)) {
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}

			k1++;
			k2++;
		}
	}

	// calcAverageNormals(&indices[0], indices.size(), &vertices[0], vertices.size(), 8, 5);
	mesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
}

//void Utils::createCylinder(IndependentMesh* mesh)
//{
//	// Amount of points on the circle faces, more points results in a more circular looking cylinder
//	int sides = 20;
//	// refers to the top and bottom part of the cylinder, totaling 2
//	int faces = 2;
//	// Radius of the cylinder
//	float radius = 1.0f;
//	std::vector<float> vertices;
//	std::vector<unsigned int> indices;
//
//	for (int i = 0; i <= 365; i += 360 / sides)		// <= to 365 because otherwise the last vertex that closes the circle would not be drawn
//	{
//		for (int j = 0; j < faces; j++)
//		{
//			float heading = toRadians(i);
//			vertices.push_back((cos(heading) * radius) / sides);
//			vertices.push_back((sin(heading) * radius) / sides);
//			vertices.push_back(float(j) / float(faces));
//		}
//	}
//
//	// Refers to the current point on the circle (circle is made of multiple points 
//	int currentPoint = 0;
//	for (int i = 0; i < 360; i += 360 / sides)
//	{
//
//		for (int j = 0; j < 360; j += 360 / sides)
//		{
//			indices.push_back(currentPoint);
//			indices.push_back(currentPoint + 1);
//			indices.push_back(currentPoint + 1 + sides);
//			indices.push_back(currentPoint + sides);
//			indices.push_back(currentPoint);
//
//			currentPoint += 1 % sides;
//		}
//	}
//
//	/*Mesh* gridObj = new Mesh();
//	gridObj->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
//	meshList.push_back(gridObj);*/
//	mesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
//}

std::vector<float> Utils::getUnitCircleVertices(int sectorCount)
{
	const float PI = glm::pi<float>();
	float sectorStep = 2 * PI / sectorCount;
	float sectorAngle;  // radian

	std::vector<float> unitCircleVertices;
	for (int i = 0; i <= sectorCount; ++i)
	{
		sectorAngle = i * sectorStep;
		unitCircleVertices.push_back(cos(sectorAngle)); // x
		unitCircleVertices.push_back(sin(sectorAngle)); // y
		unitCircleVertices.push_back(0);                // z
	}
	return unitCircleVertices;
}

void Utils::createCylinder(IndependentMesh* mesh, int sectorCount, float radius, float height)
{
	// clear memory of prev arrays
	std::vector<float> vertices;
	
	// get unit circle vectors on XY-plane
	std::vector<float> unitVertices = getUnitCircleVertices(sectorCount);

	// put side vertices to arrays
	for (int i = 0; i < 2; ++i)
	{
		float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
		float t = 1.0f - i;                              // vertical tex coord; 1 to 0

		for (int j = 0, k = 0; j <= sectorCount; ++j, k += 3)
		{
			float ux = unitVertices[k];
			float uy = unitVertices[k + 1];
			float uz = unitVertices[k + 2];
			// position vector
			vertices.push_back(ux * radius);             // vx
			vertices.push_back(uy * radius);             // vy
			vertices.push_back(h);                       // vz
			
			// texture coordinate
			vertices.push_back((float)j / sectorCount); // s
			vertices.push_back(t);                      // t
			
			// normal vector
			vertices.push_back(ux);                       // nx
			vertices.push_back(uy);                       // ny
			vertices.push_back(uz);                       // nz
		}
	}

	// the starting index for the base/top surface
	//NOTE: it is used for generating indices later
	int baseCenterIndex = (int)vertices.size() / 3;
	int topCenterIndex = baseCenterIndex + sectorCount + 1; // include center vertex

	// put base and top vertices to arrays
	for (int i = 0; i < 2; ++i)
	{
		float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
		float nz = -1 + i * 2;                           // z value of normal; -1 to 1

		// center point
		vertices.push_back(0);     vertices.push_back(0);     vertices.push_back(h);
		vertices.push_back(0.5f); vertices.push_back(0.5f);
		vertices.push_back(0);      vertices.push_back(0);      vertices.push_back(nz);

		for (int j = 0, k = 0; j < sectorCount; ++j, k += 3)
		{
			float ux = unitVertices[k];
			float uy = unitVertices[k + 1];
			// position vector
			vertices.push_back(ux * radius);             // vx
			vertices.push_back(uy * radius);             // vy
			vertices.push_back(h);                       // vz

			// texture coordinate
			vertices.push_back(-ux * 0.5f + 0.5f);      // s
			vertices.push_back(-uy * 0.5f + 0.5f);      // t

			// normal vector
			vertices.push_back(0);                        // nx
			vertices.push_back(0);                        // ny
			vertices.push_back(nz);                       // nz
		}
	}

	// generate CCW index list of cylinder triangles
	std::vector<unsigned int> indices;
	int k1 = 0;                         // 1st vertex index at base
	int k2 = sectorCount + 1;           // 1st vertex index at top

	// indices for the side surface
	for (int i = 0; i < sectorCount; ++i, ++k1, ++k2)
	{
		// 2 triangles per sector
		// k1 => k1+1 => k2
		indices.push_back(k1);
		indices.push_back(k1 + 1);
		indices.push_back(k2);

		// k2 => k1+1 => k2+1
		indices.push_back(k2);
		indices.push_back(k1 + 1);
		indices.push_back(k2 + 1);
	}

	// indices for the base surface
	//NOTE: baseCenterIndex and topCenterIndices are pre-computed during vertex generation
	//      please see the previous code snippet
	for (int i = 0, k = baseCenterIndex + 1; i < sectorCount; ++i, ++k)
	{
		if (i < sectorCount - 1)
		{
			indices.push_back(baseCenterIndex);
			indices.push_back(k + 1);
			indices.push_back(k);
		}
		else // last triangle
		{
			indices.push_back(baseCenterIndex);
			indices.push_back(baseCenterIndex + 1);
			indices.push_back(k);
		}
	}

	// indices for the top surface
	for (int i = 0, k = topCenterIndex + 1; i < sectorCount; ++i, ++k)
	{
		if (i < sectorCount - 1)
		{
			indices.push_back(topCenterIndex);
			indices.push_back(k);
			indices.push_back(k + 1);
		}
		else // last triangle
		{
			indices.push_back(topCenterIndex);
			indices.push_back(k);
			indices.push_back(topCenterIndex + 1);
		}
	}

	mesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
}

void Utils::calcAverageNormals(unsigned int* indices, unsigned int indiceCount, float* vertices,
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

