#include "SimpleCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <cmath>
#include <algorithm>

#include <iostream>


SimpleCamera::SimpleCamera(EventBus& eventBus, const glm::vec2& windowRect, const glm::vec3& pos):
	V(glm::mat4(1.0f)), P(glm::mat4(1.0f)), windowRect(glm::vec2(0.0f)),
	lmbIsDown(false), lastMousePosNDC(glm::vec2(0.0f)),
	target(glm::vec3(0.0f)) {
	
	rho = glm::length(target - pos);
	phi = 0.0f;
	theta = 0.0f;

	V = glm::translate(V, glm::vec3(0.0f, 0.0f, rho));
	V = glm::inverse(V);

	eventBus.AddListener(EventType::WindowResize, this);
	eventBus.AddListener(EventType::MouseButton, this);
	eventBus.AddListener(EventType::MouseMove, this);
}


SimpleCamera::~SimpleCamera() { }


const glm::mat4& SimpleCamera::GetViewMatrix(void) const {
	return V;
}


const glm::mat4& SimpleCamera::GetProjectionMatrix(void) const {
	return P;
}


const glm::vec3& SimpleCamera::GetPosition(void) const {
	return glm::column(V, 3);
}


void SimpleCamera::OnEvent(Event& e) {
	if (e.GetType() == EventType::WindowResize) {
		windowRect.x = (float)e.w;
		windowRect.y = (float)e.h;
		CalcProjectionMatrix();
	}
	else if (e.GetType() == EventType::MouseButton) {
		ProcessMouseButtonInput(e.mbCode, e.isPressed);
	}
	else if (e.GetType() == EventType::MouseMove) {
		ProcessMouseMoveInput(e.xScreen, e.yScreen);
	}
}


void SimpleCamera::ProcessMouseButtonInput(MouseButtonCode mbCode, bool isPressed) {
	if (mbCode == MouseButtonCode::Left) {
		if (isPressed) {
			lmbIsDown = true;
		}
		else {
			lmbIsDown = false;
		}
	}
}


void SimpleCamera::ProcessMouseMoveInput(int x, int y) {
	if (!lmbIsDown) {
		return;
	}

	glm::vec2 posMouse = ScreenToNDC(glm::vec2((float)x, (float)y));
	glm::vec2 delta = DeltaNDC(posMouse);

	const float factor = 100.0f;
	delta *= factor;

	theta = std::clamp(theta + delta.y, -90.0f, 90.0f);
	phi = std::fmodf(phi + delta.x, 360.0f);
	//NOTE rho is untouched (no zooming atm)

	// refer to this for calculations:
	// https://stackoverflow.com/questions/40195569/arcball-camera-inverting-at-90-deg-azimuth

	V = glm::mat4(1.0f);
	V = glm::rotate(V, glm::radians(theta + 90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	V = glm::rotate(V, glm::radians(phi), glm::vec3(0.0f, 1.0f, 0.0f));
	V = glm::translate(V, glm::vec3(0.0f, 0.0f, rho));
	V = glm::inverse(V);
	VIsDirty = true;

	lastMousePosNDC = posMouse;
}


void SimpleCamera::CalcProjectionMatrix(void) {
	
	float w = windowRect.x;
	float h = windowRect.y;

	const bool isOrthographic = false;

	if (isOrthographic) {
		// orthographic projection
		w = w / 100.0f;
		h = h / 100.0f;
		P = glm::ortho(-w / 2.0f, w / 2.0f, -h / 2.0f, h / 2.0f, 1.0f, 100.0f);
	}
	else {
		// perspective projection
		P = glm::perspective(glm::radians(45.0f), w / h, 1.0f, 100.0f);
	}

	PIsDirty = true;
}


glm::vec2 SimpleCamera::ScreenToNDC(const glm::vec2& posScreen) const {
	
	// this could be done in homogenous coordinates or with a 
	// matrix/vector transformation, or simply in the linearised form	

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


glm::vec2 SimpleCamera::DeltaNDC(const glm::vec2& posNDC) const {
	
	const glm::vec2 b = glm::vec2(1.0f, 1.0f);

	glm::vec2 posShifted = posNDC + b;
	glm::vec2 lastPosShifted = lastMousePosNDC + b;

	return posShifted - lastPosShifted;
}
