#pragma once
#include <glm/glm.hpp>
#include "../events/Event.hpp"
#include "../events/EventListener.hpp"


class RendererBase : public EventListener {
public:
	
	RendererBase();


	virtual ~RendererBase();	


	virtual void Prepare(void) = 0;


	virtual void DoFrame(void) = 0;


	virtual void OnEvent(Event& e) override = 0;


protected:
	void CalculateViewport(const glm::vec2& rect);


};



