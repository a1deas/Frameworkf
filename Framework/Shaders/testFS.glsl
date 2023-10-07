#version 430 core
layout (location = 0) out vec4 out_Color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec2 pass_UV;

void main()
{
    vec4 tex_Color = texture(u_Texture, pass_UV);
    out_Color = tex_Color + u_Color;
}