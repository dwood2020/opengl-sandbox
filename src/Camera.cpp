#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <iostream>


Camera::Camera(): 
	position(glm::vec3(0.0f)),
	target(glm::vec3(0.0f)), V(glm::mat4(1.0f)), 
	P(glm::mat4(1.0f)), PIsDirty(false), VIsDirty(false) { }


Camera::Camera(EventBus& eventBus): Camera() {

	eventBus.AddListener(EventType::WindowResize, this);
	eventBus.AddListener(EventType::MouseButton, this);
	eventBus.AddListener(EventType::MouseMove, this);
}


Camera::~Camera() { }


void Camera::SetPosition(glm::vec3 pos) {

	// keep a minimum distance from target
	//glm::vec3 toTarget = glm::abs(target - pos);
	//float distToTarget = glm::length(toTarget);

	//const float minDistToTarget = 1.0f;

	//if (distToTarget < minDistToTarget) {
	//	//TODO this:
	//	// calc intersection with distance sphere and set intersect pos as position
	//}
	//else {
	//	this->positionCartesian = pos;
	//}
	
	

	position = pos;	

	CalcViewMatrix();
}


const glm::vec3& Camera::GetPosition(void) const {
	return position;
}


void Camera::OnEvent(Event& e) { 
	if (e.GetType() == EventType::WindowResize) {
		CalcProjectionMatrix(e.w, e.h);
	}
	else if (e.GetType() == EventType::MouseButton) {
		ProcessMouseButtonInput(e.mbCode, e.isPressed);
	}
	else if (e.GetType() == EventType::MouseMove) {
		ProcessMouseMoveInput(e.xScreen, e.yScreen);
	}
}



void Camera::CalcProjectionMatrix(int wScreen, int hScreen) {
	//DEBUG
	std::cout << "Camera::CalcProjectionMatrix is called!" << std::endl;

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


void Camera::CalcViewMatrix(void) {
	// currently only supports translation
	// direction is inverted here, camera position is set in "intentional" coordinates
	// (e.g. (0,0,3) to move camera backwards by 3, see OpenGL coordinate system)
	// to "actually move the scene", the position vector is inverted here
	
	//V = glm::translate(glm::mat4(1.0f), position * -1.0f);

	// calc V with lookAt function
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	V = glm::lookAt(position * -1.0f, target, up);

	VIsDirty = true;
}


void Camera::ProcessMouseButtonInput(MouseButtonCode mbCode, bool isPressed) {
	if (mbCode == MouseButtonCode::Left) {
		if (isPressed) {
			lmbIsDown = true;
		}
		else {
			lmbIsDown = false;
		}
	}
}


void Camera::ProcessMouseMoveInput(int x, int y) {
	if (!lmbIsDown) {
		return;
	}

	std::cout << "DEBUG: Mouse move input is now valid" << std::endl;


}




