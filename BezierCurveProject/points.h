#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>

using namespace std;


class Points : public QOpenGLFunctions_4_4_Core
{
public:
	Points();

	~Points();

	void Add(glm::vec2 position);

	void Delete();

	void Draw();

private:
	void Update_GPU_Buffer();

	vector<glm::vec2> _pointsList;

	unsigned int _VAOpoints;
	unsigned int _VBOpoints;
};