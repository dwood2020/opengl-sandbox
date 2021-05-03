#pragma once
#include <glm/glm.hpp>
#include "CameraBase.h"
#include "../events/EventBus.h"


class ArcballCamera final : public CameraBase {
private:
	int xMouseLast = 0;
	int yMouseLast = 0;
	bool arcballOn = false;

	int xScreen;
	int yScreen;

public:
	ArcballCamera(EventBus& eventBus, int xScreen, int yScreen);
	~ArcballCamera();

	void SetPosition(glm::vec3 pos) override;
	const glm::vec3& GetPosition(void) const override;

	void OnEvent(Event& e) override;

private:
	void OnMouseButton(MouseButtonCode mbCode, bool isPressed);
	void OnMouseMove(int x, int y);

	void CalcProjectionMatrix(int wScreen, int hScreen);
	void CalcViewMatrix(void);

};


