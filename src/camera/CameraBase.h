#pragma once
#include <glm/glm.hpp>
#include "../events/EventListener.hpp"
#include "../events/EventBus.h"
#include "../events/Event.hpp"


class CameraBase : public EventListener {
public:	
	//TODO: Come up with better way of doing this
	bool PIsDirty = false;
	bool VIsDirty = false;

	virtual const glm::mat4& GetViewMatrix(void) const = 0;
	virtual const glm::mat4& GetProjectionMatrix(void) const = 0;


public:
	CameraBase();
	virtual ~CameraBase();
	
	virtual const glm::vec3& GetPosition(void) const = 0;

	virtual void OnEvent(Event& e) override = 0;

};

