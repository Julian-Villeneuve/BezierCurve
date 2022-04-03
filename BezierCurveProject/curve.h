#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>
#include "points.h"
#include "mesh.h"


class Curve
{
public:
	Curve(vector < glm::vec3> controlPoints, int nbPoints);
	~Curve();

	glm::vec3 Curve::bezierCurveCompute(float t, int start, int stop);

	Mesh* _curveMesh;
protected:
private:
	vector<glm::vec3> _controlPoints;
	int _nbPoints;
};

