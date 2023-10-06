#version 430 core
layout (location = 0) out vec4 out_Color;

uniform vec4 u_Color;

in vec3 pass_Color;

void main()
{
    out_Color = u_Color;
}