#pragma once
#include "HelloShader.h"
class HelloShaderExercises3 :
	public HelloShader
{
protected:
	virtual	bool CreateVertexShader();
	virtual	bool CreateFragmentShader();

public:
	virtual void Render();
};
