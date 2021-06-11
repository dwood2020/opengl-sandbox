#include "OctreeNode.h"
#include <iostream>

OctreeNode::OctreeNode(): parent(nullptr), children({nullptr}), nrChildren(0), position(glm::vec3(0.0f)), level(-1), type(-1) { }


OctreeNode::~OctreeNode() {
	std::cout << "DEBUG: Destroyed OctreeNode instance" << std::endl;
}


void OctreeNode::AddChild(OctreeNode* child, int octet) {
	if (children[octet] == nullptr) {
		nrChildren += 1;
	}
	children[octet] = child;

	child->parent = this;
}
