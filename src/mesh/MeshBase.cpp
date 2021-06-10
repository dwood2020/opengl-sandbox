#include "MeshBase.h"

MeshBase::MeshBase(): glMode(GL_POINTS) { }


MeshBase::~MeshBase() { }


void MeshBase::SetGlMode(GLenum glMode) {
	this->glMode = glMode;
}
