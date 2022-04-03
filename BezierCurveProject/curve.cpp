#include "curve.h"


glm::vec3 Curve::bezierCurveCompute(float t, int start, int stop)
{
    if (start == stop) return _controlPoints[start];
    glm::vec3 left = bezierCurveCompute(t, start, stop - 1);
    glm::vec3 right = bezierCurveCompute(t, start + 1, stop);
    return ((1 - t) * left) + (t * right);
}

Curve::Curve(vector < glm::vec3> controlPoints, int nbPoints)
{
	this->_controlPoints = controlPoints;
	this->_nbPoints = nbPoints;

	vector<Vertex> bezierVertices;

	/*AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	std::cout << _nbPoints;*/

	float step = 0.1 / (float)this->_nbPoints;
	//::cout << "STEP= " << step << std::endl;
	for (float t = 0; t < 1.0f; t += step)
	{
		//std::cout << t << std::endl;
		struct Vertex v;
		v.pos = bezierCurveCompute(t, 0, _nbPoints-1);
		bezierVertices.push_back(v);
	}

	/*for (int i = 0; i < bezierVertices.size(); i++)
	{
		std::cout << "Point" << i << ":" << bezierVertices.at(i).pos.x << "," << bezierVertices.at(i).pos.y << "," << bezierVertices.at(i).pos.z << std::endl;
	}*/

	this->_curveMesh = new Mesh(&bezierVertices, bezierVertices.size());

}

Curve::~Curve()
{

}
