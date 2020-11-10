#version 430 core
#extension GL_ARB_separate_shader_objects : enable

uniform sampler2D base;
uniform sampler2D normal;
uniform sampler2D position;
uniform sampler2D redux;
uniform sampler2D last;

uniform vec2 resolution;
uniform float znear;
uniform float zfar;

in vec2 uv;

out vec4 color;

vec4 bright(sampler2D tex, in vec2 uv)
{
    float bright_threshold = 2;
    vec4 color = texture2D(tex, uv);
    float lum = dot(vec4(0.30, 0.59, 0.11, 0.0), color);
    return bright_threshold*vec4(lum,lum,lum,1);
}

vec4 blur(sampler2D tex, in vec2 direction)
{ 
    vec4 b = vec4(0.0);
    
    vec2 off1 = vec2(1.411764705882353) * direction;
    vec2 off2 = vec2(3.294117647058823) * direction;
    vec2 off3 = vec2(5.176470588235294) * direction;
    
    b += bright(tex, uv) * 0.1964825501511404;
    b += bright(tex, uv + (off1 / resolution)) * 0.2969069646728344;
    b += bright(tex, uv - (off1 / resolution)) * 0.2969069646728344;
    b += bright(tex, uv + (off2 / resolution)) * 0.0944703978504473;
    b += bright(tex, uv - (off2 / resolution)) * 0.0944703978504473;
    b += bright(tex, uv + (off3 / resolution)) * 0.0103813624011480;
    b += bright(tex, uv - (off3 / resolution)) * 0.0103813624011480;
    
    return b;
}

vec3 linearToneMapping(vec3 color, float gamma)
{
    float exposure = 1.;
    color = clamp(exposure * color, 0., 1.);
    color = pow(color, vec3(1. / gamma));
    return color;
}

vec3 simpleReinhardToneMapping(vec3 color, float gamma)
{
    float exposure = 1.5;
    color *= exposure/(1. + color / exposure);
    color = pow(color, vec3(1. / gamma));
    return color;
}

vec3 lumaBasedReinhardToneMapping(vec3 color, float gamma)
{
    float luma = dot(color, vec3(0.2126, 0.7152, 0.0722));
    float toneMappedLuma = luma / (1. + luma);
    color *= toneMappedLuma / luma;
    color = pow(color, vec3(1. / gamma));
    return color;
}

vec3 whitePreservingLumaBasedReinhardToneMapping(vec3 color, float gamma)
{
    float white = 2.;
    float luma = dot(color, vec3(0.2126, 0.7152, 0.0722));
    float toneMappedLuma = luma * (1. + luma / (white*white)) / (1. + luma);
    color *= toneMappedLuma / luma;
    color = pow(color, vec3(1. / gamma));
    return color;
}

vec3 RomBinDaHouseToneMapping(vec3 color, float gamma)
{
    color = exp( -1.0 / ( 2.72*color + 0.15 ) );
    color = pow(color, vec3(1. / gamma));
    return color;
}

vec3 filmicToneMapping(vec3 color, float gamma)
{
    color = max(vec3(0.), color - vec3(0.004));
    color = (color * (6.2 * color + .5)) / (color * (6.2 * color + 1.7) + 0.06);
    return color;
}

vec3 Uncharted2ToneMapping(vec3 color, float gamma)
{
    float A = 0.15, B = 0.50, C = 0.10;
    float D = 0.20, E = 0.02, F = 0.30, W = 11.2;
    
    float exposure = 2.;
    
    color *= exposure;
    color  = ((color * (A * color + C * B) + D * E) / (color * (A * color + B) + D * F)) - E / F;
    color /= ((W * (A * W + C * B) + D * E) / (W * (A * W + B) + D * F)) - E / F;
    
    color = pow(color, vec3(1. / gamma));
    return color;
}

void main()
{
    vec4 luminance = texelFetch(redux, ivec2(0,0), 0);

    vec4 blured = 0.35*blur(last,  vec2(1,0))
                + 0.35*blur(last,  vec2(0,1))
                + 0.15*blur(last,  vec2(2,0))
                + 0.15*blur(last,  vec2(0,2));

    color = texture2D(last, uv);
    color.rgb += blured.rgb * 0.5;
    
    color.rgb = simpleReinhardToneMapping(color.rgb, 2.2);
}
