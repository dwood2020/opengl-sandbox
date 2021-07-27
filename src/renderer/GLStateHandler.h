#pragma once


/// <summary>
/// This class handles all OpenGL render states.
/// It shall cache all states to minimize state changes during rendering.
/// </summary>
class GLStateHandler final {
private:
	bool blendingEnabled;
	bool faceCullingEnabled;

public:
	GLStateHandler();

	~GLStateHandler();


	void SetBlending(bool state);

	void SetFaceCulling(bool state);
};

