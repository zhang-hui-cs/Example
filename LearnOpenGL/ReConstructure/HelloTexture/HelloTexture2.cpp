#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Tool/stb_image.h"
#include "../Tool/FileReader.h"

#include "HelloTexture.h"
#include "HelloTexture2.h"

bool HelloTexture2::CreateVertexShader()
{
	const char* source = FileReader::ReadFile(".\\HelloTexture\\vertex2.shader");

	return this->CreateVertextShaderInternal(this->_vertexShader, source);
}

bool HelloTexture2::CreateFragmentShader()
{
	const char* source = FileReader::ReadFile(".\\HelloTexture\\fragment2.shader");

	return this->CreateFragmentShaderInternal(this->_fragmentShader, source);
}

void HelloTexture2::BindTexture()
{
	HelloTexture::BindTexture();

	// load and create a texture
	// -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(".\\HelloTexture\\awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	this->_texture2 = texture;
}

void HelloTexture2::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(this->_shaderProgram);

	glUniform1i(glGetUniformLocation(this->_shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(this->_shaderProgram, "texture2"), 1);

	glBindVertexArray(this->_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}