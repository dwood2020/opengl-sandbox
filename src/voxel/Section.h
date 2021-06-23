#pragma once
#include <glm/glm.hpp>
#include "../mesh/DynamicMesh.h"


class Section final {
public:
	static constexpr unsigned int sectionSize = 8u;

	/// <summary>
	/// Pointer type to raw block array.
	/// </summary>
	typedef char(*ArrayPtr)[sectionSize][sectionSize][sectionSize];

	static std::vector<VertexPosNorm> frontFaceTemplate;
	static std::vector<VertexPosNorm> rightFaceTemplate;
	static std::vector<VertexPosNorm> rearFaceTemplate;
	static std::vector<VertexPosNorm> leftFaceTemplate;
	static std::vector<VertexPosNorm> topFaceTemplate;
	static std::vector<VertexPosNorm> bottomFaceTemplate;


private:	
	char blocks[sectionSize][sectionSize][sectionSize];

	glm::ivec3 basePos;

	DynamicMesh mesh;

	bool meshIsDirty;

private:
	Section() = default;

public:	
	/// <summary>
	/// Constructor. Initializes array.
	/// </summary>
	Section(const glm::ivec3& basePos);

	/// <summary>
	/// Destructor.
	/// </summary>
	~Section();

	/// <summary>
	/// Gets a block information at the specified location within the section
	/// NOTE: Location is in section coordinates.
	/// </summary>
	/// <param name="pos">location</param>
	/// <returns>Block information at that location</returns>
	char GetBlock(const glm::ivec3& pos);

	/// <summary>
	/// Gets a block information at the specified location within the section
	/// NOTE: Location is in section coordinates.
	/// NOTE: The floating point coordinates are floored (not rounded).
	/// </summary>
	/// <param name="pos">Location</param>
	/// <returns>Block information at that location</returns>
	char GetBlock(const glm::vec3& pos);

	/// <summary>
	/// Sets a block at the specified location within the section.
	/// NOTE: Location is in section coordinates.
	/// </summary>
	/// <param name="pos">block location</param>
	/// <param name="block">Block information</param>	
	void SetBlock(const glm::ivec3& pos, char block);

	/// <summary>
	/// Sets a block at the specified location within the section.
	/// NOTE: Location is in section coordinates.
	/// </summary>
	/// <param name="pos"> block location</param>	
	/// <param name="block">Block information</param>
	void SetBlock(const glm::vec3& pos, char block);

	/// <summary>
	/// Gets a pointer to the raw array.
	/// </summary>
	/// <returns>Pointer to raw block array (see typedef)</returns>
	ArrayPtr GetArray(void);


	/// <summary>
	/// Gets the mesh object.
	/// </summary>	
	DynamicMesh& GetMesh(void);


	/// <summary>
	/// Gets the MehsIsDirty flag.
	/// </summary>
	bool GetMeshIsDirty(void) const;


	/// <summary>
	/// (Re-)Generates the mesh vertex data from the flat 3D array.
	/// </summary>
	void GenerateMesh(void);


private:	
	inline bool IsWithinBounds(const glm::ivec3& pos) const;

	inline glm::ivec3 FloatToInt(const glm::vec3& fv) const;

};