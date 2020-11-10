#version 430 core

layout (location = 0) in vec3 iposition;
layout (location = 1) in vec3 inormal;
layout (location = 2) in vec2 icoord;
layout (location = 3) in vec4 icolor;

layout (location = 4) in vec4 iweight;
layout (location = 5) in ivec4 iboneid;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 bones[32];
uniform mat4 offset;

out vec4 P; // position
out vec4 C; // color
out vec3 N; // normal
out vec2 uv;

mat4 build_animation_matrix()
{
    return bones[iboneid.x] * iweight.x
         + bones[iboneid.y] * iweight.y
         + bones[iboneid.z] * iweight.z
         + bones[iboneid.w] * iweight.w;
}

void main()
{
    mat4 transform = model * build_animation_matrix();

    N = normalize(transpose(inverse(mat3(transform))) * inormal);
    C = icolor/255.f;
    C = iweight;
    uv = icoord;
    P = transform * vec4(iposition, 1.0f);

    gl_Position = projection * view * P;
}
