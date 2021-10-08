#pragma once


/// <summary>
/// This class handles all OpenGL render states.
/// It shall cache all states to minimize state changes during rendering.
/// States are cached as member variables.
/// </summary>
class GLStateHandler final {
private:
	bool depthTestingEnabled;
	bool blendingEnabled;
	bool faceCullingEnabled;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	GLStateHandler();

	~GLStateHandler();


	/// <summary>
	/// Sets OpenGL depth testing state.
	/// </summary>
	/// <param name="state">True: Depth testing enabled</param>
	void SetDepthTesting(bool state);


	/// <summary>
	/// Sets OpenGL blending state.
	/// </summary>
	/// <param name="state">True: Blending enabled.</param>
	void SetBlending(bool state);


	/// <summary>
	/// Sets OpenGL face culling state.
	/// </summary>
	/// <param name="state">True: Face culling enabled.</param>
	void SetFaceCulling(bool state);
};

