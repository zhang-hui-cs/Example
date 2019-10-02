#pragma once
#include "HelloTriangle.h"

class HelloTriangle1 :
	public HelloTriangle
{
public:
	virtual	void BindVertexData();
	virtual void Render();
};
