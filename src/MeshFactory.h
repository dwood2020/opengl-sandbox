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
	/// Generates a cone mesh. 0 (in local coordinates) is located in the center of the bottom circle.
	/// </summary>
	/// <param name="r">radius of bottom circle</param>
	/// <param name="h">height of cone</param>
	/// <param name="points">number of points on the bottom circle</param>
	/// <returns>Cone mesh object</returns>
	Mesh MakeCone(float r, float h, int points = 10) const;

	/// <summary>
	/// Generates a sphere mesh. 0 (in local coordinates) is located in the center.
	/// The mesh is generated in a geographic coordinate system, north and south pole are located on the (local) y-axis.
	/// Texture coordinates are optional.
	/// </summary>
	/// <param name="r">Radius</param>
	/// <param name="nrLat">Number of Latitudes</param>
	/// <param name="nrLong">Number of longitudes</param>
	/// <param name="isTextured">True if texture coordinates shall be created</param>
	/// <returns>Sphere mesh object</returns>
	Mesh MakeSphere(float r, int nrLat = 10, int nrLong = 10, bool isTextured = false) const;

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

	/// <summary>
	/// Generates a cone vertex and index list.
	/// </summary>
	/// <param name="vertices">vertices vector to write to</param>
	/// <param name="normals">normals vector to write to</param>
	/// <param name="indices">indices vector to write to</param>
	/// <param name="points">number of points on the bottom circle of the cone</param>
	/// <param name="r">radius of the bottom ring</param>
	/// <param name="h">height</param>
	void MakeCone(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<unsigned int>& indices, int points, float r, float h) const;

	/// <summary>
	/// Generates a sphere vertex + index list + optionally texture coordinates list
	/// </summary>
	/// <param name="vertices">vertices vector to write to</param>
	/// <param name="normals">normals vector to write to</param>
	/// <param name="indices">indices vector to write to</param>
	/// <param name="texCoords">texture coords vector to write to (optional)</param>
	/// <param name="nrLat">number of latitudes</param>
	/// <param name="nrLong">number of longitudes</param>
	/// <param name="r">radius</param>
	void MakeIndexedSphere(std::vector<glm::vec3>* vertices, std::vector<glm::vec3>* normals, std::vector<unsigned int>* indices, std::vector<glm::vec2>* texCoords, int nrLat, int nrLong, float r) const;
};

