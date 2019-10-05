#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "HelloTriangle.h"

const char* HelloTriangle::_vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* HelloTriangle::_fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

HelloTriangle::HelloTriangle() {
}

HelloTriangle::~HelloTriangle() {
	if (this->_VAO > 0) {
		glDeleteVertexArrays(1, &this->_VAO);
	}

	if (this->_VBO > 0) {
		glDeleteBuffers(1, &this->_VBO);
	}

	if (this->_EBO > 0) {
		glDeleteBuffers(1, &this->_EBO);
	}
}

bool HelloTriangle::CreateVertexShader() {
	this->_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->_vertexShader, 1, &HelloTriangle::_vertexShaderSource, NULL);
	glCompileShader(this->_vertexShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(this->_vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(this->_vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}
	else
	{
		return true;
	}
}

bool HelloTriangle::CreateFragmentShader() {
	int success = -1;

	// fragment shader
	this->_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->_fragmentShader, 1, &HelloTriangle::_fragmentShaderSource, NULL);
	glCompileShader(this->_fragmentShader);

	// check for shader compile errors
	glGetShaderiv(this->_fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(this->_fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	else {
		return true;
	}
}

bool HelloTriangle::LinkShaderProgram() {
	this->_shaderProgram = glCreateProgram();
	glAttachShader(this->_shaderProgram, this->_vertexShader);
	glAttachShader(this->_shaderProgram, this->_fragmentShader);
	glLinkProgram(this->_shaderProgram);

	int success = 0;
	glGetProgramiv(this->_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(this->_shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(this->_vertexShader);
	glDeleteShader(this->_fragmentShader);

	return success;
}

bool HelloTriangle::CreateShaderProgram() {
	int vertexShader = 0;
	bool success = this->CreateVertexShader();
	if (!success) {
		return false;
	}

	int fragmentShader = 0;
	success = this->CreateFragmentShader();
	if (!success) {
		return false;
	}

	return this->LinkShaderProgram();
}

void HelloTriangle::BindData() {
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glGenVertexArrays(1, &this->_VAO);
	glGenBuffers(1, &this->_VBO);
	glGenBuffers(1, &this->_EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(this->_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void HelloTriangle::Render() {
	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// draw our first triangle
	glUseProgram(this->_shaderProgram);

	glBindVertexArray(this->_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}