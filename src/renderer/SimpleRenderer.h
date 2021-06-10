#pragma once
#include <vector>

#include <glm/glm.hpp>

#include "../mesh/StaticMesh.h"
#include "../material/MaterialBase.h"
#include "../Lighting.h"
#include "../camera/CameraBase.h"
#include "RendererBase.h"
#include "RenderCommand.hpp"


class SimpleRenderer final : public RendererBase {
private:
	Lighting* lighting;
	CameraBase* camera;

	std::vector<RenderCommand> renderCommands;

public:
	SimpleRenderer();

	SimpleRenderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera, const glm::vec2& windowRect);

	~SimpleRenderer();


	void SetClearColor(const glm::vec3& clearColor);


	void AddCommand(const glm::mat4& modelMatrix, MeshBase* mesh, MaterialBase* material);


	void Prepare(void) override;


	void DoFrame(void) override;


	void OnEvent(Event& e) override;


};

