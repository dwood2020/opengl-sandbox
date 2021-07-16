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
	

	DynamicMesh mesh;
	mesh.GetVerticesPos().reserve(2 * ptsOnCircle);

	// bottom ring
	for (int i = 0; i < ptsOnCircle; i++) {
		mesh.GetVerticesPos().push_back({ glm::vec3(r * std::cosf(i * deltaPhi), 0.0f, r * std::sinf(i * deltaPhi)) });
	}

	// top ring
	for (int i = 0; i < ptsOnCircle; i++) {
		mesh.GetVerticesPos().push_back({ glm::vec3(r * std::cosf(i * deltaPhi), h, r * std::sinf(i * deltaPhi)) });
	}
	
	for (GLuint i = 1; i < static_cast<GLuint>(ptsOnCircle); i++) {
		mesh.GetIndices().push_back(i);
		mesh.GetIndices().push_back(i + 1);
		mesh.GetIndices().push_back(0);
	}

	mesh.GetIndices().push_back(ptsOnCircle);
	mesh.GetIndices().push_back(1);
	mesh.GetIndices().push_back(0);

	mesh.SetGlMode(GL_TRIANGLES);
	mesh.SetIsInstanced(true);
	mesh.Prepare();

	return mesh;
}
