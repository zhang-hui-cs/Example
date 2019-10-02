#pragma once
class HelloTriangle
{
protected:
	const static char* _vertexShaderSource;
	const static char* _fragmentShaderSource;

	int _vertexShader = -1;
	int _fragmentShader = -1;
	int _shaderProgram = -1;
	unsigned int _VAO = 0;
	unsigned int _VBO = 0;
	unsigned int _EBO = 0;
	bool CreateVertexShader();
	bool LinkShaderProgram();

	virtual	bool CreateFragmentShader();
public:
	HelloTriangle();
	~HelloTriangle();

	virtual	bool CreateShaderProgram();
	virtual	void BindVertexData();
	virtual void Render();
};
