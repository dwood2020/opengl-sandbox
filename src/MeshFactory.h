#pragma once
#include "Mesh.h"


class MeshFactory final {
public:
	MeshFactory();
	~MeshFactory();


	Mesh MakeRectangle(float w, float h, float z = 0.0f) const;

	Mesh MakeCube(int l) const;

};

