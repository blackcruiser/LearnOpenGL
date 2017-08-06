#pragma once

#include "GLAD\glad.h"
#include <string>

class Shader
{
public:
	Shader(const std::string &vertPath, const std::string &fragPath);
	~Shader();

	void use();

private:
	GLuint _createShader(GLenum type, const std::string & filePath);

private:
	GLuint  _program;
};

