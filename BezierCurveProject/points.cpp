#include "points.h"

Points::Points()
{
	initializeOpenGLFunctions();
	glGenVertexArrays(1, &_VAOpoints);
	glGenBuffers(1, &_VBOpoints);
	glPointSize(5);
}

Points::~Points()
{
	glDeleteVertexArrays(1, &_VAOpoints);
	glDeleteBuffers(1, &_VBOpoints);
}

void Points::Add(glm::vec3 position)
{
	_pointsList.push_back(position);
	Update_GPU_Buffer();
}

void Points::Delete()
{
	_pointsList.pop_back();
	Update_GPU_Buffer();
}

void Points::Draw(Shader* shader)
{
	shader->Bind();
	glColor3ub(0, 0, 0);
	glBindVertexArray(_VAOpoints);
	glBindBuffer(GL_ARRAY_BUFFER, _VBOpoints);
	glDrawArrays(GL_POINTS, 0, (int)_pointsList.size());
	shader->Unbind();
}

void Points::Update_GPU_Buffer()
{
	glBindVertexArray(_VAOpoints);
	glBindBuffer(GL_ARRAY_BUFFER, _VBOpoints);
	glBufferData(GL_ARRAY_BUFFER, _pointsList.size() * sizeof(glm::vec3), _pointsList.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}