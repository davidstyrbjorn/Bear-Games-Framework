#include"../include/graphics/shader.h"

#include<core\file_utility.h>
#include<iostream>

#define GLEW_STATIC
#include<GL\glew.h>

bear::graphics::Shader::Shader(std::string a_VertexPath, std::string a_FragmentPath)
{
	// Get shader sources
	const char* vertexSource = core::get_file_content(a_VertexPath).c_str();
	const char* fragmentSource = core::get_file_content(a_FragmentPath).c_str();

	/* Vertex */
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, 0);
	glCompileShader(vertexShader);
	std::string vertexCompileLog = "";
	if (!didCompile(vertexShader, vertexCompileLog)) {
		std::cout << "VERTEX SHADER COMPILE ERROR\n" << vertexCompileLog << "\n";
	}

	/* Fragment */
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, 0);
	glCompileShader(fragmentShader);
	std::string fragmentCompileLog = "";
	if (!didCompile(fragmentShader, fragmentCompileLog)) {
		std::cout << "FRAGMENT SHADER COMPILE ERROR\n" << fragmentCompileLog << "\n";
	}

	/* Shader Program */
	m_Program = glCreateProgram();
	/* Linking process */
	glAttachShader(m_Program, vertexShader);
	glAttachShader(m_Program, fragmentShader);
	glLinkProgram(m_Program);
	glDetachShader(m_Program, vertexShader);
	glDetachShader(m_Program, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void bear::graphics::Shader::enable() const
{
	glUseProgram(m_Program);
}

void bear::graphics::Shader::disable() const
{
	glUseProgram(0);
}

bool bear::graphics::Shader::didCompile(unsigned int a_ShaderID, std::string & a_ErrMsg)
{
	GLint _didCompile;
	glGetShaderiv(a_ShaderID, GL_COMPILE_STATUS, &_didCompile);
	if (_didCompile == GL_FALSE)
	{
		GLint _maxLength = 0;
		glGetShaderiv(a_ShaderID, GL_INFO_LOG_LENGTH, &_maxLength);
		
		GLchar infoLog[200];
		glGetShaderInfoLog(a_ShaderID, _maxLength, &_maxLength, &infoLog[0]);
		a_ErrMsg = infoLog;

		return false;
	}

	return true;
}
