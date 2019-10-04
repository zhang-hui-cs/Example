#version 330 core
in vec3 pt;
out vec4 FragColor;
void main()
{
	FragColor = vec4(pt, 1.0f);
}