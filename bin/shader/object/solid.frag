#version 430 core

in vec4 P; // position
in vec4 C; // color
in vec3 N; // normal
in vec2 uv;

uniform sampler2D base;

out vec4 color;
out vec4 normal;
out vec4 position;

void main()
{
    color = C*texture2D(base, uv);
    normal = vec4(normalize(N),1);

    position = vec4(P.xy / P.w * gl_FragCoord.z, gl_FragCoord.z, 1);
}
