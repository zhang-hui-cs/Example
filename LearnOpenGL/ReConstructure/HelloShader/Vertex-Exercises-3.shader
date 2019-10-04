#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 pt;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	pt = vec3(aPos.x + 0.5f, aPos.y + 0.5f, aPos.z);
}