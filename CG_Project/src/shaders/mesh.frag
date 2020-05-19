// Fragment shader
#version 150

in vec3 v_normal;
in vec3 N;
in vec3 L;
in vec3 H;
in vec3 V;

out vec4 frag_color;
uniform vec3 u_light_color;
uniform vec3 u_ambient_color;
uniform vec3 u_diffuse_color;
uniform vec3 u_specular_color;
uniform float u_specular_power;
uniform samplerCube u_cubemap;


//normalization after interpolation
vec3 N_normalized = normalize(N);
vec3 L_normalized = normalize(L);
vec3 H_normalized = normalize(H);

vec3 R = reflect(-V, N);

void main()
{

    float normalization = (8.0 + u_specular_power) / 8.0;
    
    float lambertian = max(dot(L_normalized, N_normalized), 0.0);
    vec3 Ia = u_ambient_color;
    vec3 Id = u_diffuse_color * u_light_color * lambertian;
    vec3 Is = u_specular_color * u_light_color
             *  normalization * pow(max(0.0,dot(N_normalized, H_normalized)), u_specular_power);
  
    vec3 output_color = Ia + Id + Is;

    output_color.rgb = pow(output_color, vec3(1.0 / 2.2)); //applying gamma correction
   
    //frag_color = vec4(output_color, 1.0);

    vec3 color = texture(u_cubemap, R).rgb; //texture lookup

    frag_color = vec4(color, 1.0);
   
    

    //vec3 N = normalize(v_normal);
    //frag_color = vec4(0.5 * N + 0.5, 1.0);
}
