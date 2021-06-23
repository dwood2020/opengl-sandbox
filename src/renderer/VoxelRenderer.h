#pragma once
#include "RendererBase.h"
#include "../events/EventBus.h"
#include "../Lighting.h"
#include "../camera/CameraBase.h"


class VoxelRenderer final : public RendererBase {
private:
	Lighting* lighting;
	CameraBase* camera;

	VoxelRenderer() = default;

public:
	VoxelRenderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera);

	~VoxelRenderer();


	void OnEvent(Event& e) override;


	void Prepare(void) override;


	void DoFrame(void) override;

};

