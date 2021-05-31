#pragma once
#include <variant>
#include "glm/glm.hpp"


//TODO: Maybe overhaul this, save uniforms on heap and use templates??

enum class MaterialUniformType {
	Int,
	Float,
	Vec3
};

/// <summary>
/// This class represents a "Material uniform": A uniform exclusively used for materials.
/// It can hold an int, float or glm::vec3 value.
/// </summary>
class MaterialUniform final {
public:
	const MaterialUniformType type;
	std::variant<int, float, glm::vec3> value;
	
private:
	MaterialUniform() = default;

public:
	MaterialUniform(int value): type(MaterialUniformType::Int), value(value) { }
	MaterialUniform(float value): type(MaterialUniformType::Float), value(value) { }
	MaterialUniform(const glm::vec3& value): type(MaterialUniformType::Vec3), value(value) { }
	
	~MaterialUniform() { }


	template <typename T>
	T GetValue(void) const {
		return std::get<(int)type>(value);
	}
};

