in vec2 textureCoord;
uniform sampler2D spriteTexture;

void main () 
{	
	vec4 color = texture2D(spriteTexture, textureCoord.xy);
	if (color.w > 0.9)
		gl_FragColor = color;
	else
		discard;
}