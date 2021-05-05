#pragma once
#include <glm/glm.hpp>
#include "CameraBase.h"
#include "../events/EventBus.h"
#include "../arcball-cpp/arcball_camera.h"


class ArcballCamera2 final : public CameraBase {
private:
	glm::vec2 screenRect;
	glm::mat4 P;
	bool arcballOn = false;
	glm::vec2 lastMousePosNDC;

	TwinklebearArcballCamera twinklebearInst;

	//TEST
	glm::mat4 V = glm::mat4(1.0f);

public:
	ArcballCamera2(EventBus& eventBus, int wScreen, int hScreen, glm::vec3& pos);
	~ArcballCamera2();

	void SetPosition(glm::vec3 pos) override;
	const glm::vec3& GetPosition(void) const override;

	const glm::mat4& GetViewMatrix(void) const override;
	const glm::mat4& GetProjectionMatrix(void) const override;

	void OnEvent(Event& e) override;

private:
	void OnMouseButton(MouseButtonCode mbCode, bool isPressed);
	void OnMouseMove(int x, int y);

	void CalcProjectionMatrix(void);
	glm::vec2 ScreenToNDC(glm::vec2& mousePos) const;
};



