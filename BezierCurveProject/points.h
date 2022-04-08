#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>
#include "shader.h"

using namespace std;


class Points : public QOpenGLFunctions_4_4_Core
{
public:
	Points();

	~Points();

	void Add(glm::vec3 position);

	void Delete();

	void Draw(Shader* shader);

private:
	void Update_GPU_Buffer();

	vector<glm::vec3> _pointsList;

	unsigned int _VAOpoints;
	unsigned int _VBOpoints;
};