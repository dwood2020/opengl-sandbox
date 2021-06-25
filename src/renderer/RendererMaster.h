#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../glad/glad.h"
#include "RendererBase.h"
#include "../events/EventListener.hpp"
#include "../events/EventBus.h"
#include "../events/Event.hpp"
#include "../camera/CameraBase.h"


class RendererMaster : public EventListener {
private:
	std::vector<RendererBase*> workerRenderers;
	CameraBase* camera;

	RendererMaster() = default;

public:
	RendererMaster(EventBus& eventBus, CameraBase& camera);

	virtual ~RendererMaster();


	void AddRenderer(RendererBase& renderer);


	void SetClearColor(const glm::vec3& clearColor);


	void SetGlPolygonMode(GLenum mode);


	void InitRenderState(const glm::vec2& windowRect);


	void PrepareRenderers(void);


	void DoFrame(void);


	void OnEvent(Event& e) override;

};

