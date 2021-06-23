#include "RendererBase.h"
#include "../glad/glad.h"


RendererBase::RendererBase() { }


RendererBase::~RendererBase() { }


void RendererBase::SetClearColor(const glm::vec3& clearColor) {
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
}


void RendererBase::CalculateViewport(const glm::vec2& rect) {
	glViewport(0, 0, (GLsizei)rect.x, (GLsizei)rect.y);
}

