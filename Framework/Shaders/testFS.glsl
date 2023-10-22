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
    //Base
    out_Color = tex_Color + u_Color;

    //Inversion
    //out_Color = vec4(vec3(1.0 - texture(u_Texture[index], pass_UV)), 1.0);

    //Grey
    //float average = 0.2126 * out_Color.r + 0.7152 * out_Color.g + 0.0722 * out_Color.b;
    //out_Color = vec4(average, average, average, 1.0);



}