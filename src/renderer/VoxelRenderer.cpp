#include "VoxelRenderer.h"


VoxelRenderer::VoxelRenderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera) {
	
	this->lighting = &lighting;
	this->camera = &camera;

	// register for events
	eventBus.AddListener(EventType::WindowResize, this);

}


VoxelRenderer::~VoxelRenderer() { }


void VoxelRenderer::OnEvent(Event& e) {

}


void VoxelRenderer::Prepare(void) {

}


void VoxelRenderer::DoFrame(void) {

}
