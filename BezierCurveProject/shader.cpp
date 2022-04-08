#include "shader.h"
#include <iostream>
#include <fstream>

//static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
//static std::string LoadShader(const std::string& filename);
//static GLuint CreateShader(const std::string& text, GLenum shaderType);

// shader constructor
// ------------------
Shader::Shader(const std::string& filename)
{
	initializeOpenGLFunctions();
	_program = glCreateProgram();
	_shaders[0] = CreateShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);
	_shaders[1] = CreateShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(_program, _shaders[i]);

	glBindAttribLocation(_program, 0, "position");

	glLinkProgram(_program);
	CheckShaderError(_program, GL_LINK_STATUS, true, "Error Program linking failed: ");
	glValidateProgram(_program);
	CheckShaderError(_program, GL_VALIDATE_STATUS, true, "Error Program is invalid: ");

}

// shader destructor
// -----------------
Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(_program, _shaders[i]);
		glDeleteShader(_shaders[i]);
	}
	glDeleteProgram(_program);
}

void Shader::Bind()
{
	glUseProgram(_program);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(_program, name.c_str()), value);
}

void Shader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(_program, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(_program, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, float x, float y)
{
	glUniform2f(glGetUniformLocation(_program, name.c_str()), x, y);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value)
{
	glUniform2fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(_program, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value)
{
	glUniform4fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(_program, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat)
{
	glUniformMatrix2fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat)
{
	glUniformMatrix3fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// shader creation method
// ----------------------
GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error: Shader creation failed!" << std::endl;

	// converting list into c_string
	// -----------------------------
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLenghts[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLenghts[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLenghts);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error shader compilation failed: ");

	return shader;
}

// shader loading method
// ---------------------
std::string Shader::LoadShader(const std::string& filename)
{
	std::ifstream file;
	file.open((filename).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << filename << std::endl;
	}
	return output;
}

// shader error method
// -------------------
void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
