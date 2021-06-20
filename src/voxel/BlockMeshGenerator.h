#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Section.h"
#include "BlockManager.h"
#include "../mesh/DynamicMesh.h"


class BlockMeshGenerator final {
private:
	BlockManager* blockManager;

public:
	BlockMeshGenerator(BlockManager& blockManager);


	~BlockMeshGenerator();


	void GenerateSectionMesh(const glm::ivec3& pos, const Section& section, DynamicMesh& mesh);

};

