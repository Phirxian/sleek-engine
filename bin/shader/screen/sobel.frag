#version 430 core

uniform sampler2D base;
uniform sampler2D normal;
uniform sampler2D position;
uniform sampler2D last;

uniform vec2 resolution;
uniform float znear;
uniform float zfar;

in vec2 uv;

out vec4 color;

vec4 sobel(sampler2D tex)
{
    vec2 inverse_resolution = 1.0/resolution;

    vec3 rgbN = textureOffset(tex, uv, ivec2(-1,  0)).xyz;
    vec3 rgbS = textureOffset(tex, uv, ivec2( 1,  0)).xyz;
    vec3 rgbW = textureOffset(tex, uv, ivec2( 0,  1)).xyz;
    vec3 rgbE = textureOffset(tex, uv, ivec2( 0, -1)).xyz;

    vec3 rgbNW = textureOffset(tex, uv, ivec2(-1,  1)).xyz;
    vec3 rgbNE = textureOffset(tex, uv, ivec2( 1,  1)).xyz;
    vec3 rgbSW = textureOffset(tex, uv, ivec2(-1, -1)).xyz;
    vec3 rgbSE = textureOffset(tex, uv, ivec2( 1, -1)).xyz;

    vec3 Gy = 2*rgbW + rgbNE + rgbNW - 2*rgbE - rgbSW - rgbSE;
    vec3 Gx = 2*rgbS + rgbNE + rgbSE - 2*rgbN - rgbNW - rgbSW;

    return vec4(sqrt(Gx*Gx+Gy*Gy),1.0);
}

void main()
{
    color = texture2D(base,  uv.xy);
    color = color * (1+sobel(base));
}
