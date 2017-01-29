#version 450

in vec2 textureCoord;
uniform sampler2D bgTexture;

void main () 
{
	vec4 color = texture2D(bgTexture, textureCoord.xy);
	gl_FragColor = color;
}