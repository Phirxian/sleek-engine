#version 430 core

uniform sampler2D base;
uniform sampler2D redux;
uniform sampler2D normal;
uniform sampler2D position;
uniform sampler2D last;

uniform vec2 resolution;
uniform float steep;

in vec2 uv;

out vec4 color;

void main()
{
    float _min = 1.0-pow(0.5, steep+1);
    float _max = pow(0.5, steep+1);
    
    if(uv.x >= _max || uv.y >= _max || uv.x >= _min)
    {
        color = texture2D(last, uv, 0);
        return;
    }
        
    vec2 uv0 = vec2((uv.xy - vec2(.5)) * 2.0);
    vec2 uv1 = vec2((uv.xy - vec2(.5)) * 2.0) + vec2(1, 0);
    vec2 uv2 = vec2((uv.xy - vec2(.5)) * 2.0) + vec2(1, 1);
    vec2 uv3 = vec2((uv.xy - vec2(.5)) * 2.0) + vec2(0, 1);
    
    vec4 luma = vec4(0.30, 0.59, 0.11, 0.0);

    float p0 = dot(luma, texture2D(last, uv0, 0));
    float p1 = dot(luma, texture2D(last, uv1, 0));
    float p2 = dot(luma, texture2D(last, uv2, 0));
    float p3 = dot(luma, texture2D(last, uv3, 0));

    float minv = min(min(p0, p1), min(p2, p3));
    float maxv = max(max(p0, p1), max(p2, p3));
    float mean = (p0 + p1 + p2 + p3) * 0.25;

    color = vec4(minv, maxv, mean, 1.0);
}
