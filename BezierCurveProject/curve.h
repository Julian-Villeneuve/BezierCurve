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
	Curve(vector <Vertex> controlPoints, int nbPoints);
	~Curve();

	glm::vec3 Curve::bezierCurveCompute(float t, int start, int stop);

	glm::vec3 Curve::bezierSurfaceCompute(float u, float v);

	void Curve::getFullCurve();

	void Curve::getFullSurface();

	Mesh* _curveMesh;
	vector<Vertex> _controlPoints;
protected:
private:
	int _nbPoints;
};

