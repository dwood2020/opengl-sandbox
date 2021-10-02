#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../mesh/DynamicMesh.h"


class RenderCommand;


/// <summary>
/// This class represents the "ground" in the voxel scene
/// (the grid which is rendered in the xy-plane)
/// </summary>
class VoxelGround final {
private:
	DynamicMesh mesh;
	std::vector<RenderCommand> renderCommands;

	glm::vec3 dimensions;

public:
	/// <summary>
	/// Constructor
	/// </summary>
	VoxelGround();
	

	~VoxelGround();


	/// <summary>
	/// Get the mesh
	/// </summary>
	/// <returns>Mesh reference</returns>
	DynamicMesh& GetMesh(void);


	/// <summary>
	/// Set the ground's dimensions as vec3:
	/// x and z are the half span of the ground mesh in x and z directions. y is ignored.
	/// </summary>
	/// <param name="dimensions">Dimensions vector (for x and z)</param>
	void SetDimensions(const glm::vec3& dimensions);


	/// <summary>
	/// Generate the mesh
	/// </summary>
	void GenerateMesh(void);
};
