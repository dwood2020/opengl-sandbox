#include "VoxelPlane.h"


VoxelPlane::VoxelPlane(): origin(glm::ivec3()), orientation(glm::ivec2()), meshesAreDirty(false) { }


VoxelPlane::~VoxelPlane() { }


const glm::ivec3& VoxelPlane::GetOrigin(void) const {
	return origin;
}


void VoxelPlane::SetOrigin(const glm::ivec3& origin) {
	this->origin = origin;
}


const glm::ivec2& VoxelPlane::GetOrientation(void) const {
	return orientation;
}


void VoxelPlane::SetOrientation(const glm::ivec2& orientation) {
	this->orientation = orientation;
}


const glm::ivec2& VoxelPlane::GetDimension(void) const {
	return dimension;
}


void VoxelPlane::SetDimension(const glm::ivec2& dimension) {
	this->dimension = dimension;
}


std::array<DynamicMesh, 2>& VoxelPlane::GetMeshes(void) {
	return meshes;
}


void VoxelPlane::GenerateMeshes(void) {
	// origin cross as first render try:

	auto& meshOriginVec = meshes[0].GetVerticesPos();
	meshOriginVec.push_back({ glm::vec3() });
	//TODO: implement this.
}
