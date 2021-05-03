#include "ArcballCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <cmath>


ArcballCamera::ArcballCamera(EventBus& eventBus, int xScreen, int yScreen): CameraBase(),
	xScreen(xScreen), yScreen(yScreen) {

	eventBus.AddListener(EventType::WindowResize, this);
	eventBus.AddListener(EventType::MouseButton, this);
	eventBus.AddListener(EventType::MouseMove, this);
}


ArcballCamera::~ArcballCamera() { }


void ArcballCamera::SetPosition(glm::vec3 pos) {
	position = pos;
	CalcViewMatrix();
}


const glm::vec3& ArcballCamera::GetPosition(void) const {
	return position;
}


void ArcballCamera::OnEvent(Event& e) { 
	if (e.GetType() == EventType::WindowResize) {
		CalcProjectionMatrix(e.w, e.h);
	}
	else if (e.GetType() == EventType::MouseButton) {
		OnMouseButton(e.mbCode, e.isPressed);
	}
	else if (e.GetType() == EventType::MouseMove) {
		OnMouseMove(e.xScreen, e.yScreen);
	}
}


void ArcballCamera::OnMouseButton(MouseButtonCode mbCode, bool isPressed) {
	if (mbCode == MouseButtonCode::Left && isPressed == true) {
		arcballOn = true;
	}
	else {
		arcballOn = false;
	}
}


void ArcballCamera::OnMouseMove(int x, int y) {
	if (arcballOn == true) {

	}
}


void ArcballCamera::CalcProjectionMatrix(int wScreen, int hScreen) {

	float w = (float)wScreen;
	float h = (float)hScreen;

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


void ArcballCamera::CalcViewMatrix(void) {
	// FOR NOW this is identical to SimpleCamera calculation

	// calc V with lookAt function
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	V = glm::lookAt(position * -1.0f, target, up);
	VIsDirty = true;
}




