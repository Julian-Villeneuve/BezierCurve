#include "openglwidget.h"

int windowWidth = 500, windowHeight = 500;


OpenGLWidget::OpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	_width = windowWidth;
	_height = windowHeight;
}

OpenGLWidget::~OpenGLWidget()
{
}

void OpenGLWidget::initializeGL()
{
	if (!initializeOpenGLFunctions()) {
		QMessageBox::critical(this, "OpenGL initialization error", "MyOpenGLWidget::initializeGL() : Unable to initialize OpenGL functions");
		exit(1);
	}

	_shaderPoly = new Shader("basicShader");
	_shaderCurve = new Shader("curveShader");
	glColor3f(0.0, 0.0, 0.0);

	// add or modify points here
	glm::vec3 point1 = glm::vec3(0.5, -0.5, 0.0);
	glm::vec3 point2 = glm::vec3(0.5, 0.5, 0.0);
	glm::vec3 point3 = glm::vec3(-0.5, 0.5, 0.0);
	glm::vec3 point4 = glm::vec3(-0.5, -0.5, 0.0);
	glm::vec3 point5 = glm::vec3(0.0, 0.0, 0.0);
	//glm::vec3 point6 = glm::vec3(0.75, -0.75, 0.0);

	// add all points as Point class to draw them
	// ------------------------------------------
	_points = new Points();
	_points->Add(point1);
	_points->Add(point2);
	_points->Add(point3);
	_points->Add(point4);
	_points->Add(point5);
	//_points->Add(point6);
	
	// add all points in a vector to compute and draw Bezier Curve then draw separately the control polygon
	// ----------------------------------------------------------------------------------------------------
	struct Vertex v1, v2, v3, v4, v5;
	v1.pos = point1;
	v2.pos = point2;
	v3.pos = point3;
	v4.pos = point4;
	v5.pos = point5;
	_controlVertices.push_back(v1);
	_controlVertices.push_back(v2);
	_controlVertices.push_back(v3);
	_controlVertices.push_back(v4);
	_controlVertices.push_back(v5);

	// the 3 parts above have to add the points in the same order

	_controlPolygon = new Mesh(&_controlVertices, _controlVertices.size());
	_curve = new Curve(_controlVertices, _controlVertices.size());
	_curve->getFullCurve();


	// to test the setupMesh() method that doesn't work
	/*struct Vertex v6;
	v6.pos = point6;
	_controlVertices.push_back(v6);
	_curve->_curveMesh->setupMesh();*/

}

void OpenGLWidget::paintGL()
{
	glClearColor(1.0f, .95f, .75f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	_points->Draw(_shaderCurve);
	_curve->_curveMesh->DrawPolygon(_shaderCurve);
	_controlPolygon->DrawPolygon(_shaderPoly);
	glFinish();
}

void OpenGLWidget::resizeGL(int width, int height)
{
	_width = width;
	_height = height;
	glViewport(0, 0, _width, _height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		_xAtPress = (event->localPos().x()) / _width * 2 - 1;
		_yAtPress = -((event->localPos().y()) / _height * 2 - 1);
		_points->Add(glm::vec3(_xAtPress, _yAtPress, 0.0));

		struct Vertex v;
		v.pos = glm::vec3(_xAtPress, _yAtPress, 0);
		_controlVertices.push_back(v);
		_nbPoint++;
		/*struct Vertex vPrev;
		vPrev.pos = glm::vec3(_prevX, _prevY, 0);*/

		//_curve->_curveMesh->setupMesh();

		_prevX = _xAtPress;
		_prevY = _yAtPress;
		update();
	}
}

