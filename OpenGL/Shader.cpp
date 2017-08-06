#include "stdafx.h"
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Shader::Shader(const std::string & vertPath, const std::string & fragPath)
{
	GLuint vertShader, fragShader;

	vertShader = _createShader(GL_VERTEX_SHADER, vertPath);
	fragShader = _createShader(GL_FRAGMENT_SHADER, fragPath);

	_program = glCreateProgram();
	glAttachShader(_program, vertShader);
	glAttachShader(_program, fragShader);
	glLinkProgram(_program);

	GLint error;
	glGetProgramiv(_program, GL_LINK_STATUS, &error);
	if (0 != error)
	{
		GLchar info[512];
		glGetProgramInfoLog(_program, 512, nullptr, info);
		cout << info << endl;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

Shader::~Shader()
{
}

void Shader::use()
{
	glUseProgram(_program);
}

GLuint Shader::_createShader(GLenum type, const string &filePath)
{
	ifstream shaderFile ;
	stringstream shaderStringstream;
	string shaderString;
	GLuint shader;
	GLint error;
	const GLchar * shaderSourcePtr = nullptr;

	shader = glCreateShader(type);

	shaderFile.open(filePath, ios::in);
	shaderStringstream << shaderFile.rdbuf();
	shaderString = shaderStringstream.str();
	shaderSourcePtr = shaderString.c_str();
	glShaderSource(shader, 1, &shaderSourcePtr, nullptr);

	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &error);
	if (0 != error)
	{
		GLchar info[512];
		
		glGetShaderInfoLog(shader, 512, nullptr, info);
		cout << info << endl;
	}

	return shader;
}

