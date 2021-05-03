#pragma once
#include "CameraBase.h"


class SimpleCamera final : public CameraBase {
private:
	bool lmbIsDown = false;
	float lastMouseX = 0.0f;
	float lastMouseY = 0.0f;

	const glm::vec3 up;

public:
	SimpleCamera();
	SimpleCamera(EventBus eventBus);
	~SimpleCamera();

	void OnEvent(Event& e) override;

private:
	void CalcViewMatrix(void) override;
	void CalcProjectionMatrix(int wScreen, int hScreen) override;

	void ProcessMouseButtonInput(MouseButtonCode mbCode, bool isPressed);
	void ProcessMouseMoveInput(int x, int y);

};


