#pragma once
#include <glm/glm.hpp>
#include "../Mesh.h"
#include "../material/MaterialBase.h"


class RenderCommand final {
public:
	glm::mat4 M;
	Mesh* mesh;
	MaterialBase* material;
	int MuniformLocation;	//TODO: this is my first approach. think about this.

	RenderCommand(): M(glm::mat4(1.0f)), mesh(nullptr), material(nullptr), MuniformLocation(-1) { }

	RenderCommand(const glm::mat4& modelMatrix, Mesh* mesh, MaterialBase* material): M(modelMatrix), mesh(mesh), material(material), MuniformLocation(-1) { }

	~RenderCommand() { }
};

