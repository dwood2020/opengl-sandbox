#include "StaticMeshFactory.h"
#include <vector>
#include "../glad/glad.h"
#include "glm/glm.hpp"
#include <cmath>


StaticMeshFactory::StaticMeshFactory() {

	// rotation matrix: 270 degrees around z axis
	R270z = glm::mat3{
		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	R270z = glm::transpose(R270z);

	// rotation matrix: 90 degrees around y axis
	R270y = glm::mat3{
		0.f, 0.f, -1.f,
		0.f, 1.f, 0.f,
		1.f, 0.f, 0.f
	};
	R270y = glm::transpose(R270y);

	// rotation matrix: 90 degrees around x axis
	R90x = glm::mat3{
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f
	};
	R90x = glm::transpose(R90x);
}


StaticMeshFactory::~StaticMeshFactory() { }


StaticMeshFactory& StaticMeshFactory::GetInstance(void) {
	static StaticMeshFactory instance;	//guaranteed to be destroyed
	return instance;
}


StaticMesh StaticMeshFactory::MakeRectangle(float w, float h, float z) const {

	StaticMesh mesh;

	const float wHalf = w / 2.0f;
	const float hHalf = h / 2.0f;

	float rep = 1.0f;

	/*
	* Construction:
	* 
	* 4 +--------+ 3
	*   |   +0,0 | h
	* 1 +--------+ 2
	*        w
	*/

	std::vector<glm::vec3> vertices = {
		{-wHalf, -hHalf, z},
		{wHalf, -hHalf, z},
		{wHalf, hHalf, z},
		{-wHalf, hHalf, z}
	};

	std::vector<glm::vec2> texCoord = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
	};

	//this somehow doesnt work as expected
	if (rep != 1.0f) {
		for (glm::vec2 v : texCoord) {
			v.x *= rep;
			v.y *= rep;
		}
	}

	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3
	};

	mesh.SetPositionVertices(vertices);
	mesh.SetTextureCoordVertices(texCoord);
	mesh.SetIndices(indices);
	mesh.SetGlMode(GL_TRIANGLES);
	mesh.Prepare();

	return mesh;
}


StaticMesh StaticMeshFactory::MakeCube(float l, bool isTextured) const {

	StaticMesh mesh;
	float lh = l / 2.0f;

	std::vector<glm::vec3> vertices = {
			{-lh, -lh, lh},
			{lh, -lh, lh},
			{lh, lh, lh},
			{-lh, lh, lh},	// front plane

			{lh, -lh, lh},
			{lh, -lh, -lh},
			{lh, lh, -lh},
			{lh, lh, lh},	// right plane

			{lh, -lh, -lh},
			{-lh, -lh, -lh},
			{-lh, lh, -lh},
			{lh, lh, -lh},		// rear plane

			{-lh, -lh, -lh},
			{-lh, -lh, lh},
			{-lh, lh, lh},
			{-lh, lh, -lh},	// left plane

			{-lh, lh, lh},
			{lh, lh, lh},
			{lh, lh, -lh},
			{-lh, lh, -lh},	// top plane

			{-lh, -lh, -lh},
			{lh, -lh, -lh},
			{lh, -lh, lh},
			{-lh, -lh, lh}	// bottom plane
	};

	std::vector<glm::vec2> texCoords;
	if (isTextured) {
		texCoords = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},

		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},

		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},

		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},

		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},

		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
		};
	}

	std::vector<glm::vec3> normals = {
		{0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f},		// front

		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},		// right

		{0.0f, 0.0f, -1.0f},
		{0.0f, 0.0f, -1.0f},
		{0.0f, 0.0f, -1.0f},
		{0.0f, 0.0f, -1.0f},	// rear

		{-1.0f, 0.0f, 0.0f},
		{-1.0f, 0.0f, 0.0f},
		{-1.0f, 0.0f, 0.0f},
		{-1.0f, 0.0f, 0.0f},	// left

		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},		// top

		{0.0f, -1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},	// bottom
	};
	
	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3,
	};

	for (unsigned int i = 1; i < 6; i++) {
		for (unsigned int j = 0; j < 6; j++) {
			indices.push_back(indices[j] + 4 * i);
		}
	}

	mesh.SetPositionVertices(vertices);
	
	if (isTextured) {
		mesh.SetTextureCoordVertices(texCoords);
	}

	mesh.SetNormalVertices(normals);
	mesh.SetIndices(indices);
	mesh.SetGlMode(GL_TRIANGLES);
	mesh.Prepare();

	return mesh;
}


StaticMesh StaticMeshFactory::MakeCone(float r, float h, int points) const {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	MakeCone(vertices, normals, indices, points, r, h);

	StaticMesh mesh;
	mesh.SetPositionVertices(vertices);
	mesh.SetNormalVertices(normals);
	mesh.SetIndices(indices);
	mesh.SetGlMode(GL_TRIANGLES);
	mesh.Prepare();

	return mesh;
}


StaticMesh StaticMeshFactory::MakeSphere(float r, int nrLat, int nrLong, bool isTextured) const {
	
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;	
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec2>* pTexCoords = nullptr;
	if (isTextured) {
		pTexCoords = &texCoords;
	}	

	MakeIndexedSphere(&vertices, &normals, &indices, pTexCoords, nrLat, nrLong, r);

	StaticMesh mesh;
	mesh.SetPositionVertices(vertices);
	mesh.SetNormalVertices(normals);
	mesh.SetIndices(indices);
	if (isTextured) {
		mesh.SetTextureCoordVertices(texCoords);
	}
	mesh.SetGlMode(GL_TRIANGLES);
	mesh.Prepare();	

	return mesh;
}


StaticMesh StaticMeshFactory::MakeSimpleCoordinateSystem(float l) const {
	
	std::vector<glm::vec3> vertices = {
		{0.0f, 0.0f, 0.0f},
		{l, 0.0f, 0.0f},

		{0.0f, 0.0f, 0.0f},
		{0.0f, l, 0.0f},

		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, l}
	};

	StaticMesh mesh;
	mesh.SetPositionVertices(vertices);
	mesh.SetGlMode(GL_LINES);
	mesh.Prepare();

	return mesh;
}


StaticMesh StaticMeshFactory::MakeCoordinateSystem(float l) const {
	
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> colorVertices;

	const int pointsPerCircle = 5;

	// make a cylinder on y axis, then rotate it for the other axes.
	std::vector<glm::vec3> verticesX;
	std::vector<unsigned int> indicesX;
	MakeCylinder(verticesX, indicesX, pointsPerCircle, 0.01f, l);

	vertices.reserve(3 * verticesX.size());
	indices.reserve(3 * indicesX.size());
	colorVertices.reserve(3 * indicesX.size());

	// y axis
	vertices.insert(std::end(vertices), verticesX.begin(), verticesX.end());
	for (unsigned int i = 0; i < verticesX.size(); i++) {
		colorVertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	}


	// rotation matrix: 90 degrees around x axis (for z axis)
	/*glm::mat3 R90x = glm::mat3 {
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f
	};
	R90x = glm::transpose(R90x);*/

	for (glm::vec3 v : verticesX) {
		vertices.push_back(R90x * v);
		colorVertices.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	}

	// rotation matrix: 270 degrees around z axis (for x axis)
	/*glm::mat3 R270z = glm::mat3{
		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	R270z = glm::transpose(R270z);*/

	for (glm::vec3 v : verticesX) {
		vertices.push_back(R270z * v);
		colorVertices.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	}

	// add all indices 
	indices.insert(indices.end(), indicesX.begin(), indicesX.end());
	for (unsigned int j = 1; j <= 2; j++) {
		for (unsigned int i : indicesX) {
			indices.push_back(i + j * 2 * pointsPerCircle);
		}
	}	

	StaticMesh mesh;
	mesh.SetPositionVertices(vertices);
	mesh.SetColorVertices(colorVertices);
	mesh.SetIndices(indices);
	mesh.SetGlMode(GL_TRIANGLES);
	mesh.Prepare();
	
	return mesh;
}


StaticMesh StaticMeshFactory::MakeSimpleGrid(float l) const {
	
	std::vector<glm::vec3> vertices;
	
	const float d = 1.0f;

	for (float x = -l; x <= l; x += d) {
		vertices.push_back(glm::vec3(x, 0.0f, -l));
		vertices.push_back(glm::vec3(x, 0.0f, l));
	}

	for (float z = -l; z <= l; z += d) {
		vertices.push_back(glm::vec3(-l, 0.0f, z));
		vertices.push_back(glm::vec3(l, 0.0f, z));
	}

	StaticMesh mesh;
	mesh.SetPositionVertices(vertices);
	mesh.SetGlMode(GL_LINES);
	mesh.Prepare();
	return mesh;
}


StaticMesh StaticMeshFactory::MakeCubeMarker(void) const {
	const int nrPoints = 6;
	const float r = 0.02f;
	const float l = 1.0f;

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;

	std::vector<glm::vec3> verticesTemp;
	std::vector<unsigned int> indicesTemp;	

	//back left vertical
	MakeCylinder(verticesTemp, indicesTemp, nrPoints, r, l);
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());
	
	
	//back right vertical
	for (glm::vec3& v : verticesTemp) {
		v += glm::vec3(1.f, 0.f, 0.f);
	}

	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());
	
	
	//front right vertical
	for (glm::vec3& v : verticesTemp) {
		v += glm::vec3(0.f, 0.f, 1.f);
	}

	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());
	

	//front left vertical
	for (glm::vec3& v : verticesTemp) {
		v += glm::vec3(-1.f, 0.f, 0.f);
	}

	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());
	
	//front bottom horizontal
	for (glm::vec3& v : verticesTemp) {
		v = R270z * v;
	}
	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());

	//front top horizontal
	for (glm::vec3& v : verticesTemp) {
		v += glm::vec3(0.f, 1.f, 0.f);
	}
	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());

	//back top horizontal
	for (glm::vec3& v : verticesTemp) {
		v += glm::vec3(0.f, 0.f, -1.f);
	}
	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());

	//back bottom horizontal
	for (glm::vec3& v : verticesTemp) {
		v += glm::vec3(0.f, -1.f, 0.f);
	}
	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());


	//left bottom horizontal
	for (glm::vec3& v : verticesTemp) {
		v = R270y * v;
	}
	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());

	//left top horizontal
	for (glm::vec3& v : verticesTemp) {
		v += glm::vec3(0.f, 1.f, 0.f);
	}
	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());

	//right top horizontal
	for (glm::vec3& v : verticesTemp) {
		v += glm::vec3(1.f, 0.f, 0.f);
	}
	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());

	//right bottom horizontal
	for (glm::vec3& v : verticesTemp) {
		v += glm::vec3(0.f, -1.f, 0.f);
	}
	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());


	StaticMesh mesh;
	mesh.SetPositionVertices(vertices);
	mesh.SetIndices(indices);
	mesh.SetGlMode(GL_TRIANGLES);
	mesh.Prepare();
	return mesh;
}


StaticMesh StaticMeshFactory::MakeSimpleCubeMarker(void) const {
	
	std::vector<glm::vec3> vertices = {
		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(1.f, 0.f, 1.f),
		glm::vec3(1.f, 0.f, 1.f),
		glm::vec3(1.f, 1.f, 1.f),
		glm::vec3(1.f, 1.f, 1.f),
		glm::vec3(0.f, 1.f, 1.f),
		glm::vec3(0.f, 1.f, 1.f),
		glm::vec3(0.f, 0.f, 1.f),

		glm::vec3(1.f, 0.f, 1.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(1.f, 1.f, 0.f),
		glm::vec3(1.f, 1.f, 0.f),
		glm::vec3(1.f, 1.f, 1.f),

		glm::vec3(1.f, 1.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f),

		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.f, 1.f, 1.f),
	};

	StaticMesh mesh;
	mesh.SetPositionVertices(vertices);
	mesh.SetGlMode(GL_LINES);
	mesh.Prepare();
	return mesh;
}


StaticMesh StaticMeshFactory::MakeSquareMarker(void) const {
	const int nrPoints = 6;
	const float r = 0.02f;
	const float l = 1.0f;

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;

	std::vector<glm::vec3> verticesTemp;
	std::vector<unsigned int> indicesTemp;

	MakeCylinder(verticesTemp, indicesTemp, nrPoints, r, l);

	//front bottom horizontal
	for (glm::vec3& v : verticesTemp) {
		v = R270z * v;
	}
	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());

	//back bottom horizontal
	for (glm::vec3& v : verticesTemp) {
		v += glm::vec3(0.f, -1.f, 0.f);
	}
	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());

	//left bottom horizontal
	for (glm::vec3& v : verticesTemp) {
		v = R270y * v;
	}
	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());

	//right bottom horizontal
	for (glm::vec3& v : verticesTemp) {
		v += glm::vec3(0.f, -1.f, 0.f);
	}
	for (unsigned int& i : indicesTemp) {
		i += static_cast<unsigned int>(verticesTemp.size());
	}
	vertices.insert(vertices.end(), verticesTemp.begin(), verticesTemp.end());
	indices.insert(indices.end(), indicesTemp.begin(), indicesTemp.end());


	StaticMesh mesh;
	mesh.SetPositionVertices(vertices);
	mesh.SetIndices(indices);
	mesh.SetGlMode(GL_TRIANGLES);
	mesh.Prepare();
	return mesh;
}


void StaticMeshFactory::MakeCylinder(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices, int points, float r, float h) const {
	vertices.reserve(2 * (size_t)points);

	const float deltaPhi = (2.0f * pi) / static_cast<float>(points);

	// bottom ring
	for (int i = 0; i < points; i++) {
		vertices.push_back(glm::vec3(r * std::cosf(i * deltaPhi), 0.0f, r * std::sinf(i * deltaPhi)));
	}

	// top ring
	for (int i = 0; i < points; i++) {
		vertices.push_back(glm::vec3(r * std::cosf(i * deltaPhi), h, r * std::sinf(i * deltaPhi)));
	}

	// indices
	indices.reserve(6u * static_cast<size_t>(points));
	for (unsigned int i = 0; i < (unsigned int)points - 1; i++) {				

		indices.push_back(i);
		indices.push_back(i + points);
		indices.push_back(i + points + 1);
		
		indices.push_back(i);
		indices.push_back(i + points + 1);
		indices.push_back(i + 1);
	}

	// do the last piece	
	indices.push_back(points - 1);
	indices.push_back(2 * points - 1);
	indices.push_back(0);
	
	indices.push_back(2 * points - 1);
	indices.push_back(points);
	indices.push_back(0);
}


void StaticMeshFactory::MakeCone(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<unsigned int>& indices, unsigned int points, float r, float h) const {	
	
	// vertices
	// --------
	vertices.reserve(static_cast<size_t>(points) + 1);	
	
	const float deltaPhi = (2.0f * pi) / (float)points;

	// cone point
	vertices.push_back(glm::vec3(0.0f, h, 0.0f));

	// cone ring
	for (unsigned int i = 0; i < points; i++) {
		vertices.push_back(glm::vec3(r * std::cosf(i * deltaPhi), 0.0f, r * std::sinf(i * deltaPhi)));
	}

	// normals
	// -------
	normals.reserve(static_cast<size_t>(points) + 1);

	float x = (r * r) / h;	
	
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	for (unsigned int i = 0; i < points; i++) {
		normals.push_back(glm::normalize(glm::vec3(r * std::cosf(i * deltaPhi), x, r * std::sinf(i * deltaPhi))));
	}

	// indices
	// -------	
	indices.reserve(static_cast<size_t>(points) * 3);

	for (unsigned int i = 1; i < points; i++) {
		indices.push_back(i);		
		indices.push_back(0);
		indices.push_back(i + 1);
	}

	indices.push_back(points);	
	indices.push_back(0);
	indices.push_back(1);
}


void StaticMeshFactory::MakeIndexedSphere(std::vector<glm::vec3>* vertices, std::vector<glm::vec3>* normals, std::vector<unsigned int>* indices, std::vector<glm::vec2>* texCoords, int nrLat, int nrLong, float r) const {
	if (vertices == nullptr || indices == nullptr || normals == nullptr) {
		return;
	}

	// Vertices
	// --------

	// NOTE: Sphere poles are on z-axis

	// north pole			
	vertices->push_back(glm::vec3(0.0f, 0.0f, r));

	const float PI = 3.1415926f;
	float rho;
	float theta;
	float phi;

	rho = r;

	// NOTE: 
	// Latitude = Breitengrad 
	// Longitude = Laengengrad

	for (int i = 1; i <= nrLat; i++) {
		for (int j = 0; j <= nrLong; j++) {

			theta = i * (PI / (nrLat + 1));
			phi = j * (2 * PI) / nrLong;

			glm::vec3 point = glm::vec3(0.0f);
			point.x = rho * sin(theta) * cos(phi);
			point.y = rho * sin(theta) * sin(phi);
			point.z = rho * cos(theta);

			vertices->push_back(point);
		}
	}

	//south pole	
	vertices->push_back(glm::vec3(0.0f, 0.0f, -r));


	// Normals
	// -------

	for (unsigned int i = 0; i < vertices->size(); i++) {
		normals->push_back((1 / r) * (*vertices)[i]);
	}

	// Indices
	// -------

	// north pole cap
	for (int i = 1; i <= nrLong; i++) {
		indices->push_back(0);
		indices->push_back(i);
		indices->push_back(i + 1);
	}
	indices->push_back(0);
	indices->push_back(nrLong);
	indices->push_back(1);

	// center
	if (nrLat > 1) {
		int stride = nrLong + 1;

		for (int i = 0; i < nrLat - 1; i++) {
			for (int j = 1; j <= nrLong; j++) {
				indices->push_back(j + i * stride);
				indices->push_back(j + (i + 1) * stride);
				indices->push_back((j + 1) + (i + 1) * stride);

				indices->push_back(j + i * stride);				
				indices->push_back((j + 1) + (i + 1) * stride);
				indices->push_back((j + 1) + i * stride);
				
			}
		}
	}

	// south pole cap
	int s = (int)vertices->size() - 1;	//Index south pole
	int x = s - (nrLong + 1);			//first index cap

	for (int i = x; i <= s - 1; i++) {
		indices->push_back(i);		
		indices->push_back(s);
		indices->push_back(i + 1);
	}


	// Texture coordinates
	// -------------------
	if (texCoords == nullptr) {
		return;
	}

	// north pole
	texCoords->push_back(glm::vec2(0.0f, 1.0f));

	//Mitte
	glm::vec2 point = glm::vec2(0.0f);

	float deltaU = 1.0f / nrLong;
	float deltaV = 1.0f / (nrLat + 1);

	for (int i = 0; i <= nrLat; i++) {
		for (int j = 0; j <= nrLong; j++) {
			point.x = j * deltaU;
			point.y = i * deltaV;
			texCoords->push_back(point);
		}
	}

	//Suedpol
	texCoords->push_back(glm::vec2(0.0f, 0.0f));
}


