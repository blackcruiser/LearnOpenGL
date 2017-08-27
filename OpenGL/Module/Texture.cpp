#include "stdafx.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <STB_IMAGE/stb_image.h>

using namespace std;


Texture::Texture() :
	_textureId(GL_NONE)
{
}


Texture::~Texture()
{
	_delete();
}

void Texture::loadFromFile(const string &path)
{
	int width, height, channel;

	unsigned char *data = stbi_load(path.c_str(), &width, &height, &channel, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);

	_delete();
	_textureId = texture;
}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, _textureId);
}

void Texture::_delete()
{
	if (GL_NONE != _textureId)
		glDeleteTextures(1, &_textureId);
}