#include "Mesh.h"

Mesh::Mesh(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices):
	vao(0), vbo(0), ebo(0), glMode(0) { 
		
	serializedData.resize(vertices.size() * 3);

	for (unsigned int i = 0; i < vertices.size(); i++) {
		serializedData[3*i] = vertices[i].x;
		serializedData[3*i + 1u] = vertices[i].y;
		serializedData[3*i + 2u] = vertices[i].z;
	}

}


Mesh::~Mesh() { }
