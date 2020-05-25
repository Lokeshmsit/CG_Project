// Vertex shader
#version 150
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texture;

out vec2 texture_corrdinate;
out vec3 n_model;

out vec3 V;
out vec3 N;
out vec3 L;
out vec3 H;

uniform mat4 u_mvp;
uniform mat4 u_mv;
uniform vec3 u_light_position;
//uniform int u_cubemap;

void main()
{
    n_model = a_normal;
     // Transform the vertex position to view space (eye coordinates)
    V = vec3(u_mv * a_position);

    // Calculate the view-space normal
    N = normalize(mat3(u_mv) * a_normal);

    // Calculate the view-space light direction
    L = normalize(u_light_position - V);

    //half way vector
    H = normalize(L + V); //light direction + view direction
    
    texture_corrdinate.y = 1-a_texture.y;
    texture_corrdinate.x = a_texture.x;
   
    gl_Position = u_mvp * a_position;

}
