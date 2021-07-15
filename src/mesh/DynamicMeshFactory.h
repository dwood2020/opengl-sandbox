#pragma once
#include <glm/glm.hpp>
#include "DynamicMesh.h"


class DynamicMeshFactory final {
private:
	const float pi = 3.1415926f;
	glm::mat3 R90x;
	glm::mat3 R270z;


	DynamicMeshFactory();

public:
	~DynamicMeshFactory();


	static DynamicMeshFactory& GetInstance(void);

	DynamicMeshFactory(DynamicMeshFactory const&) = delete;
	void operator=(DynamicMeshFactory const&) = delete;


	DynamicMesh MakeCylinder(float r, float h, int ptsOnCircle) const;
};

