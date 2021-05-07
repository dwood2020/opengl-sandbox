#include "ArcballCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <cmath>
#include <algorithm>

#include <iostream>

ArcballCamera::ArcballCamera(EventBus& eventBus, int wScreen, int hScreen, glm::vec3& pos): CameraBase(),
	V(glm::mat4(1.0f)), P(glm::mat4(1.0f)),
	position(pos), target(glm::vec3(0.0f)),
	wScreen(wScreen), hScreen(hScreen) {

	//calc initial right and up vector
	// this should be done outside and passed into ctor (future?)
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 dir = target - position;
	right = glm::normalize(glm::cross(dir, up));
	CalcViewMatrix();


	eventBus.AddListener(EventType::WindowResize, this);
	eventBus.AddListener(EventType::MouseButton, this);
	eventBus.AddListener(EventType::MouseMove, this);
}


ArcballCamera::~ArcballCamera() { }


void ArcballCamera::SetPosition(glm::vec3 pos) {
	/*position = pos;
	CalcViewMatrix();*/
}


const glm::vec3& ArcballCamera::GetPosition(void) const {
	return position;
}


const glm::mat4& ArcballCamera::GetViewMatrix(void) const {
	return V;
}

const glm::mat4& ArcballCamera::GetProjectionMatrix(void) const {
	return P;
}


void ArcballCamera::OnEvent(Event& e) { 
	if (e.GetType() == EventType::WindowResize) {
		CalcProjectionMatrix(e.w, e.h);
		wScreen = e.w;
		hScreen = e.h;
	}
	else if (e.GetType() == EventType::MouseButton) {
		OnMouseButton(e.mbCode, e.isPressed);
	}
	else if (e.GetType() == EventType::MouseMove) {
		OnMouseMove(e.xScreen, e.yScreen);
	}
}


void ArcballCamera::OnMouseButton(MouseButtonCode mbCode, bool isPressed) {
	if (mbCode == MouseButtonCode::Left) {
		if (isPressed) {
			arcballOn = true;
		}
		else {
			arcballOn = false;
			isFirstFrame = true;
		}
	}	
}


void ArcballCamera::OnMouseMove(int x, int y) {
	if (arcballOn == true) {
		CalcArcball(x, y);
	}
}


void ArcballCamera::CalcArcball(int xInp, int yInp) {

	// see here:
	// https://braintrekking.wordpress.com/2012/08/21/tutorial-of-arcball-without-quaternions/
	

	//TODO: move float conversion outside, dont convert on every calculation but only when screen is resized

	

	// transform coordinates
	float w = (float)wScreen;
	float h = (float)hScreen;

	float r = (float)std::min(wScreen, hScreen) / 2.0f;
	float x = ((float)xInp - w / 2.0f) / r;
	float y = (((float)yInp - h / 2.0f) / r) * -1.0f;	

	// calculate z-coordinate on ball
	float z;
	float rho = std::sqrtf(x * x + y * y);
	if (rho < 1.0f) {
		z = std::sqrtf(1.0f - x * x - y * y);
	}
	else {
		z = 0.0f;
	}

	// prevent "hopping" of view when releasing mouse and clicking in another position
	if (isFirstFrame) {
		isFirstFrame = false;
		xLast = x;
		yLast = y;
		zLast = z;
		return;
	}

	
	// calculate start and end vectors p1 and p2
	const glm::vec3 ballCenter = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 p1 = glm::vec3(xLast, yLast, zLast) - ballCenter;
	glm::vec3 p2 = glm::vec3(x, y, z) - ballCenter;

	// calculate angle theta between p1, p2 and cross product of p1,p2
	// cross product u is the rotation axis
	//float theta = std::acosf(std::min(glm::dot(p1, p2), 1.0f) / (glm::length(p2) * glm::length(p1)));
	float theta = glm::angle(glm::normalize(p1), glm::normalize(p2));	
	glm::vec3 u = glm::normalize(glm::cross(p1, p2));
	

	// use glm lookat function:
	// therefore transformation into homogenous coordinates (R4) is needed
	const float factor = 1.5f;
	glm::mat4 R = glm::rotate(glm::mat4(1.0f), theta * -1.0f * factor, u);

	glm::vec4 pos4 = glm::vec4(position.x, position.y, position.z, 1.0f);	
	glm::vec4 up4 = glm::vec4(up.x, up.y, up.z, 1.0f);
	pos4 = R * pos4;
	up4 = R * up4;

	// perform an isnan check as quick fix
	// (possible with C++11)
	if (std::isnan(pos4.x) || std::isnan(pos4.y) || std::isnan(pos4.z)) {
		std::cout << "ERROR::ARCBALLCAMERA::CALCARCBALL: calculated pos4 isnan" << std::endl;
		return;
	}
	if (std::isnan(up4.x) || std::isnan(up4.y) || std::isnan(up4.z)) {
		std::cout << "ERROR::ARCBALLCAMERA::CALCARCBALL: calculated up4 is nan" << std::endl;
		return;
	}

	position.x = pos4.x;
	position.y = pos4.y;
	position.z = pos4.z;

	up.x = up4.x;
	up.y = up4.y;
	up.z = up4.z;

	std::cout << "position x: " << position.x << "  y: " << position.y << " z: " << position.z << std::endl;

	// try: calc a different up vector
	/*glm::vec3 dir = target - position;
	glm::vec3 right = glm::normalize(glm::cross(dir, glm::vec3(0.0f, 1.0f, 0.0f)));
	glm::vec3 up = glm::normalize(glm::cross(right, dir));*/

	//V = glm::lookAt(position, target, up);
	//VIsDirty = true;

	CalcViewMatrix();

	xLast = x;
	yLast = y;
	zLast = z;
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

	// calc V with lookAt function	

	V = glm::lookAt(position * -1.0f, target, up);
	VIsDirty = true;
}







