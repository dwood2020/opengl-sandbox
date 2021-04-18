#include <iostream>
#include "glad/glad.h"
#include "IupWindow.h"



void OnWindowResize(int w, int h) {
	glViewport(0, 0, w, h);
}


void CheckShaderCompilationStatus(unsigned int shaderId) {
	int success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[100];
		glGetShaderInfoLog(shaderId, 100, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED:\n" << infoLog << std::endl;
	}
}


int main(int argc, char* argv[]) {

	IupWindow window(800, 600, "IupWindow class - Test 1");		
	window.Init(argc, argv);

	window.MakeContextCurrent();

	//now load OpenGL
	if (!gladLoadGL()) {		
		std::cout << "gladLoadGL failed" << std::endl;
		return -1;
	}

	int w, h;
	window.GetWindowRect(w, h);
	glViewport(0, 0, w, h);

	window.SetOnResize(OnWindowResize);

	glClearColor(0.075f, 0.196f, 0.325f, 1.0f);	
	
	std::string glVersionStr = (const char*)glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << glVersionStr << std::endl;
	window.SetGLVersionLabel(glVersionStr);


	//==========================================================================
	// FROM OLD PROJECT

	//vertices in NDC for 1 triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	unsigned int vaoId;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	// create a fitting buffer for the vertex data on the graphics card:
	unsigned int vboId;		//buffer name
	glGenBuffers(1, &vboId);	//generate a buffer
	glBindBuffer(GL_ARRAY_BUFFER, vboId);	//specifies target to which buffer obj is bound => the current array_buffer is now "vbo"
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//creates&inits buffer obj data storage
	//try with glNamedBufferData(vbo, ...)

	// next, create a vertex shader:
	const char* vertexShaderSource = "#version 400 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main(){\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	unsigned int vertexShaderId;
	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);	//creates empty shader obj. Shader obj needs a shader source code attached.
	glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);	//shader source is now copied to shader obj
	glCompileShader(vertexShaderId);	//(attempts to) compile the shader

	//receive info about compilation status:
	CheckShaderCompilationStatus(vertexShaderId);

	// create a fragment shader, same procedure as vertex shader:
	const char* fragmentShaderSource =
		"#version 400 core\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		"}\0";

	unsigned int fragmentShaderId;
	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderId);
	CheckShaderCompilationStatus(fragmentShaderId);

	// finally, create a shader program:
	// (shader program is the final object of multiple shaders linked together)
	unsigned int shaderProgramId;
	shaderProgramId = glCreateProgram();	//creates program obj
	//now, link vertex and frag shaders:
	glAttachShader(shaderProgramId, vertexShaderId);
	glAttachShader(shaderProgramId, fragmentShaderId);
	glLinkProgram(shaderProgramId);

	//receive info about linking status:
	int success;
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[100];
		glGetProgramInfoLog(shaderProgramId, 100, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKING_FAILED:\n" << infoLog << std::endl;
	}

	glUseProgram(shaderProgramId);	//installs program obj as part of current rendering state

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	// shader program on the graphics card is now installed.
	// Next, Vertex data needs to be sent to the created buffer on the card
	// OpenGL needs to be told how to interpret the vertex data inside the buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);	//TODO check why this is possible
	glBindVertexArray(0);

	//==========================================================================


	while (!window.GetWindowShouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);

		//===========================
		glUseProgram(shaderProgramId);
		glBindVertexArray(vaoId);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//===========================

		window.SwapBuffers();
		window.DoFrame();
	}

	return 0;
}
