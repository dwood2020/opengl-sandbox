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
	/// <param name="pos">location</param>
	/// <returns>Block information at that location</returns>
	char GetBlock(const glm::ivec3& pos);

	/// <summary>
	/// Gets a block information at the specified location within the section
	/// NOTE: Location is in section coordinates.
	/// NOTE: The floating point coordinates are floored (not rounded).
	/// </summary>
	/// <param name="pos">Location</param>
	/// <returns>Block information at that location</returns>
	char GetBlock(const glm::vec3& pos);

	/// <summary>
	/// Sets a block at the specified location within the section.
	/// NOTE: Location is in section coordinates.
	/// </summary>
	/// <param name="pos">block location</param>
	/// <param name="block">Block information</param>	
	void SetBlock(const glm::ivec3& pos, char block);

	/// <summary>
	/// Sets a block at the specified location within the section.
	/// NOTE: Location is in section coordinates.
	/// </summary>
	/// <param name="pos"> block location</param>	
	/// <param name="block">Block information</param>
	void SetBlock(const glm::vec3& pos, char block);

private:	
	inline bool IsWithinBounds(const glm::ivec3& pos) const;

	inline glm::ivec3 FloatToInt(const glm::vec3& fv) const;

};