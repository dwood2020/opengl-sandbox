#pragma once
#include <array>
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


	char GetBlock(int x, int y, int z);

	char GetBlock(const glm::vec3& pos);

	void SetBlock(int x, int y, int z, char block);

	void SetBlock(const glm::vec3& pos, char block);
};



