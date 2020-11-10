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

vec4 blur(sampler2D tex, in vec2 direction)
{ 
  vec4 b = vec4(0.0);
  
  vec2 off1 = vec2(1.411764705882353) * direction;
  vec2 off2 = vec2(3.2941176470588234) * direction;
  vec2 off3 = vec2(5.176470588235294) * direction;
  
  b += texture2D(tex, uv) * 0.1964825501511404;
  b += texture2D(tex, uv + (off1 / resolution)) * 0.2969069646728344;
  b += texture2D(tex, uv - (off1 / resolution)) * 0.2969069646728344;
  b += texture2D(tex, uv + (off2 / resolution)) * 0.09447039785044732;
  b += texture2D(tex, uv - (off2 / resolution)) * 0.09447039785044732;
  b += texture2D(tex, uv + (off3 / resolution)) * 0.010381362401148057;
  b += texture2D(tex, uv - (off3 / resolution)) * 0.010381362401148057;
  
  return b;
}

void main()
{
    color = 0.35*blur(last,  vec2(1,0))
          + 0.35*blur(last,  vec2(0,1))
          + 0.15*blur(last,  vec2(2,0))
          + 0.15*blur(last,  vec2(0,2));
}
