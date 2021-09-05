#pragma once
#include <array>
#include <vector>
#include <glm/glm.hpp>


class DynamicMesh;
class RenderCommand;


class VoxelGround final {
private:
	std::array<DynamicMesh, 2> meshes;
	std::vector<RenderCommand> renderCommands;

	glm::vec3 dimensions;

public:
	VoxelGround();

	~VoxelGround();


	void GenerateMesh(void);
};
