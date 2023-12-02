#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out vec4 v_color;

void main()
{
	v_color = color;
	gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(position.x, position.y, position.z, 1.0f);
}