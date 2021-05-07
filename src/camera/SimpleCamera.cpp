#include "SimpleCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>


SimpleCamera::SimpleCamera(EventBus& eventBus, const glm::vec2& windowRect, const glm::vec3& pos):
	V(glm::mat4(1.0f)), P(glm::mat4(1.0f)), windowRect(glm::vec2(0.0f)) {
	
	V = glm::translate(V, -pos);

	eventBus.AddListener(EventType::WindowResize, this);
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
