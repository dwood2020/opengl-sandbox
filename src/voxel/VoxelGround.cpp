#include "VoxelGround.h"
#include "../renderer/RenderCommand.hpp"
#include <cmath>


VoxelGround::VoxelGround() {
	dimensions = glm::ivec3(2, 0, 2);	

}


VoxelGround::~VoxelGround() { }


std::array<DynamicMesh, 2>& VoxelGround::GetMeshes(void) {
	return meshes;
}


void VoxelGround::SetDimensions(const glm::vec3& dimensions) {
	this->dimensions = dimensions;
}


void VoxelGround::GenerateMesh(void) {
	
	meshes[0].GetVerticesPos().clear();

	// z-direction grid lines
	float z = static_cast<float>(dimensions.z);
	
	for (int i = 0; i <= 2*dimensions.x; i += 1) {
		float xi = static_cast<float>(-dimensions.x + i);

		meshes[0].GetVerticesPos().push_back({ glm::vec3(xi, 0, -z) });
		meshes[0].GetVerticesPos().push_back({ glm::vec3(xi, 0, z) });
	}
		
	// x-direction grid lines
	float x = static_cast<float>(dimensions.x);

	for (int k = 0; k <= 2*dimensions.z; k += 1) {
		float zi = static_cast<float>(-dimensions.z + k);

		meshes[0].GetVerticesPos().push_back({ glm::vec3(-x, 0, zi) });
		meshes[0].GetVerticesPos().push_back({ glm::vec3(x, 0, zi) });
	}

	meshes[0].SetGlMode(GL_LINES);
	meshes[0].Prepare();


	/*meshes[1].GetVerticesPos().clear();
	meshes[1].GetVerticesPos().push_back({ glm::vec3(-dimensions.x, 0.f, dimensions.z) });
	meshes[1].GetVerticesPos().push_back({ glm::vec3(dimensions.x, 0.f, dimensions.z) });
	meshes[1].GetVerticesPos().push_back({ glm::vec3(dimensions.x, 0.f, -dimensions.z) });
	meshes[1].GetVerticesPos().push_back({ glm::vec3(-dimensions.x, 0.f, -dimensions.z) });

	meshes[1].GetIndices().clear();
	meshes[1].GetIndices().push_back(0);
	meshes[1].GetIndices().push_back(1);
	meshes[1].GetIndices().push_back(2);
	meshes[1].GetIndices().push_back(0);
	meshes[1].GetIndices().push_back(2);
	meshes[1].GetIndices().push_back(3);

	meshes[1].SetIsIndexed(true);
	meshes[1].SetGlMode(GL_TRIANGLES);
	meshes[1].Prepare();*/

}
