#version 430 core
#extension GL_ARB_separate_shader_objects : enable

uniform sampler2D base;
uniform sampler2D normal;
uniform sampler2D position;
uniform sampler2D last;

uniform vec2 resolution;
uniform float znear;
uniform float zfar;

in vec2 uv;

out vec4 color;

void main()
{
    color = vec4(1);
}
