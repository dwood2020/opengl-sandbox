#pragma once
#include <map>
#include "RendererBase.h"
#include "../events/EventBus.h"
#include "../Lighting.h"
#include "../camera/CameraBase.h"
#include "../material/MaterialBase.h"
#include "../voxel/VoxelScene.h"


class VoxelRenderer final : public RendererBase {
private:
	Lighting* lighting;
	CameraBase* camera;

	VoxelScene* voxelScene;

	std::map<char, MaterialBase*> blockMaterials;


	VoxelRenderer() = default;

public:
	VoxelRenderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera, const glm::vec2& windowRect, VoxelScene& voxelScene);

	~VoxelRenderer();


	void AddMaterial(char blocktype, MaterialBase* material);


	void OnEvent(Event& e) override;


	void Prepare(void) override;


	void DoFrame(void) override;

};

