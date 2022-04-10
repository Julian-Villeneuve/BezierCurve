#include "curve.h"


Curve::Curve(vector <Vertex> controlPoints, int nbPoints)
{
	_controlPoints = controlPoints;
	_nbPoints = nbPoints;
}

Curve::~Curve()
{

}

glm::vec3 Curve::bezierCurveCompute(float t, int start, int stop)
{
    if (start == stop) return _controlPoints[start].pos;
    glm::vec3 left = bezierCurveCompute(t, start, stop - 1);
    glm::vec3 right = bezierCurveCompute(t, start + 1, stop);
    return ((1 - t) * left) + (t * right);
}

glm::vec3 Curve::bezierSurfaceCompute(float u, float v)
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

void Curve::getFullCurve()
{
	vector<Vertex> bezierVertices;

	float step = 0.01 / (float)_nbPoints;
	for (float t = 0; t < 1.0f; t += step)
	{
		struct Vertex v;
		v.pos = bezierCurveCompute(t, 0, _nbPoints - 1);
		bezierVertices.push_back(v);
	}
	_curveMesh = new Mesh(&bezierVertices, bezierVertices.size());
}
