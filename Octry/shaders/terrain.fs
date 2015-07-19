#version 430 core

in flat vec4 gs_color;

out vec4 color;

void main()
{
	color = gs_color;
}