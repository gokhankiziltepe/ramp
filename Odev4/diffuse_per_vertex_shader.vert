#version 120

uniform mat4 MVP,ModelView;
uniform float fresnelReflectance;
uniform float fresnelPower;

attribute vec4 Position;
attribute vec3 Normal;

varying float fresnel;
void main()
{	
    vec3 vVertex = vec3(ModelView * Position);
    
    vec3 N = mat3(ModelView) * Normal;
	vec3 L = normalize(vec3(gl_LightSource[0].position.xyz - vVertex));
    
    float cosValue = dot(N, L) / (length(N) / length(L));
    
    fresnel = fresnelReflectance + (1 - fresnelReflectance) * pow(1+ dot(N,L) / (length(N)*length(L)), fresnelPower);
    gl_Position = MVP * Position;
}
	
