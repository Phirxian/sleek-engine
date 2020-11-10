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

#define FXAA_REDUCE_MIN (1.0/256.0)
#define FXAA_REDUCE_MUL (1.0/32.0)
#define FXAA_SPAN_MAX 8.0

vec4 fxaa(sampler2D tex)
{
    vec2 inverse_resolution = 1.0/resolution;

    vec3 rgbNW = textureOffset(tex, uv, ivec2(-1,  1)).xyz;
    vec3 rgbNE = textureOffset(tex, uv, ivec2( 1,  1)).xyz;
    vec3 rgbSW = textureOffset(tex, uv, ivec2(-1, -1)).xyz;
    vec3 rgbSE = textureOffset(tex, uv, ivec2( 1, -1)).xyz;

    vec3 rgbM  = texture2D(tex,  uv.xy).xyz;
    vec3 luma = vec3(0.299, 0.587, 0.114);

    float lumaNW = dot(rgbNW, luma);
    float lumaNE = dot(rgbNE, luma);
    float lumaSW = dot(rgbSW, luma);
    float lumaSE = dot(rgbSE, luma);
    float lumaM  = dot(rgbM,  luma);

    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    vec2 dir = vec2(-1,1) * (lumaNW + lumaSW - lumaNE - lumaSE);

    float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * FXAA_REDUCE_MUL),FXAA_REDUCE_MIN);
    float rcpDirMin = 1.0/(min(abs(dir.x), abs(dir.y)) + dirReduce);

    dir = inverse_resolution * min(
        vec2(FXAA_SPAN_MAX, FXAA_SPAN_MAX),
        max(vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX),dir * rcpDirMin)
    );

    vec3 rgbA = 0.25 * (
        texture2D(tex, uv.xy + dir * (1.0/3.0 - 0.5)).xyz +
        texture2D(tex, uv.xy + dir * (2.0/3.0 - 0.5)).xyz
    );

    vec3 rgbB = rgbA * 0.5 + 0.125 * (
        texture2D(tex, uv.xy + dir *  - 0.5).xyz +
        texture2D(tex, uv.xy + dir * 0.5).xyz
    );

    float lumaB = dot(rgbB, luma);

    if((lumaB < lumaMin) || (lumaB > lumaMax))
        return vec4(rgbA,1.0);
    else
        return vec4(rgbB,1.0);
}

void main()
{
    color = texture2D(last, uv).rgba;
    color *= fxaa(base);
}
