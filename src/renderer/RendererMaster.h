#pragma once
#include <vector>
#include "RendererBase.h"


class RendererMaster {
private:
	std::vector<RendererBase*> workerRenderers;

public:
	RendererMaster();

	virtual ~RendererMaster();


	void AddRenderer(RendererBase& renderer);


	void InitRenderState(void);


};

