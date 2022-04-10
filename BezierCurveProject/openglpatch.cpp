#include "openglpatch.h"

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

//float ORG[3] = { -0.75,-0.75,0 };
//
//float XP[3] = { -0.55,-0.75,0 }, XN[3] = { -0.95,-0.75,0 },
//YP[3] = { -0.75,-0.55,0 }, YN[3] = { -0.75,-0.95,0 },
//ZP[3] = { -0.75,0,0.2 }, ZN[3] = { -0.75,0,-0.2 };


OpenGLPatch::OpenGLPatch(QWidget *parent)
	: QOpenGLWidget(parent)
{
	//_myTimer.start();
}

OpenGLPatch::~OpenGLPatch()
{
}

void OpenGLPatch::initializeGL()
{
	if (!initializeOpenGLFunctions()) {
		QMessageBox::critical(this, "OpenGL initialization error", "MyOpenGLWidget::initializeGL() : Unable to initialize OpenGL functions");
		exit(1);
	}


	_shaderCam = new Shader("camera"); 

	_shaderPoints = new Shader("cameraPoints");

	_camera = new Camera(_width, _height, glm::vec3(0.0f, 0.0f, 0.0f));
	_view = _camera->getView();

	_projection = glm::perspective(glm::radians(_camera->getZoom()), float(_width) / _height, 0.1f, 100.0f);

	_model = glm::mat4(1.0);

	// add all points in a vector to compute and draw Bezier Surface
	// -------------------------------------------------------------
	glm::vec3 point1 = glm::vec3(-0.75, 0.75, getRandomZ()), point2 = glm::vec3(-0.25, 0.75, getRandomZ()), point3 = glm::vec3(0.25, 0.75, getRandomZ()), point4 = glm::vec3(0.75, 0.75, getRandomZ());
	glm::vec3 point5 = glm::vec3(-0.75, 0.25, getRandomZ()), point6 = glm::vec3(-0.25, 0.25, getRandomZ()), point7 = glm::vec3(0.25, 0.25, getRandomZ()), point8 = glm::vec3(0.75, 0.25, getRandomZ());
	glm::vec3 point9 = glm::vec3(-0.75, -0.25, getRandomZ()), point10 = glm::vec3(-0.25, -0.25, getRandomZ()), point11 = glm::vec3(0.25, -0.25, getRandomZ()), point12 = glm::vec3(0.75, -0.25, getRandomZ());
	glm::vec3 point13 = glm::vec3(-0.75, -0.75, getRandomZ()), point14 = glm::vec3(-0.25, -0.75, getRandomZ()), point15 = glm::vec3(0.25, -0.75, getRandomZ()), point16 = glm::vec3(0.75, -0.75, getRandomZ());

	struct Vertex v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16;
	v1.pos = point1; v2.pos = point2; v3.pos = point3; v4.pos = point4; v5.pos = point5; v6.pos = point6; v7.pos = point7; v8.pos = point8;
	v9.pos = point9; v10.pos = point10; v11.pos = point11; v12.pos = point12; v13.pos = point13; v14.pos = point14; v15.pos = point15; v16.pos = point16;
	_controlPoints.push_back(v1); _controlPoints.push_back(v2); _controlPoints.push_back(v3); _controlPoints.push_back(v4);
	_controlPoints.push_back(v5); _controlPoints.push_back(v6); _controlPoints.push_back(v7); _controlPoints.push_back(v8);
	_controlPoints.push_back(v9); _controlPoints.push_back(v10); _controlPoints.push_back(v11); _controlPoints.push_back(v12);
	_controlPoints.push_back(v13); _controlPoints.push_back(v14); _controlPoints.push_back(v15); _controlPoints.push_back(v16);
	

	// add all points as Point class to draw them
	// ------------------------------------------
	_points = new Points();
	for (int i = 0; i < _controlPoints.size(); i++)
	{
		_points->Add(_controlPoints[i].pos);
	}

	_surface = new Surface(_controlPoints, _controlPoints.size());
	_surface->getFullSurface();
	//_surface->_surfaceMesh->meshCompute();
	//_surface->_surfaceMesh->setupMesh();

	/*AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	std::cout << " OK ";*/
}

void OpenGLPatch::paintGL() 
{
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_shaderCam->Bind(); 
	_shaderCam->setMat4("view", _camera->getView());
	_shaderCam->setMat4("projection", _camera->getProjection());
	_shaderPoints->Bind();
	_shaderPoints->setMat4("view", _camera->getView());
	_shaderPoints->setMat4("projection", _camera->getProjection());
	_surface->_surfaceMesh->Draw(_shaderCam);
	_points->Draw(_shaderPoints);

	glFinish();
}

void OpenGLPatch::resizeGL(int width, int height)
{
	_width = width;
	_height = height;
	glViewport(0, 0, _width, _height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void OpenGLPatch::mousePressEvent(QMouseEvent* event)
{
	_camera->mousePressEvent(MouseButton::RightClick, event->x(), event->y());
	_mousePressed = true;
}

void OpenGLPatch::mouseReleaseEvent(QMouseEvent* event)
{
	_mousePressed = false;
	update();
}


void OpenGLPatch::mouseMoveEvent(QMouseEvent* event)
{	
	if(_mousePressed)
	{
		_camera->mouseMoveEvent(MouseButton::RightClick, event->x(), event->y());
		update();
	}
}

void OpenGLPatch::wheelEvent(QWheelEvent* event)
{
	_camera->wheelEvent(event->angleDelta().y(), event->angleDelta().x());
	update();
}

float OpenGLPatch::getRandomZ()
{
	return (-2) + (std::rand() % (2 - (-2) + 1));
}
