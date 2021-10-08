#pragma once
#include <vector>
#include "../glad/glad.h"
#include <glm/glm.hpp>
#include "MeshBase.h"


/// <summary>
/// Position vertex layout.
/// </summary>
struct VertexPos {
	glm::vec3 pos;
};


/// <summary>
/// Position + normal vertex layout.
/// </summary>
struct VertexPosNorm {
	glm::vec3 pos;
	glm::vec3 norm;
};


/// <summary>
/// Position + normal + texture coordinate vertex layout.
/// </summary>
struct VertexPosNormTex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 tex;
};


/// <summary>
/// This class represents a "mesh" in its actual higher-level meaning.
/// It encapsulates all required interaction with OpenGL.
/// Once prepared, all vertex data can still be altered.
/// 
/// Vertex data can either consist solely of position vertices (uses VertexPos), or
/// of position + normal vertices (uses VertexPosNorm), or
/// of position + normal + texture vertices (uses VertexPosNormTex). 
/// 
/// Which of these layouts will be used must be explicitly specified:
/// Default: Only position vertices.
/// SetUseNormals(true): position + normal vertices.
/// SetUseNormals(true) + SetUseTexCoords(true): position + normal + texture vertices.
/// SetIsIndexed(true): Indexed rendering is used.
/// Inconsistent setting defaults to position vertices only.
/// </summary>
class DynamicMesh final : public MeshBase {
private:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLsizei nrElements;

	std::vector<VertexPos> verticesPos;
	std::vector<VertexPosNorm> verticesPosNorm;
	std::vector<VertexPosNormTex> verticesPosNormTex;
	std::vector<GLuint> indices;

	bool useNormals;
	bool useTexCoords;
	bool isInstanced;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	DynamicMesh();

	~DynamicMesh();

	/// <summary>
	/// Gets the position vertices.
	/// </summary>	
	/// <returns>position vertices</returns>
	std::vector<VertexPos>& GetVerticesPos(void);


	/// <summary>
	/// Gets the position + normal vertices.
	/// </summary>	
	/// <returns>position + normal vertices</returns>
	std::vector<VertexPosNorm>& GetVerticesPosNorm(void);


	/// <summary>
	/// Gets the position + normal + texture vertices.
	/// </summary>
	/// <returns>position + normal + texture vertices</returns>
	std::vector<VertexPosNormTex>& GetVerticesPosNormTex(void);


	/// <summary>
	/// Gets the indices.
	/// </summary>
	/// <returns>indices</returns>
	std::vector<GLuint>& GetIndices(void);


	/// <summary>
	/// Use normal vertices (see class description).
	/// </summary>
	/// <param name="useNormals">True: Use normal vertices</param>
	void SetUseNormals(bool useNormals);


	/// <summary>
	/// Use texture coordinate vertices (see class description).
	/// </summary>
	/// <param name="useTexCoords">True: Use texture coordinates</param>
	void SetUseTexCoords(bool useTexCoords);


	/// <summary>
	/// Use index buffer for rendering (see class description).
	/// </summary>
	/// <param name="isIndexed">True: use indexing</param>
	void SetIsIndexed(bool isIndexed);


	/// <summary>
	/// Prepares the mesh for rendering.
	/// </summary>
	void Prepare(void) override;


	/// <summary>
	/// Renders the mesh. 
	/// NOTE: This is called by the renderer only.
	/// </summary>
	void Draw(void) override;


	/// <summary>
	/// Updates the mesh (+ sends updated array to GPU).
	/// Call this after altering the corresponding vertices.
	/// </summary>
	void Update(void);

private:
	bool CheckDataConsistency(void);
};