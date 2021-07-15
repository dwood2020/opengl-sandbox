#pragma once
#include <vector>
#include "../glad/glad.h"
#include <glm/glm.hpp>
#include "MeshBase.h"


struct VertexPos {
	glm::vec3 pos;
};


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
	GLuint ebo;
	GLsizei nrElements;

	std::vector<VertexPos> verticesPos;
	std::vector<VertexPosNorm> verticesPosNorm;
	std::vector<VertexPosNormTex> verticesPosNormTex;
	std::vector<GLuint> indices;

	bool useNormals;
	bool useTexCoords;
	bool isInstanced;

public:
	DynamicMesh();

	~DynamicMesh();


	std::vector<VertexPos>& GetVerticesPos(void);


	std::vector<VertexPosNorm>& GetVerticesPosNorm(void);


	std::vector<VertexPosNormTex>& GetVerticesPosNormTex(void);


	std::vector<GLuint>& GetIndices(void);


	void SetUseNormals(bool useNormals);


	void SetUseTexCoords(bool useTexCoords);


	void SetIsInstanced(bool isInstanced);


	void Prepare(void) override;


	void Draw(void) override;


	void Update(void);

private:
	bool CheckDataConsistency(void);
};