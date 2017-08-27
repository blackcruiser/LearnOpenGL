#pragma once

#include "GLAD/glad.h"

#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	void loadFromFile(const std::string &path);

	void use();

private:
	void _delete();

private:
	GLuint _textureId;
};

