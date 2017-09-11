#pragma once

#include "GLAD/glad.h"

#include "Texture.h"
#include "Shader.h"

#include <string>

struct Vec4
{
public:
    Vec4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
    Vec4(float xx, float yy, float zz, float ww) : x(xx), y(yy), z(zz), w(ww) {};

public:
    float x, y, z, w;
};

class Object
{
public:
    Object();
    ~Object();

    void setVertices(float* vertices, float* texCords, int verticeCount, int *indexs, int indexCount);
    void setTexture(const std::string &path);

    virtual void draw(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix);

protected:
    Vec4 _position;

	int _indexCount;
	int *_indexs;
    Texture _texture;
    Shader _shader;
    GLuint _vao, _vbo, _veo;

private:
};