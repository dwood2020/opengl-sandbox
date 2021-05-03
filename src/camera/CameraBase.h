#pragma once
#include <glm/glm.hpp>
#include "../events/EventListener.hpp"
#include "../events/EventBus.h"
#include "../events/Event.hpp"


class CameraBase : public EventListener {
public:
	glm::mat4 V;
	glm::mat4 P;

	//TODO: Come up with better way of doing this
	bool PIsDirty = false;
	bool VIsDirty = false;

protected:
	glm::vec3 position;
	glm::vec3 target;

public:
	CameraBase();
	virtual ~CameraBase();

	virtual void SetPosition(glm::vec3 pos) = 0;
	virtual const glm::vec3& GetPosition(void) const = 0;

	virtual void OnEvent(Event& e) override = 0;

};

