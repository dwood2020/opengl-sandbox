#include "MeshFactory.h"
#include <vector>
#include "glad/glad.h"
#include "glm/glm.hpp"


MeshFactory::MeshFactory() { }


MeshFactory::~MeshFactory() { }


Mesh MeshFactory::MakeRectangle(float w, float h, float z) const {

	Mesh mesh;

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


Mesh MeshFactory::MakeCube(float l, bool isTextured) const {

	Mesh mesh;
	float lh = l / 2.0f;

	if (isTextured == false) {
		
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
		mesh.SetIndices(indices);
		mesh.SetGlMode(GL_TRIANGLES);
		mesh.Prepare();

	}
	else {

		std::vector<glm::vec3> vertices = {
			{-lh, -lh, lh},
			{lh, -lh, lh},
			{lh, lh, lh},
			{-lh, lh, lh},	// front plane

			{lh, -lh, lh},
			{lh, -lh, -lh},
			{lh, lh, -lh},
			{lh, lh, lh},	// right plane

			{-lh, -lh, -lh},
			{lh, -lh, -lh},
			{lh, lh, -lh},
			{-lh, lh, -lh},	// rear plane

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

		std::vector<glm::vec2> texCoords = {
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
		mesh.SetTextureCoordVertices(texCoords);
		mesh.SetIndices(indices);
		mesh.SetGlMode(GL_TRIANGLES);
		mesh.Prepare();
	}

	return mesh;
}


Mesh MeshFactory::MakeCoordinateSystem(float l) const {
	
	std::vector<glm::vec3> vertices = {
		{0.0f, 0.0f, 0.0f},
		{l, 0.0f, 0.0f},

		{0.0f, 0.0f, 0.0f},
		{0.0f, l, 0.0f},

		{0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, l}
	};

	Mesh mesh;
	mesh.SetPositionVertices(vertices);
	mesh.SetGlMode(GL_LINES);
	mesh.Prepare();

	return mesh;
}


