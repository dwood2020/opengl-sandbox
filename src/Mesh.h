#pragma once
#include <vector>
#include "glad/glad.h"
#include <glm/glm.hpp>


class Mesh {
protected:
	unsigned int vao;	
	unsigned int vbo;
	unsigned int ebo;
	GLenum glMode;
	GLsizei nrElements;

	// these arrays serve for building the vertex data
	// and are cleared after calling Prepare()
	std::vector<glm::vec3> verticesPosition;
	std::vector<glm::vec2> verticesTexCoord;
	std::vector<glm::vec3> verticesNormal;
	std::vector<unsigned int> indices;

public:
	Mesh(std::vector<glm::vec3>& vertices);
	Mesh(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices);
	//TODO: Further overloaded ctors for normals & texture coords
	virtual ~Mesh();

	void SetMode(GLenum glMode);

	void Prepare(void);
	void Draw(void);

protected:
	Mesh();
	
};



