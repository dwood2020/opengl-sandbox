#pragma once
#include "RendererBase.h"


class VoxelRenderer final : public RendererBase {
public:
	VoxelRenderer();

	~VoxelRenderer();


	void Prepare(void) override;


	void DoFrame(void) override;


};

