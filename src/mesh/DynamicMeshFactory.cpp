#include "DynamicMeshFactory.h"
#include <cmath>

#include <iostream>


DynamicMeshFactory::DynamicMeshFactory() {

	// rotation matrix: 90 degrees around x axis (for z axis)
	R90x = glm::mat3 {
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f
	};
	R90x = glm::transpose(R90x);
	
	// rotation matrix: 270 degrees around z axis (for x axis)
	R270z = glm::mat3 {
		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	R270z = glm::transpose(R270z);
}


DynamicMeshFactory::~DynamicMeshFactory() { }


DynamicMeshFactory& DynamicMeshFactory::GetInstance(void) {
	static DynamicMeshFactory instance;	// guaranteed to be destroyed
	return instance;
}


DynamicMesh DynamicMeshFactory::MakeCylinder(float r, float h, int ptsOnCircle) const {

	const float deltaPhi = (2.0f * pi) / static_cast<float>(ptsOnCircle);

	std::cout << "DynamicMeshFactory::MakeCylinder: Singleton is working :)" << std::endl;

	return DynamicMesh();
}
