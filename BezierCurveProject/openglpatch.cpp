#include "openglpatch.h"


OpenGLPatch::OpenGLPatch(QWidget *parent)
	: QOpenGLWidget(parent)
{

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

	_shader = new Shader("basicShader");

	vector<glm::vec3> test1 = { glm::vec3(-0.5, -0.5, 1.0), glm::vec3(-0.5, 0, 1.0), glm::vec3(0.5, 0.5, 0.0), glm::vec3(1.0, -0.5, -1.0) };
	vector<glm::vec3> test2 = { glm::vec3(-0.6, -0.6, 0.9), glm::vec3(-0.6, -0.1, 0.9), glm::vec3(0.4, 0.4, -0.1), glm::vec3(0.9, -0.6, -1.1) };
	vector<glm::vec3> test3 = { glm::vec3(-0.7, -0.7, 0.8), glm::vec3(-0.7, -0.2, 0.8), glm::vec3(0.3, 0.3, -0.2), glm::vec3(0.8, -0.7, -1.2) };
	vector<glm::vec3> test4 = { glm::vec3(-0.8, -0.8, 0.7), glm::vec3(-0.8, -0.3, 0.7), glm::vec3(0.2, 0.2, -0.3), glm::vec3(0.7, -0.8, -1.3) };

	_curve1 = new Curve(test1, test1.size());
	_curve2 = new Curve(test2, test2.size());
	_curve3 = new Curve(test3, test3.size());
	_curve4 = new Curve(test4, test4.size());
}

void OpenGLPatch::paintGL() 
{
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	_shader->Bind();
	_curve1->_curveMesh->Draw();
	_curve2->_curveMesh->Draw();
	_curve3->_curveMesh->Draw();
	_curve4->_curveMesh->Draw();
	/*_curve2->_curveMesh->Draw();
	_curve3->_curveMesh->Draw();
	_curve4->_curveMesh->Draw();*/
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