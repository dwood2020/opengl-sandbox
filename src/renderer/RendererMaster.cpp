#include "RendererMaster.h"
#include "../glad/glad.h"


RendererMaster::RendererMaster(EventBus& eventBus) {

}


RendererMaster::~RendererMaster() { }


void RendererMaster::AddRenderer(RendererBase& renderer) {
	workerRenderers.push_back(&renderer);
}


void RendererMaster::SetClearColor(const glm::vec3& clearColor) {
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
}


void RendererMaster::InitRenderState(void) {


	glEnable(GL_DEPTH_TEST);
}


void RendererMaster::DoFrame(void) {

}



void RendererMaster::OnEvent(Event& e) {
	
}
