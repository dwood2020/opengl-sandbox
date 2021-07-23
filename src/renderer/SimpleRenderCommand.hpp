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
	bool isActive;

public:
	SimpleRenderCommand(): M(glm::mat4(1.0f)), mesh(nullptr), material(nullptr), isActive(true) { }


	SimpleRenderCommand(MeshBase* mesh, MaterialBase* material): M(glm::mat4(1.0f)), mesh(mesh), material(material), isActive(true) { }


	SimpleRenderCommand(const glm::mat4& M, MeshBase* mesh, MaterialBase* material):
		M(M), mesh(mesh), material(material), isActive(true) { }


	glm::mat4& GetModelMatrix(void) { return M; }


	MaterialBase* GetMaterial(void) {
		return material;
	}


	void SetActiveState(bool isActive) { this->isActive = isActive; }


	friend class Renderer;	
};
