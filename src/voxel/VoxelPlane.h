#pragma once
#include <array>
#include <glm/glm.hpp>
#include "../mesh/DynamicMesh.h"


/// <summary>
/// This class represents a plane that resides in the Voxel Scene.
/// (Being so, it cannot be randomly oriented in 3D space but has to align with the voxel grid.)
/// </summary>
class VoxelPlane final {
private:
	glm::ivec3 origin;
	glm::ivec2 orientation;
	glm::ivec2 dimension;

	std::array<DynamicMesh, 2> meshes;

	bool meshesAreDirty;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	VoxelPlane();

	~VoxelPlane();


	const glm::ivec3& GetOrigin(void) const;

	void SetOrigin(const glm::ivec3& origin);

	const glm::ivec2& GetOrientation(void) const;

	void SetOrientation(const glm::ivec2& orientation);

	const glm::ivec2& GetDimension(void) const;

	void SetDimension(const glm::ivec2& dimension);


	/// <summary>
	/// Gets the meshes array.
	/// </summary>
	/// <returns>Meshes array</returns>
	std::array<DynamicMesh, 2>& GetMeshes(void);


	/// <summary>
	/// (Re-)Generates the meshes.
	/// </summary>
	void GenerateMeshes(void);

};