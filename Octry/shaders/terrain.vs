#version 430 core

layout (location = 0) in vec3 pos;
layout (location = 1) in int depth;
layout (location = 2) in int data[8];


out vec4 vs_color;

out flat struct VS_DATA {
	int data[8];
} vs_data;

out flat int d;

void main()
{
	d = depth;
	for (int i = 0; i < 8; i++)
	{
		vs_data.data[i] = data[i];
	}
	float fract = 0;
	gl_Position = vec4(pos/1024., 1.0);
	vs_color = vec4(1.0,fract,fract,1.0);
}
