#pragma once
#include <glm/glm.hpp>
#include "events/Event.hpp"
#include "events/EventBus.h"
#include "events/EventListener.hpp"


//TODO: Make different camera subclasses, derived from one abstract base class
// which defines everything a camera must have for rendering a scene

class Camera : public EventListener {
public:	
	glm::vec3 target;

	glm::mat4 V;
	glm::mat4 P;

	bool PIsDirty;
	bool VIsDirty;

protected:
	glm::vec3 positionCartesian;

	// position in sphere coordinates:
	float rho;
	float theta;
	float phi;

	bool lmbIsDown = false;
	float lastMousePosX = 0.0f;
	float lastMousePosY = 0.0f;

	Camera();

public:	
	Camera(EventBus& eventBus);
	virtual ~Camera();

	void SetPosition(glm::vec3 pos);
	const glm::vec3& GetPosition(void) const;

	void OnEvent(Event& e) override;

protected:
	void CalcProjectionMatrix(int wScreen, int hScreen);
	void CalcViewMatrix(void);

	void ProcessMouseButtonInput(MouseButtonCode mbCode, bool isPressed);
	void ProcessMouseMoveInput(int x, int y);

};



