#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
	TexCoord = texCoord;
}

#shader fragment
#version 460 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, TexCoord);
}