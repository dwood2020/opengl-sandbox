#pragma once
#include "CameraBase.h"
#include <glm/glm.hpp>
#include "../events/EventBus.h"
#include "../events/Event.hpp"


class SimpleCamera final : public CameraBase {
private:
	glm::mat4 V;
	glm::mat4 P;
	glm::vec2 windowRect;

public:
	SimpleCamera(EventBus& eventBus, const glm::vec2& windowRect, const glm::vec3& pos);
	~SimpleCamera();

	const glm::mat4& GetViewMatrix(void) const override;

	const glm::mat4& GetProjectionMatrix(void) const override;

	const glm::vec3& GetPosition(void) const override;

	void OnEvent(Event& e) override;

private:
	void CalcProjectionMatrix(void);

};



