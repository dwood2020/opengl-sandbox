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
	bool lmbIsDown;
	glm::vec2 lastMousePosNDC;

	float rho;
	float phi;
	float theta;

	glm::vec3 target;

public:
	SimpleCamera(EventBus& eventBus, const glm::vec2& windowRect, const glm::vec3& pos);
	~SimpleCamera();

	const glm::mat4& GetViewMatrix(void) const override;

	const glm::mat4& GetProjectionMatrix(void) const override;

	const glm::vec3& GetPosition(void) const override;

	void OnEvent(Event& e) override;

private:
	void ProcessMouseButtonInput(MouseButtonCode mbCode, bool isPressed);

	void ProcessMouseMoveInput(int x, int y);
	
	void CalcProjectionMatrix(void);	

	/// <summary>
	/// Transforms screen coordinates into Normalized Device Coordinates (NDC)
	/// with top left = (-1,1) ; center = (0,0) ; bottom right = (1,-1)
	/// </summary>
	glm::vec2 ScreenToNDC(const glm::vec2& posScreen) const;

	glm::vec2 DeltaNDC(const glm::vec2& posNDC) const;

};



