#pragma once
#include "..\HelloTexture\HelloTexture.h"
class HelloCoordinateSystem2 :
	public HelloTexture
{
protected:
	virtual bool CreateVertexShader();
	virtual bool CreateFragmentShader();
	virtual void BindTexture();
	virtual void BindVertex();
public:
	virtual void Render();
};
