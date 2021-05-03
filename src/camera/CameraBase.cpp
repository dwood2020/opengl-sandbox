#include "CameraBase.h"


CameraBase::CameraBase(): 
	position(glm::vec3(0.0f)), target(glm::vec3(0.0f)),
	V(glm::mat4(1.0f)), P(glm::mat4(1.0f)) { }


CameraBase::~CameraBase() { }

