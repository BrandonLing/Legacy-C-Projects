in vec2 textureCoord;
uniform sampler2D objTexture;

void main () 
{	
	vec4 color = texture2D(objTexture, textureCoord.xy);
	gl_FragColor = color;
	//if (color.w > 0.9)
	//	gl_FragColor = color;
	//else
	//	discard;
}