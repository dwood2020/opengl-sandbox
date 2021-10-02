#pragma once
#include <glm/glm.hpp>
#include "../events/EventListener.hpp"
#include "../camera/CameraBase.h"
#include "../window/WindowBase.h"
#include "VoxelScene.h"
#include "../mesh/StaticMesh.h"
#include "../renderer/Renderer.h"
#include "../renderer/RenderCommand.hpp"


/// <summary>
/// This class handles all selection which is performed within the voxel scene
/// (via a casted ray in 3D space)
/// Currently, only objects which are part of the VoxelScene can be selected via this class.
/// </summary>
class MouseSelector final : public EventListener {
private: 
	WindowBase* window;
	CameraBase* camera;
	VoxelScene* voxelScene;
	bool isActive;

	glm::vec3 rayOrigin;
	glm::vec3 rayDirection;

	bool isOrthoProjection;
	
	StaticMesh cubeSelectionMesh;
	StaticMesh groundSelectionMesh;
	RenderCommand* cubeSelectionRC;
	RenderCommand* groundSelectionRC;

	float lastDistanceToFloor;
	

	MouseSelector() = default;

public:
	/// <summary>
	/// Constructor. Sets all needed refs but does not initialize working state.
	/// Init() needs to be called separately.
	/// </summary>
	/// <param name="eventBus">EventBus reference</param>
	/// <param name="camera">Camera reference</param>
	/// <param name="window">Window reference</param>
	/// <param name="voxelScene">VoxelScene reference</param>
	MouseSelector(EventBus& eventBus, CameraBase& camera, WindowBase& window, VoxelScene& voxelScene);

	~MouseSelector();


	/// <summary>
	/// Initializes the working state
	/// </summary>
	/// <param name="renderer">Renderer reference</param>
	/// <param name="selectionMaterial">Material which shall be used for rendering the selection boxes</param>
	void Init(Renderer& renderer, MaterialBase* selectionMaterial);

	/// <summary>
	/// Overridden event handler method.
	/// </summary>
	/// <param name="e">current event</param>
	void OnEvent(Event& e) override;

private:
	void CalculateRayPerspective(int mouseX, int mouseY);

	void CalculateRayOrtho(int mouseX, int mouseY);

	glm::vec2 ScreenToNDC(const glm::vec2& posScreen) const;

	void CheckCollisions(void);

	void DoSelection(const glm::ivec3& blockPos);

	void DoGroundSelection(const glm::ivec3& pos);

	void DoUnselection(void);

	glm::vec3 TruncPrecision(const glm::vec3& v);


	template<typename T>
	int Sign(T value) const;
};



