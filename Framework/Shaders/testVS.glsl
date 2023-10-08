#version 430 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 UV;

uniform mat4 u_MVP;

out vec2 pass_UV;

void main()
{
    gl_Position = u_MVP * vec4(Position, 1.0);
    pass_UV = UV;
}