#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Tool/FileReader.h"
#include "HelloShader2.h"

bool HelloShader2::CreateVertexShader()
{
	const char* source = FileReader::ReadFile(".\\HelloShader\\Vertex2.shader");

	return this->CreateVertextShaderInternal(this->_vertexShader, source);
}

bool HelloShader2::CreateFragmentShader()
{
	const char* source = FileReader::ReadFile(".\\HelloShader\\Fragment2.shader");

	return this->CreateFragmentShaderInternal(this->_fragmentShader, source);
}

void HelloShader2::BindVertexData()
{
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
	};

	glGenVertexArrays(1, &this->_VAO);
	glGenBuffers(1, &this->_VBO);

	glBindVertexArray(this->_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void HelloShader2::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(this->_shaderProgram);

	glBindVertexArray(this->_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}