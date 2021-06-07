#pragma once
#include <vector>

#include <glm/glm.hpp>

#include "../Mesh.h"
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


	void AddCommand(const glm::mat4& modelMatrix, Mesh* mesh, MaterialBase* material);


	void Prepare(void) override;


	void DoFrame(void) override;


	void OnEvent(Event& e) override;

private:
	void CalculateViewport(const glm::vec2& rect);

};

