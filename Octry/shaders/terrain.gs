#version 430 core

in vec4 vs_color[1];
out flat vec4 gs_color;

in flat struct VS_DATA {
	int data[8];
} vs_data[1];

in flat int d[1];

layout (points) in;
layout (triangle_strip, max_vertices = 192) out;

vec4 modelview(vec4 pos)
{
	return vec4(pos.xzy*15./8. - vec3(15./16.),pos.w);
}

void main()
{
	vec4 pos = gl_in[0].gl_Position;
	float size = 1./(1<<d[0]);
	float s = size/2;
	vec4 color = vs_color[0];
	for(int i = 0; i < 8; i++)
	{
		if (vs_data[0].data[i] == 1)
		{
			vec4 lleft = /*vec4((i&4)?s:0, (i&2)?s:0, (i&1)?s:0,0) + */pos;
			int t = i;
			if (t >= 4) {t -= 4; lleft += vec4(s,0,0,0);}
			if (t >= 2) {t -= 2; lleft += vec4(0,s,0,0);}
			if (t >= 1) {t -= 1; lleft += vec4(0,0,s,0);}
			gl_Position = lleft + vec4(0,0,0,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(s,0,0,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(0,s,0,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(s,s,0,0);
			gl_Position = modelview(gl_Position);
			gs_color = color;
			EmitVertex();
			EndPrimitive();

			gl_Position = lleft + vec4(0,0,s,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(0,s,s,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(s,0,s,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(s,s,s,0);
			gl_Position = modelview(gl_Position);
			gs_color = color;
			EmitVertex();
			EndPrimitive();

			gl_Position = lleft + vec4(0,0,0,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(0,s,0,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(0,0,s,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(0,s,s,0);
			gl_Position = modelview(gl_Position);
			gs_color = color;
			EmitVertex();
			EndPrimitive();

			gl_Position = lleft + vec4(s,0,0,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(s,0,s,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(s,s,0,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(s,s,s,0);
			gl_Position = modelview(gl_Position);
			gs_color = color;
			EmitVertex();
			EndPrimitive();

			gl_Position = lleft + vec4(0,0,0,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(0,0,s,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(s,0,0,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(s,0,s,0);
			gl_Position = modelview(gl_Position);
			gs_color = color;
			EmitVertex();
			EndPrimitive();

			gl_Position = lleft + vec4(0,s,0,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(s,s,0,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(0,s,s,0);
			gl_Position = modelview(gl_Position);
			EmitVertex();
			gl_Position = lleft + vec4(s,s,s,0);
			gl_Position = modelview(gl_Position);
			gs_color = color;
			EmitVertex();
			EndPrimitive();
		}
	}

}