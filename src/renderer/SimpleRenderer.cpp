#include "SimpleRenderer.h"


SimpleRenderer::SimpleRenderer(): lighting(nullptr), camera(nullptr) { }


SimpleRenderer::SimpleRenderer(Lighting& lighting, CameraBase& camera): lighting(&lighting), camera(&camera) { }


SimpleRenderer::~SimpleRenderer() { }



void SimpleRenderer::AddCommand(const glm::mat4& modelMatrix, Mesh* mesh, MaterialBase* material) {
	if (mesh == nullptr || material == nullptr) {
		//TODO ASSERT or check if passing arg by reference is better option
		return;
	}

	RenderCommand command(modelMatrix, mesh, material);
	renderCommands.push_back(command);
}


void SimpleRenderer::PrepareCommands(void) {
	for (RenderCommand command : renderCommands) {

	}
}


void SimpleRenderer::ExecuteCommands(void) {

}

