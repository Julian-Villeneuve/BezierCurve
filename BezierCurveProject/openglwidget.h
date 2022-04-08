#pragma once

#include <iostream>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>
#include "shader.h"
#include "mesh.h"
#include "points.h"
#include "curve.h"

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
	//void keyPressEvent(QKeyEvent* event) override;
private:
	int _width;
	int _height;
	Shader* _shaderPoly, *_shaderCurve;
	Mesh* _mesh, *_controlPolygon;
	Curve* _curve;
	Points* _points;			   // control points to show them on screen
	int _nbPoint = 4;
	GLfloat _xAtPress, _yAtPress, _prevX, _prevY;
	vector<Vertex> _controlVertices; // control points for bezier curve computing and then draw control polygon
};
