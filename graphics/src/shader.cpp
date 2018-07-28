#include"../include/graphics/shader.h"

#include"../include/graphics/graphics.h"

#include<core\matrix4x4.h>
#include<core\file_utility.h>
#include<iostream>

#define GLEW_STATIC
#include<GL\glew.h>

using namespace bear::graphics;

bear::graphics::Shader::Shader()
{

}

bear::graphics::Shader::~Shader()
{
	glDeleteProgram(m_Program);
}

void bear::graphics::Shader::compile(std::string a_VertexPath, std::string a_FragmentPath, bool a_IsSource)
{
	// Get shader sources
	std::string _vertexSource = core::get_file_content(a_VertexPath);
	std::string _fragmentSource = core::get_file_content(a_FragmentPath);
	m_VertexSource = _vertexSource.c_str();
	m_FragmentSource = _fragmentSource.c_str();

	/* Vertex */
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &m_VertexSource, 0);
	glCompileShader(vertexShader);
	std::string vertexCompileLog = "";
	if (!didCompile(vertexShader, vertexCompileLog)) {
		std::cout << "VERTEX SHADER COMPILE ERROR\n" << vertexCompileLog << "\n";
	}

	/* Fragment */
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &m_FragmentSource, 0);
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

void bear::graphics::Shader::enable()
{
	glUseProgram(m_Program);
	m_IsActive = true;
}

void bear::graphics::Shader::disable()
{
	glUseProgram(0);
	m_IsActive = false;
}

const bool bear::graphics::Shader::isActive() const
{
	return m_IsActive;
}

void bear::graphics::Shader::setUniformMatrix4x4(const char * a_UniformName, core::Matrix4x4 & a_Matrix)
{
	glUniformMatrix4fv(getUniformLocation(a_UniformName), 1, false, a_Matrix.elements);
}

void bear::graphics::Shader::setUniformInteger(const char * a_UniformName, int a_Integer)
{
	glUniform1i(getUniformLocation(a_UniformName), a_Integer);
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

int bear::graphics::Shader::getUniformLocation(const char * a_UniformName)
{
	// Check if a_UniforName already exists inside m_UniformMap
	auto iterator = m_UniformMap.find(a_UniformName);
	if (iterator == m_UniformMap.end()) {
		// It does not exist inside m_UniformMap
		// so insert 
		m_UniformMap.insert(std::pair<const char*, int>(a_UniformName, glGetUniformLocation(m_Program, a_UniformName)));
	}
	
	return m_UniformMap.at(a_UniformName);
}
