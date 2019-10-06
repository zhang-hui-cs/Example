#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "HelloCoordinateSystem.h"
#include "../Tool/FileReader.h"

bool HelloCoordinateSystem::CreateVertexShader()
{
	const char* source = FileReader::ReadFile(".\\HelloCoordinateSystem\\vertex.shader");

	return this->CreateVertextShaderInternal(this->_vertexShader, source);
}

bool HelloCoordinateSystem::CreateFragmentShader()
{
	const char* source = FileReader::ReadFile(".\\HelloCoordinateSystem\\fragment.shader");

	return this->CreateFragmentShaderInternal(this->_fragmentShader, source);
}

void HelloCoordinateSystem::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(this->_shaderProgram);

	glUniform1i(glGetUniformLocation(this->_shaderProgram, "texture1"), 0);

	// create transformations
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.5f));
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	unsigned int modelLoc = glGetUniformLocation(this->_shaderProgram, "model");
	unsigned int viewLoc = glGetUniformLocation(this->_shaderProgram, "view");
	unsigned int projectionLoc = glGetUniformLocation(this->_shaderProgram, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(this->_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}