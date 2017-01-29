in vec2 textureCoord;
uniform sampler2D fontTexture;

void main () 
{
	vec4 color = texture2D(fontTexture, textureCoord.xy);
	if ((color.x + color.y + color.z) == 3)
	{
		gl_FragColor = color;
	}
	else
	{
		discard;
	}
}