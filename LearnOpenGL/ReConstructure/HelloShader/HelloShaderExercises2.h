#pragma once
#include "HelloShader.h"
class HelloShaderExercises2 :
	public HelloShader
{
protected:
	virtual	bool CreateVertexShader();
	virtual	bool CreateFragmentShader();

public:
	virtual void Render();
};
