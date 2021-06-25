#pragma once
#include <glm/glm.hpp>
#include "../events/Event.hpp"
#include "../events/EventListener.hpp"


class RendererBase {
public:
	
	RendererBase();


	virtual ~RendererBase();	


	virtual void Prepare(void) = 0;


	virtual void DoFrame(void) = 0;
	

public:
	void CalculateViewport(const glm::vec2& rect);


};



