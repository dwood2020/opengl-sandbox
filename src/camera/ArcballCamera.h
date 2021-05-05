#pragma once
#include <glm/glm.hpp>
#include "CameraBase.h"
#include "../events/EventBus.h"


class ArcballCamera final : public CameraBase {
private:
	// last positions in transformed arcball coordinates
	float xLast = 0.0f;
	float yLast = 0.0f;
	float zLast = 1.0f;

	bool arcballOn = false;
	bool isFirstFrame = false;

	int wScreen;
	int hScreen;

public:
	ArcballCamera(EventBus& eventBus, int xScreen, int yScreen);
	~ArcballCamera();

	void SetPosition(glm::vec3 pos) override;
	const glm::vec3& GetPosition(void) const override;

	void OnEvent(Event& e) override;

private:
	void OnMouseButton(MouseButtonCode mbCode, bool isPressed);
	void OnMouseMove(int x, int y);

	void CalcArcball(int x, int y);

	void CalcProjectionMatrix(int wScreen, int hScreen);
	void CalcViewMatrix(void);

};


