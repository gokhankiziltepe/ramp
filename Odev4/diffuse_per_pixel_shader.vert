#version 120

uniform mat4 MVP,ModelView;
uniform float fresnelReflectance;
uniform float fresnelPower;

attribute vec4 Position;
attribute vec3 Normal;

varying vec3 normal,pos;
varying float reflectance;
varying float power;

void main()
{	
	reflectance = fresnelReflectance;
	power = fresnelPower;
    vec3 vVertex = vec3(ModelView * Position);
    
    normal = mat3(ModelView) * Normal;
    pos = vVertex;

    gl_Position = MVP * Position;
}
