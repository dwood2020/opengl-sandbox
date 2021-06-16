#pragma once
#include <array>
#include <map>
#include <memory>
#include <glm/glm.hpp>
#include "Section.h"


class BlockManager final {
private:
	std::map<std::array<int, 3>, std::unique_ptr<Section>> sections;

public:
	BlockManager();

	~BlockManager();
};



