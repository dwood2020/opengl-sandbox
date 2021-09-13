#pragma once
#include <glm/glm.hpp>
#include "../events/EventListener.hpp"
#include "../camera/CameraBase.h"
#include "../window/WindowBase.h"
#include "VoxelScene.h"
#include "../mesh/StaticMesh.h"
#include "../renderer/Renderer.h"
#include "../renderer/RenderCommand.hpp"


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
	

	MouseSelector() = default;

public:
	MouseSelector(EventBus& eventBus, CameraBase& camera, WindowBase& window, VoxelScene& voxelScene);

	~MouseSelector();

	void Init(Renderer& renderer, MaterialBase* selectionMaterial);

	void OnEvent(Event& e) override;

private:
	void CalculateRayPerspective(int mouseX, int mouseY);

	void CalculateRayOrtho(int mouseX, int mouseY);

	glm::vec2 ScreenToNDC(const glm::vec2& posScreen) const;

	void CheckCollisions(void);

	void DoSelection(const glm::ivec3& blockPos);

	void DoUnselection(void);

	glm::vec3 TruncPrecision(const glm::vec3& v);
};

