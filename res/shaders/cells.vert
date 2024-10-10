#version 330 core
layout (location = 0) in uvec4 vertex;

uniform mat4 view;
uniform mat4 projection;

out vec4 light;
out vec3 color;

void main(void)
{
    light = vec4(1.0, 1.0, 1.0, 1.0);
    uint occlusion = vertex.a;
    switch (occlusion) {
        case 0u:
            light *= vec4(1.0, 1.0, 1.0, 1.0);
            break;
        case 1u:
            light *= vec4(0.68, 0.68, 0.68, 1.0);
            break;
        case 2u:
            light *= vec4(0.55, 0.55, 0.55, 1.0);
            break;
        case 3u:
            light *= vec4(0.45, 0.45, 0.45, 1.0);
            break;
    }

    color = vec3(vec3(vertex.xyz) / 75);

    gl_Position = projection * view * vec4(vertex.xyz * 0.25, 1.0);
}
