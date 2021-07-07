#pragma once
#include <glm/glm.hpp>
#include "events/EventListener.hpp"
#include "camera/CameraBase.h"


class MouseSelector final : public EventListener {
private: 
	CameraBase* camera;
	bool isActive;

	glm::vec3 ray;

	MouseSelector() = default;

public:
	MouseSelector(EventBus& eventBus, CameraBase& camera);

	~MouseSelector();


	void OnEvent(Event& e) override;
};

