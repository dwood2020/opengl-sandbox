#pragma once
#include <glm/glm.hpp>
#include "CameraBase.h"
#include "../events/EventBus.h"


class ArcballCamera final : public CameraBase {
private:
	glm::mat4 V;
	glm::mat4 P;

	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
	glm::vec3 right;

	// last positions in transformed arcball coordinates
	float xLast = 0.0f;
	float yLast = 0.0f;
	float zLast = 1.0f;

	bool arcballOn = false;
	bool isFirstFrame = false;

	int wScreen;
	int hScreen;

public:
	ArcballCamera(EventBus& eventBus, int xScreen, int yScreen, glm::vec3& pos);
	~ArcballCamera();

	void SetPosition(glm::vec3 pos) override;
	const glm::vec3& GetPosition(void) const override;

	const glm::mat4& GetViewMatrix(void) const override;
	const glm::mat4& GetProjectionMatrix(void) const override;

	void OnEvent(Event& e) override;

private:
	void OnMouseButton(MouseButtonCode mbCode, bool isPressed);
	void OnMouseMove(int x, int y);

	void CalcArcball(int x, int y);

	void CalcProjectionMatrix(int wScreen, int hScreen);
	void CalcViewMatrix(void);	

};


