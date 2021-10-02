#pragma once
#include <array>
#include <vector>
#include <glm/glm.hpp>

#include "../mesh/DynamicMesh.h"

//class DynamicMesh;
class RenderCommand;


/// <summary>
/// This class represents the "ground" in the voxel scene
/// (the grid which is rendered in the xy-plane)
/// </summary>
class VoxelGround final {
private:
	std::array<DynamicMesh, 2> meshes;
	std::vector<RenderCommand> renderCommands;

	glm::vec3 dimensions;

public:
	/// <summary>
	/// Constructor
	/// </summary>
	VoxelGround();
	
	~VoxelGround();


	std::array<DynamicMesh, 2>& GetMeshes(void);


	void SetDimensions(const glm::vec3& dimensions);


	void GenerateMesh(void);
};
