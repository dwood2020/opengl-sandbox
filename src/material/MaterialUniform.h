#pragma once
#include <variant>
#include <memory>
#include <glm/glm.hpp>


/// <summary>
/// This enum represents all possible uniform data types.
/// It is equivalent with the variant fields in the Uniform class.
/// </summary>
enum class MaterialUniformType {
	Int = 0,
	Float,
	Vec3,
	Mat4
};


/// <summary>
/// This class represents a material uniform.
/// (Material uniform: Is set once as a material property and not changed (unless the material changes)
/// Approach:
/// To compact memory a little, this union-like approach is applied.
/// "Small" uniform values are part of the variant directly vs.
/// "large" uniform values, e.g. mat4 are saved outside the variant.
/// 
/// This is a trade-off between memory usage and fragmentation optimization.
/// </summary>
class MaterialUniform final {	
private:	
	std::variant<int, float, glm::vec3, std::shared_ptr<glm::mat4>> value;	
	
	int location;

public:
	/// <summary>
	/// Default constructor. Sets the location to unspecified: -1
	/// </summary>
	MaterialUniform();

public:
	/// <summary>
	/// Constructor. Sets the location to unspecified: -1
	/// </summary>
	/// <param name="value">Uniform value (Integer)</param>
	MaterialUniform(int value);


	/// <summary>
	/// Constructor. Sets the location to unspecified: -1
	/// </summary>
	/// <param name="value">Uniform value (Float)</param>
	MaterialUniform(float value);


	/// <summary>
	/// Constructor. Sets the location to unspecified: -1
	/// </summary>
	/// <param name="value">Uniform value (Vec3)</param>
	MaterialUniform(const glm::vec3& value);

	/// <summary>
	/// Constructor. Sets the location to unspecified: -1
	/// </summary>
	/// <param name="value">Uniform value (Mat4)</param>
	MaterialUniform(const glm::mat4& value);

	/// <summary>
	/// Gets the uniform type as defined in the enum MaterialUniformType.
	/// </summary>	
	/// <returns>Uniform type</returns>
	MaterialUniformType GetType(void) const;

	/// <summary>
	/// Gets the cached uniform location. Returns the initial value -1 if not cached/set yet.
	/// </summary>	
	/// <returns>Uniform location</returns>
	int GetLocation(void) const;

	/// <summary>
	/// Sets the cached uniform location.
	/// </summary>
	/// <param name="location">Uniform location</param>
	void SetLocation(int location);

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

	/// <summary>
	/// Updates the Uniform value (Type Int)
	/// </summary>
	/// <param name="value">New value</param>
	void UpdateValue(int value);

	/// <summary>
	/// Updates the Uniform value (Type Float)
	/// </summary>
	/// <param name="value">New value</param>
	void UpdateValue(float value);

	/// <summary>
	/// Updates the Uniform value (Type Vec3)
	/// </summary>
	/// <param name="value">New value</param>
	void UpdateValue(const glm::vec3& value);

	/// <summary>
	/// Updates the Uniform value (Type Mat4)
	/// </summary>
	/// <param name="value">New value</param>
	void UpdateValue(const glm::mat4& value);
};

