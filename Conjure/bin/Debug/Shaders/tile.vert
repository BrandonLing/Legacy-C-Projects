#version 450

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 texCoord;

uniform mat4 modelviewproj;
out vec2 textureCoord;

void main () 
{
	textureCoord = texCoord;
	gl_Position = modelviewproj * vec4(vertex_position, 1.0);
}