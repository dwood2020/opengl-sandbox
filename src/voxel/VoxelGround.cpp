#include "VoxelGround.h"
#include "../mesh/DynamicMesh.h"
#include "../renderer/RenderCommand.hpp"


VoxelGround::VoxelGround() {
	dimensions = glm::ivec3(2, 0, 2);	

}


VoxelGround::~VoxelGround() { }


void VoxelGround::GenerateMesh(void) {
	
	meshes[0].GetVerticesPos().clear();


	float z = static_cast<float>(dimensions.z);
	
	for (int i = -dimensions.x; i < dimensions.x; i += 1) {
		float xi = static_cast<float>(-dimensions.x + i);

		meshes[0].GetVerticesPos().push_back({ glm::vec3(xi, 0, -z) });
		meshes[0].GetVerticesPos().push_back({ glm::vec3(xi, 0, z) });
	}
	
	//TODO: implement x-direction lines
}
