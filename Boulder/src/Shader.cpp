#include "Shader.h"
#include "GLCall.h"

#include <string>
#include <vector>
#include <iostream>

Shader::Shader()
{
	std::string vertStr =
		"#version 330 core\n"
		"layout(location = 0) in vec2 position;\n"
		//"layout(location = 1) in vec2 texCoord;\n"
		"out vec2 v_TexCoord;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(position, 0.0, 1.0);\n"
		//"	v_TexCoord = texCoord;\n"
		"};";

	std::string fragStr = 
		"#version 330 core\n"
		"//default layout location is 0\n"
		"out vec4 color;\n"
		//"in vec2 v_TexCoord;\n"
		"//uniform vec4 u_Color;\n"
		"//uniform sampler2D u_Texture;\n"
		"void main()\n"
		"{\n"
		//"	vec4 texColor = texture(u_Texture, v_TexCoord);\n"
		//"	color = texColor;\n"
		"	color = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"};";

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertStrPrt = vertStr.c_str();
	GLCall(glShaderSource(VertexShaderID, 1, &vertStrPrt, nullptr));
	GLCall(glCompileShader(VertexShaderID));
	//Error handling
	int vertexResult;
	GLCall(glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &vertexResult));
	if (vertexResult == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &length));//returns number of characters in info log
		char* message = (char*)alloca(length * sizeof(char));//alloca() is used to dynamiclly create on the stack instead of heap
		GLCall(glGetShaderInfoLog(VertexShaderID, length, &length, message));//Returns the information log for a shader object
		std::cout << "Failed to compile vertex shader" << std::endl;
		std::cout << message << std::endl;
	}

	char const* fragStrPrt = fragStr.c_str();
	GLCall(glShaderSource(FragmentShaderID, 1, &fragStrPrt, nullptr));
	GLCall(glCompileShader(FragmentShaderID));
	//Error handling
	int fragmentResult;
	GLCall(glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &fragmentResult));
	if (fragmentResult == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &length));//returns number of characters in info log
		char* message = (char*)alloca(length * sizeof(char));//alloca() is used to dynamiclly create on the stack instead of heap
		GLCall(glGetShaderInfoLog(FragmentShaderID, length, &length, message));//Returns the information log for a shader object
		std::cout << "Failed to compile fragment shader" << std::endl;
		std::cout << message << std::endl;
	}

	GLuint ProgramID = glCreateProgram();
	GLCall(glAttachShader(ProgramID, VertexShaderID));
	GLCall(glAttachShader(ProgramID, FragmentShaderID));
	GLCall(glLinkProgram(ProgramID));
	GLCall(glValidateProgram(ProgramID));

	boulder_programID = ProgramID;

	GLCall(glDeleteShader(VertexShaderID));
	GLCall(glDeleteShader(FragmentShaderID));
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(boulder_programID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(boulder_programID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}
