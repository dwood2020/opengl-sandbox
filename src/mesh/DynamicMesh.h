#pragma once
#include <vector>
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


class DynamicMesh final : public MeshBase {
private:
	GLuint vao;
	GLuint vbo;

	std::vector<VertexPosNorm> verticesPosNorm;
	std::vector<VertexPosNormTex> verticesPosNormTex;

	bool useTexCoords;


public:
	DynamicMesh();

	~DynamicMesh();


	void SetUseTexCoords(bool useTexCoords);


	void Prepare(void) override;


	void Draw(void) override;



};