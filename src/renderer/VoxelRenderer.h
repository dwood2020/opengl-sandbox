#pragma once
#include <map>
#include "RendererBase.h"
#include "../Lighting.h"
#include "../camera/CameraBase.h"
#include "../voxel/VoxelScene.h"
#include "../material/MaterialBase.h"


class VoxelRenderer final : public RendererBase {
private:
	Lighting* lighting;
	CameraBase* camera;
	VoxelScene* scene;
	
	std::map<char, MaterialBase*> blockMaterials;


	VoxelRenderer() = default;

public:
	VoxelRenderer(Lighting& lighting, CameraBase& camera, VoxelScene& scene);

	~VoxelRenderer();


	void AddMaterial(char blocktype, MaterialBase* material);


	void Prepare(void) override;


	void DoFrame(void) override;


};

