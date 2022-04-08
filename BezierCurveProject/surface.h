#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>
#include "points.h"
#include "mesh.h"


class Surface
{
public:
	Surface(vector <Vertex> controlPoints, int nbPoints);
	~Surface();

	glm::vec3 Surface::bezierCurveCompute(float t, int start, int stop);

	glm::vec3 Surface::bezierSurfaceCompute(float u, float v);

	void Surface::getFullSurface();

	Mesh* _surfaceMesh;
	vector<Vertex> _controlPoints;
protected:
private:
	int _nbPoints;
};

