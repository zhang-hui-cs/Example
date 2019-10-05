#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "HelloShader.h"

HelloShader::HelloShader() {
}

HelloShader::~HelloShader() {
	if (this->_VAO > 0) {
		glDeleteVertexArrays(1, &this->_VAO);
	}

	if (this->_VBO > 0) {
		glDeleteBuffers(1, &this->_VBO);
	}
}

bool HelloShader::CreateVertextShaderInternal(int& vertexShader, const char* vsSource) {
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vsSource, NULL);
	glCompileShader(vertexShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}
	else
	{
		return true;
	}
}

bool HelloShader::CreateVertexShader() {
	const char* vsSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	return this->CreateVertextShaderInternal(this->_vertexShader, vsSource);
}

bool HelloShader::CreateFragmentShaderInternal(int& fragmentShader, const char* fsSource)
{
	int success = -1;

	// fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fsSource, NULL);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	else {
		return true;
	}
}

bool HelloShader::CreateFragmentShader() {
	const char* fsSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = ourColor;\n"
		"}\n\0";

	return this->CreateFragmentShaderInternal(this->_fragmentShader, fsSource);
}

bool HelloShader::LinkShaderProgram() {
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

bool HelloShader::CreateShaderProgram() {
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

void HelloShader::BindData() {
	float vertices[] = {
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f   // top
	};

	glGenVertexArrays(1, &this->_VAO);
	glGenBuffers(1, &this->_VBO);

	glBindVertexArray(this->_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void HelloShader::Render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(this->_shaderProgram);
	float timeValue = glfwGetTime();
	float greenValue = sin(timeValue) / 2.0f + 0.5f;
	int vertexColorLocation = glGetUniformLocation(this->_shaderProgram, "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	glBindVertexArray(this->_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}