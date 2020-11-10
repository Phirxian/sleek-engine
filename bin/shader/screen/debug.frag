#version 430 core
#extension GL_ARB_explicit_uniform_location : enable

uniform sampler2D base;
uniform sampler2D normal;
uniform sampler2D position;

uniform vec2 resolution;
uniform float znear;
uniform float zfar;

in vec2 uv;

out vec4 color;

vec4 LinearizeDepth()
{
    vec3 z = (2.0 * znear) / (zfar + znear - texture2D(position, uv*2).bbb * (zfar - znear));
    return vec4(z,1);	
}

void main()
{
    if(uv.x < 0.5)
    {
        if(uv.y < 0.5)
            color.rgb = LinearizeDepth().rgb;
        else
            color.rg = texture2D(position, uv*2).rg;
    }
    else
    {
        if(uv.y < 0.5)
            color.rgb = texture2D(base, uv*2).rgb;
        else
            color.rgb = texture2D(normal, uv*2).rgb;
    }
        
    color.a = 1;
}