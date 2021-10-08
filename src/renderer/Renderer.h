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
	MaterialBase* groundGridMaterial;

	GLStateHandler stateHandler;


	// eventbus, lighting, camera are mandatory.
	Renderer() = default;

public:
	/// <summary>
	/// Load the OpenGL state.
	/// </summary>
	static bool LoadGL(void);


	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="eventBus">EventBus reference</param>
	/// <param name="lighting">Lighting reference</param>
	/// <param name="camera">Camera reference</param>
	Renderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera);

	~Renderer();


	/// <summary>
	/// Overridden event handler method
	/// </summary>
	/// <param name="e">Current event</param>
	void OnEvent(Event& e) override;


	/// <summary>
	/// Initialize the renderer.
	/// This sets the initial viewport and state flags (via GLStateHandler)
	/// </summary>
	/// <param name="windowRect"></param>
	void Init(const glm::vec2& windowRect);

	
	/// <summary>
	/// Sets the clear color to be used
	/// </summary>
	/// <param name="clearColor">Clear color</param>
	void SetClearColor(const glm::vec3& clearColor);


	/// <summary>
	/// Set the OpenGL glPolygonMode (can be GL_FILL or GL_LINE)
	/// </summary>
	/// <param name="mode">Polygon mode</param>
	void SetGlPolygonMode(GLenum mode);


	/// <summary>
	/// Adds a simple RenderCommand to the command queue
	/// (by creating a SimpleCommand instance from the provided parameters and adding this instance).
	/// A pointer to the created and added instance is returned.
	/// </summary>
	/// <param name="modelMatrix">Model matrix</param>
	/// <param name="mesh">Mesh</param>
	/// <param name="material">Material</param>
	/// <returns>Pointer to the added RenderCommand instance</returns>
	RenderCommand* AddSimpleCommand(const glm::mat4& modelMatrix, MeshBase* mesh, MaterialBase* material);


	/// <summary>
	/// Adds the VoxelScene reference. This reference is used for rendereing the entire scene on every update.
	/// </summary>
	/// <param name="voxelScene">VoxelScene reference</param>
	/// <param name="defaultBlockMaterial">Default material to be used for blocks with invalid material id</param>
	/// <param name="gndGridMaterial">Material to be used for the VoxelGround (the xz-plane grid)</param>
	void AddVoxelScene(VoxelScene& voxelScene, MaterialBase* defaultBlockMaterial, MaterialBase* gndGridMaterial = nullptr);	


	/// <summary>
	/// Prepare the entire rendering.
	/// This method prepares the rendering by preparing every material in the material library.
	/// </summary>
	void Prepare(void);


	/// <summary>
	/// Updates and renders the current frame.
	/// (Call this method in every frame)
	/// </summary>
	void DoFrame(void);
	

private:
	void SortSimpleCommands(void);

	void DoSimpleCommands(void);

	void DoVoxelScene(void);

	void DoVoxelSceneGround(void);

	void CalculateViewport(const glm::vec2& rect);

};

