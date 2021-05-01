#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(): 
	position(glm::vec3(0.0f)), target(glm::vec3(0.0f)), V(glm::mat4(1.0f)), 
	P(glm::mat4(1.0f)), PIsDirty(false) { }


Camera::Camera(EventBus& eventBus): Camera() {

	//TODO: change this when event system features class-type listeners
	std::function<void(Event&)> lOnWndResize = [=](Event& e) {
		this->OnWindowResize(e);
	};

	eventBus.AddListener(EventType::WindowResize, lOnWndResize);
}


Camera::~Camera() { }


void Camera::OnWindowResize(Event& e) {
	if (e.GetType() == EventType::WindowResize) {
		CalcProjectionMatrix(e.w, e.h);
	}
}



void Camera::CalcProjectionMatrix(int wScreen, int hScreen) {
	float w = (float)wScreen;
	float h = (float)hScreen;

	const bool isOrthographic = false;

	if (isOrthographic) {
		// orthographic projection
		w = w / 100.0f;
		h = h / 100.0f;
		P = glm::ortho(-w/2.0f, w/2.0f, -h/2.0f, h/2.0f, 1.0f, 100.0f);
	}
	else {
		// perspective projection
		P = glm::perspective(glm::radians(45.0f), w / h, 1.0f, 100.0f);
	}

	PIsDirty = true;
}


