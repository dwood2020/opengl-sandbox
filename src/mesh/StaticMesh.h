#pragma once
#include <vector>
#include "../glad/glad.h"
#include <glm/glm.hpp>
#include "MeshBase.h"


/// <summary>
/// This class encapsulates a "static" mesh: 
/// Mesh vertices which cannot be altered after they have been sent to the GPU (after calling Prepare).
/// NOTE: This mesh class was adopted from an earlier project and shall be replaced by a new implementation
/// in the future. At present, having a non-alterable vertex array saves some memory on CPU side.
/// </summary>
class StaticMesh : public MeshBase {
protected:
	unsigned int vao;	
	unsigned int vbo;
	unsigned int ebo;
	
	GLsizei nrElements;

	// these arrays serve for building the vertex data
	// and are cleared after calling Prepare()
	// TODO: convert these to pointers
	std::vector<glm::vec3> verticesPosition;
	std::vector<glm::vec3> verticesNormal;
	std::vector<glm::vec2> verticesTexCoord;
	std::vector<glm::vec3> verticesColor;	
	std::vector<unsigned int> indices;

public:
	StaticMesh();
	virtual ~StaticMesh();

	void SetPositionVertices(std::vector<glm::vec3>& vertices);
	void SetNormalVertices(std::vector<glm::vec3>& normals);
	void SetTextureCoordVertices(std::vector<glm::vec2>& texCoords);
	void SetColorVertices(std::vector<glm::vec3>& colors);
	void SetIndices(std::vector<unsigned int>& indices);	

	void Prepare(void) override;
	void Draw(void) override;

protected:
	bool CheckDataConsistency(void) const;

};



