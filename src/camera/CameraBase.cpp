#include "CameraBase.h"


CameraBase::CameraBase(): 
	position(glm::vec3(0.0f)), target(glm::vec3(0.0f)),
	V(glm::mat4(1.0f)), P(glm::mat4(1.0f)) { }


CameraBase::~CameraBase() { }


void CameraBase::SetPosition(glm::vec3 pos) {
	position = pos;
	CalcViewMatrix();
}


const glm::vec3& CameraBase::GetPosition(void) const {
	return position;
}
