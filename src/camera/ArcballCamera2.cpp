#include "ArcballCamera2.h"

#include <iostream>


ArcballCamera2::ArcballCamera2(EventBus& eventBus, int wScreen, int hScreen, glm::vec3& pos):
	P(glm::mat4(1.0f)), lastMousePosNDC(glm::vec2(0.0f)),
	twinklebearInst(pos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) {

	screenRect.x = (float)wScreen;
	screenRect.y = (float)hScreen;

	CalcProjectionMatrix();
	V = glm::lookAt(pos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	eventBus.AddListener(EventType::WindowResize, this);
	eventBus.AddListener(EventType::MouseButton, this);
	eventBus.AddListener(EventType::MouseMove, this);
}


ArcballCamera2::~ArcballCamera2() { }


void ArcballCamera2::SetPosition(glm::vec3 pos) { }


const glm::vec3& ArcballCamera2::GetPosition(void) const {
	return twinklebearInst.eye();
}


const glm::mat4& ArcballCamera2::GetViewMatrix(void) const {
	//return twinklebearInst.transform();
	return V;
}


const glm::mat4& ArcballCamera2::GetProjectionMatrix(void) const {
	return P;
}


void ArcballCamera2::OnEvent(Event& e) {
	if (e.GetType() == EventType::WindowResize) {
		screenRect.x = (float)e.w;
		screenRect.y = (float)e.h;
		CalcProjectionMatrix();		
	}
	else if (e.GetType() == EventType::MouseButton) {
		OnMouseButton(e.mbCode, e.isPressed);
	}
	else if (e.GetType() == EventType::MouseMove) {
		OnMouseMove(e.xScreen, e.yScreen);
	}
}


void ArcballCamera2::OnMouseButton(MouseButtonCode mbCode, bool isPressed) {
	if (mbCode == MouseButtonCode::Left) {
		if (isPressed) {
			arcballOn = true;
		}
		else {
			arcballOn = false;
			//isFirstFrame = true;
		}
	}
}


void ArcballCamera2::OnMouseMove(int x, int y) {
	if (arcballOn) {
		glm::vec2 mousePos = glm::vec2((float)x, (float)y);
		glm::vec2 mousePosNDC = ScreenToNDC(mousePos);

		std::cout << "calling rotate on inst" << std::endl;
		twinklebearInst.rotate(lastMousePosNDC, mousePosNDC);

		lastMousePosNDC = mousePosNDC;

		V = glm::lookAt(twinklebearInst.eye(), glm::vec3(0.0f), twinklebearInst.up());
	}
}


void ArcballCamera2::CalcProjectionMatrix(void) {
	float w = screenRect.x;
	float h = screenRect.y;

	//TODO: revise this method

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


glm::vec2 ArcballCamera2::ScreenToNDC(glm::vec2& mousePos) const {
	glm::vec2 ndc = glm::vec2(0.0f);

	ndc.x = (2 * mousePos.x) / screenRect.x - 1.0f;
	ndc.y = 1.0f - (2 * mousePos.y) / screenRect.y;
	//ndc.y = ((2 * mousePos.y) / screenRect.y - 1.0f) * -1.0f;

	std::cout << "ndc: x: " << ndc.x << "  y: " << ndc.y << std::endl;
	
	return ndc;
}


