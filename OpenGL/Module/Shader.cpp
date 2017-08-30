#include "stdafx.h"
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

std::map<ShaderType, GLenum> Shader::_shaderTypeMap = {
    {ShaderType::VertexShader, GL_VERTEX_SHADER},
    {ShaderType::FragmentShader, GL_FRAGMENT_SHADER},
    {ShaderType::GeometryShader, GL_GEOMETRY_SHADER}
};


Shader::Shader() :
    _program(GL_NONE)
{
}

Shader::~Shader()
{
    for (auto iter = _shaderMap.begin(); iter != _shaderMap.end(); iter++)
        glDeleteShader(iter->second);

    if (GL_NONE != _program)
        glDeleteProgram(_program);
}

void Shader::loadFromFile(ShaderType type, const std::string &filePath)
{
    ifstream shaderFile;
    stringstream shaderStringstream;
    string shaderString;

    shaderFile.open(filePath, ios::in);
    shaderStringstream << shaderFile.rdbuf();
    shaderString = shaderStringstream.str();

    loadFromString(type, shaderString);
}

void Shader::loadFromString(ShaderType type, const string &source)
{
    GLuint shader;
    GLint error;
    const GLchar* shaderSourcePtr = nullptr;


    GLenum glShaderType = _shaderTypeMap[type];
    shader = glCreateShader(glShaderType);

    shaderSourcePtr = source.c_str();
    glShaderSource(shader, 1, &shaderSourcePtr, nullptr);

    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &error);
    if (GL_FALSE == error)
    {
        GLchar info[512];

        glGetShaderInfoLog(shader, 512, nullptr, info);
        cout << info << endl;

        glDeleteShader(shader);
        return;
    }

    if (_shaderMap.end() != _shaderMap.find(type))
        _shaderMap.erase(type);

    _shaderMap.insert(make_pair(type, shader));
}

void Shader::compileAndLink()
{
    if (GL_NONE != _program)
        glDeleteProgram(_program);

    _program = glCreateProgram();

    for (auto iter = _shaderMap.begin(); iter != _shaderMap.end(); iter++)
        glAttachShader(_program, iter->second);

    glLinkProgram(_program);

    GLint error;
    glGetProgramiv(_program, GL_LINK_STATUS, &error);
    if (GL_FALSE == error)
    {
        GLchar info[512];
        glGetProgramInfoLog(_program, 512, nullptr, info);
        cout << info << endl;

        glDeleteProgram(_program);
        return;
    }

    for (auto iter = _shaderMap.begin(); iter != _shaderMap.end(); iter++)
        glDeleteShader(iter->second);
    _shaderMap.clear();
}

void Shader::use()
{
    glUseProgram(_program);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value)
{
	GLuint location = glGetUniformLocation(_program, name.c_str());
	glUniformMatrix4fv(location, 1, false, &value[0][0]);
}
