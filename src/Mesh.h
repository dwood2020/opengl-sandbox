#pragma once
#include <vector>
#include "glad/glad.h"
#include <glm/vec3.hpp>


class Mesh {
public:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	GLenum glMode;

protected:
	std::vector<float> serializedData;
	std::vector<unsigned int> indices;

	Mesh(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices);
	//TODO: Further overloaded ctors for normals & texture coords
	virtual ~Mesh();

	void Prepare(std::vector<float> data);
	
};



