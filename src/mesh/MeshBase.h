#pragma once
#include <glm/glm.hpp>
#include "../glad/glad.h"


/// <summary>
/// This is a generic mesh class which provides the interface required by the
/// renderer for all mesh classes. 
/// </summary>
class MeshBase {
protected:
	GLenum glMode;

public:
	MeshBase();

	virtual ~MeshBase();

	/// <summary>
	/// Sets the OpenGL glMode (GL_LINES, GL_TRIANGLES, ...).
	/// </summary>
	/// <param name="glMode">glMode</param>
	virtual void SetGlMode(GLenum glMode);

	/// <summary>
	/// Prepares the mesh for rendering (interface)
	/// </summary>
	virtual void Prepare(void) = 0;

	/// <summary>
	/// Renders the mesh (interface).
	/// </summary>
	virtual void Draw(void) = 0;

};