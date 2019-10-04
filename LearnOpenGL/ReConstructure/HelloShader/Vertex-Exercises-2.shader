#version 330 core
layout(location = 0) in vec3 aPos;
uniform vec3 offset;

void main()
{
	gl_Position = vec4(aPos.x + offset.x, aPos.y + offset.y, aPos.z + offset.z, 1.0);
	// gl_Position = vec4(aPos, 1.0);
}