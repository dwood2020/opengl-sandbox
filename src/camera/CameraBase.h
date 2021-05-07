#pragma once
#include <glm/glm.hpp>
#include "../events/EventListener.hpp"
#include "../events/EventBus.h"
#include "../events/Event.hpp"


class CameraBase : public EventListener {
protected:	
	bool PIsDirty;
	bool VIsDirty;

public:
	CameraBase();
	virtual ~CameraBase();
	
	/// <summary>
	/// This returns true if V has changed and the shaders require a uniform update.
	/// </summary>
	/// <returns>True if V dirty, see above</returns>
	bool GetViewMatrixIsDirty(void) const;

	/// <summary>
	/// This returns True if P has changed and the shaders require a uniform update.
	/// </summary>	
	/// <returns>True if P dirty, see above</returns>
	bool GetProjectionMatrixIsDirty(void) const;

	/// <summary>
	/// This shall be called once after V and P updates are passed everywhere needed
	/// (all shader uniforms are set, ...)
	/// </summary>		
	void ResetDirtyState(void);	//TODO: change this in 2 separates or change everything into VP-Matrix usage

	/// <summary>
	/// Get the View Matrix	
	/// </summary>
	/// <returns>V</returns>
	virtual const glm::mat4& GetViewMatrix(void) const = 0;

	/// <summary>
	/// Get the Projection Matrix
	/// </summary>
	/// <returns>V</returns>
	virtual const glm::mat4& GetProjectionMatrix(void) const = 0;

	/// <summary>
	/// Get the camera position (the "eye" position)
	/// </summary>
	/// <returns>eye position</returns>
	virtual const glm::vec3& GetPosition(void) const = 0;

	/// <summary>
	/// Every camera subclass needs to implement this event handler method.
	/// (As every camera is an EventListener)
	/// </summary>
	virtual void OnEvent(Event& e) override = 0;

};

