#pragma once
#include <vector>
//#include <map>
#include <memory>
#include <glm/glm.hpp>
#include "GLStateHandler.h"
#include "../events/EventBus.h"
#include "../events/EventListener.hpp"
#include "../Lighting.h"
#include "../camera/CameraBase.h"
#include "RenderCommand.hpp"
#include "../voxel/VoxelScene.h"


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
/// </summary>
class Renderer final : public EventListener {
private:
	Lighting* lighting;
	CameraBase* camera;	
	
	std::vector<std::unique_ptr<RenderCommand>> renderCommands;
	
	VoxelScene* voxelScene;
	MaterialBase* defaultBlockMaterial;

	GLStateHandler stateHandler;


	// eventbus, lighting, camera are mandatory.
	Renderer() = default;

public:
	static bool LoadGL(void);


	Renderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera);

	~Renderer();


	void OnEvent(Event& e) override;


	void Init(const glm::vec2& windowRect);

	
	void SetClearColor(const glm::vec3& clearColor);


	void SetGlPolygonMode(GLenum mode);


	RenderCommand* AddSimpleCommand(const glm::mat4& modelMatrix, MeshBase* mesh, MaterialBase* material);


	void AddVoxelScene(VoxelScene& voxelScene, MaterialBase* defaultBlockMaterial);	


	void Prepare(void);


	void DoFrame(void);
	

private:
	void SortSimpleCommands(void);

	void DoSimpleCommands(void);

	void DoVoxelScene(void);	

	void CalculateViewport(const glm::vec2& rect);

};

