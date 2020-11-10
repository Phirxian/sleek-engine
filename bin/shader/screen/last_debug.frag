#version 430 core

uniform sampler2D base;
uniform sampler2D redux;
uniform sampler2D normal;
uniform sampler2D position;
uniform sampler2D last;

uniform float steep;

in vec2 uv;

out vec4 color;

void main()
{
    color = texture2D(last, uv, 0);
}
