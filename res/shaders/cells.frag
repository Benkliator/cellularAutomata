#version 330 core

out vec4 fragColor;
in vec4 light;
in vec3 color;

void main(void)
{
    fragColor = vec4(color, 1.0) * light;
}
