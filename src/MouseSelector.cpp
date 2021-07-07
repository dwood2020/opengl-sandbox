#include "MouseSelector.h"

#include <iostream>


MouseSelector::MouseSelector(EventBus& eventBus, CameraBase& camera): camera(&camera), isActive(false), ray(glm::vec3(0.0f)) {
	eventBus.AddListener(EventType::ToggleSelectMode, this);
}


MouseSelector::~MouseSelector() { }


void MouseSelector::OnEvent(Event& e) {
	if (e.GetType() == EventType::ToggleSelectMode) {
		ToggleSelectModeEvent& et = (ToggleSelectModeEvent&)e;
		isActive = et.GetSelectMode();
		std::cout << "MouseSelector::isActive: " << isActive << std::endl;
	}
}
