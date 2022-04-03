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

	/*// mesh class tests
	struct Vertex v1,v2,v3;
	v1.pos = glm::vec3(-0.5, -0.5, 0);
	v2.pos = glm::vec3(0, 0.5, 0);
	v3.pos = glm::vec3(0.5, -0.5, 0);
	vector<Vertex> vertices;
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	_mesh = new Mesh(&vertices, vertices.size());*/

	_shader = new Shader("basicShader");
	glColor3f(0.0, 0.0, 0.0);

	// add all points as Point class to draw them
	// ------------------------------------------
	_points = new Points();
	_points->Add(glm::vec2(0.5, -0.5));
	_points->Add(glm::vec2(0.5, 0.5));
	_points->Add(glm::vec2(-0.5, 0.5));
	_points->Add(glm::vec2(-0.5, -0.5));
	_points->Add(glm::vec2(0, 0));

	// add all points in a vector to compute and draw Bezier Curve
	// -----------------------------------------------------------
	_pointsListCurve.push_back(glm::vec3(0.5, -0.5, 0));
	_pointsListCurve.push_back(glm::vec3(0.5, 0.5, 0));
	_pointsListCurve.push_back(glm::vec3(-0.5, 0.5, 0));
	_pointsListCurve.push_back(glm::vec3(-0.5, -0.5, 0));
	_pointsListCurve.push_back(glm::vec3(0, 0, 0));
	
	// create vertices of these points to draw separately the control polygon
	// ----------------------------------------------------------------------
	struct Vertex v1, v2, v3, v4, v5;
	v1.pos = glm::vec3(0.5, -0.5, 0);
	v2.pos = glm::vec3(0.5, 0.5, 0);
	v3.pos = glm::vec3(-0.5, 0.5, 0);
	v4.pos = glm::vec3(-0.5, -0.5, 0);
	v5.pos = glm::vec3(0, 0, 0);
	controlVertices.push_back(v1);
	controlVertices.push_back(v2);
	controlVertices.push_back(v3);
	controlVertices.push_back(v4);
	controlVertices.push_back(v5);

	// the 3 parts above have to add the points in the same order

	_controlPolygon = new Mesh(&controlVertices, controlVertices.size());
	_curve = new Curve(_pointsListCurve, _pointsListCurve.size());
}

void OpenGLWidget::paintGL()
{
	glClearColor(1.0f, .95f, .75f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//_shader->Bind();
	_points->Draw();
	_curve->_curveMesh->Draw();
	_controlPolygon->DrawControl();
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
		_points->Add(glm::vec2(_xAtPress, _yAtPress));
		_pointsListCurve.push_back(glm::vec3(_xAtPress, _yAtPress, 0));
		struct Vertex v;
		v.pos = glm::vec3(_xAtPress, _yAtPress, 0);
		controlVertices.push_back(v);
		_nbPoint++;
		//_controlPolygon->~Mesh();
		//_controlPolygon = new Mesh(&controlVertices, controlVertices.size());
		//_curve = new Curve(_pointsList, _nbPoint);
		//_curve->_curveMesh->Draw();
		update();
	}
}


//void OpenGLWidget::keyPressEvent(QKeyEvent* event)
//{
//	if (event->key() == Qt::Key_S)
//	{
//		AllocConsole();
//		freopen("CONOUT$", "w", stdout);
//		freopen("CONOUT$", "w", stderr);
//		std::cout << " S KEY IS PRESSED ";
//		if(!_controlPolygon->_destroyed)
//			_controlPolygon->~Mesh();
//		_controlPolygon->DrawControl();
//		update();
//	}
//}