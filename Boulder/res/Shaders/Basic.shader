#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_m;
uniform mat4 u_v;
uniform mat4 u_p;

void main()
{
	gl_Position = (u_p * u_v * u_m) * vec4(position, 0.0, 1.0);
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

//default layout location is 0
out vec4 color;

in vec2 v_TexCoord;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
};