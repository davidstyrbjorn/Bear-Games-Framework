#include"../include/graphics/shader.h"

#include"../include/graphics/graphics.h"

#include"../include/core/matrix4x4.h"
#include"../include/core/vector2.h"
#include"../include/core/color.h"
#include"../include/core/file_utility.h"

#include<iostream>
#include<fstream>

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

void bear::graphics::Shader::setSource(const std::string& a_VertexSource, const std::string& a_FragmentSource)
{
	m_VertexSource = a_VertexSource;
	m_FragmentSource = a_FragmentSource;
}

void bear::graphics::Shader::setGeometrySourcePath(std::string a_GeometryPath)
{
	std::ifstream geometryFile(a_GeometryPath);
	if (!geometryFile.is_open()) {
		std::cout << "Could not load geometry-shader file at given path: " << a_GeometryPath << "\n";
	}
	else {
		m_GeometryFlag = true; // We've got a geometry shader file loaded!
	}

	std::string line;
	// Get content from file
	while (std::getline(geometryFile, line)) {
		m_GeometrySource += line + "\n";
	}
}

void bear::graphics::Shader::setGeometrySource(const std::string& a_GeometrySource) 
{
	m_GeometrySource = a_GeometrySource;
	m_GeometryFlag = true; // We've got a geometry shader source to compile!
}

void bear::graphics::Shader::setSourceFromFile(std::string a_VertexPath, std::string a_FragmentPath)
{
	std::ifstream vertexFile(a_VertexPath);
	std::ifstream fragmentFile(a_FragmentPath);
	if (!vertexFile.is_open() || !fragmentFile.is_open()) {
		std::cout << "Could not load shader files at given paths:\n" << a_VertexPath << "\n" << a_FragmentPath;
	}

	std::string line;
	// Get vertex file content
	while (std::getline(vertexFile, line)) {
		m_VertexSource += line + "\n";
	}

	line.clear();	 

	// Get fragment file content
	while (std::getline(fragmentFile, line)) {
		m_FragmentSource += line + "\n";
	}

	line.clear();
}

void bear::graphics::Shader::compile()
{
	const char* vertexSource = m_VertexSource.c_str();
	const char* fragmentSource = m_FragmentSource.c_str();

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

	/* Geometry */
	// Check if we're supplying a geometry shader to the program
	GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	if (m_GeometryFlag) {
		const char* geometrySource = m_GeometrySource.c_str();
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometrySource, 0);
		glCompileShader(geometryShader);
		std::string geometryCompileLog = "";
		if (!didCompile(geometryShader, geometryCompileLog)) {
			std::cout << "GEOMETRY SHADER COMPILE ERROR\n" << geometryCompileLog << "\n";
		}
	}
	
	/* Shader Program */
	m_Program = glCreateProgram();
	/* Linking process */
	glAttachShader(m_Program, vertexShader);
	if (m_GeometryFlag)
		glAttachShader(m_Program, geometryShader);
	glAttachShader(m_Program, fragmentShader);

	glLinkProgram(m_Program);

	glDetachShader(m_Program, vertexShader);
	if (m_GeometryFlag)
		glDetachShader(m_Program, geometryShader);
	glDetachShader(m_Program, fragmentShader);

	glDeleteShader(vertexShader);
	if (m_GeometryFlag)
		glDeleteShader(geometryShader);
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

void bear::graphics::Shader::setUniformVector2f(const char * a_UniformName, core::Vector2<float>& a_Vector)
{
	glUniform2f(getUniformLocation(a_UniformName), a_Vector.x, a_Vector.y);
}

void bear::graphics::Shader::setUniformColor3f(const char * a_UniformName, core::Color & a_Color)
{
	glUniform3f(getUniformLocation(a_UniformName), a_Color.r, a_Color.g, a_Color.b);
}

void bear::graphics::Shader::setUniformMatrix4x4(const char * a_UniformName, core::Matrix4x4 & a_Matrix)
{
	glUniformMatrix4fv(getUniformLocation(a_UniformName), 1, false, a_Matrix.elements);
}

void bear::graphics::Shader::setUniformInteger(const char * a_UniformName, int a_Integer)
{
	glUniform1i(getUniformLocation(a_UniformName), a_Integer);
}

void bear::graphics::Shader::setUniformIntegerArray(const char * a_UniformName, unsigned int a_Count, int * a_Integers)
{
	glUniform1iv(getUniformLocation(a_UniformName), a_Count, a_Integers);
}

void bear::graphics::Shader::setUniformVector4f(const char * a_UniformName, core::Color& a_Vector)
{
	glUniform4f(getUniformLocation(a_UniformName), a_Vector.r, a_Vector.g, a_Vector.b, a_Vector.a);
}

void bear::graphics::Shader::setUniformFloat(const char * a_UniformName, float a_Float)
{
	glUniform1f(getUniformLocation(a_UniformName), a_Float);
}

bool bear::graphics::Shader::didCompile(unsigned int a_ShaderID, std::string & a_ErrMsg)
{
	GLint _didCompile;
	glGetShaderiv(a_ShaderID, GL_COMPILE_STATUS, &_didCompile);
	if (_didCompile == GL_FALSE)
	{
		GLint _maxLength = 0;
		glGetShaderiv(a_ShaderID, GL_INFO_LOG_LENGTH, &_maxLength);
		
		GLchar infoLog[1000];
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
