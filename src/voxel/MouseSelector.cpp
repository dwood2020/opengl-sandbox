#include "MouseSelector.h"
#include <cmath>
#include "Bresenham3D.hpp"
#include "Section.h"

#include <iostream>


MouseSelector::MouseSelector(EventBus& eventBus, CameraBase& camera, WindowBase& window, VoxelScene& voxelScene, DynamicMesh& rayLineMesh): 
	camera(&camera), window(&window), voxelScene(&voxelScene), isActive(false), rayOrigin(glm::vec3(0.0f)), rayDirection(glm::vec3(0.0f)), isOrthoProjection(false) {

	this->rayLineMesh = &rayLineMesh;

	//TODO: mesh init
	//selectionMesh.GetVerticesPosNorm()

	eventBus.AddListener(EventType::ToggleSelectMode, this);
	eventBus.AddListener(EventType::MouseMove, this);
	eventBus.AddListener(EventType::ProjectionModeChanged, this);

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

		if (isOrthoProjection) {
			CalculateRayOrtho(emm.GetPositionX(), emm.GetPositionY());
		}
		else {
			CalculateRayPerspective(emm.GetPositionX(), emm.GetPositionY());
		}
		
		CheckCollisions();
	}

	if (e.GetType() == EventType::ProjectionModeChanged) {
		ProjectionModeChangedEvent& ep = (ProjectionModeChangedEvent&)e;
		if (ep.GetProjectionMode() == ProjectionMode::Orthographic) {
			isOrthoProjection = true;
		}
		else {
			isOrthoProjection = false;
		}
	}

	if (e.GetType() == EventType::Key) {
		KeyEvent& ek = (KeyEvent&)e;
		if (ek.GetKeyCode() == KeyCode::S && ek.GetIsKeydown() == true) {
			isActive = !isActive;
			std::cout << "KeyEvent received: MouseSelector::isActive: " << isActive << std::endl;
		}
	}	
}


void MouseSelector::CalculateRayPerspective(int mouseX, int mouseY) {	

	glm::vec2 mouseNDC = ScreenToNDC(glm::vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)));
		
	// procedure from antongerledan tutorial
	glm::mat4 Vinv = glm::inverse(camera->GetViewMatrix());
	glm::mat4 Pinv = glm::inverse(camera->GetProjectionMatrix());


	// homogenous clip coordinates
	glm::vec4 rayClip = glm::vec4(mouseNDC, -1.0f, 1.0f);

	// eye coordinates
	glm::vec4 rayEye = Pinv * rayClip;
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

	// world coordinates
	glm::vec4 rayWorldH = Vinv * rayEye;
	glm::vec3 rayWorld = glm::vec3(rayWorldH.x, rayWorldH.y, rayWorldH.z);	// correct retransformation from homogenous coords is omitted due to following normalization
	rayWorld = glm::normalize(rayWorld);

	rayDirection = rayWorld;
	rayOrigin = camera->GetPosition();	

	// Debug ray line 
	(rayLineMesh->GetVerticesPosNorm())[0].pos = rayOrigin;				
	rayLineMesh->GetVerticesPosNorm()[1].pos = rayOrigin + 100.0f * rayDirection;	
	rayLineMesh->Update();	

}


void MouseSelector::CalculateRayOrtho(int mouseX, int mouseY) {

	glm::mat4 Pinv = glm::inverse(camera->GetProjectionMatrix());
	glm::mat4 Vinv = glm::inverse(camera->GetViewMatrix());

	glm::vec2 mouseNDC = ScreenToNDC(glm::vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)));

	rayDirection = glm::normalize(camera->GetTarget() - camera->GetPosition());
	//std::cout << "rayDirection: [" << rayDirection.x << " " << rayDirection.y << " " << rayDirection.z << "]" << std::endl;

	glm::vec4 mouseClip = glm::vec4(mouseNDC, 0.0f, 1.0f);
	
	//glm::vec4 mouseView = Pinv * glm::vec4(mouseNDC, 0.0f, 1.0f);
	glm::vec4 mouseView = Pinv * mouseClip;
	
	
	glm::vec4 mouseWorld = Vinv * mouseView;
	mouseWorld += glm::vec4(camera->GetPosition(), 0.0f);

	std::cout << "mouseWorld: [" << mouseWorld.x << " " << mouseWorld.y << " " << mouseWorld.z << "]" << std::endl;

	//TODO: Consider Camera Position!

	rayOrigin = mouseWorld;

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


void MouseSelector::CheckCollisions(void) {

	// destination point of ray
	glm::vec3 rayDest = rayOrigin + 100.0f * rayDirection;
	glm::ivec3 rayDestI = Section::FloatToInt(rayDest);
	glm::ivec3 rayOriginI = Section::FloatToInt(rayOrigin);

	//Bresenham3D(rayOriginI.x, rayOriginI.y, rayOriginI.z, rayDestI.x, rayDestI.y, rayDestI.z, voxelScene, -1);


	// custom super simple, dumb ray traversion
	// ----------------------------------------

	rayOrigin = TruncPrecision(rayOrigin);
	rayDirection = TruncPrecision(rayDirection);

	glm::vec3 traversionPos = (rayOrigin);
	glm::vec3 traversionPosI = Section::FloatToInt(traversionPos);

	float tEnd;
	float dt;
	if (isOrthoProjection) {
		tEnd = 200.0f;
		dt = 0.5f;
	}
	else {
		tEnd = 100.0f;
		dt = 0.2f;
	}

	for (float tStep = 0.0f; tStep < tEnd; tStep += dt) {
		traversionPos = rayOrigin + tStep * rayDirection;
		traversionPosI = Section::FloatToInt(traversionPos);

		if (voxelScene->GetBlock(traversionPosI) != 0) {
			//DEBUG:
			std::cout << "Found block: Float value (" << traversionPos.x << " " << traversionPos.y << " " << traversionPos.z 
				<< ") [" << traversionPosI.x << " " << traversionPosI.y << " " << traversionPosI.z << "]: " << (int)(voxelScene->GetBlock(traversionPosI)) << std::endl;
			
			DoSelection(traversionPosI);
			break;
		}
	}

	DoUnselection();
}


void MouseSelector::DoSelection(const glm::ivec3& blockPos) {

}


void MouseSelector::DoUnselection(void) {

}


glm::vec3 MouseSelector::TruncPrecision(const glm::vec3& v) {
	
	glm::vec3 vtrunc = v;

	for (unsigned int i = 0; i < 3; i++) {
		vtrunc[i] = trunc(v[i] * 100.0f) / 100.0f;
	}
	return vtrunc;
}


