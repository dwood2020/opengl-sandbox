#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../events/EventBus.h"
#include "../events/EventListener.hpp"
#include "../Lighting.h"
#include "../camera/CameraBase.h"
#include "../material/MaterialLibrary.h"
#include "RenderCommand.hpp"
#include "SimpleRenderCommand.hpp"


/// <summary>
/// Monolithic renderer class.
/// This is the first iteration of a renderer redesign: 
/// KISS: Put everything into one class, break architecture up later.
/// 
/// The different jobs are simply separated into 2 different methods here. (=>Change this later)
/// 
/// TODO: DESIGN:
/// Possible design is: RendererMaster as Factory, forces context init before SimpleRenderer, 
/// VoxelRenderer etc can be instanciated.
/// First step: Replicate SimpleRenderer (done)
/// Second step: Add material management (material lib composition)
/// Third step: ...
/// </summary>
class Renderer final : public EventListener {
private:
	Lighting* lighting;
	CameraBase* camera;
	MaterialLibrary* materialLibrary;

	std::vector<RenderCommand> renderCommands;

	std::vector<SimpleRenderCommand> simpleRenderCommands;

	// eventbus, lighting, camera are mandatory.
	Renderer() = default;

public:
	Renderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera, MaterialLibrary& materialLibrary);

	~Renderer();


	void OnEvent(Event& e) override;


	void Init(const glm::vec2& windowRect);


	void Prepare(void);


	void DoFrame(void);


	void AddCommand(const glm::mat4& modelMatrix, MeshBase* mesh, MaterialBase* material);


	void AddSimpleCommand(const glm::mat4& modelMatrix, MeshBase* mesh, MaterialBase* material);

	
	void SetClearColor(const glm::vec3& clearColor);


	void SetGlPolygonMode(GLenum mode);



private:
	void CalculateViewport(const glm::vec2& rect);

};

