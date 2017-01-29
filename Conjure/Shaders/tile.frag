in vec2 textureCoord;
uniform sampler2D tileTexture;

void main () 
{	
	vec4 color = texture2D(tileTexture, textureCoord.xy);
	if (color.w >0.9)
	{
		gl_FragColor = color;
	}
	else
	{
		discard;
	}
}