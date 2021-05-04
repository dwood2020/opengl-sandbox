#include "ArcballCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <cmath>
#include <algorithm>

#include <iostream>

ArcballCamera::ArcballCamera(EventBus& eventBus, int wScreen, int hScreen): CameraBase(),
	wScreen(wScreen), hScreen(hScreen) {

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
		CalcArcball(x, y);
	}
}


//void ArcballCamera::CalcArcball(int xInp, int yInp) {
//		
//	// see here:
//	// https://braintrekking.wordpress.com/2012/08/21/tutorial-of-arcball-without-quaternions/
//	//
//
//	/*float dx = xInp - xScrLast;
//	float dy = yInp - yScrLast;
//	float delta = std::sqrtf(dx * dx + dy * dy);
//
//	xScrLast = xInp;
//	yScrLast = yInp;*/
//
//	// map screen coords to normalized coords (-1, 1)
//	float x = ((float)xInp * 2.0f) / (float)wScreen - 1.0f;
//	float y = ((float)yInp * 2.0f) / (float)hScreen - 1.0f;
//
//	//NOTE: The sphere is currently distorted!
//	// do a different transformation by using max(w,h) as r!
//
//	// sample to a sphere
//	float r = 1.0f;		// this is 1 because screen coords are already transformed
//	float rho = std::sqrtf(x * x + y * y);
//
//	// sphere formula:
//	//		x^2 + y^2 + z^2 = r^2 = 1
//	// <=>	sqrt(r^2 - x^2 -y^2) = abs(z)
//
//	float z;
//	if (rho < r) {
//		z = std::sqrtf(r * r - x * x - y * y);
//	}
//	else {
//		z = 0.0f;
//	}
//
//	// define start vector 
//	glm::vec3 p1 = glm::vec3(xLast, yLast, zLast);
//
//	// define end vector
//	glm::vec3 p2 = glm::vec3(x, y, z);
//
//	// compute angle theta between start and end vector
//	//float theta = std::acosf(glm::dot(p1, p2) / (glm::length(p2) * glm::length(p1)));
//	float theta = glm::angle(p1, p2);
//	std::cout << "theta: " << theta << std::endl;
//
//	// compute rotation axis u
//	glm::vec3 u = glm::normalize(glm::cross(p1, p2));
//
//	// calculate unsigned delta (in transformed system!)
//	/*float dx = x - xLast;
//	float dy = y - yLast;	
//	float delta = std::sqrtf(dx * dx + dy * dy);*/
//	float delta = glm::length(p2 - p1);
//
//	const float factor = 1.0f;
//
//	// define rotation matrix
//	glm::mat4 R = glm::mat4(1.0f);
//	R = glm::rotate(R, delta * factor, u);
//
//	// go into homogenous coordinates (to make multiplication with matrix possible)
//	glm::vec4 pos4 = glm::vec4(position.x, position.y, position.z, 1.0f);
//	pos4 = pos4 * R;
//
//	// u is camera right vector
//	glm::vec3 dir = target - position;
//	glm::vec3 up = glm::normalize(glm::cross(u, dir));
//
//	// apply new position to vec3 position attribute
//	position.x = pos4.x / pos4.w;
//	position.y = pos4.y / pos4.w;
//	position.z = pos4.z / pos4.w;
//
//	std::cout << "position: " << position.x << "  " << position.y << "  " << position.z << std::endl;
//
//	xLast = x;
//	yLast = y;
//	zLast = z;
//
//	// apply to View Matrix
//	V = glm::lookAt(position * -1.0f, target, up);
//	VIsDirty = true;
//}


void ArcballCamera::CalcArcball(int xInp, int yInp) {

	//TODO: move float conversion outside, dont convert on every calculation but only when screen is resized
	//TODO: Subscribe to & handle screenresize event!

	// transform coordinates
	float w = (float)wScreen;
	float h = (float)hScreen;

	float r = (float)std::min(wScreen, hScreen) / 2.0f;
	float x = ((float)xInp - w / 2.0f) / r;
	float y = (((float)yInp - h / 2.0f) / r) * -1.0f;	

	//std::cout << "r: " << r << "  x: " << x << "   y: " << y << std::endl;
	// ... transformation now working



}


float ArcballCamera::ZCoord(float r, float rho, float x, float y) const {
	if (rho < r) {
		return std::sqrtf(r * r - x * x - y * y);
	}
	else {
		return 0.0f;
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






