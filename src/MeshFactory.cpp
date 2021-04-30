#include "MeshFactory.h"
#include <vector>
#include "glad/glad.h"
#include "glm/glm.hpp"


MeshFactory::MeshFactory() { }


MeshFactory::~MeshFactory() { }


Mesh MeshFactory::MakeRectangle(float w, float h, float z) const {

	Mesh mesh;

	float wHalf = w / 2.0f;
	float hHalf = h / 2.0f;

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

	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3
	};

	mesh.SetPositionVertices(vertices);
	mesh.SetIndices(indices);
	mesh.SetGlMode(GL_TRIANGLES);
	mesh.Prepare();

	return mesh;
}


Mesh MeshFactory::MakeCube(float l) const {

	Mesh mesh;

	float lh = l / 2.0f;

	std::vector<glm::vec3> vertices = {
		{-lh, -lh, lh},
		{lh, -lh, lh},
		{lh, lh, lh},
		{-lh, lh, lh},	// front plane

		{-lh, -lh, -lh},
		{lh, -lh, -lh},
		{lh, lh, -lh},
		{-lh, lh, -lh}	// rear plane
	};

	std::vector<glm::vec2> texVertices = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},

		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3,	// front plane

		1, 5, 6,
		1, 6, 2,	// right plane

		5, 4, 7,
		5, 7, 6,	// rear plane

		4, 0, 3,
		4, 3, 7,	// left plane

		3, 2, 6,
		3, 6, 7,	// top plane

		4, 5, 1,
		4, 1, 0,	// bottom plane
	};

	mesh.SetPositionVertices(vertices);
	//mesh.SetTextureCoordVertices(texVertices);
	mesh.SetIndices(indices);
	mesh.SetGlMode(GL_TRIANGLES);
	mesh.Prepare();

	return mesh;
}


