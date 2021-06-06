#pragma once
#include <vector>

#include "../glad/glad.h"
#include <glm/glm.hpp>

#include "../Mesh.h"
#include "../material/MaterialBase.h"
#include "../Lighting.h"
#include "../camera/CameraBase.h"
#include "RenderCommand.hpp"


class SimpleRenderer final {
private:
	Lighting* lighting;
	CameraBase* camera;

	std::vector<RenderCommand> renderCommands;

public:
	SimpleRenderer();

	SimpleRenderer(Lighting& lighting, CameraBase& camera);

	~SimpleRenderer();


	void AddCommand(const glm::mat4& modelMatrix, Mesh* mesh, MaterialBase* material);


	void PrepareCommands(void);


	void ExecuteCommands(void);

};

