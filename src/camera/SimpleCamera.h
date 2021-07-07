#pragma once
#include "CameraBase.h"
#include <glm/glm.hpp>
#include "../events/EventBus.h"
#include "../events/Event.hpp"


class SimpleCamera final : public CameraBase {
private:
	glm::mat4 V;
	glm::mat4 P;
	glm::mat4 PV;
	glm::vec2 windowRect;
	bool lmbIsDown;
	bool mmbIsDown;
	bool isFirstFrame;
	glm::vec2 lastMousePosNDC;

	bool isOrthographic;
	float orthographicZoomFactor;

	// these angles define camera orientation in world coordinates
	// NOTE: the camera position is NOT calculated in sphere coordinates
	float rho;
	float phi;
	float theta;

	const float rhoOrtho = 100.0f;
	float rhoSaved;

	glm::vec3 target;
	glm::vec3 position;

	//This is used to restore the initial camera position which is set in the ctor
	float rhoInitial;	

public:
	/// <summary>
	/// Constructor.
	/// Sets the initial camera position on the z+ axis with specified rho.
	/// </summary>
	/// <param name="eventBus">Ref to global event bus instance</param>
	/// <param name="windowRect">Initial window dimensions as vec2, x=width, y=height</param>
	/// <param name="pos">Initial rho value (distance target-position)</param>
	SimpleCamera(EventBus& eventBus, const glm::vec2& windowRect, float rhoInitial);


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
	/// Get the View Projection matrix P * V
	/// </summary>	
	/// <returns>PV</returns>
	const glm::mat4& GetViewProjectionMatrix(void) const override;

	/// <summary>
	/// Get the camera position (or "eye") in world coordinates
	/// </summary>
	/// <returns>camera position [world]</returns>
	const glm::vec3& GetPosition(void) const override;

	/// <summary>
	/// Resets the initial camera position.
	/// </summary>	
	void ResetPosition(void);

	/// <summary>
	/// Sets the projection mode.
	/// </summary>
	/// <param name="orthographic">True if mode is orthographic</param>
	void SetProjectionMode(bool orthographic);

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
	/// Performs a translation of the camera target according to mouse input
	/// (currently only on xz plane)
	/// </summary>
	/// <param name="x">Mouse x position [screen coordinates]</param>
	/// <param name="y">Mouse y position [screen coordinates]</param>
	void PerformTranslation(float x, float y);

	/// <summary>
	/// Performs a zoom notch by altering rho according to the scroll direction, at most up to a minimum value.
	/// </summary>
	/// <param name="dir">scroll direction</param>
	void PerformZoom(MouseScrollDirection dir);

	/// <summary>
	/// Calculates an updated view matrix from the camera positions rho, phi, theta
	/// and updates the position vector from the fourth matrix column (matrix is in homogenous coordinates).
	/// Updates view projection matrix PV.
	/// </summary>	
	void UpdateViewProjectionMatrixAndPosition(void);

	/// <summary>
	/// Calculates the camera projection matrix as orthographic or perspective projection,
	/// updates View projection matrix PV.
	/// </summary>	
	void CalcProjection(void);	

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



