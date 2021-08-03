#pragma once
#include <vector>
#include "RenderCommand.hpp"


class IRenderable {
public:
	IRenderable() { }

	virtual ~IRenderable() { }


	virtual std::vector<RenderCommand> ToRenderCommands(void) = 0;
};
