#pragma once
#include <glm/glm.hpp>


/// <summary>
/// This class represents a plane that resides in the Voxel Scene.
/// (Being so, it cannot be randomly oriented in 3D space but has to align with the voxel grid.)
/// </summary>
class VoxelPlane final {
private:
	glm::ivec3 origin;
	glm::ivec2 orientation;

public:
	VoxelPlane();

	~VoxelPlane();

};