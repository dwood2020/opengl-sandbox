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
	Mesh();
	virtual ~Mesh();

	void SetPositionVertices(std::vector<glm::vec3>& vertices);
	void SetTextureCoordVertices(std::vector<glm::vec2>& texCoords);
	void SetIndices(std::vector<unsigned int>& indices);
	void SetMode(GLenum glMode);

	void Prepare(void);
	void Draw(void);

};



