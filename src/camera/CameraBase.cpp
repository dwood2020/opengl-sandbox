#include "CameraBase.h"


CameraBase::CameraBase(): PVIsDirty(false) { }


CameraBase::~CameraBase() { }


bool CameraBase::GetViewProjectionMatrixIsDirty(void) const {
	return PVIsDirty;
}


void CameraBase::ResetDirtyState(void) {
	PVIsDirty = false;
}
