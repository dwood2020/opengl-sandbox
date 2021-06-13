#include "OctreeNode.h"
#include <iostream>

OctreeNode::OctreeNode(): parent(nullptr), children({nullptr}), nrChildren(0), position(glm::vec3(0.0f)), level(-1), type(-1) { }


OctreeNode::~OctreeNode() {
	std::cout << "DEBUG: Destroyed OctreeNode instance" << std::endl;
}


void OctreeNode::AddChild(OctreeNode* child, int octant) {
	if (children[octant] == nullptr) {
		nrChildren += 1;
	}
	children[octant] = child;

	child->parent = this;
	child->position = GetChildCenter(octant);	
}


glm::vec3 OctreeNode::GetChildCenter(int octant) const {
	glm::vec3 dir = glm::vec3(0.0f);

	switch (octant) {
	case 0:
		dir = glm::vec3(1.0f, 1.0f, 1.0f); break;
	case 1:
		dir = glm::vec3(-1.0f, 1.0f, 1.0f); break;
	case 2:
		dir = glm::vec3(-1.0f, -1.0f, 1.0f); break;
	case 3:
		dir = glm::vec3(1.0f, -1.0f, 1.0f); break;
	case 4:
		dir = glm::vec3(1.0f, 1.0f, -1.0f); break;
	case 5:
		dir = glm::vec3(-1.0f, 1.0f, -1.0f); break;
	case 6:
		dir = glm::vec3(-1.0f, -1.0f, -1.0f); break;
	case 7:
		dir = glm::vec3(1.0f, -1.0f, -1.0f); break;
	}

	//TODO: this-level = 0 edge case

	return dir * (this->level / 2.0f);
}
