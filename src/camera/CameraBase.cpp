#include "CameraBase.h"


CameraBase::CameraBase(): VIsDirty(false), PIsDirty(false) { }


CameraBase::~CameraBase() { }


bool CameraBase::GetViewMatrixIsDirty(void) const {
	return VIsDirty;
}


bool CameraBase::GetProjectionMatrixIsDirty(void) const {
	return PIsDirty;
}

