#version 430 core

uniform sampler2D base;
uniform sampler2D redux;
uniform sampler2D normal;
uniform sampler2D position;
uniform sampler2D last;

uniform vec3  lights_position[3];
uniform vec3  lights_color[3];
uniform float lights_constantAttenuation[3];
uniform float lights_linearAttenuation[3];
uniform float lights_quadraticAttenuation[3];
uniform vec3 camera;

/*
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 ambient;
uniform float shininess;
*/
in vec2 uv;

const int max_lights = 3;
out vec4 color;

vec3 readPosition(in vec2 uv)
{
    vec3 N = texture2D(position, uv).rgb;
    return N;
}

vec3 readNormals(in vec2 uv)
{
    vec3 N   = texture2D(normal, uv).rgb;
         N.z = sqrt(1.0 - N.x*N.x - N.y*N.y);
    return N;
}

vec4 calculateLights()
{
   vec3 finalColor = vec3(0.0);
   vec3 N = readNormals();
   vec3 P = readPosition();
   
   for (int i=0;i<max_lights;i++)
   {
      vec3 light_ambient, light_diffuse, light_specular;
      
      vec3 lightDir = normalize(lights_position[i] - P); 
      vec3 viewDir = normalize(camera - P); 
      vec3 reflectDir = reflect(-lightDir, N); 
      vec3 halfwayDir = normalize(lightDir + viewDir);   
      
      float diff = max(dot(lightDir, N), 0.0f); 
      float NdotHV = clamp(dot(viewDir, reflectDir), 0.0, 1.0); 
      
      light_ambient = 0.05 * ambient * lights_color[i]; 
      light_diffuse = diff * diffuse * lights_color[i]; 
      //light_specular = specular * pow(max(dot(normal, halfwayDir), 0.0), shininess);
      light_specular = specular * pow(max(NdotHV, 0.0), shininess); 
      
      float d = length(lights_position[i] - P);
      float att = 1.0/ (lights_constantAttenuation[i] 
                       +lights_linearAttenuation[i]*d 
                       +lights_quadraticAttenuation[i]*d*d);
      
      finalColor += (light_ambient + light_diffuse + light_specular) * att;
   }
   
   return vec4(finalColor, 1.0);
}

void main()
{
    color = texture2D(last, uv, 0) * calculateLights();
}