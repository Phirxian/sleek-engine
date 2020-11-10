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

uniform vec3 handle[32];
uniform vec3 position[32];
uniform vec4 rotation[32];
uniform vec3 scale[32];

out vec4 P; // position
out vec4 C; // color
out vec3 N; // normal
out vec2 uv;

#define weighted_interpolation(node, W)           \
    node[iboneid.x]*W.x + node[iboneid.y]*W.y +   \
    node[iboneid.z]*W.z + node[iboneid.w]*W.w

mat4 build_animation_matrix()
{
    vec4 R = vec4(0.0);

    for(int i = 0; i < 4; i++)
    {
        float w = iweight[i];
        w *= 1.0 - 2.0*float(dot(rotation[iboneid[i]], R) < 0.0);
        R += rotation[iboneid[i]] * w;
    }

    vec3 T = weighted_interpolation(position, iweight);
    vec3 H = weighted_interpolation(handle, iweight);
    vec3 S = weighted_interpolation(scale, iweight);

    float magnitude = length(R);
    R /= magnitude;
    H /= magnitude;
    T /= magnitude;

    vec3 Z = 2.0*R.xyz*R.xyz;
    vec3 A = -Z.yxx - Z.zzy;
    vec3 B = 2.0*R.xyz*R.w;
    vec3 C = 2.0*R.xxy*R.zyz;

    mat4 identity = mat4(1.0);

    mat4 rotation = mat4(
        vec4(   A.x   , C.y + B.z, C.x - B.y, 0),
        vec4(C.y - B.z,    A.y   , C.z + B.x, 0),
        vec4(C.x + B.y, C.x - B.x,    A.z   , 0),
        vec4(T+H, 0.0)
    );

    mat4 scale = mat4(
        vec4(S.x,   0,   0, 0.0),
        vec4(  0, S.y,   0, 0.0),
        vec4(  0,   0, S.z, 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );

    mat4 inv_h = mat4(
        vec4( 1.0,   0,   0, 0.0),
        vec4(   0, 1.0,   0, 0.0),
        vec4(   0,   0, 1.0, 0.0),
        vec4(-H, 1.0)
    );

    return (identity+rotation) * scale * inv_h;
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
