#version 430 core

in vec2 uv;
in vec3 N;
in vec4 P;
in vec4 C;

uniform sampler2D base;

out vec4 color;
out vec4 normal;
out vec4 position;

void main()
{
    float render = 0.45;
    vec3 face = cross(dFdx(position), dFdy(position));
    
    float difference = length(position-face);
          difference = pow(difference + 1.0, 3.0) - 2.6;
          
    color = vec4(difference, 0.0, 0.0, 1.0);
}
