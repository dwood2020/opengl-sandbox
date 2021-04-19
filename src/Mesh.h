#pragma once
#include <vector>
#include "glad/glad.h"
#include <glm/glm.hpp>


class Mesh {
public:
	unsigned int vao;	
	GLenum glMode;

protected:
	unsigned int vbo;
	unsigned int ebo;

	std::vector<glm::vec3> verticesPosition;
	std::vector<glm::vec2> verticesTexCoord;
	std::vector<glm::vec3> verticesNormal;
	std::vector<unsigned int> indices;

public:
	Mesh(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices);
	//TODO: Further overloaded ctors for normals & texture coords
	virtual ~Mesh();

	void Prepare(void);
	void Draw(void);

protected:
	Mesh();
	
};



