#pragma once
#include "HelloTexture.h"
class HelloTextureExercise2 :
	public HelloTexture
{
protected:
	virtual	bool CreateVertexShader();
	virtual	bool CreateFragmentShader();
	virtual void BindTexture();
	virtual void BindVertexData();
};
