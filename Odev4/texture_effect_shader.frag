#version 120

uniform sampler2D image;
uniform sampler2D ramp;

varying vec2 f_texcoord;
 
void main(void) 
{
	vec3 inColor = texture2D(image, f_texcoord).xyz;
	vec3 outColor;
	outColor.r = texture2D(ramp, vec2(inColor.r, 1)).r;
	outColor.g = texture2D(ramp, vec2(inColor.g, 1)).g;
	outColor.b = texture2D(ramp, vec2(inColor.b, 1)).b;
    gl_FragColor = vec4(outColor, 1.0);
}
