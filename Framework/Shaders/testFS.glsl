#version 430 core
layout (location = 0) out vec4 out_Color;

uniform vec4 u_Color;
uniform sampler2D u_Texture[2];


in vec2 pass_UV;
in float pass_TexIndex;

void main()
{
    int index = int(pass_TexIndex);
    vec4 tex_Color = texture(u_Texture[index], pass_UV);
    out_Color = tex_Color + u_Color;
}