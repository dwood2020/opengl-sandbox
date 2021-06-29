#pragma once
#include <glm/glm.hpp>
#include "../mesh/MeshBase.h"
#include "../material/MaterialBase.h"
#include "Renderer.h"


class SimpleRenderCommand final {
private:
	glm::mat4 M;
	MeshBase* mesh;
	MaterialBase* material;

public:
	SimpleRenderCommand(): M(glm::mat4(1.0f)), mesh(nullptr), material(nullptr) { }

	SimpleRenderCommand(const glm::mat4& M, MeshBase* mesh, MaterialBase* material):
		M(M), mesh(mesh), material(material) { }

	friend class Renderer;
};
