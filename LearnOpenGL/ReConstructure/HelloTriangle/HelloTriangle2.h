#pragma once
#include "HelloTriangle.h"
class HelloTriangle2 :
	public HelloTriangle
{
private:
	unsigned int* _pVAOs = NULL;
	unsigned int* _pVBOs = NULL;
	int* _pShaderProgram = NULL;
	int* _pFragmentShader = NULL;
protected:
	virtual bool CreateFragmentShader();
	virtual 	bool LinkShaderProgram();
public:
	virtual bool CreateShaderProgram();
	virtual void BindData();
	virtual void Render();

	~HelloTriangle2();
};
