#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>

class Shader : public QOpenGLFunctions_4_4_Core
{
public:
	Shader(const std::string& filename);

	void Bind();

	void Shader::Unbind();

	void setInt(const std::string& name, int value);
	void setBool(const std::string& name, bool value);
	void setFloat(const std::string& name, float value);
	void setVec2(const std::string& name, const glm::vec2& value);
	void setVec2(const std::string& name, float x, float y);
	void setVec3(const std::string& name, const glm::vec3& value);
	void setVec3(const std::string& name, float x, float y, float z);
	void setVec4(const std::string& name, const glm::vec4& value);
	void setVec4(const std::string& name, float x, float y, float z, float w);
	void setMat2(const std::string& name, const glm::mat2& mat);
	void setMat3(const std::string& name, const glm::mat3& mat);
	void setMat4(const std::string& name, const glm::mat4& mat);

	virtual ~Shader();

	GLuint _program;
protected:
private:
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}
	static const unsigned int NUM_SHADERS = 2;

	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	std::string LoadShader(const std::string& filename);
	GLuint CreateShader(const std::string& text, GLenum shaderType);

	
	GLuint _shaders[NUM_SHADERS];
};

#endif // SHADER_H