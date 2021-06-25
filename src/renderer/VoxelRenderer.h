#pragma once
#include "RendererBase.h"
#include "../Lighting.h"
#include "../camera/CameraBase.h"
#include "../voxel/VoxelScene.h"


class VoxelRenderer final : public RendererBase {
private:
	Lighting* lighting;
	CameraBase* camera;
	VoxelScene* scene;


	VoxelRenderer() = default;

public:
	VoxelRenderer(Lighting& lighting, CameraBase& camera, VoxelScene& scene);

	~VoxelRenderer();


	void Prepare(void) override;


	void DoFrame(void) override;


};

