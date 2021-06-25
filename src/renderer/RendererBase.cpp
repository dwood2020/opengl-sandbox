#include "RendererBase.h"
#include "../glad/glad.h"


RendererBase::RendererBase() { }


RendererBase::~RendererBase() { }


void RendererBase::CalculateViewport(const glm::vec2& rect) {
	glViewport(0, 0, (GLsizei)rect.x, (GLsizei)rect.y);
}

