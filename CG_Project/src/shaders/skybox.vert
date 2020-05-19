// Skybox vertex shader
#version 150
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec3 a_position;

out vec3 TexCoords;

uniform mat4 u_p; 
uniform mat4 u_v;

void main()
{
    TexCoords = a_position;
    vec4 pos = u_p * u_v * vec4(a_position, 1.0f);
    gl_Position = pos.xyww;
    
}
