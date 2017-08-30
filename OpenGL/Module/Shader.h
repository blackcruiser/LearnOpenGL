#pragma once

#include "GLAD/glad.h"

#include <glm/include/glm/glm.hpp>

#include <string>
#include <map>

enum class ShaderType : int
{
    VertexShader,
    FragmentShader,
    GeometryShader,
};

class Shader
{
public:
    Shader();
    ~Shader();

    void loadFromFile(ShaderType type, const std::string &filePath);
    void loadFromString(ShaderType type, const std::string &source);

    void compileAndLink();
    void use();

	void setMat4(const std::string &name, const glm::mat4 &value);

private:
    static std::map<ShaderType, GLenum> _shaderTypeMap;
    std::map<ShaderType, GLuint> _shaderMap;

    GLuint  _program;
};

