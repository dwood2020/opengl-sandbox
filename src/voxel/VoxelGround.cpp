#include "VoxelGround.h"
#include "../renderer/RenderCommand.hpp"
#include <cmath>


VoxelGround::VoxelGround() {
	dimensions = glm::ivec3(2, 0, 2);	

}


VoxelGround::~VoxelGround() { }


DynamicMesh& VoxelGround::GetMesh(void) {
	return mesh;
}


void VoxelGround::SetDimensions(const glm::vec3& dimensions) {
	this->dimensions = dimensions;
}


void VoxelGround::GenerateMesh(void) {
	
	mesh.GetVerticesPos().clear();

	// z-direction grid lines
	float z = static_cast<float>(dimensions.z);
	
	for (int i = 0; i <= 2*dimensions.x; i += 1) {
		float xi = static_cast<float>(-dimensions.x + i);

		mesh.GetVerticesPos().push_back({ glm::vec3(xi, 0, -z) });
		mesh.GetVerticesPos().push_back({ glm::vec3(xi, 0, z) });
	}
		
	// x-direction grid lines
	float x = static_cast<float>(dimensions.x);

	for (int k = 0; k <= 2*dimensions.z; k += 1) {
		float zi = static_cast<float>(-dimensions.z + k);

		mesh.GetVerticesPos().push_back({ glm::vec3(-x, 0, zi) });
		mesh.GetVerticesPos().push_back({ glm::vec3(x, 0, zi) });
	}

	mesh.SetGlMode(GL_LINES);
	mesh.Prepare();	
}
