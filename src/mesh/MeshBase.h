#pragma once
#include <glm/glm.hpp>
#include "../glad/glad.h"


class MeshBase {
protected:
	GLenum glMode;

public:
	MeshBase();

	virtual ~MeshBase();


	virtual void SetGlMode(GLenum glMode);


	virtual void Prepare(void) = 0;


	virtual void Draw(void) = 0;

};