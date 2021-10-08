#pragma once
#include <glm/glm.hpp>
#include "DynamicMesh.h"


/// <summary>
/// This class acts as factory for various DynamicMesh shapes.
/// It is implemented as Singleton (which omits an external object responsibility).
/// </summary>
class DynamicMeshFactory final {
private:
	const float pi = 3.1415926f;
	glm::mat3 R90x;
	glm::mat3 R270z;


	DynamicMeshFactory();

public:
	~DynamicMeshFactory();


	/// <summary>
	/// Gets the singleton instance. 
	/// It is lazy-initialized so instantiation happens on first use.
	/// </summary>
	/// <returns>instance</returns>
	static DynamicMeshFactory& GetInstance(void);

	DynamicMeshFactory(DynamicMeshFactory const&) = delete;
	void operator=(DynamicMeshFactory const&) = delete;


	/// <summary>
	/// Makes a cylinder.
	/// </summary>
	/// <param name="r">Cylinder base radius</param>
	/// <param name="h">Cylinder height</param>
	/// <param name="ptsOnCircle">Number of vertices on the base circle</param>
	/// <returns>DynamicMesh object</returns>
	DynamicMesh MakeCylinder(float r, float h, int ptsOnCircle) const;
};

