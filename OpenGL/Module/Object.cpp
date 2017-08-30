#include "stdafx.h"
#include "Object.h"

using namespace std;

Object::Object()
{
	_shader.loadFromFile(ShaderType::VertexShader, "Resource/vertShader.txt");
	_shader.loadFromFile(ShaderType::FragmentShader, "Resource/fragShader.txt");
	_shader.compileAndLink();

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
}

Object::~Object()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
}

void Object::setVertices(float* vertices, float* texCords, int count)
{
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float) * (3 + 2), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float) * 3, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, count * sizeof(float) * 3, count * sizeof(float) * 2, texCords);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 0, (void*)(count * sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Object::setTexture(const string &path)
{
	_texture.loadFromFile(path);
}

void Object::draw(const glm::mat4 &mvp)
{
	glBindVertexArray(_vao);

	_texture.use();
	_shader.use();
	_shader.setMat4("mvp", mvp);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}