#pragma once
#include <glm/glm.hpp>
#include "../events/Event.hpp"
#include "../events/EventBus.h"
#include "CameraBase.h"


class SimpleCamera : public CameraBase {
protected:
	glm::mat4 V;
	glm::mat4 P;

	glm::vec3 position;
	glm::vec3 target;

	bool lmbIsDown = false;
	glm::vec2 lastMousePos;

	const glm::vec3 up;


	SimpleCamera();

public:
	SimpleCamera(EventBus& eventBus);
	virtual ~SimpleCamera();

	void SetPosition(glm::vec3 pos) override;
	const glm::vec3& GetPosition(void) const override;

	const glm::mat4& GetViewMatrix(void) const override;
	const glm::mat4& GetProjectionMatrix(void) const override;

	void OnEvent(Event& e) override;

protected:
	void CalcProjectionMatrix(int wScreen, int hScreen);
	void CalcViewMatrix(void);

	void ProcessMouseButtonInput(MouseButtonCode mbCode, bool isPressed);
	void ProcessMouseMoveInput(int x, int y);

};



