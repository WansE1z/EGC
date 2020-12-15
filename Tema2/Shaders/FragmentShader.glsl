#version 330

// TODO: get values from fragment shader
in vec3 frag_position;
in vec3 frag_color;
in vec3 frag_normal;
in vec2 frag_texture;
in float noise;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec3 out_texture;

void main()
{
	vec3 color = vec3(frag_texture * ( 1. + noise), 0.0); // 1. -> prin incrementarea valorii se va face mai galben forma
	out_color = vec4(color.rgb, 1.0); // culoarea sferei reprezentata prin varianta rgb
	out_normal = vec4(frag_normal,1);
	out_texture = vec3(frag_texture , 1.0);
}