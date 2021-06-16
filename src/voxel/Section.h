#pragma once
#include <glm/glm.hpp>


constexpr unsigned int sectionSize = 16u;


class Section final {
private:	
	char blocks[sectionSize][sectionSize][sectionSize];

public:
	Section();

	~Section();

	/// <summary>
	/// Gets a block information at the specified location within the section
	/// NOTE: Location is in section coordinates.
	/// </summary>
	/// <param name="x">x location</param>
	/// <param name="y">y location</param>
	/// <param name="z">z location</param>
	/// <returns>Block information at that location</returns>
	char GetBlock(int x, int y, int z);

	/// <summary>
	/// Gets a block information at the specified location within the section
	/// NOTE: Location is in section coordinates.
	/// NOTE: The floating point coordinates are floored (not rounded).
	/// </summary>
	/// <param name="pos">Location</param>
	/// <returns>Block information at that location</returns>
	char GetBlock(const glm::vec3& pos);

};