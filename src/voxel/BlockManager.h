#pragma once
#include <map>
#include <memory>
#include <glm/glm.hpp>
#include "Section.h"


class BlockManager final {
private:
	std::map<glm::ivec3, std::unique_ptr<Section>> sections;

public:
	BlockManager();

	~BlockManager();


	char GetBlock(const glm::ivec3& pos);	


	void SetBlock(const glm::ivec3& pos, char block);
};



