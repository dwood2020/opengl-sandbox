#include "MouseSelector.h"
#include <cmath>
#include "Bresenham3D.hpp"
#include "Section.h"

#include <iostream>


MouseSelector::MouseSelector(EventBus& eventBus, CameraBase& camera, WindowBase& window, VoxelScene& voxelScene, DynamicMesh& rayLineMesh): 
	camera(&camera), window(&window), voxelScene(&voxelScene), isActive(false), rayOrigin(glm::vec3(0.0f)), rayDirection(glm::vec3(0.0f)) {

	this->rayLineMesh = &rayLineMesh;

	eventBus.AddListener(EventType::ToggleSelectMode, this);
	eventBus.AddListener(EventType::MouseMove, this);

	eventBus.AddListener(EventType::Key, this);
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
		DoSelection();
	}

	if (e.GetType() == EventType::Key) {
		KeyEvent& ek = (KeyEvent&)e;
		if (ek.GetKeyCode() == KeyCode::S && ek.GetIsKeydown() == true) {
			isActive = !isActive;
			std::cout << "KeyEvent received: MouseSelector::isActive: " << isActive << std::endl;
		}
	}
}


void MouseSelector::CalculateRay(int mouseX, int mouseY) {	

	glm::vec2 mouseNDC = ScreenToNDC(glm::vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)));
	
	/*glm::mat4 Vinv = glm::inverse(camera->GetViewMatrix());
	glm::mat4 Pinv = glm::inverse(camera->GetProjectionMatrix());*/


	// same procedure as in ThinMatrix tutorial
	//glm::vec4 clipCoords = glm::vec4(mouseNDC.x, mouseNDC.y, 1.0f, 1.0f);

	////to eye coords
	//glm::vec4 eyeCoords = Pinv * clipCoords;
	//eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, 1.f, 1.f);

	////to world coords
	//glm::vec4 rayWorld = Vinv * eyeCoords;
	//glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	//mouseRay = glm::normalize(mouseRay);

	//rayDirection = mouseRay;
	//rayDirection.z *= -1.f;
	//rayOrigin = camera->GetPosition();

	//std::cout << rayDirection.x << " " << rayDirection.y << " " << rayDirection.z << std::endl;

	glm::mat4 PVinv = glm::inverse(camera->GetViewProjectionMatrix());
	glm::vec4 clipCoords = glm::vec4(mouseNDC.x, mouseNDC.y, 1.0f, 1.0f);
	

	rayDirection = glm::normalize(PVinv * clipCoords);
	rayOrigin = camera->GetPosition();



	(rayLineMesh->GetVerticesPosNorm())[0].pos = rayOrigin;	
	
	//(rayLineMesh->GetVerticesPosNorm())[0].pos = rayOrigin + glm::vec3(0.1f, 0.1f, 0.1f);
	
	//std::cout << (rayLineMesh->GetVerticesPosNorm())[0].pos.x << " " << (rayLineMesh->GetVerticesPosNorm())[0].pos.y << " " << (rayLineMesh->GetVerticesPosNorm())[0].pos.z << std::endl;
	rayLineMesh->GetVerticesPosNorm()[1].pos = rayOrigin + 100.0f * rayDirection;	
	//(rayLineMesh->GetVerticesPosNorm())[0].pos = glm::vec3(0.0f);
	rayLineMesh->Update();

	//std::cout << rayDirection.x << " " << rayDirection.y << " " << rayDirection.z << std::endl;

	/*rayDirection = NDCToWorld(mouseNDC);
	rayOrigin = camera->GetPosition();*/

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


void MouseSelector::DoSelection(void) {

	// destination point of ray
	glm::vec3 rayDest = rayOrigin + 100.0f * rayDirection;
	//std::cout << "rayDest: [" << rayDest.x << " " << rayDest.y << " " << rayDest.z << "]" << std::endl;

	glm::ivec3 rayDestI = Section::FloatToInt(rayDest);
	//std::cout << "rayDestI: [" << rayDestI.x << " " << rayDestI.y << " " << rayDestI.z << "]" << std::endl;

	glm::ivec3 rayOriginI = Section::FloatToInt(rayOrigin);
	//std::cout << "rayOriginI: [" << rayOriginI.x << " " << rayOriginI.y << " " << rayOriginI.z << "]" << std::endl;

	//TODO: Write custom float to int conversion method! Section::... does not handle positions < 0 correctly!

	//Bresenham3D(rayOriginI.x, rayOriginI.y, rayOriginI.z, rayDestI.x, rayDestI.y, rayDestI.z, voxelScene, -1);

	// custom super simple, dumb ray traversion

	//rayOrigin = TruncPrecision(rayOrigin);
	//rayDirection = TruncPrecision(rayDirection);

	glm::vec3 traversionPos = (rayOrigin);
	glm::vec3 traversionPosI = Section::FloatToInt(traversionPos);

	for (float dt = 0.f; dt < 100.f; dt += 0.1f) {
		traversionPos = rayOrigin + dt * rayDirection;
		//traversionPos = TruncPrecision(traversionPos);
		traversionPosI = Section::FloatToInt(traversionPos);

		if (voxelScene->GetBlock(traversionPosI) != 0) {
			std::cout << "Found block: Float value (" << traversionPos.x << " " << traversionPos.y << " " << traversionPos.z 
				<< ") [" << traversionPosI.x << " " << traversionPosI.y << " " << traversionPosI.z << "]: " << (int)(voxelScene->GetBlock(traversionPosI)) << std::endl;
			break;
		}
	}


}


glm::vec3 MouseSelector::TruncPrecision(const glm::vec3& v) {
	
	glm::vec3 vtrunc = v;

	for (unsigned int i = 0; i < 3; i++) {
		vtrunc[i] = trunc(v[i] * 100.0f) / 100.0f;
	}
	return vtrunc;
}


