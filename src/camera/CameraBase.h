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

	void SetPosition(glm::vec3 pos);
	const glm::vec3& GetPosition(void) const;

	virtual void OnEvent(Event& e) override = 0;

protected:
	virtual void CalcViewMatrix(void) = 0;
	virtual void CalcProjectionMatrix(int wScreen, int hScreen) = 0;

};

