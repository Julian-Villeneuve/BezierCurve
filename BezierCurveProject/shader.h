#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>

class Shader : public QOpenGLFunctions_4_4_Core
{
public:
	Shader(const std::string& filename);

	void Bind();

	virtual ~Shader();
protected:
private:
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}
	static const unsigned int NUM_SHADERS = 2;

	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	std::string LoadShader(const std::string& filename);
	GLuint CreateShader(const std::string& text, GLenum shaderType);

	GLuint _program;
	GLuint _shaders[NUM_SHADERS];
};

#endif // SHADER_H