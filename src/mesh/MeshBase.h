#pragma once
#include <glm/glm.hpp>


class MeshBase {
public:
	MeshBase();

	virtual ~MeshBase();


	virtual void Prepare(void) = 0;


	virtual void Draw(void) = 0;

};