#pragma once
#include <variant>
#include <memory>
#include "glm/glm.hpp"


/// <summary>
/// This enum represents all possible uniform data types.
/// It is equivalent with the variant fields in the Uniform class.
/// </summary>
enum class UniformType {
	Int,
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

private:
	Uniform() = default;

public:
	Uniform(int value);

	Uniform(float value);

	Uniform(const glm::vec3& value);

	Uniform(const glm::mat4& value);


	UniformType GetType(void) const;


	int GetInt(void) const;


	float GetFloat(void) const;
};

