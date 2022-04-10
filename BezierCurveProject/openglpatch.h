#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <random>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTime>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>
#include "shader.h"
#include "mesh.h"
#include "points.h"
#include "curve.h"
#include "surface.h"
#include "camera.h"

class OpenGLPatch : public QOpenGLWidget, protected QOpenGLFunctions_4_4_Core
{
	Q_OBJECT

public:
	OpenGLPatch(QWidget *parent = Q_NULLPTR);
	~OpenGLPatch();

protected:
	// OpenGL management
	// -----------------
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;

	// OpenGL events
	// -------------
	void OpenGLPatch::mousePressEvent(QMouseEvent* event) override;
	void OpenGLPatch::mouseReleaseEvent(QMouseEvent* event) override;
	void OpenGLPatch::mouseMoveEvent(QMouseEvent* event) override;
	void OpenGLPatch::wheelEvent(QWheelEvent* event) override;

private:
	float getRandomZ();

	bool _mousePressed=false;
	int _width;
	int _height;
	QTime _myTimer;
	Shader* _shaderCam, *_shaderPoints;
	Points* _points;
	vector<Vertex> _controlPoints;
	vector<glm::vec3> test1;
	Camera* _camera;
	Surface* _surface;

	// matrices
	glm::mat4 _model;
	glm::mat4 _view;
	glm::mat4 _projection;
};
