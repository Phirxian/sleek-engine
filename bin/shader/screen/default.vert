#version 430 core

layout (location = 0) in vec3 iposition;
layout (location = 1) in vec3 inormal;
layout (location = 2) in vec2 icoord;
layout (location = 3) in vec4 icolor;

uniform sampler2D base;
uniform vec2 resolution;

out vec2 uv;

void main()
{
    uv = (iposition.xy + 1.0) * 0.5;
    gl_Position = vec4(iposition, 1.0f);
}
