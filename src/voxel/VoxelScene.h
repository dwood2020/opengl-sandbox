#pragma once
#include <array>
#include <map>
#include <memory>
#include <glm/glm.hpp>
#include "Section.h"
#include "../mesh/DynamicMesh.h"
#include "VoxelGround.h"


using SectionsMap = std::map<std::array<int, 3>, std::unique_ptr<Section>>;


/// <summary>
/// This class holds all Voxel sections and therefore represents the Voxel "Scene".
/// It provides direct access to a single block.
/// The "voxel ground" (the grid on the xz plane) is also held here as it is part of the voxel scene.
/// </summary>
class VoxelScene final {
private:
	SectionsMap sections;

public:
	VoxelGround ground;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	VoxelScene();


	~VoxelScene();


	/// <summary>
	/// Gets a specific block.
	/// </summary>
	/// <param name="pos">Specific position</param>
	/// <returns>Block value</returns>
	char GetBlock(const glm::ivec3& pos);


	/// <summary>
	/// Sets a block at a specific position.
	/// </summary>
	/// <param name="pos">Specific position</param>
	/// <param name="block">Block value</param>
	void SetBlock(const glm::ivec3& pos, char block);


	/// <summary>
	/// Gets the sections (SectionsMap).
	/// </summary>	
	/// <returns>sections map</returns>
	SectionsMap& GetSectionsMap(void);


	/// <summary>
	/// Gets the VoxelGround reference.
	/// </summary>	
	/// <returns>VoxelGround reference</returns>
	VoxelGround& GetGround(void);


	/// <summary>
	/// Generate all meshes from the voxel grid data.
	/// </summary>
	void GenerateMeshes(void);

private:
	/// <summary>
	/// Calculates the section position to any given block position
	/// </summary>
	/// <param name="pos">Block position</param>
	/// <returns>Section position</returns>
	std::array<int, 3> CalcSectionPosKey(const glm::ivec3& pos);	//TODO: use glm::ivec3 as return value (needs custom serialization)


	/// <summary>
	/// Transforms global block position to a local section position
	/// </summary>
	/// <param name="pos">Global block position</param>
	/// <returns>Local block position (in section)</returns>
	glm::ivec3 ToSectionCoords(const glm::ivec3& pos);

};

