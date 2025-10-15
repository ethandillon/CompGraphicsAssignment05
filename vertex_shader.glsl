
#version 330 core

in vec4 b_position;
in vec4 b_color;

uniform mat4 u_transform;

out vec4 s_color;

void
main()
{
    s_color = b_color;
    gl_Position = u_transform * b_position;
}
