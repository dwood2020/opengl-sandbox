#pragma once
#include <variant>
#include <memory>
#include "glm/glm.hpp"


/// <summary>
/// This enum represents all possible uniform data types.
/// It is equivalent with the variant fields in the Uniform class.
/// </summary>
enum class UniformType {
	Int = 0,
	Float,
	Vec3,
	Mat4
};


/// <summary>
/// This class represents a uniform.
/// Approach:
/// To compact memory a little, this union-like approach is applied.
/// "Small" uniform values are part of the variant directly vs.
/// "large" uniform values, e.g. mat4 are saved outside the variant.
/// 
/// This is a trade-off between memory usage and fragmentation optimization.
/// </summary>
class Uniform final {
private:	
	std::variant<int, float, glm::vec3, std::shared_ptr<glm::mat4>> value;	
	
	int location;

private:
	/// <summary>
	/// Default constructor. Sets the location to unspecified: -1
	/// </summary>
	Uniform();

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="value">Uniform value (Integer)</param>
	Uniform(int value);


	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="value">Uniform value (Float)</param>
	Uniform(float value);


	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="value">Uniform value (Vec3)</param>
	Uniform(const glm::vec3& value);

	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="value">Uniform value (Mat4)</param>
	Uniform(const glm::mat4& value);

	/// <summary>
	/// Gets the uniform type as defined in the enum UniformType.
	/// </summary>	
	/// <returns>Uniform type</returns>
	UniformType GetType(void) const;

	/// <summary>
	/// Gets the uniform value.
	/// </summary>	
	/// <returns>Uniform value (Int)</returns>
	int GetInt(void) const;

	/// <summary>
	/// Gets the uniform value.
	/// </summary>	
	/// <returns>Uniform value (Float)</returns>
	float GetFloat(void) const;

	/// <summary>
	/// Gets the uniform value.
	/// </summary>	
	/// <returns>Uniform value (Vec3)</returns>
	const glm::vec3& GetVec3(void) const;

	/// <summary>
	/// Gets the uniform value.
	/// </summary>	
	/// <returns>Uniform value (Mat4)</returns>
	const glm::mat4& GetMat4(void) const;
};

