#include "openglwidget.h"

int windowWidth = 500, windowHeight = 500;

Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0)),
						  Vertex(glm::vec3(0,0.5,0)),
						  Vertex(glm::vec3(0.5,-0.5,0))
};

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

	_mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	_shader = new Shader("basicShader");
}

void OpenGLWidget::paintGL()
{
	glClearColor(1.0f, .95f, .75f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	_shader->Bind();
	_mesh->Draw();
	glFinish();
}

void OpenGLWidget::resizeGL(int width, int height)
{
	_width = width;
	_height = height;
	glViewport(0, 0, _width, _height);
}