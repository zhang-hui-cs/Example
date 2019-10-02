#pragma once
class HelloTriangle
{
private:
	const static char* _vertexShaderSource;
	const static char* _fragmentShaderSource;

	int _vertexShader = -1;
	int _fragmentShader = -1;
	int _shaderProgram = -1;
	unsigned int _VAO = 0;
	unsigned int _VBO = 0;
	bool CreateVertexShader();
	bool CreateFragmentShader();
	bool LinkShaderProgram();
public:
	HelloTriangle();
	~HelloTriangle();
	bool CreateShaderProgram();
	void BindVertexData();
	int GetShaderProgram();
	unsigned int GetVAO();
};
