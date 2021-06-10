#include "OctreeManager.h"


OctreeManager::OctreeManager(): rootNode(nullptr) { }


OctreeManager::~OctreeManager() { }


void OctreeManager::AddLeaf(const glm::vec3& pos) {
	if (rootNode == nullptr) {
		// add first node

		//IDEA: "pos" ist northwest bottom corner, "center" is actual center position of node
	}
}
