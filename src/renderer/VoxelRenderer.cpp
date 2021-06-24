#include "VoxelRenderer.h"


VoxelRenderer::VoxelRenderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera, const glm::vec2& windowRect) {
	
	this->lighting = &lighting;
	this->camera = &camera;

	// register for events
	eventBus.AddListener(EventType::WindowResize, this);

	// initialize rendering	
	CalculateViewport(windowRect);
}


VoxelRenderer::~VoxelRenderer() { }


void VoxelRenderer::OnEvent(Event& e) {

}


void VoxelRenderer::Prepare(void) {

}


void VoxelRenderer::DoFrame(void) {

}
