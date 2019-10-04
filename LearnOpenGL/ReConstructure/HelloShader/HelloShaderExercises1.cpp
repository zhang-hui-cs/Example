#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Tool/FileReader.h"

#include "HelloShaderExercises1.h"

bool HelloShaderExercises1::CreateVertexShader()
{
	const char* source = FileReader::ReadFile(".\\HelloShader\\Vertex-Exercises-1.shader");

	return this->CreateVertextShaderInternal(this->_vertexShader, source);
}