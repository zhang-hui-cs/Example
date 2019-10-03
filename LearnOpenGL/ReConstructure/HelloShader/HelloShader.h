#pragma once
class HelloShader
{
protected:
	//const static char* _vertexShaderSource;
	//const static char* _fragmentShaderSource;

	int _vertexShader = -1;
	int _fragmentShader = -1;
	int _shaderProgram = -1;
	unsigned int _VAO = 0;
	unsigned int _VBO = 0;
	bool LinkShaderProgram();

	virtual	bool CreateVertexShader();
	virtual	bool CreateFragmentShader();
	virtual bool CreateVertextShaderInternal(int& vertexShader, const char* vsSource);
	virtual bool CreateFragmentShaderInternal(int& fragmentShader, const char* fsSource);
public:
	HelloShader();
	~HelloShader();

	virtual	bool CreateShaderProgram();
	virtual	void BindVertexData();
	virtual void Render();
};
