#pragma once
#include <array>
#include <glm/glm.hpp>


class OctreeNode final {
public:
	OctreeNode* parent;
	std::array<OctreeNode*, 8> children;
	unsigned char nrChildren;

	int level;
	char type;

public:
	OctreeNode();
	~OctreeNode();

};

