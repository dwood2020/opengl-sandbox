#pragma once
#include <glm/glm.hpp>
#include "../Mesh.h"
#include "../material/MaterialBase.h"


class RenderCommand final {
public:
	glm::mat4 M;
	Mesh* mesh;
	MaterialBase* material;
	int mUniformLocation;	//TODO: this is my first approach. think about this.
	int pvUniformLocation;
	int viewPosUniformLocation;

	RenderCommand(): M(glm::mat4(1.0f)), mesh(nullptr), material(nullptr), mUniformLocation(-1), pvUniformLocation(-1), viewPosUniformLocation(-1) { }

	RenderCommand(const glm::mat4& modelMatrix, Mesh* mesh, MaterialBase* material): 
		M(modelMatrix), mesh(mesh), material(material), mUniformLocation(-1), pvUniformLocation(-1), viewPosUniformLocation(-1) { }

	~RenderCommand() { }
};
