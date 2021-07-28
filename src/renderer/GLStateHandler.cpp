#include "GLStateHandler.h"
#include "../glad/glad.h"


GLStateHandler::GLStateHandler(): 
	depthTestingEnabled(false), blendingEnabled(false), faceCullingEnabled(false) { }


GLStateHandler::~GLStateHandler() { }


void GLStateHandler::SetDepthTesting(bool state) {
	if (state && !depthTestingEnabled) {
		glEnable(GL_DEPTH_TEST);
	}
	else if (!state && depthTestingEnabled) {
		glDisable(GL_DEPTH_TEST);
	}
}


void GLStateHandler::SetBlending(bool state) {
	if (state && !blendingEnabled) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else if (!state && blendingEnabled) {
		glDisable(GL_BLEND);
	}
}


void GLStateHandler::SetFaceCulling(bool state) {
	if (state && !faceCullingEnabled) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}
	else if (!state && faceCullingEnabled) {
		glDisable(GL_CULL_FACE);
	}
}
