// Vertex shader
#version 150
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texture;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_Bitangent;


out vec2 tex_corrd;
out vec3 n_model;

out vec3 V;
out vec3 N;
out vec3 L;
out vec3 H;

uniform mat4 u_m;
uniform mat4 u_mvp;
uniform mat4 u_mv;
uniform vec3 u_light_position;
//uniform int u_cubemap;
out mat3 TBN;

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
    
    tex_corrd.y = 1-a_texture.y;
    tex_corrd.x = a_texture.x;
   
    gl_Position = u_mvp * a_position;

    vec3 T = normalize(vec3(u_mv * vec4(a_Tangent,   0.0)));
    vec3 B = normalize(vec3(u_mv * vec4(a_Bitangent, 0.0)));
    vec3 N = normalize(vec3(u_mv * vec4(a_normal,    0.0)));
    TBN = mat3(T, B, N);

}
