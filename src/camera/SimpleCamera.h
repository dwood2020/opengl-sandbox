#pragma once
#include <glm/glm.hpp>
#include "../events/Event.hpp"
#include "../events/EventBus.h"
#include "CameraBase.h"


//TODO: Make different camera subclasses, derived from one abstract base class
// which defines everything a camera must have for rendering a scene

class SimpleCamera : public CameraBase {
public:
	/*glm::mat4 V;
	glm::mat4 P;

	bool PIsDirty;
	bool VIsDirty;*/

protected:
	/*glm::vec3 position;
	glm::vec3 target;*/

	bool lmbIsDown = false;
	float lastMouseX = 0.0f;
	float lastMouseY = 0.0f;

	const glm::vec3 up;


	SimpleCamera();

public:
	SimpleCamera(EventBus& eventBus);
	virtual ~SimpleCamera();

	void SetPosition(glm::vec3 pos) override;
	const glm::vec3& GetPosition(void) const override;

	void OnEvent(Event& e) override;

protected:
	void CalcProjectionMatrix(int wScreen, int hScreen);
	void CalcViewMatrix(void);

	void ProcessMouseButtonInput(MouseButtonCode mbCode, bool isPressed);
	void ProcessMouseMoveInput(int x, int y);

};



