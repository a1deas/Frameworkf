#version 430 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;

out vec3 pass_Color;

uniform float u_Offset;

void main()
{
    gl_Position = vec4(Position.x + u_Offset, Position.y, Position.z, 1.0);
    pass_Color = Color;
}