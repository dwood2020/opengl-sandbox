#pragma once
#include <array>
#include <map>
#include <memory>
#include <glm/glm.hpp>
#include "Section.h"
#include "../mesh/DynamicMesh.h"


using SectionsMap = std::map<std::array<int, 3>, std::unique_ptr<Section>>;


class VoxelScene final {
private:
	SectionsMap sections;	

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
	/// Gets the sections (SectionsMap)
	/// </summary>	
	/// <returns>sections map</returns>
	SectionsMap& GetSections(void);

	//TODO: Make this private and event-triggerable!
	void GenerateMeshes(void);

private:		
	std::array<int, 3> CalcSectionPosKey(const glm::ivec3& pos);	//TODO: use glm::ivec3 (needs custom serialization)

	glm::ivec3 ToSectionCoords(const glm::ivec3& pos);

};

