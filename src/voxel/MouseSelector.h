#pragma once
#include <glm/glm.hpp>
#include "../events/EventListener.hpp"
#include "../camera/CameraBase.h"
#include "../window/WindowBase.h"


class MouseSelector final : public EventListener {
private: 
	WindowBase* window;
	CameraBase* camera;
	bool isActive;

	glm::vec3 rayOrigin;
	glm::vec3 rayDirection;
	

	MouseSelector() = default;

public:
	MouseSelector(EventBus& eventBus, CameraBase& camera, WindowBase& window);

	~MouseSelector();

	void OnEvent(Event& e) override;

private:
	void CalculateRay(int mouseX, int mouseY);

	glm::vec4 NDCToWorld(const glm::vec2& ndc) const;

	glm::vec2 ScreenToNDC(const glm::vec2& posScreen) const;

	void DoSelection(void);
};

