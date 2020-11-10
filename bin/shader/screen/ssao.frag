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

float readDepths(in vec2 uv)
{
    float z = (2.0 * znear) / (zfar + znear - texture2D(position, uv).b * (zfar - znear));
    return z;
}

float compareDepths(in float depth1, in vec2 uv)
{
    float depth2 = readDepths(uv);
    float neg = depth1-depth2;

    float aoCap = clamp(1.0-depth2/8, 0.45, 0.80);
    float aoMultiplier = 1000.0;
    float depthTolerance = 0.0015;

    float diff = sqrt(clamp(1.0-neg,0.0,1.0));
    float ao = min(aoCap,max(0.0,neg-depthTolerance) * aoMultiplier) * diff;

    return ao*ao*ao;
}

vec4 ssao(in vec2 uv)
{
    float depth = readDepths(uv);

    float spw = 1.0 / resolution.x / 2;
    float sph = 1.0 / resolution.y / 2;
    float pw = spw*(1.0-depth);
    float ph = sph*(1.0-depth);

    float ao = 0.0;
    float aoscale = 0.4;
    int iteration = 1;

    ao += compareDepths(depth, vec2(uv.x+pw,uv.y+ph));
    ao += compareDepths(depth, vec2(uv.x-pw,uv.y+ph));
    ao += compareDepths(depth, vec2(uv.x+pw,uv.y-ph));
    ao += compareDepths(depth, vec2(uv.x-pw,uv.y-ph));

    for(int i = 0; i<iteration; ++i)
    {
        float tmp = 0.0;
        spw *= 2.0;
        sph *= 2.0;
        aoscale *= 1.2;

        pw = spw*max(0.3, 1.0-depth);
        ph = sph*max(0.3, 1.0-depth);

        tmp += compareDepths(depth, vec2(uv.x+pw,uv.y));
        tmp += compareDepths(depth, vec2(uv.x-pw,uv.y));
        tmp += compareDepths(depth, vec2(uv.x,uv.y+ph));
        tmp += compareDepths(depth, vec2(uv.x,uv.y-ph));

        // diagonals
        tmp += compareDepths(depth, vec2(uv.x+2*pw,uv.y+ph));
        tmp += compareDepths(depth, vec2(uv.x-2*pw,uv.y+ph));
        tmp += compareDepths(depth, vec2(uv.x+2*pw,uv.y-ph));
        tmp += compareDepths(depth, vec2(uv.x-2*pw,uv.y-ph));

        // diagonals
        tmp += compareDepths(depth, vec2(uv.x+pw,uv.y+2*ph));
        tmp += compareDepths(depth, vec2(uv.x-pw,uv.y+2*ph));
        tmp += compareDepths(depth, vec2(uv.x+pw,uv.y-2*ph));
        tmp += compareDepths(depth, vec2(uv.x-pw,uv.y-2*ph));

        ao += tmp / aoscale;
    }

    ao /= iteration*12 + 4;
    ao = 1.0 - ao;

    return vec4(ao, ao, ao, 1);
}

void main()
{
    color = ssao(uv);
}
