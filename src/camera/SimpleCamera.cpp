#include "SimpleCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <cmath>
#include <algorithm>

#include <iostream>


SimpleCamera::SimpleCamera(EventBus& eventBus, const glm::vec2& windowRect, const glm::vec3& pos):
	V(glm::mat4(1.0f)), P(glm::mat4(1.0f)), windowRect(windowRect),
	lmbIsDown(false), mmbIsDown(false), isFirstFrame(true), lastMousePosNDC(glm::vec2(0.0f)),
	target(glm::vec3(0.0f)) {
	
	rho = glm::length(target - pos);
	phi = 0.0f;
	theta = 0.0f;

	/*V = glm::translate(V, glm::vec3(0.0f, 0.0f, rho));
	position = glm::column(V, 3);
	V = glm::inverse(V);*/
	
	UpdateViewMatrixAndPosition();
	//std::cout << "position: " << position.x << " " << position.y << " " << position.z << std::endl;

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
	return position;
}


void SimpleCamera::OnEvent(Event& e) {
	if (e.GetType() == EventType::WindowResize) {
		WindowResizeEvent& eResize = (WindowResizeEvent&)e;
		windowRect.x = (float)eResize.GetScreenWidth();
		windowRect.y = (float)eResize.GetScreenHeight();
		CalcProjectionMatrix();
	}
	else if (e.GetType() == EventType::MouseButton) {
		MouseButtonEvent& etmp = (MouseButtonEvent&)e;
		ProcessMouseButtonInput(((MouseButtonEvent&)e).GetMbCode(), etmp.GetIsPressed());
	}
	else if (e.GetType() == EventType::MouseMove) {
		MouseMoveEvent& emm = (MouseMoveEvent&)e;
		ProcessMouseMoveInput(emm.GetPositionX(), emm.GetPositionY());
	}
}


void SimpleCamera::ProcessMouseButtonInput(MouseButtonCode mbCode, bool isPressed) {
	if (mbCode == MouseButtonCode::Left) {
		if (isPressed) {
			lmbIsDown = true;
		}
		else {
			lmbIsDown = false;
			isFirstFrame = true;
		}
	}
	else if (mbCode == MouseButtonCode::Middle) {
		if (isPressed) {
			mmbIsDown = true;
		}
		else {
			mmbIsDown = false;
			isFirstFrame = true;
		}
	}
}


void SimpleCamera::ProcessMouseMoveInput(int x, int y) {
	if (lmbIsDown) {
		PerformRotation((float)x, (float)y);		
	}
	else if (mmbIsDown) {
		PerformTranslation((float)x, (float)y);
	}
	
}


void SimpleCamera::PerformRotation(float x, float y) {

	glm::vec2 posMouse = ScreenToNDC(glm::vec2(x, y));
	glm::vec2 delta = DeltaNDC(posMouse);

	lastMousePosNDC = posMouse;

	if (isFirstFrame) {
		isFirstFrame = false;
		return;
	}

	float factor = ((windowRect.x + windowRect.y) / 2.0f) / 7.0f;
	delta *= factor;

	theta = std::clamp(theta + delta.y, -90.0f, 90.0f);
	phi = std::fmodf(phi + delta.x, 360.0f);
	//NOTE rho is untouched (no zooming atm)

	//std::cout << "rho: " << rho << "  phi: " << phi << "  theta: " << theta << std::endl;

	// refer to this for calculations:
	// https://stackoverflow.com/questions/40195569/arcball-camera-inverting-at-90-deg-azimuth

	// NOTE all previous matrix calculations have been moved here:
	UpdateViewMatrixAndPosition();
}


void SimpleCamera::PerformTranslation(float x, float y) {
	
	glm::vec2 posMouse = ScreenToNDC(glm::vec2(x, y));
	glm::vec2 delta = DeltaNDC(posMouse);

	lastMousePosNDC = posMouse;

	if (isFirstFrame) {
		isFirstFrame = false;
		return;
	}


	const float rightScale = -1.5f;
	const float upScale = 1.5f;
	const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// calculation:
	// retrieve camera right and up vector (normalized), multiply with deltas and add to current target (and pos)

	glm::vec3 dir = target - position;
	
	glm::vec3 right = glm::normalize(glm::cross(dir, worldUp));
	glm::vec3 up = glm::normalize(glm::cross(dir, right));

	glm::vec3 deltaPan = (right * delta.x * rightScale) + (up * delta.y * upScale);

	target = target + deltaPan;
	position = position + deltaPan;

	UpdateViewMatrixAndPosition();
}


void SimpleCamera::UpdateViewMatrixAndPosition(void) {

	const float xInputInv = -1.0f;
	const float yInputInv = 1.0f;

	// these steps calculate the transformation matrix camera->world	
	V = glm::mat4(1.0f);

	V = glm::translate(V, target);

	V = glm::rotate(V, glm::radians(phi) * xInputInv, glm::vec3(0.0f, 1.0f, 0.0f));
	V = glm::rotate(V, glm::radians(theta) * yInputInv, glm::vec3(1.0f, 0.0f, 0.0f));

	V = glm::translate(V, glm::vec3(0.0f, 0.0f, rho));

	// update position before inverting the matrix, because
	// position is the position in world coordinates
	position = glm::column(V, 3);
	std::cout << "position: " << position.x << " " << position.y << " " << position.z << std::endl;

	// V is actually V^-1, as the View matrix is defined to be the transformation world->camera
	V = glm::inverse(V);

	VIsDirty = true;
}


void SimpleCamera::CalcProjectionMatrix(bool asOrthographic) {
	
	float w = windowRect.x;
	float h = windowRect.y;	

	if (asOrthographic) {
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
	// here, a matrix/vector transformation is used.
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
	
	// zero crossing problems are avoided by a simple transformation (pure translation)

	const glm::vec2 b = glm::vec2(1.0f, 1.0f);

	glm::vec2 posShifted = posNDC + b;
	glm::vec2 lastPosShifted = lastMousePosNDC + b;

	return posShifted - lastPosShifted;
}
