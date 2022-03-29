#pragma once

#include <iostream>
#include <QOpenGLWidget>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>
#include "shader.h"
#include "mesh.h"
#include "points.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_4_Core
{
	Q_OBJECT

public:
	OpenGLWidget(QWidget *parent = Q_NULLPTR);
	~OpenGLWidget();
protected:
	// OpenGL management
	// -----------------
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;

	// OpenGL events
	// -------------
	void OpenGLWidget::mousePressEvent(QMouseEvent* event);
private:
	int _width;
	int _height;
	Shader* _shader;
	Mesh* _mesh;
	Points* _points;
	GLfloat _xAtPress;
	GLfloat _yAtPress;
};
