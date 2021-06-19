#pragma once
#include <glm/glm.hpp>
#include "Section.h"
#include "BlockManager.h"


class BlockMeshGenerator final {
private:
	BlockManager* blockManager;

public:
	BlockMeshGenerator(BlockManager& blockManager);

	~BlockMeshGenerator();
};

