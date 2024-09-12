#version 430

layout (location = 0) in vec3 iposition;
layout (location = 1) in vec3 inormal;
layout (location = 2) in vec2 icoord;
layout (location = 3) in vec4 icolor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 P; // position
out vec4 C; // color
out vec3 N; // normal
out vec2 uv;

void main()
{
    N = mat3(transpose(inverse(model))) * inormal;
    C = icolor / 255.0f;
    uv = icoord;
    P = model * vec4(iposition, 1.0f);
    gl_Position = projection * view * P;
}