#include "VoxelGround.h"

#include "../renderer/RenderCommand.hpp"


VoxelGround::VoxelGround() {
	dimensions = glm::ivec3(2, 0, 2);	

}


VoxelGround::~VoxelGround() { }


void VoxelGround::GenerateMesh(void) {
	
	meshes[0].GetVerticesPos().clear();

	// z-direction grid lines
	float z = static_cast<float>(dimensions.z);
	
	for (int i = -dimensions.x; i < dimensions.x; i += 1) {
		float xi = static_cast<float>(-dimensions.x + i);

		meshes[0].GetVerticesPos().push_back({ glm::vec3(xi, 0, -z) });
		meshes[0].GetVerticesPos().push_back({ glm::vec3(xi, 0, z) });
	}
	
	
	// x-direction grid lines
	float x = static_cast<float>(dimensions.x);

	for (int k = -dimensions.z; k < dimensions.z; k += 1) {
		float zi = static_cast<float>(-dimensions.z + k);

		meshes[0].GetVerticesPos().push_back({ glm::vec3(-x, 0, zi) });
		meshes[0].GetVerticesPos().push_back({ glm::vec3(x, 0, zi) });
	}

	meshes[0].SetGlMode(GL_LINES);
	meshes[0].Prepare();

}
