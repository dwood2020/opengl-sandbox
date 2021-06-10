#include "OctreeNode.h"

OctreeNode::OctreeNode(): parent(nullptr), children({nullptr}), nrChildren(0), level(-1), type(-1) { }


OctreeNode::~OctreeNode() { }
