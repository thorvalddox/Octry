#version 430 core

in vec4 vs_color[1];
out flat vec4 gs_color;

in flat struct VS_DATA {
	int data[8];
} vs_data[1];

in flat int d[1];

layout (points) in;
layout (triangle_strip, max_vertices = 192) out;

uniform float step;

float cx = 0.995, sx = 0.1;
float cs = cos(step), ss = sin(step);
mat4 mv_mat = mat4(vec4(cs * cx,-ss*2./3., -sx,0),vec4(ss,cs*2./3.,0,0),vec4(cs * sx,0,cx,0),vec4(0,0,0,1));


vec4 modelview(vec4 pos)
{

	vec4 modelvec = vec4(pos.xyz*15./8. - vec3(15./16.),pos.w);
	modelvec = mv_mat * modelvec;
	return modelvec.xzyw;
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
			ivec3 relpos = ivec3(0,0,0);
			if (t >= 4) {t -= 4; lleft += vec4(s,0,0,0);relpos.x = 1;}
			if (t >= 2) {t -= 2; lleft += vec4(0,s,0,0);relpos.y = 1;}
			if (t >= 1) {t -= 1; lleft += vec4(0,0,s,0);relpos.z = 1;}
#ifdef EXTENDED
			gl_Position = lleft + vec4(s/2,s/2,s/2,0);
			gl_Position = modelview(gl_Position);
			gs_color = color;
			EmitVertex();
			EndPrimitive();
#else

			//if (relpos.z == 0 || vs_data[0].data[i-1] == 0)
			{ 
				gl_Position = lleft + vec4(0,0,0,0);
				gl_Position = modelview(gl_Position);
				gs_color = color;
				EmitVertex();
				gl_Position = lleft + vec4(s,0,0,0);
				gl_Position = modelview(gl_Position);
				gs_color = color;
				EmitVertex();
				gl_Position = lleft + vec4(0,s,0,0);
				gl_Position = modelview(gl_Position);
				gs_color = color;
				EmitVertex();
				gl_Position = lleft + vec4(s,s,0,0);
				gl_Position = modelview(gl_Position);
				gs_color = color;
				gs_color = color;
				EmitVertex();
				EndPrimitive();
			}
			//if (relpos.z == 1 || vs_data[0].data[i+1] == 0)
			{
				gl_Position = lleft + vec4(0,0,s,0);
				gl_Position = modelview(gl_Position);
				gs_color = color;
				EmitVertex();
				gl_Position = lleft + vec4(0,s,s,0);
				gl_Position = modelview(gl_Position);
				gs_color = color;
				EmitVertex();
				gl_Position = lleft + vec4(s,0,s,0);
				gl_Position = modelview(gl_Position);
				gs_color = color;
				EmitVertex();
				gl_Position = lleft + vec4(s,s,s,0);
				gl_Position = modelview(gl_Position);
				gs_color = color;
				EmitVertex();
				EndPrimitive();
			}
			//if (relpos.x == 0 || vs_data[0].data[i-4] == 0)
			{
				gl_Position = lleft + vec4(0,0,0,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.9;
				EmitVertex();
				gl_Position = lleft + vec4(0,s,0,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.9;
				EmitVertex();
				gl_Position = lleft + vec4(0,0,s,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.9;
				EmitVertex();
				gl_Position = lleft + vec4(0,s,s,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.9;
				EmitVertex();
				EndPrimitive();
			}
			//if (relpos.x == 1 || vs_data[0].data[i+4] == 0)
			{
				gl_Position = lleft + vec4(s,0,0,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.9;
				EmitVertex();
				gl_Position = lleft + vec4(s,0,s,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.9;
				EmitVertex();
				gl_Position = lleft + vec4(s,s,0,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.9;
				EmitVertex();
				gl_Position = lleft + vec4(s,s,s,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.9;
				EmitVertex();
				EndPrimitive();
			}
			//if (relpos.y == 0 || vs_data[0].data[i-2] == 0)
			{
				gl_Position = lleft + vec4(0,0,0,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.8;
				EmitVertex();
				gl_Position = lleft + vec4(0,0,s,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.8;
				EmitVertex();
				gl_Position = lleft + vec4(s,0,0,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.8;
				EmitVertex();
				gl_Position = lleft + vec4(s,0,s,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.8;
				EmitVertex();
				EndPrimitive();
			}
			//if (relpos.y == 1 || vs_data[0].data[i+2] == 0)
			{
				gl_Position = lleft + vec4(0,s,0,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.8;
				EmitVertex();
				gl_Position = lleft + vec4(s,s,0,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.8;
				EmitVertex();
				gl_Position = lleft + vec4(0,s,s,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.8;
				EmitVertex();
				gl_Position = lleft + vec4(s,s,s,0);
				gl_Position = modelview(gl_Position);
				gs_color = color*0.8;
				EmitVertex();
				EndPrimitive();
			}
#endif
		}
	}

}