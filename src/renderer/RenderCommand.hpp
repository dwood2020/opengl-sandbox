#pragma once
#include <glm/glm.hpp>
#include "../mesh/MeshBase.h"
#include "../material/MaterialBase.h"
#include "Renderer.h"


/// <summary>
/// This class represents a single render command which shall be processed by the renderer.
/// It holds all information needed for rendering any object to the window: model matrix, mesh, material.
/// In addition, a render command has an active/inactive state It is only rendered if active.
/// </summary>
class RenderCommand final {
private:
	glm::mat4 M;	
	MeshBase* mesh;
	MaterialBase* material;
	bool isActive;

public:
	/// <summary>
	/// Default Constructor. Initializes M to an identity matrix.
	/// </summary>
	RenderCommand(): M(glm::mat4(1.0f)), mesh(nullptr), material(nullptr), isActive(true) { }


	/// <summary>
	/// Constructor. Initializes M to an identity matrix.
	/// </summary>
	/// <param name="mesh">Mesh</param>
	/// <param name="material">Material</param>
	RenderCommand(MeshBase* mesh, MaterialBase* material): M(glm::mat4(1.0f)), mesh(mesh), material(material), isActive(true) { }

	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="M">Model matrix</param>
	/// <param name="mesh">Mesh</param>
	/// <param name="material">Material</param>
	RenderCommand(const glm::mat4& M, MeshBase* mesh, MaterialBase* material):
		M(M), mesh(mesh), material(material), isActive(true) { }


	/// <summary>
	/// Gets the model matrix.
	/// </summary>
	/// <returns>Model matrix M</returns>
	glm::mat4& GetModelMatrix(void) { return M; }


	/// <summary>
	/// Gets the material.
	/// </summary>
	/// <returns>Material</returns>
	MaterialBase* GetMaterial(void) {
		return material;
	}

	/// <summary>
	/// This sets the active state of the render command.
	/// It is only actually rendered if its active state is true.
	/// </summary>
	/// <param name="isActive">True: Active, render command is rendered</param>
	void SetActiveState(bool isActive) { this->isActive = isActive; }


	// give the renderer direct access to all fields.
	friend class Renderer;	
};
