#include "RendererMaster.h"


RendererMaster::RendererMaster(EventBus& eventBus, CameraBase& camera): camera(&camera) { }


RendererMaster::~RendererMaster() { }


void RendererMaster::AddRenderer(RendererBase& renderer) {
	workerRenderers.push_back(&renderer);
}


void RendererMaster::SetClearColor(const glm::vec3& clearColor) {
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
}


void RendererMaster::SetGlPolygonMode(GLenum mode) {
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}


void RendererMaster::InitRenderState(const glm::vec2& windowRect) {

	// first viewport calculation
	if (workerRenderers.size() > 0) {
		workerRenderers[0]->CalculateViewport(windowRect);
	}

	glEnable(GL_DEPTH_TEST);
}


void RendererMaster::PrepareRenderers(void) {
	for (RendererBase* worker : workerRenderers) {
		worker->Prepare();
	}
}


void RendererMaster::DoFrame(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (RendererBase* worker : workerRenderers) {
		worker->DoFrame();
	}

	if (camera->GetViewProjectionMatrixIsDirty() == true) {
		camera->ResetDirtyState();
	}
}



void RendererMaster::OnEvent(Event& e) {
	
}
