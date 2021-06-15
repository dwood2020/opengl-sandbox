#pragma once
#include <glm/glm.hpp>


constexpr unsigned int sectionSize = 16u;


class Section final {
private:
	char blocks[sectionSize][sectionSize][sectionSize];

public:
	Section();

	~Section();


	char GetBlock(int x, int y, int z);


	char GetBlock(const glm::vec3& pos);

};