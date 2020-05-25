// Fragment shader
#version 150

in vec3 v_normal;
in vec3 N;
in vec3 L;
in vec3 H;
in vec3 V;
in vec2 texture_corrdinate;
in vec3 n_model;

out vec4 frag_color;
uniform vec3 u_light_color;
uniform vec3 u_ambient_color;
uniform vec3 u_diffuse_color;
uniform vec3 u_specular_color;
uniform float u_specular_power;
//uniform samplerCube u_cubemap;
uniform sampler2D tex0;
uniform sampler2D tex1;

//normalization after interpolation
vec3 N_normalized = normalize(N);
vec3 L_normalized = normalize(L);
vec3 H_normalized = normalize(H);

vec3 R = reflect(-V, N);

void main()
{

    float normalization = (8.0 + u_specular_power) / 8.0;
    
    vec4 specular_color_tex =  texture(tex1, texture_corrdinate);
    float  spec_power = specular_color_tex.r*100+1;
    float lambertian = max(dot(L_normalized, N_normalized), 0.0);

    vec3 diff_color_tex =  texture(tex0, texture_corrdinate).rgb;

    vec3 Ia = u_ambient_color;
    vec3 Id = diff_color_tex * u_light_color * lambertian;
    vec3 Is = u_specular_color * u_light_color
             *  normalization * pow(max(0.0,dot(N_normalized, -H_normalized)), spec_power);
       //Ia +
    vec3 output_color = Id + Is;

    //vec4 texture_color = texture(tex0, texture_corrdinate);
    //output_color =  texture_color.rgb;

    output_color.rgb = pow(output_color, vec3(1.0 / 2.2)); //applying gamma correction

    //frag_color = vec4(output_color, 1.0);

    //vec3 color = texture(u_cubemap, R).rgb; //texture lookup

    frag_color = vec4(output_color, 1.0);

    //vec3 N = normalize(v_normal);
    //frag_color = vec4(0.5 * N + 0.5, 1.0);
}
