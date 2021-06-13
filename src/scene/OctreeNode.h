#pragma once
#include <array>
#include <glm/glm.hpp>


class OctreeNode final {
public:
	OctreeNode* parent;
	std::array<OctreeNode*, 8> children;
	unsigned char nrChildren;

	glm::vec3 position;

	int level;
	char type;

public:
	OctreeNode();
	~OctreeNode();

	void AddChild(OctreeNode* child, int octet);


	glm::vec3 GetChildCenter(int octant) const;

};

