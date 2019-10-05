#pragma once
#include "HelloTexture.h"
class HelloTexture2 :
	public HelloTexture
{
protected:
	unsigned int _texture2 = 0;
	virtual	bool CreateVertexShader();
	virtual	bool CreateFragmentShader();
	virtual void BindTexture();

public:
	virtual void Render();
};
