#pragma once
#include "../HelloShader/HelloShader.h"

class HelloTexture :
	public HelloShader
{
protected:
	unsigned int _EBO = 0;
	unsigned int _texture = 0;
	virtual	bool CreateVertexShader();
	virtual	bool CreateFragmentShader();
	virtual void BindTexture();
	virtual void BindVertex();
public:
	virtual	void BindData();
	virtual void Render();
};
