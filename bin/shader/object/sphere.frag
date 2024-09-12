#version 430

in vec2 uv;
in vec3 N;
in vec4 P;
in vec4 C;

uniform sampler2D base;

out vec4 color;
out vec4 normal;
out vec4 position;

float atan2(in float y, in float x)
{
    float s = float(abs(x) > abs(y));
    return mix(3.14159265359/2.0 - atan(x,y), atan(y,x), s);
}

void main()
{
    float uvx = 0.5 - atan2(N.z, N.y) / 3.14159265359 / 2.0;
    float uvy = 0.5 - N.x * 0.5;

    color = C*texture2D(base, vec2(uvx, uvy));
    normal = vec4(normalize(N),1);

    position = vec4(P.xy / P.w * gl_FragCoord.z, gl_FragCoord.z, 1);
}
