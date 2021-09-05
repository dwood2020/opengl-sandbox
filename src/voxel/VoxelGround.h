#pragma once
#include <vector>


class DynamicMesh;
class RenderCommand;


class VoxelGround final {
private:
	std::vector<DynamicMesh> meshes;
	std::vector<RenderCommand> renderCommands;

public:
	VoxelGround();

	~VoxelGround();
};
