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
	mesh.SetMode(GL_TRIANGLES);
	mesh.Prepare();

	return mesh;
}


Mesh MeshFactory::MakeCube(int l) const {
	return Mesh();
}


