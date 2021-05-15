#pragma once
#include "Mesh.h"


class MeshFactory final {
public:
	MeshFactory();
	~MeshFactory();

	/// <summary>
	/// Generates a rectangle mesh in the xy plane. 
	/// </summary>
	/// <param name="w">Width</param>
	/// <param name="h">Height</param>
	/// <param name="z">z position</param>
	/// <returns>Rectangle mesh object</returns>
	Mesh MakeRectangle(float w, float h, float z = 0.0f) const;

	/// <summary>
	/// Generates a cube mesh. 0 (in local coordinates) is located in its center.
	/// </summary>
	/// <param name="l">Side length</param>
	/// <param name="isTextured">True if texture coordinates shall be included.</param>
	/// <returns>Cube mesh object</returns>
	Mesh MakeCube(float l, bool isTextured = false) const;

	/// <summary>
	/// Generates a simple coordinate system consisting of a line each in positive x-, y- and z-direction.
	/// </summary>
	/// <param name="l">Length of lines</param>
	/// <returns>Coordinate system mesh object</returns>
	Mesh MakeSimpleCoordinateSystem(float l = 1.0f) const;

	/// <summary>
	/// Generates a 3D coordinate system consisting of a thin cylinder each in positive x-, y- and z-direction.
	/// </summary>
	/// <param name="l">Length of axes</param>
	/// <returns>Coordinate system mesh object</returns>
	Mesh MakeCoordinateSystem(float l = 1.0f) const;

	/// <summary>
	/// Generates a simple quadratic grid mesh in the xz-plane of size 2l * 2l.
	/// NOTE: Larger grid sizes quickly lead to heavy aliasing effects.
	/// </summary>
	/// <param name="l">Half edge length, see summary</param>	
	/// <returns>Grid mesh object</returns>
	Mesh MakeSimpleGrid(float l = 10.0f) const;


private:
	/// <summary>
	/// Generates a cylinder vertex and index list.
	/// </summary>
	/// <param name="vertices">vertices vector to write to</param>
	/// <param name="indices">indices vector to write to</param>
	/// <param name="points">number of points on each end circle of the cylinder</param>
	/// <param name="r">radius</param>
	/// <param name="h">height</param>
	void MakeCylinder(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices, int points, float r, float h) const;


	void MakeCone(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices, int points, float r, float h) const;
};

