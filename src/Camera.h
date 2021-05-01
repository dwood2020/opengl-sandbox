#pragma once
#include <glm/glm.hpp>
#include "events/Event.hpp"
#include "events/EventBus.h"


//TODO: Make different camera subclasses, derived from one abstract base class
// which defines everything a camera must have for rendering a scene

class Camera {
public:	
	glm::vec3 target;

	glm::mat4 V;
	glm::mat4 P;

	bool PIsDirty;

protected:
	glm::vec3 position;

public:
	Camera();	//TODO: Think about making this private
	Camera(EventBus& eventBus);
	virtual ~Camera();

	void SetPosition(glm::vec3 pos);
	const glm::vec3& GetPosition(void) const;

	// event listener methods:
	// these will disappear when event system is updated
	void OnWindowResize(Event& e);

protected:
	void CalcProjectionMatrix(int wScreen, int hScreen);
	void CalcViewMatrix(void);

};



