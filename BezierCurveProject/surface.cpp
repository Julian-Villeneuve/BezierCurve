#include "surface.h"

Surface::Surface(vector <Vertex> controlPoints, int nbPoints)
{
	_controlPoints = controlPoints;
	_nbPoints = nbPoints;
}

Surface::~Surface()
{

}

glm::vec3 Surface::bezierCurveCompute(float t, int start, int stop)
{
    if (start == stop) return _controlPoints[start].pos;
    glm::vec3 left = bezierCurveCompute(t, start, stop - 1);
    glm::vec3 right = bezierCurveCompute(t, start + 1, stop);
    return ((1 - t) * left) + (t * right);
}

glm::vec3 Surface::bezierSurfaceCompute(float u, float v)
{
	vector<Vertex> allPoints = _controlPoints;
	vector<glm::vec3> pointsToAdd;
	vector<Vertex> superCurve;

	for (int i = 0; i < 4; ++i)
	{
		superCurve.clear();
		superCurve.push_back(allPoints[i * 4]);
		superCurve.push_back(allPoints[i * 4 + 1]);
		superCurve.push_back(allPoints[i * 4 + 2]);
		superCurve.push_back(allPoints[i * 4 + 3]);

		_controlPoints = superCurve;
		pointsToAdd.push_back(bezierCurveCompute(u, 0, superCurve.size() - 1));


	}
	_controlPoints.clear();
	for (int j = 0; j < pointsToAdd.size(); j++)
	{
		struct Vertex v;
		v.pos = pointsToAdd[j];
		_controlPoints.push_back(v);
	}

	glm::vec3 res = bezierCurveCompute(v, 0, pointsToAdd.size() - 1);
	_controlPoints = allPoints;
	return res;

}

void Surface::getFullSurface()
{
	vector<Vertex> bezierVertices;

	float step = 0.1 / (float)this->_nbPoints;
	for (float u = 0; u <= 1.0f; u += step)
	{
		for (float v = 0; v <= 1.0f; v += step)
		{
			struct Vertex vertex;
			vertex.pos = bezierSurfaceCompute(u, v);
			bezierVertices.push_back(vertex);
		}
	}

	vector<unsigned int> indices;
	for (int i = 1; i < bezierVertices.size(); i++)
	{
		for (int j = 0; j < (1.0/step) - 1; j++)
		{
			indices.push_back(i * (1.0 / step) + j);
			indices.push_back(i * ((1.0 / step) - 1) + j);
			indices.push_back(i * ((1.0 / step) - 1) + (j + 1));
		}
	}

	_surfaceMesh = new Mesh(&bezierVertices, indices);
}
