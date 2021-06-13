#include "OctreeManager.h"
#include <cmath>
#include <string>


OctreeManager::OctreeManager(): rootNode(nullptr) { }


OctreeManager::~OctreeManager() { }


void OctreeManager::AddLeaf(const glm::vec3& center) {
	if (rootNode == nullptr) {
		// add first node
		OctreeNode* node = GetNewNode();
		node->level = 0;
		node->position = center;
		
		// add a level 1 node as initial root
		OctreeNode* parentNode = GetNewNode();
		parentNode->level = 1;
		parentNode->position = center - parentNode->GetChildCenter(0);
		parentNode->AddChild(node, 0);

		rootNode = parentNode;				
		return;
	}
	
	// added leaf node is not the first node
	OctreeNode* newNode = GetNewNode();
	newNode->position = center;
	newNode->level = 0;

	// check if inside bounds of current root
	bool insideRootBounds = IsInsideBounds(newNode, rootNode);

	if (insideRootBounds) {
		OctreeNode* parent = rootNode;

		while (parent->level > 1) {
			OctreeNode* nextParent = GetNewNode();
			int octant = GetOctant(newNode->position, parent->position);
			nextParent->position = parent->GetChildCenter(octant);
			nextParent->level = parent->level - 1;
			parent->AddChild(nextParent, octant);
			
			parent = nextParent;
		}

		int leafOctant = GetOctant(newNode->position, parent->position);
		parent->AddChild(newNode, leafOctant);
	}

	
	//if (insideRootBounds) {
	//	// iterate to the new leaf's direct parent node
	//	OctreeNode* directParent = rootNode;
	//	int directParentOctant = GetOctant(newNode->position, directParent->position);
	//	while (directParent->level > newNode->level + 1) {
	//		OctreeNode* newParent = GetNewNode();
	//		newParent->level = directParent->level - 1;
	//		directParent->AddChild(newParent, directParentOctant);
	//		
	//		directParent = newParent;
	//		directParentOctant = GetOctant(newNode->position, directParent->position);
	//	}

	//	directParent->AddChild(newNode, directParentOctant);

	//}
	//else {

	//}


}


bool OctreeManager::IsInsideBounds(OctreeNode* node, OctreeNode* root) const {
	bool insideRootBounds = true;

	for (unsigned int i = 0; i < 3; i++) {
		if (abs(node->position[i] - root->position[i]) > root->level) {
			insideRootBounds = false;
			break;
		}
	}

	return insideRootBounds;
}


int OctreeManager::GetOctant(const glm::vec3& pos, const glm::vec3& rootCenter) {
	
	std::string octet = "xxx";
	octet[0] = ((pos.x > rootCenter.x) ? '+' : '-');
	octet[1] = ((pos.y > rootCenter.y) ? '+' : '-');
	octet[2] = ((pos.z > rootCenter.z) ? '+' : '-');
	
	if (octet == "+++") return 0;
	if (octet == "-++") return 1;
	if (octet == "--+") return 2;
	if (octet == "+-+") return 3;
	if (octet == "++-") return 4;
	if (octet == "-+-") return 5;
	if (octet == "---") return 6;
	if (octet == "+--") return 7;

	return -1;
}


OctreeNode* OctreeManager::GetNewNode(void) {
	nodeInstances.push_back(std::make_unique<OctreeNode>());
	return nodeInstances.back().get();
}
