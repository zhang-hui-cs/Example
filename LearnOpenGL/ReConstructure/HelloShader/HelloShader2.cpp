#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "HelloShader2.h"

bool HelloShader2::CreateVertexShader()
{
	const char* source = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPos, 1.0);\n"
		"ourColor = aColor;\n"
		"}\n";

	return this->CreateVertextShaderInternal(this->_vertexShader, source);
}

bool HelloShader2::CreateFragmentShader()
{
	const char* source = "#version 330 core \n"
		"out vec4 FragColor; \n"
		"in vec3 ourColor; \n"
		"void main() \n"
		"{ \n"
		"	FragColor = vec4(ourColor, 1.0); \n"
		"} \n";

	return this->CreateFragmentShaderInternal(this->_fragmentShader, source);
}

//bool HelloShader2::CreateShaderProgram()
//{
//	return false;
//}

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