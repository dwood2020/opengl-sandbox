#pragma once
#include <vector>
#include "../glad/glad.h"
#include <glm/glm.hpp>
#include "MeshBase.h"


struct VertexPosNorm {
	glm::vec3 pos;
	glm::vec3 norm;
};


struct VertexPosNormTex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 tex;
};


class DynamicMesh : public MeshBase {
protected:
	GLuint vao;
	GLuint vbo;

	std::vector<VertexPosNorm> verticesPosNorm;
	std::vector<VertexPosNormTex> verticesPosNormTex;


public:
	DynamicMesh();

	virtual ~DynamicMesh();


	void Prepare(void) override;


	void Draw(void) override;

};