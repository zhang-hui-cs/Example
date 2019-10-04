#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Tool/FileReader.h"

#include "HelloShaderExercises2.h"

bool HelloShaderExercises2::CreateVertexShader()
{
	const char* source = FileReader::ReadFile(".\\HelloShader\\Vertex-Exercises-2.shader");

	return this->CreateVertextShaderInternal(this->_vertexShader, source);
}

bool HelloShaderExercises2::CreateFragmentShader()
{
	const char* source = FileReader::ReadFile(".\\HelloShader\\Fragment-Exercises-2.shader");

	return this->CreateFragmentShaderInternal(this->_fragmentShader, source);
}

void HelloShaderExercises2::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(this->_shaderProgram);
	float timeValue = glfwGetTime();
	float offset = sin(timeValue) / 2.0f;
	int vertexColorLocation = glGetUniformLocation(this->_shaderProgram, "offset");
	glUniform3f(vertexColorLocation, offset, 0.0f, 0.0f);

	glBindVertexArray(this->_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}