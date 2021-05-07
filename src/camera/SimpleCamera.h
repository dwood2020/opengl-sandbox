#pragma once
#include "CameraBase.h"
#include <glm/glm.hpp>
#include "../events/EventBus.h"
#include "../events/Event.hpp"


class SimpleCamera final : public CameraBase {
private:
	glm::mat4 V;
	glm::mat4 P;
	glm::vec2 windowRect;
	bool lmbIsDown;
	bool isFirstFrame;
	glm::vec2 lastMousePosNDC;

	// these angles define camera orientation in world coordinates
	// NOTE: the camera position is NOT calculated in sphere coordinates
	float rho;
	float phi;
	float theta;

	glm::vec3 target;
	glm::vec3 position;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="eventBus">Ref to global event bus instance</param>
	/// <param name="windowRect">Initial window dimensions as vec2, x=width, y=height</param>
	/// <param name="pos">Initial camera position. Should be on the z+ axis, other positions are untested.</param>
	SimpleCamera(EventBus& eventBus, const glm::vec2& windowRect, const glm::vec3& pos);


	~SimpleCamera();

	/// <summary>
	/// Get the view matrix
	/// </summary>
	/// <returns>V</return>	
	const glm::mat4& GetViewMatrix(void) const override;

	/// <summary>
	/// Get the position matrix
	/// </summary>
	/// <returns>P</returns>
	const glm::mat4& GetProjectionMatrix(void) const override;

	/// <summary>
	/// Get the camera position (or "eye") in world coordinates
	/// </summary>
	/// <returns>camera position [world]</returns>
	const glm::vec3& GetPosition(void) const override;

	/// <summary>
	/// The event handler (see CameraBase)
	/// </summary>
	void OnEvent(Event& e) override;

private:
	/// <summary>
	/// Processes the received mouse button input events,
	/// sets boolean member fields if neccessary.
	/// </summary>
	void ProcessMouseButtonInput(MouseButtonCode mbCode, bool isPressed);

	/// <summary>
	/// Processes the received mouse moved events depending on boolean members' values
	/// </summary>
	void ProcessMouseMoveInput(int x, int y);
	
	/// <summary>
	/// Performs a rotation according to mouse input
	/// </summary>
	/// <param name="x">Mouse x position [screen coordinates]</param>
	/// <param name="y">Mouse y position [screen coordinates]</param>
	void PerformRotation(float x, float y);

	/// <summary>
	/// Calculates the camera projection matrix as orthographic or perspective projection.
	/// </summary>
	/// <param name="asOrthographic">True for orthographic proj., False for perspective proj.</param>
	void CalcProjectionMatrix(bool asOrthographic = false);	

	/// <summary>
	/// Transforms screen coordinates into Normalized Device Coordinates (NDC)
	/// with top left = (-1,1) ; center = (0,0) ; bottom right = (1,-1)
	/// </summary>
	glm::vec2 ScreenToNDC(const glm::vec2& posScreen) const;

	/// <summary>
	/// Retrieves a signed delta between mouse pos in last (active) and current frame and in NDC.
	/// Handles zero crossings correctly.
	/// </summary>
	/// <param name="posNDC">mouse pos [NDC] in current frame</param>	
	/// <returns>delta [NDC]</returns>
	glm::vec2 DeltaNDC(const glm::vec2& posNDC) const;

};



