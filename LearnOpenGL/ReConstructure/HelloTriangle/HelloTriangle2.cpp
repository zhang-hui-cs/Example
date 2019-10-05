#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "HelloTriangle2.h"

HelloTriangle2::~HelloTriangle2() {
	if (this->_pVAOs != NULL) {
		glDeleteVertexArrays(2, this->_pVAOs);

		delete[] this->_pVAOs;
		this->_pVAOs = NULL;
	}

	if (this->_pVBOs != NULL) {
		glDeleteBuffers(2, this->_pVBOs);

		delete[] this->_pVBOs;
		this->_pVBOs = NULL;
	}
}

void HelloTriangle2::BindData() {
	float vertices1[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f,  0.5f, 0.0f,  // top left
	};

	float vertices2[] = {
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	};

	this->_pVAOs = new unsigned int[2];
	this->_pVBOs = new unsigned int[2];

	glGenVertexArrays(2, this->_pVAOs);
	glGenBuffers(2, this->_pVBOs);

	glBindVertexArray(this->_pVAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, this->_pVBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(this->_pVAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, this->_pVBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void HelloTriangle2::Render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(this->_pShaderProgram[0]);
	glBindVertexArray(this->_pVAOs[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glUseProgram(this->_pShaderProgram[1]);
	glBindVertexArray(this->_pVAOs[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool HelloTriangle2::CreateFragmentShader() {
	int success = -1;
	this->_pFragmentShader = new int[2];

	this->_pFragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->_pFragmentShader[0], 1, &HelloTriangle::_fragmentShaderSource, NULL);
	glCompileShader(this->_pFragmentShader[0]);
	glGetShaderiv(this->_pFragmentShader[0], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(this->_pFragmentShader[0], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	const char* fss2 = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
		"}\n\0";

	this->_pFragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->_pFragmentShader[1], 1, &fss2, NULL);
	glCompileShader(this->_pFragmentShader[1]);
	glGetShaderiv(this->_pFragmentShader[1], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(this->_pFragmentShader[1], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	return true;
}

bool HelloTriangle2::CreateShaderProgram() {
	if (!this->CreateVertexShader()) {
		return false;
	}

	if (!this->CreateFragmentShader()) {
		return false;
	}

	return	this->LinkShaderProgram();
}

bool HelloTriangle2::LinkShaderProgram() {
	this->_pShaderProgram = new int[2];

	this->_pShaderProgram[0] = glCreateProgram();
	glAttachShader(this->_pShaderProgram[0], this->_vertexShader);
	glAttachShader(this->_pShaderProgram[0], this->_pFragmentShader[0]);
	glLinkProgram(this->_pShaderProgram[0]);

	int success = 0;
	glGetProgramiv(this->_pShaderProgram[0], GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(this->_pShaderProgram[0], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

		return false;
	}

	this->_pShaderProgram[1] = glCreateProgram();
	glAttachShader(this->_pShaderProgram[1], this->_vertexShader);
	glAttachShader(this->_pShaderProgram[1], this->_pFragmentShader[1]);
	glLinkProgram(this->_pShaderProgram[1]);

	success = 0;
	glGetProgramiv(this->_pShaderProgram[1], GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(this->_pShaderProgram[1], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

		return false;
	}

	glDeleteShader(this->_vertexShader);
	glDeleteShader(this->_pFragmentShader[0]);
	glDeleteShader(this->_pFragmentShader[1]);

	return success;
}