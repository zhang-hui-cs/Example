#pragma once
#include "../HelloTexture/HelloTexture.h"
class HelloCoordinateSystem :
	public HelloTexture
{
protected:
	virtual	bool CreateVertexShader();
	virtual	bool CreateFragmentShader();
public:
	virtual void Render();
};
