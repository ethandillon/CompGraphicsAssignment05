#version 330 core

out vec4 fColor;

in vec4 s_color;

void main()
{
    fColor = s_color;
//    fColor = vec4(1,0,1,1);
}
