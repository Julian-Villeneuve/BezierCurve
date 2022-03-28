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
