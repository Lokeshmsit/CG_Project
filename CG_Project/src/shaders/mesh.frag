// Fragment shader
#version 150

in vec3 N;
in vec3 L;
in vec3 H;
in vec3 V;
in vec2 tex_coord;
in vec3 n_model;

out vec4 frag_color;
uniform vec3 u_light_color;
uniform vec3 u_ambient_color;
uniform vec3 u_specular_color;
uniform float u_specular_power;
uniform mat4 u_mv;


uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

//normalization after interpolation
vec3 N_normalized = normalize(N);
vec3 L_normalized = normalize(L);
vec3 H_normalized = normalize(H);

vec3 R = reflect(-V, N);


mat3 tangent_space(vec3 eye, vec2 tex_coord, vec3 normal)
{
// Computing pixel derivatives
vec3 delta_pos1 = dFdx(eye);
vec3 delta_pos2 = dFdy(eye);
vec2 delta_uv1 = dFdx(tex_coord);
vec2 delta_uv2 = dFdy(tex_coord);

// Computing tangent space vectors
vec3 N = normal;
vec3 T = normalize(delta_pos1 * delta_uv2.y - delta_pos2 * delta_uv1.y);
vec3 B = normalize(delta_pos2 * delta_uv1.x - delta_pos1 * delta_uv2.x);
return mat3(T, B, N);
}



void main()
{

   vec3 normalmap = texture(tex2, tex_coord).rgb;
    normalmap = normalmap * 2.0 - 1.0;
   
   mat3 TBN = tangent_space(V, tex_coord, normalmap);
   N_normalized = normalize(TBN * normalmap);

   vec4 specular_color_tex =  texture(tex1, tex_coord);

   float spec_power = specular_color_tex.r*100+1;
   float lambertian = max(dot(L_normalized, N_normalized), 0.0);

   float normalization = (8.0 + spec_power) / 8.0;

   vec3 diff_color_tex =  texture(tex0, tex_coord).rgb;

   float gloss = 1.0 - diff_color_tex.r; 
   float specular_power = exp2(gloss * 10.0);

   vec3 Ia = u_ambient_color; 
   vec3 Id = diff_color_tex * u_light_color * lambertian;
   vec3 Is = u_specular_color * u_light_color
             *  normalization * pow(max(0.0,dot(N_normalized, -H_normalized)), spec_power);
       
   vec3 output_color = Ia + Id + Is;

   frag_color = vec4(output_color, 1.0);

}
