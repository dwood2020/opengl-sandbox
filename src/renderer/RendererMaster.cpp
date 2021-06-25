#include "RendererMaster.h"


RendererMaster::RendererMaster() { }


RendererMaster::~RendererMaster() { }


void RendererMaster::AddRenderer(RendererBase& renderer) {
	workerRenderers.push_back(&renderer);
}


void RendererMaster::InitRenderState(void) {

}
