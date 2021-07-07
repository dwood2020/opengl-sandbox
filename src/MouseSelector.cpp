#include "MouseSelector.h"

#include <iostream>


MouseSelector::MouseSelector(EventBus& eventBus, CameraBase& camera, WindowBase& window): 
	camera(&camera), window(&window), isActive(false), ray(glm::vec3(0.0f)) {

	eventBus.AddListener(EventType::ToggleSelectMode, this);
	eventBus.AddListener(EventType::MouseMove, this);
}


MouseSelector::~MouseSelector() { }


void MouseSelector::OnEvent(Event& e) {
	if (e.GetType() == EventType::ToggleSelectMode) {
		ToggleSelectModeEvent& et = (ToggleSelectModeEvent&)e;
		isActive = et.GetSelectMode();
		std::cout << "MouseSelector::isActive: " << isActive << std::endl;
	}

	if (isActive && e.GetType() == EventType::MouseMove) {
		MouseMoveEvent& emm = (MouseMoveEvent&)e;
		CalculateRay(emm.GetPositionX(), emm.GetPositionY());
	}
}


void MouseSelector::CalculateRay(int mouseX, int mouseY) {	

	glm::vec2 mouseNDC = ScreenToNDC(glm::vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)));

	//std::cout << "mouseNDC.x: " << mouseNDC.x << "  mouseNDC.y: " << mouseNDC.y << std::endl;

	glm::vec4 mouseWorld = NDCToWorld(mouseNDC);

	std::cout << "mouseWorld.x: " << mouseWorld.x << "  mouseWorld.y: " << mouseWorld.y << "  mouseWorld.z: " << mouseWorld.z << std::endl;
}


glm::vec4 MouseSelector::NDCToWorld(const glm::vec2& ndc) const {
	
	glm::mat4 PVinv = glm::inverse(camera->GetViewProjectionMatrix());

	//NOTE: All directions are returned inverted. 
	//TM tutorial said -1 for z in clip space
	return glm::normalize(PVinv * glm::vec4(ndc.x, ndc.y, 1.0f, 1.0f));
}


//NOTE: This code is copied from SimpleCamera, maybe re-architecture later
glm::vec2 MouseSelector::ScreenToNDC(const glm::vec2& posScreen) const {
	// this could be done in homogenous coordinates or with a 
	// matrix/vector transformation, or simply in the linearised form	
	// here, a matrix/vector transformation is used.
	glm::vec2 windowRect = window->GetWindowRect();

	glm::mat2 A = {
		{2.0f / windowRect.x, 0.0f},
		{0.0f, -2.0f / windowRect.y}
	};

	glm::vec2 b = {
		-1.0f,
		1.0f
	};

	return A * posScreen + b;
}
