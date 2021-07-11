#pragma once
#include <glm/glm.hpp>
#include "../events/EventListener.hpp"
#include "../camera/CameraBase.h"
#include "../window/WindowBase.h"
#include "VoxelScene.h"

#include "../mesh/DynamicMesh.h"


class MouseSelector final : public EventListener {
private: 
	WindowBase* window;
	CameraBase* camera;
	VoxelScene* voxelScene;
	bool isActive;

	glm::vec3 rayOrigin;
	glm::vec3 rayDirection;

	bool isOrthoProjection;

	DynamicMesh* rayLineMesh;
	

	MouseSelector() = default;

public:
	MouseSelector(EventBus& eventBus, CameraBase& camera, WindowBase& window, VoxelScene& voxelScene, DynamicMesh& rayLineMesh);

	~MouseSelector();

	void OnEvent(Event& e) override;

private:
	void CalculateRayPerspective(int mouseX, int mouseY);

	void CalculateRayOrtho(int mouseX, int mouseY);

	glm::vec2 ScreenToNDC(const glm::vec2& posScreen) const;

	void DoSelection(void);

	glm::vec3 TruncPrecision(const glm::vec3& v);
};

